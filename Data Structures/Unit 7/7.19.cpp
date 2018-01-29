//Problem 7.19
//Referenced: Provided course source code and
//Data Structures and Algorithm Analysis in C++
#include <iostream>
#include <vector>

using namespace std;

const int & median3(vector<int> &, int , int);
void quicksort(vector<int> &, int, int);
void insertionSort(vector<int> &, int, int);
void printV(vector<int>);

int main() {
	vector <int> numeros = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
	cout << "Array before sorting: " << endl;
	printV(numeros);
	quicksort(numeros, 0, numeros.size() - 1);
	cout << "Array after sorting: " << endl;
	printV(numeros);
}

//Method to print vector.
void printV(vector<int> p) {
	for(int i = 0; i < p.size() - 1; i++) {
		cout << p[i] << ", ";
	}
	cout << p[p.size() - 1] << endl;
}

//Median-of-three partitioning.
//Finds median of first element, last element, and center element.
const int & median3(vector<int> & a, int left, int right) {
	int center = (left + right)/2;
	if(a[center] < a[left]) {
		swap(a[left], a[center]);
	}
	if(a[right] < a[right]) {
		swap(a[left], a[right]);
	}
	if(a[right] < a[center]) {
		swap(a[center], a[right]);
	}
	//Pivot position placed at right - 1.
	swap(a[center], a[right - 1]);
	return a[right - 1];
}

void quicksort(vector<int> & a, int left, int right) {
	//cout << "QuickSort being performed." << endl;
	//printV(a);
	if(left + 3 <= right) {
		int pivot = median3(a, left, right);
		cout << "Three: " << left << right << endl;
		cout << "Pivot = " << pivot << endl;
		int i = left;
		int j = right - 1;
		//Infinite Loop
		for( ; ; ) {
			while(a[++i] < pivot) {}
			while(pivot < a[--j]) {}
			if(i < j) {
				swap(a[i], a[j]);
			}
			else {
				break;
			}
		}
		//Restore the pivot
		swap(a[i], a[right - 1]);
		//Sort small elements
		quicksort(a, left, i - 1);
		//Sort large elements
		quicksort(a, i + 1, right);
	}
	else {
		insertionSort(a, left, right);
	}
}

void insertionSort(vector<int> & a, int low, int high) {
	//cout << "InsertionSort being performed." << endl;
	//printV(a);
	for(int p = low + 1; p <= high; p++) {
		int tmp = a[p];
		int j;
		for(j = p; j > low && tmp < a[j-1]; j--) {
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
}