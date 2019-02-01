#include "gtest/gtest.h"

#include "Perceptron.h"
#include "ImageHeader.h"
#include "LabelHeader.h"
#include "UtilityFunctions.h"



TEST(SUITE003Perceptron, TestPerceptron001) {
	Perceptron objCreation;

	SUCCEED();
}

TEST(SUITE003Perceptron, DISABLED_TestPerceptron002) 
{
	
	//Perceptron objCreation; // issue is here revisit cannot re-declare

	ImageHeader outputHdr;
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int layerSize = 20;
	int neuronSize = 10;

	outputHdr.maxImages = layerSize;
	outputHdr.imgWidth = 1;
	outputHdr.imgHeight = layerSize;

	imgHdr.maxImages = 50;
	imgHdr.imgWidth = 50; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 50; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;
	
	Perceptron objCreation = Perceptron(imgHdr, lblHdr, layerSize, outputHdr, neuronSize);

	SUCCEED();
}













