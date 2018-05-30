//
//  InvoiceMain.cpp
//  Assignment1
//  This is the main driver program for Problem 3. Driver uses Invoice class declared in Invoice.h file
//  It indirectly uses Price class also declared in Invoice.h
//  Created by Om Soni on 5/28/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include "Invoice.h"

using namespace std;

int main() {
    
    string part, partdesc ;
    int quantity, price ;
    //Prompt user to enter a valid part number
    do {
        cout << "Please enter the part number (Enter 0 to exit): ";
        cin >> part ;
        if (part.length() != 8) {
            cout << "Valid part numbers are 8 characters\n";
            continue ;
        }
        else
            break;
    } while (true);
    
    cin.ignore();
    //Prompt user to enter a valid part description
    do {
        cout << "Please enter the part description: ";
        getline(cin, partdesc);
        if (partdesc.length() > 9 )
            break;
        else
            cout << "Part Description should be atleast 20 characters" <<endl;
    }  while(true);
        
    //Prompt user to enter a valid part price
    do {
        try {
            cout << "Please enter the part price (divisor=100): ";
            cin >> price ;
            if (price > 0)
                break;
            else {
                cout << "Part price can't be negative. Setting to 0." <<endl;
                price = 0;
                break;
            }
        }catch (exception ex) {
            cout << "Enter a number for price." <<endl;
            continue;
        }
    }  while(true);
        
    //Prompt user to enter a valid part quantity
    do {
        cout << "Please enter the part quantity: ";
        cin >> quantity ;
        if (quantity > 1)
            break;
        else
            cout << "Part quantity can't be negative" <<endl;
    }  while(true);
    
    Invoice invoice1(part, partdesc, quantity, price) ;
    /*
    //No argument constructor
    Invoice invoice1;
    invoice1.setPartNumber(part);
    invoice1.setPartDesc(partdesc);
    invoice1.setPrice(price);
    invoice1.setQuantity(quantity); */
    cout << "Invoice:" + invoice1.toString() <<endl ;
    
    return 0;
}
