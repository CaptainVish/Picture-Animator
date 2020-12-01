#version 330 core
in vec2 texture_coordinates;
uniform sampler2D basic_texture;

//in vec3 fColor;
out vec4 outColor;

void main(void) {
        // outColor = vec4(1.0f, 0.0f, 0.0f, 1.0);

        vec4 texel = texture(basic_texture, texture_coordinates);

		outColor = texel;

}
