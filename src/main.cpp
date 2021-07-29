// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
#include <stdio.h>
#include <unistd.h>
#include "utils.h"
#include "water.h"
#include "clouds.h"
#include "bg.h"
#include "boat.h"
#include "tree.h"
// #include <opencv2/opencv.hpp>

Mat img,inpaintMask, objectMask, inpaintResult;
Point prevPt(-1,-1);

float width=600, height=600;


static void onMouse( int event, int x, int y, int flags, void* )
{
    if( event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON) )
        prevPt = Point(-1,-1);
    else if( event == EVENT_LBUTTONDOWN )
        prevPt = Point(x,y);
    else if( event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON) )
    {
        Point pt(x,y);
        if( prevPt.x < 0 )
            prevPt = pt;
        line( inpaintMask, prevPt, pt, Scalar::all(255), 5, 8, 0 );
        line( objectMask, prevPt, pt, Scalar::all(255), 5, 8, 0 );
        line( img, prevPt, pt, Scalar::all(255), 5, 8, 0 );
        prevPt = pt;
        imshow("image", img);
        // imshow("image: mask", inpaintMask);
        // imshow("image: object mask", objectMask);
    }
}

void makeLayer(std::string filename,std::string toSave){
    img=imread(filename,IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Failed to load image: " << filename << std::endl;
        exit(-1);
    }
    namedWindow("image", WINDOW_AUTOSIZE);

    // Create a copy for the original image
    Mat imgCopy = img.clone();
    // Initialize mask (black image)
    inpaintMask = Mat::zeros(imgCopy.size(), CV_8U);
    objectMask = Mat::zeros(imgCopy.size(), CV_8UC3);

    // Show the original image
    imshow("image", img);
    setMouseCallback( "image", onMouse, NULL);

    for(;;)
    {
        char c = (char)waitKey();

        if(c=='s'){

            // do inpainting
            inpaint(img, inpaintMask, inpaintResult, 3, INPAINT_TELEA);
            // imshow("Inpaint Output using FMM", inpaintResult);

            //save objectMask
            cv::Mat objectResult;
            cv::bitwise_and(imgCopy, objectMask, objectResult);


            //converting bg of object image to transparent
            cv::Mat objectResult_bgra;
            cv::cvtColor(objectResult, objectResult_bgra, cv::COLOR_BGR2BGRA);

            // find all white pixel and set alpha value to zero:
            for (int y = 0; y < objectResult_bgra.rows; ++y)
            for (int x = 0; x < objectResult_bgra.cols; ++x)
            {
                cv::Vec4b & pixel = objectResult_bgra.at<cv::Vec4b>(y, x);
                // if pixel is white
                if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0)
                {
                    // set alpha to zero:
                    pixel[3] = 0;
                }
            }


            // imshow("object", objectResult_bgra);

            // cout << "Enter object name:" <<endl;
            // cin >> filename2;
            imwrite(toSave + ".png", objectResult_bgra);


            // To save edges
            // cv::Mat result_white(30,30,CV_8UC3, cv::Scalar(255,255,255));
            // cv::bitwise_and(source_image, mask, result_white, mask);

            // reseting object mask
            objectMask = Scalar::all(0);

            // save background
            imwrite(filename, inpaintResult);
            std::cout << "Inpainted bg saved in bg.png" <<std::endl;
            destroyWindow("image");
            break;

        }

        if (c == 'r') {
            inpaintMask = Scalar::all(0);
            objectMask = Scalar::all(0);
            imgCopy.copyTo(img);
            imshow("image", img);
        }

        if ( c == 27 ){
            destroyWindow("image");
            break;
        }
    }




}

int main(int argc, char** argv)
{
        // set_width_height(argv[1],width,height);


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


// parse command line arguments
    // std::string filename=argv[1];
    std::string filename;
    // img=imread(filename,IMREAD_COLOR);
    // imwrite("bg.png",img);
    Wave wave(0.0001,0.01,0.0001,0.0001,0.0001);//frequency, wave_length, amplitude, translation, rotation
    // Background bg(filename.c_str());
    Background bg;
    // Background bg2("bg.png");
    Background bg2;
    std::vector<Clouds> clouds;
    std::vector<Water> water;
    std::vector<Tree> tree;
    std::vector<Boat> boats;
    
    // if(argc>2){
    // Clouds _cloud(argv[2]);
    // clouds.push_back(_cloud);
    // Water _water(argv[3],wave);
    // water.push_back(_water);
    // Tree _tree(argv[4]);
    // tree.push_back(_tree);
    // Boat _boat(argv[5],wave);
    // boats.push_back(_boat);
    // }
    int opt;
    while((opt = getopt(argc, argv, ":f:b:c:w:t:h")) != -1)
{
    switch(opt)
    {
        case 'h':
        printf("-f option to add a file\n");
        printf("-b option to add a file containing boat\n");
        printf("-c option to add a file containing clouds\n");
        printf("-w option to add a file containing water\n");
        printf("-t option to add a file containing tree\n");
        printf("-h option for help menu\n");
        break;

        case 'f':{
        printf("filename %s\n", optarg);
        filename=optarg;
        img=imread(filename,IMREAD_COLOR);
        imwrite("bg.png",img);
        bg=Background(filename.c_str());
        bg2=Background("bg.png");
        break;
        }

        case 'c':{
        printf("clouds %s \n", optarg);
        Clouds _cloud(optarg,&wave);
        clouds.push_back(_cloud);
        break;
        }
	       
        case 'b':{
            printf("boat %s \n", optarg);
            Boat _boat(optarg,&wave);
            boats.push_back(_boat);
            break;
        }

        case 'w':{
            printf("water %s \n", optarg);
            Water _water(optarg,&wave);
            water.push_back(_water);
            break;
        }

        case 't':{
            printf("tree %s \n", optarg);
            Tree _tree(optarg,&wave);
            tree.push_back(_tree);
            break;
        }

        case ':':{
            printf("option %c needs a value\n",opt);
            break;
        }

        case '?':{
            printf("unknown option: %c\n", optopt);
            break;
        }

        }
    }





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
     1.0f,  1.0f, 0.0f,      1.0f, 1.0f,   // top right
     1.0f, -1.0f, 0.0f,      1.0f, 0.0f,   // bottom right
    -1.0f, -1.0f, 0.0f,      0.0f, 0.0f,   // bottom left
    -1.0f,  1.0f, 0.0f,      0.0f, 1.0f    // top left
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

// boolean flags and variables for different operations and sliders
    bool b_cloud=false,b_water=false,b_tree=false,b_boats=false,b_about=false,show=false,boat_point=false,tree_point=false;
    bool reset=false;
    float frequency=0.0f,wave_length=0.0f,amplitude=0.0f,windspeed=0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui::ShowDemoWindow();

        {
            static float f = 0.0f;
            static int counter = 0;

            // ImGui::Begin("Hello, world!");
            //
            // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            // ImGui::End();
            
            if(ImGui::Button("show")) show=!show; ImGui::SameLine();
            if(ImGui::Button("Clouds")) b_cloud=!b_cloud;ImGui::SameLine();
            if(ImGui::Button("Water")) b_water=!b_water;ImGui::SameLine();
            if(ImGui::Button("Tree")) b_tree=!b_tree;ImGui::SameLine();
            if(ImGui::Button("Boats")) b_boats=!b_boats;ImGui::SameLine();
            if(ImGui::Button("Boat Point")) boat_point=!boat_point;ImGui::SameLine();
            if(ImGui::Button("Tree Point")) tree_point=!tree_point;ImGui::SameLine();
            if(ImGui::Button("About")) b_about=!b_about;ImGui::SameLine();
            if(ImGui::Button("Reset")) reset=!reset;
            if(ImGui::SliderFloat("Wind Speed",&windspeed,1.0f,10.0f)) {
                wave.update_parameters(windspeed);

                // std::cout<<frequency<<std::endl;
                // std::cout<<"something something"<<wave.frequency<<std::endl;
            }
            // if(ImGui::SliderFloat("frequency",&frequency,1.0f,100.0f)){
            //     wave.update_frequency(frequency);
            //     std::cout<<"updated frequency "<<wave.frequency<<std::endl;
            // }
            // if(ImGui::SliderFloat("wavelength",&wave_length,0.0f,1.0f)){
            //     wave.update_wavelength(wave_length);
            //     std::cout<<"update wavelength "<<wave.wave_length<<std::endl;
            // }
            // if(ImGui::SliderFloat("amplitude",&amplitude,0.0f,0.1f)){
            //     wave.update_amplitude(amplitude);
            //     std::cout<<"updated amplitude "<<wave.amplitude<<std::endl;
            // }

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
        if(!boat_point && !tree_point ){
            bg.run(VAO,width,height);
        }
        if(b_cloud)
        {
            std::cout<<"Select Clouds"<<std::endl;
            makeLayer("bg.png","cloud");
            Clouds temp("./cloud.png",&wave,true);
            clouds.push_back(temp);
            bg=Background("bg.png");
            b_cloud=false;
        }
        if(b_about)
        {
            std::cout<<"About the project"<<std::endl;
            makeLayer("About.png","cloud");
            Clouds temp("./cloud.png",&wave,true);
            clouds.push_back(temp);
            bg=Background("About.png");
            b_cloud=false;
        }
        if(b_water){
            std::cout<<"Select Water"<<std::endl;
            makeLayer("bg.png","water");
            Water temp("./water.png",&wave,true);
            water.push_back(temp);
            bg=Background("bg.png");
            b_water=false;
        }
        if(b_tree){
            std::cout<<"Select tree"<<std::endl;
            makeLayer("bg.png","tree");
            Tree temp("./tree.png",&wave,true);
            tree.push_back(temp);
            // bg=Background("./bg.png");
            // bg2=Background("./tree.png");
            bg=Background("./bg.png");

            b_tree=false;
        }
        if(b_boats){

            std::cout<<"Select boats"<<std::endl;
            makeLayer("bg.png","boat");
            Boat temp("./boat.png",&wave,true);
            boats.push_back(temp);
            // bg=Background("./bg.png");
            // bg2=Background("./boat.png");
            bg=Background("./bg.png");

            b_boats=false;
        }
        // will only add to the last boat added in the list

        if(boat_point){
            bg2.tex=boats.back().tex;
            bg2.run(VAO,width,height);
            //mouse position
            if(io.MouseClicked[0] && !ImGui::IsAnyItemActive()){
                float x = io.MousePos.x;
                float y = io.MousePos.y;
                float hw=width/2,hh=height/2;

                x=(x-hw)/hw;
                y=-(hh-y)/hh;
                std::cout<<x<<" "<<y<<std::endl;
                boats.back().setPos(x,y);
                boat_point=false;
             }

        }
        // will only add to the last tree added in the list
        if(tree_point){
            bg2.tex=tree.back().tex;
            bg2.run(VAO,width,height);
            //mouse position
            if(io.MouseClicked[0] && !ImGui::IsAnyItemActive()){
                float x = io.MousePos.x;
                float y = io.MousePos.y;
                float hw=width/2,hh=height/2;

                x=(x-hw)/hw;
                y=-(hh-y)/hh;
                std::cout<<x<<" "<<y<<std::endl;
                tree.back().setPos(x,y);
                tree_point=false;
             }
        }

        if(reset){
            clouds.clear();
            water.clear();
            tree.clear();
            boats.clear();
            img=imread(filename,IMREAD_COLOR);
            imwrite("bg.png",img);
            bg=Background(filename.c_str());

            reset=false;
        }

        if(show){
        // std::cout<<"show"<<std::endl;
        // cloud.run(VAO,width,height);
        // water.run(VAO,width,height);
        // tree.run(VAO,width,height);
        // boat.run(VAO,width,height);
        for(int i=0;i<clouds.size();++i){
                // std::cout<<"cloud object present"<<std::endl;
                clouds[i].run(VAO,width,height);
        }
        for(int i=0;i<water.size();++i){
                // std::cout<<"cloud object present"<<std::endl;
                water[i].run(VAO,width,height);
        }
        for(int i=0;i<tree.size();++i){
                // std::cout<<"cloud object present"<<std::endl;
                tree[i].run(VAO,width,height);
        }
        for(int i=0;i<boats.size();++i){
                // std::cout<<"cloud object present"<<std::endl;
                // std::cout<<i<<std::endl;
                boats[i].run(VAO,width,height);
        }


        }

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
    remove("bg.png");
    remove("boat.png");
    remove("cloud.png");
    remove("tree.png");
    remove("water.png");


    return 0;
}
