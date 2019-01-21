#include "pch.h"

#include "Neuron.h"
#include "Layer.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(NeuronLoad, NeuronSuite) {
	Neuron a_neuron;
	EXPECT_EQ(a_neuron.bias, 0);
}

TEST(LayerLoad, LayerSuite) {
	Layer a_layer;
	EXPECT_EQ(a_layer.GetLayerSize(), 0);
}