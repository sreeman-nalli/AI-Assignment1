#include "algorithm.h"
#include <vector>

using namespace std;

/////////////////////////////////////////QUEUE/////////////////////////////////////
Queue::Queue() {
	front = NULL;
	rear = NULL;
	count = 0;
	maxQLen = 0;
}
Queue::~Queue() {
}

void Queue::Join (Puzzle *newthing) {
	Node *temp;
	temp = new Node;
	temp->data = newthing;
	temp->next = NULL;

	if (rear != NULL) {
		rear->next = temp;
	}
	rear = temp;
	if (front == NULL) {
		front = temp;
	}
	count++;
	if (maxQLen < count) {
		maxQLen = count;
	}
}

void Queue::Leave() {
	Node *temp;
	if (front == NULL) {
		return;
	}
	temp = front;
	front = front->next;
	if (front == NULL) {
		rear = NULL;
	}
	delete temp;
	count--;
}

Puzzle * Queue::Front() {
	return front->data;
}

bool Queue::isEmpty() {
	if (count == 0) {
		return true;
	}
	return false;
}

int Queue::QueueLength() {
	return count;
}

int Queue::MaxLength() {
	return maxQLen;
}

bool Queue::StateExists(Puzzle *state) {
	Node *current = front;
	Puzzle *traversingStates;
	string visitedStates;
	string givenState = state->getString();
	while (current != NULL) {
		traversingStates = current->data;
		visitedStates = traversingStates->getString();
		if (visitedStates == givenState) {
			return true;
		}
		current = current->next;
	}
	return false;
}


VisitedListQueue::VisitedListQueue() {
	front = NULL;
	rear = NULL;
	count = 0;
}
VisitedListQueue::~VisitedListQueue() {
}

void VisitedListQueue::Join (string newthing) {
	State *temp;
	temp = new State;
	temp->data = newthing;
	temp->next = NULL;

	if (rear != NULL) {
		rear->next = temp;
	}
	rear = temp;
	if (front == NULL) {
		front = temp;
	}
	count++;
}

void VisitedListQueue::Leave() {
	State *temp;
	if (front == NULL) {
		return;
	}
	temp = front;
	front = front->next;
	if (front == NULL) {
		rear = NULL;
	}
	delete temp;
	count--;
}

string VisitedListQueue::Front() {
	return front->data;
}

bool VisitedListQueue::isEmpty() {
	if (count == 0) {
		return true;
	}
	return false;
}

int VisitedListQueue::QueueLength() {
	return count;
}

bool VisitedListQueue::StateExists(Puzzle *state) {
	State *current = front;
	string givenState = state->getString();
	while (current != NULL) {
		if (givenState.compare(current->data) == 0) {
			return true;
		}
		current = current->next;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search
//
// Move Generator: U,R,D,L
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch(string const initialState, string const goalState, int &numOfStateExpansions, int &maxQLength, float &actualRunningTime){
    string path;
	clock_t startTime;
    //add necessary variables here

		Queue *queue = new Queue();
		 Puzzle *p = new Puzzle(initialState, goalState);
		//  Puzzle *p = new Puzzle("123840765", goalState);
		Puzzle *temp = p;
		bool goalMatch = p->goalMatch();
		numOfStateExpansions = 0;


    // algorithm implementation
	// cout << "------------------------------" << endl;
  //   cout << "<<breadthFirstSearch>>" << endl;
  //   cout << "------------------------------" << endl;
	cout<< initialState << endl;
	cout<< goalState <<endl;
	startTime = clock();

	maxQLength=0;

	string tempPath;
	while (goalMatch == false) {
		++numOfStateExpansions;
		if (temp->canMoveLeft() == true) {
			if (temp->getPathLength() > 0) {
				tempPath = temp->getPath()[temp->getPathLength()-1];
				if (tempPath.compare("R") != 0) {
					queue->Join(temp->moveLeft());
				}
			}else {
				queue->Join(temp->moveLeft());
			}

			//cout<<"L"<<endl;
		}
		if (temp->canMoveUp() == true) {
			if (temp->getPathLength() > 0) {
				tempPath = temp->getPath()[temp->getPathLength()-1];
				if (tempPath.compare("D") != 0) {
					queue->Join(temp->moveUp());
				}
			}else {
				queue->Join(temp->moveUp());
			}


				//cout<<"U"<<endl;
			}
			if (temp->canMoveRight() == true) {
				if (temp->getPathLength() > 0) {
					tempPath = temp->getPath()[temp->getPathLength()-1];
					if (tempPath.compare("L") != 0) {
						queue->Join(temp->moveRight());
					}
				}else {
					queue->Join(temp->moveRight());
				}

				//cout<<"R"<<endl;
			}
			if (temp->canMoveDown() == true) {
				if (temp->getPathLength() > 0) {
					tempPath = temp->getPath()[temp->getPathLength()-1];
					if (tempPath.compare("U") != 0) {
						queue->Join(temp->moveDown());
					}
				}else {
					queue->Join(temp->moveDown());
				}

				//cout<<"D"<<endl;
			}

			temp = queue->Front();
			queue->Leave();
			goalMatch = temp->goalMatch();
	}

	maxQLength=queue->MaxLength();
	delete queue;
	//***********************************************************************************************************
		actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
		//path = "DDRRLLLUUU";  //this is just a dummy path for testing the function

		path = temp->getPath();

		delete p;
		cout<<path<<endl;
		return path;

}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Breadth-First Search with VisitedList
//
// Move Generator: L,U,R,D
//
////////////////////////////////////////////////////////////////////////////////////////////
string breadthFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){
    string path;
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<breadthFirstSearch_with_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();
	maxQLength=0;

	Queue *queue = new Queue();
	// Queue *visitedList = new Queue();
	VisitedListQueue *visitedList = new VisitedListQueue();
	Puzzle *p = new Puzzle(initialState, goalState);
	Puzzle *state = p;
	Puzzle *temp;
	bool goalMatch = state->goalMatch();

	numOfStateExpansions = 0;
	// visitedList->Join(p);
	visitedList->Join(p->getString());

	string tempPath;
	int count = 0;

	while (goalMatch == false) {
		++numOfStateExpansions;
		if (state->canMoveLeft() == true) {

			temp = state->moveLeft();
			if (state->getPathLength() > 0) {
				tempPath = state->getPath()[state->getPathLength()-1];
				if (tempPath.compare("R") != 0) {
					if (visitedList->StateExists(temp) == false) {
						queue->Join(temp);

						// visitedList->Join(temp);
					}
				}else {
					count++;
				}
			}else {
				if (visitedList->StateExists(temp) == false) {
					queue->Join(temp);

					// visitedList->Join(temp);
				}
			}

			visitedList->Join(temp->getString());
			//cout<<"L"<<endl;
		}
		if (state->canMoveUp() == true) {
				temp = state->moveUp();
				//
				// if (visitedList->StateExists(temp) == false) {
				// 	queue->Join(temp);
				// }
				// visitedList->Join(temp);

				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("D") != 0) {
						if (visitedList->StateExists(temp) == false) {
							queue->Join(temp);

							// visitedList->Join(temp);
						}
					}else {
						count++;
					}
				}else {
					if (visitedList->StateExists(temp) == false) {
						queue->Join(temp);

						// visitedList->Join(temp);
					}
				}
				visitedList->Join(temp->getString());
				//cout<<"U"<<endl;
			}
			if (state->canMoveRight() == true) {
				temp = state->moveRight();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("L") != 0) {
						if (visitedList->StateExists(temp) == false) {
							queue->Join(temp);

							// visitedList->Join(temp);
						}
					}else {
						count++;
					}
				}else {
					if (visitedList->StateExists(temp) == false) {
						queue->Join(temp);

						// visitedList->Join(temp);
					}
				}
				visitedList->Join(temp->getString());
				//cout<<"R"<<endl;
			}
			if (state->canMoveDown() == true) {
				temp = state->moveDown();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("U") != 0) {
						if (visitedList->StateExists(temp) == false) {
							queue->Join(temp);

							// visitedList->Join(temp);
						}
					}else {
						count++;
					}
				}else {
					if (visitedList->StateExists(temp) == false) {
						queue->Join(temp);

						// visitedList->Join(temp);
					}
				}
				visitedList->Join(temp->getString());
				//cout<<"D"<<endl;
			}

			state = queue->Front();
			queue->Leave();
			goalMatch = state->goalMatch();

			if (count % 10000 == 0) {

				cout<<"COUNT: "<<count<<endl;
			}
	}

	cout<<"ENDING"<<endl;
	cout<<count<<endl;
	path = state->getPath();

	maxQLength=queue->MaxLength();
	delete queue;
	delete visitedList;
	delete p;
	//cout<<path<<endl;
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	//path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
	return path;

}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	clock_t startTime;
    //add necessary variables here

		Puzzle *p = new Puzzle(initialState, goalState);

		cout<<"toString: "<<p->toString()<<endl;
		cout<<"getString: "<<p->getString()<<endl;

		p = p->moveRight();

		cout<<"toString: "<<p->toString()<<endl;
		cout<<"getString: "<<p->getString()<<endl;

    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_No_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();

	maxQLength=0;


//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUU";  //this is just a dummy path for testing the function
	return path;

}




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:
//
// Move Generator:
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_with_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_with_NonStrict_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();

	maxQLength=0;


//***********************************************************************************************************
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUU"; //this is just a dummy path for testing the function

	return path;

}


string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){

   string path;
   clock_t startTime;

   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;
	startTime = clock();

	maxQLength=0;


//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	path = "DDRRLLLUUU"; //this is just a dummy path for testing the function

	return path;

}
