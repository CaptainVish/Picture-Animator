//boat.cpp
#include "boat.h"
#include <string>
// constructor
Boat::Boat(std::string filename,Wave *wave_){
    wave=wave_;
    t1=wave->get_time();
    // pos=glm::vec2(254,527);
    if (load_texture(filename.c_str(), &tex)){
        std::cout << "texture loaded successfully !!!!" << std::endl;
    }
    shaderProgram=createProgram("./shaders/boat.vs","./shaders/boat.fs");
}

bool Boat::setPos(float x,float y){
    pos.x=x;
    pos.y=y;
}
void Boat::run(unsigned int VAO,int width,int height){
    // if(count>0 && count>=maxcount && mid){
    //     translation=-translation;
    //     rotation=-rotation;
    //     mid=false;
    //     maxcount=120;
    //     count=0;
    // }
    //
    // if(count>0 && count>=maxcount && !mid){
    //     translation=-translation;
    //     rotation=-rotation;
    //     count=0;
    // }

    long double time_diff=wave->get_time_diff(t1);
    float k=wave->k,w=wave->w,amplitude=wave->amplitude/10;
    float y=amplitude*sin(k*pos.x-w*time_diff);
    float tan_theta=k*amplitude*cos(k*pos.x-w*time_diff);
    float theta=atan(tan_theta);
    // std::cout<<pos.x<<" "<<pos.y<<std::endl;
    // std::cout<<y<<std::endl;
    // std::cout<<theta<<std::endl;
    glm::mat4 model=glm::mat4(1.0f);
    // std::cout<<pos.x<<" "<<pos.y<<std::endl;

    // model= glm::translate(model,glm::vec3(0.0,(current_pos+translation),0.0));

    model=glm::translate(model,glm::vec3(0,y,0));

    model=glm::translate(model,glm::vec3(-pos.x,-(pos.y+y),0));
    // std::cout<<glm::to_string(model)<<std::endl;
    // exit(0);
    model =glm::rotate(model,theta,glm::vec3(0,0,1));
    model=glm::translate(model,glm::vec3(pos.x,(pos.y+y),0));


    // current_pos+=translation;
    // current_angle+=rotation;
    // count++;

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
