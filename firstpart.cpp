#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <cmath>
#include <chrono>


using namespace std;

int find_min_sorted(int array[]){
    return array[0];
}
int find_max_sorted(int array[], int N){
    return array[N-1];

}
int find_mode(int array[], int N){
    int number = array[0];
    int mode = number;
    int count = 1;
    int countMode = 1;

    for (int i=1; i<N; i++){
        if (array[i] == number){                            // count occurrences of the current number
            count++;
        }
        else{                                               // now this is a different number
            if (count > countMode){
                countMode = count;                          // mode is the biggest ocurrences
                mode = number;
            }
            count = 1;                                      // reset count for the new number
            number = array[i];
        }
    }
    return mode;
}
double find_median(int array[], int N){
    if(N % 2){
        // N: odd
        return array[(N-1)/2];     
    }else{
        // N : even => Median = (array[(N+1)/2] + array[(N-1)/2]) / 2   
        return (array[(N+1)/2] + array[(N-1)/2]) / (double)2;
    }
}
int find_sum(int array[], int N){
    int sum = 0; 
    for (int i = 0; i < N; i++){
        sum += array[i]; 
    }
    return sum;
}

double find_arithmetic_mean(int sum, int N){
    return ((double) sum)/N;
}

double find_harmonic_mean(int array[], int N){
    double sum = 0.0;
    for (int i = 0; i < N; i++){
        sum = sum + (double)1 / array[i];
    }
    return (double)N / sum;
}

double find_standard_deviation(int array[], int N, double arithmetic_mean){
    double sd = 0.0;
    for(int i=0; i<N; i++){
        sd += pow(array[i] - arithmetic_mean,2);
    }
    return sqrt(sd/N);
}

double find_interquartile_range(int array[], int N){
    double first_median;
    double second_median;


    if(N % 2){
        // N: odd
        int quartile_size = ((N-1)/2);
        if( quartile_size % 2 ){
            // quartile_size : odd
            return 0.0;
        }else{
            // quartile_size : even
            return 0.0;
        }
    }else{
        // N : even => Median = (array[(N+1)/2] + array[(N-1)/2]) / 2   
        return (array[(N+1)/2] + array[(N-1)/2]) / (double)2;
    }


}

int main(int argc, char** argv){


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    /*Initialize the array*/
    int N = atoi(argv[1]);                              // Cast string input to int 
    int random_integers[N];                             // Array declaration
    random_device rd; 									// Obtain a random number from hardware
    mt19937 gen(rd()); 									// Seed the generator
    uniform_int_distribution<> distr(1000, 10000); 		// Define the range
    for(int i=0; i<N; i++){                  
        random_integers[i] = distr(gen);				// Generate number
    }

    /*Sort the array and benefit*/
    sort(random_integers, random_integers + N);
    int min = find_min_sorted(random_integers);
    int max = find_max_sorted(random_integers, N);
    int range = find_max_sorted(random_integers, N) - find_min_sorted(random_integers);
    int mode = find_mode(random_integers, N);
    double median = find_median(random_integers, N);
    int sum = find_sum(random_integers, N);
    double arithmetic_mean = find_arithmetic_mean(find_sum(random_integers, N), N);
    double harmonic_mean = find_harmonic_mean(random_integers, N);
    double standard_deviation = find_standard_deviation(random_integers, N, find_arithmetic_mean(find_sum(random_integers, N), N));

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();



    ofstream MyFile("output1.txt");                    // Create, open, write and close a text file
    MyFile << min <<endl;
    MyFile << max <<endl;
    MyFile << range <<endl;
    MyFile << mode <<endl;
    MyFile << median <<endl;
    MyFile << sum <<endl;
    MyFile << arithmetic_mean <<endl;
    MyFile << harmonic_mean <<endl;
    MyFile << standard_deviation <<endl;
    MyFile << find_interquartile_range <<endl;
    MyFile << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / (double)1000000000 << endl;







    MyFile.close();
    return 0;                                          // End of main()
}

