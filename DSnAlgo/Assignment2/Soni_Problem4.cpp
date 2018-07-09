//  main.cpp
//  Assignment2.4
//
//  Created by Om Soni on 6/10/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//
#include <iostream>
#include <ctime>
#include "Complex.h"
using namespace std;

double rand_double( double low, double high );
int main(int argc, const char * argv[]) {

    srand (10);
    double realpart1 = rand_double(10,50);
    double imginarypart1 = rand_double(10,50);
    srand (100);
    double realpart2 = rand_double(30,50);
    double imginarypart2 = rand_double(80,100);
    Complex complex1 = Complex(realpart1,imginarypart1);
    Complex complex2 = Complex(realpart2,imginarypart2);
    Complex complex3 = complex1 + complex2;
    cout << "First Number: " << complex1 << "\n" ;
    cout << "Second Number: " << complex2 << "\n" ;
    cout << "Addition of Two:" << complex3 << "\n" ;
    Complex complex4 = complex2 - complex1 ;
    cout << "Substraction of Two:" << complex4 << "\n" ;
    return 0;
}
double rand_double( double low, double high ) {
    return ( ( double )rand() * ( high - low ) ) / ( double )RAND_MAX + low;
}
