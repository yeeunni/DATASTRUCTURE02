#include "stdio.h"
#pragma warning(disable:4996)
#ifndef INCLUDES_t
#define INCLUDES_t
#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<cstring>
using namespace std;
#endif
#include "edit.h";

class Database_BST_Node { //tree node
public:
	Database_BST_Node* right = NULL;
	Database_BST_Node* left = NULL;
	int unique_num = 0;
	string dirName;
	string fileName;
};

class Database_BST {
private:
	Database_BST_Node* Root;
	int total; //total number of tree 
	int count = 0;
	editStack es; //instance of editStack(for EDIT)
	editQ eq;// instance of editQ(for EDIT)
	int brightness; // brightness for using EDIT
	Database_BST_Node* find; //pointer of EDIT file's address
public:
	Database_BST() {
		Root = NULL;
		total = 0;
	}
	Database_BST_Node* getRoot() {
		if (Root) {
			return Root;
		}
		else
			return NULL;
	}
	void insert_tree(int num, string dir, string file) { // insert tree node from linked list(read only data from linked list)
		Database_BST_Node* cur = Root;
		Database_BST_Node* cur_parent = NULL;
		Database_BST_Node* add_tree = new Database_BST_Node; //allocate heap memory of Database_BST_Node
		add_tree->right = NULL;
		add_tree->left = NULL;
		add_tree->unique_num = num;
		add_tree->dirName = dir;
		add_tree->fileName = file;
		if (total > 300) { //total nodes is over 300-> delete leaf node 
			delete_node();
			total -= 1;
		}
		if (Root == NULL) { //assign Root
			Root = add_tree;
		}
		else {
			while (cur != NULL) { //insert tree node with criteria of unique number's size

				cur_parent = cur;

				if (cur->unique_num == num) { // if same unique_num  is in tree node
					delete add_tree;
					break;
				}
				else if (cur->unique_num < num) {

					cur = cur->right;

				}
				else if (cur->unique_num > num) {

					cur = cur->left;

				}
			}
			if (cur_parent != NULL) { 
				if (cur_parent->unique_num < num) {
					cur_parent->right = add_tree;
					total += 1;                      //total number of node ++
					
				}
				else if (cur_parent->unique_num > num) {
					cur_parent->left = add_tree;
					total += 1;                       //total number of node ++

				}
			}
		}
	}
	void get_brightness(int num) {
		brightness = num;
	}

	bool exist() { // if tree is exist?
		if (Root) // Root is not NULL
			return true; //exist is true
		else
			return false;
	}
	void Inorder(Database_BST_Node* cur) //inorder to print all nodes of BST
	{
		ofstream log("log.txt", ios::app);
		if (cur == NULL)
			return;

		//  recur left subtree 
		Inorder(cur->left);

		// print node 
		log << cur->dirName << " /" << "\"" << cur->fileName  << "\"" << "/ " << cur->unique_num;
		log << endl;
		// recur right subtree 
		Inorder(cur->right);
	}
	void postorderforExit(Database_BST_Node* cur) //delete all tree node for EXIT
	{
		if (cur == NULL)
			return;

		//  recur left subtree 
		postorderforExit(cur->left);
		// recur right subtree 
		postorderforExit(cur->right);
		delete_node(cur);
	}
	void usePostorder() {
		postorderforExit(Root);
	}
	int numisin() { //if uniquenumber is in BST?
		if (find != NULL) //find node is not NULL
			return 1; // is in = true
		else
			return 0;
	}
	void get_img(Database_BST_Node* cur, int num) { //find node's address and type of edit parameter
		ofstream log("log.txt", ios::app);
		string total_file = "./" + cur->dirName + "/" + cur->fileName + ".RAW"; //read find node's information -> path of file
		char total_file_c[100];
		string output_total;
		strcpy(total_file_c, total_file.c_str()); // string to char
		int width = 256, height = 256;

		FILE* input_file, * output_file;

		unsigned char input_data[256][256];
		unsigned char output_data[256][256];


		// read raw file
		input_file = fopen(total_file_c, "rb");
		if (input_file == NULL)
		{
			printf("File not found!!\n");
			return;
		}
		fread(input_data, sizeof(unsigned char), width * height, input_file);

		if (num == 0) { //select function
			return;
		}
		else if (num == -1) { //flipped edit
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					es.push(input_data[i][j]);  //256*256 img push in stack
				}
			}

			for (int m = 0; m < height; m++) {
				for (int n = 0; n < width; n++) {

					output_data[m][n] = es.pop(); //ouput_data = 256*256 img pop in stack
				}

			}
			output_total = "./Result/" + cur->fileName + "_flipped.RAW"; //change name
		}
		else if (num == -2) { //adjusted edit(change brightness)
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					eq.Enque(input_data[i][j]);   //file enque in queue
				}
			}

			for (int m = 0; m < height; m++) {
				for (int n = 0; n < width; n++) {

					if (brightness + input_data[m][n] > 255) { //if over the max brightness
						brightness = 255 - input_data[m][n]; 
					}
					else if (brightness + input_data[m][n] < 0) { //if under the min brightness
						input_data[m][n] = 0;
					}
					output_data[m][n] = eq.Deque() + brightness; //output_data = deque
				}
			}
			output_total = "./Result/" + cur->fileName + "_adjusted.RAW"; //change name
		}
		else if (num == -3) { //resized edit
			int c = 0, r = 0;
			for (int i = 0; i < height; i += 2) {
				for (int j = 0; j < width; j += 2) {
					output_data[i / 2][j / 2] = (input_data[i][j] + input_data[i][j + 1] + input_data[i + 1][j] + input_data[i + 1][j]) / 4; //resized to 1/4 of original img size
				}
			}
			output_total = "./Result/" + cur->fileName + "_resized.RAW"; //change name
		}
		//store changed img
		char total_file_out[100];
		strcpy(total_file_out, output_total.c_str());
		output_file = fopen(total_file_out, "wb");
		fwrite(output_data, sizeof(unsigned char), width * height, output_file);
		log << '\n' << "========EDIT======= " << endl;
		log << "SUCCESS" << endl;
		log << "==================" << endl;
		fclose(input_file);
		fclose(output_file);
	}

	void Preorder(Database_BST_Node* cur, int inputNum) //find file that is same with input unique number by preorder
	{
		ofstream log("log.txt", ios::app);
		if (cur == NULL) {
			return;
		}

		if (cur->unique_num == inputNum) {
			get_img(cur, 0);    
			log << "=====SELECT======" << endl;
			log << "SUCCESS" << endl;
			log << "================" << endl;

			count = 1;
			find = cur;                            //find node is cur node's address whose unique number is same with input number
			return;
		}
		Preorder(cur->left, inputNum); //recur left subtree
		Preorder(cur->right, inputNum); //recur right subtree
	}

	void select(int inputNum) { //select function
		ofstream log("log.txt", ios::app);
		     
			Preorder(Root, inputNum);    //Preorder function
		
	}
	void select_edit(int inputNum) { //select find node and edit
		if (inputNum == -1) {          //flipped edit
			get_img(find, -1);
		}
		else if (inputNum == -2) { //adjusted edit
			get_img(find, -2);
		}
		else if (inputNum == -3) { //resized edit
			get_img(find, -3);
		}
	}

	void printInorder() {  //use this->Inorder function

		this->Inorder(Root);

	}
	void t_error(int num) { //error message
		ofstream log("log.txt", ios::app);
		if (num == 4) {                         //MOVE ERROR
			log << endl;
			log << "========ERROR========" << endl;
			log << 400 << endl;
			log << "=====================" << endl;
		}
		else if (num == 5) {                     //PRINT ERROR
			log << endl;
			log << "========ERROR========" << endl;
			log << 500 << endl;
			log << "=====================" << endl;
		} 
		else if (num == 6) {                    //SEARCH ERROR
			log << endl;
			log << "========ERROR========" << endl;
			log << 600 << endl;
			log << "=====================" << endl;
		}
		else if (num == 7) {                       //SELECT ERROR
			log << endl;
			log << "========ERROR========" << endl;
			log << 700 << endl;
			log << "=====================" << endl;
		}
		else if (num == 8) {                       //EDIT ERROR
			log << endl;
			log << "========ERROR========" << endl;
			log << 800 << endl;
			log << "=====================" << endl;
		}
	}


	Database_BST_Node* get_max(Database_BST_Node* node) {  //get max node of subtree's left for delete node that has 2 child nodes
		Database_BST_Node* cur = node->left;

		while (cur && cur->right != NULL) {
			cur = cur->right;
		}
		return cur;
	}

	Database_BST_Node* get_min(Database_BST_Node* node) { //get the most min leaf node
		Database_BST_Node* cur_parent = NULL;
		Database_BST_Node* cur = node->left;

		while (cur && cur->left != NULL) {
			cur_parent = cur;
			cur = cur->left;
		}
		return cur; //return cur
	}
	Database_BST_Node* get_minParent(Database_BST_Node* node) { //get the most min leaf node's parent node
		Database_BST_Node* cur_parent = NULL;
		Database_BST_Node* cur = node->left;

		while (cur && cur->left != NULL) {
			cur_parent = cur;
			cur = cur->left;
		}
		return cur_parent; //return cur_parent
	}
	void delete_node() {

		Database_BST_Node* cur = get_min(Root); //cur is the most min node
		Database_BST_Node* cur_parent = get_minParent(Root); 

		if (cur->right == NULL && cur->left == NULL) { //if delete node has no child
			if (cur_parent == NULL) {
				Root = NULL;
			}
			else if (cur_parent->unique_num > cur->unique_num) {
				cur_parent->left = NULL;                      // //disconnect cur->left
			}
			else if (cur_parent->unique_num < cur->unique_num) {
				cur_parent->right = NULL;                     //disconnect cur->right
			}
			delete cur;
			return;
		}
		else if (cur->right != NULL && cur->left == NULL) { //if delete node has right child
			if (cur_parent == NULL) {
				Root = cur->right;
			}
			else if (cur_parent->unique_num < cur->unique_num) {
				cur_parent->right = cur->right;  //disconnect cur->right
				cur->right = NULL;
			}
			else if (cur_parent->unique_num > cur->unique_num) {
				cur_parent->left = cur->right;
				cur->right = NULL;  //disconnect cur->right
			}
			delete cur;
			return;
		}
		else if (cur->right == NULL && cur->left != NULL) { //if delete node has left child
			if (cur_parent == NULL) {
				Root = cur->left;
			}
			else if (cur_parent->unique_num < cur->unique_num) { 
				cur_parent->right = cur->left;
				cur->left = NULL;                          //disconnect cur->left
			}
			else if (cur_parent->unique_num > cur->unique_num) {
				cur_parent->left = cur->left;
				cur->left = NULL;                       //disconnect cur->left
			}
			delete cur;
			return;
		}
		else if (cur->right != NULL && cur->left != NULL) { //if delete node has 2 child nodes
			int temp;
			temp = cur->unique_num;
			cur->unique_num = get_max(cur)->unique_num;     /*change del node's value and get_max node's value*/
			get_max(cur)->unique_num = temp;
			Database_BST_Node* del = get_max(cur);    
			delete_node(del);      //delete_node that has parameter
		}
	}
	void delete_node(Database_BST_Node* node) {  //same with delete_node but has parameter ->skip comment (same algorithm)

		int num = node->unique_num;
		Database_BST_Node* cur = Root;
		Database_BST_Node* cur_parent = cur;

		while (cur != NULL) {

			if (cur->unique_num == num) {

				if (cur->right == NULL && cur->left == NULL) {
					if (cur_parent == NULL) {
						Root = NULL;
					}
					else if (cur_parent->unique_num > num) {
						cur_parent->left = NULL;
					}
					else if (cur_parent->unique_num < num) {
						cur_parent->right = NULL;
					}
					delete cur;
					return;
				}
				else if (cur->right != NULL && cur->left == NULL) {
					if (cur_parent == NULL) {
						Root = cur->right;
					}
					else if (cur_parent->unique_num < cur->unique_num) {
						cur_parent->right = cur->right;
						cur->right = NULL;
					}
					else if (cur_parent->unique_num > cur->unique_num) {
						cur_parent->left = cur->right;
						cur->right = NULL;
					}
					delete cur;
					return;
				}
				else if (cur->right == NULL && cur->left != NULL) {
					if (cur_parent == NULL) {
						Root = cur->left;
					}
					else if (cur_parent->unique_num < cur->unique_num) {
						cur_parent->right = cur->left;
						cur->left = NULL;
					}
					else if (cur_parent->unique_num > cur->unique_num) {
						cur_parent->left = cur->left;
						cur->left = NULL;
					}
					delete cur;
					return;
				}
				else if (cur->right != NULL && cur->left != NULL) {
					int temp;
					temp = cur->unique_num;
					cur->unique_num = get_max(cur)->unique_num;
					get_max(cur)->unique_num = temp;
					Database_BST_Node* del = get_max(cur);
					delete_node(del);  //recur function
				}
			}
			else if (cur->unique_num < num) {
				cur_parent = cur;
				cur = cur->right;
			}
			else if (cur->unique_num > num) {
				cur_parent = cur;
				cur = cur->left;
			}
		}
	}


};
