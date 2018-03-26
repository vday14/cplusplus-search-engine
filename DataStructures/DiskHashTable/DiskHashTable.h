//
// Created by nick on 3/23/18.
//

#pragma once

#include <iostream>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

using namespace std;

ssize_t FileSize(int file) {
    struct stat st;
    fstat(file, &st);
    return st.st_size;
}

/*
 *
 * A very simple implementation of a hash table: stored on disk though! :)
 *
 * This implementation supports only insertion and lookup. Once a key is inserted, one should abstain from inserting
 * the same key. There is no error checking for this: if a duplicate key is inserted, it will permanently destroy the
 * integrity of the hash table. In addition, one cannot delete key-value pairs from the table.
 *
 * The header of the file consists of 10 bytes. These 10 bytes correspond to the number of keys in the hash table. One
 * must manually deduce or preset the key and value size.
 *
 */

class DiskHashTable {

public:

    /**
     * Constructs a disk hash table. If the file at the path is not found, or has a file size of 0, it will
     * automatically spawn a file for the disk hash table. The initial number of bytes that the hash table spawns with
     * is 1000.
     *
     * @param path
     * @param maxKeySize_in
     * @param maxValueSize_in
     */
    DiskHashTable(string path, size_t maxKeySize_in, size_t maxValueSize_in) {
        file = open(path.c_str(), O_CREAT | O_RDWR, S_IRWXU);
        fileName = path;
        fileSize = FileSize(file);
        maxKeySize = maxKeySize_in;
        maxValueSize = maxValueSize_in;
        nodeSize = maxKeySize + maxValueSize + 2;
        if(nodeSize % 10 != 0) {
            cerr << "The sum of key size + value size + 2 must be divisible by 10!";
            exit(1);
        }
        if(fileSize <= 0) {             // no file, or empty file
            lseek(file, 1009, SEEK_SET);
            write(file, "", 1);
            lseek(file, 0, SEEK_SET);
            fileSize = FileSize(file) - 10;
            capacity = floor(fileSize / nodeSize);
            size = 0;
        } else {                        // pre-existing diskhashtable
            char numKeys[10];
            lseek(file, 0, SEEK_SET);
            read(file, numKeys, 10);
            size = stoll(numKeys);
            capacity = floor(fileSize / nodeSize);
        }
    }

    /**
     * Inserts a key-value pair into the disk hash table.
     * @param key
     * @param value
     * @return
     */
    bool insert(string key, string value) {
        if((double) size / capacity >= 0.75) {
            rehash();
        }
        size_t loc = 10 + (hasher(key) % capacity) * nodeSize;
        string node = key + '\t' + value;
        node.resize(nodeSize);
        lseek(file, loc, SEEK_SET);
        char buffer[nodeSize];
        bool rewindToStart = true;
        while(read(file, buffer, nodeSize)) {
            lseek(file, -nodeSize, SEEK_CUR);
            if(buffer[0] == '\0') {
                write(file, node.c_str(), strlen(node.c_str()));
                rewindToStart = false;
                break;
            } else {
                lseek(file, nodeSize, SEEK_CUR);
            }
        }
        lseek(file, 10, SEEK_SET);
        while(rewindToStart && read(file, buffer, nodeSize)) {
            lseek(file, -nodeSize, SEEK_CUR);
            if(buffer[0] == '\0') {
                write(file, node.c_str(), strlen(node.c_str()));
                rewindToStart = false;
                break;
            } else {
                lseek(file, nodeSize, SEEK_CUR);
            }
        }
        size++;
        lseek(file, 0, SEEK_SET);
        string sizeString = to_string(size) + "\n";
        sizeString.resize(10);
        write(file, sizeString.c_str(), 10);
        return true;
    }

    /**
     * Looks up the key and returns the value.
     * @param query The key to look up.
     * @return The value corresponding to the key in the hash table. Returns an empty string if not found.
     */
    string find(string query) {
        size_t loc = 10 + (hasher(query) % capacity) * nodeSize;
        lseek(file, loc, SEEK_SET);
        char buffer[nodeSize];
        pair<string, string> result;
        size_t searched = 0;
        do {
            searched++;
            buffer[0] = '\0';
            size_t bytes = read(file, buffer, nodeSize);
            if(bytes == 0) {
                lseek(file, 10, SEEK_SET);
                read(file, buffer, nodeSize);
            }
            result = extractKeyValueFromBuffer(buffer);
            if(searched == size) {
                return "";
            }
        } while(strcmp(result.first.c_str(), query.c_str()) != 0);
        std::cout << searched << std::endl;
        return result.second;
    }

private:

    int file;
    string fileName;

    size_t size;
    size_t capacity;
    ssize_t fileSize;

    size_t maxKeySize;
    size_t maxValueSize;
    size_t nodeSize;

    std::hash<string> hasher;

    pair<string, string> extractKeyValueFromBuffer(char* buffer) {
        string key = "";
        string value = "";
        bool midVal = false;
        for (int i = 0; i < strlen(buffer); i++) {
            if (midVal) {
                value += buffer[i];
            } else if (buffer[i] == '\t') {
                midVal = true;
            } else {
                key += buffer[i];
            }
        }
        return {key, value};
    };

    void rehash() {
        string tempRehashedFileName = fileName + "_rehashed.txt";
        int rehashFile = open(tempRehashedFileName.c_str(), O_CREAT | O_RDWR, S_IRWXU);
        ssize_t doubledFileSize = fileSize * 2 + 9;
        lseek(rehashFile, doubledFileSize, SEEK_SET);
        write(rehashFile, "", 1);
        fileSize = FileSize(rehashFile) - 10;
        size_t newCapacity = floor(doubledFileSize / nodeSize);
        lseek(rehashFile, 0, SEEK_SET);
        string sizeString = to_string(size) + '\n';
        sizeString.resize(10);
        write(rehashFile, sizeString.c_str(), 10);
        for(int i = 0; i < capacity; i++) {
            size_t oldLocation = 10 + i * nodeSize;
            lseek(file, oldLocation, SEEK_SET);
            char entry[nodeSize];
            read(file, entry, nodeSize);
            pair<string, string> result = extractKeyValueFromBuffer(entry);
            if(result.first != "") {
                size_t newLocation = 10 + (hasher(result.first) % newCapacity) * nodeSize;
                lseek(rehashFile, newLocation, SEEK_SET);
                char buffer[nodeSize];
                while(read(rehashFile, buffer, nodeSize)) {
                    lseek(rehashFile, -nodeSize, SEEK_CUR);
                    if(buffer[0] == '\0') {
                        write(rehashFile, entry, strlen(entry));
                        break;
                    } else {
                        lseek(rehashFile, nodeSize, SEEK_CUR);
                    }
                }
            }
        }
        capacity = newCapacity;
        close(file);
        remove(fileName.c_str());
        rename(tempRehashedFileName.c_str(), fileName.c_str());
        file = rehashFile;
    }

};