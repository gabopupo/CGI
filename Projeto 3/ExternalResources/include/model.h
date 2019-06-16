#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <OBJ/OBJ_Loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory);

class Model 
{
public:
    // model data
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;

	// used to find the model size and center
	float minX = 1000;
	float maxX = -1000;
	float minY = 1000;
	float maxY = -1000;

    // constructor, expects a file path to a obj model
    Model(const char *path)
    {
        loadModel(path);
    }

    // draws the model and all its meshes
    void Draw(GLint shader)
    {
        for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }
    
private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(const char *path)
    {
        // read file via OBJ_loader
		objl::Loader loader;
		loader.LoadFile(path);

        // retrieve the directory path of the file path
		string pathS = path;
        directory = pathS.substr(0, pathS.find_last_of('/'));

		cout << "meshes: " << loader.LoadedMeshes.size() << endl;

        // convert and process all the meshes from OBJ_loader to our meshes
		for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
			Mesh newMesh = processMesh(loader.LoadedMeshes[i]);

			// find the model's maxs and mins
			if (newMesh.minX < minX)
				minX = newMesh.minX;
			if (newMesh.maxX > maxX)
				maxX = newMesh.maxX;
			if (newMesh.minY < minY)
				minY = newMesh.minY;
			if (newMesh.maxY > maxY)
				maxY = newMesh.maxY;

			meshes.push_back(newMesh);
		}
    }

    Mesh processMesh(objl::Mesh mesh)
    {
        // data to fill
        vector<Vertex> vertices;
		glm::vec4 color(0.0f, 0.0f, 1.0f, 1.0f);
		Texture texture;

        // walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh.Vertices.size(); i++)
        {
            Vertex vertex;

			// placeholder vector
            glm::vec3 vector; 

			// positions
            vector.x = mesh.Vertices[i].Position.X;
            vector.y = mesh.Vertices[i].Position.Y;
            vector.z = mesh.Vertices[i].Position.Z;
            vertex.Position = vector;

            // normals
            vector.x = mesh.Vertices[i].Normal.X;
            vector.y = mesh.Vertices[i].Normal.Y;
            vector.z = mesh.Vertices[i].Normal.Z;
            vertex.Normal = vector;

            // texture coordinates
            glm::vec2 vec;
            vec.x = mesh.Vertices[i].TextureCoordinate.X;
            vec.y = mesh.Vertices[i].TextureCoordinate.Y;
            vertex.TexCoords = vec;

            vertices.push_back(vertex);
        }

        // process materials
		if (mesh.MeshMaterial.Kd.X != 0 || mesh.MeshMaterial.Kd.Y != 0 || mesh.MeshMaterial.Kd.Z != 0) {
			color.x = mesh.MeshMaterial.Kd.X;
			color.y = mesh.MeshMaterial.Kd.Y;
			color.z = mesh.MeshMaterial.Kd.Z;
		}

		cout << "mesh name: " << mesh.MeshName << endl;
		cout << "material name: " << mesh.MeshMaterial.name << endl;
		cout << "color: " << color.x << ' ' << color.y << ' ' << color.z << endl;
		cout << "texture: " << mesh.MeshMaterial.map_Kd << endl;
		if (!mesh.MeshMaterial.map_Kd.empty())
			texture = loadTexture(mesh.MeshMaterial.map_Kd);
        
        // return a mesh object created from the extracted mesh data
        return Mesh(vertices, mesh.Indices, color, !mesh.MeshMaterial.map_Kd.empty(), texture);
    }

    // loads the texture if it was not loaded yet
    Texture loadTexture(string path)
    {
		Texture texture;

        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), path.c_str()) == 0)
            {
                texture = textures_loaded[j];
                skip = true; // a texture with the same file path has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
			stbi_set_flip_vertically_on_load(true);
            texture.id = TextureFromFile(path.c_str(), this->directory);
            texture.path = path.c_str();
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
        }

        return texture;
    }
};


unsigned int TextureFromFile(const char *path, const string &directory)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
#endif