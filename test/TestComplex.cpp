#include "gtest/gtest.h"
#include "Complex.h"
#include <iostream>
#include <string>

TEST (Test, createEmptyConstructor) {
    EXPECT_EQ(Complex(), Complex(0, 0));
}

TEST (Test, createBasicConstructor) {
    Complex result;
    result.setComplex(1, 2);
    EXPECT_EQ(Complex(1, 2), result);
}

TEST (Test, addTwoComplex) {
    Complex z1(10, 5);
    Complex z2(5, 0);

    EXPECT_EQ(z1 + z2, Complex(15, 5));
}

TEST (Test, substractTwoComplex) {
    Complex z1(5, 1);
    Complex z2(3, 5);

    EXPECT_EQ(z1 - z2, Complex(2, -4));
}

TEST (Test, multiplicationConstansAndComplex) {
    Complex z1(2, 5);
    Complex result;
    result =  (Complex) 5 * z1;
    EXPECT_EQ(result, Complex(10, 25));
}

TEST (Test, multiplicationTwoComplex) {
    Complex z1(2, -5);
    Complex z2(3, 10);
    EXPECT_EQ(z1 * z2, Complex(56, 5));
}


TEST (Test, divisionConstantsAndComplex) {
    Complex z1(30, 30);
    Complex result;
    result = z1 / (Complex) 30;
    EXPECT_EQ(result, Complex(1, 1));
}

TEST (Test, divisionZeroTest) {
    Complex z1(1, 8);
    Complex z2(0, 0);
    EXPECT_THROW(z1 / z2, std::exception);
}

TEST (Test, divisionTwoComplex) {
    Complex z1(1, 8);
    Complex z2(2, 3);
    EXPECT_EQ(z1 / z2, Complex(2, 1));
}

TEST (Test, showInformationAboutComplexNumber) {
    Complex z1(2, 5);
    Complex z2(0, -3);
    Complex z3(-5, 0);
    Complex z4(0, -1);
    Complex z5(3, 1);
    Complex z6(0, 1);
    Complex z7(10, -7);
    std::stringstream os;

    os << z1;
    ASSERT_EQ("(2+5i)", os.str());

    os = std::stringstream();
    os << z2;
    ASSERT_EQ("(-3i)", os.str());

    os = std::stringstream();
    os << z3;
    ASSERT_EQ("(-5)", os.str());

    os = std::stringstream();
    os << z4;
    ASSERT_EQ("(-i)", os.str());

    os = std::stringstream();
    os << z5;
    ASSERT_EQ("(3+i)", os.str());

    os = std::stringstream();
    os << z6;
    ASSERT_EQ("(i)", os.str());

    os = std::stringstream();
    os << z7;
    ASSERT_EQ("(10-7i)", os.str());
}

TEST (Test, getComplexFromCin) {
    Complex z1;
    std::stringstream is;

    is << "(51+55.2i)";
    is >> z1;

    ASSERT_EQ(z1, Complex(51, 55.2));

    is << "(10-5i)";
    is >> z1;

    ASSERT_EQ(z1, Complex(10, -5));

    is << "(-3-1i)";
    is >> z1;

    ASSERT_EQ(z1, Complex(-3, -1));

    is << "(0-1i)";
    is >> z1;

    ASSERT_EQ(z1, Complex(0, -1));

    is << "(1.5+0i)";
    is >> z1;

    ASSERT_EQ(z1, Complex(1.5, 0));
}

TEST (Test, shorterVersionComplex) {
    Complex z1;
    std::stringstream is;

    is << "(-i)";
    is >> z1;
    ASSERT_EQ(z1, Complex(0, -1));
    z1 = Complex();

    is << "(i)";
    is >> z1;
    ASSERT_EQ(z1, Complex(0, 1));
    z1 = Complex();

    is << "(2i)";
    is >> z1;
    ASSERT_EQ(z1, Complex(0, 2));
    z1 = Complex();

    is << "(2)";
    is >> z1;
    ASSERT_EQ(z1, Complex(2, 0));
    z1 = Complex();

    is << "(-4i)";
    is >> z1;
    EXPECT_EQ(z1, Complex(0, -4));
    z1 = Complex();

    is << "(3-i)";
    is >> z1;
    EXPECT_EQ(z1, Complex(3, -1));
    z1 = Complex();
}

TEST (Test, unfamiliarSyntaxErrorComplex) {
    Complex z1;
    std::stringstream is;

    is << "5+6i)";
    EXPECT_THROW(is >> z1, std::exception);
    is = std::stringstream();

    is << "(5+6i";
    EXPECT_THROW(is >> z1, std::exception);
    is = std::stringstream();

    is << "(5+6";
    EXPECT_THROW(is >> z1, std::exception);
    is = std::stringstream();

    is << "(5+6)";
    EXPECT_THROW(is >> z1, std::exception);
    is = std::stringstream();

    is << "(5%6i";
    EXPECT_THROW(is >> z1, std::exception);
    is = std::stringstream();

    is << "(a+6i)";
    EXPECT_THROW(is >> z1, std::exception);
    is = std::stringstream();

}