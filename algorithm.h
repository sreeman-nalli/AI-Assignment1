
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "puzzle.h"

const heuristicFunction HEURISTIC_FUNCTION=manhattanDistance;

//
// int parindex=0;
// int leftindex = (parindex * 2) + 1;		// Left child
// int rightindex = (parindex * 2) + 2;	// Right child
//
// int parentIndexCost = data[parindex]->getFCost();
// int leftIndexCost, rightIndexCost;
//
// if (leftindex < last) {
// 	compDel++;
// 	 leftIndexCost = data[leftindex]->getFCost();
// }else {
// 	leftIndexCost = 99999;
// }
// if (rightindex < last) {
// 	compDel++;
// 	rightIndexCost = data[rightindex]->getFCost();
// }else {
// 	rightIndexCost = 99999;
// }
//
// while (parentIndexCost > leftIndexCost || parentIndexCost > rightIndexCost){
// 	// cout<<"2"<<endl;
// 	if (rightIndexCost > leftIndexCost) { 	// Follow left.
// 		swap(data[leftindex], data[parindex]);
// 		parindex = leftindex;
// 	}
// 	else { 													// Else, follow right.
// 		swap(data[rightindex], data[parindex]);
// 		parindex = rightindex;
// 	}
// 	leftindex = (parindex * 2) + 1;
// 	rightindex = (parindex * 2) + 2;
//
// 	parentIndexCost = data[parindex]->getFCost();
// 	if (leftindex < last) {
// 		compDel++;
// 		 leftIndexCost = data[leftindex]->getFCost();
// 	}else {
// 		leftIndexCost = 99999;
// 	}
// 	if (rightindex < last) {
// 		compDel++;
// 		rightIndexCost = data[rightindex]->getFCost();
// 	}else {
// 		rightIndexCost = 99999;
// 	}
//
// 	if (leftindex > last) {
// 		break;
// 	} else {
// 		if (rightindex > last) {
// 			compDel++;
// 			if (parentIndexCost > leftIndexCost) {
// 				swap(data[parindex], data[leftindex]);
// 			}
// 			break;
// 		}
// 	}
// }


struct Node {
	Puzzle *data;
	Node *next;
};

/* implement your Queue class here */
class Queue {
private:
	Node *front;
	Node *rear;
	int count;
	int maxQLen;
public:
	Queue();
	~Queue();
	void Join(Puzzle *newthing);
	void AddToFront (Puzzle *newthing);
	void Leave();
	void LeaveWithoutDelete();
	Puzzle * Front();
	bool isEmpty();
	int QueueLength();
	int MaxLength();
	bool StateExists(Puzzle *state);
};

struct State {
	string data;
	State *next;
};

/* implement your Queue class here */
class VisitedListQueue {
private:
	State *front;
	State *rear;
	int count;
public:
	VisitedListQueue();
	~VisitedListQueue();
	void Join(string newthing);
	void Leave();
	string Front();
	bool isEmpty();
	int QueueLength();
	bool StateExists(Puzzle *state);
	bool StrictExpandedListStateCheck(Puzzle *state);
};

class HashedVisitedList {
private:
	State *list[296];
	int count;
public:
	HashedVisitedList() {
		count = 0;
		for (int i = 0; i<296; ++i) {
			list[i] = NULL;
		}
	}
	~HashedVisitedList() {}
	void InsertString (string strState, int position);
	void InsertStringPDS(string strState, int position, int stateDepth);
	bool StateExists(string strState, int position);
	bool StateExistsPDS(string strState, int position, int stateDepth);
	void TraverseList ();
};

struct StatePDS{
	string data;
	int depth;
	StatePDS *next;
};

class HashedVisitedListPDS {
private:
	StatePDS *list[296];
	int count;
public:
	HashedVisitedListPDS() {
		count = 0;
		for (int i = 0; i<296; ++i) {
			list[i] = NULL;
		}
	}
	~HashedVisitedListPDS() {}
	void InsertStringPDS(string strState, int position, int stateDepth);
	bool StateExistsPDS(string strState, int position, int stateDepth);
};



class Heap {
	private:
		Puzzle *data[400000];
		int last;
		int compAdd;
		int compDel;
		int maxHeapLength;
	public:
		Heap() {
			last = -1;
			compAdd = 0;
			compDel = 0;
			maxHeapLength = 0;
		};
		~Heap() { };//destructor
		void InsertHeap(Puzzle *state);
		void FixHeap();
		Puzzle * Delete();
		int MaxHeapLenght() {return maxHeapLength;}
		Puzzle *Front() {
			return data[0];
		}
		int NumOfDeletionsFromHeap() {
			return compDel;
		}
		void DeleteFromMiddle (int position);
		void traverseStates(Puzzle *state);
};



//Function prototypes

int generateHashKey (Puzzle * state);

string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth);
string progressiveDeepeningSearch_with_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth);

string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime);
string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime);

string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic);

#endif
