/*
* hash.cpp
* 
* This program inserts a sequence of 12 integers using a table of size 17.
*
* It then uses rehashing to insert the same input sequence using a table size of 7.
*
* Hashing function used: .
*
* Created by Aaron Williams
*/

#include <iostream>

using namespace std;

hash_1(const int &, int);
insert_1(
hash_2(const int &, int);



int main() {
	
	int numsCount = 12;
	int ts_1 = 17;
	int ts_2 = 7;
	int numeros[] = {121, 81, 16, 100, 25, 0, 1, 9, 4, 36, 64, 49};
	int table_1[numsCount];
	int table_2[ts_2];
	
	//First hash table construction.
	for(int i = 0; i < numsCount; i++) {
		table_1[i] = hash_1(numeros[i], ts_1);
	}
	
	for(int j = 0; j < numsCount; j++) {
		cout << "Key Value: " << numeros[j] << " Hashed Value: " << table_1[j] << endl;
	}
}

//Hash function for first table. Uses function of key % tablesize.
int hash_1(const int & key, int tablesize) {
	return key % tablesize;
}

/*int hash_2 {

}*/