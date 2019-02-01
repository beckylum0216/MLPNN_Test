//
// Created by becky on 10/01/2019.
//

#include <iostream>
#include "BooleanArithmetic.h"

GLdouble BooleanArithmetic::DotMultiply(ImageHeader imgHdr, GLdouble ** targetOne, GLdouble **targetTwo)
{
    GLdouble tempResult = 0.00;

    for(int ii = 0; ii < imgHdr.imgWidth; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            tempResult += targetOne[ii][jj] * targetTwo[ii][jj];

            std::cout.precision(10);
            //std::cout << "dot Result: " << tempResult << " target1: " << targetOne[ii][jj] << " target2: " << targetTwo[ii][jj] << std::endl;
        }
    }

    return tempResult;
}

// ftp://ftp.taygeta.com/pub/c/boxmuller.c
GLdouble BooleanArithmetic::BoxMullerTransform()
{
    bool flag = false;
    GLdouble boxMuller = 0.00;
    GLdouble boxResultX = 0.00;
    GLdouble boxResultY = 0.00;
    GLdouble boxMullerResult = 0.00;

    if (flag)
    {
        flag = false;

        //std::cout << "Box Muller Y: " << boxResultY << std::endl;
        boxMullerResult = boxResultY;
    }
    else
    {
        GLdouble randomOne;
        GLdouble randomTwo;
        GLdouble weight;
        do
        {
            randomOne = UniformRandom() * 2 - 1;
            randomTwo = UniformRandom() * 2 - 1;

            //std::cout << "Rand 1: " << randomOne << " Rand 2: " << randomTwo << std::endl;

            weight = randomOne * randomOne + randomTwo * randomTwo;
        } while (weight >= 1 || weight == 0);

        boxMuller  = std::sqrt(-2.0 * std::log(weight) / weight);
        boxResultX = randomOne * boxMuller;
        boxResultY = randomTwo * boxMuller;

        //std::cout << "Box Muller X: " << boxResultX << std::endl;

        boxMullerResult = boxResultX;

        flag = true;
    }

    return boxMullerResult;
}

GLdouble BooleanArithmetic::UniformRandom()
{
    // this is suspect
    GLdouble tempResult = ((GLdouble)std::rand()) / ((GLdouble)(RAND_MAX + 1));
    //std::cout << "Uniform Random: " << tempResult << std::endl;

    return tempResult;
}

GLdouble  BooleanArithmetic::SigmoidFunction(GLdouble targetInput)
{
    GLdouble  tempResult;
	// shift by ONE!!!
    tempResult = 1 / (1 + std::exp((-1*targetInput))) ;

    return tempResult;
}