#include "utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
extern bool controlPointsUpdated;


bool load_texture( const char *file_name, GLuint *tex ) {
    int x, y, n;
    int force_channels = 4;
    unsigned char *image_data = stbi_load( file_name, &x, &y, &n, force_channels );
    if ( !image_data ) {
        fprintf( stderr, "ERROR: could not load %s\n", file_name );
        return false;
    }
    // NPOT check
    if ( ( x & ( x - 1 ) ) != 0 || ( y & ( y - 1 ) ) != 0 ) {
        fprintf( stderr, "WARNING: texture %s is not power-of-2 dimensions\n",
                         file_name );
    }
    int width_in_bytes = x * 4;
    unsigned char *top = NULL;
    unsigned char *bottom = NULL;
    unsigned char temp = 0;
    int half_height = y / 2;

    for ( int row = 0; row < half_height; row++ ) {
        top = image_data + row * width_in_bytes;
        bottom = image_data + ( y - row - 1 ) * width_in_bytes;
        for ( int col = 0; col < width_in_bytes; col++ ) {
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            top++;
            bottom++;
        }
    }
    glGenTextures( 1, tex );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, *tex );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                image_data );
    glGenerateMipmap( GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    GLfloat max_aniso = 0.0f;
    glGetFloatv( GL_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso );
    // set the maximum!
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso );
    return true;
}

bool load_texture( const char *file_name, GLuint *tex,float &width, float &height ) {
    int x, y, n;
    int force_channels = 4;
    unsigned char *image_data = stbi_load( file_name, &x, &y, &n, force_channels );
    width=x;
    height=y;
    if ( !image_data ) {
        fprintf( stderr, "ERROR: could not load %s\n", file_name );
        return false;
    }
    // NPOT check
    if ( ( x & ( x - 1 ) ) != 0 || ( y & ( y - 1 ) ) != 0 ) {
        fprintf( stderr, "WARNING: texture %s is not power-of-2 dimensions\n",
                         file_name );
    }
    int width_in_bytes = x * 4;
    unsigned char *top = NULL;
    unsigned char *bottom = NULL;
    unsigned char temp = 0;
    int half_height = y / 2;

    for ( int row = 0; row < half_height; row++ ) {
        top = image_data + row * width_in_bytes;
        bottom = image_data + ( y - row - 1 ) * width_in_bytes;
        for ( int col = 0; col < width_in_bytes; col++ ) {
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            top++;
            bottom++;
        }
    }
    glGenTextures( 1, tex );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, *tex );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                image_data );
    glGenerateMipmap( GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    GLfloat max_aniso = 0.0f;
    glGetFloatv( GL_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso );
    // set the maximum!
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso );
    return true;
}


void cleanup(GLFWwindow* window){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}



void setupModelTransformation(unsigned int &program)
{
    //Modelling transformations (Model -> World coordinates)
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));//Model coordinates are the world coordinates
    //TODO: Q1/Q2 - Apply modelling transformations here.

    //TODO: Reset modelling transformations to Identity. Uncomment line below before attempting Q4!
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));//Model coordinates are the world coordinates

    //Pass on the modelling matrix to the vertex shader
    glUseProgram(program);
    int vModel_uniform = glGetUniformLocation(program, "vModel");
    if(vModel_uniform == -1){
        fprintf(stderr, "Could not bind location: vModel\n");
        exit(0);
    }
    glUniformMatrix4fv(vModel_uniform, 1, GL_FALSE, glm::value_ptr(model));
}


void setupViewTransformation(unsigned int &program)
{
    //Viewing transformations (World -> Camera coordinates
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    //Camera at (0, 0, 1) looking down the negative Z-axis in a right handed coordinate system

    //TODO: Q4 - Apply viewing transformations here.

    //Pass on the viewing matrix to the vertex shader
    glUseProgram(program);
    int vView_uniform = glGetUniformLocation(program, "vView");
    if(vView_uniform == -1){
        fprintf(stderr, "Could not bind location: vView\n");
        exit(0);
    }
    glUniformMatrix4fv(vView_uniform, 1, GL_FALSE, glm::value_ptr(view));
}

void setupProjectionTransformation(unsigned int &program, int screen_width, int screen_height)
{
    // //Projection transformation (Orthographic projection)
    // float aspect = (float)screen_width/(float)screen_height;
    // float view_height = 25.0f;
    //
    // //TODO: Q4 - Apply projection transformation here. Appropriately switch between orthographic (given below) and perspective transformations.
    // glm::mat4 projection = glm::ortho(-view_height*aspect/2.0f, view_height*aspect/2.0f, -view_height/2.0f, view_height/2.0f, 0.1f, 1000.0f);
    glm::mat4  projection=glm::mat4(1.0f);
    //Pass on the projection matrix to the vertex shader
    glUseProgram(program);
    int vProjection_uniform = glGetUniformLocation(program, "vProjection");
    if(vProjection_uniform == -1){
        fprintf(stderr, "Could not bind location: vProjection\n");
        exit(0);
    }
    glUniformMatrix4fv(vProjection_uniform, 1, GL_FALSE, glm::value_ptr(projection));
}


void setVAO(unsigned int &VAO){
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

GLuint createShader(const char* filename, GLenum type)
{
    const GLchar* source = getShaderCode(filename);
    if (source == NULL) {
        fprintf(stderr, "Error opening %s: ", filename); perror("");
        return 0;
    }
    GLuint res = glCreateShader(type);
    glShaderSource(res, 1, &source, NULL);
    free((void*)source);

    glCompileShader(res);
    GLint compile_ok = GL_FALSE;
    char infoLog[512];
    glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
    if (compile_ok == GL_FALSE) {
        // fprintf(stderr, "%s:", filename);

        std::cout << "Error in compilation of :" << filename << " " << compile_ok << std::endl;
        glGetShaderInfoLog(res, 512, NULL, infoLog);

        glDeleteShader(res);
        return 0;
    }

    return res;
}

const char * setGLSLVersion(){
    #if __APPLE__
    // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

    return glsl_version;
}

int openGLInit(){
    #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        exit(1);
    }

    //Enable multisampling
    glEnable(GL_MULTISAMPLE);

    // Enable Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set point size
    glPointSize(10.0f);

    // Enable smooth point rendering
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

unsigned int createProgram(const char *vshader_filename, const char* fshader_filename)
{
    //Create shader objects
    GLuint vs, fs;
    if ((vs = createShader(vshader_filename, GL_VERTEX_SHADER))   == 0) return 0;
    if ((fs = createShader(fshader_filename, GL_FRAGMENT_SHADER)) == 0) return 0;

    //Creare program object and link shader objects
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    GLint link_ok;
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        // fprintf(stderr, "glLinkProgram error:");
        // printLog(program);
        std::cout << "Linking error " << std::endl  ;
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}


char * getShaderCode(const char* filename)
{
    FILE* input = fopen(filename, "rb");
    if(input == NULL) return NULL;

    if(fseek(input, 0, SEEK_END) == -1) return NULL;
    long size = ftell(input);
    if(size == -1) return NULL;
    if(fseek(input, 0, SEEK_SET) == -1) return NULL;

    /*if using c-compiler: dont cast malloc's return value*/
    char *content = (char*) malloc( (size_t) size +1  );
    if(content == NULL) return NULL;

    fread(content, 1, (size_t)size, input);
    if(ferror(input)) {
        free(content);
        return NULL;
    }

    fclose(input);
    content[size] = '\0';
    return content;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* setupWindow(int width, int height)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        exit(0);

    // Decide GL+GLSL versions
    const char * glsl_version = setGLSLVersion();


    // Create window with graphics context
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWwindow* window = glfwCreateWindow(width, height, "Window Title", NULL, NULL);
    if (window == NULL)
        exit(0);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    int status = openGLInit();
    if(!status){
        std::cout << "Initialized OpenGL succesfully " << std::endl;
    }
    std::cout<< "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return window;
}

void set_width_height(const char*file_name,float &width,float &height){
    int w,h,channels;
    unsigned char *img = stbi_load(file_name, &w, &h, &channels, 0);
    if(img == NULL) {
          printf("Error in loading the image\n");
          exit(1);
    }

    width=(int)(((float)w/h)*height);

    std::cout<<"width "<<width<<" height "<<height<<std::endl;
}
