#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

double loop(int);

int main() {
double growth = 0;
loop(2);
loop(4);
loop(8);
loop(16);
loop(32);

return 0;
	
}

double loop(int N) {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	int sum = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < i*i; j++) {
			if(j % i == 0) { 
				for(int k = 0; k < j; k++) {
					sum++;
				}
			}	
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double duration = duration_cast<nanoseconds>(t2 - t1).count();
	cout << "N: " << N << endl;
	cout << "Runtime: " << duration << endl;
	return duration;
}