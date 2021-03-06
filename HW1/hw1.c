#include "hw1.h"
#include <math.h>

/***********************DRIVER*******************************/
int main(){
    int filter_len = 444; //Length of filter generated in MATLAB
    int signal_len = 220500; //Length of signal given to us
    int fs = 44100; //Sampling frequency
    double* noisy = calloc(signal_len, sizeof(double));
    double* filter = calloc(filter_len, sizeof(double));
    double* conv;
    read_from_file("noisy.dat", noisy, 0);
    read_from_file("filter.dat", filter, 0);

    // Part 1
    conv = filter_signal(noisy, filter, signal_len, filter_len);
    write_to_file("filterResponse.dat", noisy, signal_len);
    free(filter);
    // Part 2
    modulate(conv, signal_len, fs, 10000);
    write_to_file("AM.dat", conv, filter_len+signal_len-1);
    free(noisy);

    return 0;
}


/******************Part 1: Noise Filtering*******************/

double* filter_signal(double* signal, double* filter, int signal_size, int filter_size){
    //TODO: Convolve signal with filter

    double * conv = calloc(signal_size + filter_size - 1, sizeof(double));

	
    for(int i = 0; i < filter_size + signal_size - 1; i++)
    {
	for(int j = 0; j < signal_size; j++)
	{
            if(i - j >= 0){
	    	conv[i] = signal[j] * filter[i - j];		
	    }
	}
    }
 
    return conv;

}


/***********************Part 2: Modulation*******************/

//multiply a signal in the time domain by a sign wave of frequency omega
void modulate(double* signal, int signal_len, double fs, double omega){
    double tau = 6.283185; //2*pi
    for(int i = 0; i < signal_len; i++){
        //sinf takes in a value in radians
        //2*pi*omega = tau*omega
        //t = i/fs
        double angle = tau*(double)(omega*i/fs); 
        //signal[i] = sqrt((signal[i]*sin(angle) + signal[i]*cos(angle))*(signal[i]*sin(angle)+signal[i]*cos(angle))); 
    	signal[i] = abs(signal[i]*sin(angle) + signal[i]*cos(angle));
    }
}

/***********************FILE IO******************************/
int read_from_file(const char* name, double* buffer, int start){
    int buf_size = 0;
    FILE* file;
    double d;

    file = fopen(name, "rb");
    if (file == NULL){
        perror("Error opening file");
    }
   
    int i = 0;
    while(!feof(file)){
        fread(&d, sizeof(double), 1, file);
        if (i < start) i++;
        else{
            buffer[buf_size] = d;
            buf_size += 1;
        }
    }   

    fclose(file);
    return buf_size;
}

void write_to_file(const char* name, double* data, int size){
    FILE* file;
    int nbytes = 0;

    file = fopen(name, "a+");
    if (file == NULL){
        perror("Error opening file");
    }
    
    int i;
    for(i = 0; i < size; i++){
        fwrite(&data[i], sizeof(double), 1, file);
    }

    fclose(file);

    return;
}
