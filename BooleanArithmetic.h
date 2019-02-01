//
// Created by becky on 10/01/2019.
//

#ifndef TEMPMLPNN_BOOLEANARITHMETIC_H
#define TEMPMLPNN_BOOLEANARITHMETIC_H

#include <cmath>
#include <cstdlib>
#include <GL/freeglut.h>
#include "ImageHeader.h"

class BooleanArithmetic {
    public:
        GLdouble DotMultiply(ImageHeader imgHdr, GLdouble ** targetOne, GLdouble ** targetTwo);
        GLdouble BoxMullerTransform();
        GLdouble UniformRandom();
        GLdouble SigmoidFunction(GLdouble targetInput);
};


#endif //TEMPMLPNN_BOOLEANARITHMETIC_H
