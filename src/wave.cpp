//wave.cpp
#include "wave.h"
#include <string>
// constructor
Wave::Wave(float frequency_,float wave_length_,float amplitude_){
    frequency=frequency_;
    wave_length=wave_length_;
    amplitude=amplitude_;
    k=(2*M_PI)/wave_length;
    w=2*M_PI*frequency;
}

float Wave::get_position(float x, float t){
    float argument=k*x-w*t;
    return amplitude*sin(argument);
}



std::chrono::high_resolution_clock::time_point Wave::get_time(){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    return t1;
}
long double Wave::get_time_diff(std::chrono::high_resolution_clock::time_point t1){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;
    return time_span.count();
}
