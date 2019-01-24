#include "gtest/gtest.h"

#include "ImageHeader.h"
#include "LabelHeader.h"
#include "Layer.h"

TEST(Suite002Layer, TestLayer001) {
	Layer objCreation;

	SUCCEED();
}

TEST(Suite002Layer, TestLayer002)
{
	
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	imgHdr.maxImages = 50;
	imgHdr.imgWidth = 50; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 50; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	Layer objCreation = Layer(imgHdr, lblHdr, 10);

	SUCCEED();
}

TEST(Suite002Layer, TestLayer003Resize)
{
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int neuronSize;

	imgHdr.maxImages = 50;
	imgHdr.imgWidth = 50; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 50; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	neuronSize = 10;

	Layer objCreation;

	objCreation.ResizeLayer(imgHdr, lblHdr, neuronSize);


	SUCCEED();
}
