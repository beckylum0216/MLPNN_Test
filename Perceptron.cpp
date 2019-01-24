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
    theLayer = new Layer[1]();
	sigmoidLayer = new Layer[1]();
	imgLbl = new GLdouble[1]();
	layerCount = 1;
	neuronCount = 1;

}

Perceptron::Perceptron(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize, int neuronSize)
{
    std::cout << "num of images: " << imgHdr.maxImages << std::endl;
    theLayer = new Layer[layerSize];
    
	for(int ii = 0; ii < layerSize; ii += 1)
    {
		for (int jj = 0; jj < neuronSize; jj += 1)
		{
			theLayer[ii].ResizeLayer(imgHdr, lblHdr, neuronSize);
		}
        
    }
	
    imgLbl = new GLdouble[lblHdr.maxLabels]();

    sigmoidLayer = new Layer(imgHdr, lblHdr, neuronSize);

	imageHdr = imgHdr;
	labelHdr = lblHdr;

	layerCount = layerSize;
	neuronCount = neuronSize;
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

int Perceptron::GetLayerCount()
{
	return layerCount;
}

int Perceptron::GetNeuronCount()
{
	return neuronCount;
}

void Perceptron::InitLayer_Random()
{
    std::cout << "Running initialisation..." << std::endl;

    for(int hh = 0; hh < layerCount; hh += 1)
    {
        for(int ii = 0; ii < neuronCount; ii += 1)
        {
            std::cout << "Initialising layer: " << ii << std::endl;
            for(int jj = 0; jj < imageHdr.imgWidth; jj += 1)
            {
                for(int kk = 0; kk < imageHdr.imgHeight; kk += 1)
                {
                    theLayer[hh].GetNeurons()[ii].inputArr[jj][kk] = 0.00;
                    int totalPixels = imageHdr.imgWidth * imageHdr.imgHeight;
                    theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] = (std::rand()% totalPixels)/(double)(totalPixels);
					std::cout << "Initial weight: " << theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] << std::endl;
                }
            }

            theLayer[hh].GetNeurons()[ii].bias = 0.00;
            theLayer[hh].GetNeurons()[ii].output = 0.00;
            theLayer[hh].GetNeurons()[ii].sigmoidOutput = 0.00;
        }
    }

    for(int aa = 0; aa < labelHdr.maxLabels; aa += 1)
    {
        imgLbl[aa] = 0.00;
    }

    std::cout << "Finished running initialisation..." << std::endl;
}


//https://medium.com/usf-msds/deep-learning-best-practices-1-weight-initialization-14e5c0295b94
void Perceptron::InitLayer_KaiMing(int neuronSize)
{
	GLdouble inputSize = (GLdouble)imageHdr.imgWidth * (GLdouble)imageHdr.imgHeight * (GLdouble)imageHdr.maxImages;
	GLdouble popSize = ((GLdouble)inputSize + (GLdouble)neuronCount);

	for (int hh = 0; hh < layerCount; hh += 1)
	{
		for (int ii = 0; ii < neuronCount; ii += 1)
		{
			std::cout << "Initialising layer: " << ii << std::endl;
			for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
			{
				for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
				{
					theLayer[hh].GetNeurons()[ii].inputArr[jj][kk] = 0.00;
					//int totalPixels = imageHdr.imgWidth * imageHdr.imgHeight;

					GLdouble constKaiMing = (GLdouble) std::sqrt(2 / ((GLdouble) popSize - 1.0));
					GLdouble tempResult = BoxMullerTransform() * constKaiMing;
					theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] = tempResult;
					std::cout.precision(16);
					//std::cout << "Initial weight: " << tempResult << std::endl;
				}
			}

			theLayer[hh].GetNeurons()[ii].bias = 0.00;
			theLayer[hh].GetNeurons()[ii].output = 0.00;
			theLayer[hh].GetNeurons()[ii].sigmoidOutput = 0.00;
		}
	}

	for (int aa = 0; aa < labelHdr.maxLabels; aa += 1)
	{
		imgLbl[aa] = 0.00;
	}

	std::cout << "Finished running initialisation..." << std::endl;
}

void Perceptron::InitLayer_Xavier()
{
	GLdouble inputSize = (GLdouble)imageHdr.imgWidth * (GLdouble)imageHdr.imgHeight * (GLdouble) imageHdr.maxImages;
	GLdouble popSize = ((GLdouble)inputSize + (GLdouble)neuronCount) / 2;

	for (int hh = 0; hh < layerCount; hh += 1)
	{
		for (int ii = 0; ii < neuronCount; ii += 1)
		{
			std::cout << "Initialising layer: " << ii << std::endl;
			for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
			{
				for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
				{
					theLayer[hh].GetNeurons()[ii].inputArr[jj][kk] = 0.00;
					//int totalPixels = imageHdr.imgWidth * imageHdr.imgHeight;

					GLdouble constXavier = 1 / popSize;
					GLdouble tempResult = BoxMullerTransform() * constXavier;
					theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] = tempResult;
					std::cout.precision(16);
					//std::cout << "Initial weight: " << tempResult << std::endl;
				}
			}

			theLayer[hh].GetNeurons()[ii].bias = 0.00;
			theLayer[hh].GetNeurons()[ii].output = 0.00;
			theLayer[hh].GetNeurons()[ii].sigmoidOutput = 0.00;
		}
	}
}


// ftp://ftp.taygeta.com/pub/c/boxmuller.c
GLdouble Perceptron::BoxMullerTransform()
{
	bool flag = false;
	GLdouble boxMuller = 0.00;
	GLdouble boxResultX = 0.00;
	GLdouble boxResultY = 0.00;
	
	if (flag) {
		flag = false;

		//std::cout << "Box Muller Y: " << boxResultY << std::endl;

		return boxResultY;
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
		flag = true;

		//std::cout << "Box Muller X: " << boxResultX << std::endl;
		
		return boxResultX;
	}
}

GLdouble Perceptron::UniformRandom()
{
	// this is suspect
	GLdouble tempResult = ((GLdouble)std::rand()) / ((GLdouble)(RAND_MAX + 1));
	//std::cout << "Uniform Random: " << tempResult << std::endl;
	
	return tempResult;
}

void Perceptron::InitSigmoidLayer_Xavier(ImageHeader imgHdr, int neuronSize)
{

	GLdouble inputSize = (GLdouble)imageHdr.imgWidth * (GLdouble)imageHdr.imgHeight * (GLdouble)imageHdr.maxImages;
	GLdouble popSize = ((GLdouble)inputSize + (GLdouble)neuronCount) / 2;

	
	for (int ii = 0; ii < neuronCount; ii += 1)
	{
		std::cout << "Initialising layer: " << ii << std::endl;
		for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
		{
			for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
			{
				sigmoidLayer->GetNeurons()[ii].inputArr[jj][kk] = 0.00;

				GLdouble constXavier = 1 / popSize;
				GLdouble tempResult = BoxMullerTransform() * constXavier;
				sigmoidLayer->GetNeurons()[ii].weightOne[jj][kk] = tempResult;
				std::cout.precision(16);
				//std::cout << "Initial weight: " << tempResult << std::endl;
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
void Perceptron::SetLayer(GLdouble** imgInput)
{

    for(int hh = 0; hh < layerCount; hh += 1)
    {
        for(int ii = 0; ii < neuronCount; ii += 1)
        {
            for(int jj = 0; jj < imageHdr.imgWidth; jj += 1)
            {
                for(int kk = 0; kk < imageHdr.imgHeight; kk += 1)
                {

					theLayer[hh].GetNeurons()[ii].inputArr[jj][kk] = imgInput[jj][kk];

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
void Perceptron::ForwardPropagation()
{
    BooleanArithmetic ba;

    for (int hh = 0; hh < layerCount; hh += 1)
    {
        for(int ii = 0; ii < neuronCount; ii += 1)
        {
            GLdouble tempSigmoid;
			GLdouble tempOutput = 0.00;

            for(int jj = 0; jj < imageHdr.imgWidth; jj += 1)
            {
                for(int kk = 0; kk < imageHdr.imgHeight; kk +=1)
                {
                    
                    tempOutput += ba.DotMultiply(imageHdr, theLayer[hh].GetNeurons()[ii].inputArr, theLayer[hh].GetNeurons()[ii].weightOne);

                }
            }
			theLayer[hh].GetNeurons()[ii].output = tempOutput;
			//std::cout << "Neuron output: " << tempOutput << std::endl;

            tempSigmoid = SigmoidFunction(theLayer[hh].GetNeurons()[ii].output);
            theLayer[hh].GetNeurons()[ii].sigmoidOutput = tempSigmoid;

            //std::cout << "sigmoid output: " << theLayer->GetNeurons()[ii].sigmoidOutput << std::endl;
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
// this is suspect - error is huge!!!
GLdouble Perceptron::CalculateError(ImageHeader imgHdr, int targetLabel)
{
    GLdouble  tempError;

    tempError = imgLbl[targetLabel] - GetLayerPrediction();

    return tempError;
}

void Perceptron::UpdateNeuronWeights(ImageHeader imgHdr, GLdouble stdError, GLdouble learningRate)
{
	for (int hh = 0; hh < layerCount; hh += 1)
	{
		for (int ii = 0; ii < neuronCount; ii += 1)
		{
			for (int jj = 0; jj < imgHdr.imgWidth; jj += 1)
			{
				for (int kk = 0; kk < imgHdr.imgHeight; kk += 1)
				{
					GLdouble tempSGD = learningRate * theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] * stdError;
					theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] += tempSGD;

					std::cout << "Updated Neuron: " << theLayer[hh].GetNeurons()[ii].weightOne[jj][kk] << std::endl;
					//sigmoidLayer->GetNeurons()[targetNeuron].weightOne[ii][jj] *= theLayer[targetLayer].GetNeurons()[targetNeuron].sigmoidOutput * learningRate * stdError;
				}
				
			}
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

int Perceptron::GetLayerPrediction()
{
    GLdouble maxOutput = 0.0;
    int layerPrediction = 0;

    for (int ii = 0; ii < layerCount; ii += 1)
    {
		for (int jj = 0; jj < theLayer[ii].GetNeuralSize(); jj += 1)
		{
			if (theLayer[ii].GetNeurons()[ii].sigmoidOutput > maxOutput)
			{
				maxOutput = theLayer[ii].GetNeurons()[jj].output;
				layerPrediction = jj;
			}

		}
        
    }

    return layerPrediction;
}