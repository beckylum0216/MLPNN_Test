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

        void ResizeNeuron(ImageHeader imgHdr, LabelHeader lblHdr);
        GLdouble ** inputArr;
        GLdouble ** weightOne;
        GLdouble output;
        GLdouble sigmoidOutput;
        GLdouble bias;



};


#endif //DEEPLENS_RL_33111264_NEURON_H
