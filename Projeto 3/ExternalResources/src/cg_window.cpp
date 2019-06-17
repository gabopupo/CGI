#include <cg_window.hpp>

#include "model.h"

glm::vec3 front;
bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;
float lastX;
float lastY;
float fov = 45.0f;

// Mouse functions
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


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
		z = 0;

	
		// initialize the rotation values
		angleX = 0;
		angleY = 0;
		angleZ = 0;

		// initialize the scaling values
		dimension = 1;
	
	
	
	}

	// Window destructor
	Window::~Window() { glfwTerminate(); }

	// vertex shader source string
	const char *vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoords;\n"

		"out vec2 TexCoords;\n"

		"uniform mat4 transform;\n"

		"void main() {\n"
		"TexCoords = aTexCoords;\n"
		"   gl_Position = transform * vec4(aPos, 1.0);\n"
		"}\0";

	// fragment shader source string
	const char *fragmentShaderSource =
		"#version 330 core\n"

		"out vec4 FragColor;\n"

		"in vec2 TexCoords;\n"

		"uniform int hasTexture;\n"
		"uniform vec4 color;\n"
		"uniform sampler2D texture1;\n"

		"void main() {\n"
		"  if (hasTexture != 0) {\n"
		"    FragColor = texture(texture1, TexCoords);\n"
		"  }\n"
		"  else {\n"
		"    FragColor = color;\n"
		"  }\n"
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

	// get cotangent of angle
	inline float cot(float x) {
		return 1 / glm::tan(x);
	}

	// create a single window with the specified size
	void Window::createWindow(int width, int height)
	{
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
		screenHeight = height;
		screenWidth = width;
	
		lastX = screenWidth / 2.0;
		lastY = screenHeight / 2.0;
	
		glfwSetCursorPosCallback(_window, mouse_callback);
		glfwSetScrollCallback(_window, scroll_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
	
	}

	// process the useful inputs
	void Window::processInput(GLFWwindow *_window)
	{
		// escape key: close process
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(_window, true);

		// translation keys
		
		if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
				y -= DIST_VAR; // W: move up
			else if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
				y += DIST_VAR; // S: move down
		} else {
			if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
				z -= DIST_VAR; // W: move front
			if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
				x += DIST_VAR; // A: mode left
			if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
				z += DIST_VAR; // S: move back
			if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
				x -= DIST_VAR; // D: move right
		}
	}

	glm::mat4 Window::getRotationMatrix()
	{
		glm::mat4 rotationX = glm::mat4(1.0f);
		glm::mat4 rotationY = glm::mat4(1.0f);
		glm::mat4 rotationZ = glm::mat4(1.0f);
		float sin, cos;

		// compute rotation on x axis
		sin = glm::sin(angleX + front.y);
		cos = glm::cos(angleX + front.y);
		rotationX[1][1] = cos;
		rotationX[1][2] = sin;
		rotationX[2][1] = -sin;
		rotationX[2][2] = cos;

		// compute rotation on y axis
		sin = glm::sin(angleY + front.x);
		cos = glm::cos(angleY + front.x);
		rotationY[0][0] = cos;
		rotationY[0][2] = sin;
		rotationY[2][0] = -sin;
		rotationY[2][2] = cos;

		// compute rotation on z axis
		sin = glm::sin(angleZ);
		cos = glm::cos(angleZ);
		rotationZ[0][0] = cos;
		rotationZ[0][1] = sin;
		rotationZ[1][0] = -sin;
		rotationZ[1][1] = cos;

		return rotationX * rotationY * rotationZ;
	}

	void Window::run(const char * objFile)
	{
		// enable the depth test
		glEnable(GL_DEPTH_TEST);

		// build and compile our shader program
		GLint shaderProgram = createRenderingPipeline();
		Model model(objFile);

		// get the "transform" variable location (to apply transformations later)
		GLuint shaderTransform = glGetUniformLocation(shaderProgram, "transform");

		// window main loop
		while (!glfwWindowShouldClose(_window))
		{
			// process the input commands
			processInput(_window);

			// calculate the scaling matrix
			glm::mat4 scalingMatrix = glm::mat4(1.0f);
			scalingMatrix[0][0] = dimension;
			scalingMatrix[1][1] = dimension;
			scalingMatrix[2][2] = dimension;

			// get rotation matrix based on pressed keys
			glm::mat4 rotationMatrix = getRotationMatrix();

			// calculate the translation matrix
			glm::mat4 translationMatrix = glm::mat4(1.0f);
			translationMatrix[0][3] = x ;
			translationMatrix[1][3] = y ;
			translationMatrix[2][3] = z + fov;




			// calculate the viewport matrices
			glm::mat4 viewTranslationMatrix = glm::mat4(1.0f);
			viewTranslationMatrix[2][3] = -1;

			glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, 1.0f);
			glm::vec3 n = glm::normalize(lookAt); // camera direction
			glm::vec3 u = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), n)); // camera right
			glm::vec3 v = glm::cross(n, u); // camera up

			glm::mat4 viewRotationMatrix = glm::mat4(1.0f);
			viewRotationMatrix[0][0] = u.x;
			viewRotationMatrix[0][1] = u.y;
			viewRotationMatrix[0][2] = u.z;

			viewRotationMatrix[1][0] = v.x;
			viewRotationMatrix[1][1] = v.y;
			viewRotationMatrix[1][2] = v.z;

			viewRotationMatrix[2][0] = n.x;
			viewRotationMatrix[2][1] = n.y;
			viewRotationMatrix[2][2] = n.z;

			// conversion from world coordinates to viewing coordinates
			glm::mat4 viewMatrix = viewRotationMatrix * viewTranslationMatrix;

			// normalize viewport
			float zNear = 0.001f, zFar = 50.0f;
			glm::mat4 normalizedPerspective = glm::mat4(1.0f);
			float frustumAngle = 15.0f;
			normalizedPerspective[0][0] = cot(frustumAngle / 2) / (screenWidth / screenHeight);
			normalizedPerspective[1][1] = cot(frustumAngle / 2);
			normalizedPerspective[2][2] = (zNear + zFar) / (zNear - zFar);
			normalizedPerspective[3][3] = 0;
			normalizedPerspective[3][2] = -1;
			normalizedPerspective[2][3] = -((2 * zNear*zFar) / (zNear - zFar));

			// apply the transformations
			glUniformMatrix4fv(shaderTransform, 1, GL_TRUE, glm::value_ptr(scalingMatrix * rotationMatrix * translationMatrix * glm::transpose(normalizedPerspective) * glm::transpose(viewMatrix)));

			// paint the background
			glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// draw the model
			model.Draw(shaderProgram);

			// swap the buffers to make any changes visible
			glfwSwapBuffers(_window);

			// process remaining events
			glfwPollEvents();
		}

		// clear all the glfw resources
		glfwTerminate();
	}


	


}

// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f; 
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;


	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;


	
	front.x = 10 * (cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	front.y = 10 * sin(glm::radians(pitch));
	front.z = 10 * (sin(glm::radians(yaw)) * cos(glm::radians(pitch)));

	
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= 5*yoffset;
	
}
