#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sys/time.h>
#define N 1024

double A[N][N];
double B[N][N];
double C[N][N];

using namespace std;

double calc_time(struct timeval start, struct timeval end) {
  double start_sec = (double)start.tv_sec*1000000.0 + (double)start.tv_usec;
  double end_sec = (double)end.tv_sec*1000000.0 + (double)end.tv_usec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
};

void multiply_one(double A[][N], double B[][N], double C[][N]) 
{ 
    int i, j, k; 
    double sum;
    for (i = 0; i < N; i++) 
    { 
        for (j = 0; j < N; j++) 
        { 
            sum = 0; 
            for (k = 0; k < N; k++) {
                sum += A[i][k] *  B[k][j]; 
            }
              C[i][j] = sum;
        } 
      
    } 
} 



void multiply_two(double A[N][N], double B[N][N], double C[N][N]) 
{ 
    int i, j, k; 
    double temp;
    for (i = 0; i < N; i++) 
    {
      for (k = 0; k < N; k++) 
        {  temp = A[i][k];
            for (j = 0; j < N; j++) 
                C[i][j] += temp *  B[k][j]; 
        } 
    } 
} 

void multiply_three(double A[N][N], double B[N][N], double C[N][N]) 
{ 
    int i, j, k; 
    double temp;
    for (j = 0; j < N; j++) 
    { 
        for (k = 0; k < N; k++) 
        { 
            temp = B[k][j];
            for (i= 0; i < N; i++) {
            	C[i][j] += temp * A[i][k];
            }
                 
        } 
    } 
} 

void multiply_tiling(double A[][N], double B[][N], double C[][N]) 
{ 
    int i, j, k, ii, jj; 
    double sum;
    for (i = 0; i < N; i += 64) { 
        for (j = 0; j < N; j += 64 ) { 
            for (ii = i; ii < (i+64); ii++){
                for (jj = j; jj < (j+64); jj++){
                     sum = 0; 
                        for (k = 0; k < N; k++) {
                            sum += A[ii][k] *  B[k][jj]; 
                        }
                    C[ii][jj] = sum;
                }
            }
                
        }
            
    } 
} 

int main()
{
	srand(time(NULL));

	for (int row = 0; row < N; row++){
		for (int col = 0; col < N; col++){
    		A[row][col] = rand() % 10 + 1;
		}
	}

	for (int row = 0; row < N; row++){
		for (int col = 0; col < N; col++){
    		B[row][col] = rand() % 10 + 1;
		}
	}

	
	int choice;
	cout << "Please enter a nest ordering between one to four: " << endl;
	cin >> choice;

	struct timeval start_time, end_time;
	switch(choice){

		case 1:
			gettimeofday(&start_time, NULL);
			multiply_one(A,B,C);
			gettimeofday(&end_time, NULL);
			break;
		case 2:
			gettimeofday(&start_time, NULL);
			multiply_two(A,B,C);
			gettimeofday(&end_time, NULL);
			break;
		case 3:
			gettimeofday(&start_time, NULL);
			multiply_three(A,B,C);
			gettimeofday(&end_time, NULL);
        default:
            gettimeofday(&start_time, NULL);
            multiply_tiling(A,B,C);
            gettimeofday(&end_time, NULL);
        
	}
 
double elapsed_us = calc_time(start_time, end_time);
double elapsed_s = elapsed_us / 1000000.0;
cout << "Time= " <<  elapsed_s << " seconds." << endl;
return 0; 
} 



