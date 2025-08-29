#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../header/shader.h"
#include <string>

class Model{
public:

    Shader* shader;
    GLfloat vertices[48]; // 8 vertices * 3 (x,y,z) * 2 (vertices, colores)
    GLuint indices[36]; // 
    float angle;
    glm::mat4 modelmat;
    GLuint VAO, VBO, EBO;

    Model();
    //Model(GLfloat* vertices, GLuint indices);
    //Model(std::string ubicacionOBJ);
    
    void initModel(std::string vert, std::string frag);
    void renderModel(glm::mat4 view, glm::mat4 projection);
    void renderModel(glm::mat4 view, glm::mat4 projection, glm::vec3 posCamara);
    void updateModel(float timeValue);
    void finish();


};