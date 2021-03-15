#include <stdexcept>
#include "Complex.h"
#include <string>

Complex::Complex() {
    this->Re = 0;
    this->Im = 0;
}

Complex::Complex(double Re, double Im) {
    this->Re = Re;
    this->Im = Im;
}

void Complex::setComplex(double Re, double Im) {
    this->Re = Re;
    this->Im = Im;
}

Complex Complex::operator+(const Complex &Z) {

    Complex result;

    result.setComplex(Re + Z.Re, Im + Z.Im);

    return result;
}

Complex Complex::operator-(const Complex &Z) {

    Complex result;

    result.setComplex(Re - Z.Re, Im - Z.Im);

    return result;
}

bool operator==(const Complex & Z1, const Complex & Z2) {
    if (Z1.Re == Z2.Re && Z1.Im == Z2.Im) return true;
    return false;
}

Complex Complex::operator*(const Complex &Z) {
    Complex result;

    result.setComplex(Re * Z.Re - Im * Z.Im, Re * Z.Im + Im * Z.Re);

    return result;
}

Complex Complex::operator/(const Complex &Z) {
    if (Z.Re == 0 && Z.Im == 0) throw std::invalid_argument("[Error] Division by zero!");
    Complex result;

    result.setComplex((Re * Z.Re + Im * Z.Im) / (Z.Re * Z.Re + Z.Im * Z.Im),
               (Z.Re * Im - Re * Z.Im) / (Z.Re * Z.Re + Z.Im * Z.Im));

    return result;
}

std::ostream & operator<<(std::ostream & os, const Complex &Z) {
    if (Z.Re == 0 && Z.Im != 0){
        if (Z.Im == 1){
            os << "("  << "i)";
            return os;
        } else if (Z.Im == -1){
            os << "("  << "-i)";
            return os;
        }
        os << "(" << Z.Im << "i)";
        return os;
    }

    if (Z.Re != 0 && Z.Im == 0) {
        os << "(" << Z.Re << ")";
        return os;
    }

    os << "(" << Z.Re;
    if (Z.Im < 0) {
        if (Z.Im == -1){
            os << "-i)";
            return os;
        }
        os  << Z.Im << "i)";
        return os;
    } else {
        if (Z.Im == 1){
            os << "+i)";
            return os;
        }
        os << '+' << Z.Im << "i)";
        return os;
    }
}

std::istream &operator>>(std::istream &is, Complex & Z) {

    double number;
    char characters[5];

    is >> characters[0] >> characters[1] >> characters[2];
    if (characters[0] == '(') { //! (i) (-i) (-4i)
        if (characters[1] == '-'){
            if (characters[2] == 'i') {
                is >> characters[3];
                if (characters[3] == ')') {
                    Z.Re = 0;
                    Z.Im = -1;
                    return is;
                }
            }
        } else if (characters[1] == 'i') {
            if (characters[2] == ')') {
                Z.Re = 0;
                Z.Im = 1;
                return is;
            }
        }
    }

    for (int i = 4; i >= 0; i--) {
        if (characters[i] != NULL) {
            is.putback(characters[i]);
            characters[i] = NULL;
        }
    }

    is >> characters[0] >> number >> characters[1];


    if (characters[0] == '(' && characters[1] == ')') { //! (2)
        Z.Re = number;
        return is;
    }

    if (characters[0] == '(' && characters[1] == 'i') { //! (2i)
        is >> characters[2];
        if (characters[2] == ')') {
            Z.Im = number;
            return is;
        }
        is.putback(characters[2]);
    }

    if (characters[0] == '(' && (characters[1] == '+' || characters[1] == '-')) { //! (2+i)
        is >> characters[2];
        if (characters[2] == 'i'){
            Z.Re = number;
            if (characters[1] == '+') {
                Z.Im = 1;
            } else {
                Z.Im = -1;
            }
            return is;
        }
        is.putback(characters[2]);
    }

    if (characters[0] == '(' && (characters[1] == '+' || characters[1] == '-')) { //! (2+3i)
        double imag;
        is >> imag >> characters[3] >> characters[4];
        if (characters[3] == 'i' && characters[4] == ')') {
            Z.Re = number;
            if (characters[1] == '+') {
                Z.Im = imag;
            } else if (characters[1] == '-') {
                Z.Im = -imag;
            }

            return is;
        }
    }

    throw std::invalid_argument("[Error] Complex syntax error!");

}

double Complex::getReal() {
    return Re;
}

double Complex::getImag() {
    return Im;
}



