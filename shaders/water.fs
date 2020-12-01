#version 330 core
in vec2 texture_coordinates;
uniform float a;
uniform float w;
uniform float k;
uniform float t;
uniform sampler2D basic_texture;

//in vec3 fColor;
out vec4 outColor;

void main(void) {
        // outColor = vec4(1.0f, 0.0f, 0.0f, 1.0);
        float y=a*sin(k*(texture_coordinates.x)-w*t);
        float x=a*sin(k*(texture_coordinates.y)-w*t);
        vec2 temp=vec2(texture_coordinates.x+x,texture_coordinates.y+y);
        //vec2 temp=vec2(texture_coordinates.x,texture_coordinates.y);
        vec4 texel = texture(basic_texture, temp);
		outColor = texel;

}
