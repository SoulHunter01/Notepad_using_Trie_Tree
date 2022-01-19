// Trie Tree CPP FILE

#include "Trie.h"

using namespace std;

Trie::Trie() {	// Trie Tree Constructor
	root = new Node();
	root->character = '*';
	root->isEnd = false;
	for (int i = 0; i < 26; i++) {
		root->child[i] = NULL;
	}
	root->meaning = "";
	root->synonyms = NULL;
}

void Trie::insertWord(Node* r, string word, string meaning, string* synonyms, int siz) {	// inserting in trie tree
	int pos;

	for (int i = 1; i < word.size(); i++) {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			pos = (int)word[i] - (int)'A';
		}
		else if (word[i] >= 'a' && word[i] <= 'z') {
			pos = (int)word[i] - (int)'a';
		}

		if (r->child[pos] == NULL) {
			r->child[pos] = new Node();
			r->child[pos]->character = word[i];
			r->child[pos]->isEnd = false;
		}
		r = r->child[pos];
	}
	r->isEnd = true;
	r->meaning = meaning;
	r->synonyms = new string[siz];
	r->siz = siz;
	for (int i = 0; i < siz; i++) {
		r->synonyms[i] = synonyms[i];
	}
}

void Trie::insert(string word, string meaning, string* synonyms, int siz) {	// main insert functions
	insertWord(root, word, meaning, synonyms, siz);
}

void Trie::printWord(char word[], int pos) {	// printing single word in trie tree
	for (int i = 0; i < pos; i++) {
		cout << word[i];
	}
}

void Trie::printAll(Node* r, char word[], int pos = 0) {	// printing all words in trie tree
	if (r == NULL) {
		return;
	}
	if (r->isEnd == true) {
		printWord(word, pos);
		cout << endl;
		cout << r->meaning << endl;
		for (int i = 0; i < r->siz; i++) {
			cout << r->synonyms[i] << endl;
		}
		cout << endl;
	}
	for (int i = 0; i < 26; i++) {
		if (r->child[i] != NULL) {
			word[pos] = r->child[i]->character;
			printAll(r->child[i], word, pos + 1);
		}
	}
}

void Trie::print() {	// main print function
	char word[1000];

	printAll(root, word);
}

void Trie::search(string word) {	// searching a word in trie tree
	Node* current;
	current = root;

	for (int i = 0; i < word.size(); i++) {
		int pos = (int)word[i] - 'a';

		if (current->child[pos] == NULL) {
			cout << "-" << word << " -- word does not exist\n";
			return;
		}
		current = current->child[pos];
	}

	if (current->isEnd == true) {
		cout << "-" << word << endl << current->meaning << endl;

		for (int j = 0; j < current->siz; j++) {
			cout << current->synonyms[j] << endl;
		}
	}
}

Trie::~Trie() {	// Trie Tree destructor
	delete root;
}