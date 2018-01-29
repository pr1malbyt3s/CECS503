/**
 * A sample code of Creating C++ linked lists,
 * Including definitions the list node class and linked list class,
 * and how to create a blank linked list and a one-node linked list.
 *
 * Outline: understand the definition and structure of the linked
 * list and build a linked list based on it.
 *
 * Update: Edits made by Aaron Williams to the Node and LinkedList classes.
 * Code now produces double linked-lists.
 */

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int value; 
    Node *pNext;
    Node *pPrev; //Added 
    
public:
    /* Constructors with No Arguments */
    Node(void)
    : pNext(NULL), pPrev(NULL) //Added
    { }
    
    /* Constructors with a given value */
    Node(int val)
    : value(val), pNext(NULL), pPrev(NULL) //Added
    { }
    
    /* Constructors with a given value and links for next and previous nodes */
    Node(int val, Node* next, Node* previous)
    : value(val), pNext(next), pPrev(previous) //Added
    { }
    
    /* Getters */
    int getValue(void)
    { return value; }
    
    Node* getNext(void)
    { return pNext; }
    
    Node* getPrev(void) //Change
    { return pPrev; }
    
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *pHead;
    /* pointer of tail node */
    Node *pTail;
    
public:
    /* Constructors with No Arguments */
    LinkedList(void);
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);
    
    /* Traversing the list and printing the value of each node */
    void traverse_and_print();
	
	void push_back(int val);
};

LinkedList::LinkedList()
{
    /* Initialize the head and tail node */
    pHead = pTail = NULL;
}

LinkedList::LinkedList(int val)
{
    /* Create a new node, acting as both the head and tail node */
    pHead = new Node(val);
    pTail = pHead;
}

LinkedList::~LinkedList()
{
    
}

void LinkedList::traverse_and_print()
{
    Node *p = pHead;
    
    
    /* The list is empty? */
    if (pHead == NULL) {
        cout << "The list is empty.\n" << endl;
        return;
    }
    
    cout << "LinkedList: " << endl;
    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        /*Change from source code made here. */
        cout << "<-" << p->getPrev();
        cout << " [" << "Node Value: " << p->getValue() << ", " << p << "] ";
        cout << "->" << p->getNext() << endl;
        
        /* The pointer moves along to the next one */
        p = p->pNext;
    }
    cout << endl;
}

void LinkedList::push_back(int val){
	/*Your code here*/
	
	/*If list is empty, create a new node. */
	if (pHead == NULL) {
		pHead = new Node(val);
		pTail = pHead;
		return;
	}
	
	/*Add new node to back of the list. */
	pTail->pNext = new Node(val, NULL, pTail); //New constructor used
	/*Change tail pointer to newly added node. */
	pTail = pTail->pNext;
	
}

int main(int argc, const char * argv[])
{
    /* Create an empty list */
    LinkedList list1;
    cout << "Created an empty list named list1." << endl;
    /* output the result */
    cout << "list1:" << endl;
    list1.traverse_and_print();
   
    /* Create a list with only one node */
    LinkedList list2(10);
    cout << "Created a list named list2 with only one node." << endl;
    /* output the result */
    cout << "list2:" << endl;
    list2.traverse_and_print();
	
	/*your testing code here*/
	for (int i = 0 ; i < 10; i++){
		list2.push_back(i);
	}
	cout << "Added 10 nodes to list2." << endl;
	cout << "list2:" << endl;
	list2.traverse_and_print();
    return 0;
}



