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
		//getters and setters
        Layer * GetLayer();
		int GetLayerCount();
		int GetNeuronCount();

        // initialising layer
        void InitLayer_Random();
		void InitLayer_KaiMing(int neuronSize);
		void InitLayer_Xavier();
		GLdouble BoxMullerTransform();
		GLdouble UniformRandom();

        void InitSigmoidLayer_Xavier(ImageHeader imgHdr, int neuronSize);

        void ResizePerceptron(ImageHeader imgHdr, LabelHeader lblHdr, int layerSize, int neuronSize);

        GLdouble SigmoidFunction(GLdouble targetInput);

        //training perceptron

		// SetLayer is suspect
        void SetLayer(GLdouble** imgInput);
        void SetLabel(GLdouble * lblInput, LabelHeader lblHdr);
       
		void ForwardPropagation();
		void ForwardSigmoidPropagation();

        GLdouble CalculateError(ImageHeader imgHdr, int targetLabel);
		GLdouble CalculateSigmoidError(ImageHeader imgHdr, int targetLabel);

		GLdouble DerivativeLayer(ImageHeader imgHdr, int layerSize, int neuronSize);
		GLdouble DerivativeSigmoid(ImageHeader imgHdr, int layerSize, int neuronSize);

        void UpdateNeuronWeights(ImageHeader imgHdr, GLdouble stdError, GLdouble learningRate);
		void UpdateSigmoidWeights(ImageHeader imgHdr, GLdouble stdError, GLdouble learningRate);

        // testing perceptron
        int  GetLayerPrediction();
		int  GetSigmoidLayerPrediction();

    private:
        Layer * theLayer;
        Layer * sigmoidLayer;
		GLdouble * imgLbl;
		ImageHeader imageHdr;
		LabelHeader labelHdr;
		int layerCount;
		int neuronCount;

		GLdouble sumOfMSE;
        
};


#endif //DEEPLENS_RL_33111264_PERCEPTRON_H
