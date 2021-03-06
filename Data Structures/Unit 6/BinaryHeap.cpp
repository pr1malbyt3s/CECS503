#include <iostream>
#include <vector>
using namespace std;

class UnderflowException
{
};

template<typename Comparable>
class BinaryHeap
{
	public:
		explicit BinaryHeap(int capacity = 100) :
			array(capacity + 1), currentSize(0)
		{
		}

		explicit BinaryHeap(const vector<Comparable> & items) :
			array(items.size() + 10), currentSize(items.size())
		{
			for (int i = 0; i < items.size(); i++)
				array[i + 1] = items[i];
			buildHeap();
		}

		bool isEmpty() const
		{
			return currentSize == 0;
		}

		/**
		 * Find the smallest item in the priority queue.
		 * Return the smallest item, or throw Underflow if empty.
		 */
		const Comparable & findMin() const
		{
			if (isEmpty())
				throw UnderflowException();
			return array[1];
		}
		/**
		 * Insert item x, allowing duplicates.
		 */
		void insert(const Comparable & x)
		{
			if (currentSize == array.size() - 1)
				array.resize(array.size() * 2);

			// Percolate up
			int hole = ++currentSize;
			for (; hole > 1 && x < array[hole / 2]; hole /= 2)
			{
					array[hole] = array[hole / 2];
			}
				
			array[hole] = x;
		}

		/**
		 * Remove the minimum item.
		 * Throws UnderflowException if empty.
		 */
		void deleteMin()
		{
			if (isEmpty())
				throw UnderflowException();

			array[1] = array[currentSize--];
			percolateDown(1);
		}

		/**
		 * Remove the minimum item and place it in minItem.
		 * Throws Underflow if empty.
		 */
		void deleteMin(Comparable & minItem)
		{
			if (isEmpty())
				throw UnderflowException();

			minItem = array[1];
			array[1] = array[currentSize--];
			percolateDown(1);
		}

		void makeEmpty()
		{
			currentSize = 0;
		}

		void printHeap()
		{
			cout << "[";
			for (unsigned i = 0; i <= currentSize; i++)
				cout << array[i] << ",";
			cout << "]" << endl;
		}

	private:
		vector<Comparable> array; // The heap array
		unsigned currentSize; // Number of elements in heap


		/**
		 * Establish heap order property from an arbitrary
		 * arrangement of items. Runs in linear time.
		 */
		void buildHeap()
		{
			for (int i = currentSize / 2; i > 0; i--)
				percolateDown(i);
		}

		/**
		 * Internal method to percolate down in the heap.
		 * hole is the index at which the percolate begins.
		 */
		void percolateDown(unsigned hole)
		{
			unsigned child;
			Comparable tmp = array[hole];

			for (; hole * 2 <= currentSize; hole = child)
			{
				child = hole * 2;
				if (child != currentSize && array[child + 1] < array[child])
					child++;
				if (array[child] < tmp)
					array[hole] = array[child];
				else
					break;
			}
			array[hole] = tmp;
		}
};

int main()
{

	// BinaryHeap<int> h(7);
	//
	// h.insert(10);
	// h.printHeap();
	// h.insert(12);
	// h.printHeap();
	// h.insert(1);
	// h.printHeap();
	// h.insert(14);
	// h.printHeap();
	// h.printHeap();
	// h.insert(6);
	// h.printHeap();
	// h.insert(5);
	// h.printHeap();
	// h.insert(8);
	// h.printHeap();
	// h.insert(15);
	// h.printHeap();
	// h.insert(3);
	// h.printHeap();
	// h.insert(9);
	// h.printHeap();
	// h.insert(7);
	// h.printHeap();
	// h.insert(4);
	// h.printHeap();
	// h.insert(11);
	// h.printHeap();
	// h.insert(13);
	// h.printHeap();
	// h.insert(2);
	// h.printHeap();
	// h.insert(-2);
	//
	// h.printHeap();
	// h.deleteMin();
	// h.printHeap();
	//
	// h.printHeap();
	// h.deleteMin();
	// h.printHeap();
	//
	// h.printHeap();
	// h.deleteMin();
	// h.printHeap();
	
	BinaryHeap<string> h(4);

	h.insert("Smith");
	h.printHeap();
	h.insert("John");
	h.printHeap();
	h.insert("Mary");
	h.printHeap();
	h.insert("Mark");
	h.printHeap();
	


	return 0;
}
