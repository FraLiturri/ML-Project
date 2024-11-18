#include <iostream>
#include <vector>

const int hidden_number = 3;
const int inputsize;
const int outputsize;

std::vector<int> LayerSizes(hidden_number); 

class Layer
{
public:
	virtual ~Layer() = default;
	virtual int NumNode() const = 0;
	virtual Layer *GetPrevLayer() const = 0;
};

template <class T = Layer>
class HiddenLayer : public Layer
{
public:
	HiddenLayer() : NumNodes_1(0), PrevLayer(nullptr) {}
	HiddenLayer(int NumNodes, T *LayerPrecedente)
		: NumNodes_1(NumNodes), PrevLayer(LayerPrecedente) {}

	int NumNode() const override { return NumNodes_1; }

	Layer *GetPrevLayer() const override { return PrevLayer; }

protected:
	T *PrevLayer;

private:
	int NumNodes_1;
};

// InputLayer derivato da Layer
class InputLayer : public Layer
{
public:
	InputLayer() : NumNodes_1(0) {}
	InputLayer(int NumNodes) : NumNodes_1(NumNodes) {}

	int NumNode() const override { return NumNodes_1; }
	Layer *GetPrevLayer() const override { return nullptr; }

private:
	int NumNodes_1 = inputsize;
};

class MLP
{
public:
	MLP() {}
	MLP(InputLayer *I, Layer *O) : OutputLayer(O), InLayer(I) {};

private:
	// std::vector<Layer*> LayerPointers;
	Layer *OutputLayer;
	Layer *InLayer;
};
