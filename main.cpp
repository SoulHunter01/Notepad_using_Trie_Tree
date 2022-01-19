// main program

#include "LinkedList.h"	// contains all the header files

using namespace std;

void readDictionaryFile(Trie& T) {	// function to read dictionary file and create trie tree;
	ifstream File;

	File.open("dictionary.txt");
	//---------------------------
	/*Variables for trie tree*/

	int size = 100;	// how many synonyms

	string word;	// word to be inserted in trie tree

	string meaning;	// meaning of the word

	string* synonyms = NULL;	// synonyms pointer

	string temp;	// taking a line from file

	int i = 0, check = 1;

	//---------------------------

	while (!File.eof()) {			// This loop runs untill all the dictionary file is read!
		getline(File, temp, '\n');

		if (temp[0] == '-') {
			if (synonyms != NULL) {
				T.insert(word, meaning, synonyms, i);
				delete[] synonyms;
				synonyms = NULL;
				i = 0;
				check = 1;
			}

			if (temp[1] != '-') {
				word = temp;
			} else {
				meaning = temp;
			}
		} else {
			if (check == 1) {
				synonyms = new string[size];
				check++;
			}

			synonyms[i] = temp;
			i++;
		}
	}

	T.insert(word, meaning, synonyms, i);	// inserting in trie tree

	delete[] synonyms;

	File.close();
}

void gotoxy(int x, int y) {		// function to control cursor.
	
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);	
}

void control2ndSreen(int x, int y) {		// function to control 25% part of screen.
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main() {
	system("cls");		// clearing screen if already not cleared
	
	/* Menu starts here*/

	int choice;
	gotoxy(17, 15);
	cout << "-----------------------------------------------\n";
	gotoxy(17, 16);
	cout << "1.Do you want to open a new file?\n";
	gotoxy(17, 17);
	cout << "2.Do you want to open an already existing file?\n";
	gotoxy(17, 18);
	cout << "Enter 1 or 2/n";
	gotoxy(17, 19);
	cout << "---------------------------------------------\n";
	cin >> choice;

	/*Menu ends here*/

	switch (choice) {
		case 1: {
			system("cls");
			ofstream newFile;
			newFile.open("Output.txt");

			Trie T;

			readDictionaryFile(T);

			string str = "";

			LinkedList Lk;

			HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

			DWORD Events = 0;     // Event count
			DWORD EventsRead = 0; // Events read from console

			bool Running = true;

			int x = 0, y = 0;
			gotoxy(x, y);

			while (Running) {	// loop to control cursor and input on runtime

				// gets the systems current "event" count
				GetNumberOfConsoleInputEvents(rhnd, &Events);

				if (Events != 0) { // if something happened we will handle the events we want

					// create event buffer the size of how many Events
					INPUT_RECORD eventBuffer[200];

					// fills the event buffer with the events and saves count in EventsRead
					ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

					// loop through the event buffer using the saved count
					for (DWORD i = 0; i < EventsRead; ++i) {

						// check if event[i] is a key event && if so is a press not a release
						if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {

							// check if the key press was an arrow key
							switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

								case VK_UP: {//up
									if (y < 1 || !Lk.canGoUp()) {
										break;
									}
									y--;
									gotoxy(x, y);
									Lk.currentMoveUp();
									break;
								}
								case VK_DOWN: {//down
									if (y > 19 || !Lk.canGoDown()) {
										break;
									}
									y++;
									gotoxy(x, y);
									Lk.currentMoveDown();
									break;
								}
								case VK_RIGHT: {//right
									if (x > 118 || !Lk.canGoRight()) {
										break;
									}
									x++;
									gotoxy(x, y);
									Lk.currentMoveRight();
									break;
								}
								case VK_LEFT: {//left
									if (x < 1 || !Lk.canGoLeft()) {
										break;
									}
									x--;
									gotoxy(x, y);
									Lk.currentMoveLeft();
									break;
								}
								case VK_RETURN: {// Enter
									Lk.insert('\n', str);
									system("cls");
									Lk.print();
									x = 0;
									y++;
									gotoxy(x, y);
									break;
								}
								case VK_BACK: {// Backspace
									Lk.Delete();
									system("cls");
									Lk.print();
									x--;
									gotoxy(x, y);
									Lk.currentMoveLeft();
									break;
								}
								case VK_ESCAPE: {// escape key
									Lk.DeleteAll();
									system("cls");
									gotoxy(17, 15);
									char choice_end;
									cout << "-----------------------------------------------\n";
									gotoxy(17, 16);
									cout << "Do you want to exit the app?\n";
									gotoxy(17, 17);
									cout << "Enter either Y/N";
									cin >> choice_end;
									gotoxy(17, 18);
									cout << "------------------------------------------------\n";
									switch (choice_end) {
									case 'Y':
									case 'y': {
										system("pause");
										return 0;
									}
									case 'N':
									case 'n': {
										system("cls");
										gotoxy(17, 15);
										cout << "-----------------------------------------------\n";
										gotoxy(17, 16);
										cout << "You should exit the app now! :) \n";
										gotoxy(17, 17);
										cout << "Good Bye\n";
										gotoxy(17, 18);
										cout << "------------------------------------------------\n";
									}
											system("pause");
											return 0;
									}
							}
							default: 

								newFile << eventBuffer->Event.KeyEvent.uChar.AsciiChar;
								Lk.insert(eventBuffer->Event.KeyEvent.uChar.AsciiChar, str);
								system("cls");
								Lk.print();
								x++;
								gotoxy(x, y);

								control2ndSreen(0, 21);
								for (int i = 0; i < 120; i++) {
									cout << "-";
								}

								cout << endl;
								T.search(str);

								break;
							}
						}

					} // end EventsRead loop

				}

			} // end program loop
			newFile.close();
			break;
		}
		case 2: {
			system("cls");
			string Fname;
			fstream existFile;
			gotoxy(17, 15);
			cout << "-----------------------------------------------\n";
			gotoxy(17, 16);
			cout << "Enter the name of the File:\n";
			cin >> Fname;
			gotoxy(17, 17);
			cout << "---------------------------------------------\n";
			existFile.open(Fname, ios_base::app);
			if (existFile.is_open()) {
				Trie T;

				readDictionaryFile(T);

				string str = "";

				LinkedList Lk;

				HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

				DWORD Events = 0;     // Event count
				DWORD EventsRead = 0; // Events read from console

				bool Running = true;

				int x = 0, y = 0;
				gotoxy(x, y);

				while (Running) {

					// gets the systems current "event" count
					GetNumberOfConsoleInputEvents(rhnd, &Events);

					if (Events != 0) { // if something happened we will handle the events we want

						// create event buffer the size of how many Events
						INPUT_RECORD eventBuffer[200];

						// fills the event buffer with the events and saves count in EventsRead
						ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

						// loop through the event buffer using the saved count
						for (DWORD i = 0; i < EventsRead; ++i) {

							// check if event[i] is a key event && if so is a press not a release
							if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {


								// check if the key press was an arrow key
								switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

									case VK_UP: {//up
										if (y < 1 || !Lk.canGoUp()) {
											break;
										}
										y--;
										gotoxy(x, y);
										Lk.currentMoveUp();
										break;
									}
									case VK_DOWN: {//down
										if (y > 19 || !Lk.canGoDown()) {
											break;
										}
										y++;
										gotoxy(x, y);
										Lk.currentMoveDown();
										break;
									}
									case VK_RIGHT: {//right
										if (x > 118 || !Lk.canGoRight()) {
											break;
										}
										x++;
										gotoxy(x, y);
										Lk.currentMoveRight();
										break;
									}
									case VK_LEFT: {//left
										if (x < 1 || !Lk.canGoLeft()) {
											break;
										}
										x--;
										gotoxy(x, y);
										Lk.currentMoveLeft();
										break;
									}
									case VK_RETURN: {// Enter
										Lk.insert('\n', str);
										system("cls");
										Lk.print();

										x = 0;
										y++;
										gotoxy(x, y);
										break;
									}
									case VK_BACK: {// Backspace
										Lk.Delete();
										system("cls");
										Lk.print();
										x--;
										gotoxy(x, y);
										Lk.currentMoveLeft();
										break;
									}
									case VK_ESCAPE: {// Escape key
										Lk.DeleteAll();
										system("cls");
										existFile.close();
										gotoxy(17, 15);
										char choice_end;
										cout << "-----------------------------------------------\n";
										gotoxy(17, 16);
										cout << "Do you want to exit the app?\n";
										gotoxy(17, 17);
										cout << "Enter either Y/N";
										cin >> choice_end;
										gotoxy(17, 18);
										cout << "------------------------------------------------\n";
										switch (choice_end) {
										case 'Y':
										case 'y': {
											system("pause");
											return 0;
										}
										case 'N':
										case 'n': {
											gotoxy(17, 15);
											cout << "-----------------------------------------------\n";
											gotoxy(17, 16);
											cout << "You should exit the app now! :) \n";
											gotoxy(17, 17);
											cout << "Good Bye\n";
											gotoxy(17, 18);
											cout << "------------------------------------------------\n";
										}
												system("pause");
												return 0;
										}
								}
								default:

									existFile << eventBuffer->Event.KeyEvent.uChar.AsciiChar;
									Lk.insert(eventBuffer->Event.KeyEvent.uChar.AsciiChar, str);
									system("cls");
									Lk.print();
									x++;
									gotoxy(x, y);

									control2ndSreen(0, 21);
									for (int i = 0; i < 120; i++) {
										cout << "-";
									}

									cout << endl;
									T.search(str);

									break;
								}
							}

						} // end EventsRead loop

					}

				} // end program loop
			} else {
				system("cls");
				gotoxy(17, 15);
				cout << Fname << "File does not exist.\n";
				system("pause");
				return 0;
			}
			existFile.close();
			break;
		}
		default: {
			system("cls");
			gotoxy(17, 15);
			cout << "Invalid Choice\n";
			return 0;
		}
	}

	system("pause");

	return 0;
}