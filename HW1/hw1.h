#ifndef FILEIO__H
#define FILEIO__H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* filter_signal(double* signal, double* filter, int signal_size, int filter_size);
void modulate(double* signal, int signal_len, double fs, double omega);

int read_from_file(const char* name, double* buffer, int start);
void write_to_file(const char* name, double* data, int size);


#endif
