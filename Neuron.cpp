//
// Created by becky on 23/12/2018.
//

#include <iostream>
#include "Neuron.h"

Neuron::Neuron()
{

    inputArr = new GLdouble * [28]();
    weightOne = new GLdouble * [28]();

    for (int jj = 0; jj < 28; jj += 1)
    {
        inputArr[jj] = new GLdouble[28]();
        weightOne[jj] = new GLdouble[28]();
    }

    output = 0;
    bias = 0;
}

Neuron::Neuron(ImageHeader imgHdr, LabelHeader lblHdr)
{

    inputArr = new GLdouble * [imgHdr.imgWidth]();
    weightOne = new GLdouble * [imgHdr.imgWidth]();
    for(int ii = 0; ii < imgHdr.imgWidth; ii += 1)
    {
        inputArr[ii] = new GLdouble[imgHdr.imgHeight]();
        weightOne[ii] = new GLdouble[imgHdr.imgHeight]();
    }

    output = 0;
    bias = 0;


}

Neuron::~Neuron()
{
    std::cout << "Neuron Destructor: Deleting neuron..." << std::endl;
    delete [] inputArr;
    delete [] weightOne;
}

Neuron& Neuron::operator=(Neuron rhsNeuron)
{
    this->Swap(rhsNeuron);
    return *this;
}

void Neuron::Swap(Neuron &rhsNeuron)
{
    std::swap(this->inputArr, rhsNeuron.inputArr);
    std::swap(this->weightOne, rhsNeuron.weightOne);
    std::swap(this->output, rhsNeuron.output);
    std::swap(this->bias, rhsNeuron.bias);

}

void Neuron::ResizeNeuron(ImageHeader imgHdr, LabelHeader lblHdr){
    std::cout << "Running neuron resize..." << std::endl;

    GLdouble ** tempArr;
    GLdouble ** tempWeightOne;

    // initialise new arrays;
    tempArr = new GLdouble*[imgHdr.imgWidth];
    tempWeightOne = new GLdouble*[imgHdr.imgWidth];
    for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
    {
        tempArr[jj] = new GLdouble[imgHdr.imgHeight];
        tempWeightOne[jj] = new GLdouble[imgHdr.imgHeight];
    }

    // copying original arrays
    for(int jj = 0; jj < 28; jj += 1)
    {
        for(int kk = 0; kk < 28; kk += 1)
        {
            tempArr[jj][kk] = inputArr[jj][kk];
            tempWeightOne[jj][kk] = weightOne[jj][kk];

        }
    }


    // clear arrays
    delete [] inputArr;
    delete [] weightOne;

    // redeclaring arrays and copying contents from temp to class arrays


        inputArr = new GLdouble * [imgHdr.imgWidth]();
        weightOne = new GLdouble * [imgHdr.imgWidth]();

        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            inputArr[jj] = new GLdouble [imgHdr.imgHeight]();
            weightOne[jj] = new GLdouble [imgHdr.imgHeight]();

            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                inputArr[jj][kk] = tempArr[jj][kk];
                weightOne[jj][kk] = tempWeightOne[jj][kk];

            }
        }


    delete [] tempArr;
    delete [] tempWeightOne;


    std::cout << "Finished resizing neuron..." << std::endl;
}