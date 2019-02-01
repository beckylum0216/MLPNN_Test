//
// Created by becky on 23/12/2018.
//

#ifndef DEEPLENS_RL_33111264_PERCEPTRON_H
#define DEEPLENS_RL_33111264_PERCEPTRON_H

#include <vector>
#include "Layer.h"
#include "ImageHeader.h"

class Perceptron {
    public:
        Perceptron();
        Perceptron(ImageHeader imgHdr, LabelHeader lblHdr, int hiddenSize, ImageHeader outputHdr, int neuronSize);
        ~Perceptron();
		//getters and setters
        Layer * GetHiddenLayer();
        Layer * GetSigmoidLayer();
		int GetHiddenCount();
		int GetNeuronCount();
		ImageHeader GetImgHdr();
		ImageHeader GetOutputHdr();

        // initialising layer


        //training perceptron


    private:
        Layer * hiddenLayer;
        Layer * sigmoidLayer;
        ImageHeader outputHeader;
		ImageHeader imageHdr;
		LabelHeader labelHdr;
		int hiddenCount;
		int neuronCount;

        
};


#endif //DEEPLENS_RL_33111264_PERCEPTRON_H
