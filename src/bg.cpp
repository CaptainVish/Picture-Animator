//bg.cpp
#include "bg.h"
#include <string>
// constructor
Background::Background(std::string filename,bool from_layer){
    if(from_layer)glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    if (load_texture(filename.c_str(), &tex)){
        std::cout << "texture loaded successfully !!!!" << std::endl;
    }
    shaderProgram=createProgram("./shaders/cloud.vs","./shaders/cloud.fs");
}

void Background::run(unsigned int VAO,int width,int height){
    glUseProgram(shaderProgram);
    setupModelTransformation(shaderProgram);
    setupViewTransformation(shaderProgram);
    setupProjectionTransformation(shaderProgram, width , height);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}
