#ifndef INCLUDES
#define INCLUDES
#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<cstring>
using namespace std;
#endif
#ifndef TREE
#define TREE
#include"Tree.h"
#endif

class Loaded_LIST_Node2 { //linked list node2 : have information of unique number, file name, directory name
public:
	int unique_num;
	string dir_name;
	string file_name;
	Loaded_LIST_Node2* right;
	Loaded_LIST_Node2* prior;  
	Loaded_LIST_Node2() {
		right = NULL;
		prior = NULL;
	}
};

class Loaded_LIST_Node1 { //linked list node1 : have information of directory name only
public:
	string dir_name;
	Loaded_LIST_Node2* right;
	Loaded_LIST_Node1* down;
	Loaded_LIST_Node1() {
		right = NULL;
		down = NULL;
	}
};





class Loaded_LIST {
private:
	Loaded_LIST_Node1* head;
	Loaded_LIST_Node1* rear;
	Loaded_LIST_Node1* curr;
	Loaded_LIST_Node2* cur;
	Loaded_LIST_Node2* tail;
	Loaded_LIST_Node1* title;
	int num = 0; //total nodes of linked list
public:
	Loaded_LIST() { 
		head = NULL;
		rear = head;
		cur = NULL;
		tail = NULL;
		int error;
	}
	int L_exist() {
		if (head == NULL) { // if Loaded_List_Node1 * head is null
			return 0; // L_exist() == false
		}
		else
			return 1;
	}
	void insert_node(char* ch) { //linked list in "LOAD"
		int i = 0;
		int j = 0;
		int m = 0;
		char temp[100];
		char temp1[100];
		Loaded_LIST_Node2* add = new Loaded_LIST_Node2; //allocate heap memory of Loaded_List_Node2
		add->right = NULL;
		Loaded_LIST_Node1* add_dirName = new Loaded_LIST_Node1; //allocate heap memory of Loaded_List_Node1
		ofstream log("log.txt", ios::app); //write on log.txt
		if (head == NULL) { //if linked list is empty
			head = add_dirName;   
			head->dir_name = "img_files";
			title = head;
			rear = head;
		}

		for (i = 0; i < strlen(ch); i++) { //classify unique number and file name from csv file's line
			if (ch[i] == ',') {

				for (j = 0; j < i; j++) {
					temp[j] = ch[j];
				}
				add->unique_num = atoi(temp); //string to int

			}
		}
		
		int k = 0;
		for (i = 0; i < strlen(ch); i++) { //after ',' is file name
			if (ch[i] == ',') {
				for (k = i + 1; k < strlen(ch); k++) {
					temp1[m] = ch[k];
					m++;
				}
				temp1[m] = NULL;
			}
		}
		for (i = 0; i < strlen(temp1); i++) { //before '.RAW' is file name 
			if (temp1[i] == '.') {
				temp1[i] = NULL;
			}
		}
		string temp2(temp1); //char to string
		add->file_name = temp2; //assign file name
		add->dir_name = "img_files"; //assign first directory name
		log << add->file_name << "/" << add->unique_num << endl;
		if (num > 100) { //if total linked list nodes are over 100
			Loaded_LIST_Node2* del = head->right; 
			head->right = del->right;
			delete del; //delete node that is in linked list from first to...
			num -= 1; //total num --
		}

		if (title->right == NULL) // first linked node 
		{
			title->right = add;
			cur = title->right;
			tail = add;
			num++;  //update total nodes of linked list
		}

		else { // linking nodes by using tail node

			tail->right = add;
			add->prior = tail;
			tail = tail->right;
			num += 1;  //update total nodes of linked list
		}

	}
	void insert_node(char* ch, Loaded_LIST_Node1* title, string dirName) { //linked list in "ADD" : with parameter title's address and same with "LOAD" insert_node function -> skip comment
		int i = 0;
		int j = 0;
		int m = 0;
		char temp[100];
		char temp1[100];
		cur = title->right;
		ofstream log("log.txt", ios::app);
		Loaded_LIST_Node2* add = new Loaded_LIST_Node2;
		add->right = NULL;
		Loaded_LIST_Node1* add_dirName = new Loaded_LIST_Node1;

		if (head == NULL) {
			head = add_dirName;
			head->dir_name = "img_files";
			title = head;
		}

		for (i = 0; i < strlen(ch); i++) {
			if (ch[i] == ',') {

				for (j = 0; j < i; j++) {
					temp[j] = ch[j];
				}
				add->unique_num = atoi(temp);

			}
		}
		
		int k = 0;
		for (i = 0; i < strlen(ch); i++) {
			if (ch[i] == ',') {
				for (k = i + 1; k < strlen(ch); k++) {
					temp1[m] = ch[k];
					m++;
				}
				temp1[m] = NULL;
			}
		}
		for (i = 0; i < strlen(temp1); i++) {
			if (temp1[i] == '.') {
				temp1[i] = NULL;
			}
		}
		string temp2(temp1);
		add->file_name = temp2;
		add->dir_name = dirName;


		int num = 0;
		if (title->right == NULL) //title is directory node(Loaded_List_Node1)
		{
			title->right = add;
			cur = title->right;
			tail = add;
		}

		else {

			tail->right = add;
			add->prior = tail;
			tail = tail->right;
		}

		num += 1; //update total nodes of linked list
	}

	Loaded_LIST_Node1* add(string dirName) { // function of add directory node
		Loaded_LIST_Node1* add_dirName = new Loaded_LIST_Node1; //allocate heap memory of Loaded_List_Node1
		add_dirName->dir_name = dirName; 

		rear->down = add_dirName;//linking directory node

		rear = rear->down;  
		return rear; //return title's address then, insert node by using this address
	}

	void modify_uniqueNum(string r_title_name, string r_search, int r_inputNum) {
		ofstream log("log.txt", ios::app);
		string search; //search file name
		string title_name; //directory name
		int inputNum; //unique num(will change)

		title_name = r_title_name;  
		search = r_search;
		inputNum = r_inputNum;
		int count = 0;
		int find = 0;


		Loaded_LIST_Node1* curr = head; 
		cur = curr->right; 


		while (curr != NULL) {
			cur = curr->right;

			while (cur != NULL) {
				if (cur->unique_num == inputNum) { //if inputNum(that is change with original unique num) is already in linked list
					L_error(3); //error
					return;
				}
				if (cur->file_name == search) { //if find search file name in linked list
					find = 1; //find is 1
					break;
				}
				cur = cur->right;
				
			}
			if (find == 1) { 
				
				Loaded_LIST_Node2** store = &cur; //store find node's address
				Loaded_LIST_Node2* add = new Loaded_LIST_Node2; //allocate heap memory Loaded_List_Node2
				add->dir_name = title_name;
				add->file_name = search;
				add->unique_num = inputNum;
				if (curr->right == cur) { //if cur node is in first of linked list
					curr->right = add;
					add->prior = NULL;
					add->right = cur->right;
					cur->right->prior = add;
				}
				else if (cur->right == NULL) //if cur node is in tail of linked list
				{
					add->prior = cur->prior;
					cur->prior->right = add;
				}

				else { 
					add->right = cur->right;
					cur->right->prior = add;
					add->prior = cur->prior;
					cur->prior->right = add;
				}
				delete cur;
				log << "========MODIFY============" << endl;
				log << "SUCCESS" << endl;
				log << "==========================" << endl;
				return;
			}
			curr = curr->down;
		}
		 if (find == 0) { //can't find file name
			 L_error(3); //error
			 return;
			}

	}
	int already_in(string dirName) { //if directory is already in linked list
		Loaded_LIST_Node1* curr = head;
		while (curr != NULL) {
			if (curr->dir_name == dirName) {
				return 1;
			}
			curr = curr->down;
		}
		return 0;

	}
	void move(Database_BST* t) { 

		Loaded_LIST_Node1* curr = head;
		Loaded_LIST_Node1* p_curr = curr; //parent of curr
		Loaded_LIST_Node2* del; //delete node
		Loaded_LIST_Node1* rear; 

		while (head != NULL) {
			curr = head;
			p_curr = curr;

			while (curr->down != NULL) { //go to the last directory node of linked list
				p_curr = curr;
				curr = curr->down;
			}

			Loaded_LIST_Node2* cur = curr->right; // call cur node 
			while (cur->right != NULL) { // go to the last node of Loaded_List_Node2

				cur = cur->right;
			}
			if (cur->right == NULL) {

				tail = cur;
			}
			while (tail != NULL) { //from tail to first node -> move to tree and delete
				//cout << tail->unique_num<<endl;
				t->insert_tree(tail->unique_num, tail->dir_name, tail->file_name); //move to tree
				del = tail;
				tail = tail->prior;
				delete del;
			}
			rear = curr;
			p_curr->down = NULL;
			if (rear == head) { //only head remains-> delete it and break
				delete rear;
				break;
			}
			delete rear; //the directory node is also deleted
		}
		return;

	}
	void delete_all(string dirName) { //delete all nodes of linked list when "LOAD" or "ADD" already be in linked list
		Loaded_LIST_Node1* curr = head;
		Loaded_LIST_Node1* p_curr = curr;
		Loaded_LIST_Node2* del;

		while (curr->down != NULL) { //similar algorithm with move function -> skip comment
			p_curr = curr;
			cur = curr->right;
			if (curr->dir_name == dirName) {
				while (cur->right != NULL) {

					cur = cur->right;
				}
				if (cur->right == NULL) {

					tail = cur;
				}
				while (tail != NULL) {

					del = tail;
					tail = tail->prior;
					delete del;
				}
				p_curr->down = NULL;
				delete curr;
				break;
			}
			curr = curr->down;
		}
	}
	void L_error(int num) { //error message class
		ofstream log("log.txt", ios::app);
		if (num == 1) {
			log << "========ERROR========" << endl;
			log << 100 << endl;
			log << "=====================" << endl;
		}
		else if (num == 2) {
			log << "========ERROR========" << endl;
			log << 200 << endl;
			log << "=====================" << endl;
		}
		else if (num == 3) {
			log << "========ERROR========" << endl;
			log << 300 << endl;
			log << "=====================" << endl;
		}
	}
};