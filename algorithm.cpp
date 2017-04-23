#include "algorithm.h"
#include <vector>
#include <string>
#include <sstream>


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


void Queue::AddToFront (Puzzle *newthing) {
	Node *temp;
	temp = new Node;
	temp->data = newthing;
	temp->next = front;
	front = temp;

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

bool VisitedListQueue::StrictExpandedListStateCheck(Puzzle *state) {

	// State *current = front;
	// string givenStateString = state->getString();
	// int givenStateCost = state->getFCost();
	// string tempStateStr;
	// int tempStateCost;
	// int strLen = tempStateStr.length();
	// State *prev = NULL;
	//
	// bool exists = false;
	// while (current != NULL) {
	// 	// tempStateStr = current->data.substr(0,9); OR
	// 	// if (givenStateString.compare(tempStateStr) == 0) {
	// 	// 	if (givenStateCost < current->data)
	// 	// }
	//
	// 	tempStateStr = current->data;
	// 	if (tempStateStr.compare(0,9,givenStateString) == 0) {
	// 		// tempStateCost = tempStateStr.substr(9, strLen-9);
	// 		exists = true;
	// 		istringstream ( tempStateStr.substr(9, strLen-9) ) >> tempStateCost;
	// 		if (givenStateCost < tempStateCost) {
	// 			// this->Join(givenStateString.append(givenStateCost.toString()));
	// 			prev->next = current->next;
	// 			delete current;
	// 			this->Join(givenStateString.append(static_cast<ostringstream*>( &(ostringstream() << givenStateCost) )->str()));
	// 			return true;
	// 		} else {
	// 			return false;
	// 		}
	// 	}
	// 	prev = current;
	// 	current = current->next;
	// }
	//
	// //IF STATE xDOESNT EXIST
	// this->Join(givenStateString.append(static_cast<ostringstream*>( &(ostringstream() << givenStateCost) )->str()));
	// return true;

}

////////////////////////////////////////////////////////////////////////

/////////////////////////HEAP STRUCTURE///////////////////////////////////////////////////////

// InsertHeap - input value to add to the heap.
void Heap::InsertHeap (Puzzle *state) {

//NEED TO MODIFY TO ACCOMODATE REPEATED STATES IN HEAP AND REMOVE STATES WHERE THOSE STATES
//WHO HAVE A HIGHER COST ALSO HAVE A LOWER COST IN THE HEAP

	data[last+1] = state;
	last = last+1;

	if (last==0) {
		return;
	}
	if (maxHeapLength < last) {
		maxHeapLength = last;
	}

	// Fix the heap before leaving.
	int child_index = last;
	int par_index = 0;
	bool swapping = true;
	bool downSwapping = false;
	int startDownSwappingPosition = 0;
	string childStr;
	string parStr;
	int rightindex = 0;
	int leftindex = 0;
	while (swapping == true) {
		swapping = false;
		if(child_index % 2 == 0) {
			par_index = (child_index / 2) - 1; 	// Right child
		} else {
			par_index = (child_index / 2); 		// Left child
		}

		if (par_index >= 0) { // Make sure par_index is within the array.
			compAdd++;				// --------------------------------------------- // Debug
			childStr = data[child_index]->getString();
			parStr = data[par_index]->getString();

			if (childStr.compare(parStr) == 0) {
				downSwapping = true;
				//cout<<"DSwap"<<endl;
				startDownSwappingPosition = child_index;
			}

			if (data[child_index]->getFCost() < data[par_index]->getFCost()) {
				swap(data[child_index], data[par_index]);
				swapping = true;
				child_index = par_index;
			}
		}
	}

	//REORDER THE DOWN SWAP
	if (downSwapping == true) {
		this->DeleteFromMiddle(startDownSwappingPosition);
	}
}

void Heap::DeleteFromMiddle(int position) {

	Puzzle *temp = data[position];
	// Swap node with last, "delete" last
	data[position] = data[last];
	//data[last] = 0;//deleting...
	data[last] = NULL;
	//delete data[last];

	// subtract last
	last--;
	delete temp;

	// Fix the heap.
	int parindex = 0;
	int leftindex = (parindex * 2) + 1;		// Left child
	int rightindex = (parindex * 2) + 2;	// Right child

	int parentIndexCost = data[parindex]->getFCost();
	int leftIndexCost, rightIndexCost;
	if (leftindex < last) {
		compDel++;
		 leftIndexCost = data[leftindex]->getFCost();
	}else {
		leftIndexCost = 99999;
	}
	if (rightindex < last) {
		compDel++;
		rightIndexCost = data[rightindex]->getFCost();
	}else {
		rightIndexCost = 99999;
	}

	while (parentIndexCost > leftIndexCost || parentIndexCost > rightIndexCost){
		// cout<<"2"<<endl;
		if (rightIndexCost > leftIndexCost) { 	// Follow left.
			//printf("Swap data[%d]=%d with data[%d]=%d \n",leftindex, data[leftindex], parindex, data[parindex]);
			swap(data[leftindex], data[parindex]);
			parindex = leftindex;
		}
		else { 													// Else, follow right.
			//printf("Swap data[%d]=%d with data[%d]=%d \n",rightindex, data[rightindex], parindex, data[parindex]);
			swap(data[rightindex], data[parindex]);
			parindex = rightindex;
		}
		// cout<<"3"<<endl;
		leftindex = (parindex * 2) + 1;
		rightindex = (parindex * 2) + 2;

		parentIndexCost = data[parindex]->getFCost();
		if (leftindex < last) {
			compDel++;
			 leftIndexCost = data[leftindex]->getFCost();
		}else {
			leftIndexCost = 99999;
		}
		if (rightindex < last) {
			compDel++;
			rightIndexCost = data[rightindex]->getFCost();
		}else {
			rightIndexCost = 99999;
		}

		if (leftindex > last) {
			break;
		} else {
			if (rightindex > last) {
				compDel++;
				if (parentIndexCost > leftIndexCost) {
					swap(data[parindex], data[leftindex]);
				}
				break;
			}
		}
	}
}

// Delete - remove the root, and return the value.
Puzzle * Heap::Delete(){
	if (last <= 0) {
		printf("Heap is already empty\n");
		return NULL;
	}else if (last == 1) {
		return data[last];
		last--;
	}

	Puzzle *temp = data[0];

	// Swap node with last, "delete" last
	data[0] = data[last];
	//data[last] = 0;//deleting...
	data[last] = NULL;
	//delete data[last];

	// subtract last
	last--;

	// Fix the heap.
	int parindex=0;
	int leftindex = (parindex * 2) + 1;		// Left child
	int rightindex = (parindex * 2) + 2;	// Right child

	int parentIndexCost = data[parindex]->getFCost();
	int leftIndexCost, rightIndexCost;

	if (leftindex < last) {
		compDel++;
		 leftIndexCost = data[leftindex]->getFCost();
	}else {
		leftIndexCost = 99999;
	}
	if (rightindex < last) {
		compDel++;
		rightIndexCost = data[rightindex]->getFCost();
	}else {
		rightIndexCost = 99999;
	}

	while (parentIndexCost > leftIndexCost || parentIndexCost > rightIndexCost){
		// cout<<"2"<<endl;
		if (rightIndexCost > leftIndexCost) { 	// Follow left.
			//printf("Swap data[%d]=%d with data[%d]=%d \n",leftindex, data[leftindex], parindex, data[parindex]);
			swap(data[leftindex], data[parindex]);
			parindex = leftindex;
		}
		else { 													// Else, follow right.
			//printf("Swap data[%d]=%d with data[%d]=%d \n",rightindex, data[rightindex], parindex, data[parindex]);
			swap(data[rightindex], data[parindex]);
			parindex = rightindex;
		}
		// cout<<"3"<<endl;
		leftindex = (parindex * 2) + 1;
		rightindex = (parindex * 2) + 2;

		parentIndexCost = data[parindex]->getFCost();
		if (leftindex < last) {
			compDel++;
			 leftIndexCost = data[leftindex]->getFCost();
		}else {
			leftIndexCost = 99999;
		}
		if (rightindex < last) {
			compDel++;
			rightIndexCost = data[rightindex]->getFCost();
		}else {
			rightIndexCost = 99999;
		}

		if (leftindex > last) {
			break;
		} else {
			if (rightindex > last) {
				compDel++;
				if (parentIndexCost > leftIndexCost) {
					swap(data[parindex], data[leftindex]);
				}
				break;
			}
		}
	}

	return temp;
}


void HashedVisitedList::InsertString (string strState, int position) {
	if (list[position] == NULL) {
		list[position] = new State();
		list[position]->data = strState;
		list[position]->next = NULL;
	}else {
		State *temp = list[position];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new State();
		temp = temp->next;
		temp->data = strState;
		temp->next = NULL;
	}
}


bool HashedVisitedList::StateExists(string strState, int position) {
	State *temp = list[position];
	State *prev = NULL;
	string tmp;
	while (temp != NULL) {
		tmp = temp->data;
		if (strState.compare(tmp) == 0) {
			return true;
		}
		prev = temp;
		temp = temp->next;
	}
	return false;
}


void HashedVisitedList::InsertString (string strState, int position, int stateDepth) {
	ostringstream tempStr;
	tempStr << stateDepth;
	strState = strState + tempStr.str();
	if (list[position] == NULL) {
		list[position] = new State();
		list[position]->data = strState;
		list[position]->next = NULL;
	}else {
		State *temp = list[position];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new State();
		temp = temp->next;
		temp->data = strState;
		temp->next = NULL;
	}
}


bool HashedVisitedList::StateExists(string strState, int position, int stateDepth) {
	State *temp = list[position];
	State *prev = NULL;
	string tmp;
	string tempStr;
	int length = 0;
	int existingDepth = 0;
	ostringstream newStateDepth;

	while (temp != NULL) {
		tmp = temp->data;
		if (strState.compare(tmp.substr(0,9)) == 0) {
			length = tmp.length();
			istringstream tmpDepth(tmp.substr(9,length-9));
			tmpDepth >> existingDepth;
			if (existingDepth > stateDepth) {
				newStateDepth << stateDepth;
				temp->data = tmp.substr(0,9) + newStateDepth.str();
			}
			return true;
		}
		prev = temp;
		temp = temp->next;
	}
}

void HashedVisitedList::TraverseList() {
	for (int i =0; i < 296; ++i) {
		if (list[i] != NULL) {
			cout<<list[i]->data<<" Pos: "<<i<<endl;
		}
	}
}

int generateHashKey (string strState) {

	// 36 different totals
	//
	// string temp = state->getString();
	int total = 0;
	for (int i = 0; i < 9 ; ++i) {
		total = total + (((i/3)+1) * (strState[i]-48));
	}
	return ((total-54) * 8) + (strState[0]-48);
}



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
	HashedVisitedList *visitedList = new HashedVisitedList();
	// VisitedListQueue *visitedList = new VisitedListQueue();

	Puzzle *p = new Puzzle(initialState, goalState);
	Puzzle *state = p;
	Puzzle *temp;
	bool goalMatch = state->goalMatch();

	numOfStateExpansions = 0;

	int position = generateHashKey(p->getString());
	visitedList->InsertString(p->getString(), position);
	// visitedList->Join(p->getString());

	string tempPath;
	int count = 0;

	while (goalMatch == false) {
		++numOfStateExpansions;

		if (state->canMoveLeft() == true) {
			// temp = state->moveLeft();
			if (state->getPathLength() > 0) {
				tempPath = state->getPath()[state->getPathLength()-1];
				if (tempPath.compare("R") != 0) {
					temp = state->moveLeft();
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }else {
					// 	count++;
					// 	delete temp;
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->Join(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						count++;
						delete temp;
					}

				}else {
					count++;
				}
			}else {
				temp = state->moveLeft();
				// if (visitedList->StateExists(temp) == false) {
				// 	queue->Join(temp);
				// 	visitedList->Join(temp->getString());
				// }
				position = generateHashKey(temp->getString());
				if (visitedList->StateExists(temp->getString(), position) == false) {
					queue->Join(temp);
					visitedList->InsertString(temp->getString(),position);
				}else {
					delete temp;
				}
			}
			// visitedList->Join(temp->getString());
		}
		if (state->canMoveUp() == true) {
				// temp = state->moveUp();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("D") != 0) {
						temp = state->moveUp();
						// if (visitedList->StateExists(temp) == false) {
						// 	queue->Join(temp);
						// 	visitedList->Join(temp->getString());
						// }
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							queue->Join(temp);
							visitedList->InsertString(temp->getString(),position);
						}else {
							count++;
							delete temp;
						}
					}else {
						count++;
					}
				}else {
					temp = state->moveUp();
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->Join(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						delete temp;
					}
				}
				// visitedList->Join(temp->getString());
			}
			if (state->canMoveRight() == true) {
				// temp = state->moveRight();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("L") != 0) {
						temp = state->moveRight();
						// if (visitedList->StateExists(temp) == false) {
						// 	queue->Join(temp);
						// 	visitedList->Join(temp->getString());
						// }
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							queue->Join(temp);
							visitedList->InsertString(temp->getString(),position);
						}else {
							count++;
							delete temp;
						}
					}else {
						count++;
					}
				}else {
					temp = state->moveRight();
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->Join(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						delete temp;
					}
				}
				// visitedList->Join(temp->getString());
			}
			if (state->canMoveDown() == true) {
				// temp = state->moveDown();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("U") != 0) {
						temp = state->moveDown();
						// if (visitedList->StateExists(temp) == false) {
						// 	queue->Join(temp);
						// 	visitedList->Join(temp->getString());
						// }
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							queue->Join(temp);
							visitedList->InsertString(temp->getString(),position);
						}else {
							count++;
							delete temp;
						}
					}else {
						count++;
					}
				}else {
					temp = state->moveDown();
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->Join(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						delete temp;
					}
				}
				// visitedList->Join(temp->getString());
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

    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_No_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

startTime = clock();

	Queue *queue = new Queue();
	 Puzzle *p = new Puzzle(initialState, goalState);
	//  Puzzle *p = new Puzzle("123840765", goalState);
	// Puzzle *temp = p;
	Puzzle *temp;
	bool goalMatch = p->goalMatch();
	numOfStateExpansions = 0;

	maxQLength=0;
	string tempPath;
	int pdsDepth = 1;
	queue->AddToFront(p);

	Puzzle *newP = NULL;

	while (goalMatch == false) {
		if (queue->isEmpty()) {
			//delete queue;
			//queue = new Queue();
			// queue->AddToFront(new Puzzle(initialState, goalState));
			newP = new Puzzle(initialState, goalState);
			queue->AddToFront(newP);
			pdsDepth++;
			cout<<"DEPTH: "<<pdsDepth<<endl;
		}

		temp = queue->Front();
		queue->Leave();
		goalMatch = temp->goalMatch();
		++numOfStateExpansions;

		if (temp->canMoveLeft(pdsDepth) == true) {
			if (temp->getPathLength() > 0) {
				tempPath = temp->getPath()[temp->getPathLength()-1];
				if (tempPath.compare("R") != 0) {
					queue->AddToFront(temp->moveLeft());
				}
			}else {
				queue->AddToFront(temp->moveLeft());
			}
		}
		if (temp->canMoveUp(pdsDepth) == true) {
			if (temp->getPathLength() > 0) {
				tempPath = temp->getPath()[temp->getPathLength()-1];
				if (tempPath.compare("D") != 0) {
					queue->AddToFront(temp->moveUp());
				}
			}else {
				queue->AddToFront(temp->moveUp());
			}
		}
		if (temp->canMoveRight(pdsDepth) == true) {
				if (temp->getPathLength() > 0) {
					tempPath = temp->getPath()[temp->getPathLength()-1];
					if (tempPath.compare("L") != 0) {
						queue->AddToFront(temp->moveRight());
					}
				}else {
					queue->AddToFront(temp->moveRight());
				}
		}
		if (temp->canMoveDown(pdsDepth) == true) {
				if (temp->getPathLength() > 0) {
					tempPath = temp->getPath()[temp->getPathLength()-1];
					if (tempPath.compare("U") != 0) {
						queue->AddToFront(temp->moveDown());
					}
				}else {
					queue->AddToFront(temp->moveDown());
				}
		}
		delete temp;
	}

	cout<<"ENDDD"<<endl;

	maxQLength=queue->MaxLength();
	delete queue;


//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);

	path = temp->getPath();
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

	Queue *queue = new Queue();
	HashedVisitedList *visitedList = new HashedVisitedList();
	// VisitedListQueue *visitedList = new VisitedListQueue();

	Puzzle *p = new Puzzle(initialState, goalState);
	Puzzle *state = NULL;
	Puzzle *temp;
	bool goalMatch = p->goalMatch();

	queue->AddToFront(p);
	numOfStateExpansions = 0;

	int position = generateHashKey(p->getString());
	visitedList->InsertString(p->getString(), position);

	int pdsDepth = 1;

	string tempPath;
	int count = 0;
	Puzzle *newP = NULL;

	while (goalMatch == false) {
	// for (int i = 0; i<10; i++) {
		if (queue->isEmpty()) {
			//delete queue;
			//queue = new Queue();
			// queue->AddToFront(new Puzzle(initialState, goalState));
			state = NULL;
			delete visitedList;
			visitedList = new HashedVisitedList();
			position = generateHashKey(p->getString());
			visitedList->InsertString(p->getString(), position);

			newP = new Puzzle(initialState, goalState);
			queue->AddToFront(newP);
			pdsDepth++;
			cout<<"DEPTH: "<<pdsDepth<<endl;
		}
		// cout<<"1"<<endl;
		state = queue->Front();
		queue->Leave();
		goalMatch = state->goalMatch();

		if (goalMatch == true) {
			break;
		}
		++numOfStateExpansions;
		// cout<<"2"<<endl;

		if (state->canMoveLeft(pdsDepth) == true) {
			// cout<<"3.1"<<endl;
			// temp = state->moveLeft();
			if (state->getPathLength() > 0) {
				tempPath = state->getPath()[state->getPathLength()-1];
				if (tempPath.compare("R") != 0) {
					temp = state->moveLeft();
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }else {
					// 	count++;
					// 	delete temp;
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->AddToFront(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						count++;
						delete temp;
					}

				}else {
					count++;
				}
			}else {
				// cout<<"3.2"<<endl;
				temp = state->moveLeft();
				// if (visitedList->StateExists(temp) == false) {
				// 	queue->Join(temp);
				// 	visitedList->Join(temp->getString());
				// }
				position = generateHashKey(temp->getString());
				if (visitedList->StateExists(temp->getString(), position) == false) {
					queue->AddToFront(temp);
					visitedList->InsertString(temp->getString(),position);
				}else {
					delete temp;
				}
			}
			// visitedList->Join(temp->getString());
		}
		if (state->canMoveUp(pdsDepth) == true) {
			// cout<<"4.1"<<endl;
				// temp = state->moveUp();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("D") != 0) {
						temp = state->moveUp();
						// if (visitedList->StateExists(temp) == false) {
						// 	queue->Join(temp);
						// 	visitedList->Join(temp->getString());
						// }
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							queue->AddToFront(temp);
							visitedList->InsertString(temp->getString(),position);
						}else {
							count++;
							delete temp;
						}
					}else {
						count++;
					}
				}else {
					// cout<<"4.2"<<endl;
					temp = state->moveUp();
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->AddToFront(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						delete temp;
					}
				}
				// visitedList->Join(temp->getString());
			}
			if (state->canMoveRight(pdsDepth) == true) {
				// cout<<"5.1"<<endl;
				// temp = state->moveRight();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("L") != 0) {
						temp = state->moveRight();
						// if (visitedList->StateExists(temp) == false) {
						// 	queue->Join(temp);
						// 	visitedList->Join(temp->getString());
						// }
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							queue->AddToFront(temp);
							visitedList->InsertString(temp->getString(),position);
						}else {
							count++;
							delete temp;
						}
					}else {
						count++;
					}
				}else {
					temp = state->moveRight();
					// cout<<"5.2"<<endl;
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->AddToFront(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						delete temp;
					}
				}
				// visitedList->Join(temp->getString());
			}
			if (state->canMoveDown(pdsDepth) == true) {
				// cout<<"6.1"<<endl;
				// temp = state->moveDown();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("U") != 0) {
						temp = state->moveDown();
						// if (visitedList->StateExists(temp) == false) {
						// 	queue->Join(temp);
						// 	visitedList->Join(temp->getString());
						// }
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							queue->AddToFront(temp);
							visitedList->InsertString(temp->getString(),position);
						}else {
							count++;
							delete temp;
						}
					}else {
						count++;
					}
				}else {
					// cout<<"6.2"<<endl;
					temp = state->moveDown();
					// if (visitedList->StateExists(temp) == false) {
					// 	queue->Join(temp);
					// 	visitedList->Join(temp->getString());
					// }
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						queue->AddToFront(temp);
						visitedList->InsertString(temp->getString(),position);
					}else {
						delete temp;
					}
				}
				// visitedList->Join(temp->getString());
				delete state;
			}
	}

	cout<<"ENDING"<<endl;
	// cout<<count<<endl;
	path = state->getPath();

	maxQLength=queue->MaxLength();
	delete queue;
	delete visitedList;


//***********************************************************************************************************
    actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	// path = "DDRRLLLUUU"; //this is just a dummy path for testing the function

	return path;

}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Heap Array: 3i+1, 3i+2, 3i+3, 3i+4.
//Ask about the actual cost
//Should Heap store the Heuristics + Cost? Or someother value?

//Create a Hash Function: use the tile number at position "0" of the board to generate the hashkey
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){

   string path;
   clock_t startTime;

   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;
	 numOfStateExpansions = 0;


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;
	startTime = clock();
	maxQLength=0;


	Heap *heap = new Heap();
	// VisitedListQueue *visitedList = new VisitedListQueue();
	HashedVisitedList *visitedList = new HashedVisitedList();
	Puzzle *p = new Puzzle(initialState, goalState);
	Puzzle *state = p;
	Puzzle *temp;
	bool goalMatch = state->goalMatch();
	string tempPath;
	// visitedList->Join(p->getString());

	int position = generateHashKey(p->getString());
	visitedList->InsertString(p->getString(),position);
	//visitedList->TraverseList();

int ccount = 0;
 	while (goalMatch == false) {
		++numOfStateExpansions;

		 	if (state->canMoveLeft() == true) {
				temp = state->moveLeft();
				if (state->getPathLength() > 0) {
					tempPath = state->getPath()[state->getPathLength()-1];
					if (tempPath.compare("R") != 0) {
						temp->updateHCost(heuristic);
						temp->updateFCost();
						position = generateHashKey(state->getString());
						if (visitedList->StateExists(state->getString(), position) == false) {
							position = generateHashKey(temp->getString());
							if (visitedList->StateExists(temp->getString(), position) == false) {
								//IF State exists in heap and : 1) if fcost is lower, don't Insert
								// 														: 2) Else Insert into heap
								heap->InsertHeap(temp);
								// visitedList->Join(temp->getString());
								visitedList->InsertString(p->getString(),position);
							}else {
								delete temp;
							}
						}
					}
				}else {
					temp->updateHCost(heuristic);
					temp->updateFCost();
					position = generateHashKey(temp->getString());
					if (visitedList->StateExists(temp->getString(), position) == false) {
						//IF State exists in heap and : 1) if fcost is lower, don't Insert
						// 														: 2) Else Insert into heap
						heap->InsertHeap(temp);
						// visitedList->Join(temp->getString());
						visitedList->InsertString(p->getString(),position);
					}else {
						delete temp;
					}
				}
			}

			if (state->canMoveUp() == true) {
					temp = state->moveUp();
					if (state->getPathLength() > 0) {
						tempPath = state->getPath()[state->getPathLength()-1];
						if (tempPath.compare("D") != 0) {
							temp->updateHCost(heuristic);
							temp->updateFCost();
							if (visitedList->StateExists(state->getString(), position) == false) {
								position = generateHashKey(temp->getString());
								if (visitedList->StateExists(temp->getString(), position) == false) {
									//IF State exists in heap and : 1) if fcost is lower, don't Insert
									// 														: 2) Else Insert into heap
									heap->InsertHeap(temp);
									// visitedList->Join(temp->getString());
									visitedList->InsertString(p->getString(),position);
								}else {
									delete temp;
								}
							}
						}
					}else {
						temp->updateHCost(heuristic);
						temp->updateFCost();
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							//IF State exists in heap and : 1) if fcost is lower, don't Insert
							// 														: 2) Else Insert into heap
							heap->InsertHeap(temp);
							// visitedList->Join(temp->getString());
							visitedList->InsertString(p->getString(),position);
						}else {
							delete temp;
						}
					}
				}
				if (state->canMoveRight() == true) {
					temp = state->moveRight();
					if (state->getPathLength() > 0) {
						tempPath = state->getPath()[state->getPathLength()-1];
						if (tempPath.compare("L") != 0) {
								temp->updateHCost(heuristic);
								temp->updateFCost();
								if (visitedList->StateExists(state->getString(), position) == false) {
									position = generateHashKey(temp->getString());
									if (visitedList->StateExists(temp->getString(), position) == false) {
										//IF State exists in heap and : 1) if fcost is lower, don't Insert
										// 														: 2) Else Insert into heap
										heap->InsertHeap(temp);
										// visitedList->Join(temp->getString());
										visitedList->InsertString(p->getString(),position);
									}else {
										delete temp;
									}
								}
						}
					}else {
						temp->updateHCost(heuristic);
						temp->updateFCost();
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							//IF State exists in heap and : 1) if fcost is lower, don't Insert
							// 														: 2) Else Insert into heap
							heap->InsertHeap(temp);
							// visitedList->Join(temp->getString());
							visitedList->InsertString(p->getString(),position);
						}else {
							delete temp;
						}
					}
				}

				if (state->canMoveDown() == true) {
					temp = state->moveDown();
					if (state->getPathLength() > 0) {
						tempPath = state->getPath()[state->getPathLength()-1];
						if (tempPath.compare("U") != 0) {
							temp->updateHCost(heuristic);
							temp->updateFCost();
							if (visitedList->StateExists(state->getString(), position) == false) {
								position = generateHashKey(temp->getString());
								if (visitedList->StateExists(temp->getString(), position) == false) {
									//IF State exists in heap and : 1) if fcost is lower, don't Insert
									// 														: 2) Else Insert into heap
									heap->InsertHeap(temp);
									// visitedList->Join(temp->getString());
									visitedList->InsertString(p->getString(),position);
								}else {
									delete temp;
								}
							}
						}
					}else {
						temp->updateHCost(heuristic);
						temp->updateFCost();
						position = generateHashKey(temp->getString());
						if (visitedList->StateExists(temp->getString(), position) == false) {
							//IF State exists in heap and : 1) if fcost is lower, don't Insert
							// 														: 2) Else Insert into heap
							heap->InsertHeap(temp);
							// visitedList->Join(temp->getString());
							visitedList->InsertString(p->getString(),position);
						}else {
							delete temp;
						}
					}
				}

				//Deletes the state that is returned from the heap
				//delete state;

				ccount++;
				//std::cout << ccount << '\n';
				state = heap->Delete();
				goalMatch = state->goalMatch();
		// }
	}

	path = state->getPath();

	maxQLength=heap->MaxHeapLenght();
	numOfDeletionsFromMiddleOfHeap = heap->NumOfDeletionsFromHeap();
	delete heap;
	delete visitedList;
	delete p;

	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);

	return path;

}


// if (ccount == 16667) {
// 541781
// 	if (state->canMoveLeft() == true) {
// 		temp = state->moveLeft();
// 		temp->updateHCost(heuristic);
// 		temp->updateFCost();
//
// 		position = generateHashKey(temp->getString());
// 		cout<<"L Out"<<endl;
// 		if (visitedList->StateExists(temp->getString(), position) == false) {
// 			//IF State exists in heap and : 1) if fcost is lower, don't Insert
// 			// 														: 2) Else Insert into heap
// 			cout<<"L In"<<endl;
// 			heap->InsertHeap(temp);
// 			// visitedList->Join(temp->getString());
// 			visitedList->InsertString(p->getString(),position);
// 		}
// 	} else if (state->canMoveUp() == true) {
// 		temp = state->moveUp();
// 		temp->updateHCost(heuristic);
// 		temp->updateFCost();
// 		position = generateHashKey(temp->getString());
// 		cout<<"U Out"<<endl;
// 		if (visitedList->StateExists(temp->getString(), position) == false) {
// 			//IF State exists in heap and : 1) if fcost is lower, don't Insert
// 			// 														: 2) Else Insert into heap
// 			cout<<"U In"<<endl;
// 			heap->InsertHeap(temp);
// 			// visitedList->Join(temp->getString());
// 			visitedList->InsertString(p->getString(),position);
// 		}
// 	} else if (state->canMoveRight() == true) {
// 		temp = state->moveRight();
// 		temp->updateHCost(heuristic);
// 		temp->updateFCost();
// 		position = generateHashKey(temp->getString());
// 		cout<<"R Out"<<endl;
// 		cout<<position<<endl;
// 		cout<<temp->getString()<<endl;
// 		if (visitedList->StateExists(temp->getString(), position) == false) {
// 			//IF State exists in heap and : 1) if fcost is lower, don't Insert
// 			// 														: 2) Else Insert into heap
// 			cout<<"R In"<<endl;
// 			heap->InsertHeap(temp);
// 			// visitedList->Join(temp->getString());
// 			visitedList->InsertString(p->getString(),position);
// 		}
// 		cout<<"R DOne"<<endl;
// 	} else if (state->canMoveDown() == true) {
// 		temp = state->moveDown();
// 		temp->updateHCost(heuristic);
// 		temp->updateFCost();
// 		position = generateHashKey(temp->getString());
// 		cout<<"D Out"<<endl;
// 		if (visitedList->StateExists(temp->getString(), position) == false) {
// 			//IF State exists in heap and : 1) if fcost is lower, don't Insert
// 			// 														: 2) Else Insert into heap
// 			cout<<"D In"<<endl;
// 			heap->InsertHeap(temp);
// 			// visitedList->Join(temp->getString());
// 			visitedList->InsertString(p->getString(),position);
// 		}
// 	}
// 	break;
// }else {
