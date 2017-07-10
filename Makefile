CUDA_INSTALL_PATH ?= /usr/local/cuda
VER = -4.9

CXX := /usr/bin/g++
CC := /usr/bin/gcc
LINK := $(CXX) -fPIC
CCPATH := ./gcc
NVCC  := $(CUDA_INSTALL_PATH)/bin/nvcc -ccbin $(CCPATH)

# Includes
INCLUDES = -I. -I$(CUDA_INSTALL_PATH)/include

# Libraries
LIB_CUDA := -lcuda
LIB_FFTW := -lfftw3 -lm


# Options
NVCCOPTIONS = -arch sm_30 -ptx

# Common flags
COMMONFLAGS += $(INCLUDES)
NVCCFLAGS += $(COMMONFLAGS) $(NVCCOPTIONS)
CXXFLAGS += $(COMMONFLAGS) -std=c++11 -g -O3
CFLAGS += $(COMMONFLAGS)



CUDA_OBJS = kernels.ptx 
OBJS = main.cpp.o SubsetSumSolver.cpp.o Runner.cpp.o
TARGET = solution.x
LINKLINE = $(LINK) -o $(TARGET) $(OBJS) $(LIB_CUDA) $(LIB_FFTW)

.SUFFIXES:	.c	.cpp	.cu	.o	
%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.ptx: %.cu
	$(NVCC) $(NVCCFLAGS) $< -o $@

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): prepare $(OBJS) $(CUDA_OBJS)
	$(LINKLINE)

clean:
	rm -rf $(TARGET) *.o *.ptx

prepare:
	rm -rf $(CCPATH);\
	mkdir -p $(CCPATH);\
	ln -s $(CXX) $(CCPATH)/g++;\
	ln -s $(CC) $(CCPATH)/gcc;
	

