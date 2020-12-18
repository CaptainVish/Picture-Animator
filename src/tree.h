//tree.h
#include "utils.h"
#include "wave.h"
#include <string>
#ifndef _TREE_H_
#define _TREE_H_

class Tree{
public:
    GLuint tex;
    unsigned int shaderProgram;
    // float rotation=0.0005f;
    Wave *wave;
    // glm::vec2 pos=glm::vec2(0.49f,0.81f);
    glm::vec2 pos=glm::vec2(0.0f,0.0f);

    float current_angle=0.0f;
    float count=0;//max count 60
    float maxcount=60;
    bool mid=false;
    Tree(){};
    Tree(std::string filename,Wave *wave_,bool from_layer=false);
    void run(unsigned int VAO,int width,int height);
    bool setPos(float x,float y);
};


#endif
