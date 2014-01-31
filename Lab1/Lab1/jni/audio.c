#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <jni.h>
#include <android/log.h>

double* filter_signal(double* signal, double* filter, int signal_size, int filter_size);
void modulate(double* signal, int signal_len, double fs, double omega);
void filter();
void Java_s1418551_lab1_AudioProcessActivity_filterSignal(JNIEnv* env, jobject javaThis);
void Java_s1418551_lab1_AudioProcessAvtivity_modulateSignal(JNIEnv* env, jobject javaThis);

int read_from_file(const char* name, double* buffer, int start);
void write_to_file(const char* name, double* data, int size);

//extern "C"{
/***********************DRIVER*******************************/
void Java_s1418551_lab1_AudioProcessActivity_filterSignal(JNIEnv* env, jobject javaThis){
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "I'm in filter");
	int filter_len = 444; //Length of filter generated in MATLAB
    int signal_len = 220500; //Length of signal given to us
    int fs = 44100; //Sampling frequency
    double* noisy = calloc(signal_len, sizeof(double));
    double* filter = calloc(filter_len, sizeof(double));
    double* conv;
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Ready to read");
    read_from_file("noisy.dat", noisy, 0);
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Read noisy");
    read_from_file("filter.dat", filter, 0);
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Read filter");

    // Part 1
    conv = filter_signal(noisy, filter, signal_len, filter_len);
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "filtered signal");
    write_to_file("filterResponse.dat", noisy, signal_len);
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "wrote to file");
    free(filter);
    free(noisy);
}

void Java_s1418551_lab1_AudioProcessActivity_modulateSignal(JNIEnv* env, jobject javaThis){
    int filter_len = 444; //Length of filter generated in MATLAB
	int signal_len = 220500; //Length of signal given to us
	int fs = 44100; //Sampling frequency
	double* response = calloc(signal_len, sizeof(double));
	read_from_file("filterResponse.dat", response, 0);
    // Part 2
    modulate(response, signal_len, fs, 100000);
    write_to_file("AM.dat", response, filter_len+signal_len-1);
    free(response);

    return;
}


/******************Part 1: Noise Filtering*******************/

double* filter_signal(double* signal, double* filter, int signal_size, int filter_size){
    double * conv = calloc(signal_size + filter_size - 1, sizeof(double));

    int i;
    for(i = 0; i < filter_size + signal_size - 1; i++)
    {
    int j;
	for(j = 0; j < signal_size; j++)
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
    int i;
    for(i = 0; i < signal_len; i++){
        //sinf takes in a value in radians
        //2*pi*omega = tau*omega
        //t = i/fs
        double angle = tau*(double)(omega*(double)i/fs);
        signal[i] = signal[i]*sinf(angle);
    }
}

/***********************FILE IO******************************/
int read_from_file(const char* name, double* buffer, int start){
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "In Read File");
    int buf_size = 0;
    FILE* file;
    double d;

    file = fopen(name, "rb");
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Opened File");
    if (file == NULL){
        perror("Error opening file");
        __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "File is null");
    }
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Waiting to fread");

    int i = 0;
    while(!feof(file)){
        fread(&d, sizeof(double), 1, file);
        __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "fread");
        if (i < start) i++;
        else{
        	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "In Else");
            buffer[buf_size] = d;
            buf_size += 1;
        }
    }

    fclose(file);
    __android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Closed File");
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
//}
