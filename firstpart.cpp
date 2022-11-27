#include <iostream>
#include <random>

using namespace std;

int main()
{

    int N=10;
    int random_integers[N];
    
    random_device rd; 									// Obtain a random number from hardware
    mt19937 gen(rd()); 									// Seed the generator
    uniform_int_distribution<> distr(1000, 10000); 		// Define the range

    for(int i=0; i<N; i++){
        random_integers[i] = distr(gen);				// Generate number
    }
    
    cout << "N = " << N <<endl;
    cout << "random_integers[0:N-1]" <<endl;
    for(int i=0; i<N; i++){
    	cout<< random_integers[i] << endl;    
    }

    return 0;
}

