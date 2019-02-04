//
// Created by becky on 24/12/2018.
//

#include <vector>
#include <iostream>
#include "Layer.h"

Layer::Layer()
{
    neuralLayer = new Neuron[1]();
    imgLbl = new GLdouble [1]();
    neuralSize = 1;
    sumOfMSE = 0.00;
	imageHdr.maxImages = 1;
	imageHdr.imgWidth = 1;
	imageHdr.imgHeight = 1;
	labelHdr.magicNumber = 0;
	labelHdr.maxLabels = 1;

}

Layer::Layer(const Layer &rhsLayer)
{
    this->neuralLayer = rhsLayer.neuralLayer;
	this->neuralSize = rhsLayer.neuralSize;
}

Layer::Layer(ImageHeader imgHdr, LabelHeader lblHdr, int labelSize, int neuronSize)
{
    std::cout << "running overloaded layer" << std::endl;

    neuralLayer = new Neuron[neuronSize]();
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        neuralLayer[ii].ResizeNeuron(imgHdr);
        std::cout << "Neuron Resize index: " << ii << std::endl;
    }
    
	imageHdr = imgHdr;
	labelHdr = lblHdr;

	std::cout << "declaring imglbl array..." << std::endl;
    imgLbl = new GLdouble [lblHdr.maxLabels]();

	neuralSize = neuronSize;
   
    sumOfMSE = 0.00;

    std::cout << "layer created..." << std::endl;
}

Layer::~Layer()
{
    std::cout << "deleting layers..." << std::endl;
    delete [] neuralLayer;
    delete[] imgLbl;
}

Layer& Layer::operator=(Layer rhsVar)
{
    this->Swap(rhsVar);
    return *this;
}

void Layer::Swap(Layer &rhsVar)
{
    std::swap(this->neuralLayer, rhsVar.neuralLayer);
}

Neuron * Layer::GetNeurons()
{
    return neuralLayer;
}

GLdouble * Layer::GetImgLbl()
{
    return imgLbl;
}

int Layer::GetNeuralSize()
{
	return neuralSize;
}

void Layer::ResizeLayer(ImageHeader imgHdr, LabelHeader lblHdr,int labelSize, int neuronSize)
{
    std::cout << "Running layer resize..." << std::endl;

    // initialise temp neuron
    Neuron * tempNeuron;
    tempNeuron = new Neuron[neuronSize]();

    // resizing temp neuron
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        std::cout << "Neuron index: " << ii << std::endl;
        tempNeuron[ii].ResizeNeuron(imgHdr);
    }

	// copying old neurons to temp neurons
    for(int ii = 0; ii < neuralSize; ii += 1)
    {
        for(int jj = 0; jj < this->neuralLayer[ii].sizeX; jj += 1)
        {
            for(int kk = 0; kk < this->neuralLayer[ii].sizeY; kk += 1)
            {
                tempNeuron[ii].inputArray[jj][kk] = this->neuralLayer[ii].inputArray[jj][kk];
                tempNeuron[ii].weightOne[jj][kk] = this->neuralLayer[ii].weightOne[jj][kk];
            }
        }

    }

    GLdouble * tempLabel;
    tempLabel = new GLdouble[labelHdr.maxLabels]();

    for(int ii = 0; ii < labelHdr.maxLabels; ii += 1)
    {
        tempLabel[ii] = this->imgLbl[ii];
    }

    neuralSize = neuronSize;
    imageHdr = imgHdr;
	

    std::cout << "Deleting the layer" << std::endl;
    
	delete [] neuralLayer; // offending code ?
    delete [] imgLbl;

    std::cout << "Finish deleting the layer" << std::endl;

	//neuralLayer = tempNeuron; //did not work before
    neuralLayer = new Neuron[neuronSize]; // here is the offending declaration causes destructors to run
	imgLbl = new GLdouble[labelHdr.maxLabels];

    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        neuralLayer[ii].ResizeNeuron(imgHdr);
    }

	// performing deep copy - copying temp data into resized layer
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                neuralLayer[ii].inputArray[jj][kk] = tempNeuron[ii].inputArray[jj][kk];
                neuralLayer[ii].weightOne[jj][kk] = tempNeuron[ii].weightOne[jj][kk];
            }
        }

    }

    for(int ii = 0; ii < labelHdr.maxLabels; ii += 1)
    {
        imgLbl[ii] = tempLabel[ii];
    }
	
    std::cout << "deleting tempNeurons... " << std::endl;

    delete[] tempNeuron;
    delete[] tempLabel;

    std::cout << "Finished resizing layer..." << std::endl;
}

void Layer::InitLayer_Random()
{
    std::cout << "Running initialisation..." << std::endl;

    for(int ii = 0; ii < neuralSize; ii += 1)
    {
        std::cout << "Initialising layer: " << ii << std::endl;
        for(int jj = 0; jj < imageHdr.imgWidth; jj += 1)
        {
            for(int kk = 0; kk < imageHdr.imgHeight; kk += 1)
            {
                neuralLayer[ii].inputArray[jj][kk] = 0.00;
                int totalPixels = imageHdr.imgWidth * imageHdr.imgHeight;
                neuralLayer[ii].weightOne[jj][kk] = (std::rand()% totalPixels)/(double)(totalPixels);
                //std::cout << "Initial weight: " << neuralLayer[ii].weightOne[jj][kk] << std::endl;
            }
        }

        neuralLayer[ii].labeledOutput = 0.00;
        neuralLayer[ii].bias = 0.00;
        neuralLayer[ii].output = 0.00;
        neuralLayer[ii].sigmoidOutput = 0.00;


    }

    for(int kk = 0; kk < labelHdr.maxLabels; kk += 1)
    {
        imgLbl[kk] = 0;

    }

    std::cout << "Finished running initialisation..." << std::endl;
}

void Layer::InitLayer_KaiMing()
{
    GLdouble inputSize = (GLdouble)imageHdr.imgWidth * (GLdouble)imageHdr.imgHeight * (GLdouble)imageHdr.maxImages;
    GLdouble popSize = ((GLdouble)inputSize + (GLdouble)neuralSize);
    BooleanArithmetic ba;

    for (int ii = 0; ii < neuralSize; ii += 1)
    {
        std::cout << "Initialising layer: " << ii << std::endl;
        for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
        {
            for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
            {
                neuralLayer[ii].inputArray[jj][kk] = 0.00;
                //int totalPixels = imageHdr.imgWidth * imageHdr.imgHeight;

                GLdouble constKaiMing = (GLdouble) std::sqrt(2 / ((GLdouble) popSize));
                GLdouble tempResult = ba.BoxMullerTransform() * constKaiMing;
                neuralLayer[ii].weightOne[jj][kk] = tempResult;
                std::cout.precision(16);
                //std::cout << "Initial weight: " << tempResult << std::endl;
            }
        }

        neuralLayer[ii].labeledOutput = 0.00;
        neuralLayer[ii].bias = 0.00;
        neuralLayer[ii].output = 0.00;
        neuralLayer[ii].sigmoidOutput = 0.00;

    }

    for(int kk = 0; kk < labelHdr.maxLabels; kk += 1)
    {
        imgLbl[kk] = 0;

    }
}

void Layer::InitLayer_Xavier()
{
    GLdouble inputSize = (GLdouble)imageHdr.imgWidth * (GLdouble)imageHdr.imgHeight;
    //GLdouble inputSize = (GLdouble) imageHdr.maxImages;
    GLdouble popSize = ((GLdouble)inputSize + (GLdouble)neuralSize) / 2;
    BooleanArithmetic ba;

    for (int ii = 0; ii < neuralSize; ii += 1)
    {
        std::cout << "Initialising layer: " << ii << std::endl;
        for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
        {
            for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
            {
                neuralLayer[ii].inputArray[jj][kk] = 0.00;
                //int totalPixels = imageHdr.imgWidth * imageHdr.imgHeight;

                GLdouble constXavier = 1 / popSize;
                GLdouble tempResult = ba.BoxMullerTransform() * constXavier;
                neuralLayer[ii].weightOne[jj][kk] = tempResult;
                std::cout.precision(16);
                //std::cout << "Initial weight: " << tempResult << std::endl;
            }
        }

        neuralLayer[ii].labeledOutput = 0.00;
        neuralLayer[ii].bias = 0.00;
        neuralLayer[ii].output = 0.00;
        neuralLayer[ii].sigmoidOutput = 0.00;

    }

    for(int kk = 0; kk < labelHdr.maxLabels; kk += 1)
    {
        imgLbl[kk] = 0;

    }
}

void Layer::SetLayer(GLdouble** imgInput)
{
    // perform deep copy
    for(int ii = 0; ii < neuralSize; ii += 1)
    {
        for(int jj = 0; jj < imageHdr.imgWidth; jj += 1)
        {
            for(int kk = 0; kk < imageHdr.imgHeight; kk += 1)
            {
                neuralLayer[ii].inputArray[jj][kk] = imgInput[jj][kk];

                //std::cout << "neuron index: " << ii << " deep copy input: " << neuralLayer[ii].inputArray[jj][kk] << std::endl;
            }
        }
    }

}

void Layer::SetLayerBias(GLdouble imgBias)
{
	// perform deep copy
	for (int ii = 0; ii < neuralSize; ii += 1)
	{
		for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
		{
			for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
			{
				neuralLayer[ii].inputArray[jj][kk] = imgBias;

				//std::cout << "neuron index: " << ii << " deep copy input: " << neuralLayer[ii].inputArray[jj][kk] << std::endl;
			}
		}
	}

}

void Layer::SetImgLbl(GLdouble * lblInput)
{
    for(int ii = 0; ii < labelHdr.maxLabels; ii += 1)
    {
        imgLbl[ii] = lblInput[ii];
        //std::cout << "lbl index: " << ii << " label: " << imgLbl[ii] << " lbl input: " << lblInput[ii] <<std::endl;
    }
}



// https://becominghuman.ai/neural-network-xor-application-and-fundamentals-6b1d539941ed
void Layer::ForwardPropagation()
{
    BooleanArithmetic ba;

    GLdouble tempSigmoid;
    GLdouble tempOutput = 0.00;

    std::cout << "=========================================================================" << std::endl;

    for(int ii = 0; ii < neuralSize; ii += 1)
    {
		// ax + b
        tempOutput = ba.DotMultiply(imageHdr, neuralLayer[ii].inputArray, neuralLayer[ii].weightOne);

		//std::cout << "Dot Multiply: " << ba.DotMultiply(imageHdr, neuralLayer[ii].inputArray, neuralLayer[ii].weightOne) << std::endl;

        neuralLayer[ii].output = tempOutput + neuralLayer[ii].bias;
        //std::cout << "index: " << ii << " Neuron output: " << neuralLayer[ii].output << std::endl;

        tempSigmoid = ba.SigmoidFunction(neuralLayer[ii].output);

        neuralLayer[ii].sigmoidOutput = tempSigmoid;

        std::cout << "index: " << ii << " sigmoid output: " << neuralLayer[ii].sigmoidOutput << " Neuron output: " << neuralLayer[ii].output << std::endl;
    }
}

GLdouble ** Layer::CollateHiddenResult(ImageHeader imgHdr)
{
	GLdouble ** trainHiddenResult = new GLdouble *[imgHdr.imgWidth]();
	for (int aa = 0; aa < imgHdr.imgWidth; aa += 1)
	{
		trainHiddenResult[aa] = new GLdouble[imgHdr.imgHeight]();
	}

	for (int ii = 0; ii < 1; ii += 1)
	{
		for (int jj = 0; jj < imgHdr.imgHeight; jj += 1)
		{
			trainHiddenResult[ii][jj] = neuralLayer[jj].sigmoidOutput;
		}
	}

	return trainHiddenResult;
}

int Layer::GetLayerPrediction()
{
    GLdouble maxOutput = 0.0;
    int layerPrediction = 0;

    // converting output into comparable signal
    for (int jj = 0; jj < neuralSize; jj += 1)
    {
        //std::cout << "predict index: " << jj << " predict sigmoids: " << neuralLayer[jj].sigmoidOutput << std::endl;

        if (neuralLayer[jj].sigmoidOutput > maxOutput)
        {
            maxOutput = neuralLayer[jj].sigmoidOutput;
            layerPrediction = jj;
        }

    }

    return layerPrediction;
}

GLdouble Layer::CalculateGeneralError(int target)
{
	GLdouble tempError = 0.00;
	GLdouble tempMSE = 0.00;
	GLdouble mseResult = 0.00;

	tempError = imgLbl[target] - neuralLayer->sigmoidOutput;
	std::cout << "initial error: " << tempError << " actual: " << imgLbl[target] << " target check: " << target << std::endl;

	tempMSE = tempError * tempError;
	std::cout << "tempMSE: " << tempMSE << std::endl;

	tempMSE = tempMSE/(GLdouble)(imageHdr.maxImages * imageHdr.imgWidth * imageHdr.imgHeight);
	std::cout << "tempMSE: " << tempMSE << " size: " << (GLdouble)(imageHdr.maxImages * imageHdr.imgWidth * imageHdr.imgHeight) <<std::endl;

	sumOfMSE += tempMSE;
	std::cout << "sumOfMSE: " << sumOfMSE << std::endl;

	mseResult = sumOfMSE;
	std::cout << "total error: " << mseResult << std::endl;

	return tempError;
}


// calculate the MNIST std error
GLdouble Layer::CalculateMNISTError(int targetLabel)
{
    GLdouble tempError = 0.00;
    GLdouble tempMSE = 0.00;
    GLdouble mseResult = 0.00;

    tempError = GetLayerPrediction() - imgLbl[targetLabel];

    tempMSE = tempError * tempError;

    //std::cout << "tempMSE: " << tempMSE << std::endl;

    sumOfMSE += tempMSE;

    //std::cout << "sumOfMSE: " << sumOfMSE << std::endl;

    mseResult = sumOfMSE / (GLdouble)(imageHdr.maxImages * imageHdr.imgWidth * imageHdr.imgHeight);

    return mseResult;
}



GLdouble Layer::CalculateDerivative()
{
    GLdouble tempResult = 0.00;

    for (int ii = 0; ii < neuralSize; ii += 1)
    {

        tempResult = neuralLayer[ii].sigmoidOutput * (1 - neuralLayer[ii].sigmoidOutput);
		neuralLayer[ii].derivativeOutput = tempResult;

        //std::cout << "derivative Output: " << tempResult << std::endl;

    }

    return tempResult;
}

void Layer::UpdateNeuronWeights(GLdouble stdError, GLdouble learningRate)
{
	CalculateDerivative();

    for (int ii = 0; ii < neuralSize; ii += 1)
    {
        for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
        {
            for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
            {
               
				neuralLayer[ii].errorOutput = neuralLayer[ii].derivativeOutput * stdError * neuralLayer[ii].weightOne[jj][kk] * -1;
				
				//GLdouble checkDelta = neuralLayer[ii].inputArray[jj][kk] * neuralLayer[ii].derivativeOutput * stdError;
				//std::cout << "check delta: " << checkDelta << " check total  output: " << neuralLayer[ii].inputArray[jj][kk] << " derivative: " << neuralLayer[ii].derivativeOutput <<" stdError: " << stdError << std::endl;
				//GLdouble tempSGD = learningRate * neuralLayer[ii].inputArray[jj][kk] * tempDerivative * stdError;
				
				GLdouble tempSGD = learningRate * neuralLayer[ii].inputArray[jj][kk] * neuralLayer[ii].derivativeOutput * stdError * -1;
				//std::cout << "temp SGD: " << tempSGD << std::endl;
				
				neuralLayer[ii].weightOne[jj][kk] += tempSGD;

                //std::cout << "Update Index: "<< ii << " Error Output: " << neuralLayer[ii].errorOutput <<" Updated weight: " << neuralLayer[ii].weightOne[jj][kk] << std::endl;
            }
        }
	}
}

GLdouble Layer::TotalLayerError()
{

	GLdouble errorResult = 0.00;
	for (int ii = 0; ii < neuralSize; ii += 1)
	{
		errorResult += neuralLayer[ii].errorOutput;
	}

	std::cout << "Total Layer Error: " << errorResult << std::endl;

	return errorResult;
}

void Layer::BackpropagationHidden(GLdouble sumOfError, GLdouble stdError, GLdouble learningRate)
{
	CalculateDerivative();

	for (int ii = 0; ii < neuralSize; ii += 1)
	{
		for (int jj = 0; jj < imageHdr.imgWidth; jj += 1)
		{
			for (int kk = 0; kk < imageHdr.imgHeight; kk += 1)
			{
				neuralLayer[ii].errorOutput = -1 * stdError * neuralLayer[ii].derivativeOutput * neuralLayer[ii].weightOne[jj][kk];
				//std::cout << "Hidden Error output: " << neuralLayer[ii].errorOutput << std::endl;;

				GLdouble tempSGD = -1 * learningRate * neuralLayer[ii].derivativeOutput * sumOfError * neuralLayer[ii].inputArray[jj][kk];

				//std::cout << "hidden SGD: " << tempSGD << " hidden derivative: " << neuralLayer[ii].derivativeOutput << " input: " << neuralLayer[ii].inputArray[jj][kk] << " prior layer total error: " << sumOfError <<std::endl;
				
				neuralLayer[ii].weightOne[jj][kk] += tempSGD;

				//std::cout << "New hidden weight: " << neuralLayer[ii].weightOne[jj][kk] << std::endl;

			}
		}
	}
	

}