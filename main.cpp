//link statically glew but doesn't work...
//#define GLEW_STATIC


#include <GL/glew.h>

#include <fstream> //fstream
#include <ctime>
#include <chrono>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
#include<iostream>

//Matrix libraries
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


//Other files of the project
#include "Vect.hpp"
#include "Vertex.hpp"
#include "Branch.hpp"
#include "Plant.hpp"

//--------------------
//  OpenGL functions
//--------------------

//Define an error callback
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
    getchar();
}
//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
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



int main( void )
{
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

  //--------------------------------
  //  Generation of the vertices
  //--------------------------------

  Vect vDepart(1.0f, 0.0f, 0.0f);
  Vertex pointDepart(1.0f, 1.0f, 1.0f);
  t_data dataDepart;
  dataDepart.sizeNewVertices = 1.0f;
  dataDepart.varX = 0.0f;
  dataDepart.varY = 0.0f;
  dataDepart.varZ = 0.0f;

  dataDepart.sizeMaxBranch = 4;

  Plant newPlant(&pointDepart, dataDepart, vDepart);

  std::cout << newPlant;
  newPlant.update();
  newPlant.update();

  std::cout << newPlant << "\n\nNumber unique vertex : " << newPlant.getNumberUniqueVertexPlant() << "\n";

  GLfloat* vertices  = new GLfloat[newPlant.getNumberFloatPlant()];

  newPlant.fillGfloatArray(vertices);

  for(int i = 0; i < (int)newPlant.getNumberFloatPlant(); i++){
    if(i%11 == 0){
      std::cout << std::endl;
    }
    std::cout << " " << vertices[i];
  }

  //Create Vertex array object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Generate vertex buffers
  GLuint vbo;
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

  //Load shader source file
  std::ifstream in("shader.vert");
  std::string contents((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
  const char* vertSource = contents.c_str();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertSource, NULL);
  glCompileShader(vertexShader);
  getShaderCompileStatus(vertexShader);

  //Load and compile fragment shader shader.frag
  std::ifstream in2("shader.frag");
  std::string contents2((std::istreambuf_iterator<char>(in2)),std::istreambuf_iterator<char>());
  const char* fragSource = contents2.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragSource, NULL);
  glCompileShader(fragmentShader);
  getShaderCompileStatus(fragmentShader);

  //Link shaders into a program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  //Link vertex data to shader
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);//avant dernier param = 7 * sizeof(float)
  glEnableVertexAttribArray(posAttrib);
  GLint colourAttrib = glGetAttribLocation(shaderProgram, "colour");
  glVertexAttribPointer(colourAttrib, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(colourAttrib);
  GLint normalAttrib = glGetAttribLocation(shaderProgram, "normal");
  glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(normalAttrib);
  GLint textureAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
  glEnableVertexAttribArray(textureAttrib);

  glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

  //Transforms :
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


  clock_t start = std::clock();
  do
  {
      double frame_time = (double) (clock()-start) / double(CLOCKS_PER_SEC);
      float period = 5; //seconds
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
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDrawArrays(GL_LINES, 0, 4);
      //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      //Swap buffers
      glfwSwapBuffers(window);
      //Get and organize events, like keyboard and mouse input, window resizing, etc...
      glfwPollEvents();
  } //Check if the ESC key had been pressed or if the window had been closed

  while (!glfwWindowShouldClose(window));
  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  //Close OpenGL window and terminate GLFW
  glfwDestroyWindow(window);
  //Finalize and clean up GLFW
  glfwTerminate();
  delete vertices;
  exit(EXIT_SUCCESS);

  return 0;
}
