#include "gtest/gtest.h"

#include "ImageHeader.h"
#include "LabelHeader.h"
#include "UtilityFunctions.h"
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

	Layer objCreation = Layer(imgHdr, lblHdr, lblHdr.maxLabels, 10);

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

	Layer * objCreation = new Layer();

	objCreation->ResizeLayer(imgHdr, lblHdr, lblHdr.maxLabels, neuronSize);


	SUCCEED();
}

TEST(Suite002Layer, TestLayer004Init_Random)
{
	
	ImageHeader outputHdr;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	int layerSize = 20;
	int neuronSize = 10;

	outputHdr.maxImages = layerSize;
	outputHdr.imgWidth = 1;
	outputHdr.imgHeight = layerSize;

	imgHdr.maxImages = 100;
	imgHdr.imgWidth = 32; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 32; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	layerSize = 20;

	neuronSize = 10;

	Layer testObj = Layer(imgHdr, lblHdr, layerSize, neuronSize);

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
					checkWeights += testObj.GetNeurons()[bb].weightOne[cc][dd];
				}
			}

		}

		EXPECT_EQ(1, checkWeights);
	}

}

TEST(Suite002Layer, TestLayer005_InitKaiMing)
{
	ImageHeader outputHdr;
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int layerSize = 20;
	int neuronSize = 10;

	outputHdr.maxImages = layerSize;
	outputHdr.imgWidth = 1;
	outputHdr.imgHeight = layerSize;

	imgHdr.maxImages = 100;
	imgHdr.imgWidth = 32; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 32; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	layerSize = 3;

	neuronSize = 10;

	Layer testObj = Layer(imgHdr, lblHdr, layerSize, neuronSize);

	testObj.InitLayer_KaiMing();

	
	GLdouble checkWeights = 0.00;
	for (int bb = 0; bb < neuronSize; bb += 1)
	{

		for (int cc = 0; cc < imgHdr.imgWidth; cc += 1)
		{
			for (int dd = 0; dd < imgHdr.imgWidth; dd += 1)
			{
				checkWeights += testObj.GetNeurons()[bb].weightOne[cc][dd];
			}

		}
	}

	EXPECT_EQ(1, checkWeights);
	
}

TEST(TestSuite002Layer, TestLayer006_InitXavier)
{
	ImageHeader outputHdr;
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	int labelSize;
	int neuronSize = 20;

	outputHdr.maxImages = neuronSize;
	outputHdr.imgWidth = 1;
	outputHdr.imgHeight = neuronSize;

	imgHdr.maxImages = 100;
	imgHdr.imgWidth = 32; // have to revisit this as initial array size is set at 28 elements
	imgHdr.imgHeight = 32; // have to revisit this as initial array size is set at 28 elements

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 50;

	labelSize = lblHdr.maxLabels;


	Layer testObj = Layer(imgHdr, lblHdr, labelSize, neuronSize);

	testObj.InitLayer_Xavier();

	
	GLdouble checkWeights = 0.00;
	for (int bb = 0; bb < neuronSize; bb += 1)
	{

		for (int cc = 0; cc < imgHdr.imgWidth; cc += 1)
		{
			for (int dd = 0; dd < imgHdr.imgWidth; dd += 1)
			{
				checkWeights += testObj.GetNeurons()[bb].weightOne[cc][dd];
			}

		}
	}

	EXPECT_EQ(1, checkWeights);
	
}

TEST(TestSuite002Layer, DISABLED_TestLayer007_SetLayer)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	std::string imgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string lblFile = "../mnist/t10k-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	Layer * oneLayerNN = new Layer(imgHdr, lblHdr, lblHdr.maxLabels, 10);

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

	oneLayerNN->InitLayer_KaiMing();

	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{

		oneLayerNN->SetLayer(tempImgMatrix[ii]);
	}

	SUCCEED();
}

TEST(TestSuite002Layer, DISABLED_TestLayer008_ForwardPropagation)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	std::string imgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string lblFile = "../mnist/t10k-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	Layer * oneLayerNN = new Layer(imgHdr, lblHdr, lblHdr.maxLabels, 10);

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

TEST(TestSuite002Layer, DISABLED_TestLayer009_StdError)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	std::string imgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string lblFile = "../mnist/t10k-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	imgHdr.maxImages = imgHdr.maxImages - 55000;

	Layer * oneLayerNN = new Layer(imgHdr, lblHdr, lblHdr.maxLabels, 10);

	oneLayerNN->SetImgLbl(getFiles.ReadLabelFile(lblFile, lblHdr));

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
		GLdouble stdError = oneLayerNN->CalculateGeneralError(ii);
		std::cout << "Std Error: " << stdError << std::endl;
	}

	SUCCEED();
}

TEST(TestSuite003Layer, DISABLED_TestLayer010_BackPropagation)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;

	std::string imgFile = "../mnist/train-images.idx3-ubyte";
	std::string lblFile = "../mnist/train-labels.idx1-ubyte";

	UtilityFunctions getFiles;

	imgHdr = getFiles.ReadImageHeader(imgFile);
	lblHdr = getFiles.ReadLabelHeader(lblFile);

	Layer * oneLayerNN = new Layer(imgHdr, lblHdr, lblHdr.maxLabels, 10);

	oneLayerNN->SetImgLbl(getFiles.ReadLabelFile(lblFile, lblHdr));

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

	int epoch = 3;

	for (int hh = 0; hh < epoch; hh += 1)
	{
		std::cout << "epoch: " << hh << std::endl;
		for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
		{

			oneLayerNN->SetLayer(tempImgMatrix[ii]);

			oneLayerNN->ForwardPropagation();
			GLdouble stdError = oneLayerNN->CalculateGeneralError(ii);

			std::cout << "Image index: " << ii << " Current std error: " << stdError << std::endl;

			oneLayerNN->UpdateNeuronWeights(stdError, 0.0001);
		}
	}




	for (int aa = 0; aa < oneLayerNN->GetNeuralSize(); aa += 1)
	{
		getFiles.WriteWeightOutput(aa, oneLayerNN->GetNeurons()[aa].weightOne, imgHdr);
	}

	SUCCEED();
}

TEST(TestSuite002Layer, TestLayer011_Classifier)
{
	GLdouble learningRate = 0.1;
	GLdouble layerBias = 1.00;
	ImageHeader imgHdr;
	ImageHeader imgHdr1;
	ImageHeader imgHdr2;
	ImageHeader imgHdr3;

	LabelHeader lblHdr;
	ImageHeader outputHdr;

	std::string imgFile = "../mnist/train-images.idx3-ubyte";
	std::string lblFile = "../mnist/train-labels.idx1-ubyte";

	int hiddenSize = 300;
	int hiddenSize1 = 80;
	int hiddenSize2 = 40;
	int hiddenSize3 = 20;

	int outputSize = 10;

	UtilityFunctions getFiles;
	lblHdr = getFiles.ReadLabelHeader(lblFile);
	imgHdr = getFiles.ReadImageHeader(imgFile);
	
	imgHdr1.maxImages = imgHdr.maxImages;
	imgHdr1.imgWidth = 1;
	imgHdr1.imgHeight = hiddenSize;

	imgHdr2.maxImages = hiddenSize;
	imgHdr2.imgWidth = 1;
	imgHdr2.imgHeight = hiddenSize1;

	imgHdr3.maxImages = hiddenSize1;
	imgHdr3.imgWidth = 1;
	imgHdr3.imgHeight = hiddenSize2;

	outputHdr.maxImages = hiddenSize2;
	outputHdr.imgWidth = 1;
	outputHdr.imgHeight = hiddenSize3;

	Layer * oneLayerNN = new Layer(imgHdr, lblHdr, lblHdr.maxLabels, hiddenSize);
	Layer * twoLayerNN = new Layer(imgHdr1, lblHdr, lblHdr.maxLabels, hiddenSize1);
	Layer * threeLayerNN = new Layer(imgHdr2, lblHdr, lblHdr.maxLabels, hiddenSize2);
	Layer * fourLayerNN = new Layer(imgHdr3, lblHdr, lblHdr.maxLabels, hiddenSize3);
	Layer * outputLayer = new Layer(outputHdr, lblHdr, lblHdr.maxLabels, outputSize);

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
	twoLayerNN->InitLayer_Xavier();
	threeLayerNN->InitLayer_Xavier();
	fourLayerNN->InitLayer_Xavier();
	outputLayer->InitLayer_Xavier();


	oneLayerNN->SetLayerBias(layerBias);
	twoLayerNN->SetLayerBias(layerBias);
	threeLayerNN->SetLayerBias(layerBias);
	fourLayerNN->SetLayerBias(layerBias);
	outputLayer->SetLayerBias(layerBias);

	// copying image labels for correction 
	oneLayerNN->SetImgLbl(getFiles.ReadLabelFile(lblFile, lblHdr));
	twoLayerNN->SetImgLbl(getFiles.ReadLabelFile(lblFile, lblHdr));
	threeLayerNN->SetImgLbl(getFiles.ReadLabelFile(lblFile, lblHdr));
	fourLayerNN->SetImgLbl(getFiles.ReadLabelFile(lblFile, lblHdr));
	outputLayer->SetImgLbl(getFiles.ReadLabelFile(lblFile, lblHdr));


	// training neural net
	std::cout << "Training neural net..." << std::endl;
	for (int epoch = 0; epoch < 3; epoch += 1)
	{
		int count = 0;
		for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
		{
			// training one hidden layer
			// adding inputs
			oneLayerNN->SetLayer(tempImgMatrix[ii]);
			oneLayerNN->ForwardPropagation();
			//GLdouble stdError = oneLayerNN->CalculateMNISTError(ii);

			twoLayerNN->SetLayer(oneLayerNN->CollateHiddenResult(imgHdr1));
			twoLayerNN->ForwardPropagation();

			threeLayerNN->SetLayer(twoLayerNN->CollateHiddenResult(imgHdr2));
			threeLayerNN->ForwardPropagation();

			fourLayerNN->SetLayer(threeLayerNN->CollateHiddenResult(imgHdr3));
			fourLayerNN->ForwardPropagation();

			// training sigmoid layer
			outputLayer->SetLayer(fourLayerNN->CollateHiddenResult(outputHdr));
			outputLayer->ForwardPropagation();

			GLdouble stdSigmoidError = outputLayer->CalculateMNISTError(ii);
			outputLayer->UpdateNeuronWeights(stdSigmoidError, learningRate);

			GLdouble stdHiddenErrorFour = fourLayerNN->CalculateMNISTError(ii);
			GLdouble errorLayerOutput = outputLayer->TotalLayerError();
			fourLayerNN->BackpropagationHidden(errorLayerOutput, stdHiddenErrorFour, learningRate);

			GLdouble stdHiddenErrorThree = threeLayerNN->CalculateMNISTError(ii);
			GLdouble errorLayerFour = fourLayerNN->TotalLayerError();
			threeLayerNN->BackpropagationHidden(errorLayerFour, stdHiddenErrorThree, learningRate);

			GLdouble stdHiddenErrorTwo = twoLayerNN->CalculateMNISTError(ii);
			GLdouble errorLayerThree = threeLayerNN->TotalLayerError();
			twoLayerNN->BackpropagationHidden(errorLayerThree, stdHiddenErrorTwo, learningRate);

			GLdouble stdHiddenErrorOne = oneLayerNN->CalculateMNISTError(ii);
			GLdouble errorLayerTwo = twoLayerNN->TotalLayerError();
			oneLayerNN->BackpropagationHidden(errorLayerTwo, stdHiddenErrorOne, learningRate);

			std::cout << "Image index: " << ii << std::endl;

			int trainPrediction = outputLayer->GetLayerPrediction();

			if (trainPrediction != outputLayer->GetImgLbl()[ii])
			{
				count++;
			}


			std::cout << "*********************************************************************************************" << std::endl;
			std::cout << "Index: " << ii << " Prediction: " << trainPrediction << " Actual: " << outputLayer->GetImgLbl()[ii] << std::endl;
			std::cout << "*********************************************************************************************" << std::endl;

			std::cout << "Image index: " << ii << std::endl;
		}

		double trainErrorRate;
		trainErrorRate = (double)count / (double)imgHdr.maxImages;
		std::cout.precision(5);
		std::cout << "Error Count: " << count << " % incorrect: " << std::fixed << trainErrorRate << std::endl;
	}
	


	/*
	// loading pre-trained weights
	for (int aa = 0; aa < oneLayerNN->GetLayer()->GetNeuralSize(); aa += 1)
	{
		oneLayerNN->GetLayer()->GetNeurons()[aa].weightOne = getFiles.ReadCSVFile(oneLayerNN->GetLayer()->GetNeuralSize(), imgHdr);

	}
	*/

	// testing neural net
	ImageHeader testImgHdr;
	ImageHeader testOutputHdr;
	LabelHeader testLblHdr;

	std::string testImgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string testLblFile = "../mnist/t10k-labels.idx1-ubyte";

	testImgHdr = getFiles.ReadImageHeader(testImgFile);
	testLblHdr = getFiles.ReadLabelHeader(testLblFile);

	testOutputHdr = outputHdr;

	GLdouble * testImgLbl = new GLdouble[testLblHdr.maxLabels]();
	testImgLbl = getFiles.ReadLabelFile(testLblFile, testLblHdr);

	GLdouble *** testImgMatrix = new GLdouble **[testImgHdr.maxImages]();
	for (int ii = 0; ii < testImgHdr.maxImages; ii += 1)
	{
		testImgMatrix[ii] = new GLdouble*[testImgHdr.imgWidth]();
		for (int jj = 0; jj < testImgHdr.imgHeight; jj += 1)
		{
			testImgMatrix[ii][jj] = new GLdouble[testImgHdr.imgWidth]();
		}
	}

	testImgMatrix = getFiles.ReadImageFile(testImgFile, testImgHdr);

	int errorCount = 0;

	std::cout << "testing neural net..." << std::endl;
	for (int ii = 0; ii < testImgHdr.maxImages; ii += 1)
	{

		oneLayerNN->SetLayer(testImgMatrix[ii]);
		oneLayerNN->ForwardPropagation();

		twoLayerNN->SetLayer(oneLayerNN->CollateHiddenResult(imgHdr1));
		twoLayerNN->ForwardPropagation();
	
		threeLayerNN->SetLayer(twoLayerNN->CollateHiddenResult(imgHdr2));
		threeLayerNN->ForwardPropagation();

		fourLayerNN->SetLayer(threeLayerNN->CollateHiddenResult(imgHdr3));
		fourLayerNN->ForwardPropagation();
		
		outputLayer->SetLayer(fourLayerNN->CollateHiddenResult(outputHdr));
		outputLayer->ForwardPropagation();

		int testPrediction = oneLayerNN->GetLayerPrediction();

		if (testPrediction != testImgLbl[ii])
		{
			errorCount++;
		}

		std::cout << "Index: " << ii << "Prediction: " << testPrediction << " Actual: " << testImgLbl[ii] << std::endl;
	}

	double tempErrorRate;
	tempErrorRate = (double)errorCount / (double)testImgHdr.maxImages;
	std::cout.precision(5);
	std::cout << "Error Count: " << errorCount << " % incorrect: " << std::fixed << tempErrorRate << std::endl;

	SUCCEED();
}

TEST(TestSuite002Layer, DISABLED_TestLayer012_XOR_Gate)
{
	int count = 0;
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	ImageHeader outputHdr;

	//std::string imgFile = "../mnist/train-images.idx3-ubyte";
	//std::string lblFile = "../mnist/train-labels.idx1-ubyte";

	int hiddenSize = 2;
	int outputSize = 1;

	UtilityFunctions getFiles;

	imgHdr.maxImages = 4;
	imgHdr.imgWidth = 2;
	imgHdr.imgHeight = 2;

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 4;

	outputHdr.maxImages = 4;
	outputHdr.imgWidth = 1;
	outputHdr.imgHeight = 2;

	Layer * oneLayerNN = new Layer(imgHdr, lblHdr, lblHdr.maxLabels, hiddenSize);
	Layer * outputLayer = new Layer(outputHdr, lblHdr, lblHdr.maxLabels, outputSize);

	GLdouble * xorLbl = new GLdouble[lblHdr.maxLabels];

	xorLbl[0] = 0.00;
	xorLbl[1] = 1.00;
	xorLbl[2] = 1.00;
	xorLbl[3] = 0.00;
	
	GLdouble trainlbl[4];

	trainlbl[0] = 0.00;
	trainlbl[1] = 1.00;
	trainlbl[2] = 1.00;
	trainlbl[3] = 0.00;


	/*
	for (int ii = 0; ii < lblHdr.maxLabels; ii += 1)
	{
		xorLbl[ii] = 1;
	}
	*/

	

	GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{
		tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
		for (int jj = 0; jj < imgHdr.imgWidth; jj += 1)
		{
			tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgHeight]();
		}
	}

	
	tempImgMatrix[0][0][0] = 1;
	tempImgMatrix[0][0][1] = 1;
	tempImgMatrix[0][1][1] = 1;
	tempImgMatrix[0][0][1] = 1;

	tempImgMatrix[1][0][0] = 0;
	tempImgMatrix[1][0][1] = 0;
	tempImgMatrix[1][1][1] = 1;
	tempImgMatrix[1][0][1] = 1;

	tempImgMatrix[2][0][0] = 1;
	tempImgMatrix[2][0][1] = 1;
	tempImgMatrix[2][1][1] = 0;
	tempImgMatrix[2][0][1] = 0;

	tempImgMatrix[3][0][0] = 0;
	tempImgMatrix[3][0][1] = 0;
	tempImgMatrix[3][1][1] = 0;
	tempImgMatrix[3][0][1] = 0;



	/*
	for (int aa = 0; aa < imgHdr.maxImages; aa += 1)
	{
		for (int bb = 0; bb < imgHdr.imgWidth; bb += 1)
		{
			for (int cc = 0; cc < imgHdr.imgHeight; cc += 1)
			{
				tempImgMatrix[aa][bb][cc] = 1.00;
			}
		}
	}
	*/
	
	
	oneLayerNN->InitLayer_Xavier();
	outputLayer->InitLayer_Xavier();
	oneLayerNN->SetImgLbl(xorLbl);
	outputLayer->SetImgLbl(xorLbl);

	// training neural net
	std::cout << "Training neural net..." << std::endl;
	for (int epoch = 0; epoch < 10; epoch += 1)
	{
		for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
		{

			// adding inputs
			oneLayerNN->SetLayer(tempImgMatrix[ii]);

			// training one hidden layer
			oneLayerNN->ForwardPropagation();
			GLdouble stdError = oneLayerNN->CalculateGeneralError(ii);
			oneLayerNN->UpdateNeuronWeights(stdError, 0.0001);

			GLdouble ** trainHiddenResult = new GLdouble *[outputHdr.imgWidth]();
			for (int aa = 0; aa < outputHdr.imgWidth; aa += 1)
			{
				trainHiddenResult[aa] = new GLdouble[outputHdr.imgHeight]();
			}

			for (int ii = 0; ii < outputHdr.imgWidth; ii += 1)
			{
				for (int jj = 0; jj < outputHdr.imgHeight; jj += 1)
				{
					trainHiddenResult[ii][jj] = oneLayerNN->GetNeurons()[jj].sigmoidOutput;
				}
			}

			// training sigmoid layer
			outputLayer->SetLayer(trainHiddenResult);
			outputLayer->ForwardPropagation();
			
			GLdouble stdSigmoidError = outputLayer->CalculateGeneralError(ii);
			outputLayer->UpdateNeuronWeights(stdSigmoidError, 0.0001);
			
			GLdouble stdHiddenError = oneLayerNN->CalculateGeneralError(ii);
			GLdouble errorLayer = outputLayer->TotalLayerError();

			oneLayerNN->BackpropagationHidden(errorLayer, stdHiddenError, 0.0001);

			std::cout << "Image index: " << ii << std::endl;

			int testPrediction = outputLayer->GetLayerPrediction();
			std::cout << "*********************************************************************************************" << std::endl;
			std::cout << "Index: " << ii << " Prediction: " << outputLayer->GetNeurons()[ii].output << " Actual: " << outputLayer->GetImgLbl()[ii] << std::endl;
			std::cout << "*********************************************************************************************" << std::endl;
		}
		
	}



	/*
	// loading pre-trained weights
	for (int aa = 0; aa < oneLayerNN->GetLayer()->GetNeuralSize(); aa += 1)
	{
		oneLayerNN->GetLayer()->GetNeurons()[aa].weightOne = getFiles.ReadCSVFile(oneLayerNN->GetLayer()->GetNeuralSize(), imgHdr);

	}
	*/
	
	// testing neural net
	ImageHeader testImgHdr;
	ImageHeader testOutputHdr;
	LabelHeader testLblHdr;

	//std::string testImgFile = "../mnist/t10k-images.idx3-ubyte";
	//std::string testLblFile = "../mnist/t10k-labels.idx1-ubyte";
	//testImgHdr = getFiles.ReadImageHeader(testImgFile);
	//testLblHdr = getFiles.ReadLabelHeader(testLblFile);

	testImgHdr.maxImages = 4;
	testImgHdr.imgWidth = 2;
	testImgHdr.imgHeight = 2;

	testLblHdr.maxLabels = 4;

	testOutputHdr.maxImages = 4;
	testOutputHdr.imgWidth = 1;
	testOutputHdr.imgHeight = 2;

	int * testImgLbl = new int[testLblHdr.maxLabels]();
	//testImgLbl = getFiles.ReadLabelFile(testLblFile, testLblHdr);

	testImgLbl[0] = 0;
	testImgLbl[1] = 1;
	testImgLbl[2] = 1;
	testImgLbl[3] = 0;

	GLdouble *** testImgMatrix = new GLdouble **[testImgHdr.maxImages]();
	for (int ii = 0; ii < testImgHdr.maxImages; ii += 1)
	{
		testImgMatrix[ii] = new GLdouble*[testImgHdr.imgWidth]();
		for (int jj = 0; jj < testImgHdr.imgHeight; jj += 1)
		{
			testImgMatrix[ii][jj] = new GLdouble[testImgHdr.imgWidth]();
		}
	}
	/*
	testImgMatrix = getFiles.ReadImageFile(testImgFile, testImgHdr);
	*/

	testImgMatrix[0][0][0] = 1;
	testImgMatrix[0][0][1] = 1;
	testImgMatrix[0][1][1] = 1;
	testImgMatrix[0][0][1] = 1;

	testImgMatrix[1][0][0] = 0;
	testImgMatrix[1][0][1] = 0;
	testImgMatrix[1][1][1] = 0;
	testImgMatrix[1][0][1] = 0;

	testImgMatrix[2][0][0] = 1;
	testImgMatrix[2][0][1] = 1;
	testImgMatrix[2][1][1] = 0;
	testImgMatrix[2][0][1] = 0;

	testImgMatrix[3][0][0] = 0;
	testImgMatrix[3][0][1] = 0;
	testImgMatrix[3][1][1] = 1;
	testImgMatrix[3][0][1] = 1;
	

	int errorCount = 0;

	std::cout << "testing neural net..." << std::endl;
	for (int ii = 0; ii < testImgHdr.maxImages; ii += 1)
	{

		oneLayerNN->SetLayer(testImgMatrix[ii]);
		oneLayerNN->ForwardPropagation();

		GLdouble ** hiddenResult = new GLdouble *[testOutputHdr.imgWidth]();
		for (int aa = 0; aa < testOutputHdr.imgHeight; aa += 1)
		{
			hiddenResult[aa] = new GLdouble[testOutputHdr.imgHeight]();
		}

		for (int ii = 0; ii < testOutputHdr.imgWidth; ii += 1)
		{
			for (int jj = 0; jj < testOutputHdr.imgHeight; jj += 1)
			{
				hiddenResult[ii][jj] = oneLayerNN->GetNeurons()[jj].sigmoidOutput;
			}
		}


		outputLayer->SetLayer(hiddenResult);

		outputLayer->ForwardPropagation();

		int testPrediction = testImgLbl[ii];

		if (testPrediction != testImgLbl[ii])
		{
			errorCount++;
		}
		std::cout << "*********************************************************************************************" << std::endl;
		std::cout << "Index: " << ii << "Prediction: " << testPrediction << " Actual: " << testImgLbl[ii] << std::endl;
		std::cout << "*********************************************************************************************" << std::endl;
	}

	double tempErrorRate;
	tempErrorRate = (double)errorCount / (double)testImgHdr.maxImages;
	std::cout.precision(5);
	std::cout << "Error Count: " << errorCount << " % incorrect: " << std::fixed << tempErrorRate << std::endl;
	
	delete[] xorLbl;
	delete[] tempImgMatrix;
	delete[] testImgLbl;
	delete[] testImgMatrix;

	SUCCEED();
}



TEST(TestSuite002Layer, DISABLED_TestLayer013_Worked_Example)
{
	
	ImageHeader imgHdr;
	LabelHeader lblHdr;
	ImageHeader outputHdr;

	//std::string imgFile = "../mnist/train-images.idx3-ubyte";
	//std::string lblFile = "../mnist/train-labels.idx1-ubyte";

	int hiddenSize = 2;
	int outputSize = 2;

	UtilityFunctions getFiles;

	imgHdr.maxImages = 1;
	imgHdr.imgWidth = 1;
	imgHdr.imgHeight = 2;

	lblHdr.magicNumber = 0;
	lblHdr.maxLabels = 1;

	outputHdr.maxImages = 1;
	outputHdr.imgWidth = 1;
	outputHdr.imgHeight = hiddenSize;

	Layer * oneLayerNN = new Layer(imgHdr, lblHdr, lblHdr.maxLabels, hiddenSize);
	Layer * outputLayer = new Layer(outputHdr, lblHdr, lblHdr.maxLabels, outputSize);

	

	GLdouble * xorLbl = new GLdouble[lblHdr.maxLabels]();	
	for (int ii = 0; ii < lblHdr.maxLabels; ii += 1)
	{
		xorLbl[ii] = 0.01;
	}
	
	oneLayerNN->SetImgLbl(xorLbl);
	outputLayer->SetImgLbl(xorLbl);

	GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
	for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
	{
		tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
		for (int jj = 0; jj < imgHdr.imgWidth; jj += 1)
		{
			tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgHeight]();
		}
	}

	tempImgMatrix[0][0][0] = 0.05;
	tempImgMatrix[0][0][1] = 0.10;
	
	/*
	for (int aa = 0; aa < imgHdr.maxImages; aa += 1)
	{
		for (int bb = 0; bb < imgHdr.imgWidth; bb += 1)
		{
			for (int cc = 0; cc < imgHdr.imgHeight; cc += 1)
			{
				if (cc < 0)
				{
					tempImgMatrix[aa][bb][cc] = 1.00;
				}
				else
				{
					tempImgMatrix[aa][bb][cc] = 0.00;
				}

			}
		}
	}
	*/

	//oneLayerNN->InitLayer_Xavier();
	//outputLayer->InitLayer_Xavier();

	oneLayerNN->GetNeurons()[0].weightOne[0][0] = 0.15;
	oneLayerNN->GetNeurons()[0].weightOne[0][1] = 0.20;
	oneLayerNN->GetNeurons()[1].weightOne[0][0] = 0.25;
	oneLayerNN->GetNeurons()[1].weightOne[0][1] = 0.30;

	oneLayerNN->GetNeurons()[0].bias = 0.35;
	oneLayerNN->GetNeurons()[1].bias = 0.35;


	outputLayer->GetNeurons()[0].weightOne[0][0] = 0.40;
	outputLayer->GetNeurons()[0].weightOne[0][1] = 0.45;
	outputLayer->GetNeurons()[1].weightOne[0][0] = 0.50;
	outputLayer->GetNeurons()[1].weightOne[0][1] = 0.55;

	outputLayer->GetNeurons()[0].bias = 0.60;
	outputLayer->GetNeurons()[1].bias = 0.60;


	// training neural net
	std::cout << "Training neural net..." << std::endl;
	for (int epoch = 0; epoch < 1; epoch += 1)
	{
		for (int ii = 0; ii < imgHdr.maxImages; ii += 1)
		{
			// adding inputs
			oneLayerNN->SetLayer(tempImgMatrix[ii]);

			// training one hidden layer
			oneLayerNN->ForwardPropagation();

			GLdouble ** trainHiddenResult = new GLdouble *[outputHdr.imgWidth]();
			for (int aa = 0; aa < outputHdr.imgWidth; aa += 1)
			{
				trainHiddenResult[aa] = new GLdouble[outputHdr.imgHeight]();
			}

			for (int ii = 0; ii < outputHdr.imgWidth; ii += 1)
			{
				for (int jj = 0; jj < outputHdr.imgHeight; jj += 1)
				{
					trainHiddenResult[ii][jj] = oneLayerNN->GetNeurons()[jj].sigmoidOutput;
				}
			}

			// training sigmoid layer
			outputLayer->SetLayer(trainHiddenResult);
			outputLayer->ForwardPropagation();

			GLdouble stdOutputError = 0.00;
			stdOutputError = outputLayer->CalculateGeneralError(ii);
			outputLayer->UpdateNeuronWeights(stdOutputError, 0.5);
			
			GLdouble stdHiddenError = oneLayerNN->CalculateGeneralError(ii);

			GLdouble errorLayer = outputLayer->TotalLayerError();

			oneLayerNN->BackpropagationHidden(errorLayer, stdHiddenError, 0.5);

			std::cout << "Image index: " << ii << std::endl;

			int testPrediction = outputLayer->GetLayerPrediction();

			std::cout << "Index: " << ii << " Prediction: " << testPrediction << " Actual: " << outputLayer->GetImgLbl()[ii] << std::endl;

		}

	}



	/*
	// loading pre-trained weights
	for (int aa = 0; aa < oneLayerNN->GetLayer()->GetNeuralSize(); aa += 1)
	{
		oneLayerNN->GetLayer()->GetNeurons()[aa].weightOne = getFiles.ReadCSVFile(oneLayerNN->GetLayer()->GetNeuralSize(), imgHdr);

	}
	*/
	/*
	// testing neural net
	ImageHeader testImgHdr;
	ImageHeader testOutputHdr;
	LabelHeader testLblHdr;

	std::string testImgFile = "../mnist/t10k-images.idx3-ubyte";
	std::string testLblFile = "../mnist/t10k-labels.idx1-ubyte";

	testImgHdr = getFiles.ReadImageHeader(testImgFile);
	testLblHdr = getFiles.ReadLabelHeader(testLblFile);

	testOutputHdr = outputHdr;

	int * testImgLbl = new int[testLblHdr.maxLabels]();
	testImgLbl = getFiles.ReadLabelFile(testLblFile, testLblHdr);

	GLdouble *** testImgMatrix = new GLdouble **[testImgHdr.maxImages]();
	for (int ii = 0; ii < testImgHdr.maxImages; ii += 1)
	{
		testImgMatrix[ii] = new GLdouble*[testImgHdr.imgWidth]();
		for (int jj = 0; jj < testImgHdr.imgHeight; jj += 1)
		{
			testImgMatrix[ii][jj] = new GLdouble[testImgHdr.imgWidth]();
		}
	}

	testImgMatrix = getFiles.ReadImageFile(testImgFile, testImgHdr);

	int errorCount = 0;

	std::cout << "testing neural net..." << std::endl;
	for (int ii = 0; ii < testImgHdr.maxImages; ii += 1)
	{

		oneLayerNN->SetLayer(testImgMatrix[ii]);
		oneLayerNN->ForwardPropagation();

		GLdouble ** hiddenResult = new GLdouble *[testOutputHdr.imgWidth]();
		for (int aa = 0; aa < testOutputHdr.imgHeight; aa += 1)
		{
			hiddenResult[aa] = new GLdouble[testOutputHdr.imgHeight]();
		}

		for (int ii = 0; ii < testOutputHdr.imgWidth; ii += 1)
		{
			for (int jj = 0; jj < testOutputHdr.imgHeight; jj += 1)
			{
				hiddenResult[ii][jj] = oneLayerNN->GetNeurons()[jj].sigmoidOutput;
			}
		}


		outputLayer->SetLayer(hiddenResult);

		outputLayer->ForwardPropagation();

		int testPrediction = oneLayerNN->GetLayerPrediction();

		if (testPrediction != testImgLbl[ii])
		{
			errorCount++;
		}

		std::cout << "Index: " << ii << "Prediction: " << testPrediction << " Actual: " << testImgLbl[ii] << std::endl;
	}

	double tempErrorRate;
	tempErrorRate = (double)errorCount / (double)testImgHdr.maxImages;
	std::cout.precision(5);
	std::cout << "Error Count: " << errorCount << " % incorrect: " << std::fixed << tempErrorRate << std::endl;
	*/

	SUCCEED();
}