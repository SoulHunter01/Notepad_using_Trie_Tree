// 4D LINKED LIST CPP FILE
#include "LinkedList.h"

using namespace std;

void connect_top_and_bottom(LinkedNode* topNode, LinkedNode* bottomNode) {  // connecting top and bottom of current node
    if (topNode == NULL || bottomNode == NULL) {
        return;
    }
    bottomNode->top = topNode;
    topNode->bottom = bottomNode;
}

void start_and_end_of_line(LinkedNode* inserted_node, LinkedNode*& start_node, LinkedNode*& end_node) { // checking start and end of a line
    LinkedNode* i = inserted_node;
    LinkedNode* i_backup = inserted_node;
    while (i != NULL && i->character != '\n') {
        i_backup = i;
        i = i->left;
    }

    start_node = i_backup;

    i = inserted_node;
    i_backup = inserted_node;
    while (i != NULL) {
        i_backup = i;
        if (i->character == '\n') {
            break;
        }
        i = i->right;
    }

    end_node = i_backup;
}

bool is_first_line(LinkedNode* reference_node) {    // checking if it is the first line
    if (reference_node == NULL) {
        return false;
    }
    while (true) {
        if (reference_node->left == NULL || reference_node->left->character == '\n') {
            return reference_node->top == NULL;
        }
        reference_node = reference_node->left;
    }
}

bool is_last_line(LinkedNode* reference_node) { // checking if it is the last line
    if (reference_node == NULL) {
        return false;
    }
    while (true) {
        if (reference_node->left == NULL || reference_node->left->character == '\n') {
            return reference_node->bottom == NULL;
        }
        reference_node = reference_node->left;
    }
}

void set_pointers_for_two_lines(LinkedNode* current_line_start, LinkedNode* current_line_end, LinkedNode* prev_line_start, LinkedNode* prev_line_end) { // setting pointers for 2 lines
    LinkedNode* curr1 = current_line_start;
    LinkedNode* curr2 = prev_line_start;

    while (true) {
        connect_top_and_bottom(curr2, curr1);
        if (curr1 == current_line_end || curr2 == prev_line_end) {
            break;
        }
        curr1 = curr1->right;
        curr2 = curr2->right;
    }
}

void align_lines(LinkedNode* inserted_node) {   // alligning lines to match correct top and bottom nodes
    LinkedNode* current_line_start = NULL;
    LinkedNode* current_line_end = NULL;
    start_and_end_of_line(inserted_node, current_line_start, current_line_end);

    if (!is_first_line(inserted_node) && !is_last_line(inserted_node)) {
        LinkedNode* prev_line_start = NULL;
        LinkedNode* prev_line_end = NULL;
        start_and_end_of_line(current_line_start->top, prev_line_start, prev_line_end);

        set_pointers_for_two_lines(current_line_start, current_line_end, prev_line_start, prev_line_end);

        LinkedNode* next_line_start = NULL;
        LinkedNode* next_line_end = NULL;
        start_and_end_of_line(current_line_start->bottom, prev_line_start, prev_line_end);

        set_pointers_for_two_lines(current_line_start, current_line_end, prev_line_start, prev_line_end);
    }
    else if (!is_last_line(inserted_node)) {
        LinkedNode* next_line_start = NULL;
        LinkedNode* next_line_end = NULL;
        start_and_end_of_line(current_line_start->bottom, next_line_start, next_line_end);

        set_pointers_for_two_lines(current_line_start, current_line_end, next_line_start, next_line_end);
    }
    else if (!is_first_line(inserted_node)) {
        LinkedNode* prev_line_start = NULL;
        LinkedNode* prev_line_end = NULL;
        start_and_end_of_line(current_line_start->top, prev_line_start, prev_line_end);

        set_pointers_for_two_lines(current_line_start, current_line_end, prev_line_start, prev_line_end);
    }
}

void Initialize_new_line(LinkedNode* node) {    // A new line starts from this function
    LinkedNode* current_line_start = NULL;
    LinkedNode* current_line_end = NULL;
    start_and_end_of_line(node, current_line_start, current_line_end);

    if (!is_first_line(node)) {
        LinkedNode* prev_line_start = NULL;
        LinkedNode* prev_line_end = NULL;
        start_and_end_of_line(current_line_start->top, prev_line_start, prev_line_end);

        current_line_start->top = prev_line_start;
        prev_line_start->bottom = current_line_start;
    }
    if (!is_last_line(node)) {
        LinkedNode* next_line_start = NULL;
        LinkedNode* next_line_end = NULL;
        start_and_end_of_line(current_line_start->bottom, next_line_start, next_line_end);

        current_line_start->bottom = next_line_start;

        next_line_start->top = current_line_start;
    }
}

LinkedNode* start_of_prev_line(LinkedNode* curr) {  // getting the first node of previous line
    LinkedNode* i = curr;
    LinkedNode* i_backup = curr;

    while (i->character != '\n') {
        i_backup = i;
        i = i->left;
    }
    i = i->left;
    while (i != NULL && i->character != '\n') {
        i_backup = i;
        i = i->left;
    }

    return i_backup;
}

LinkedList::LinkedList() {  // Linked List Constructor
    head = NULL;
    cursor_node = NULL;
    tail = NULL;
}

void LinkedList::insert(char character, string& str) {  // inserting node in linked list
    LinkedNode* new_node = new LinkedNode();
    new_node->character = character;
    new_node->left = cursor_node;
    new_node->top = NULL;
    new_node->bottom = NULL;

    if (cursor_node == NULL) {
        if (head == NULL) {
            head = new_node;
            new_node->right = NULL;
        }
        else {
            new_node->right = head;
            head->left = new_node;
        }
    }
    else {
        if (cursor_node->right != NULL) {
            cursor_node->right->left = new_node;
        }
        new_node->right = cursor_node->right;
        cursor_node->right = new_node;
    }

    cursor_node = new_node;

    if ((new_node->character == ' ') || (new_node->character == ';') || (new_node->character == '.') || (new_node->character == ',') ) {
        LinkedNode* temp2 = new_node->left;
        LinkedNode* temp3 = temp2;
        str = "";
        while (temp2 != NULL && ((temp2->character != ' ') && (temp2->character != ';') && (temp2->character != ',') && (temp2->character != '.') && (temp2->character != '\n'))) {
            str += temp2->character;
            //temp3 = temp2;
            temp2 = temp2->left;
        }

        int len = str.length();
        int n = len - 1;
        for (int i = 0; i < (len / 2); i++) {
            swap(str[i], str[n]);
            n = n - 1;
        }
    }

   

    if (cursor_node->character != '\n' || cursor_node->left->character == '\n') {
        if (cursor_node->left == NULL || cursor_node->left->character == '\n') {
            if (head != new_node) {
                new_node->top = start_of_prev_line(new_node);
            }
            Initialize_new_line(cursor_node);
        }
        else {
            align_lines(cursor_node);
        }
    }
}

void LinkedList::print() {  // printing complete Linked List
    LinkedNode* temp;
    temp = head;

    while (temp != NULL) {
        cout << temp->character;
        temp = temp->right;
    }
}

bool LinkedList::canGoRight() { // checking if cursor can go right
    return (cursor_node != NULL && cursor_node->right != NULL);
}

bool LinkedList::canGoLeft() { // checking if cursor can go left
    return (cursor_node != NULL && cursor_node->left != NULL);
}

bool LinkedList::canGoUp() { // checking if cursor can go up
    return (cursor_node != NULL && cursor_node->top != NULL);
}

bool LinkedList::canGoDown() { // checking if cursor can go down
    return (cursor_node != NULL && cursor_node->bottom != NULL);
}

void LinkedList::currentMoveUp() {  // moving current to current->top
    cursor_node = cursor_node->top;
}

void LinkedList::currentMoveDown() { // moving current to current->bottom
    cursor_node = cursor_node->bottom;
}

void LinkedList::currentMoveLeft() { // moving current to current->left
    cursor_node = cursor_node->left;
}

void LinkedList::currentMoveRight() { // moving current to current->right
    cursor_node = cursor_node->right;
}

void LinkedList::Delete() { // Deleting using backspace
    if (cursor_node != NULL) {
        if (cursor_node->left != NULL) {
            cursor_node->left->right = cursor_node->right;
        }
        if (cursor_node->right != NULL) {
            cursor_node->right->left = cursor_node->left;
        }

        LinkedNode* temp = cursor_node;

        cursor_node = cursor_node->left;
        delete temp;
        align_lines(cursor_node);
    }
}

void LinkedList::DeleteAll() {  // Deleting all the linked list
    LinkedNode* temp = head;
    LinkedNode* temp2;
    while (temp != NULL) {
        temp2 = temp;
        temp = temp->left;
        delete temp2;
    }
}

LinkedList::~LinkedList() { // Destructor of Linked List
    cout << "Already deleted\n";
}