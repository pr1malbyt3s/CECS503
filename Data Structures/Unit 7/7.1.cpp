#include <iostream>
#include <vector>

using namespace std;

void sort(vector<int> a) {
	int k = 0;
	int tmp = 0;
	
	for(int i = 1; i < a.size(); i++) {
		tmp = a[i];
		for(k = i; k > 0 && tmp < a[k-1]; k--) {
			a[k] = a[k-1];
		}
		a[k] = tmp;
		cout << "Pass " << i << endl;
		cout << "Current Order: ";
		for(int i = 0; i < a.size() - 1; i++) {
			cout << a[i] << ", ";
		}
		cout << a[a.size()-1];
		cout << endl;
	}
}

int main() {
	vector<int> a = {3,1,4,1,5,9,2,6,5};
	sort(a);
}