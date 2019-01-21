//
// Created by becky on 10/01/2019.
//

#include "BooleanArithmetic.h"

GLdouble BooleanArithmetic::DotMultiply(ImageHeader imgHdr, GLdouble **targetOne, GLdouble **targetTwo)
{
    GLdouble tempResult;

    for(int ii = 0; ii < imgHdr.imgWidth; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            tempResult += targetOne[ii][jj] * targetTwo[ii][jj];
        }
    }

    return tempResult;
}