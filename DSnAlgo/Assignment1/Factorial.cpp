//
//  Factorial.cpp
//  Assignment1
//
//  Created by Om Soni on 5/28/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//

int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}
