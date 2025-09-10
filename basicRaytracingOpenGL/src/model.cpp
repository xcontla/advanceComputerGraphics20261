#include "../header/model.h"


    Model::Model()
    {

        vertices[0] = -1.0f; vertices[1]  =-1.0f; vertices[2]  =  0.0f; // v0
        vertices[3]  = 0.0f; vertices[4]  = 0.0f;  //t0

        vertices[5] =  1.0f; vertices[6]  =-1.0f; vertices[7]  =  0.0f; //v1
        vertices[8]  = 1.0f; vertices[9]  = 0.0f;  // t1
        
        vertices[10] = 1.0f; vertices[11] = 1.0f; vertices[12] =  0.0f; //v2
        vertices[13] = 1.0f; vertices[14] = 1.0f;  // t2
        
        vertices[15] =-1.0f; vertices[16] = 1.0f; vertices[17] =  0.0f; //v3
        vertices[18] = 0.0f; vertices[19] = 1.0f;  // t3

        indices[0] = 0;indices[1] = 1;indices[2] = 2;
        indices[3] = 0;indices[4] = 2;indices[5] = 3; //cara
    }

    //Model::Model(GLfloat* vertices, GLuint indices){}

    void Model::initModel()
    {

    modelmat = glm::mat4(1.0f);
    shader = new Shader("./shader/raytracing.vert","./shader/raytracing.frag");
         // Crear y enlazar el VAO y VBO
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Especificar el layout del vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    }

    void Model::updateModel(float timeValue){
        angle = 0.0; //timeValue * glm::radians(50.0f); // 50 grados por segundo

        modelmat = glm::mat4(1.0);//glm::rotate(modelmat, angle, glm::vec3(0.5f, 1.0f, 0.0f)); // Rotar alrededor de (0.5, 1.0, 0.0)
    }

    void Model::renderModel(glm::mat4 view, glm::mat4 projection){
        
        shader->use();

        // Enviar las matrices al shader
        shader->setMat4x4("model", modelmat);
        shader->setMat4x4("view", view);
        shader->setMat4x4("projection", projection);
        
        // Dibujar el cubo
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }
    void Model::finish(){

        
        shader->terminate();
        delete(shader);
    
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }