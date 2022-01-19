// Trie Tree Header File

#ifndef Trie_H
#define Trie_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <cstring>
#include <fstream>

struct Node {	// node of trie tree;
	char character;
	bool isEnd;
	Node* child[26];
	std::string meaning;
	int siz;
	std::string* synonyms;
};

class Trie {	// Trie Tree
private:
	Node* root;

	void insertWord(Node*, std::string, std::string, std::string*, int);
	void printWord(char[], int);
	void printAll(Node*, char[], int);
public:
	Trie();
	void insert(std::string, std::string, std::string*, int);
	void print();
	void search(std::string);
	~Trie();
};

#endif	// !Trie_H