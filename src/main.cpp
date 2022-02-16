#include <OpenGLPrj.hpp>

#include <GLFW/glfw3.h>

#include <Shader.hpp>

#include <iostream>
#include <string>
#include <vector>

const std::string program_name = ("Reds Game");

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);



// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


// camera
static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

static bool firstMouse = true;



// yaw is initialized to -90.0 degrees since a yaw of 0.0
// results in a direction vector pointing to the right so we
// initially rotate a bit to the left.


static float yaw = -90.0f;

static float pitch = 0.0f;
static float lastX = 800.0f / 2.0f;
static float lastY = 600.0f / 2.0f;
static float fov = 45.0f;

// timing



static float deltaTime = 0.0f; // time between current frame and last frame
static float lastFrame = 0.0f;

static glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//CALLBACK for KEYS


static int pom=0;
static float transl_pom=0.0f;
static int br_lenta=0;
static int flag_moveA=0;
static int flag_moveD=0;
static int flag_signalA=1;
static int flag_signalD=1;
static int health=3;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        pom++;
    }
    if(pom%2==0) {
        /*
        if (key == GLFW_KEY_A && action == GLFW_PRESS) {
            if (br_lenta != -2) {
                transl_pom = transl_pom - 0.6f;
                br_lenta--;
            }
        }
        if (key == GLFW_KEY_D && action == GLFW_PRESS) {
            if (br_lenta != 2) {
                transl_pom = transl_pom + 0.6f;
                br_lenta++;
            }
        }
         */

        if (key == GLFW_KEY_A && action == GLFW_PRESS) {
            if (br_lenta != -2) {
                flag_moveA=1;

            }
        }
        if (key == GLFW_KEY_D && action == GLFW_PRESS) {
            if (br_lenta != 2) {
                flag_moveD=1;
            }
        }
    }
}




int main() {
    // glfw: initialize and configure

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(
      GLFW_OPENGL_FORWARD_COMPAT,
      GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                          program_name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state

    glEnable(GL_DEPTH_TEST);



    std::string shader_location("../res/shaders/");

    std::string used_shaders("shader");
    std::string material_shader("material");



    Shader ourShader(shader_location + used_shaders + std::string(".vert"),
                     shader_location + used_shaders + std::string(".frag"));
    Shader lightingShader(
            shader_location + material_shader + std::string(".vert"),
            shader_location + material_shader + std::string(".frag"));

    glEnable(GL_BLEND);









    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    float vertices[] = {
            //1--------------    /text------ //2to-------------  text-------
            -20.0f, -20.0f, -0.5f, 0.0f, 0.0f, 20.0f,  -20.0f, -0.5f, 1.0f, 0.0f,
            20.0f,  20.0f,  -0.5f, 1.0f, 1.0f, 20.0f,  20.0f,  -0.5f, 1.0f, 1.0f,
            -20.0f, 20.0f,  -0.5f, 0.0f, 1.0f, -20.0f, -20.0f, -0.5f, 0.0f, 0.0f,

    };

    float verticesTILE[] = {
            0.3f, -0.4f, 0.0f, 1.0f, 1.0f, // top right
            0.3f, -1.2f, 0.0f, 1.0f, 0.0f, // bottom right
            -0.3f, -1.2f, 0.0f, 0.0f, 0.0f, // bottom left
            -0.3f, -0.4f, 0.0f, 0.0f, 1.0f  // top left
    };



    float verticesPTG[] = {
            // positions             // colors           // texture coordinates
            0.2f,  -0.4f, 0.0f,      1.0f, 1.0f, // top right
            0.2f, -1.0f, 0.0f,      1.0f, 0.0f, // bottom right
            -0.2f, -1.0f, 0.0f,     0.0f, 0.0f, // bottom left
            -0.2f,  -0.4f, 0.0f,      0.0f, 1.0f  // top left

            // positions             // colors           // texture coordinates



    };


    float verticesPTG2[] = {
            // positions             // colors           // texture coordinates
            0.8f,  0.5f, 0.0f,      1.0f, 1.0f, // top right
            0.8f, -1.9f, 0.0f,      1.0f, 0.0f, // bottom right
            -0.8f, -1.9f, 0.0f,     0.0f, 0.0f, // bottom left
            -0.8f,  0.5f, 0.0f,      0.0f, 1.0f  // top left

            // positions             // colors           // texture coordinates



    };

    float verticesArrowBody[] = {
            // positions         //color              // pos 2              //colors
            -0.1f, -0.0f, -0.05f, 0.0f,  0.0f,  1.0f, 0.1f,  -0.0f, -0.05f,  0.0f,  0.0f,  1.0f,
            0.1f,  0.5f,  -0.05f, 0.0f,  0.0f,  1.0f, 0.1f,  0.5f,  -0.05f,  0.0f,  0.0f,  1.0f,
            -0.1f, 0.5f,  -0.05f,  0.0f,  0.0f, 1.0f,-0.1f, -0.0f, -0.05f,  0.0f,  0.0f,  1.0f,

            -0.1f, -0.0f, 0.05f,  0.0f,  0.0f,  -1.0f,  0.1f,  -0.0f, 0.05f, 0.0f,  0.0f,  -1.0f,
            0.1f,  0.5f,  0.05f,  0.0f,  0.0f,  -1.0f, 0.1f,  0.5f,  0.05f,  0.0f,  0.0f, -1.0f,
            -0.1f, 0.5f,  0.05f, 0.0f,  0.0f,  -1.0f,  -0.1f, -0.0f, 0.05f,  0.0f,  0.0f, -1.0f,

            -0.1f, 0.5f,  0.05f,  -1.0f, 0.0f,  0.0f,  -0.1f, 0.5f,  -0.05f, -1.0f, 0.0f,  0.0f,
            -0.1f, -0.0f, -0.05f, -1.0f, 0.0f,  0.0f, -0.1f, -0.0f, -0.05f, -1.0f, 0.0f,  0.0f,
            -0.1f, -0.0f, 0.05f, -1.0f, 0.0f,  0.0f,  -0.1f, 0.5f,  0.05f,  -1.0f, 0.0f,  0.0f,

            0.1f,  0.5f,  0.05f,  1.0f,  0.0f,  0.0f,  0.1f,  0.5f,  -0.05f, 1.0f,  0.0f,  0.0f,
            0.1f,  -0.0f, -0.05f, 1.0f,  0.0f,  0.0f, 0.1f,  -0.0f, -0.05f, 1.0f,  0.0f,  0.0f,
            0.1f,  -0.0f, 0.05f, 1.0f,  0.0f,  0.0f,  0.1f,  0.5f,  0.05f,  1.0f,  0.0f,  0.0f,

            -0.1f, -0.0f, -0.05f, 0.0f,  -1.0f, 0.0f,  0.1f,  -0.0f, -0.05f, 0.0f,  -1.0f, 0.0f,
            0.1f,  -0.0f, 0.05f,  0.0f,  -1.0f, 0.0f, 0.1f,  -0.0f, 0.05f,  0.0f,  -1.0f, 0.0f,
            -0.1f, -0.0f, 0.05f, 0.0f,  -1.0f, 0.0f,  -0.1f, -0.0f, -0.05f, 0.0f,  -1.0f, 0.0f,

            -0.1f, 0.5f,  -0.05f, 0.0f,  1.0f,  0.0f,  0.1f,  0.5f,  -0.05f, 0.0f,  1.0f,  0.0f,
            0.1f,  0.5f,  0.05f,  0.0f,  1.0f,  0.0f, 0.1f,  0.5f,  0.05f,  0.0f,  1.0f,  0.0f,
            -0.1f, 0.5f,  0.05f, 0.0f,  1.0f,  0.0f,  -0.1f, 0.5f,  -0.05f, 0.0f,  1.0f,  0.0f



    };
    float verticesHead[]={
            -0.2f, 0.5f, 0.05f,0.0f,  0.0f,  1.0f, //levo
            0.2f, 0.5f, 0.05f,1.0f,  0.0f,  0.0f,//desno
            0.0f, 0.7f, 0.05f,0.0f,  0.0f,  1.0f//gore
    };
    float verticesHeadSupport1[]={
            0.0f, 0.7f, 0.05f, 0.0f,  0.0f,  1.0f, //gore levo
            0.0f, 0.7f, -0.05f, 0.0f,  0.0f,  1.0f, //gore desno
            0.2f, 0.5f, 0.05f, 1.0f,  0.0f,  0.0f,
            0.2f, 0.5f, -0.05f, 1.0f,  0.0f,  0.0f

    };
    float verticesHeadSupport2[]={
            0.0f, 0.7f, -0.05f, 0.0f,  0.0f,  1.0f,
            0.0f, 0.7f, 0.05f, 0.0f,  0.0f,  1.0f,

            -0.2f, 0.5f, 0.05f, 1.0f,  0.0f,  0.0f,
            -0.2f, 0.5f, -0.05f, 1.0f,  0.0f,  0.0f

    };
    float verticesHeadSupport3[]={

            -0.2f, 0.5f, 0.05f,1.0f,  0.0f,  0.0f,
            - 0.2f, 0.5f, -0.05f,1.0f,  0.0f,  0.0f,
            0.2f, 0.5f, 0.05f,1.0f,  0.0f,  0.0f,
            0.2f, 0.5f, -0.05f,1.0f,  0.0f,  0.0f

    };

    unsigned int indices1[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int indices2[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int indices3[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int indicesTILE[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    unsigned int indicesPTG[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int indicesPTG2[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


//--------------------------------------------------------------------------------------------------------------------------------------------------------
    unsigned int VBOBODY, VAOBODY;
    glGenVertexArrays(1, &VAOBODY);
    glGenBuffers(1, &VBOBODY);

    glBindBuffer(GL_ARRAY_BUFFER, VBOBODY);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArrowBody), verticesArrowBody, GL_STATIC_DRAW);

    glBindVertexArray(VAOBODY);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    unsigned int VBOHead, VAOHead;
    glGenVertexArrays(1, &VAOHead);
    glGenBuffers(1, &VBOHead);

    glBindBuffer(GL_ARRAY_BUFFER, VBOHead);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHead), verticesHead, GL_STATIC_DRAW);

    glBindVertexArray(VAOHead);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    unsigned int VBOHeadSupport1, VAOHeadSupport1, EBOHeadSupport1;
    glGenVertexArrays(1, &VAOHeadSupport1);
    glGenBuffers(1, &VBOHeadSupport1);
    glGenBuffers(1, &EBOHeadSupport1);
    glBindBuffer(GL_ARRAY_BUFFER, VBOHeadSupport1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHeadSupport1), verticesHeadSupport1, GL_STATIC_DRAW);

    glBindVertexArray(VAOHeadSupport1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOHeadSupport1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int VBOHeadSupport2, VAOHeadSupport2, EBOHeadSupport2;
    glGenVertexArrays(1, &VAOHeadSupport2);
    glGenBuffers(1, &VBOHeadSupport2);
    glGenBuffers(1, &EBOHeadSupport2);
    glBindBuffer(GL_ARRAY_BUFFER, VBOHeadSupport2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHeadSupport2), verticesHeadSupport2, GL_STATIC_DRAW);

    glBindVertexArray(VAOHeadSupport2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOHeadSupport2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int VBOHeadSupport3, VAOHeadSupport3, EBOHeadSupport3;
    glGenVertexArrays(1, &VAOHeadSupport3);
    glGenBuffers(1, &VBOHeadSupport3);
    glGenBuffers(1, &EBOHeadSupport3);
    glBindBuffer(GL_ARRAY_BUFFER, VBOHeadSupport3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHeadSupport3), verticesHeadSupport3, GL_STATIC_DRAW);

    glBindVertexArray(VAOHeadSupport3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOHeadSupport3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    unsigned int VBOPTG, VAOPTG, EBOPTG;
    glGenVertexArrays(1, &VAOPTG);
    glGenBuffers(1, &VBOPTG);
    glGenBuffers(1, &EBOPTG);

    glBindVertexArray(VAOPTG);

    glBindBuffer(GL_ARRAY_BUFFER, VBOPTG);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPTG), verticesPTG, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPTG);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPTG), indicesPTG, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);




    unsigned int VBOPTG2, VAOPTG2, EBOPTG2;
    glGenVertexArrays(1, &VAOPTG2);
    glGenBuffers(1, &VBOPTG2);
    glGenBuffers(1, &EBOPTG2);

    glBindVertexArray(VAOPTG2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOPTG2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPTG2), verticesPTG2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOPTG2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesPTG2), indicesPTG2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //--------------------------------------------------------------------------------------------------------------------------------------
    unsigned int VBOTILE, VAOTILE, EBOTILE;
    glGenVertexArrays(1, &VAOTILE);
    glGenBuffers(1, &VBOTILE);
    glGenBuffers(1, &EBOTILE);
    glBindVertexArray(VAOTILE);

    glBindBuffer(GL_ARRAY_BUFFER, VBOTILE);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTILE), verticesTILE, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOTILE);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTILE), indicesTILE, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    unsigned int texture1, texture2, textureS2, textureS3, textureS4, textureTILE, textureL1, textureL2, textureL3, textureL4, textureL5, textureL6, textureL7;
    unsigned int textureD1, textureD2, textureD3, textureD4, textureD5, textureD6, textureD7, textureD8;
    unsigned int textureZ1, textureZ2, textureZ3, textureZ4,textureZ5, textureZ6;

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // texture 1


    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("../res/textures/grass1.jpg", &width,
                                    &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    // texture 1



    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_1.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture 2




    glGenTextures(1, &textureS2);
    glBindTexture(GL_TEXTURE_2D, textureS2);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_2.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture 3




    glGenTextures(1, &textureS3);
    glBindTexture(GL_TEXTURE_2D, textureS3);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_3.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture 4




    glGenTextures(1, &textureS4);
    glBindTexture(GL_TEXTURE_2D, textureS4);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_4.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

//textureTILE



    glGenTextures(1, &textureTILE);
    glBindTexture(GL_TEXTURE_2D, textureTILE);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/TILE.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//TEXTURE L1


    glGenTextures(1, &textureL1);
    glBindTexture(GL_TEXTURE_2D, textureL1);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_L1.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

//TEXTURE L2

    glGenTextures(1, &textureL2);
    glBindTexture(GL_TEXTURE_2D, textureL2);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_L2.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

//TEXTURE L3

    glGenTextures(1, &textureL3);
    glBindTexture(GL_TEXTURE_2D, textureL3);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_L3.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

//TEXTURE L4

    glGenTextures(1, &textureL4);
    glBindTexture(GL_TEXTURE_2D, textureL4);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_L4.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


//TEXTURE L5

    glGenTextures(1, &textureL5);
    glBindTexture(GL_TEXTURE_2D, textureL5);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_L5.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


//TEXTURE L6


    glGenTextures(1, &textureL6);
    glBindTexture(GL_TEXTURE_2D, textureL6);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_L6.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

//TEXTURE L7

    glGenTextures(1, &textureL7);
    glBindTexture(GL_TEXTURE_2D, textureL7);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_L7.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture D1


    glGenTextures(1, &textureD1);
    glBindTexture(GL_TEXTURE_2D, textureD1);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D1.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    // texture D2


    glGenTextures(1, &textureD2);
    glBindTexture(GL_TEXTURE_2D, textureD2);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D2.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture D3


    glGenTextures(1, &textureD3);
    glBindTexture(GL_TEXTURE_2D, textureD3);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D3.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    // texture D4



    glGenTextures(1, &textureD4);
    glBindTexture(GL_TEXTURE_2D, textureD4);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D4.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    // texture D5



    glGenTextures(1, &textureD5);
    glBindTexture(GL_TEXTURE_2D, textureD5);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D5.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture D6


    glGenTextures(1, &textureD6);
    glBindTexture(GL_TEXTURE_2D, textureD6);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D6.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture D7


    glGenTextures(1, &textureD7);
    glBindTexture(GL_TEXTURE_2D, textureD7);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D7.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture D8


    glGenTextures(1, &textureD8);
    glBindTexture(GL_TEXTURE_2D, textureD8);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/still_D8.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

//-------------------------------------------------------------------------------------------------------------------------

    // texture D8


    glGenTextures(1, &textureZ1);
    glBindTexture(GL_TEXTURE_2D, textureZ1);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/zigg_s1.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // texture Z2


    glGenTextures(1, &textureZ2);
    glBindTexture(GL_TEXTURE_2D, textureZ2);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/zigg_s2.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    // texture D8


    glGenTextures(1, &textureZ3);
    glBindTexture(GL_TEXTURE_2D, textureZ3);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/zigg_s3.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);




    // texture D8


    glGenTextures(1, &textureZ4);
    glBindTexture(GL_TEXTURE_2D, textureZ4);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/zigg_s4.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);






    // texture D8


    glGenTextures(1, &textureZ5);
    glBindTexture(GL_TEXTURE_2D, textureZ5);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/zigg_s5.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    glGenTextures(1, &textureZ6);
    glBindTexture(GL_TEXTURE_2D, textureZ6);
    // set the texture wrapping parameters
    glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(
            true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can
    // find files on any IDE/platform; replace it with your own image path.
    data = stbi_load("../res/textures/zigg_s6.png", &width,
                     &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    ourShader.setInt("textureTILE", 2);

    //Textures for moving left
    ourShader.setInt("textureL1", 3);
    ourShader.setInt("textureL2", 4);
    ourShader.setInt("textureL3", 5);
    ourShader.setInt("textureL4", 6);
    ourShader.setInt("textureL5", 7);
    ourShader.setInt("textureL6", 8);
    ourShader.setInt("textureL7", 9);


    ourShader.setInt("textureD1", 10);
    ourShader.setInt("textureD2", 11);
    ourShader.setInt("textureD3", 12);
    ourShader.setInt("textureD4", 13);
    ourShader.setInt("textureD5", 14);
    ourShader.setInt("textureD6", 15);
    ourShader.setInt("textureD7", 16);
    ourShader.setInt("textureD8", 17);

    ourShader.setInt("textureS2", 18);
    ourShader.setInt("textureS3", 19);
    ourShader.setInt("textureS4", 20);
    ourShader.setInt("textureZ1", 21);
    ourShader.setInt("textureZ2", 22);
    ourShader.setInt("textureZ3", 23);
    ourShader.setInt("textureZ4", 24);
    ourShader.setInt("textureZ5", 25);
    ourShader.setInt("textureZ6", 26);


    // render loop
    // -----------
    int pomosna=0;
    int idle=0;
    int pom_150_pat=0;
    int random_pole[15];
    for(int j=0; j<12; j++)
        random_pole[j]=(std::rand() % (3 + 2)) - 2;
    int current_pos=0;
    float picker[15];
    for(int j=0; j<12; j++)
        picker[j]=random_pole[j]*0.65f;
    float distance[12];
    for(int j=0; j<12; j++)
        distance[j]=0.0f;
    float pomos_y;
    float pomos_ym=0.0f;
    int incrementor=1;
    int pom2=0;
    int pom3=0;
    int pom4=0;
    // printf("%d", random_pole);
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);


        // activate shader
        ourShader.use();
        pomos_y=sin(glfwGetTime() / 2.0f) * 1.0f;
        // pass projection matrix to shader (note that in this case it could change
        // every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov),
                                                static_cast<float>(SCR_WIDTH) /
                                                static_cast<float>(SCR_HEIGHT),
                                                0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        // for (unsigned int i = 0; i < 10; i++) {
        // calculate the model matrix for each object and pass it to shader before
        // drawing
        glm::mat4 model = glm::mat4(
                1.0f);
        model=glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-78.0f), glm::vec3(1.0f, 0.0f, 0.0f));// make sure to initialize matrix to identity matrix first
        // model = glm::translate(model, cubePositions[i]);
        // float angle = 20.0f * i;
        // model =
        //  glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        // }

//---------------------------------------------------------------------------------------------------------------------------------------------------
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureZ1);
        if( (flag_signalA==1) && (flag_signalD==1) &&(pom%2==0)) {

            if (idle == 0) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureZ2);

            } else if (idle == 1) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureZ3);
                // idle++;
            } else if (idle == 2) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureZ5);
                // idle++;
            } else if (idle == 3) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureZ6);
                // idle=0;
            }
        }
        model = glm::mat4(
                1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 2.1f, -7.0f));

        ourShader.setMat4("model", model);
        glBindVertexArray(VAOPTG2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);




//--------------------------------------------------------------------------------------------------------------------------


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        if( (flag_signalA==1) && (flag_signalD==1) &&(pom%2==0)) {
            if (glfwGetTime() > 0.2f && idle < 4) {
                idle++;
                // pomos_ym+=0.3f;
                if(pom4==0) {
                    pom3=1;
                    for (int j = 0; j < incrementor; j++) {
                        distance[j] += 0.3f;
                        random_pole[j] = (std::rand() % (3 + 2)) - 2;

                    }
                    pom3=0;
                }
                if(idle==3)
                {
                    if(pom4==0) {
                        pom3=1;
                        for (int i = 0; i < incrementor; i++) {
                            if (distance[i] >= 5.4f) {
                                if((random_pole[i]-1)==br_lenta)
                                {
                                    health--;
                                }
                                picker[i] = random_pole[i] * 0.65f;
                                distance[i] = 0.0f;
                            }
                        }
                        pom3=0;
                    }
                    if(incrementor<=12) {
                        if(incrementor>=4){
                            if(pom2>=6) {
                                incrementor++;
                                pom2 = 0;
                            }
                        }
                        else{
                            incrementor++;
                        }
                    }
                }
                if (idle == 4) {
                    idle = 0;
                    pom2++;
                }
                glfwSetTime(0.0f);
            }
            if (idle == 0) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture2);

            } else if (idle == 1) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureS2);
                // idle++;
            } else if (idle == 2) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureS3);
                // idle++;
            } else if (idle == 3) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureS4);
                // idle=0;
            }
        }


        model = glm::mat4(
                1.0f);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        if ((flag_moveA==1) && (flag_signalD==1)) {
            flag_signalA=0;
            if(glfwGetTime()>0.05f && pomosna<10){


                transl_pom-=0.06f;
                pomosna++;
                glfwSetTime(0.0f);
            }
            if(pomosna==1)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL1);
            }
            if(pomosna==2)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL2);
            }
            if(pomosna==3)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL3);
            }
            if(pomosna==4)
            {

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL4);
            }
            if(pomosna==5)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL3);
            }
            if(pomosna==6)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL2);
            }
            if(pomosna==7)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL5);
            }
            if(pomosna==8)
            {

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL6);
            }
            if(pomosna==9)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureL7);
            }
            if(pomosna==10)
            {
                flag_signalA=1;
                pomosna=0;
                br_lenta--;
                flag_moveA=0;
                if(pom3==0) {
                    pom4=1;
                    for (int j = 0; j < incrementor; j++) {
                        distance[j] += 0.3f;
                        random_pole[j] = (std::rand() % (3 + 2)) - 2;

                    }
                    pom4=0;
                }
                if(pom3==0) {
                    pom4=1;
                    for (int i = 0; i < incrementor; i++) {

                        if (distance[i] >= 5.4f) {
                            if((random_pole[i]-1)==br_lenta)
                            {
                                health--;
                            }
                            picker[i] = random_pole[i] * 0.65f;
                            distance[i] = 0.0f;
                        }
                    }
                    pom4=0;
                }
                if(incrementor<=12) {
                    if(incrementor>=4){
                        if(pom2>=6) {
                            incrementor++;
                            pom2 = 0;
                        }
                    }
                    else
                    {
                        incrementor++;
                    }
                }
                pom2++;

            }


        }
        if ((flag_moveD==1) && (flag_signalA==1)) {
            flag_signalD=0;
            if(glfwGetTime()>0.05f && pomosna<10){


                transl_pom+=0.06f;
                pomosna++;
                glfwSetTime(0.0f);
            }
            if(pomosna==1)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD1);
            }
            if(pomosna==2)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD2);
            }
            if(pomosna==3)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD3);
            }
            if(pomosna==4)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD4);

            }
            if(pomosna==5)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD5);
            }
            if(pomosna==6)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD4);
            }
            if(pomosna==7)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD6);
            }
            if(pomosna==8)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD7);
            }
            if(pomosna==9)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, textureD8);
            }
            if(pomosna==10)
            {
                flag_signalD=1;
                pomosna=0;
                br_lenta++;
                flag_moveD=0;
                for(int j=0 ;j<incrementor; j++)
                {
                    distance[j]+=0.3f;
                    random_pole[j]=(std::rand() % (3 + 2)) - 2;

                }
                for(int i=0; i<incrementor; i++)
                {
                    if(distance[i]>=5.4f)
                    {
                        if((random_pole[i]-1)==br_lenta)
                        {
                            health--;
                        }
                        picker[i]=random_pole[i]*0.65f;
                        distance[i]=0.0f;
                    }
                }

                if(incrementor<=12) {
                    if(incrementor>=4){
                        if(pom2>=6) {
                            incrementor++;
                            pom2 = 0;
                        }
                    }
                    else
                    {
                        incrementor++;
                    }
                }
                pom2++;
            }

        }
        model = glm::translate(model, glm::vec3(transl_pom, 0.0f, 0.0f));
        ourShader.setMat4("model", model);



        glBindVertexArray(VAOPTG);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


//------------------------------------------------------------------------------------------------------------ARROW BODY
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.setVec3("lightPos", lightPos);


        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation


        // modelBody = glm::translate(modelBody, glm::vec3(-1.3f, -6.4f, 1.0f));






        //current_pos = random_pole;




        //  printf("%f\n",  picker );
        //  printf("%d\n", random_pole);




        // for (unsigned int i = 0; i < 10; i++) {




        for(int i=0; i<incrementor; i++)
        {

            glm::mat4 modelBody = glm::mat4(1.0f);
            modelBody = glm::rotate(modelBody, glm::radians(-77.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            lightingShader.setMat4("model", modelBody);

            // render the cube
            modelBody = glm::rotate(modelBody, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //printf("%d %d %d\n", i, picker[i], incrementor);

            modelBody = glm::translate(modelBody, glm::vec3(picker[i],  distance[i]-6.4f, 1.0f));
            lightingShader.setMat4("model", modelBody);
            glBindVertexArray(VAOBODY);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(VAOHead);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(VAOHeadSupport1);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(VAOHeadSupport2);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(VAOHeadSupport3);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            modelBody = glm::translate(modelBody, glm::vec3(0.0f, 0.0f, -0.1f));
            lightingShader.setMat4("model", modelBody);
            glBindVertexArray(VAOHead);
            glDrawArrays(GL_TRIANGLES, 0, 3);

        }




        // modelBody = glm::translate(modelBody, glm::vec3(picker, -6.4f, 1.0f));








//-------------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------------------------


        ourShader.use();


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureTILE);
        glBindVertexArray(VAOTILE);

        float pravo = -1.5f;
        float ips=-0.8f;
        for(unsigned int j = 0; j < 7; j++) {
            float desno=-1.3f;
            for (unsigned int i = 0; i < 5; i++) {

                model = glm::mat4(
                        1.0f);
                model = glm::translate(model, glm::vec3(desno, ips, pravo));
                model = glm::rotate(model, glm::radians(-77.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                ourShader.setMat4("model", model);
                desno += 0.65f;
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            }
            pravo-=0.9f;
            ips+=0.2f;
        }
        glfwSetKeyCallback(window, key_callback);

/*      model = glm::mat4(
              1.0f);

      model=glm::translate(model, glm::vec3(0.0f, -0.8f, -1.5f));
      model = glm::rotate(model, glm::radians(-78.0f), glm::vec3(1.0f, 0.0f, 0.0f));// make sure to initialize matrix to identity matrix first
      // model = glm::translate(model, cubePositions[i]);
      // float angle = 20.0f * i;
      // model =
      //  glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      ourShader.setMat4("model", model);

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); */
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
        // etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAOPTG);
    glDeleteBuffers(1, &VBOPTG);
    glDeleteBuffers(1, &EBOPTG);
    glDeleteVertexArrays(1, &VAOPTG2);
    glDeleteBuffers(1, &VBOPTG2);
    glDeleteBuffers(1, &EBOPTG2);
    glDeleteVertexArrays(1, &VAOTILE);
    glDeleteBuffers(1, &VBOTILE);
    glDeleteVertexArrays(1, &VAOBODY);
    glDeleteBuffers(1, &VBOBODY);
    glDeleteVertexArrays(1, &VAOHead);
    glDeleteBuffers(1, &VBOHead);
    glDeleteVertexArrays(1, &VAOHeadSupport1);
    glDeleteBuffers(1, &VBOHeadSupport1);
    glDeleteVertexArrays(1, &VAOHeadSupport2);
    glDeleteBuffers(1, &VBOHeadSupport2);
    glDeleteVertexArrays(1, &VAOHeadSupport3);
    glDeleteBuffers(1, &VBOHeadSupport3);
    glDeleteBuffers(1, &EBOHeadSupport1);
    glDeleteBuffers(1, &EBOHeadSupport2);
    glDeleteBuffers(1, &EBOHeadSupport3);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(health==0)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5f * deltaTime;
    if(pom%2==1) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -=
                    glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos +=
                    glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }


}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposd, double yposd) {
    float xpos = static_cast<float>(xposd);
    float ypos = static_cast<float>(yposd);
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset =
            lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= static_cast<float>(yoffset);
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
