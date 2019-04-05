#include <cg_window.hpp>

namespace cgicmc {

	// Window constructor
	Window::Window() {
		glfwInit();
		glfwWindowHint(GLFW_SAMPLES, 4); // apply 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // select OpenGL version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	// Window destructor
	Window::~Window() { glfwTerminate(); }

	// vertex shader source string
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// fragment shader source string
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec3 FragColor;\n"
		"void main() {\n"
		"   FragColor = vec3(1.0f, 0.5f, 0.2f);\n"
		"}\n\0";

	// program rendering pipeline attaching all shaders
	GLint createRenderingPipeline() {

		// create the vertex shader using vertexShaderSource
		GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, GL_TRUE, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// create the fragment shader using fragmentShaderSource
		GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, GL_TRUE, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		// create the program using the shaders
		GLint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// delete the shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}

	// create a single window with the specified size
	void Window::createWindow(int width, int height) {
		_window = glfwCreateWindow(width, height, "CG 2019", NULL, NULL);
		if (_window == NULL) {
			std::cout << "Failed to create GLFW window\n";
			glfwTerminate();
			exit(-1);
		}
		glfwMakeContextCurrent(_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n";
			exit(-2);
		}
		glViewport(0, 0, width, height);
	}

	// process the useful inputs
	void Window::processInput(GLFWwindow *_window) {
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(_window, true);
	}

	void Window::run() {

		// build and compile our shader program
		GLint shaderProgram = createRenderingPipeline();
		glUseProgram(shaderProgram);

		// set up the vertices points
		float vertices[] = {
			// bottom triangle	
			0.0f, -0.5f, 0.0f, // left  
			0.3f, -0.5f, 0.0f, // right 
			0.0f,  0.0f, 0.0f,  // top   
			// right triangle			
			0.0f,  0.0f, 0.0f,  // left
			0.5f,  0.0f, 0.0f,  // right
			0.5f,  0.3f, 0.0f,   // top 
			// top triangle	
			-0.3f,  0.5f, 0.0f,  // left
			0.0f,  0.5f, 0.0f,  // right
			0.0f,  0.0f, 0.0f,   // top 
			// left triangle	
			-0.5f,  0.0f, 0.0f,  // left
			-0.5f,  -0.3f, 0.0f,  // right
			0.0f,  0.0f, 0.0f,   // top  
		};

		// generate and bind the Vertex Array Object (VAO)
		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// generate and bind the Vertex Buffer Object (VAO)
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// send our vertices data to the OpenGL buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// specify that our coordinate data is going into attribute index 0, and contains 3 floats per vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

		// enable attribute index 0 as being used
		glEnableVertexAttribArray(0);

		// window main loop
		while (!glfwWindowShouldClose(_window)) {
			// process the input commands
			processInput(_window);

			// paint the background
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// draw the triangles
			glDrawArrays(GL_TRIANGLES, 0, 12);

			// swap the buffers to make any changes visible
			glfwSwapBuffers(_window);

			// process remaining events
			glfwPollEvents();
		}

		// de-allocate all resources once they've outlived their purpose:
		glDeleteVertexArrays(GL_TRUE, &VAO);
		glDeleteBuffers(GL_TRUE, &VBO);
	}
}