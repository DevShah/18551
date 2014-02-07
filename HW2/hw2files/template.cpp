/*** 18551 Homework 2 Starter Code ******/

// Please add your own comments to the code before you submit 

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>

using namespace cv;

void IPCAtrain(char *trainFolderPath, int numTrain);
int read_from_file(const char* name, int* buffer, int start);
void write_to_file(const char* name, int* data, int size);

void DisplayMat(Mat MatDisp){
	for (int i = 0; i <MatDisp.rows;i++)
	{
		for(int j = 0; j < MatDisp.cols; j++)
		{
			printf("%f ", MatDisp.at<float>(i,j));
		}
		printf("\n");
	}


}

int main()
{

	
	IPCAtrain(" ", 8);
	// Call IPCAtrain to generate a text file containing eigenvectors and means of each clas

	// Call IPCAtest using a test function and see if it returns the correct class label

	// We will be testing on our own set of test images after you submit the code

	return 0;
}
void IPCAtrain(char* trainFolderPath, int numTrain)
{
	/* trainFolderPath is the path to the folder containing the training images
	   numTrain is the number of training images per class */

	// Run a loop to iterate over classes (people)
	
	
	

	for(int i = 1;i < 5;i++)
	{
		//Run a loop to iterate over images of same person and generate the data matrix for the class 
		//i.e. a matrix in which each column is a vectorized version of the face matrix under consideration

		// Subtract the mean vector from each vector of the data matrix

		// Compute the covariance matrix and generate the eigen vectors using the Gram trick
		
		// Store the eigen vectors and the mean vector in a file, which will be accessed by the IPCAtest function
	
		Mat A;;
		int * read = (int*)malloc(30000*sizeof(int));
		for(int j = 1; j <= numTrain; j++)
		{
			char num[2];
			char class_num[2];
			int c = j;
			int d = i;
			sprintf(num, "%d", c);
			sprintf(class_num, "%d", d);
			char * filename = (char*)malloc(35);
			strcat(filename, "Train_Files/class");
			strcat(filename, class_num);
			strcat(filename, "0");
			strcat(filename, num);
			strcat(filename, ".jpg");
		  	printf("%s\n", filename);
			//read_from_file(filename, read, 0);
			//Mat E = Mat(128,128);
			Mat E = imread(filename, 0);
			//add(A, E, A);
			A += E;
		}
		Mat mean;
		mean = A / 8;
		Mat EigenValues,EigenVectors;
        	eigen(A,1,EigenValues,EigenVectors);
        	//DisplayMat(EigenVectors);
		Mat Cov;
		
		cv::calcCovarMatrix(&mean, 1, Cov, mean, CV_32FC1);
		
		char * mean_file = (char *) malloc(100);
		char * cov_file = (char *) malloc(100);
		sprintf(cov_file, "cov%d", i);	 
		sprintf(mean_file, "mean%d", i);
		strcat(mean_file, ".txt");
		strcat(cov_file, ".txt");
		//int * v = (int *) malloc(128 * sizeof(int));
		//std::vector<double> v(first_row.begin<double>(), first_row.end<double>());
		for(int k = 0; k < 128; k++){
			cv::imwrite(mean_file, A);
			cv::imwrite(cov_file, Cov);
			 
		}
		
		
	}
	return;
}

int IPCAtest(char *imgName)
{
	/* imgName is the path and filename of the test image */

	// Read the eigen vectors and means for each class from file
	
	// Project the input test image onto each eigen space and reconstruct

	// Compute the reconstruction error between the input test image and the reconstructed image
	// You can use euclidean distance (or any other appropriate distance measure)

	// return the class label corresponding to the eigen space which showed minimum reconstruction error 

	int * buf = (int*)malloc(3000*sizeof(int));
	read_from_file(imgName, buf, 0);
	

	return 0;
}

int read_from_file(const char* name, int* buffer, int start){
    int buf_size = 0;
    FILE* file;
    int d;

    file = fopen(name, "rb");
    if (file == NULL){
        perror("Error opening file");
    }
   
    int i = 0;
    while(!feof(file)){
        fread(&d, sizeof(int), 1, file);
        if (i < start) i++;
        else{
            buffer[buf_size] = d;
            buf_size += 1;
        }
    }   

    fclose(file);
    return buf_size;
}

void write_to_file(const char* name, int* data, int size){
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
