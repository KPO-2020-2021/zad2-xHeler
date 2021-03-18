#include <Complex.h>
#include <iostream>

#ifndef COMPLEX_COMPLEXEXPRESSION_H
#define COMPLEX_COMPLEXEXPRESSION_H

class ComplexExpression {
private:
    Complex z1;
    Complex z2;
    char op;

public:
    ComplexExpression();
    ComplexExpression(Complex z1, Complex z2, char op);

    Complex calculateExpression();

    friend bool operator==(const ComplexExpression & ce1, const ComplexExpression &ce2);
    friend std::ostream & operator<<(std::ostream & os, const ComplexExpression & ce);
    friend std::istream & operator>>(std::istream & is, ComplexExpression & ce);

    const Complex &getZ1() const;
    void setZ1(const Complex &z1);
    const Complex &getZ2() const;
    void setZ2(const Complex &z2);
    char getOp() const;
    void setOp(char op);
};

#endif //COMPLEX_COMPLEXEXPRESSION_H
