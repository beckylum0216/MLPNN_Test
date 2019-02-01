//
// Created by becky on 23/12/2018.
//

#include <math.h>
#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include "Perceptron.h"
#include "ImageHeader.h"
#include "BooleanArithmetic.h"

Perceptron::Perceptron()
{
    hiddenLayer = new Layer[1]();
	sigmoidLayer = new Layer[1]();
	hiddenCount = 1;
	neuronCount = 1;

}

Perceptron::Perceptron(ImageHeader imgHdr, LabelHeader lblHdr, int hiddenSize, ImageHeader outputHdr, int neuronSize)
{
    std::cout << "num of images: " << imgHdr.maxImages << std::endl;
    hiddenLayer = new Layer(imgHdr, lblHdr, hiddenSize, hiddenSize);

    sigmoidLayer = new Layer(outputHdr, lblHdr,hiddenSize, neuronSize);

	imageHdr = imgHdr;
	labelHdr = lblHdr;
	outputHeader = outputHdr;
	hiddenCount = hiddenSize;
	neuronCount = neuronSize;
}

Perceptron::~Perceptron()
{
    std::cout << "deleting perceptron... " << std::endl;
    delete[] hiddenLayer;
    delete[] sigmoidLayer;
}

Layer * Perceptron::GetHiddenLayer()
{
    return hiddenLayer;
}

Layer * Perceptron::GetSigmoidLayer()
{
	return sigmoidLayer;
}

int Perceptron::GetHiddenCount()
{
	return hiddenCount;
}

int Perceptron::GetNeuronCount()
{
	return neuronCount;
}

ImageHeader Perceptron::GetImgHdr()
{
	return imageHdr;
}

ImageHeader Perceptron::GetOutputHdr()
{
	return outputHeader;
}






