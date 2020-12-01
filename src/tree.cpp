//tree.cpp
#include "tree.h"
#include <string>
// constructor
Tree::Tree(std::string filename){

    if (load_texture(filename.c_str(), &tex)){
        std::cout << "texture loaded successfully !!!!" << std::endl;
    }
    shaderProgram=createProgram("./shaders/tree.vs","./shaders/tree.fs");
}

void Tree::run(unsigned int VAO,int width,int height){
    if(count>0 && count>=maxcount && mid){
        rotation=-rotation;
        mid=false;
        maxcount=120;
        count=0;
    }

    if(count>0 && count>=maxcount && !mid){
        rotation=-rotation;
        count=0;
    }
    glm::mat4 model=glm::mat4(1.0f);
    // std::cout<<pos.x<<" "<<pos.y<<std::endl;
    model=glm::translate(model,glm::vec3(-pos.x,-pos.y,0));
    model =glm::rotate(model,glm::radians(current_angle+rotation),glm::vec3(0,0,1));
    model=glm::translate(model,glm::vec3(pos.x,pos.y,0));

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
