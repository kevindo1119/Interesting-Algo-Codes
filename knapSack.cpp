//
//  main.cpp
//  341-a3-1
//
//  Created by Kevin Du on 2017-06-23.
//  Copyright © 2017 Kevin Du. All rights reserved.
//


#include <iostream>
#include <string>
#include <vector>
using namespace std;

int returnMax(int a, int b){
	if (a > b){
		return a;
	} else {
		return b;
	}
}

void initKnapsack(int &lineNum, int &storageSize, 
				vector<pair <int, int>> &fileSystem) {
	int temp1;
	int temp2;
	int fileWeight;
	int fileScore;
	cin >> temp1;
	cin >> temp2;

	if (! (temp1 >= 1 && temp1 <= 2000)) {
		cerr << "ERROR: input lineNum is " << temp1 << 
		" , which is out of bound!" <<endl;
	}
	if (! (temp2 >= 1 && temp2 <= 2000)) {
		cerr << "ERROR: input storageSize is " << temp2 << 
		" , which is out of bound!" <<endl;
	}
	
	lineNum = temp1;
	storageSize = temp2;
	
	while (!cin.eof()) { // cin the input fileWeight and fileScore till EOF
			cin >> fileWeight;
			cin >> fileScore;
			if (!(0 <= fileWeight && fileWeight <= 10000)) {
				cerr << "ERROR: input fileWeight is " << fileWeight <<
				" , which is out of bound!" <<endl;
				break;
			}
			if (!(0 <= fileScore && fileScore <= 10000)) {
				cerr << "ERROR: input fileScore is " << fileScore <<
				" , which is out of bound!" <<endl;
				break;
			}
			fileSystem.push_back(make_pair(fileWeight,fileScore));
	}
	fileSystem.pop_back();
}

void printFileSystem(int lineNum, int storageSize,vector<pair <int, int>> &fileSystem) {
	for(int i=0; i < fileSystem.size(); ++i) {
		cout <<"The " << i << "th element in file system is " <<
			"{ fileWeight: " << fileSystem[i].first << ", fileScore: " 
			<< fileSystem[i].second << " }" << endl; 
	}
	cout << "lineNum is " << lineNum << endl;
	cout << "storageSize is " << storageSize << endl;
}

void printRes(const int x, const int y, const vector<int> myVect);

void knapSackMain(int &lineNum, int &storageSize,
                                vector<pair <int, int>> &fileSystem) {
	int kMatrix[lineNum+1][storageSize+1];
	// Use bottom-up impl
	int i = 0;
	int j = 0;
	int pickedCounter = 0;
        vector<int> pickedItem;
        int right = storageSize;
        int bottum = lineNum;
	
	for (int t = 0; t <storageSize + 1; ++t) {
		kMatrix[0][t] = 0;
	}
	
	for (int s = 0; s <lineNum + 1; ++s) {
                kMatrix[s][0] = 0;
        }

	for (i = 1; i < lineNum+1; ++i) {
		for (j = 1; j < storageSize+1; ++ j) {
			if ( i == 0 || j == 0) {
				kMatrix[i][j] = 0;
			} else if (fileSystem[i-1].first <= j) {
				int temp1 = fileSystem[i-1].second;
				int temp2 = kMatrix[i-1][j-fileSystem[i-1].first];
				int temp3 = kMatrix[i-1][j];
				kMatrix[i][j] = returnMax(temp1+temp2, temp3);
			} else {
				kMatrix[i][j] = kMatrix[i-1][j];
			}
		}
	}

	while (bottum >= 1) {
		if (kMatrix[bottum][right] == kMatrix[bottum-1][right]) {
			--bottum;
		} else {
			pickedItem.push_back(bottum+1);
			right = right - fileSystem[bottum-1].first;
			++pickedCounter;
			--bottum; 
		}
	}

	if (kMatrix[bottum][right] > 0) {
		++pickedCounter;
		pickedItem.push_back(bottum+1);
	}
	
	printRes(kMatrix[lineNum][storageSize], pickedCounter, pickedItem);
		
}

void printRes(const int x, const int y, const vector<int> myVect) {
	cout << x << ' ' << y << endl;
	for(auto i: myVect){
                cout << i-1 << ' ';
        }
	cout << endl;
}

int main (){
	int lineNum;
	int storageSize;
	vector <pair <int, int>> fileSystem;
	initKnapsack(lineNum, storageSize, fileSystem);
//	printFileSystem(lineNum, storageSize, fileSystem);
	knapSackMain(lineNum, storageSize, fileSystem);
	return 0;
}

