// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

//Define a Node class for each array, containing a pointer to Data and the values
//of specific fields in Data that need to be used later
class Node {
public:
	Data* p2Data;
	unsigned int value2;
	string value4;

};
	
void insertionSort(list<Data*> &l);
void countingSort(list<Data*> &l);
void CreateArray(list<Data*> &l);
void CreateArray2(list<Data*> &l);
bool comparison(const Node &prev, const Node &next);
bool comparison2(const Node &prev, const Node &next);
Data* digits[200][900000] = {};
Node arr[1200000] = {};
int numCount[1000] = {};
int i = 0;

void sortDataList(list<Data *> &l, int field) {
	if (field == 1) {
		insertionSort(l);
	}
	else if (field == 2) {
		CreateArray(l);
		//it was found that stable_sort (mergesort) worked faster than any of the algorithms
		//that I thought up of
		stable_sort(arr, arr + l.size(), comparison);
		//filling up the list from the array
		list<Data*>::iterator itr = l.begin();
		i = 0;
		for (itr ; itr != l.end() ; itr++) {
			*(itr) = arr[i].p2Data;
			i++;
		}
	}
	else if (field == 3) {
		countingSort(l);
	}
	else if (field == 4) {
		CreateArray2(l);
		//qsort was found to be faster than stable_sort, but the stability of this is questionable
		sort(arr, arr + l.size(), comparison2);
		list<Data*>::iterator itr = l.begin();
		i = 0;
		for (itr; itr != l.end() ; itr++) {
			(*itr) = arr[i].p2Data;
			i++;
		}
	}
	else { cout << "Wrong field" << endl; }
}

//An insertion sort is best for almost sorted fields 
void insertionSort(list<Data*> &l)  {
	list<Data*>::iterator itr;
	for(itr = l.begin(); itr != l.end(); itr++) {
		//basic swap left/right function given by std
		while(itr != l.begin() && ((*itr)->val1 < (*prev(itr))->val1)) {
			iter_swap(itr,prev(itr));
			itr--;
		}
	}
}


// A counting sort is best if the range of input data is not that big compared to the number of data points
void countingSort(list<Data*> &l) {
	//starts from the end of the list and iterates until the beginning
	//This was found to work since starting from the beginning yielded backwards results
	int temp = 0;
	list<Data*>::iterator itr = l.end();
	while (itr != l.begin()) {
		itr--;
		temp = (*itr)->val3;
		numCount[temp]++;
		digits[temp][numCount[temp]] = (*itr);		
	}	
	itr = l.begin();
	int k = 0;	
	//resorting the list by populating it with data from the created Digits matrix
	while (itr != l.end()) {		
		while (numCount[k]) {			
			(*itr) = digits[k][numCount[k]];
			itr++;
			numCount[k]--;
		}
	k++;
	}
}

//creating an array of type Node, filling it with the Data points in the original linked list
//as well as its components	
void CreateArray(list<Data*> &l) {
	
	list<Data*>::const_iterator itr = l.begin();
	for (itr ; itr != l.end(); itr++) {
		arr[i].p2Data = (*itr);
		arr[i].value2 = (*itr)->val2;
		i++;
	}
}
//creating an array in the same way as above, except for the fourth data field
//I found this way to be faster than filling out one node array and calling it from it twice
void CreateArray2(list<Data*> &l) {
	
	list<Data*>::const_iterator itr = l.begin();
	for (itr ; itr != l.end(); itr++) {
		arr[i].p2Data = (*itr);
		arr[i].value4 = (*itr)->val4;
		i++;
	}
}


	
//two comparison functions written for the array created above
//using one comparison for each was found to be faster
//this is used for the stable_sort function parameter in stdlib
bool comparison(const Node &prev, const Node &next) {
  return prev.value2 < next.value2;
}
 		

bool comparison2(const Node &prev, const Node &next) {
	return prev.value4 < next.value4;
}

	
	
	
	
	
	
	
	