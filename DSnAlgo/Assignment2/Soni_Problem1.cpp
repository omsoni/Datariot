//
//  Soni_Problem1.cpp
//  Assignment2
//  Created by Om Soni on 6/05/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
using namespace std;

/*
 * The main driver function for problem 1. Function prompts student answer single digit multiplication question
 * if they answer incorrectly, it will prompt them to try again. User can exit the program by entering 0.
*/
int main() {
    int number1, number2, answer;
    do {
        //Keep numbers singal digit for elementary school kids
        number1 = rand() % 10;
        number2 = rand() % 10 ;
        // incase one of the numbers is 0 get another pair
        if ((number1 * number2) == 0)
            continue;
        cout << "How much is " << number1 << " times " << number2 << " ? (Enter 0 to exit):" << endl ;
        //loop if answer is wrong, prompt more attempts
        do {
            cin >> answer ;
            //if exit condition
            if (answer == 0)
                exit(EXIT_SUCCESS) ;
            //if answer is correct. give another question (exit inner loop)
            else if (answer == (number1 * number2)) {
                cout << "Very Good !! Let us try another one!" << endl ;
                break ;
            }
            //if answer is incorrect. prompt for more attempts.
            else {
                cout << "That is not correct. Try again." << endl ;
                cout << "How much is " << number1 << " times " << number2 << " ? (Enter 0 to exit)" << endl ;
            }
        } while(true);
    } while (true);
}
