//
// Created by becky on 16/01/2019.
//

#ifndef TEMPMLPNN_CONVOLUTION_H
#define TEMPMLPNN_CONVOLUTION_H

#include <GL/freeglut.h>
#include "ImageHeader.h"


class Convolution {
    public:
        Convolution(ImageHeader imgHdr, int layerSize, int neuronSize);
        ~Convolution();
        GLdouble ** GaussianFilter(GLdouble ** imgInput, ImageHeader imgHdr, int layerSize, int neuronSize);
        GLdouble ** MaxPooling(GLdouble ** imgInput, ImageHeader imgHdr, int layerSize, int neuronSize);
        GLdouble Maxima(GLdouble ** imgInput, ImageHeader imgHdr, int inputX, int inputY);

    private:
        GLdouble ** gaussConvolution;
        GLdouble ** maxPool;
};


#endif //TEMPMLPNN_CONVOLUTION_H
