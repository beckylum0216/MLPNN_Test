//
// Created by becky on 23/12/2018.
//

#include <iostream>
#include "Neuron.h"

Neuron::Neuron()
{
    inputArray = new GLdouble * [1]();
    weightOne = new GLdouble * [1]();
    for (int jj = 0; jj < 1; jj += 1)
    {
        inputArray[jj] = new GLdouble[1]();
        weightOne[jj] = new GLdouble[1]();
    }

	for (int ii = 0; ii < 1; ii += 1)
	{
		for (int jj = 0; jj < 1; jj += 1)
		{
			inputArray[ii][jj] = 0.00;
			weightOne[ii][jj] = 0.00;
		}
	}


    output = 0;
    bias = 0;
	sigmoidOutput = 0;

	sizeX = 1;
	sizeY = 1;
    labeledOutput = 0.00;
}

Neuron::Neuron(ImageHeader imgHdr)
{

    inputArray = new GLdouble * [imgHdr.imgWidth]();
    weightOne = new GLdouble * [imgHdr.imgWidth]();
    for(int ii = 0; ii < imgHdr.imgWidth; ii += 1)
    {
        inputArray[ii] = new GLdouble[imgHdr.imgHeight]();
        weightOne[ii] = new GLdouble[imgHdr.imgHeight]();
    }

	for (int ii = 0; ii < imgHdr.imgWidth; ii += 1)
	{
		for (int jj = 0; jj < imgHdr.imgHeight; jj += 1)
		{
			inputArray[ii][jj] = 0.00;
			weightOne[ii][jj] = 0.00;
		}
	}

    output = 0;
    bias = 0;

	sizeX = imgHdr.imgWidth;
	sizeY = imgHdr.imgHeight;


}

Neuron::~Neuron()
{
    std::cout << "Neuron Destructor: Deleting neuron..." << std::endl;

    delete [] inputArray;
    delete [] weightOne;
}

Neuron& Neuron::operator=(Neuron rhsNeuron)
{
    this->Swap(rhsNeuron);
    return *this;
}

void Neuron::Swap(Neuron &rhsNeuron)
{
    std::swap(this->inputArray, rhsNeuron.inputArray);
    std::swap(this->weightOne, rhsNeuron.weightOne);
    std::swap(this->output, rhsNeuron.output);
    std::swap(this->bias, rhsNeuron.bias);

}

void Neuron::ResizeNeuron(ImageHeader imgHdr){
    std::cout << "Running neuron resize..." << std::endl;

    GLdouble ** tempArr;
    GLdouble ** tempWeightOne;

    // initialise new arrays;
    tempArr = new GLdouble*[imgHdr.imgWidth]();
    tempWeightOne = new GLdouble*[imgHdr.imgWidth]();
    for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
    {
        tempArr[jj] = new GLdouble[imgHdr.imgHeight]();
        tempWeightOne[jj] = new GLdouble[imgHdr.imgHeight]();
    }

    // copying original arrays
    for(int jj = 0; jj < sizeX; jj += 1)
    {
        for(int kk = 0; kk < sizeY; kk += 1)
        {
            tempArr[jj][kk] = inputArray[jj][kk];
            tempWeightOne[jj][kk] = weightOne[jj][kk];

        }
    }

	sizeX = imgHdr.imgWidth;
	sizeY = imgHdr.imgHeight;

	// dunno how it worked in the first version
	
    // clear arrays
    delete [] inputArray;
    delete [] weightOne;
	

    // redeclaring arrays and copying contents from temp to class arrays
    inputArray = new GLdouble * [imgHdr.imgWidth]();
    weightOne = new GLdouble * [imgHdr.imgWidth]();
    for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
    {
        inputArray[jj] = new GLdouble [imgHdr.imgHeight]();
        weightOne[jj] = new GLdouble [imgHdr.imgHeight]();

        for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
        {
            inputArray[jj][kk] = tempArr[jj][kk];
            weightOne[jj][kk] = tempWeightOne[jj][kk];
        }
    }
	
    delete [] tempArr;
    delete [] tempWeightOne;

    std::cout << "Finished resizing neuron..." << std::endl;
}

void Neuron::SetInputArray(GLdouble **targetArray)
{
    for(int ii = 0; ii < sizeX; ii += 1)
    {
        for(int jj = 0; jj < sizeY; jj += 1)
        {
            inputArray[ii][jj] = targetArray[ii][jj];
            std::cout << "target input: " << targetArray[ii][jj] << " input check: " << inputArray[ii][jj] << std::endl;
        }
    }
}