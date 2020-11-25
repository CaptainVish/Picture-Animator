//boat.cpp
#include "boat.h"
#include <string>
// constructor
Boat::Boat(std::string filename){
    pos=glm::vec2(254,527);
    if (load_texture(filename.c_str(), &tex)){
        std::cout << "texture loaded successfully !!!!" << std::endl;
    }
    shaderProgram=createProgram("./shaders/cloud.vs","./shaders/cloud.fs");
}

void Boat::run(unsigned int VAO,int width,int height){
    if(count>0 && count>=maxcount && mid){
        translation=-translation;
        rotation=-rotation;
        mid=false;
        maxcount=120;
        count=0;
    }

    if(count>0 && count>=maxcount && !mid){
        translation=-translation;
        rotation=-rotation;
        count=0;
    }

    glm::mat4 model =glm::rotate(glm::mat4(1.0f),glm::radians(current_angle+rotation),glm::vec3(0,0,1));
    model= glm::translate(model,glm::vec3(0.0,(current_pos+translation),0.0));

    current_pos+=translation;
    current_angle+=rotation;
    count++;

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
