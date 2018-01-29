#include <iostream>
using namespace std;

template<typename Container>
void printCollection(const Container & c, ostream & out = cout)
{
	if (c.empty())
	{
		out << "(empty)";
	}
	else
	{
		typename Container::const_iterator itr = c.begin();
		out << "[ " << *itr++; // Print first item
		while (itr != c.end())
		{
			out << ", " << *itr++;
		} // end while
		out << " ]" << endl;
	} // end ifelse

}

template<typename Object>
class Vector
{
	public:
		explicit Vector(int initSize = 0) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
		{
			objects = new Object[theCapacity];
		}
		Vector(const Vector & rhs) : objects(NULL)
		{
			operator=(rhs);
		}
		~Vector()
		{
			delete[] objects;
		}

		const Vector & operator=(const Vector & rhs)
		{
			if (this != &rhs)
			{
				delete[] objects;
				theSize = rhs.size();
				theCapacity = rhs.theCapacity;

				objects = new Object[capacity()];

				for(int k = 0; k < size(); k++)
				{
					objects[k] = rhs.objects[k];
				} // end for

			}
			return *this;
		}

		void resize(int newSize)
		{
			if (newSize > theCapacity)
			{
				reserve(newSize * 2 + 1);
			} // end if

			theSize = newSize;
		}

		void reserve(int newCapacity)
		{
			if (newCapacity < theSize)
			{
				return;
			} // end if

			Object *oldArray = objects;

			objects = new Object[newCapacity];
			for (int k = 0; k < theSize; k++)
			{
				objects[k] = oldArray[k];
			} // end for

			theCapacity = newCapacity;

			delete[] oldArray;
		}

		Object & operator[](int index)
		{
			return objects[index];
		}
		const Object & operator[](int index) const
		{
			return objects[index];
		}

		bool empty() const
		{
			return size() == 0;
		}
		int size() const
		{
			return theSize;
		}
		int capacity() const
		{
			return theCapacity;
		}

		void push_back(const Object & x)
		{
			if (theSize == theCapacity)
			{
				reserve(2 * theCapacity + 1);
			} // end if
			objects[theSize++] = x;
		}

		void pop_back()
		{
			theSize--;
		}

		const Object & back() const
		{
			return objects[theSize - 1];
		}

		typedef Object * iterator;
		typedef const Object * const_iterator;

		iterator begin()
		{
			return &objects[0];
		}
		const_iterator begin() const
		{
			return &objects[0];
		}
		iterator end()
		{
			return &objects[size()];
		}
		const_iterator end() const
		{
			return &objects[size()];
		}

		enum
		{
			SPARE_CAPACITY = 16
		};

		private:
		int theSize;
		int theCapacity;
		Object * objects;
	};

int main()
{
	Vector<int> myV(10);

	for(int i = 0; i < myV.size(); i++)
	{
		myV[i] = int(3*i);
	} // end for
	printCollection(myV, cout);
	myV.push_back(91);
	printCollection(myV, cout);
	myV.pop_back();
	printCollection(myV, cout);
	cout << "The Capacity: " << myV.capacity() << endl;
	cout << "The Size:     " << myV.size() << endl;
	cout << "The begining: " << *myV.begin() << endl;
	Vector<int>::iterator myItr = myV.begin();
	myItr = myItr + 3;
	cout << "The ...: " << *myItr << endl;
	for (unsigned i = 0; i < 3; ++i)
	{
		myItr++;
		cout << "The ...: " << *myItr << endl;
	} // end for
	cout << "The ...: " << *myItr << endl;

	return 0;
}

