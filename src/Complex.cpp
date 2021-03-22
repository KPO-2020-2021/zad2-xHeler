#include "Complex.h"
#include <stdexcept>
#include <string>
#include <sstream>

void putBackNumberToStream(std::istream &is, double number);
bool isCharacterEqualsGet(std::istream &is, char character);


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
    if (std::abs(Z1.Re - Z2.Re) < PRECISION_RIFFLE &&
        std::abs(Z1.Im - Z2.Im) < PRECISION_RIFFLE) return true;
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

    if (!isCharacterEqualsGet(is, '(')){
        std::string bin;
        is >> bin;
        throw std::invalid_argument("[Error] Syntax error.");
    }
    if (isReadableOnlyImaginary(is, Z)) return is;
    if (isReadableOneSegment(is, Z)) return is;
    if (isReadableComplexShort(is, Z)) return is;
    if (isReadableFullComplex(is, Z)) return is;

    std::string bin;
    is >> bin;
    throw std::invalid_argument("[Error] Syntax error.");
}

bool isReadableOnlyImaginary(std::istream &is, Complex &Z) {
    //!  (i) (-i)
    char tmp;
    char op;

    if(is.peek() == 'i') {
        is >> tmp;
        if (!isCharacterEqualsGet(is, ')')) return false;
        Z.Re = 0;
        Z.Im = 1;
        return true;
    }

    if (is.peek() == '-') {
        is >> op;
        if (is.peek() == 'i') {
            is >> tmp;
            if (!isCharacterEqualsGet(is, ')')) return false;
            Z.Re = 0;
            Z.Im = -1;
            return true;
        }
        is.putback(op);
        return false;
    }
    return false;
}

bool isReadableOneSegment(std::istream &is, Complex &Z) {
    //!  (-4) (-4i) (9) (9i)
    char tmp;
    double number;

    if(is.peek() == '-') {
        is >> number;
        if (is.peek() == 'i') {
            is >> tmp;
            if (!isCharacterEqualsGet(is, ')')) return false;
            Z.Re = 0;
            Z.Im = number;
            return true;
        } else if (is.peek() == ')') {
            is >> tmp;
            Z.Re = number;
            Z.Im = 0;
            return true;
        }
        putBackNumberToStream(is, number);
        return false;
    }


    if (is.peek() > 47 && is.peek() < 58) {

        is >> number;
        if (is.peek() == 'i') {
            is >> tmp;
            if (!isCharacterEqualsGet(is, ')')) return false;
            Z.Re = 0;
            Z.Im = number;
            return true;
        } else if (is.peek() == ')') {
            is >> tmp;
            Z.Re = number;
            Z.Im = 0;
            return true;
        }
        putBackNumberToStream(is, number);
        return false;
    }

    return false;
}

bool isReadableComplexShort(std::istream &is, Complex &Z) {
    //!  (4+i) (2-i)
    char op;
    char tmp;
    double number;

    if(is.peek() == 45 || is.peek() > 47 && is.peek() < 58) {
        is >> number;
        is >> op;
        if (op == '+' && is.peek() == 'i') {
            is >> tmp;
            if (!isCharacterEqualsGet(is, ')')) return false;
            Z.Re = number;
            Z.Im = 1;
            return true;
        } else if (op == '-' && is.peek() == 'i') {
            is >> tmp;
            if (!isCharacterEqualsGet(is, ')')) return false;
            Z.Re = number;
            Z.Im = -1;
            return true;
        }
        is.putback(op);
        putBackNumberToStream(is, number);
        return false;
    }
    return false;
}

double Complex::getReal() {
    return Re;
}

double Complex::getImag() {
    return Im;
}

bool isReadableFullComplex(std::istream &is, Complex &Z) {
    //!  (4+3i) (4-5i)

    is >> Z.Re;
    if (is.fail()) return false;

    is >> Z.Im;
    if (is.fail()) return false;

    if (!isCharacterEqualsGet(is, 'i')) return false;
    if (!isCharacterEqualsGet(is, ')')) return false;

    return true;
}

void putBackNumberToStream(std::istream &is, double number) {
    if ((number - (int) number) == 0) {
        int tmp = number;
        std::string str = std::to_string(tmp);
        for (int i = str.length() - 1; i >= 0; i--) {
            is.putback(str[i]);
        }
    } else {
        std::stringstream str;
        str.precision(2);
        str << std::fixed << number;
        int lastIndex = str.str().length();

        for (int i = lastIndex - 1; i >= 0; i--){
            if (lastIndex - 1 == i && str.str()[i] != '0'){
                is.putback(str.str()[i]);
            } else if (lastIndex - 2 == i && str.str()[i] != '0'){
                is.putback(str.str()[i]);
            } else if (lastIndex - 2 > i) {
                is.putback(str.str()[i]);
            }
        }
    }
}

bool isCharacterEqualsGet(std::istream &is, char character) {
    char tmp;
    is >> tmp;
    if (is.fail()) return false;
    if (tmp != character) {
        is.putback(tmp);
        return false;
    }
    return true;
}



