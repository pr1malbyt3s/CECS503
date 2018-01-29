//Problem 7.15
#include <iostream>
#include <vector>

using namespace std;

void mergeSort(int[], int, int);
void merge(int[], int, int, int);
void printA(int[], int);

int main() {
	int numbers[] = {3,1,4,1,5,9,2,6};
	cout << "Array before sorting: " << endl;
	printA(numbers, 8);
	mergeSort(numbers, 0, 7);
	cout << "Array after sorting: " << endl;
	printA(numbers, 8);
	cout << numbers[7] << endl;
}

void printA(int A[], int size) {
	for(int i = 0; i < size - 1; i++) {
		cout << A[i] << ", ";
	}
	cout << A[size - 1] << endl;
}

void mergeSort(int a[], int p, int r) {
	//cout << "MergeSort being performed." << endl;
	//printA(a, 8);
	if(p < r) {
		int q = (p + r)/2;
		mergeSort(a, p, q);
		mergeSort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

void merge(int a[], int p, int q, int r) {
	int c[8];
	int i = p;
	int j = q+1;
	int k = p;
	while((i <= q) && (j <= r)) {
		if(a[i] < a[j]) {
			c[k] = a[i];
			i = i + 1;
			k = k + 1;
		}
		
		else {
			c[k] =  a[j];
			j = j + 1;
			k = k + 1;
		}
	}
	
	while(i <= q) {
		c[k] = a[i];
		i = i + 1;
		k = k + 1;
	}
	while(j <= r) {
		c[k] = a[j];
		j = j + 1;
		k = k + 1;
	}
	//Copy sorted array over.
	int l = p;
	while(l <= r) {
		a[l] = c[l];
		l = l + 1;
	}
}


