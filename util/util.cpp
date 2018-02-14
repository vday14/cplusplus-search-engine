//
// Created by Ben Bergkamp on 2/13/18.
//

#include "util.h"
namespace util
	{

		size_t FileSize(int f)
			{
			struct stat fileInfo;
			fstat(f, &fileInfo);
			return fileInfo.st_size;
			}


		int getFileDescriptor(string fileName, string type)
			{
			if (type == "R") {
				return open(fileName.c_str(), O_RDONLY);
			} else if (type == "W") {
				return open(fileName.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			}


			}


		char *getFileMap(string fileName)
			{

			string localPath = util::GetCurrentWorkingDir();
			fileName = localPath + fileName;
			int f = open(fileName.c_str(), O_RDONLY);
			if (f != -1) {
				size_t fileSize = FileSize(f);
				char *map = (char *) mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, f, 0);
				if (map != MAP_FAILED) {
					return map;
				}
			}
			return nullptr;
			}


		char *getFileMap(int fileDescriptor)
			{
			if (fileDescriptor != -1) {
				size_t fileSize = FileSize(fileDescriptor);
				char *map = (char *) mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fileDescriptor, 0);
				if (map != MAP_FAILED) {
					return map;
				}
			}
			return nullptr;
			}


		int writeToNewFileToLocation(char *fileContents, string locationOnDisk)
			{
			int fileSize = strlen(fileContents);

			int fd = creat(locationOnDisk.c_str(), S_IRWXU);
			ssize_t bytes_written = 0;
			if (fd != -1)
				bytes_written = write(fd, fileContents, fileSize);
			else
				cout << "ERROR CREATING FILE\n";

			if (bytes_written != fileSize)
				cout << "ERROR: Only " << bytes_written << " bytes written\n";


			return fd;

			}


		string GetCurrentWorkingDir(void)
			{

			return (getenv("PWD"));;
			}
	}