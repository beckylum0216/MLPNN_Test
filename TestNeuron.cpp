#include "gtest/gtest.h"
#include "Neuron.h"
#include "ImageHeader.h"
#include "LabelHeader.h"

TEST(Suite001Neuron, TestNeuron001) {
	Neuron objCreation;

	SUCCEED();
}

TEST(Suite001Neuron, TestNeuron002)
{
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	

	imgHdr.maxImages = 50;
	imgHdr.imgWidth = 50; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 50; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	Neuron objCreation;

	imgHdr.maxImages = 150;
	imgHdr.imgWidth = 150; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 150; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	objCreation.ResizeNeuron(imgHdr);
	
	SUCCEED();
}