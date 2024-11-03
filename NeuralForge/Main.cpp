

#include "Common.hpp"




#include "Shader.hpp"



#include "Camera.hpp"



#include "Polygons2D.hpp"
#include "Delaunay2D.hpp"

#include "Settings.hpp"

#include "NF.hpp"







int main(void)
{
	GLFWwindow* window = initialize();

	/*glDebugMessageCallback(MessageCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);*/






	Shader shader("resources/shaders/shader1.shader");
	shader.Bind();

	Camera camera(window);


	//Settings settings(camera);


	Polygons2D p2d;






	
	TimeCounter mainCounter;




	vector<vector<float>> X = { { 1, 2, 3, 2.5 },{2.0, 5.0, -1.0, 2.0}, {-1.5, 2.7, 3.3, -0.8} };
	vector<vector<float>> W1_ = { { 0.2, 0.8, -0.5, 1.0},{0.5, -0.91, 0.26, -0.5},{-0.26, -0.27, 0.17, 0.87} };
	vector<vector<float>> W1 = transpose(W1_);
	vector<float> b1 = { 2,3,0.5 };


	vector<vector<float>> W2_ = { {0.1, -0.14, 0.5}, {-0.5, 0.12, -0.33}, {-0.44, 0.73, -0.13} };
	vector<vector<float>> W2 = transpose(W2_);
	vector<float> b2 = { -1, 2, -0.5 };

	vector<vector<float>> outputLayer1, outputLayer2;

	outputLayer1 = neuronMult(X, W1, b1);
	outputLayer2 = neuronMult(outputLayer1, W2, b2);


	//print(X);
	print(outputLayer1);
	print(outputLayer2);


	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng(seed);

	// Standard normal distribution (mean = 0, stddev = 1)
	std::normal_distribution<float> dist(0.0f, 1.0f);

	// Generate a 4x3 matrix of random numbers
	std::vector<std::vector<float>> weights(4, std::vector<float>(3));

	for (size_t i = 0; i < weights.size(); ++i) {
		for (size_t j = 0; j < weights[i].size(); ++j) {
			weights[i][j] = dist(rng);
		}
	}

	print(weights);


	mainCounter.endCounter();










	return 0;


	//getPos(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int locationOrtho = glGetUniformLocation(shader.ID, "u_OrthoProjection");
	int colorLocation = glGetUniformLocation(shader.ID, "u_Color");

	camera.updateCamera();
	glUniformMatrix4fv(locationOrtho, 1, GL_FALSE, camera.orthoMatrix.data());





	//glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);

	
	while (!glfwWindowShouldClose(window))
	{

		if (isRunning)
		{


			glClearColor(0.035f, 0.065f, 0.085f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			//2d objects

			glUniform4f(colorLocation, 40.0f / 255.0f, 239.9f / 255.0f, 239.0f / 255.0f, 0.6);
			p2d.draw();


			camera.updateCamera();
			glUniformMatrix4fv(locationOrtho, 1, GL_FALSE, camera.orthoMatrix.data());



		}
		//settings.write();

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


