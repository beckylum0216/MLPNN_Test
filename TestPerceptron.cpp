#include "gtest/gtest.h"

#include "Perceptron.h"
#include "ImageHeader.h"
#include "LabelHeader.h"
#include "UtilityFunctions.h"



TEST(SUITE003Perceptron, TestPerceptron001) {
	Perceptron objCreation;

	SUCCEED();
}

TEST(SUITE003Perceptron, TestPerceptron002) {
	
	//Perceptron objCreation; // issue is here revisit cannot re-declare

	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int layerSize;
	int neuronSize;

	imgHdr.maxImages = 50;
	imgHdr.imgWidth = 50; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 50; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;
	
	layerSize = 3;

	neuronSize = 10;

	Perceptron objCreation = Perceptron(imgHdr, lblHdr, layerSize, neuronSize);

	SUCCEED();
}

TEST(TestSuite003Perceptron, DISABLED_TestPerceptron003_InitRandom)
{
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int layerSize;
	int neuronSize;

	imgHdr.maxImages = 100;
	imgHdr.imgWidth = 32; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 32; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	layerSize = 3;

	neuronSize = 15;

	Perceptron testObj = Perceptron(imgHdr, lblHdr, layerSize, neuronSize);

	testObj.InitLayer_Random();

	for (int aa = 0; aa < layerSize; aa += 1)
	{
		GLdouble checkWeights = 0.00;
		for (int bb = 0; bb < neuronSize; bb += 1)
		{
			
			for (int cc = 0; cc < imgHdr.imgWidth; cc += 1)
			{
				for (int dd = 0; dd < imgHdr.imgWidth; dd += 1)
				{
					checkWeights += testObj.GetLayer()[aa].GetNeurons()[bb].weightOne[cc][dd];
				}
			}

		}

		EXPECT_EQ(1, checkWeights);
	}

}

TEST(TestSuite003Perceptron, TestPerceptron003_InitKaiMing)
{
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int layerSize;
	int neuronSize;

	imgHdr.maxImages = 100;
	imgHdr.imgWidth = 32; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 32; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	layerSize = 3;

	neuronSize = 10;

	Perceptron testObj = Perceptron(imgHdr, lblHdr, layerSize, neuronSize);

	testObj.InitLayer_KaiMing(neuronSize);

	for (int aa = 0; aa < layerSize; aa += 1)
	{
		GLdouble checkWeights = 0.00;
		for (int bb = 0; bb < neuronSize; bb += 1)
		{
			
			for (int cc = 0; cc < imgHdr.imgWidth; cc += 1)
			{
				for (int dd = 0; dd < imgHdr.imgWidth; dd += 1)
				{
					checkWeights += testObj.GetLayer()[aa].GetNeurons()[bb].weightOne[cc][dd];
				}

			}
		}

		EXPECT_EQ(1, checkWeights);
	}

}

TEST(TestSuite003Perceptron, TestPerceptron004_InitXavier)
{
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int layerSize;
	int neuronSize;

	imgHdr.maxImages = 100;
	imgHdr.imgWidth = 32; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 32; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	layerSize = 3;

	neuronSize = 10;

	Perceptron testObj = Perceptron(imgHdr, lblHdr, layerSize, neuronSize);

	testObj.InitLayer_Xavier();

	for (int aa = 0; aa < layerSize; aa += 1)
	{
		GLdouble checkWeights = 0.00;
		for (int bb = 0; bb < neuronSize; bb += 1)
		{

			for (int cc = 0; cc < imgHdr.imgWidth; cc += 1)
			{
				for (int dd = 0; dd < imgHdr.imgWidth; dd += 1)
				{
					checkWeights += testObj.GetLayer()[aa].GetNeurons()[bb].weightOne[cc][dd];
				}

			}
		}

		EXPECT_EQ(1, checkWeights);
	}

}


TEST(TestSuite003Perceptron, TestPerceptron005_SetLayer)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	
	std::string imgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string lblFile = "../mnist/t10k-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	Perceptron * oneLayerNN = new Perceptron(imgHdr, lblHdr, 2, 10);

	GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{
		tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
		for (int jj = 0; jj < imgHdr.imgHeight; jj += 1)
		{
			tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
		}
	}

	tempImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

	oneLayerNN->InitLayer_KaiMing(10);

	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{
		
		oneLayerNN->SetLayer(tempImgMatrix[ii]);
	}

	SUCCEED();
}

TEST(TestSuite003Perceptron, TestPerceptron006_ForwardPropagation)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	std::string imgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string lblFile = "../mnist/t10k-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	Perceptron * oneLayerNN = new Perceptron(imgHdr, lblHdr, 2, 10);

	GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{
		tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
		for (int jj = 0; jj < imgHdr.imgHeight; jj += 1)
		{
			tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
		}
	}

	tempImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

	oneLayerNN->InitLayer_Xavier();

	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{

		oneLayerNN->SetLayer(tempImgMatrix[ii]);
	}

	oneLayerNN->ForwardPropagation();

	SUCCEED();
}

TEST(TestSuite003Perceptron, DISABLED_TestPerceptron007_StdError)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	std::string imgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string lblFile = "../mnist/t10k-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	Perceptron * oneLayerNN = new Perceptron(imgHdr, lblHdr, 2, 10);

	GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{
		tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
		for (int jj = 0; jj < imgHdr.imgHeight; jj += 1)
		{
			tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
		}
	}

	tempImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

	oneLayerNN->InitLayer_Xavier();

	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{

		oneLayerNN->SetLayer(tempImgMatrix[ii]);

		oneLayerNN->ForwardPropagation();
		GLdouble stdError = oneLayerNN->CalculateError(imgHdr, ii);
		std::cout << "Std Error: " << stdError << std::endl;
	}

	

	SUCCEED();
}

TEST(TestSuite003Perceptron, TestPerceptron008_BackPropagation)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	std::string imgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string lblFile = "../mnist/t10k-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	Perceptron * oneLayerNN = new Perceptron(imgHdr, lblHdr, 2, 10);

	GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{
		tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
		for (int jj = 0; jj < imgHdr.imgHeight; jj += 1)
		{
			tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
		}
	}

	tempImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

	oneLayerNN->InitLayer_Xavier();

	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{

		oneLayerNN->SetLayer(tempImgMatrix[ii]);

		oneLayerNN->ForwardPropagation();
		GLdouble stdError = oneLayerNN->CalculateError(imgHdr, ii);
		std::cout << "Std Error: " << stdError << std::endl;
		oneLayerNN->UpdateNeuronWeights(imgHdr, stdError, 0.001);

	}




	SUCCEED();
}

