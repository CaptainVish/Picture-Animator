//clouds.cpp
#include "clouds.h"
#include <string>
// constructor
Clouds::Clouds(std::string filename){
    if (load_texture(filename.c_str(), &tex)){
        std::cout << "texture loaded successfully !!!!" << std::endl;
    }
    shaderProgram=createProgram("./shaders/cloud.vs","./shaders/cloud.fs");
}

void Clouds::run(unsigned int VAO,int width,int height){
    // std::cout<<current_pos<<std::endl;
    if(current_pos>=2)current_pos=-2;
    glm::mat4 model= glm::translate(glm::mat4(1.0f),glm::vec3((current_pos+translation),0.0,0.0));
    current_pos+=translation;
    // std::cout<<current_pos<<std::endl;

    glUseProgram(shaderProgram);
    int vModel_uniform=glGetUniformLocation(shaderProgram,"vModel");
    if(vModel_uniform == -1){
        fprintf(stderr, "Could not bind location: vModel\n");
        exit(0);
    }
    glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(model));

    // setupModelTransformation(shaderProgram);
    setupViewTransformation(shaderProgram);
    setupProjectionTransformation(shaderProgram, width , height);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}
