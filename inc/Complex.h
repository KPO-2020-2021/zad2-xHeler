#include <iostream>
#include <string>

#ifndef COMPLEX_COMPLEX_H
#define COMPLEX_COMPLEX_H

class Complex {
private:
    double Re;
    double Im;

public:
    Complex();
    Complex(double Re, double Im = 0);

    Complex operator+ (const Complex & Z);
    Complex operator-(const Complex & Z);
    Complex operator*(const Complex & Z);
    Complex operator/(const Complex & Z);
    friend bool operator==(const Complex & Z1, const Complex & Z2);
    friend std::ostream & operator<<(std::ostream & os, const Complex & Z);
    friend std::istream & operator>>(std::istream & is, Complex & Z);

    void setComplex(double Re, double Im);
    double getReal();
    double getImag();
};

#endif //COMPLEX_COMPLEX_H
