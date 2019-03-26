//#include "../include/cg_window.hpp"
#include <cg_window.hpp>

namespace cgicmc {

Window::Window() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::~Window() { glfwTerminate(); }

const char *vertexShaderSource =	"#version 330 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "void main()\n"
                                  "{\n"
                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                  "}\0";

const char *fragmentShaderSource =  "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\n\0";


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

void Window::processInput(GLFWwindow *_window) {
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(_window, true);
}

void Window::run() {
// build and compile our shader program
	// ------------------------------------
	//cria o vertex shader com base na string vertexShaderSource
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, true, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//cria o fragment shader 
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, true, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(false, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(false);

	glBindBuffer(GL_ARRAY_BUFFER, false);// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

  while (!glfwWindowShouldClose(_window)) {

    // Comandos de entrada
    processInput(_window);

    // Comandos de renderizacao vao aqui
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // etc...

  glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

    // Controla eventos e troca os buffers para renderizacao
    glfwSwapBuffers(_window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(true, &VAO);
	glDeleteBuffers(true, &VBO);
}
}
