# the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  CFLAGS  = -std=c++11 -c

  # the build target executable:
  TARGET = indexer/tests/test

  all: $(TARGET)

  $(TARGET): $(TARGET).cpp
		$(CC) $(CFLAGS) $(TARGET).cpp -o $(TARGET)
  clean:
		$(RM) $(TARGET)

test:
	make all
	    chmod a+x indexer/tests/test
		./indexer/tests/test indexer/tests/source/test1.txt > indexer/tests/source/test1out.txt
		diff test1out.txt test1.out.correct.txt

