//Initial tree class implementation for search.cpp

//Create trie data structure using dictionary.txt
//Each line is a valid search query

//Root node has edges with letter values pointing to nodes with same letter values.
//If you search a string, it finds the edge, then occupies the node and removes that letter
//from the string being searched.

//Use a boolean value to indicate if a node is a valid search query or not.

//Searching for a query in the trie should yield depth first traversal results.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct trienode;
struct root;

struct trienode {
			friend struct edge;
			friend class trie;
			private:
				vector<edge> edges;
			public:
				string data; //Letters in node.
				int qv; //Valid query value.
				trienode() {
				}
				trienode(string data) {
					this->data = data;
					this->qv = 0;
				}
				string getString() {
					return data;
				}
				int getQV() {
					return qv;
				}
		};

struct edge {
			friend struct trienode;
			friend class trie;
			private:
				trienode* p; //Node above edge.
				trienode* c; //Node below edge.
				char letter;
			public:
				edge() {
				}
				edge(char letter) {
					this->letter = letter;
				}
				char assign_letter(char letter) {
					this->letter = letter;
					return letter;
				}
		};
		



//Trie class
class trie {
	private:
		trienode* root = new trienode();
	
	public:
		trie() {
		
		}
		~trie() {
		
		}
		
		trienode* insert(string word, trienode* root) {
			trienode* node = root;
			edge* current =  new edge();
			int i = 0;
			int j = 0;
			if(word.length() == 0) {
				return root;
			}
			//Until the end of the word is reached
			while(word[j] != NULL) {
				//If an edge already exists for the current letter.
				if(find(node->edges.begin(), node->edges.end(), word[j]) != node->edges.end()) {
					i = find(node->edges.begin(), node->edges.end(), word[j]) - node->edges.begin();
					//Move current to node pointed to by edge.
					current = edges[i];
					//If edge already has a child node, move the node pointer to the child node.
					if(edges[i]->c != NULL) {
						node = edges[i]->c;
					}
					//If edge doesn't have child node, create child node for substring
					else {
						node = new trienode(word.substr(0,(j-1)));
						edges[i]->c = node;
					}
					insert(word, node);			
				}
				//If edge doesn't exist for the current letter. 
				else {
					//Create an edge for the letter.
					node->edges.pushback(word[j]);
					i = find(node->edges.begin(), node->edges.end(), word[j]) - node->edges.begin();
					edges[i]->p = node;
					node = new trienode(word.substr(0, (j-1)));
					edges[i]->c = node;
					current = edges[i];
					node = edges[i]->c;
					insert(word, node);
				}
				j++;
			}
			return node;
		}
	
		bool isQueryValid(trienode *node) {
			if(node.getQV() != 0) {
				return TRUE
			}
			else {
				return FALSE
			}
		} 
	
};

int main {
	trie *dictionary_trie = new trie();
	//For every line in file
	dictionary_trie->insert("line", root);
}