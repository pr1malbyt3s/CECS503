#include <iostream>
#include <vector>
#include <string>
using namespace std;

int nextPrime(int n);
int inihash(const string & key);
int inihash(int key);

template<typename HashedObj>
class HashTable
{
	public:
		explicit HashTable(int size = 11) : array(nextPrime(size))
		{
			makeEmpty();
		}

		bool contains(const HashedObj & x) const
		{
			return isActive(findPos(x));
		}

		void makeEmpty()
		{
			currentSize = 0;
			for (unsigned i = 0; i < array.size(); i++)
				array[i].info = EMPTY;
		}

		bool insert(const HashedObj & x)
		{
			// Insert x as active
			int currentPos = findPos(x);
			if (isActive(currentPos))
				return false;

			array[currentPos] = HashEntry(x, ACTIVE);

			// Rehash; see Section 5.5
			if (++currentSize > array.size() / 2)
				rehash();

			return true;
		}

		bool remove(const HashedObj & x)
		{
			unsigned currentPos = findPos(x);
			if (!isActive(currentPos))
				return false;

			array[currentPos].info = DELETED;
			return true;
		}
		void Printhash()
		{
			cout << "ACTIEV = " << ACTIVE << ", EMPTY = " << EMPTY << ", DELETED = " << DELETED << endl;

			for (unsigned j = 0; j < array.size(); j++)
			{
				if (array[j].info == ACTIVE)
				{
					cout << j << " info =  " << array[j].info << ", element = " << array[j].element << endl;
				}
				else
					cout << j << " info =  " << array[j].info << endl;
			}
		}
		enum EntryType
		{
			ACTIVE, EMPTY, DELETED
		};

	private:
		struct HashEntry
		{
				HashedObj element;
				EntryType info;

				HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY) : element(e), info(i)
				{
				}
		};

		vector<HashEntry> array;
		unsigned currentSize;

		bool isActive(int currentPos) const
		{
			return array[currentPos].info == ACTIVE;
		}

		unsigned findPos(const HashedObj & x) const
		{
			int offset = 1;
			unsigned currentPos = myhash(x);

			// Assuming table is half-empty, and table length is prime,
			// this loop terminates
			while (array[currentPos].info != EMPTY && array[currentPos].element != x)
			{
				currentPos += offset; // Compute ith probe
				offset += 2;
				cout << "I am probing " << endl;
				if (currentPos >= array.size())
					currentPos -= array.size();
			}

			return currentPos;
		}

		void rehash()
		{
			vector<HashEntry> oldArray = array;
			cout << "I am rehashing " << endl;
			// Create new double-sized, empty table
			array.resize(nextPrime(2 * oldArray.size()));
			for (unsigned j = 0; j < array.size(); j++)
				array[j].info = EMPTY;

			// Copy table over
			currentSize = 0;
			for (unsigned i = 0; i < oldArray.size(); i++)
				if (oldArray[i].info == ACTIVE)
					insert(oldArray[i].element);
		}
		int myhash(const HashedObj & x) const
		{
			int hashVal = inihash(x);

			hashVal %= array.size();
			if (hashVal < 0)
				hashVal += array.size();

			return hashVal;
		}
};

bool isPrime(int n)
{
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

int nextPrime(int n)
{
	if (n <= 0)
		n = 3;

	if (n % 2 == 0)
		n++;

	for (; !isPrime(n); n += 2)
		;

	return n;
}

int inihash(const string & key)
{
	int hashVal = 0;

	for (unsigned i = 0; i < key.length(); i++)
		hashVal = 41 * hashVal + key[i];

	return hashVal;
}

int inihash(int key)
{
	return 5*key;
}

int main()
{
	HashTable<int> H;

	const int NUMS = 7;
	const int GAP = 3;
	int i;

	cout << "Checking... (no more output means success)" << endl;

	for (i = GAP; i != 0; i = (i + GAP) % NUMS)
	{
		H.insert(i);
		cout << "Inserting " << i << endl;
	}
	H.Printhash();
	for (i = 1; i < NUMS; i += 2)
	{
		H.remove(i);
		cout << "Removing " << i << endl;
	}
	H.Printhash();
	for (i = 2; i < NUMS; i += 2)
	{
		if (!H.contains(i))
			cout << "Contains fails " << i << endl;
		else
			cout << "Contain " << i << endl;

	}
	for (i = 1; i < NUMS; i += 2)
	{
		if (H.contains(i))
			cout << "OOPS!!! " << i << endl;
		else
			cout << "Does not contain " << i << endl;

	}

	return 0;
}
