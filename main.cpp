//link statically glew but doesn't work...
//#define GLEW_STATIC

//Library for loading textures (Simple OpenGL Image Library)
#include <soil/src/SOIL.h>

#include <GL/glew.h>

#include<iostream> //cout
#include<iomanip>//setw
#include <fstream> //fstream
#include <vector>
#include <ctime>
#include <chrono>


//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

//Matrix libraries
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Plant.hpp"
#include "Branch.hpp"
#include "Vect.hpp"
#include "Vertex.hpp"
#include "Data.hpp"

#define speedCamera 0.1f


//just to test quickly 
bool go_update = false;

//Define an error callback
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
    getchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  ///////////////////////////////////////////
  // WARNING : the keyboard is a qwerty !  //
  ///////////////////////////////////////////

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  glfwSetWindowShouldClose(window, GL_TRUE);

  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
  {
    go_update = true;
  }
}

bool getShaderCompileStatus(GLuint shader){
    //Get status
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_TRUE){
        return true;
    } else {
        //Get log
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cout << buffer << std::endl;
        return false;
    }
}

GLuint createShader(GLenum type, const GLchar* src) 
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    getShaderCompileStatus(shader);
    return shader;
}
 
void manage_keyboadr_events(std::vector<GLfloat> &vertices, Plant& p)
{
  float camera_x = 0.5f;
  float camera_y = 0.5f;
  float camera_z = 0.5f;
  // float camera_target_x = 0.0f;
  // float camera_target_y = 0.0f;
  // float camera_target_z = 0.0f;

  char inputGive;

  inputGive = getchar();

  switch (inputGive) {
    /////////////////////////////Update plant
  case 'u':
    p.update();
    std::cout << p << "\n\n Number element : " << p.getNumberElementPlant() << "\n";
    p.fillVectorVertices(vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    break;
  case 'a':
    camera_x += speedCamera;
    break;
  case 'q':
    camera_x -= speedCamera;
    break;
  case 'z':
    camera_y += speedCamera;
    break;
  case 's':
    camera_y -= speedCamera;
    break;
  case 'e':
    camera_z += speedCamera;
    break;
  case 'd':
    camera_z -= speedCamera;
    break;
  default :
    break;
  }
}






//////////////////////////////////////
//             MAIN                 //
//////////////////////////////////////



int main( void )
{
    srand(time(NULL));

    //Set the error callback
    glfwSetErrorCallback(error_callback);
    //Initialize GLFW
    if (!glfwInit()){exit(EXIT_FAILURE);}
    //Declare a window object
    GLFWwindow* window;
    //Create a window and create its OpenGL context
    window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
    //If the window couldn't be created
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    //This function makes the context of the specified window current on the calling thread.
    glfwMakeContextCurrent(window);
    //Sets the key callback
    glfwSetKeyCallback(window, key_callback);

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    //If GLEW hasn't initialized
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    //TODO: create Vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Example: generate vertex buffers
    GLuint vbo;
    glGenBuffers(1, &vbo);

    ////////////////////////////////////
    //       TODO: load vertices      //
    ////////////////////////////////////
    std::cout << "Hello world\n\n";

    Vect vDepart(0.025f, 0.025f, 0.5f);
    normalize(vDepart);

    Vertex pointDepart(0.0f, 0.0f, -0.6f);
    t_data dataDepart;
    dataDepart.sizeNewVertices = 0.5f;
    dataDepart.varX = 1.0f;
    dataDepart.varY = -0.5f;
    dataDepart.varZ = 0.0f;

    dataDepart.sizeMaxBranch = 100;
    
    Plant newPlant(&pointDepart, dataDepart, vDepart);

    //display our plant member variables

    
    newPlant.update();
    // std::cout << newPlant << "\n\nNumber unique vertex : " << newPlant.getNumberUniqueVertexPlant() << "\n";
    

    std::vector<GLfloat> vertices;
    newPlant.fillVectorVertices(vertices);


    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Note : the size total of the array is the size of a GLfloat * number of element in the vector (i.e. vertices.size() )
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    //TODO: element buffer (make sure GLuint!!!!)

    //load shader source file
    std::ifstream in("shader.vert");
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    const char* vertSource = contents.c_str();
    //Example: compile a shader source file for vertex shading
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertSource);

    //load fragment shader
    std::ifstream in2("shader.frag");
    std::string contents2((std::istreambuf_iterator<char>(in2)), std::istreambuf_iterator<char>());
    const char* fragSource = contents2.c_str();
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragSource);

    //load geomerty shader
    // std::ifstream in3("shader.geom");
    // std::string contents3((std::istreambuf_iterator<char>(in3)), std::istreambuf_iterator<char>());
    // const char* geomSource = contents3.c_str();
    // //Example: compile a shader source file for vertex shading
    // GLuint geomShader = createShader(GL_GEOMETRY_SHADER, geomSource);


    //TODO: link shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, geomShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    //TODO: link vertex data to shader
    //Param : 1 input
    //        2 nbr of value for that input
    //        3 type of component
    //        4 do the components have to be normalized (only the normal !)
    //        5 number of bit for the other components
    //        6 offset
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    GLint colourAttrib = glGetAttribLocation(shaderProgram, "colour");
    glVertexAttribPointer(colourAttrib, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(colourAttrib);

    GLint normalAttrib = glGetAttribLocation(shaderProgram, "normal");
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(normalAttrib);

    GLint textureAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(textureAttrib);

    //Load texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    //Load image
    int width, height;
    unsigned char* image = SOIL_load_image("kitten.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_DEPTH_TEST);


    //Set a background color
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    //Transforms :
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    //glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    //printf("%f, %f, %f\n", result.x, result.y, result.z);

    //Model matrix transformayion
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");

    //View matrix transformation
    glm::mat4 view = glm::lookAt(glm::vec3(1.2f, 1.2f, 1.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)) ;
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    //perspective projection
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));



    //Main Loop
    //clock_t start = std::clock();
    clock_t start = std::clock();
    go_update = false;
    
    do
    {
        double frame_time = (double) (clock()-start) / double(CLOCKS_PER_SEC);
        float period = 5; //seconds


        //==================================
        //          Update tree
        //==================================

        //if SPACE is pressed go_update = true
        if(go_update)
        {
          newPlant.update();
          newPlant.fillVectorVertices(vertices);
          glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

          std::cout << "number branch " << newPlant.getNumberBranch() << std::endl;
          //std::cout << newPlant << "Number unique vertex : " << newPlant.getNumberUniqueVertexPlant() << "\n";
          /*
          for(uint i = 0 ; i  < vertices.size() ; ++i)
          {
            if((i % 11) == 0)
               std::cout << std::endl;
            std::cout << vertices[i] << " ";
            
          }
          std::cout << std::endl;
          */
          go_update = false;
        }

        //==================================
        //       TODO: 3D Transforms
        //==================================
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, 360 * float(frame_time) / period , glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));//upload the matrux in the vertex shader

        //==================================
        //       TODO: Load a light
        //==================================

        glm::vec4 light_position = view * glm::rotate(model, 360 * float(frame_time) / period , glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(1,0,1.3,1.0);
        GLint uniLightPos = glGetUniformLocation(shaderProgram, "light_position");
        glUniform4fv(uniLightPos, 1, glm::value_ptr(light_position));

        glm::vec4 light_colour(1,1,1,1);
        GLint uniLightCol = glGetUniformLocation(shaderProgram, "light_colour");
        glUniform4fv(uniLightCol, 1, glm::value_ptr(light_colour));

        //==================================
        //          Draw Model
        //==================================
        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //at the beginning, draw a simple line
        //number of edge to draw is equal to the number of vertices + 1 because there is no loop in this tree
        //Param : 1 type of primitive
        //        2 offset (how many vertices to skip)
        //        3 number of VERTICES not primitives
        glDrawArrays(GL_POINTS, 0, newPlant.getNumberElementPlant());
        // glDrawArrays(GL_LINES, 0, newPlant.getNumberElementPlant() * 2);

        //Swap buffers
        glfwSwapBuffers(window);
        //Get and organize events, like keyboard and mouse input, window resizing, etc...
        glfwPollEvents();

    } //Check if the ESC key had been pressed or if the window had been closed
    while (!glfwWindowShouldClose(window));
    
    glDeleteTextures(1, &tex);
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    //glDeleteShader(geomShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    //Close OpenGL window and terminate GLFW
    glfwDestroyWindow(window);
    //Finalize and clean up GLFW
    glfwTerminate();

    exit(EXIT_SUCCESS);
    return 0;
}

int main_()
{
    srand(time(NULL));
    //test maths functions :
    Vect v(0.025f, 0.025f, 0.5f);
    normalize(v);

    for(int i = 0 ; i < 10000 ; i++)
    {
        v = findRandOrthogonal(v);
        normalize(v);
        std::cout << ".";
    }

    
    /*
    int var1 = -35;
    int var2 = 1;

    std::cout << var1 << var2 << std::endl; 
    std::cout << var2 << var1 << std::endl; 

    std::cout << var1 << std::setw(3) << var2 << std::endl; 
    std::cout << var1 << std::setw(3) << var2 << std::endl; 
    */
    return 0;
}

