//
//  Soni_Problem3.cpp
//  Assignment2.3
//  The program prompts the users for a number to check if it a pallandrum
//  It concatenates the reminders to create a backwards string representation of number
//  it then converts it into number and compares if it is same as number.
//  Created by Om Soni on 6/5/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

bool checkIfPallandrum(long number);
int main(int argc, const char * argv[]) {
    bool isPallandrum = false ;
    long number ;
    do {
    cout << "Enter a number to check for pallendrum (Enter 0 to exit): " ;
        cin >> number ;
        if (number ==0)
            break;
        isPallandrum = checkIfPallandrum(number);
        if(isPallandrum){
            cout << "Given number is a pallandrum! Try another one.\n";
        } else
             cout << "Given number is NOT a pallandrum! Try another one.\n";
    } while (true);
    return 0;
}

//function to check the number for pallandrum

bool checkIfPallandrum(long number) {
    long quotient, reminder ;
    long temp = number;
    string backwards = "" ;
    do {
        quotient = temp/10;
        reminder = temp % 10;
        temp = quotient;
        backwards += std::to_string(reminder);
        
    } while (quotient > 10);
    backwards += std::to_string(quotient);
    long number1 = stoll(backwards, nullptr, 10);
    cout << "Backwards, the number is : " << backwards << endl ;
    if (number == number1)
        return true ;
    else return false;
}
