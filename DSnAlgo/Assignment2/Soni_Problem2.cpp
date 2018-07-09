//
//  Soni_Problem2
//  Assignment2
//  This is the main driver function to run the maize solver.
//  It uses the classes defined in the header file Maize.h
//  Program prompts the user to enter the file name with maize defination.
//  It then reads the file and create a object representation of class Maize.
//  Maize consist of Points class for each location in the maize.
//  Path class defines a traverable path. These path were identified by MaizeRunner and
//  added to stack. The program direction and keep tracks of paths it has already traversed.
//  It also checks left and right at junctions and if the exit is there, it will take that exit.
//  Algothrim is created by me and it is not one of standard algorithm out there.
//  Created by Om Soni on 6/10/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <iomanip>
#include "Maize.h"
using namespace std;

Maize createMaize(string  file);
//Driver to run the maize solver
int main() {
    string file ;
    cout << "Enter the filename with maize (Enter 0 to exit):";
    cin >> file ;
    Maize maize = createMaize(file);
    MaizeRunner maizeRunner = MaizeRunner(maize);
    cout << "Done creating object representation of maize.......\n";
    maizeRunner.enterMaize();
    cout << "Solving maize.......\n";
    maizeRunner.run();
    return 1;
}

Maize createMaize(string  file) {
    ifstream iFile(file);
    cout << "Reading file " << file << "....." << endl;
    if (! iFile)
    {
        cout << "Error opening input file." ;
        exit(1);
    }
    long maize_rows = std::count(std::istreambuf_iterator<char>(iFile),
               std::istreambuf_iterator<char>(), '\n') + 1; //+1 for end of file
    iFile.clear();
    iFile.seekg(0, ios::beg);
    
    unsigned char temp;
    std::string line;
    vector<unsigned char> vec;
    //do it once to get the size of the maize
    // and declare right size arrays
    std::getline(iFile, line);
    std::istringstream iss(line);
    while(iss >> temp)
        vec.push_back(temp);
    
    long maize_columns = vec.size() ;
    cout << "Successfully created the maize from file. Maize size: " << maize_rows << " X " << maize_columns << ".\n";
    cout << "Creating object repreosentation of maize.......\n\n\n";
    char **maizeArr = new char*[maize_rows] ;
    for (int i=0; i < maize_rows; i++)
        maizeArr[i] = new char(maize_columns);
  
    cout << "  ";
    for (int i=0; i < maize_columns; i++)
        cout << setfill(' ') << setw(2) << i ;
    cout << "\n";
    
    int i=0,j=0 ;

    do {
        j=0;
        std::istringstream iss(line);
        cout << setfill(' ') << setw(2) << i << ' ' << line << "\n";
        while(iss >> temp) {
            maizeArr[i][j] = temp ;
            j++;
        //loop through maize row
        }
        //cout << " The maizeArr for " << i  << " and " << j << " is " << maizeArr[i][j] ;
        i++;
    } while (std::getline(iFile, line));
    cout << "\n\n";
    Maize maize = Maize(maizeArr, maize_rows, maize_columns);
    return maize;
}
