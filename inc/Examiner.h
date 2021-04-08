#include <string>
#include "ComplexExpression.h"
#include <fstream>

#ifndef COMPLEX_EXAMINER_H
#define COMPLEX_EXAMINER_H

class Examiner {
private:
    int score = 0;
    int tasks = 0;

public:
    Examiner();
    Examiner(std::string fileName);
};

#endif //COMPLEX_EXAMINER_H
