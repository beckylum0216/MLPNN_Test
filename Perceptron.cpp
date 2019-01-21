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
    theLayer = new Layer();
    layerSize = 1;
    imgLbl = new GLdouble();
}

Perceptron::Perceptron(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize, int neuronSize)
{
    std::cout << "num of images: " << imgHdr.maxImages << std::endl;
    theLayer = new Layer[layerSize];
    for(int ii = 0; ii < layerSize; ii += 1)
    {
        theLayer[ii].ResizeLayer(imgHdr, lblHdr, neuronSize);
    }
    imgLbl = new GLdouble[lblHdr.maxLabels]();

    sigmoidLayer = new Layer(imgHdr, lblHdr, neuronSize);

}

Perceptron::~Perceptron()
{
    std::cout << "deleting perceptron... " << std::endl;
    delete[] theLayer;
    delete[] imgLbl;
}

Layer * Perceptron::GetLayer()
{
    return theLayer;
}



void Perceptron::InitLayer(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize,int neuronSize)
{
    std::cout << "Running initialisation..." << std::endl;

    for(int hh = 0; hh < layerSize; hh += 1)
    {
        for(int ii = 0; ii < neuronSize; ii += 1)
        {
            std::cout << "Initialising layer: " << ii << std::endl;
            for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
            {
                for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
                {
                    theLayer[hh].GetNeurons()[ii].inputArr[jj][kk] = 0.00;
                    int totalPixels = imgHdr.imgWidth * imgHdr.imgHeight;
                    theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] = std::rand()% totalPixels/(double)(totalPixels);
                }
            }

            theLayer[hh].GetNeurons()[ii].bias = 0.00;
            theLayer[hh].GetNeurons()[ii].output = 0.00;
            theLayer[hh].GetNeurons()[ii].sigmoidOutput = 0.00;
        }
    }


    for(int aa = 0; aa < lblHdr.maxLabels; aa += 1)
    {
        imgLbl[aa] = 0.00;
    }

    std::cout << "Finished running initialisation..." << std::endl;
}

void Perceptron::InitSigmoidLayer(ImageHeader imgHdr, int neuronSize)
{
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                sigmoidLayer->GetNeurons()[ii].inputArr[jj][kk] = 0.00;
                sigmoidLayer->GetNeurons()[ii].weightOne[jj][kk] = std::rand()%imgHdr.maxImages/(double)(imgHdr.maxImages);
            }
        }

        sigmoidLayer->GetNeurons()[ii].bias = 0.00;
        sigmoidLayer->GetNeurons()[ii].output = 0.00;
        sigmoidLayer->GetNeurons()[ii].sigmoidOutput = 0.00;
    }
}

void Perceptron::ResizePerceptron(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize, int neuronSize)
{
    std::cout << "Running Resize perceptron..." << std::endl;
    for(int ii = 0; ii < layerSize; ii += 1)
    {
        theLayer[ii].ResizeLayer(imgHdr, lblHdr, neuronSize);
    }


    std::cout << "Finished resizing perceptron..." << std::endl;
}

GLdouble  Perceptron::SigmoidFunction(GLdouble targetInput)
{
    GLdouble  tempResult;

    tempResult = 1 - (1 / (1 + std::exp(targetInput)));

    return tempResult;
}


// reading the pictures as black or white
void Perceptron::SetLayer(GLdouble** imgInput, ImageHeader imgHdr, int layerSize, int neuronSize)
{

    for(int hh = 0; hh < layerSize; hh += 1)
    {
        for(int ii = 0; ii < neuronSize; ii += 1)
        {
            for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
            {
                for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
                {
                    if(imgInput[jj][kk]/255 > 0)
                    {
                        theLayer[hh].GetNeurons()[ii].inputArr[jj][kk] = 0;
                    }
                    else
                    {
                        theLayer[hh].GetNeurons()[ii].inputArr[jj][kk] = 1;
                    }

                }
            }
        }
    }

}

void Perceptron::SetLabel(GLdouble *lblInput, LabelHeader lblHdr)
{
    for(int ii = 0; ii < lblHdr.maxLabels; ii += 1)
    {
        imgLbl[ii] = lblInput[ii];
    }
}

//
// https://becominghuman.ai/neural-network-xor-application-and-fundamentals-6b1d539941ed
void Perceptron::ForwardPropagation(ImageHeader imgHdr, int layerSize, int neuronSize)
{
    BooleanArithmetic ba;

    for (int hh = 0; hh < layerSize; hh += 1)
    {
        for(int ii = 0; ii < neuronSize; ii += 1)
        {
            GLdouble tempSigmoid;

            for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
            {
                for(int kk = 0; kk < imgHdr.imgHeight; kk +=1)
                {
                    GLdouble tempOutput;


                    tempOutput += ba.DotMultiply(imgHdr, theLayer[hh].GetNeurons()[ii].inputArr, theLayer[hh].GetNeurons()[ii].weightOne);

                    std::cout << "Neuron output: " << tempOutput << std::endl;

                    theLayer[hh].GetNeurons()[ii].output = tempOutput;


                }
            }

            tempSigmoid = SigmoidFunction(theLayer[hh].GetNeurons()[ii].output);
            theLayer[hh].GetNeurons()[ii].sigmoidOutput = tempSigmoid;

            std::cout << "layer output: " << theLayer->GetNeurons()[ii].sigmoidOutput << std::endl;
        }

    }
}

void Perceptron::CalculateOutput(ImageHeader imgHdr, int layerSize, int neuronSize)
{
    for(int hh = 0; hh < layerSize; hh += 1)
    {
        for(int ii = 0; ii < neuronSize; ii += 1)
        {
            for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
            {
                for(int kk = 0; kk < imgHdr.imgHeight; kk +=1)
                {
                    sigmoidLayer->GetNeurons()[ii].output += theLayer[hh].GetNeurons()[ii].sigmoidOutput * sigmoidLayer->GetNeurons()[ii].weightOne[jj][kk];
                }
            }

            std::cout << "sigmoidLayer Output: " << sigmoidLayer->GetNeurons()[ii].output<< std::endl;
            sigmoidLayer->GetNeurons()[ii].sigmoidOutput = SigmoidFunction(sigmoidLayer->GetNeurons()[ii].output);
        }
    }
}

// calculate the std error
// this is suspect error is huge!!!
GLdouble Perceptron::CalculateError(ImageHeader imgHdr, int targetLayer, int targetNeuron)
{
    GLdouble  tempError;

    tempError = targetNeuron - GetLayerPrediction(targetLayer, targetNeuron);
    //tempError /= 10;

    return tempError;
}

void Perceptron::UpdateNeuronWeights(ImageHeader imgHdr, int targetLayer,int targetNeuron, GLdouble stdError, GLdouble learningRate)
{
    for(int ii = 0; ii < imgHdr.imgWidth; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            theLayer[targetLayer].GetNeurons()[targetNeuron].weightOne[ii][jj] *= learningRate * theLayer[targetLayer].GetNeurons()[targetNeuron].inputArr[ii][jj] * stdError;
            sigmoidLayer->GetNeurons()[targetNeuron].weightOne[ii][jj] *= theLayer[targetLayer].GetNeurons()[targetNeuron].sigmoidOutput * learningRate * stdError;
        }
    }
}

std::vector <GLdouble> Perceptron::SetTargetOutput(int targetIndex, int outputSize)
{
    std::vector <GLdouble> outputVector;

    for(int ii = 0 ; ii < outputSize; ii += 1)
    {
        if(targetIndex == ii)
        {
            outputVector.push_back(1);
        }
        else
        {
            outputVector.push_back(0);
        }
    }

    return outputVector;
}

int Perceptron::GetLayerPrediction(int layersize, int neuronSize)
{
    GLdouble maxOutput = 0.00;
    int layerPrediction = 0;

    for (int ii = 0; ii < neuronSize; ii += 1)
    {
        if(sigmoidLayer->GetNeurons()[ii].output > maxOutput)
        {
            maxOutput = sigmoidLayer->GetNeurons()[ii].output;
            layerPrediction = ii;
        }
    }

    return layerPrediction;
}