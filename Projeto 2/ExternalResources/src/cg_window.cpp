#include <cg_window.hpp>

namespace cgicmc {

	// Window constructor
	Window::Window() {
		// initialize and configure the glfw
		glfwInit();
		glfwWindowHint(GLFW_SAMPLES, 4); // apply 4x antialiasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // select OpenGL version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// initialize the translation values
		x = 0;
		y = 0;

		// initialize the rotation values
		stopRotation = false;
		spacePressed = false;
		rotationAngle = 0;
		rotationSpeed = 0.01f;
	}

	// Window destructor
	Window::~Window() { glfwTerminate(); }

	// vertex shader source string
	const char *vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"

		"uniform mat4 transform;\n"

		"void main() {\n"
		"   gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// fragment shader source string
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec3 FragColor;\n"
		"void main() {\n"
		"   FragColor = vec3(1.0f, 0.0f, 0.0f);\n"
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

		// escape key: close process
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(_window, true);

		// translation keys
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
			y += DIST_VAR; // W: move up
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
			x -= DIST_VAR; // A: mode left
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
			y -= DIST_VAR; // S: move down
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
			x += DIST_VAR; // D: move right

		// rotation keys
		// condition to avoid speed changing when rotation is halted
		if (!stopRotation) {
			// increase rotation speed
			if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
				rotationSpeed += SPEED_VAR;
			// decrease rotation speed
			if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
				rotationSpeed -= SPEED_VAR;
		}

		// stop rotation when space key is pressed
		if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			// to avoid repeated changes with a single key press
			if (!spacePressed) {
				spacePressed = true;
				stopRotation = !stopRotation;
			}
		} else {
			spacePressed = false;
		}
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

		// get the "transform" variable location (to apply transformations later)
		GLuint shaderTransform = glGetUniformLocation(shaderProgram, "transform");

		// window main loop
		while (!glfwWindowShouldClose(_window)) {
			
			// process the input commands
			processInput(_window);

			// DEBUG: print values
			//std::cout<<"X: "<<x<<"  Y: "<<y<<"  angle: "<<rotationAngle<<"  speed: "<<rotationSpeed<<' '<<stopRotation<<std::endl;

			// apply the rotation (if not stopped)
			if (!stopRotation) {
				rotationAngle += rotationSpeed;
			}

			// calculate the translation matrix
			glm::mat4 translationMatrix = glm::mat4(1.0f);
			translationMatrix[0][3] = x;
			translationMatrix[1][3] = y;

			// calculate the rotation matrix
			glm::mat4 rotationMatrix = glm::mat4(1.0f);
			float sin = glm::sin(rotationAngle);
			float cos = glm::cos(rotationAngle);
			rotationMatrix[0][0] = cos;
			rotationMatrix[0][1] = sin;
			rotationMatrix[1][0] = -sin;
			rotationMatrix[1][1] = cos;

			// apply the transformations
			glUniformMatrix4fv(shaderTransform, 1, GL_TRUE, glm::value_ptr(rotationMatrix * translationMatrix));

			// paint the background
			glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
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