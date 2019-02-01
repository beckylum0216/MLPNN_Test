//
// Created by becky on 23/12/2018.
//

#ifndef DEEPLENS_RL_33111264_NEURON_H
#define DEEPLENS_RL_33111264_NEURON_H


#include <GL/freeglut.h>
#include "LabelHeader.h"
#include "ImageHeader.h"

class Neuron {

    public:
        Neuron();
        Neuron(ImageHeader imgHdr);
        ~Neuron();
        Neuron& operator= (Neuron rhsNeuron);
        void Swap(Neuron &rhsNeuron);
        

		//functions that actually matter
		void ResizeNeuron(ImageHeader imgHdr);
		void SetInputArray(GLdouble ** targetArray);
		

		// properties of a neuron - essentially a struct in a class
		GLdouble ** inputArray;
        GLdouble ** weightOne;

        GLdouble output;
        GLdouble sigmoidOutput;
		GLdouble derivativeOutput;
		GLdouble errorOutput;
        GLdouble bias;
		GLdouble sizeX;
		GLdouble sizeY;
		GLdouble labeledOutput;

	private:

};


#endif //DEEPLENS_RL_33111264_NEURON_H
