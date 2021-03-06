#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <jni.h>
#include <android/log.h>

double* filter_signal(double* signal, double* filter, int signal_size,
		int filter_size);
void modulate(double* signal, int signal_len, double fs, double omega);
void filter();
void Java_s1418551_lab1_AudioProcessActivity_filterSignal(JNIEnv* env,
		jobject javaThis);
void Java_s1418551_lab1_AudioProcessAvtivity_modulateSignal(JNIEnv* env,
		jobject javaThis);

int read_from_file(const char* name, double* buffer, int start);
void write_to_file(const char* name, double* data, int size);

//extern "C"{
/***********************DRIVER*******************************/
void Java_s1418551_lab1_AudioProcessActivity_filterSignal(JNIEnv* env,
		jobject javaThis) {
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "I'm in filter");
	int filter_len = 444; //Length of filter generated in MATLAB
	int signal_len = 220500; //Length of signal given to us
	int fs = 44100; //Sampling frequency
	double* noisy = calloc(signal_len, sizeof(double));
	double* filter = calloc(filter_len, sizeof(double));
	double* conv;
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Ready to read");
	read_from_file(
			"/storage/emulated/0/Android/data/com.dropbox.android/files/scratch/noisy.dat",
			noisy, 0);
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Read noisy");
	read_from_file(
			"/storage/emulated/0/Android/data/com.dropbox.android/files/scratch/filter.dat",
			filter, 0);
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Read filter");

	// Part 1
	conv = filter_signal(noisy, filter, signal_len, filter_len);
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "filtered signal");
	write_to_file("/storage/emulated/0/Android/data/com.dropbox.android/files/scratch/filterResponse.dat", noisy, signal_len);
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "wrote to file");
	free(filter);
	free(noisy);
}

void Java_s1418551_lab1_AudioProcessActivity_modulateSignal(JNIEnv* env,
		jobject javaThis) {
	int filter_len = 444; //Length of filter generated in MATLAB
	int signal_len = 220500; //Length of signal given to us
	int fs = 44100; //Sampling frequency
	double* response = calloc(signal_len, sizeof(double));
	read_from_file("/storage/emulated/0/Android/data/com.dropbox.android/files/scratch/filterResponse.dat", response, 0);
	// Part 2
	modulate(response, signal_len, fs, 100000);
	write_to_file("/storage/emulated/0/Android/data/com.dropbox.android/files/scratch/AM.dat", response, filter_len + signal_len - 1);
	free(response);

	return;
}

/******************Part 1: Noise Filtering*******************/

double* filter_signal(double* signal, double* filter, int signal_size,
		int filter_size) {
	double * conv = calloc(signal_size + filter_size - 1, sizeof(double));
	int i;
	for (i = 0; i < filter_size + signal_size - 1; i++) {

		//__android_log_print(ANDROID_LOG_ERROR, "USER_PRINT",
		//		"In filter Signal %d, %d, %d, %d", i, filter_size + signal_size,
		//		filter_size, signal_size);

		int j;
		for (j = 0; j <= i; j++) {
			if (i - j >= 0) {
				conv[i] = signal[j] * filter[i - j];

			}
		}
	}

	return conv;

}

/***********************Part 2: Modulation*******************/

//multiply a signal in the time domain by a sign wave of frequency omega
void modulate(double* signal, int signal_len, double fs, double omega) {
	double tau = 6.283185; //2*pi
	int i;
	for (i = 0; i < signal_len; i++) {
		//sinf takes in a value in radians
		//2*pi*omega = tau*omega
		//t = i/fs
		double angle = tau * (double) (omega * (double) i / fs);
        //signal[i] = sqrt((signal[i]*sin(angle) + signal[i]*cos(angle))*(signal[i]*sin(angle)+signal[i]*cos(angle)));
        signal[i] = abs(signal[i]*sin(angle) + signal[i]*cos(angle));
    }
}

/***********************FILE IO******************************/
int read_from_file(const char* name, double* buffer, int start) {
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "In Read File");
	int buf_size = 0;
	FILE* file;
	double d;

	//chdir("/data/data/s14_18551.lab1/files/");
	file = fopen(name, "rb");

	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", name);

	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Opened File");
	if (file == NULL) {
		perror("Error opening file");
		__android_log_print(ANDROID_LOG_ERROR, "USER_PRINT", "FOPEN FAIL");
	}

	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Waiting to fread");

	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", name);

	int i = 0;
	while (!feof(file)) {
		fread(&d, sizeof(double), 1, file);

		if (i < start)
			i++;
		else {
			buffer[buf_size] = d;
			buf_size += 1;
			//__android_log_print(ANDROID_LOG_ERROR, "USER_PRINT", "fread %d", buf_size);
		}
	}
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "In Else");
	fclose(file);
	__android_log_write(ANDROID_LOG_ERROR, "USER_PRINT", "Closed File");
	return buf_size;
}

void write_to_file(const char* name, double* data, int size) {
	FILE* file;
	int nbytes = 0;

	file = fopen(name, "a+");
	if (file == NULL) {
		perror("Error opening file");
	}

	int i;
	for (i = 0; i < size; i++) {
		fwrite(&data[i], sizeof(double), 1, file);
	}

	fclose(file);

	return;
}
//}
