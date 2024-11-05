#pragma once

#include "Common.hpp"
//[[noreturn]] tells the compiler that the function does not return to the caller
[[noreturn]] void terminate_with_error(const std::string& message) {
	std::cerr << "Error: " << message << std::endl;
	std::exit(EXIT_FAILURE);
}

float dot(const std::vector<float>& input1, const std::vector<float>& input2) {

	if (input1.size() != input2.size())
	{
		terminate_with_error("Vectors must be of the same size");
	}

	float output = 0.0f;
	for (size_t i = 0; i < input1.size(); ++i)
	{
		output += input1[i] * input2[i];
	}
	return output;
}


vector<vector<float>> matMult(const vector<vector<float>>& input1, const vector<vector<float>>& input2) {

	if (input1[0].size() != input2.size())
	{
		terminate_with_error("Error: Input1 row size must be equal to input2 column size");
	}

	// Initializes output matrix with zeros and with dimensions [input1.size(),input2[0].size()]
	vector<vector<float>> output(input1.size(), std::vector<float>(input2[0].size(), 0.0f));

	for (size_t i = 0; i < input1.size(); ++i)
	{
		for (size_t j = 0; j < input1[0].size(); ++j)
		{
			for (size_t k = 0; k < input2[0].size(); ++k)
			{
				output[i][k] += input1[i][j] * input2[j][k];
			}
		}
	}
	return output;
}

//TEST IF USING REFERENCES INSIDE LOOPS REDUCES INDEXING OVERHEAD

vector<vector<float>> neuronMult(const vector<vector<float>>& inputs, const vector<vector<float>>& weights, const vector<float>& biases) {

	if (inputs[0].size() != weights.size())
	{
		terminate_with_error("Error: Inputs row size must be equal to weights column size");
	}
	if (weights[0].size() != biases.size())
	{
		terminate_with_error("Error: Biases size must be equal to weights column size");
	}

	// Initializes output matrix with zeros and with dimensions [input1.size(),input2[0].size()]
	vector<vector<float>> output(inputs.size(), std::vector<float>(weights[0].size(), 0.0f));

	for (size_t i = 0; i < inputs.size(); ++i)
	{
		//summing the biases
		for (size_t k = 0; k < weights[0].size(); ++k) {
			output[i][k] = biases[k];
		}

		for (size_t j = 0; j < inputs[0].size(); ++j)
		{
			for (size_t k = 0; k < weights[0].size(); ++k)
			{
				output[i][k] += inputs[i][j] * weights[j][k];
			}
		}
	}
	return output;
}

vector<vector<float>> transpose(const vector<vector<float>>& input) {

	// Initialize output matrix with dimensions [input[0].size()][input.size()]
	vector<vector<float>> output(input[0].size(), std::vector<float>(input.size(), 0.0f));

	for (size_t i = 0; i < input.size(); ++i)
	{
		for (size_t j = 0; j < input[0].size(); ++j)
		{
			output[j][i] = input[i][j];
		}
	}
	return output;
}


//Ideal if ReLU
std::vector<std::vector<float>> createKaimingWeights(size_t rows, size_t columns) {
	//n_in = rows (neurons previous layer), n_out = columns (neurons current layer)

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//std::mt19937 rng(seed);
	std::mt19937 rng(0);
	float stddev = std::sqrt(2.0f / rows);
	std::normal_distribution<float> dist(0.0f, stddev);

	std::vector<std::vector<float>> weights(rows, std::vector<float>(columns));
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < columns; ++j) {
			weights[i][j] = dist(rng);
		}
	}
	return weights;
}

void ReLU(vector<vector<float>>& input) {
	for (auto& row : input) {
		for (auto& value : row) {
			value = std::max(0.0f, value);
		}
	}
}

void softmax(std::vector<float>& input) {
	// Find the maximum value in the input for numerical stability
	float max_input = *std::max_element(input.begin(), input.end());

	// Exponentiate each element and compute the sum
	float sum = 0.0f;
	for (auto& i : input) {
		i = std::exp(i - max_input);
		sum += i;
	}

	// Normalize the exponentials to get probabilities
	for (auto& i : input) {
		i /= sum;
	}
}


struct NF {
	vector<vector<float>> input;
	vector<vector<vector<float>>> weights;
	vector<vector<float>> biases;

	vector<vector<float>> currentOutput;

	NF(vector<vector<float>> input_, vector<int> neuronsPerLayer) :input(input_)
	{
		currentOutput = input;

		int n_layers = neuronsPerLayer.size();
		int n_batches = input.size();

		for (size_t i = 0; i < neuronsPerLayer.size(); i++)
		{
			//esto está mal, solo es valida para la creación. Para un forward normal no lo tiene que rehacer
			weights.push_back(createKaimingWeights(currentOutput[0].size(),neuronsPerLayer[i]));
			biases.push_back(weig)
			

		}
	};

};