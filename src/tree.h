//tree.h
#include "utils.h"
#include <string>
#ifndef _TREE_H_
#define _TREE_H_

class Tree{
public:
    GLuint tex;
    unsigned int shaderProgram;
    float rotation=0.02f;
    glm::vec2 pos=glm::vec2(0.225,0.96);
    float current_angle=0.0f;
    float count=0;//max count 60
    float maxcount=60;
    bool mid=true;
    Tree(){};
    Tree(std::string filename);
    void run(unsigned int VAO,int width,int height);

};


#endif
