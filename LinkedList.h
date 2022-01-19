// 4D LINKED LIST HEADER FILE
#ifndef LinkedList_H
#define LinkedList_H

#include "Trie.h"

struct LinkedNode {
	char character;
	LinkedNode* top;
	LinkedNode* bottom;
	LinkedNode* left;
	LinkedNode* right;
};

class LinkedList {
private:
	LinkedNode* head;
	LinkedNode* cursor_node;
	LinkedNode* tail;
public:
	LinkedList();
	void insert(char, std::string&);
	void print();
	bool canGoRight();
	bool canGoLeft();
	bool canGoUp();
	bool canGoDown();
	void currentMoveRight();
	void currentMoveLeft();
	void currentMoveUp();
	void currentMoveDown();
	void Delete();
	void DeleteAll();
	~LinkedList();
};

#endif // !4D_Linked_List_H