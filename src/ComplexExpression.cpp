#include "ComplexExpression.h"

ComplexExpression::ComplexExpression() {
    z1 = Complex();
    z2 = Complex();
    op = NULL;
}

ComplexExpression::ComplexExpression(Complex z1, Complex z2, char op) {
    this->z1 = z1;
    this->z2 = z2;
    this->op = op;
}

bool operator==(const ComplexExpression &ce1, const ComplexExpression & ce2) {
    if (ce1.z1 == ce2.z1 && ce1.z2 == ce2.z2 && ce1.op == ce2.op) return true;
    return false;
}

std::ostream & operator<<(std::ostream & os, const ComplexExpression & ce) {

    os << ce.z1 << ce.op << ce.z2;

    if (os.fail()) {
        return os;
    }
    return os;
}

const Complex &ComplexExpression::getZ1() const {
    return z1;
}

void ComplexExpression::setZ1(const Complex &z1) {
    ComplexExpression::z1 = z1;
}

const Complex &ComplexExpression::getZ2() const {
    return z2;
}

void ComplexExpression::setZ2(const Complex &z2) {
    ComplexExpression::z2 = z2;
}

char ComplexExpression::getOp() const {
    return op;
}

void ComplexExpression::setOp(char op) {
    ComplexExpression::op = op;
}

std::istream &operator>>(std::istream &is, ComplexExpression &ce) {
    Complex z1, z2;
    char op;

    try {
        is >> z1;
        if (is.fail()) return is;

        is >> op;
        if (is.fail()) return is;

        is >> z2;
        if (is.fail()) return is;
    } catch (std::exception e) {
        is.clear();
        return is;
    }

    ce.setOp(op);
    ce.setZ1(z1);
    ce.setZ2(z2);

    return is;
}

Complex ComplexExpression::calculateExpression() {
    Complex result;

    switch (op) {
        case '+': result = z1 + z2; break;
        case '-': result = z1 - z2; break;
        case '*': result = z1 * z2; break;
        case '/': result = z1 / z2; break;
    }
    return result;
}
