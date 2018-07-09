//
//  Complex.h
//  Assignment2.4
//
//  Created by Om Soni on 6/10/18.
//  Copyright © 2018 Om Soni. All rights reserved.
//
#ifndef Complex_h
#define Complex_h

class Complex {
private:
    double realPart;
    double imginaryPart;
public:
    Complex(double real, double imaginary) :realPart(real), imginaryPart(imaginary){};
    
    Complex operator + (const Complex &complex2)
    {
        return Complex(realPart + complex2.realPart, imginaryPart +complex2.imginaryPart);
        
    };
    
    Complex operator - (const Complex &complex2)
    {
        return Complex(realPart - complex2.realPart, imginaryPart - complex2.imginaryPart);

    };
    
    std::string to_string(){
        return std::to_string(realPart) + " + " + std::to_string(imginaryPart) + "i";
    }
    
    friend std::ostream& operator << (std::ostream &strm, Complex &complex) {
        return  strm << "( " << complex.to_string()  << " ) " ;
    }
};
#endif /* Complex_h */
