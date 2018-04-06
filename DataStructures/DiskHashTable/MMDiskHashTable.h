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

class MMDiskHashTable {

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
    MMDiskHashTable(string path, size_t maxKeySize_in, size_t maxValueSize_in) {
        file = open(path.c_str(), O_CREAT | O_RDWR, S_IRWXU);
        fileName = path;
        fileSize = FileSize1(file);
        maxKeySize = maxKeySize_in;
        maxValueSize = maxValueSize_in;
        nodeSize = maxKeySize + maxValueSize + 2;
        if(1000 % nodeSize != 0) {
            cerr << "The sum of key size + value size + 2 must divide a multiple of 1000!";
            exit(1);
        }
        if(fileSize <= 0) {             // no file, or empty file
            lseek(file, 1009, SEEK_SET);
            write(file, "", 1);
            fileSize = FileSize1(file) - 10;
            capacity = floor(fileSize / nodeSize);
            size = 0;
        } else {                        // pre-existing diskhashtable
            char numKeys[10];
            lseek(file, 0, SEEK_SET);
            read(file, numKeys, 10);
            size = stoll(numKeys);
            fileSize = FileSize1(file) - 10;
            capacity = floor(fileSize / nodeSize);
        }
        map = (char*) mmap(nullptr, FileSize1(file), PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
        string sizeString = to_string(size);
        sizeString.resize(10);
        for(size_t i = 0; i < 10; i++) {
            map[i] = sizeString[i];
        }

    }

    /**
     * Inserts a key-value pair into the disk hash table.
     * @param key
     * @param value
     * @return
     */
    bool insert(string key, string value) {
        if(key.size() > maxKeySize) {
            cerr << "A key you tried to insert into a disk hash table was larger than the set max key size!";
            exit(1);
        }
        if(value.size() > maxValueSize) {
            cerr << "A value you tried to insert into a disk hash table was larger than the set max value size!";
            exit(1);
        }
        if((double) size / capacity >= 0.75) {
            rehash();
        }

        size_t loc = 10 + (hasher(key) % capacity) * nodeSize;
        string node = key + '\t' + value;
        node.resize(nodeSize);

        while(map[loc] != '\0') {
            loc += nodeSize;
            if(loc >= FileSize1(file)) {
                loc = 10;
            }
        }

        for(size_t i = 0; i < nodeSize; i++) {
            map[loc++] = node[i];
        }

        size++;
        string sizeString = to_string(size);
        sizeString.resize(10);
        for(size_t i = 0; i < 10; i++) {
            map[i] = sizeString[i];
        }
        return false;
    }

    /**
     * Looks up the key and returns the value.
     * @param query The key to look up.
     * @return The value corresponding to the key in the hash table. Returns an empty string if not found.
     */
    string find(string query) {
        size_t loc = 10 + (hasher(query) % capacity) * nodeSize;
        string key = "";
        char* searchMap = map + loc;
        while(*searchMap != '\0') {
            auto q = extractKeyValueFromBuffer(searchMap);
            if(q.first == query) {
                return q.second;
            }
            searchMap += nodeSize;
            if(searchMap >= map + FileSize1(file)) {
                searchMap = map + 10;
            }
        }
        return "";
    }


   void CloseFile ( )
       {
       close(file);
       }
private:

    int file;
    string fileName;
    char* map;

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
    }

    void rehash() {
        string tempRehashedFileName = fileName + "_rehashed.txt";
        int rehashFile = open(tempRehashedFileName.c_str(), O_CREAT | O_RDWR, S_IRWXU);
        ssize_t doubledFileSize = (fileSize * 2) + 9;
        lseek(rehashFile, doubledFileSize, SEEK_SET);
        write(rehashFile, "", 1);
        fileSize = FileSize1(rehashFile) - 10;
        char* newMap = (char*) mmap(nullptr, FileSize1(rehashFile), PROT_READ | PROT_WRITE, MAP_SHARED, rehashFile, 0);
        size_t newCapacity = floor(doubledFileSize / nodeSize);
        string sizeString = to_string(size);
        sizeString.resize(10);
        for(size_t i = 0; i < 10; i++) {
            newMap[i] = sizeString[i];
        }
        for(int i = 0; i < capacity; i++) {
            size_t oldLocation = 10 + i * nodeSize;
            pair<string, string> result = extractKeyValueFromBuffer(map + oldLocation);
            if (result.first != "") {
                size_t newLocation = 10 + (hasher(result.first) % newCapacity) * nodeSize;

                while (newMap[newLocation] != '\0') {
                    newLocation += nodeSize;
                    if (newLocation >= FileSize1(rehashFile)) {
                        newLocation = 10;
                    }
                }

                string node = result.first + '\t' + result.second;
                node.resize(nodeSize);
                for (int i = 0; i < nodeSize; i++) {
                    newMap[newLocation++] = node[i];
                }
            }
        }
        capacity = newCapacity;
        close(file);
        remove(fileName.c_str());
        rename(tempRehashedFileName.c_str(), fileName.c_str());
        file = rehashFile;
        map = newMap;
    }

    ssize_t FileSize1(int file) {
        struct stat st;
        fstat(file, &st);
        return st.st_size;
    }

};
