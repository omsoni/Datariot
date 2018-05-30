//
//  Soni_Problem4.cpp
//  Assignment1
//
//  Created by Om Soni on 5/28/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <limits>
#include "Assignment1B.h"
using namespace std;

int factorial(int n); //function prototype
/*
 * The main driver function for problem 4. Function prompts user to enter the choice to test a specific part of problem.
 * Then it uses a function to excute that choice.
*/
int main() {
    char choice ;
    do {
        cout << "Enter 'a' for Factorial, 'b' for Mathematical Constant, 'c' for Mathemtical Constant with Power (Enter z to exit): ";
        cin >> choice ;
        switch(choice) {
            case 'z': exit(0);
            case 'a': factorialRun();
                    cout << "\n\n";
                    break;
            case 'b': mathConstant();
                    cout << "\n\n";
                    break;
            case 'c': mathConstantWithPower() ;
                    break ;
            default: cout << "\nPlease make a valid choice." << endl;
                    continue;
        }
    } while (true);
}
/*
 * This function implements the functionality for part b of Problem 4.
 */
void mathConstant() {
    double e =1.0;
    unsigned int terms;
    // Sentinal controlled Iteration
    do { //Prompt for valid user input unless user choses to exit
        cout << "Please enter number of terms for desired accuracy (Enter 0 to exit): ";
        cin >> terms ;
        if (terms > 0)
            break ;
        else
            cout << "\nPlease enter a +ve number for terms.";
     } while (true);
    
    //Iterate for number of terms
    for (unsigned int i=1; i <= terms; i++) {
        e+=(double)1/factorial(i);
        //cout << "e=" << e << "for i=" << i ;
    }
    cout << "\nMathematical constant value for terms " << terms << " is " <<e <<endl;
}

/*
 * This function implements the functionality for part c of Problem 4.
 * Code uses factorial function in Factorial.cpp and pow from standard cmath library for calculating the mathematical term.
 */
void mathConstantWithPower() {
    double e =1;
    int terms=0, power=0;
    
    do { //Prompt for power(x) input for terms unless user choses to exit
        cout << "Please enter a +ve number for power term (Enter 0 to exit): ";
        cin >> power ;
        if (power > 0)
            break ;
    } while (true);
    do { //Prompt for valid user input for terms unless user choses to exit
        cout << "Please enter the number of terms for desired accuracy (Enter 0 to exit): ";
        cin >> terms ;
        if (terms > 0)
            break ;
    } while (true);
    
    //Iterate for number of terms
    for (unsigned int i=1; i <= terms; i++) {
        e+=(double)(pow(power, i)/factorial(i));
    }
    cout << "\nMathematical constant value for x=" << power << " with " << terms << " terms " << "is " <<e << endl;
}

/*
 * This function implements the functionality for part a of Problem 4.
 * The code for factorial(n)  is in Factorial.cpp.
 * function uses recurrsion to calculate the factorial
 */
void factorialRun()
{
    int n;
    cout << "Enter a positive integer to computer factorial: ";
    cin >> n;
    int fact = factorial(n);
    cout << "\nFactorial of " << n << " is " << fact << endl;
}

