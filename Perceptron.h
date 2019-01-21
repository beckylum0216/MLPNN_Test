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
        Perceptron(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize, int neuronSize);
        ~Perceptron();
        Layer * GetLayer();
        // initialising layer
        void InitLayer(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize,int neuronSize);
        void InitSigmoidLayer(ImageHeader imgHdr, int neuronSize);

        void ResizePerceptron(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize, int neuronSize);

        GLdouble SigmoidFunction(GLdouble targetInput);

        //training perceptron
        void SetLayer(GLdouble** imgInput, ImageHeader imgHdr, int layerSize,int neuronSize);
        void SetLabel(GLdouble * lblInput, LabelHeader lblHdr);
        void ForwardPropagation(ImageHeader imgHdr, int layerSize, int neuronSize);
        void CalculateOutput(ImageHeader imgHdr, int layerSize, int neuronSize);
        GLdouble CalculateError(ImageHeader imgHdr, int targetLayer, int targetNeuron);
        void UpdateNeuronWeights(ImageHeader imgHdr, int targetLayer, int targetNeuron, GLdouble stdError, GLdouble learningRate);


        // testing perceptron
        std::vector <GLdouble> SetTargetOutput(int targetIndex, int outputSize);
        int  GetLayerPrediction(int layerSize, int neuronSize);

    private:
        Layer * theLayer;
        Layer * sigmoidLayer;

        int layerSize;
        GLdouble * imgLbl;

};


#endif //DEEPLENS_RL_33111264_PERCEPTRON_H
