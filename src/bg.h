//clouds.h
#include "utils.h"
#include <string>
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

class Background{
public:
    GLuint tex;
    unsigned int shaderProgram;
    Background(){};
    Background(std::string filename);
    void run(unsigned int VAO,int width,int height);

};


#endif
