# Common binaries
GCC             ?= gcc

# Debug build flags
ifeq ($(dbg),1)
      CCFLAGS   += -g
      NVCCFLAGS += -g -G
      TARGET    := debug
else
      TARGET    := release
endif


# Common includes and paths
LDFLAGS       := -lm
CFLAGS  = -O3

# Target rules
all: build

build: hw1

run: build
	./test

clean:
	rm -f hw1 *.o core.* gnuplot_tmpdatafile_* *.a out.bin