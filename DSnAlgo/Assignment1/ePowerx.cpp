//
//  Contant-e.cpp
//  Assignment1
//
//  Created by Om Soni on 5/28/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int factorial(int n); //function prototype
int main1() {
    
    float e =1;
    int accuracy, power;
    
    do {
        cout << "Please enter a +ve number for power term (Enter 0 to exit): ";
        cin >> power ;
        if (power > 0)
            break ;
    } while (true);
    do {
        cout << "Please enter the number of terms for desired accuracy (Enter 0 to exit): ";
        cin >> accuracy ;
        if (accuracy > 0)
                break ;
    } while (true);

    for (unsigned int i=1; i <= accuracy; i++) {
        e+=pow(power, i)/factorial(i);
    }
    return 0;
}
