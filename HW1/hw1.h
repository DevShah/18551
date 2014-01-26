#ifndef FILEIO__H
#define FILEIO__H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float* filter_signal(float* signal, float* filter, int signal_size, int filter_size);
void modulate(float* signal, int signal_len, float fs, float omega);

int read_from_file(const char* name, float* buffer, int start);
void write_to_file(const char* name, float* data, int size);


#endif
