VER = -4.9

CXX := /usr/bin/g++
CC := /usr/bin/gcc
LINK := $(CXX) -fPIC
CCPATH := ./gcc

# Includes
INCLUDES = -I. 

# Libraries
LIB_FFTW := -lfftw3 -lm


# Options

# Common flags
COMMONFLAGS += $(INCLUDES)
CXXFLAGS += $(COMMONFLAGS) -std=c++11 -g -O3
CFLAGS += $(COMMONFLAGS)


OBJS = main.cpp.o SubsetSumSolver.cpp.o Runner.cpp.o
TARGET = solution.x
LINKLINE = $(LINK) -o $(TARGET) $(OBJS) $(LIB_FFTW)

.SUFFIXES:	.c	.cpp	.cu	.o	
%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): prepare $(OBJS)
	$(LINKLINE)

clean:
	rm -rf $(TARGET) *.o *.ptx

prepare:
	rm -rf $(CCPATH);\
	mkdir -p $(CCPATH);\
	ln -s $(CXX) $(CCPATH)/g++;\
	ln -s $(CC) $(CCPATH)/gcc;
	

