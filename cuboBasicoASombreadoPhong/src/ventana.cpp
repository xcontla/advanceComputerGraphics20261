#include "../header/ventana.h"
#include <iostream>
Ventana::Ventana(){
    width = 800;
    height = 600;
}

Ventana::Ventana(GLuint w, GLuint h){
    width = w;
    height = h;
}


void Ventana::initGLFW()
{
        if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return ;
    }

    // Crear una ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Cubo Rotando", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);


}

    // Inicializar GLEW
void Ventana::initGLEW(){
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW" << std::endl;
        return;
    }
    std::cout << "Inicialización Correcta de GLEW y GLFW" << std::endl;
    // Habilitar depth testing y face culling
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glCullFace(GL_BACK);      // Culling de caras traseras
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario

    glClearColor(0.0,0.0,0.0,1.0); // color fondo
}

void Ventana::initModels(Model* m)
{
    model = m;
    model->initModel("./shader/cubo.vert","./shader/cubo.frag");
   
}
void Ventana::initViewProyection(){
     // Configurar matrices de transformación (model, view, projection)
    //view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    posCamara = glm::vec3(0.0f, 0.0f, -3.0f);
    view = glm::lookAt(posCamara, glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
    projection = glm::perspective(
        glm::radians(45.0f), // FOV 
        (float)width / (float)height, // aspect ratio
        0.1f, // near
        100.0f); // far

}

void Ventana::render(){
while (!glfwWindowShouldClose(window)) {
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model->renderModel(view, projection, posCamara);


        glfwSwapBuffers(window);
        glfwPollEvents();
        update();
    }


}
void Ventana::update(){
 // Calcular la rotación del cubo
    model->updateModel(glfwGetTime());
}

void Ventana::idel(){}

void Ventana::finish(){

    model->finish();
}