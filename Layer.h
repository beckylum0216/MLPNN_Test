//
// Created by becky on 24/12/2018.
//

#ifndef DEEPLENS_RL_33111264_LAYER_H
#define DEEPLENS_RL_33111264_LAYER_H

#include <math.h>
#include "Neuron.h"
#include "ImageHeader.h"
#include "LabelHeader.h"
#include "BooleanArithmetic.h"

class Layer {
    public:
        Layer();
        Layer(const Layer &rhsLayer);
        Layer(ImageHeader imgHdr, LabelHeader lblHdr, int labelSize, int neuronSize);
        ~Layer();

        //Getters and Setters
		int GetNeuralSize();

        Layer & operator= (Layer rhsVar);
        /**
        *	@brief getter for Neurons
        *	@param
        *	@return neuron
        *	@pre
        *	@post
        */
        Neuron * GetNeurons();

        GLdouble * GetImgLbl();


        /**
        *	@brief resizes neurons
        *	@param
        *	@return void
        *	@pre
        *	@post
        */
        void ResizeLayer(ImageHeader imgHdr, LabelHeader lblHdr, int labelSize, int neuronSize);

		void InitLayer_Random();
		void InitLayer_KaiMing();
		void InitLayer_Xavier();

		void SetLayer(GLdouble** imgInput);

		void SetImgLbl(GLdouble * lblInput);

		void ForwardPropagation();

		int  GetLayerPrediction();

		GLdouble CalculateGeneralError(int target);

		GLdouble CalculateMNISTError(int targetLabel);

		void UpdateNeuronWeights(GLdouble stdError, GLdouble learningRate);

		GLdouble TotalLayerError();

		void BackpropagationHidden(GLdouble sumOfError, GLdouble stdError, GLdouble learningRate);

    private:

		void Swap(Layer &rhsVar);
		GLdouble CalculateDerivative();

		Neuron * neuralLayer;
		GLdouble * imgLbl;
		int neuralSize;
        ImageHeader imageHdr;
        LabelHeader labelHdr;
        GLdouble  sumOfMSE;

};


#endif //DEEPLENS_RL_33111264_LAYER_H
