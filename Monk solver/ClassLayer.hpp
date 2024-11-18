#include <iostream>
#include <vector>

const int hidden_number;
const int inputsize;
const int outputsize;
std::vector<int, hidden_number> LayerSizes = {}

class Layer {
public:
    virtual ~Layer() = default;
    virtual int NumNode() const = 0;
    virtual Layer* GetPrevLayer() const = 0;
};

template<class T = Layer>
class HiddenLayer : public Layer {
public:
    HiddenLayer() : NumNodes_1(0), PrevLayer(nullptr) {}
    HiddenLayer(int NumNodes, T* LayerPrecedente) 
        : NumNodes_1(NumNodes), PrevLayer(LayerPrecedente) {}

    int NumNode() const override { return NumNodes_1; }

    Layer* GetPrevLayer() const override { return PrevLayer; }

protected:
    T* PrevLayer;

private:
    int NumNodes_1;
};



// InputLayer derivato da Layer
class InputLayer : public Layer {
public:
    InputLayer() : NumNodes_1(0) {}
    InputLayer(int NumNodes) : NumNodes_1(NumNodes) {}

    int NumNode() const override { return NumNodes_1; }
    Layer* GetPrevLayer() const override { return nullptr; }

private:
    int NumNodes_1 = inputsize;
};





class MLP 
{
	public:	
		MLP(){}
		MLP(InputLayer *I, Layer *O):
			OutputLayer(O), InLayer(I);
	
	
	private:
		//std::vector<Layer*> LayerPointers;
		Layer *OutputLayer;
		Layer *InLayer;
	
	
}



/*
template<class T>
class MLP
{
	public:
		MLP(){}
		MLP(InputLayer *a, Layer *Output, T *LayerPointer):
					LayerInput(a), LayerOutput(Output)
					{
						
						LayerPointer = 
						while(LayerPointer != NULL)
						{
							LayersPointer.push_back();
						}
						
						
						
						
					}















	private:
		std::vector<Layer*> LayersPointer;
		InputLayer *LayerInput;
		Layer *LayerOutput;
}






MLP sempronio(3, 2, [3.4.5], )




/*main


std::vector<int> Dati;

InputLayer *a = new InputLayer(std::size(Dati));
Layer *b = new Layer(16, a);
Layer *c = new Layer(16, b);
Layer *output = new Layer(2, c);

MLP *Modello = new Modello()


Modello.train();

Modello.
* 
*/
