// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

#include "utils.h"

#include "clouds.h"
#include "bg.h"
#include "boat.h"
#include "tree.h"


int width = 550, height=700;
int main(int, char**)
{
    // Setup window

    GLFWwindow *window = setupWindow(width, height);
    ImGuiIO& io = ImGui::GetIO(); // Create IO object

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x  << " " << vec.y  << " " << vec.z << std::endl;


    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


// important **********************************
    // GLuint tex1,tex2,tex3;
    //
    // if (load_texture("./bg.png", &tex1)){
    //     std::cout << "texture loaded successfully !!!!" << std::endl;
    // }
    //
    // if (load_texture("./boat.png", &tex2)){
    //     std::cout << "texture loaded successfully !!!!" << std::endl;
    // }

    Background bg("./bg.png");
    Clouds cloud("./clouds.png");
    Tree tree("./tree.png");
    Boat boat("./boat.png");
    // if (load_texture("./clouds.png", &tex3)){
    //     std::cout << "texture loaded successfully !!!!" << std::endl;
    // }
// important ************************************

    // unsigned int shaderProgram = createProgram("./shaders/vshader.vs", "./shaders/fshader.fs");
    // glUseProgram(shaderProgram);
    //
    //
    // setupModelTransformation(shaderProgram);
    // setupViewTransformation(shaderProgram);
    // setupProjectionTransformation(shaderProgram, width , height);


    float vertices[] = {
    // positions            // texture coords
     10.5f,  10.5f, 0.0f,      1.0f, 1.0f,   // top right
     10.5f, -10.5f, 0.0f,      1.0f, 0.0f,   // bottom right
    -10.5f, -10.5f, 0.0f,      0.0f, 0.0f,   // bottom left
    -10.5f,  10.5f, 0.0f,      0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glEnable(GL_MULTISAMPLE);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            // ImGui::Begin("Hello, world!");
            //
            // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            // ImGui::End();
        }

        //mouse position
        if(io.MouseClicked[0] && !ImGui::IsAnyItemActive()){
            float x = io.MousePos.x;
            float y = io.MousePos.y;
            std::cout<<x<<" "<<y<<std::endl;
         }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);


        // important business **********************************
        // glActiveTexture( GL_TEXTURE0 );
        // glBindTexture( GL_TEXTURE_2D, tex1 );
        // glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //
        // glActiveTexture( GL_TEXTURE0 );
        // glBindTexture( GL_TEXTURE_2D, tex2 );
        // glBindVertexArray(VAO);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glUseProgram(shaderProgram);
        bg.run(VAO,width,height);
        cloud.run(VAO,width,height);
        tree.run(VAO,width,height);
        boat.run(VAO,width,height);
        // glActiveTexture( GL_TEXTURE0 );
        // glBindTexture( GL_TEXTURE_2D, tex3 );
        // glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // important business ***********************************



        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }

    // Cleanup
    cleanup(window);

    return 0;
}
