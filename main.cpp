#include <iostream>
#include <string>
#include <GL/freeglut.h>
#include "src/UtilityFunctions.h"
#include "src/Layer.h"
#include "src/Convolution.h"
#include "src/Perceptron.h"

int count = 0;
ImageHeader imgHdr;
LabelHeader lblHdr;
Perceptron * oneLayerNN;



void GetHeaders()
{
    UtilityFunctions getFiles;
    std::string imgFile = "../../mnist/train-images.idx3-ubyte";
    std::string lblFile = "../../mnist/train-labels.idx1-ubyte";

    std::cout << "imgFile path: " << imgFile << std::endl;
    std::cout << "lblFile path: " << lblFile << std::endl;

    imgHdr = getFiles.ReadImageHeader(imgFile);
    lblHdr = getFiles.ReadLabelHeader(lblFile);


}

void TrainModel(Perceptron * & perceptronOne, int layerSize, int neuronSize)
{
    std::cout << "Running Training..." << std::endl;

    UtilityFunctions getFiles;
    std::string imgFile = "../../mnist/train-images.idx3-ubyte";
    std::string lblFile = "../../mnist/train-labels.idx1-ubyte";

    Convolution * convolveOne;

    perceptronOne->SetLabel(getFiles.ReadLabelFile(lblFile, lblHdr), lblHdr);

    GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
        }
    }

    tempImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

    perceptronOne->InitLayer(imgHdr, lblHdr, layerSize,neuronSize);
    perceptronOne->InitSigmoidLayer(imgHdr, neuronSize);

    for(int epoch = 0; epoch < 10; epoch += 1)
    {
        convolveOne = new Convolution(imgHdr, layerSize, neuronSize);

        for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
        {
            // my apologies will refactor when time permits
            perceptronOne->SetLayer(convolveOne->MaxPooling(convolveOne->GaussianFilter(tempImgMatrix[ii], imgHdr, layerSize, neuronSize), imgHdr, layerSize, neuronSize), imgHdr, layerSize, neuronSize);
        }

        perceptronOne->ForwardPropagation(imgHdr, layerSize, neuronSize);
        perceptronOne->CalculateOutput(imgHdr, layerSize, neuronSize);

        // calculate error and update weights
        for(int hh = 0; hh < layerSize; hh += 1)
        {
            for(int ii = 0; ii < 10; ii += 1)
            {
                GLdouble stdError;
                stdError = perceptronOne->CalculateError(imgHdr, hh, ii);
                perceptronOne->UpdateNeuronWeights(imgHdr, hh, ii, stdError, 0.001);
            }
        }

    }


    delete [] tempImgMatrix;
}

void GetTestingHeaders()
{
    UtilityFunctions getFiles;
    std::string imgFile = "../../mnist/t10k-images.idx3-ubyte";
    std::string lblFile = "../../mnist/t10k-labels.idx1-ubyte";

    imgHdr = getFiles.ReadImageHeader(imgFile);
    lblHdr = getFiles.ReadLabelHeader(lblFile);
}


void TestModel(Perceptron * layerOne, int layerSize, int neuronSize)
{
    UtilityFunctions getFiles;
    std::string imgFile = "../../mnist/t10k-images.idx3-ubyte";
    std::string lblFile = "../../mnist/t10k-labels.idx1-ubyte";

    GLdouble * testImgLbl = new GLdouble[lblHdr.maxLabels]();
    testImgLbl = getFiles.ReadLabelFile(lblFile, lblHdr);

    GLdouble *** testImgMatrix = new GLdouble **[imgHdr.maxImages]();
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        testImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            testImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
        }
    }

    testImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

    int errorCount = 0;

    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {

        layerOne->SetLayer(testImgMatrix[ii], imgHdr, layerSize, neuronSize);
        layerOne->ForwardPropagation(imgHdr, layerSize, neuronSize);
        layerOne->CalculateOutput(imgHdr, layerSize, neuronSize);

        int layerPrediction = layerOne->GetLayerPrediction(layerSize, neuronSize);

        if(layerPrediction != testImgLbl[ii])
        {
            errorCount++;
        }

        std::cout << "Prediction: " << layerPrediction << " Actual: " << testImgLbl[ii] << std::endl;


    }
    double tempErrorRate;
    tempErrorRate = (double) errorCount / imgHdr.maxImages;
    std::cout.precision(5);
    std::cout << "Error Count: " << errorCount << " % incorrect: " << std::fixed << tempErrorRate << std::endl;
}

void display()
{

    UtilityFunctions uf;
    std::string imgFile = "../../mnist/train-images.idx3-ubyte";
    std::string lblFile = "../../mnist/train-labels.idx1-ubyte";

    GetHeaders();

    GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
        }
    }

    tempImgMatrix = uf.ReadImageFile(imgFile, imgHdr);

    uf.DisplayImage(tempImgMatrix[count % imgHdr.maxImages], imgHdr);

    delete [] tempImgMatrix;

}

void reshape(int w, int h)
{
    GLdouble width = w;
    GLdouble height = h;

    glViewport(0, 0, w, h);
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) h = 1;
    GLfloat ratio = 1.0f * w / h;
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    //gluPerspective(45, ratio, 1, 500);
    gluOrtho2D(0.0, (1.0/width)* imgHdr.imgWidth, 0.0, (1.0/height)*imgHdr.imgHeight);
    //gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);

    glutInitWindowSize(256, 256); /* 760 x 280 pixel graphics display window */

    glutInitWindowPosition(0,0); /* place window top left on display */

    glutCreateWindow("Image handler"); /* graphics window title */
    glClearColor(0.0, 0.0, 0.0, 0.0); /* set up to draw on black background */

    glutDisplayFunc(display);
}

int main(int argc, char** argv)
{
    GetHeaders();
    oneLayerNN = new Perceptron(imgHdr, lblHdr, 2, 10);

    TrainModel(oneLayerNN, 2, 10);
    GetTestingHeaders();
    TestModel(oneLayerNN, 2, 10);

    return 0;
}

/*
int main(int argc, char** argv)
{


    glutInit(&argc, argv);

    init();
    glutMainLoop();
    return 0;
}
*/
