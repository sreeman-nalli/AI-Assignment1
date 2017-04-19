
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "puzzle.h"

const heuristicFunction HEURISTIC_FUNCTION=manhattanDistance;


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
	void Leave();
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
	bool StateExists(string strState, int position);
	void TraverseList ();
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
