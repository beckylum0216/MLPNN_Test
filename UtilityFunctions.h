//
// Created by becky on 22/12/2018.
//

#ifndef DEEPLENS_RL_33111264_UTILITYFUNCTIONS_H
#define DEEPLENS_RL_33111264_UTILITYFUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include "ImageHeader.h"
#include "LabelHeader.h"

class UtilityFunctions {
    public:
        UtilityFunctions();
        ~UtilityFunctions();
        int ReverseByte(int inputBits);
        ImageHeader ReadImageHeader(std::string theFile);
        LabelHeader ReadLabelHeader(std::string theFile);

        GLdouble *** ReadImageFile(std::string theFile, ImageHeader  imageHdr);
        GLdouble * ReadLabelFile(std::string theFile, LabelHeader  labelHdr);
        void DeallocateMemory();
        void DisplayImage(GLdouble ** targetImage, ImageHeader imgHdr);





    private:
        GLdouble *** imgMatrix;
        GLdouble * lblMatrix;

};


#endif //DEEPLENS_RL_33111264_UTILITYFUNCTIONS_H
