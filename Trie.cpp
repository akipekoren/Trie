#include "Trie.h"
#include <iostream>
#include <sstream>



Trie::Trie(){
	this->root = new TrieNode();
	this->size = 0;
}


Trie::Trie(const Trie & copy){


	root = copy.createClone();
	size = copy.size;
	cout << "Copy constructor called" << endl;
}


Trie::Trie(Trie && move):root(nullptr), size(0){

	cout << "Move constructor called" << endl;
	
	swap(move);

	
}

void Trie::swap(Trie&tr)
{
	std::swap(root,tr.root);

	// swap function for move constructor
}


Trie::~Trie(){
	deleteTrie(); // Destroy the tree
	cout << "Destructor called" << endl;
}



TrieNode * Trie::createClone() const {


	// create clone function
	TrieNode *CloneHead = new TrieNode();
	TrieNode *Cloneptr = CloneHead;
	TrieNode *ptr_head = root;

	for (int i =0; i<26; i++)
	{
		if(ptr_head->children[i])
		{
			Cloneptr->children[i] = new TrieNode(); // create empty children for copy
			cloneHelper(ptr_head->children[i],Cloneptr->children[i]);
	
		}
	}



	return CloneHead;
}


void Trie::cloneHelper(TrieNode* source, TrieNode*& destination) const {

		TrieNode *ptrClone = destination;
		TrieNode * ptr = source;
		TrieNode *temp = ptr; // Pointers for ptr and ptr clone
		TrieNode *temptemp = ptr;


	for (int i = 0; i<26 ; i++)
		{

			if (ptr->children[i] && !ptrClone->children[i]) // search the all array and find the letter
			{
				if(ptr->children[i]->isWord == false)
				{
				ptrClone->children[i] = new TrieNode(); // first nodes are created
				ptrClone->children[i]->isWord = false;
	
				cloneHelper(ptr->children[i],ptrClone->children[i]);  // go to function
				}
				else
				{
				ptrClone->children[i] = new TrieNode(); // creating the empty children
				ptrClone->children[i]->isWord = true;
		
				cloneHelper(ptr->children[i],ptrClone->children[i]);
		
				}
				
			}

			else if (ptr->children[i] && ptrClone->children[i]) // if not
			{
				cloneHelper(ptr->children[i],ptrClone->children[i]);
			}

			
			
		}
			
		
		ptrClone = destination; // make ptrClone equal to destination
		
}


/*******************************************************************/
/*                      OPERATORS ARE BELOW      
/*******************************************************************/

	ostream& operator<<(ostream& os, const Trie & tr)
	{
		
		if(!tr.isEmpty())
		{
		TrieNode *temp = tr.root;
		string word = " ";
		tr.printHelper(os,temp,word); // recursion
		os << word;
		return os;
		}
		else
			os<<"Trie is empty";
			return os;
		
	}

	bool operator ==(Trie&rhs, Trie&lhs)
	{

		TrieNode * ptr1= rhs.root; // temp pointers
		TrieNode * ptr2 = lhs.root;
	
		
		if (rhs.length() == lhs.length()) // firstly check the tree's lengths
		{
			

			for (int i = 0; i< 26 ; i++)
			{



				if (ptr1->children[i] && ptr2->children[i])
				{
					
					continue;
		
				}

				else if (!ptr1->children[i] && ptr2->children[i] || ptr1->children[i] && !ptr2->children[i])
				{
					
					return false;
				}
			}

			return true;
			
		}

		else // lengths are not equal return false
		{
			
			return false;
		}


	}

	bool operator !=(Trie&rhs,Trie&lhs)
	{

		// just opposite of == operator
		bool checker = true;

		if (rhs == lhs) // check if they are equal
		{
			return false;
		}

		else
		{
			return true; // if they are not equal return true
		}
	}

	Trie& Trie::operator = (Trie&& rhs)
	{


		// Move assignment operator
		if (this != &rhs)
		{
			
			Trie rhs_2 = rhs;

			swap(rhs);
			rhs.deleteTrie(); // Deleting the right tree
			rhs.size = 0;
			rhs.root = nullptr;


	
		
		}
		return *this;
	}

	Trie& Trie::operator = (Trie& rhs)
	{
		if(this != &rhs)
		{
			delete root;
			root = new TrieNode();

			TrieNode *temp1 = root;
			TrieNode * temp2 = rhs.root;
			
		for (int i= 0; i< 26 ; i++)
		{
			if (temp2->children[i])
			{
				temp1->children[i] = new TrieNode();
				cloneHelper(temp2->children[i],temp1->children[i]); // Calling the cloneHelper
			}
		}
		
		}

	
		
		return *this;
	}

	Trie operator + (Trie& tr, string word)
	{
		Trie cc(tr); // Create a copy
		if (!cc.searchWord(word))
			cc.insertWord(word);

			return cc;
	}

	Trie operator + (string word, Trie& tr)
	{
		Trie cc(tr); // Create a copy
		if (!cc.searchWord(word))
			cc.insertWord(word);

			return cc;
	}

	Trie& Trie:: operator+ (Trie&rhs)
	{
		// Addition of two tree

			size = rhs.size + size; 


		
		TrieNode *temp1 = rhs.root;
		TrieNode *temp2 = root; // temp pointers
		


		for (int i= 0; i<26 ; i++)

		{
			if(temp1->children[i] && !temp2->children[i])
				
			{
				temp2->children[i] = new TrieNode();
				cloneHelper(temp1->children[i],temp2->children[i]);	
			}

			else if (temp1->children[i] && temp2->children[i]) // If hey both have the same children
			{
				cloneHelper(temp1->children[i],temp2->children[i]);	
			}

		}



		
		return *this;

	} 

	Trie& Trie ::operator +=(Trie & rhs)
	{
			TrieNode *temp1 = rhs.root;
			TrieNode *temp2 = root;


			size= rhs.size + size; // Make their length equal

				for (int i= 0; i<26 ; i++)

		{
			if(temp1->children[i] && !temp2->children[i])
				
			{
				temp2->children[i] = new TrieNode();
				cloneHelper(temp1->children[i],temp2->children[i]);	
			}

			else if (temp1->children[i] && temp2->children[i]) // if they both have the same children
			{
				cloneHelper(temp1->children[i],temp2->children[i]);	 // calling the clonehelper function
			}

		}


				return *this;

	}
	
	Trie& Trie ::operator +=(string word)
	{

		Trie cc = *this; // Cloning the tree
		if (!cc.searchWord(word))
			cc.insertWord(word); // If word is not in tree then add to tree

		*this = cc;
			return *this;

	}


bool Trie::searchWord(string word) {
	lower(word);
	TrieNode * ptr = root;
	int len = word.length();
	for (int i = 0; i < len; i++) {
		int targetIndex = word.at(i) - 'a';
		if (!ptr->children[targetIndex]) {
			return false;
		}
		ptr = ptr->children[targetIndex];
	}
	if (ptr->isWord) {
		return true;
	}
	return false;
}

void Trie::lower(string & word) {
	string res;
	for (char c : word) {
		if (c >= 'A' && c < 'a') {
			res += (c - 'A' + 'a');
		}
		else {
			res += c;
		}
	}
	word = res;
}


void Trie::insertWord(string word) {
	lower(word);
	if (!searchWord(word)) {
		TrieNode * ptr = root;
		int len = word.length();
		for (int i = 0; i < len; i++) {
			int targetIndex = word.at(i) - 'a';
			if (!ptr->children[targetIndex]) {
				ptr->children[targetIndex] = new TrieNode();
			}
			//			ptr->isLeaf = false;
			ptr = ptr->children[targetIndex];
		}
		ptr->isWord = true;
		size += 1;
	}
}

bool Trie::hasChildren(TrieNode * node, int i = 0) const {
	if (node) {
		for (i; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				return true;
			}
		}
	}
	return false;
}

void Trie::deleteWord(string word) {
	lower(word);
	if (searchWord(word)) {
		if (deleteWordHelper(root, word)) {
			size--;
		}
	}
}

bool Trie::isEmpty() const {
	return !(this->hasChildren(root));
}

bool Trie::deleteWordHelper(TrieNode *& node, string word) {
	if (word.length()) {
		if (node != nullptr &&
			node->children[word[0] - 'a'] != nullptr &&
			deleteWordHelper(node->children[word[0] - 'a'], word.substr(1)) &&
			!node->isWord
			) {
			if (!hasChildren(node)) {
				delete node;
				node = nullptr;
				return true;
			}
			else {
				node->isWord = false;
				return true;
			}

		}
	}
	if (word.length() == 0 && node->isWord) {
		if (!hasChildren(node)) {
			delete node;
			node = nullptr;
			return true;
		}
		else {
			node->isWord = false;
			return false;
		}
	}
}

void Trie::printHelper(ostream & os, TrieNode * node, string & word) const {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (node->children[i]) {
			word += char(i + 'a');
			if (node->children[i]->isWord) {
				os << word << endl;
				printHelper(os, node->children[i], word);
			}
			else {
				printHelper(os, node->children[i], word);
			}
		}
		else if (i == 26) {
			word = word.substr(0, word.length() - 1);
		}
	}
	word = word.substr(0, word.length() - 1);
}

void Trie::deleteTrie() {
	if (root) {
		deleteTrieHelper(root);
		root = nullptr;
		size = 0;
	}
}

void Trie::deleteTrieHelper(TrieNode * node) {
	if (hasChildren(node)) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (node->children[i]) {
				deleteTrieHelper(node->children[i]);
			}
		}
	}
	delete node;
}

int Trie::length() {
	return size;
}