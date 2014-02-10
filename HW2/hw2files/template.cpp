/*** 18551 Homework 2 Starter Code ******/

// Please add your own comments to the code before you submit 

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>

using namespace cv;

void IPCAtrain(char *trainFolderPath, int numTrain);
int IPCAtest(char *imgName);
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

	char * fileName = (char *)malloc(40);
	fileName = "311";
	IPCAtest(fileName);

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
	
		Mat A = Mat(128,128,CV_32FC1);
		int * read = (int*)malloc(30000*sizeof(int));
		Mat E = Mat(100,100, CV_32F);
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
			Mat B(A.size(), A.type());
			E = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
			E.convertTo(B, CV_32FC1);
			//add(A, E, A);
			A += B;
			//DisplayMat(A);
		}
		Mat mean;
		mean = A / 8;
		Mat EigenValues,EigenVectors;
        	eigen(A,1,EigenValues,EigenVectors);
        	//DisplayMat(EigenVectors);
		Mat Cov;
		Mat mean_2;
		Mat findMeanVec = Mat(1, mean.cols, CV_32F);
		Mat F = Mat(128, 128, CV_32F);
		mean.convertTo(F, CV_32F);	
		for(int k = 0; k < mean.cols; k++)
		{
			float findMean = 0;
			for(int l = 0; l < F.rows; l++)
			{
				findMean += F.at<float>(l, k);
			}
			findMean = findMean / mean.rows;
			findMeanVec.at<float>(0, k) = findMean;
			for(int l = 0; l < F.rows; l++)
			{
				F.at<float>(l, k) -= findMean;
			}
			
		}


		char * mean_file = (char *) malloc(100);
		char * cov_file = (char *) malloc(100);
		sprintf(cov_file, "eigen%d", i);	 
		sprintf(mean_file, "mean%d", i);
		strcat(mean_file, ".txt");
		strcat(cov_file, ".txt");
		//int * v = (int *) malloc(128 * sizeof(int));
		//std::vector<double> v(first_row.begin<double>(), first_row.end<double>());
		
		calcCovarMatrix(F, Cov, mean_2, CV_COVAR_NORMAL | CV_COVAR_ROWS);
		eigen(Cov, 1, EigenValues, EigenVectors);

		cv::FileStorage file(mean_file, cv::FileStorage::WRITE);
		cv::FileStorage file2(cov_file, cv::FileStorage::WRITE);
		file << "mean" << findMeanVec; 
		file2 << "eigen" << EigenVectors;
		file.release();
		
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

	//cv::FileStorage storage(imgName, cv::FileStorage::READ);
	cv::FileStorage e1("eigen1.txt", cv::FileStorage::READ);
	cv::FileStorage e2("eigen2.txt", cv::FileStorage::READ);
	cv::FileStorage e3("eigen3.txt", cv::FileStorage::READ);
	cv::FileStorage e4("eigen4.txt", cv::FileStorage::READ);

		
	cv::FileStorage m1("mean1.txt", cv::FileStorage::READ);
	cv::FileStorage m2("mean2.txt", cv::FileStorage::READ);
	cv::FileStorage m3("mean3.txt", cv::FileStorage::READ);
	cv::FileStorage m4("mean4.txt", cv::FileStorage::READ);

	cv::FileStorage t1(imgName, cv::FileStorage::READ);

	Mat eigen1;
	Mat eigen2;
	Mat eigen3;
	Mat eigen4;
	Mat mean1;	
	Mat mean2;	
	Mat mean3;	
	Mat mean4;	

	Mat t;

	char * filename = (char*)malloc(35);
	strcat(filename, "Test_Files/class");
	strcat(filename, imgName);
	strcat(filename, ".jpg");
	printf("%s\n", filename);	
	t = cv::imread(filename, CV_LOAD_IMAGE_UNCHANGED);
	e1["eigen"] >> eigen1; 
	e2["eigen"] >> eigen2; 
	e3["eigen"] >> eigen3; 
	e4["eigen"] >> eigen4;
	m1["mean"] >> mean1;
	m2["mean"] >> mean2;
	m3["mean"] >> mean3;
	m4["mean"] >> mean4;

	e1.release();
	e2.release();
	e3.release();
	e4.release();
	m1.release();
	m2.release();
	m3.release();
	m4.release();
	
	
	Mat A;
	t.convertTo(A, CV_32F);	
	Mat EigenValues,EigenVectors;
       	eigen(A,1,EigenValues,EigenVectors);
	float sum1 = 0;
	float sum2 = 0;
	float sum3 = 0;
	float sum4 = 0;
	for(int i = 0; i < EigenVectors.rows; i++)
	{
		sum1 += (eigen1.at<float>(i, 0) - EigenVectors.at<float>(i,0)) * (eigen1.at<float>(i,0) - EigenVectors.at<float>(i,0));
	}	
	for(int i = 0; i < EigenVectors.rows; i++)
	{
		sum2 += (eigen2.at<float>(i,0) - EigenVectors.at<float>(i,0)) * (eigen2.at<float>(i,0) - EigenVectors.at<float>(i,0));
	}	
	for(int i = 0; i < EigenVectors.rows; i++)
	{
		sum3 += (eigen3.at<float>(i,0) - EigenVectors.at<float>(i,0)) * (eigen3.at<float>(i,0) - EigenVectors.at<float>(i,0));
	}	
	for(int i = 0; i < EigenVectors.rows; i++)
	{
		sum4 += (eigen4.at<float>(i,0) - EigenVectors.at<float>(i,0)) * (eigen4.at<float>(i,0) - EigenVectors.at<float>(i,0));
	}	


	if(sum1 < sum2 && sum1 < sum3 && sum1 < sum4)
		return 1;
	else if(sum2 < sum1 && sum2 < sum3 && sum2 < sum4)
		return 2;	
	else if(sum3 < sum1 && sum3 < sum2 && sum3 < sum4)
		return 3;
	else 
		return 4;
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
