//
// Created by becky on 24/12/2018.
//

#include <vector>
#include <iostream>
#include "Layer.h"

Layer::Layer()
{
    theLayer = new Neuron();
    layerSize = 0;
}

Layer::Layer(const Layer &rhsLayer)
{
    this->theLayer = rhsLayer.theLayer;
    this->layerSize = rhsLayer.layerSize;
}

Layer::Layer(ImageHeader imgHdr, LabelHeader lblHdr, int neuronSize)
{
    std::cout << "running overloaded layer" << std::endl;

    theLayer = new Neuron[neuronSize]();
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        theLayer[ii].ResizeNeuron(imgHdr, lblHdr);
    }

    std::cout << "layer created..." << std::endl;
}

Layer::~Layer()
{
    std::cout << "deleting layers..." << std::endl;
    delete [] theLayer;
}

Layer& Layer::operator=(Layer rhsVar)
{
    this->Swap(rhsVar);
    return *this;
}

void Layer::Swap(Layer &rhsVar)
{
    std::swap(this->theLayer, rhsVar.theLayer);
}

Neuron * Layer::GetNeurons()
{
    return theLayer;
}

int Layer::GetLayerSize()
{
	return layerSize;
}

void Layer::ResizeLayer(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize)
{
    std::cout << "Running layer resize..." << std::endl;

    // initialise temp neuron
    Neuron * tempNeuron;
    tempNeuron = new Neuron[inputSize];

    // resizing temp neuron
    for(int ii = 0; ii < inputSize; ii += 1)
    {
        std::cout << "Neuron index: " << ii << std::endl;
        tempNeuron[ii].ResizeNeuron(imgHdr, lblHdr);
    }


    for(int ii = 0; ii < layerSize; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                tempNeuron[ii].inputArr[jj][kk] = this->theLayer[ii].inputArr[jj][kk];
                tempNeuron[ii].weightOne[jj][kk] = this->theLayer[ii].weightOne[jj][kk];
            }
        }

    }

    layerSize = inputSize;

    std::cout << "Deleting the layer" << std::endl;
    delete theLayer;
    std::cout << "Finish deleting the layer" << std::endl;

    theLayer = new Neuron[inputSize]; // here is the offending declaration causes desstructors to run

    for(int ii = 0; ii < inputSize; ii += 1)
    {
        theLayer[ii].ResizeNeuron(imgHdr, lblHdr);
    }

    for(int ii = 0; ii < inputSize; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                theLayer[ii].inputArr[jj][kk] = tempNeuron[ii].inputArr[jj][kk];
                theLayer[ii].weightOne[jj][kk] = tempNeuron[ii].weightOne[jj][kk];
            }
        }

    }

    std::cout << "deleting tempNeurons... " << std::endl;

    delete[] tempNeuron;

    std::cout << "Finished resizing layer..." << std::endl;
}