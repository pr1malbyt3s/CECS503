/**
* hash.cpp created by Aaron Williams
*
* Program creates a HashTable class that demonstrates
* hash table construction and rehashing.
*
* Reference Used: 
* http://www.algolist.net/Data_structures/Hash_table/Simple_example
*/
#include <iostream>
using namespace std;

 //HashTable Class
class HashTable {
	private:
		//Entry data type
		struct Entry {
			private:
				int key;
				int hash_value;
			public:
				Entry(int key, int hash_value) {
					this->key = key;
					this->hash_value = hash_value;
				}
				int getKey() {
					return key;
				}
				int getHash() {
					return hash_value;
				}
		};
		Entry **table;
		int TS;
	public:
		//Constructor generates table for passed table size.
		HashTable() {
		}
		HashTable(int Table_Size) {
			table = new Entry* [Table_Size];
				for(int i = 0; i < Table_Size; i++) {
					table[i] = NULL;
				}
			TS = Table_Size;	
		}
		~HashTable() {
			for(int i = 0; i < TS; i++) {
				if(table[i] != NULL) {
					delete table[i];
				}
			}
			delete[] table;
		}
		//Initial hash method
		//Hash function is key mod table size.
		//Uses linear probing for collision avoidance.
		void hash_1(int key) {
			int hash_value = ((key * 3) % TS);
			while(table[hash_value] != NULL && table[hash_value]->getKey() != key) {
				hash_value = (hash_value + 1) % TS;
			}
			if(table[hash_value] != NULL) {
				delete table[hash_value];
			}
			table[hash_value] = new Entry(key, hash_value);
		}
		//Print method
		void PrintTable() {
			cout << "Table Size: " << TS << endl;
			for(int i = 0; i < TS; i++) {
				if(table[i] != NULL) {
					cout << "Key: " << table[i]->getKey() << "  Hash Value: " << table[i]->getHash() << endl;
				}
			}
			cout << endl;
		}
		//Second hashing method
		//Hash function changed to key*3 % table size in hash_1.
		//Continues to use linear probing for collision avoidance.
		void hash_2(int keys[], int keys_count) {
			int entry_count = 0;
			double load_factor = 0;
			int i = 0;
			while(i < keys_count) {
				hash_1(keys[i]); //Uses flow of original hash method.
				entry_count += 1;
				//Load factor recalculated after each entry by typecasting TS.
				load_factor = (entry_count/(double)TS);
				//Checks if load factor exceeded.
				if(load_factor > 0.5) {
					cout << "Load factor exceeded. Rehashing now. Current table: " << endl;
					PrintTable();
					resize();
					i = -1;
					entry_count = 0;
				}
				i++;
			}
		}
		//Resizing method
		void resize() {
			int old_TS = TS;
			int new_TS = TS * 2;
			int i = 2;
			//Checks for next prime number >= 2 * current table size.
			while(i < new_TS) {
				if(new_TS % i == 0) {
					new_TS = new_TS + 1;
					i = 1;
				}
				i++;
			}
			TS = new_TS;
			delete table;
			table = new Entry* [TS];
		}
};

int main() {
	//12-integer sequence to be input to hash table.
	int numeros[] = {121, 81, 16, 100, 25, 0, 1, 9, 4, 36, 64, 49};
	
	//Part 1
	HashTable *HT1 = new HashTable(17);
	for(int i = 0; i < 12; i++) {
		HT1->hash_1(numeros[i]);
	}
	HT1->PrintTable();
	
	//Part 2
	HashTable *HT2 = new HashTable(7);
	HT2->hash_2(numeros, 12);
	HT2->PrintTable();
}