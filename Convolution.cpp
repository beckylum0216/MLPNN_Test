//
// Created by becky on 16/01/2019.
//

#include "Convolution.h"

Convolution::Convolution(ImageHeader imgHdr, int layerSize, int neuronSize)
{


    gaussConvolution = new GLdouble * [imgHdr.imgWidth]();
    maxPool = new GLdouble * [imgHdr.imgWidth]();
    for (int ii = 0; ii < imgHdr.imgHeight; ii +=1)
    {
        gaussConvolution[ii] = new GLdouble [imgHdr.imgHeight]();
        maxPool[ii] = new GLdouble[imgHdr.imgHeight]();
    }

    // initialise result arrays
    for(int ii = 0; ii < imgHdr.imgWidth; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            gaussConvolution[ii][jj] = 0.00;
            maxPool[ii][jj] = 0.00;
        }
    }
}

Convolution::~Convolution()
{
    delete[] gaussConvolution;
}

GLdouble ** Convolution::GaussianFilter(GLdouble **imgInput, ImageHeader imgHdr, int layerSize, int neuronSize)
{
    GLdouble kernelGauss[3][3] = {{0.0625, 0.125, 0.0625}, {0.125, 0.5, 0.125}, {0.0625, 0.125, 0.0625}};

    for(int ii = 1; ii < imgHdr.imgWidth; ii += 1)
    {
        for(int jj = 1; jj < imgHdr.imgHeight; jj += 1)
        {
            for(int kk = 0; kk < 3; kk += 1)
            {
                for (int ll = 0; ll < 3; ll += 1)
                {
                    gaussConvolution[ii][jj] = imgInput[ii][jj] * kernelGauss[kk][ll];
                }
            }
        }
    }

    return gaussConvolution;
}


GLdouble ** Convolution::MaxPooling(GLdouble **imgInput, ImageHeader imgHdr, int layerSize, int neuronSize)
{
    for(int ii = 1; ii < imgHdr.imgWidth; ii += 1)
    {
        for(int jj = 1; jj < imgHdr.imgHeight; jj += 1)
        {
            maxPool[ii][jj] = Maxima(imgInput, imgHdr, ii, jj);

        }
    }

    return maxPool;
}

GLdouble Convolution::Maxima(GLdouble **imgInput, ImageHeader imgHdr, int inputX, int inputY)
{
    GLdouble  maxResult = 0.00;

    if(imgInput[inputX][inputY] > maxResult)
    {
        maxResult = imgInput[inputX][inputY];
    }

    return maxResult;
}