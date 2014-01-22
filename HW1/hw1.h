#ifndef FILEIO__H
#define FILEIO__H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void filter(float* signal, float* filter);
void modulate(float* signal, int signal_len, float fs, float omega);

int read_from_file(const char* name, float* buffer, int start);
void write_to_file(const char* name, float* data, int size);


#endif