#pragma once
#ifndef EDIT
#define EDIT
#include<iostream>
#include<fstream>
#include <string>
#include<cstring>
using namespace std;
#endif

class editQ {   //queue for EDIT(_adjusted)
private:
	int idx;  //index of aueue array
	int size = 256 * 256 + 1;  //raw file width x height + 1
	unsigned char queue[256 * 256 + 1];  //call unsigned char queue array
	int i = 0;

public:
	editQ() {
		idx = -1;
	}
	int q_isempty() {     //if idx == -1 -> queue is empty
		if (idx == -1) {
			return 1;
		}
		else
			return 0;
	}
	void Enque(unsigned char input) { //if queue is not over -> enqueue
		
		if (idx < size) {
			idx += 1;
			queue[idx] = input;
	
		}
	}

	unsigned char Deque() {   //first in first out
		if (i < idx + 1) {
			return queue[i++];
		}
	}
};

class editStack {
private:
	int top = -1; // top index of stack
	int size = 256 * 256 + 1;  //raw file width x height + 1
	unsigned char stack[256 * 256 + 1]; //call unsigned char queue stack

public:

	int Stack_isempty() { //if top is -1 -> this stack is empty
		if (top == -1) {
			return 1;
		}
		else
			return 0;
	}

	void push(unsigned char input) {
		if (top < size && input != NULL) {  //stack is not over and input is not null
			top += 1;
			
			stack[top] = input;           //input stack
		
		}
	}
	unsigned char pop() {
		int delIndex;
		if (Stack_isempty()) { 
			return NULL;
		}
		delIndex = top;     //store original top
		top -= 1;          //update top

		return stack[delIndex]; //last in first out
	}
};