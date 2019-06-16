#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string path;
};

class Mesh {
public:
	// Mesh data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    unsigned int VAO;
	glm::vec4 color;
	bool hasTexture;
	Texture texture;

	// used to find the model size and center
	float minX = 1000;
	float maxX = -1000;
	float minY = 1000;
	float maxY = -1000;

    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, glm::vec4 color, bool hasTexture, Texture texture)
    {
        this->vertices = vertices;
        this->indices = indices;
		this->color = color;
		this->hasTexture = hasTexture;
        this->texture = texture;


		// find the min and max points
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i].Position.x < minX)
				minX = vertices[i].Position.x;
			if (vertices[i].Position.x > maxX)
				maxX = vertices[i].Position.x;
			if (vertices[i].Position.y < minY)
				minY = vertices[i].Position.y;
			if (vertices[i].Position.y > maxY)
				maxY = vertices[i].Position.y;
		}

        // now that we have all the required data, set the vertex buffers and its attribute pointers
        setupMesh();
    }

    // render the mesh
    void Draw(GLint shader) 
	{
		// set color and texture bool
		glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
		glUniform1i(glGetUniformLocation(shader, "hasTexture"), hasTexture);

		// bind the texture
		glUniform1i(glGetUniformLocation(shader, "texture1"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.id);
        
        // draw mesh
		glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    // render data
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coordinates
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};

#endif