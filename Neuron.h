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
        Neuron(ImageHeader imgHdr, LabelHeader lblHdr);
        ~Neuron();
        Neuron& operator= (Neuron rhsNeuron);
        void Swap(Neuron &rhsNeuron);
        

		//functions that actually matter
		void ResizeNeuron(ImageHeader imgHdr, LabelHeader lblHdr);
		

		// properties of a neuron - essentially a struct in a class
		GLdouble ** inputArr;
        GLdouble ** weightOne;
        GLdouble output;
        GLdouble sigmoidOutput;
        GLdouble bias;
		GLdouble sizeX;
		GLdouble sizeY;

	private:

};


#endif //DEEPLENS_RL_33111264_NEURON_H
