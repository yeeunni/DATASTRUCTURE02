#ifndef INCLUDES_L1
#define INCLUDES_L1
#include "LoadCsv.h"
#endif
#include "SearchStack.h"
#include<sstream>
class Manager {


public:
	int manager() {

		ifstream file; //read csv file ifstream 'file'
		ofstream log("log.txt", ios::out | ios::app); // write on txt file ofstream 'log'
		ifstream txt; // read txt file ifstream 'txt'
		string order; //read order from command.txt
		string str; // read file from csv file
		Loaded_LIST Loaded_LIST; // instance of Loaded_LIST
		Loaded_LIST_Node1* title; //instance of Loaded_List_Node1

		Database_BST t; //instance of Database_BST
		SearchStack ss; //instance of SearchStack
		searchQueue(searchq); //instance of searchQueue
		int no_edit = 0;

		txt.open("command.txt", ios::in); //txt file open
		while (!txt.eof()) 
		{
			getline(txt, order);
			stringstream com(order);
			string command, dir, filename, number;
			com >> command;
			if (command == "LOAD") 
			{
				file.open("img_files/filesnumbers.csv", ios::in);
				if (!file.is_open()) {                    //if no file->error  
					Loaded_LIST.L_error(1); 
					return 0;
				}
				else {
					log << "========LOAD========" << endl;
					while (!file.eof()) {
						getline(file, str);      //read file line by line
						if (!str.compare(""))           //don't read last space sentence
							break;
						char ch1[100];
						if (str[0] == '\xEF' && str[1] == '\xBB' && str[2] == '\xBF') //when read utf-8 file, remove trash value
						{
							str.erase(0, 3);
						}
						strcpy(ch1, str.c_str()); // string to char for clssify unique num, file name
						if (Loaded_LIST.already_in(dir)) { //if directory name is already in linked list, delete it
							Loaded_LIST.delete_all(dir);
						}

						Loaded_LIST.insert_node(ch1); // add linked list
					}
					log << "==================" << endl;
					file.close();
				}
			}
			else if (command == "ADD")
			{
				com >> dir; // read directory name
				com >> filename; //read csv file name
				if (filename.size() < 1 || dir.size() < 1 || !Loaded_LIST.L_exist()) { // don't have any parameter or if linked list is not exist->error 
					Loaded_LIST.L_error(2);
				}
				else {
					string final_filename = dir + "/" + filename; // path of csv file

					file.open(final_filename, ios::in);

					title = Loaded_LIST.add(dir); // add directory to exisisting linked list and return its address 
					if (!file.is_open()) {  //if file is not exist
						ofstream ofs(final_filename, ios::in); //make file by using ofstream
						return 0;
					}

					while (!file.eof()) {
						getline(file, str);  //same with <Load>
						if (!str.compare(""))
							break;
						char ch2[100];
						if (str[0] == '\xEF' && str[1] == '\xBB' && str[2] == '\xBF')
						{
							str.erase(0, 3);
						}
						if (Loaded_LIST.already_in(dir)) {
							Loaded_LIST.delete_all(dir);
						}
						strcpy(ch2, str.c_str());
						Loaded_LIST.insert_node(ch2, title, dir);
					}
					log << "========ADD========" << endl;
					log << "SUCCESS" << endl;
					log << "==================" << endl;
					file.close();
				}

			}
			else if (command == "MODIFY")
			{
				com >> dir; //read directory name
				getline(com, filename, '"'); //read file name by criteria '"'
				getline(com, filename, '"');
				com >> number; //read unique num(would like to change with it)
				if (dir.size() < 1 || number.size() < 1) { //insufficient parameter
					Loaded_LIST.L_error(3); //error
				}
				
				int r_inputNum = atoi(number.c_str()); //string number to int number
				Loaded_LIST.modify_uniqueNum(dir, filename, r_inputNum); //Loaded_List function
				
			}
			else if (command == "MOVE") 
			{
				if (Loaded_LIST.L_exist()) {
					Loaded_LIST.move(&t); //linked list move to tree's address
					log << "========MOVE========" << endl;
					log << "SUCCESS" << endl;
					log << "===================" << endl;
				}
				else
					t.t_error(4);
			}
			else if (command == "PRINT")
			{
				if (t.exist()) {   
					log << "========PRINT==============" << endl;
					t.printInorder(); //print tree's all nodes by inorder
					log << "===========================" << endl;
				}
				else
					t.t_error(4);   //tree is not exist, error
			}
			else if (command == "SEARCH")
			{
				string word; //read search word or part of sentence
				getline(com, word, '"'); // read word by criteria '"'
				getline(com, word, '"');
				
				if (word.size() < 1 || !t.exist()) { //no parameter or tree is empty
					t.t_error(6); //error
				}
				else {
					log << "=====SEARCH===============" << endl;
					ss.postorder(&t, &(searchq)); //post-order by stack and enqueue
					searchq.moore(word); // search filename by moore algorithm
					
					log << "==========================" << endl;
				}
			}
			else if (command == "SELECT")
			{
				string num;
				com >> num;  //read unique num
				if (num.size() < 1) { //no parameter -> error
					t.t_error(7);
					no_edit = 1;
				}
				else {
					int r_inputNum = atoi(num.c_str()); //string to int
					t.select(r_inputNum);//select function
				}
				if (!t.numisin()) { //if unique num is not in tree
					t.t_error(7); //error
					no_edit = 1; //can't do edit
				}

			}
			else if (command == "EDIT")
			{
				if (no_edit == 0) { //if SELECT is successful
					string type; //show type of image edit
					string num;
					com >> type; //read
					type = type[1]; //ignore '-'
					if (type.size() < 1) { //no parameter
						t.t_error(8); //error
					}
					if (type == "f") {
						t.select_edit(-1);

					}
					else if (type == "l") {
						com >> num;
						if (num.size() < 1) { //no parameter -> error
							t.t_error(8);
						}
						int r_inputNum = atoi(num.c_str()); //brightness num string to int
						t.get_brightness(r_inputNum);
						t.select_edit(-2);

					}
					else if (type == "r") {
						t.select_edit(-3);

					}
				}
				else
					t.t_error(8); //fail in SELECT -> so fail edit
			}

			else if (command == "EXIT") {
				t.usePostorder();
				log << '\n' << "========EXIT======= " << endl;
				log << "SUCCESS" << endl;
				log << "=================" << endl;
				break;
			}
		}
	}

};
