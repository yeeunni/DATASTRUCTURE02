#ifndef INCLUDES_L
#define INCLUDES_L
#include "LoadCsv.h"
#endif
#include<algorithm>



class stackNode {
public:
	int num;            //store unique number
	string file;        //store file name
	Database_BST_Node* address;  
};

class searchQueue {
private:
	int idx;
	stackNode* queue[300];   //queue array
public:
	searchQueue() {   
		idx = -1;
	}
	int q_isempty() {
		if (idx == -1) {  
			return 1;
		}
		else
			return 0;
	}
	void Enque(stackNode* node) {   //enqueue function
		
		if (idx < 299) {          //total number of array queue is 300
			idx += 1;             
			queue[idx] = node;    //first in first out 
			
		}
	}
	int isinQ(int snum) {     //can check snum is already in queue

		for (int i = 0; i < idx + 1; i++) {
			if (queue[i]->num == snum) {
				return 1;
			}
		}
		return 0;
	}

	

	void moore(string word) {                   //moore alogrithm for detecting string word parameter 
		ofstream log("log.txt", ios::app);
		int memo_ascii[100];                  //array that store each word index's ascii code
		int word_size = word.size();          
		int shift;                          //how many shift when in moore algorithm
		int check = 0;                      //can know if bad char is in my word

		for (int j = 0; j < word_size; j++) {
			//store each word index's ascii code
			memo_ascii[j] = word[j];
		}
		for (int i = 0; i < idx + 1; i++) {        //skim all queue node's file
			int file_size = queue[i]->file.size(); 
			
			int file_start = 0;                 //index of start comparing in file
			while (file_start <= (file_size - word_size)) { 
				check = 0;   //initialization check before comparing
				int k = word_size - 1; //because index starts 0 to word_size-1
				while (k >= 0 && word[k] == (queue[i]->file)[file_start + k]) { //compare from rear of word so compare and index k--
					k--;
				}

				if (k < 0) {  //all parts of word and file is same
					log << "\"" << queue[i]->file << "\"" << " /" << queue[i]->num;
					log << endl;
					queue[i] == NULL; 
					break;

				}
				else{
					for (int j = 0; j < word_size; j++) {   
						if (memo_ascii[j] == (int)queue[i]->file[file_start+k]) {  //if bad char is in word
							shift = abs(k - j);            //if not abs-> can occur '-'-> can occur infinite loop  
							file_start += shift;                //update file_start
							check = 1;                    
							break;
						}	
					}
					if (check == 0) { //bad char is not in word
						file_start = file_start + word_size;  //shift total size of word
					}
					
				}
				
			}

		}
	}
};
class SearchStack {
private:
	int top = -1;
	stackNode* stack[300]; //stack array
public:

	int Stack_isempty() {
		if (top == -1) {
			return 1;
		}
		else
			return 0;
	}

	void push(Database_BST_Node* node) {
		if (top < 299 && node != NULL) {
			top += 1;
			stackNode* add = new stackNode; //allocate heap memory stackNode
			add->file = node->fileName;
			add->num = node->unique_num;
			add->address = node;
			
			stack[top] = add;  //assign stack[top] = add
		
		}
	}
	stackNode* pop() {              //last in first out
		ofstream log("log.txt", ios::app);
		int delIndex;
		if (Stack_isempty()) {
			log << "empty" << endl;
			return NULL;
		}
		delIndex = top;
	
		top -= 1;
		
		return stack[delIndex];
	}

	void postorder(Database_BST* t, searchQueue* (queue)) { //postorder by using stack and store it queue
		Database_BST_Node* cur = t->getRoot(); //read tree t's Root address
		Database_BST_Node* p_cur = cur;    //cur's parent cur
		Database_BST_Node* L_node = NULL;   //the most recently pop node 
		while (cur->left != NULL) {
			if (t->getRoot() != NULL) {   //tree is not empty
				push(cur);       // root of each subtrees push in stack
				p_cur = cur;         //assign parent of cur
				cur = cur->left;     //update cur
			}
		}
		push(cur);           //cur whose cur->left is NULL also push
		
		while (!Stack_isempty()) {      //while stack is not empty

			if (cur->left == NULL && cur->right == NULL) {     //leaf node

				queue->Enque(pop());           //pop from stack and enqueue it
				
				L_node = cur;                     //  assign L_node
				if (top == -1) {                  //if stack is empty
					break;
				}
				cur = stack[top]->address;         //stack is not empty 
				


			}
			else if (cur->left != NULL && cur->right == NULL) {
				if ((queue->isinQ(cur->left->unique_num))) {
					queue->Enque(pop());

					L_node = cur;
					if (top == -1) {
						break;
					}
					cur = stack[top]->address;     //update cur because when in pop() function, top -=1
					
				}
			}
			else if (cur->left == NULL && cur->right != NULL) {    
				if (!(queue->isinQ(cur->right->unique_num))) {    //if not visit(push and pop and enqueue) cur->right

					cur = cur->right;             
					push(cur);               //push cur
				}
				else if (cur->right == L_node) {          //if already visit cur->right
					queue->Enque(pop());            // pop cur
					L_node = cur;                        //update cur
					if (top == -1) {
						break;
					}
					cur = stack[top]->address;
				}
			}
			else if (cur->left != NULL && cur->right != NULL) {
				if (cur->left == L_node && cur->right != NULL) {      //if already visit cur->left and have cur->right
					cur = cur->right;             //move cur = cur->right
					push(cur);               //push cur
				}
				else if (cur->right == L_node) {        //if already visit cur->right(== already visit cur->left)

					queue->Enque(pop());  //pop and enqueue cur
					L_node = cur;  //assign L_node
					if (top == -1) {
						break;
					}
					cur = stack[top]->address;
				}
			}

		}
	}
};

