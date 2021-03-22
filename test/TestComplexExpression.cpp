#include "gtest/gtest.h"
#include "ComplexExpression.h"

TEST (Test, emptyConstructor) {
    ComplexExpression ce;
    Complex z1;
    EXPECT_EQ(ce, ComplexExpression(z1, z1, NULL));
}

TEST (Test, constructorAndSetters) {
    int plus;
    ComplexExpression ce1(Complex(2, 1), Complex(2, 2), '+');
    ComplexExpression ce2;
    ce2.setZ1(Complex(2, 1));
    ce2.setZ2(Complex(2, 2));
    ce2.setOp('+');

    EXPECT_EQ(ce1, ce2);
}

TEST (Test, getComplexExpressionFromStream) {
    std::stringstream ss;
    ComplexExpression ce;
    ComplexExpression result(Complex(2, 3), Complex(2, 9), '+');

    ss << "(2+3i)+(2+9i)";
    ss >> ce;

    ASSERT_EQ(result, ce);
}

TEST (Test, AddCalculateExpression) {
    ComplexExpression ce(Complex(2.33, 1.78), Complex(1.67, 0.22), '+');
    Complex result(4, 2);
    ASSERT_EQ(result, ce.calculateExpression());
}

TEST (Test, SubtractCalculateExpression) {
    ComplexExpression ce(Complex(4, 0), Complex(-7, 1), '-');
    Complex result(11, -1);
    ASSERT_EQ(result, ce.calculateExpression());
}

TEST (Test, MultiplicationCalculateExpression) {
    ComplexExpression ce(Complex(2, 3), Complex(1, 1), '*');
    Complex result(-1, 5);
    ASSERT_EQ(result, ce.calculateExpression());
}

TEST (Test, DivisionCalculateExpression) {
    ComplexExpression ce(Complex(4, 4), Complex(1, 1), '/');
    Complex result(4, 0);
    ASSERT_EQ(result, ce.calculateExpression());
}

TEST (Test, ThrowSyntaxError) {
    ComplexExpression result(Complex(), Complex(), EOF);
    ComplexExpression ce;
    std::stringstream ss;

    ss << "2+3i)+(2+9i)";
    ss >> ce;

    ASSERT_EQ(result.getOp(), EOF);

}