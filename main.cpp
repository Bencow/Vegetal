//link statically glew but doesn't work...
//#define GLEW_STATIC

//Library for loading textures (Simple OpenGL Image Library)
#include "soil/src/SOIL.h"

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

#define speedCamera 1.0f
#define speedRotation 10.0f
#define PRIMITIVE 1


//just to test quickly
bool go_update = false;
bool go_update_leaves = false;

//Camera gesture
float camera_x = 5.0f;
float camera_y = 0.0f;
float camera_z = 1.0f;
float camera_target_x = 0.0f;
float camera_target_y = 0.0f;
float camera_target_z = 1.0f;
float camera_angle_rotation = 0;

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
  if(key == GLFW_KEY_L && action == GLFW_PRESS)
  {
    go_update_leaves = true;
  }

  else if(key == GLFW_KEY_A && action == GLFW_PRESS){
	  camera_angle_rotation -= speedRotation;
	  if (camera_angle_rotation < 0) {
		  camera_angle_rotation = 360;
	  }
  }
  else if(key == GLFW_KEY_W && action == GLFW_PRESS){	
	glm::vec3 myVecDirct(camera_x - camera_target_x, camera_y - camera_target_y, camera_z - camera_target_z);
	myVecDirct = glm::normalize(myVecDirct);
	camera_x -= myVecDirct.x * speedCamera;
	camera_y -= myVecDirct.y * speedCamera;
	camera_z -= myVecDirct.z * speedCamera;

  }
  else if(key == GLFW_KEY_S && action == GLFW_PRESS){
	  glm::vec3 myVecDirct(camera_x - camera_target_x, camera_y - camera_target_y, camera_z - camera_target_z);
	  myVecDirct = glm::normalize(myVecDirct);
	  camera_x += myVecDirct.x * speedCamera;
	  camera_y += myVecDirct.y * speedCamera;
	  camera_z += myVecDirct.z * speedCamera;
  }
  else if(key == GLFW_KEY_D && action == GLFW_PRESS){
	  camera_angle_rotation+= speedRotation;
	  if (camera_angle_rotation > 360) {
		  camera_angle_rotation = 0;
	  }
  }

  else if(key == GLFW_KEY_R && action == GLFW_PRESS){
    camera_target_x += speedCamera;
  }
  else if(key == GLFW_KEY_F && action == GLFW_PRESS){
    camera_target_x -= speedCamera;
  }
  else if(key == GLFW_KEY_T && action == GLFW_PRESS){
    camera_target_y += speedCamera;
  }
  else if(key == GLFW_KEY_G && action == GLFW_PRESS){
    camera_target_y -= speedCamera;
  }
  else if(key == GLFW_KEY_UP && action == GLFW_PRESS){
    camera_target_z += speedCamera;
  }
  else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
    camera_target_z -= speedCamera;
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


GLuint createShader(GLenum type, std::string shader_name) 
{
    std::ifstream in(shader_name);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    const char* source = contents.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    getShaderCompileStatus(shader);
    return shader;
}
 
void setShaderAttributs(GLint posAttrib, GLint colourAttrib, GLint normalAttrib, GLint textureAttrib)
{
    //TODO: link vertex data to shader
    //Param : 1 input
    //        2 nbr of value for that input
    //        3 type of component
    //        4 do the components have to be normalized (only the normal !)
    //        5 number of bit for the other components
    //        6 offset
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    glVertexAttribPointer(colourAttrib, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(colourAttrib);

    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_TRUE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(normalAttrib);

    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(textureAttrib);
}


void printSkeleton(std::vector< std::vector<Vertex*> >& skeleton)
{
    std::cout << "print skeleton" << std::endl;
    for(int i = 0 ; i < skeleton.size() ; i++)
    {
        for(int j = 0 ; j < skeleton[i].size() ; j++)
        {
            std::cout << *skeleton[i][j];
        }
        std::cout << std::endl;
    }
}

void add_volume_branch(std::vector<GLfloat> &vertices, std::vector< std::vector<Vertex*> >& skeleton, int type_primitive)
{
    if(type_primitive == 0)//Simple vertex
    {
        //fill the vector vertices with all the points contained in the skeleton
        //For all the branches
        for(int i = 0 ; i < skeleton.size() ; i++)
        {
            //for all the vertices in the branch n°i
            for(int j = 0 ; j < skeleton[i].size() ; j++)
            {
                //copy all the floats of the vertex in the array vertices
                skeleton[i][j]->fillVectorVertices(vertices);
            }
        }
    }
    if(type_primitive == 1)//line between the current vertex and the next one
    {
        //for all branches
        for(int i = 0 ; i < skeleton.size() ; i++)
        {
            //for all vertices in branch i (except the last one)
            for(int j = 0 ; j < skeleton[i].size()-1 ; ++j)
            {
                //copy the current vertex and the next one to draw a line between both
                skeleton[i][j]->fillVectorVertices(vertices);
                skeleton[i][j+1]->fillVectorVertices(vertices);
            }
        }
    }
    std::cout << "END add volume" << std::endl;
}

void add_volume_leaves(std::vector<GLfloat>& leaves, std::vector<Vertex*> skeleton_leaves, int primitive)
{
    if(true)//add the type of primitive after
    {
        for(uint i = 0 ; i < skeleton_leaves.size() ; ++i)
        {
            //copy all the floats of the vertex in the array vertices
            skeleton_leaves[i]->fillVectorVertices(leaves);
        }
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
    ////////////////////////////////////
    //       Load vertices            //
    ////////////////////////////////////

    //create a plant
    Vect vDepart(0.0f, 0.0f, 1.0f);
    Vertex pointDepart(0.0f, 0.0f, 0.0f);
    t_data dataDepart;

  	readParameter(dataDepart);

    Plant newPlant(&pointDepart, dataDepart, vDepart);

    std::vector< std::vector<Vertex*> > skeleton_branch;
    std::vector<Vertex*> skeleton_leaves;
    std::vector<GLfloat> vertices_branch;
    std::vector<GLfloat> vertices_leaves;
    GLfloat vertices_ground[] =
    {
        //Pos                  colour               normal                tex
         1.0f,  1.0f, -0.6f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
        -1.0f,  1.0f, -0.6f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
        -1.0f, -1.0f, -0.6f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,

         1.0f,  1.0f, -0.6f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
         1.0f, -1.0f, -0.6f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
        -1.0f, -1.0f, -0.6f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
        
    };

    //update the plant once
    newPlant.update();
    newPlant.fillSkeleton(skeleton_branch);

    ///////////////////////
    //create buffers     //
    ///////////////////////
    GLuint vao_branch;
    GLuint vao_leaves;
    GLuint vao_ground;
    glGenVertexArrays(1, &vao_branch);
    glGenVertexArrays(1, &vao_leaves);
    glGenVertexArrays(1, &vao_ground);
    //generate vertex buffers
    GLuint vbo_branch;
    GLuint vbo_leaves;
    GLuint vbo_ground;
    glGenBuffers(1, &vbo_branch);
    glGenBuffers(1, &vbo_leaves);
    glGenBuffers(1, &vbo_ground);

    ///////////////////////////////
    //load all shaders           //
    ///////////////////////////////
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, "shader.vert");
    //GLuint geomShader = createShader(GL_GEOMETRY_SHADER, "shader.geom");
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, "shader.frag");
    
    //TODO: link shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, geomShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    GLint colourAttrib = glGetAttribLocation(shaderProgram, "colour");
    GLint normalAttrib = glGetAttribLocation(shaderProgram, "normal");
    GLint textureAttrib = glGetAttribLocation(shaderProgram, "texcoord");

    //////////////////////////////////
    //Set up things for the branches//
    //////////////////////////////////
    add_volume_branch(vertices_branch, skeleton_branch, PRIMITIVE);
    //the vao will store the vbo with it and every time you bind it and call 
    //glDrawArrays, it will use the vbo associated with the bound vao
    glBindVertexArray(vao_branch);//use the vao_branch as active vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_branch);//make vbo_leaves the active array buffer
    //Note : the size total of the array is the size of a GLfloat * number of element in the vector (i.e. vertices.size() )
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_branch.size(), vertices_branch.data(), GL_STATIC_DRAW);
    setShaderAttributs(posAttrib, colourAttrib, normalAttrib, textureAttrib);


    //////////////////////////////////
    //Set up things for the leaves  //
    //////////////////////////////////    
    add_volume_leaves(vertices_leaves, skeleton_leaves, 0);
    glBindVertexArray(vao_leaves);//use the vao_branch as active vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_leaves);//make vbo_leaves the active array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_leaves.size(), vertices_leaves.data(), GL_STATIC_DRAW);
    setShaderAttributs(posAttrib, colourAttrib, normalAttrib, textureAttrib);

    
    //////////////////////////////////
    //Set up things for the ground  //
    //////////////////////////////////   
    glBindVertexArray(vao_ground);//use the vao_branch as active vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ground);//make vbo_leaves the active array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_ground), vertices_ground, GL_STATIC_DRAW);
    setShaderAttributs(posAttrib, colourAttrib, normalAttrib, textureAttrib);





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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
        //       TODO: 3D Transforms
        //==================================
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, camera_angle_rotation , glm::vec3(0.0f, 0.0f, 1.0f));
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
        //       TODO: camera gesture
        //==================================
           glm::mat4 view = glm::lookAt(
               glm::vec3(camera_x, camera_y, camera_z), //Camera position
               glm::vec3(camera_target_x, camera_target_y, camera_target_z), //Camera view target
               glm::vec3(0.0f, 0.0f, 1.0f)  //Camera up vector which is usually z
           );
           GLint uniView = glGetUniformLocation(shaderProgram, "view");
           glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

           //TODO: create and load projection matrix
           glm::mat4 proj = glm::perspective(45.0f,                              //VERTICAL FOV
                                             640.f / 480.f,       //aspect ratio
                                             0.1f,              //near plane distance (min z)
                                             100.0f                //Far plane distance (max z)
           );
           GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
           glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

        //==================================
        //          Draw Model
        //==================================
        //Clear color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw background
        //...


        //update tree
        //if SPACE is pressed go_update = true
        if(go_update)
        {
          newPlant.update();
          newPlant.fillSkeleton(skeleton_branch);
          add_volume_branch(vertices_branch, skeleton_branch, PRIMITIVE);
          //make vbo_branch the active array buffer
          glBindBuffer(GL_ARRAY_BUFFER, vbo_branch);
          //copy the data to it
          glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_branch.size(), vertices_branch.data(), GL_STATIC_DRAW);
          go_update = false;
        }
        //update leaves
        if(go_update_leaves)
        {
            newPlant.add_leaves(skeleton_leaves);
            add_volume_leaves(vertices_leaves, skeleton_leaves, 0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo_leaves);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_leaves.size(), vertices_leaves.data(), GL_STATIC_DRAW);
            go_update_leaves = false;
        }

        //draw leaves
        glBindVertexArray(vao_leaves);
        glDrawArrays(GL_POINTS, 0, newPlant.getNumberLeaves()); 

        //Draw branch
        glBindVertexArray(vao_branch);
        //draw the active array buffer
        //Param : 1 type of primitive
        //        2 offset (how many vertices to skip)
        //        3 number of VERTICES not primitives

        if(PRIMITIVE == 0)
            glDrawArrays(GL_POINTS, 0, newPlant.getNumberElementPlant());
        if(PRIMITIVE == 1)
            glDrawArrays(GL_LINES, 0, newPlant.getNumberElementPlant() * 2);
        

        //draw ground
        glBindVertexArray(vao_ground);
        glDrawArrays(GL_TRIANGLES, 0, 6); 




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
    glDeleteBuffers(1, &vbo_branch);
    glDeleteBuffers(1, &vbo_leaves);
    glDeleteVertexArrays(1, &vao_branch);
    glDeleteVertexArrays(1, &vao_leaves);

    //Close OpenGL window and terminate GLFW
    glfwDestroyWindow(window);
    //Finalize and clean up GLFW
    glfwTerminate();

    exit(EXIT_SUCCESS);
    return 0;
}
