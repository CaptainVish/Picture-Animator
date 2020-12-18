//water.cpp
#include "water.h"
#include <string>
// constructor
Water::Water(std::string filename,Wave *wave_,bool from_layer){
    if(from_layer)glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    wave=wave_;
    t1=wave->get_time();
    if (load_texture(filename.c_str(), &tex)){
        std::cout << "texture loaded successfully !!!!" << std::endl;
    }
    shaderProgram=createProgram("./shaders/water.vs","./shaders/water.fs");
}

void Water::run(unsigned int VAO,int width,int height){


    long double time_diff=wave->get_time_diff(t1);
    float k=wave->k,w=wave->w,amplitude=wave->amplitude;
    // std::cout<<wave->frequency<<" "<<wave->amplitude<<" "<<wave->wave_length<<std::endl;
    // float y=amplitude*sin(k*pos.x-w*time_diff);
    // std::cout<<y<<std::endl;
    // std::cout<<theta<<std::endl;

    glm::mat4 model=glm::mat4(1.0f);
    glUseProgram(shaderProgram);
    int vModel_uniform=glGetUniformLocation(shaderProgram,"vModel");
    if(vModel_uniform == -1){
        fprintf(stderr, "Could not bind location for water: vModel\n");
        exit(0);
    }
    glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(model));

     int a_value=glGetUniformLocation(shaderProgram,"a");
     glUniform1f(a_value,amplitude);
    //
    int w_value=glGetUniformLocation(shaderProgram,"w");
    glUniform1f(w_value,w);

    int k_value=glGetUniformLocation(shaderProgram,"k");
    glUniform1f(k_value,k);

    int t_value=glGetUniformLocation(shaderProgram,"t");
    glUniform1f(t_value,(float)time_diff);


    // setupModelTransformation(shaderProgram);
    setupViewTransformation(shaderProgram);
    setupProjectionTransformation(shaderProgram, width , height);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}
