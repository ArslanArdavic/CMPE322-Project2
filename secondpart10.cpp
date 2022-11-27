#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

using namespace std;

int* list;

int minimum;
int maximum;
int range;
int mode;
double median;
int sum;
double arithmetic_mean;
double harmonic_mean;
double standard_deviation;
double interquartile_range;

void *find_min_sorted(void *param);
void *find_max_sorted(void *param);
void *find_range(void *param);
void *find_mode(void *param);
void *find_median(void *param);
void *find_sum(void *param);
void *find_arithmetic_mean(void *param);
void *find_harmonic_mean(void *param);
void *find_standard_deviation(void *param);
void *find_interquartile_range(void *param);




int main(int argc, char** argv){

    /*Initialize the array*/
    int N = atoi(argv[1]);                              // Cast string input to int 
    pthread_t tid_1;pthread_t tid_4;pthread_t tid_7;
    pthread_t tid_2;pthread_t tid_5;pthread_t tid_8;
    pthread_t tid_3;pthread_t tid_6;pthread_t tid_9;pthread_t tid_10;
    pthread_t tidList[10];

    list = (int*) malloc(sizeof(int)*N); 
    random_device rd; 									// Obtain a random number from hardware
    mt19937 gen(rd()); 									// Seed the generator
    uniform_int_distribution<> distr(1000, 10000);

    for(int i=0; i<N; i++){                  
        list[i] = distr(gen);				// Generate number
    }

    /*Sort the array and benefit*/
    sort(list, list + N);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	pthread_create(&tid_1, 0, find_min_sorted, &N);
    pthread_create(&tid_2, 0, find_max_sorted, &N);
    pthread_create(&tid_3, 0, find_range, &N);
    pthread_create(&tid_4, 0, find_mode, &N);
    pthread_create(&tid_5, 0, find_median, &N);
    
    pthread_create(&tid_6, 0, find_sum, &N);
    pthread_create(&tid_7, 0, find_arithmetic_mean, &N);
    pthread_create(&tid_8, 0, find_harmonic_mean, &N);
    pthread_create(&tid_9, 0, find_standard_deviation, &N);
    pthread_create(&tid_10, 0, find_interquartile_range, &N);
    

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    pthread_join(tid_3, NULL);
    pthread_join(tid_4, NULL);
    
    pthread_join(tid_5, NULL);
    pthread_join(tid_6, NULL);
    pthread_join(tid_7, NULL);
    pthread_join(tid_8, NULL);
    pthread_join(tid_9, NULL);
    pthread_join(tid_10, NULL);
    
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    ofstream MyFile("output2.txt");                    // Create, open, write and close a text file
    MyFile << minimum <<endl;
    MyFile << maximum <<endl;
    MyFile << range <<endl;
    MyFile << mode <<endl;
    MyFile << median <<endl;
    MyFile << sum <<endl;
    MyFile << arithmetic_mean <<endl;
    MyFile << harmonic_mean <<endl;
    MyFile << standard_deviation <<endl;
    MyFile << interquartile_range <<endl;
    
    MyFile << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / (double)1000000000 << endl;
    MyFile.close();
    return 0;       
}

void *find_min_sorted(void *param){
    minimum = list[0];
    pthread_exit(0);
}
void *find_max_sorted(void *param){
    int N = *(int *) param;
    maximum = list[N-1];
    pthread_exit(0);
}
void *find_range(void *param){
    int N = *(int *) param;
    range = list[N-1] - list[0];
    pthread_exit(0);
}
void *find_mode(void *param){
    int N = *(int *) param;
    int number = list[0];
    int mode = number;
    int count = 1;
    int countMode = 1;

    for (int i=0; i<N; i++){
        if (list[i] == number){                            // count occurrences of the current number
            count++;
        }
        else{                                               // now this is a different number
            if (count > countMode){
                countMode = count;                          // mode is the biggest ocurrences
                mode = number;
            }
            count = 1;                                      // reset count for the new number
            number = list[i];
        }
    }
    pthread_exit(0);
}

void *find_median(void *param){
    int N = *(int *) param;
    if(N % 2){
        // N: odd
        median = list[(N-1)/2];     
    }else{
        // N : even => Median = (array[(N+1)/2] + array[(N-1)/2]) / 2   
        median = (list[(N+1)/2] + list[(N-1)/2]) / (double)2;
    }
    pthread_exit(0);
}

void *find_sum(void *param){
    int N = *(int *) param;
    sum = 0; 
    for (int i = 0; i < N; i++){
        sum += list[i]; 
    }
    pthread_exit(0);
}

void *find_arithmetic_mean(void *param){
    int N = *(int *) param;
    int zumme = 0;
    for (int i = 0; i < N; i++){
        zumme += list[i]; 
    }
    arithmetic_mean = zumme/(double)N;
    pthread_exit(0);
}



void *find_harmonic_mean(void *param){
    int N = *(int *) param;
    double Zumme = 0.0;
    for (int i = 0; i < N; i++){
        Zumme = Zumme + (double)1 / list[i];
    }
    harmonic_mean = (double)N / Zumme;
    pthread_exit(0);

}
void *find_standard_deviation(void *param){
    int N = *(int *) param;
    double sd = 0.0;
    for(int i=0; i<N; i++){
        sd += pow(list[i] - arithmetic_mean,2);
    }
    standard_deviation =  sqrt(sd/N);
    pthread_exit(0);

}

void *find_interquartile_range(void *param){
    int N = *(int *) param;
    interquartile_range = 0.0;
    pthread_exit(0);
}