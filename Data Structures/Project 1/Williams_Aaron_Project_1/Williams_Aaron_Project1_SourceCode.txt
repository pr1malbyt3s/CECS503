/* Search.cpp implemented with Node, Edge, and Trie classes. Will return
* all possible words in Trie based on prefix entered by user.
*
* Aaron Williams, CECS 503, University of Louisville
*
* Referenced: 
* http://yucoding.blogspot.com/2015/06/leetcode-question-implement-trie-prefix.html
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Node;
class Edge;

//Node class: represents a node in the trie.
class Node {
	public:
		Node() {
			qv = 0;
			//Set all elements of edge array to NULL.
			for(int i = 0; i < 37; i++) {
				edges[i] = NULL;
			}
		}
		~Node() {}
		//Query value assigned to valid node.
		int qv;
		//String or substring contained in node. 
		string data;
		//Array of pointers to potential edges of the node.
		Edge* edges[37];
		//Assigns the current substring to the node.
		void assign(string data) {
			this->data = data;
		}
};

//Edge class: represents the edge connecting two nodes.
class Edge {
	public:
		Edge() {
			 //Sets initial edge value to null byte.
			letter = '0';
		}
		~Edge() {}
		//Letter referenced by edge.
		char letter; 
		//Edge child  node.
		Node* c;
		//Edge parent node. 
		Node* p;
};

//Trie class: combination of nodes and edges.
class trie {
	private:
	//Root node of trie.
	Node* root; 
	//Iterator used to assign values to nodes.
	int value;
	friend void trieFind(trie &, string);
	friend void CLI(trie &);
	public:
		trie() {
			root = new Node();
			value = 0;
		}
		~trie() {
			delete root;
		}
		
		//Inserts a string into the trie.
		void insert(string s) {
			Node *a = root;
			int len = s.size();
			for(int i = 0; i < len; i++) {
				int d = 0;
				//Checks if character at current string position is digit.
				//If so, assigns it in array based on its value.
				if(isdigit(s[i])) {
					d = s[i] - '0' + 1;
				}
				//Checks if character at current string position is char.
				//If so, assigns it in array based on its decimal value.
				else if(isalpha(s[i])) {
					d = s[i] - 'a' + 11;
				}
				if(! a->edges[d]) {
					//Creates new edge for the position.
					a->edges[d] = new Edge();
					//Creates new child node for the edge.
					a->edges[d]->c = new Node();
					//Assigns the current letter to the edge.
					a->edges[d]->letter = s[i];
					//Assigns the current substring to the child node.
					a->edges[d]->c->assign(s.substr(0,i+1)); 
					//Assigns the current node as the parent node of new edge.
					a->edges[d]->p = a;
				}
				//Iterates current node to newly created node.
				a = a->edges[d]->c;
			}
			//Increase count iterator by one.
			value++;
			//Assigns an integer value to last node in string sequence.
			a->qv = value; 
		}
		
		//Searches trie for a given string.
		bool search(string s) {
			Node *a = root;
			int len = s.size();
			for(int i = 0; i < len; i++) {
				int d = 0;
				//Checks if character at current string position is digit.
				//If so, assigns it in array based on its value.
				if(isdigit(s[i])) {
					d = s[i] - '0' + 1;
				}
				//Checks if character at current string position is char.
				//If so, assigns it in array based on its decimal value.
				else if(isalpha(s[i])) {
					d = s[i] - 'a' + 11;
				}
				//Checks if edge exists. If so, iterates to next node.
				if(a->edges[d]) {
					a = a->edges[d]->c;
				}
				else {
					cout << s << " not found." << endl;
					return false;
				}
			}
			//If nodes query value is not zero, it means it is the end node
			//in the sequence for the string.
			if(a->qv != 0) {
				cout << s << " present in Trie." << endl;
				cout << "Value: " << a->qv << endl;
				return true;
			}
			else {
				cout << s << " not found." << endl;
				return false;
			}
		}
};

//Builds trie using a given file.
void trieBuild(trie & Trie, string fileName) {
	ifstream file (fileName);
	//Checks if file exists.
	if(!file) {
		cout << "Unable to locate file." << endl;
		exit(1);
	}
	string line;
	//Continues until end of file.
	while(getline(file, line)) {
		if(line.empty()) {
			continue;
		}
		//Calls insert method from trie class.
		Trie.insert(line);
	}
	file.close();
}

void trieFind(trie & Trie, string prefix) {
	Node* a = Trie.root;
	int len = prefix.size();
	for(int i = 0; i < len; i++) {
			int d = 0;
			//Checks if character at current string position is digit.
			//If so, assigns it in array based on its value.
			if(isdigit(prefix[i])) {
				d = prefix[i] - '0' + 1;
			}				
			//Checks if character at current string position is char.
			//If so, assigns it in array based on its decimal value.
			else if(isalpha(prefix[i])) {
				d = prefix[i] - 'a' + 11;				
			}
			//Checks if edge exists. If so, iterates to next node.
			if(a->edges[d]) {
				a = a->edges[d]->c;
			}
			//If edge doesn't exist, it exits function.
			else if(! a->edges[d]) {
				cout << "No entries found for prefix: " << prefix << endl;
				return;
			}
	}
	//Checks if prefix is a valid search query.
	if(a->qv != 0) {
		cout << prefix << endl;
	}
	//Iterates through current node edges.
	for(int j = 0; j < 37; j++) {
		if(a->edges[j]) {
			//Utilizes recursive function call.
			trieFind(Trie, a->edges[j]->c->data);
		}
	}
}

void CLI(trie & Trie) {
	//Prefix to be searched.
	string word;
	//User response for another search.
	string response;
	//Prompts user for prefix.
	cout << "Please enter prefix to search for: " << endl;
	cin >> word;
	cout << endl;
	//Calls trieFind and prints results.
	cout << "Results: " << endl;
	trieFind(Trie, word);
	cout << endl;
	//Asks user for another search.
	cout << "Search again? Enter y for yes." << endl;
	cin >> response;
	if(response == "y" || response == "Y") {
		cout << endl;
		CLI(Trie);
	}
}

int main() {
	//Trie initialized.
	trie Trie;
	//Trie built using dictionary.txt file.
	trieBuild(Trie, "dictionary.txt");
	//Perform search on Trie.
	CLI(Trie);
}