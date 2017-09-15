//
//  main.cpp
//  Created by Kevin Du on 2017-05-18.
//  Copyright © 2017 Kevin Du. All rights reserved.
//

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void initX(long long length, long long *polyX) {
    long long inputTemp;
    for (long long i = 0; i < length; ++i) {
        cin >> inputTemp;
        polyX[i] = inputTemp;
    }
}

void initY(long long length, long long *polyY) {
    long long inputTemp;
    for (long long i = 0; i < length; ++i) {
        cin >> inputTemp;
        polyY[i] = inputTemp;
    }
}

void initR(long long length, long long *polyR) {
    for (long long i = 0; i < 2*length-1; ++i) {
        polyR[i] = 0;
    }
}

void eraseXYR(long long length, long long *polyX, long long *polyY, long long *polyR){
    for (long long i = 0; i < length; ++i) {
        polyX[i] = 0;
        polyY[i] = 0;
    }
    for (long long i = 0; i < 2*length-1; ++i) {
        polyR[i] = 0;
    }
}

void printXYR(long long length, long long *polyX, long long *polyY, long long *polyR){
    cout << "POLY X :" << endl;
    for (long long i =0; i < length; ++i) {
        cout << "The " << i << "th polyX is: " << polyX[i] << endl;
    }
    cout << "POLY Y :" << endl;
    for (long long i =0; i < length; ++i) {
        cout << "The " << i << "th polyY is: " << polyY[i] << endl;
    }
    cout << "POLY R :" << endl;
    for (long long i = 0; i < 2*length-1; ++i) {
        cout << "The " << i << "th polyR is: "<< polyR[i] <<endl;
    }
}


void poly2Power(long long *polyR, const long long *polyX, const long long *polyY, long long length){
    long long polyTemp1[length];
    long long polyTemp2[length];
    long long half = length / 2;
    
    for (long long i=0; i < length*2; ++i) { // initialize polyR
        polyR[i] = 0;
    }
    
    if (length == 1){
        polyR[0] = polyX[0] * polyY[0];
    }
    else if (length == 2) {
        long long temp1 = polyX[0] * polyY[0];
        long long temp2 = polyX[1] * polyY[1];
        long long temp3 = (polyX[0] + polyX[1]) * (polyY[0] + polyY[1]);
        polyR[0] = temp1;
        polyR[2] = temp2;
        polyR[1] = temp3 - temp1 - temp2;
    }
    else {
        
        for ( long long i = 0 ; i < half ; i++ ) { //a+b; c+d
            long long a = polyX[i];
            long long b = polyX[half+i];
            long long c = polyY[i];
            long long d = polyY[half+i];
            polyTemp1[i] = a + b;
            polyTemp2[i] = c + d;
        }
        
        for (long long i = 0 ; i < half ; i++) {
            polyTemp1[i+half] = 0;
            polyTemp2[i+half] = 0;
        }
        
        poly2Power(polyR + half, polyTemp1, polyTemp2, half); // (a+b) * (c+d)
        poly2Power(polyTemp1, polyX, polyY, half); // bd
        poly2Power(polyTemp2, polyX + half, polyY + half, half); // ac
        
        for (long long i = 0 ; i < length ; i++){
            long long temp1 = polyTemp1[i];
            long long temp2 = polyTemp2[i];
            polyR[i] = polyR[i] + temp1;
            polyR[i+half] = polyR[i+half] - temp1 - temp2;
            polyR[i+length] = polyR[i+length] + temp2;
        }
    }
}

void polyAll(long long *polyR, long long *polyX, long long *polyY, long long length){
    long long temp = 1;
    while (length & (length - 1)){
        while (temp < length) { temp = temp*2;}
        long long len = temp;
        while (len >= ++length) {
            polyX[length - 1] = 0;
            polyY[length - 1] = 0;
        } length = length - 1;
    }
    poly2Power(polyR, polyX, polyY, length);
}

void printR(long long length, const long long *polyR) {
    for (long long i=0; i < 2*length-2; ++i) {
        cout << polyR[i] << " ";
    }
    cout << polyR[2*length-2]<<endl;
}

int main(int argc, const char * argv[]) {
    
    long long tempLength;
    cin >> tempLength;
    if(tempLength > 100000 || tempLength < 0) {
        cerr << "ERROR: Input length > 100000 OR < 0" <<endl;
        return 0;
    }
    
    long long polyX[100000]; // polynomial X
    long long polyY[100000]; // polynomial Y
    long long polyR[200001]; // polynomial result of (X * Y)
    
    initX(tempLength + 1, polyX);
    initY(tempLength + 1, polyY);
    initR(tempLength + 1, polyR);
    polyAll(polyR, polyX, polyY, tempLength+1);
 //   printXYR(tempLength+1, polyX, polyY, polyR);
    printR(tempLength+1, polyR);
    eraseXYR(tempLength+1, polyX, polyY, polyR);
    return 0;
}
