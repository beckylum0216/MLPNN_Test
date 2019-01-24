//
// Created by becky on 24/12/2018.
//

#include <vector>
#include <iostream>
#include "Layer.h"

Layer::Layer()
{
    neuralLayer = new Neuron[2]();
    neuralSize = 2;
}

Layer::Layer(const Layer &rhsLayer)
{
    this->neuralLayer = rhsLayer.neuralLayer;
    this->layerSize = rhsLayer.layerSize;
	this->neuralSize = rhsLayer.neuralSize;
}

Layer::Layer(ImageHeader imgHdr, LabelHeader lblHdr, int neuronSize)
{
    std::cout << "running overloaded layer" << std::endl;

    neuralLayer = new Neuron[neuronSize]();
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        neuralLayer[ii].ResizeNeuron(imgHdr, lblHdr);
    }

	layerSize = neuronSize;
	neuralSize = neuronSize;

    std::cout << "layer created..." << std::endl;
}

Layer::~Layer()
{
    std::cout << "deleting layers..." << std::endl;
    delete [] neuralLayer;
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

int Layer::GetLayerSize()
{
	return layerSize;
}

int Layer::GetNeuralSize()
{
	return neuralSize;
}

void Layer::ResizeLayer(ImageHeader imgHdr, LabelHeader lblHdr, int neuronSize)
{
    std::cout << "Running layer resize..." << std::endl;

    // initialise temp neuron
    Neuron * tempNeuron;
    tempNeuron = new Neuron[neuronSize]();

    // resizing temp neuron
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        std::cout << "Neuron index: " << ii << std::endl;
        tempNeuron[ii].ResizeNeuron(imgHdr, lblHdr);
    }

	// copying old neurons to temp neurons
    for(int ii = 0; ii < neuralSize; ii += 1)
    {
        for(int jj = 0; jj < this->neuralLayer[ii].sizeX; jj += 1)
        {
            for(int kk = 0; kk < this->neuralLayer[ii].sizeY; kk += 1)
            {
                tempNeuron[ii].inputArr[jj][kk] = this->neuralLayer[ii].inputArr[jj][kk];
                tempNeuron[ii].weightOne[jj][kk] = this->neuralLayer[ii].weightOne[jj][kk];
            }
        }

    }

    neuralSize = neuronSize;

    std::cout << "Deleting the layer" << std::endl;
    
	delete [] neuralLayer; // offending code ?

    std::cout << "Finish deleting the layer" << std::endl;

	//neuralLayer = tempNeuron; //did not work before
    neuralLayer = new Neuron[neuronSize]; // here is the offending declaration causes destructors to run
	
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        neuralLayer[ii].ResizeNeuron(imgHdr, lblHdr);
    }

	// performing deep copy - copying temp data into resized layer
    for(int ii = 0; ii < neuronSize; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                neuralLayer[ii].inputArr[jj][kk] = tempNeuron[ii].inputArr[jj][kk];
                neuralLayer[ii].weightOne[jj][kk] = tempNeuron[ii].weightOne[jj][kk];
            }
        }

    }
	
    std::cout << "deleting tempNeurons... " << std::endl;
    delete[] tempNeuron;

    std::cout << "Finished resizing layer..." << std::endl;
}