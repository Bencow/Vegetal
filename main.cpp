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


//just to test quickly
bool go_update = false;
bool go_update_graphic = false;

//Camera gesture
float camera_x = 5.0f;
float camera_y = 0.0f;
float camera_z = 1.0f;
float camera_target_x = 0.0f;
float camera_target_y = 0.0f;
float camera_target_z = 1.0f;
float camera_angle_rotation = 0;



int PRIMITIVE = 0;

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
  else if(key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){
	  camera_angle_rotation -= speedRotation;
	  if (camera_angle_rotation < 0) {
		  camera_angle_rotation = 360;
	  }
  }
  else if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
	glm::vec3 myVecDirct(camera_x - camera_target_x, camera_y - camera_target_y, camera_z - camera_target_z);
	myVecDirct = glm::normalize(myVecDirct);
	camera_x -= myVecDirct.x * speedCamera;
	camera_y -= myVecDirct.y * speedCamera;
	camera_z -= myVecDirct.z * speedCamera;

  }
  else if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
	  glm::vec3 myVecDirct(camera_x - camera_target_x, camera_y - camera_target_y, camera_z - camera_target_z);
	  myVecDirct = glm::normalize(myVecDirct);
	  camera_x += myVecDirct.x * speedCamera;
	  camera_y += myVecDirct.y * speedCamera;
	  camera_z += myVecDirct.z * speedCamera;
  }
  else if(key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
	  camera_angle_rotation+= speedRotation;
	  if (camera_angle_rotation > 360) {
		  camera_angle_rotation = 0;
	  }
  }
  else if(key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    camera_target_z += speedCamera;
  }
  else if(key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){
    camera_target_z -= speedCamera;
  }

  else if (key == GLFW_KEY_B && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
	  PRIMITIVE++;
	  if (PRIMITIVE > 2) {
		  PRIMITIVE = 0;
	  }

	  go_update_graphic = true;
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

void addVolume(std::vector<GLfloat> &vertices, std::vector< std::vector<Vertex*> >& skeleton, int type_primitive)
{

	vertices.clear();

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
	if (type_primitive == 2) //Cylinder
	{
		//for all branches
		for (int i = 0; i < skeleton.size(); i++)
		{
			//for all vertices in branch i (except the last one)
			for (int j = 0; j < skeleton[i].size() - 1; ++j)
			{

				Vertex* v1 = skeleton[i][j];
				Vertex* v2 = skeleton[i][j + 1];
				
				Vect w(v2->getX() - v1->getX(), v2->getY() - v1->getY(), v2->getZ() - v1->getZ());
				Vect u= giveOrthoVec(w);

				glm::vec3 myVec(u.getX(), u.getY(), u.getZ());
				myVec = glm::normalize(myVec);

				u.setX(myVec.x);
				u.setY(myVec.y);
				u.setZ(myVec.z);

				Vect v = crossProduct(w, u);


				Vertex p1;
				Vertex p2;

				
				for (int i = 0; i < 360; i++) {
			
					p1.setX(v1->getX() + (cos(i) * u.getX() + sin(i)* v.getX())* 0.2f); //1.0f size to change after
					p1.setY(v1->getX() + (cos(i) * u.getY() + sin(i)* v.getY())* 0.2f);
					p1.setZ(v1->getZ() + (cos(i) * u.getZ() + sin(i)* v.getZ())* 0.2f);

					/*
					p2.setX(p1.getX() + w.getX());
					p2.setY(p1.getY() + w.getY());
					p2.setZ(p1.getZ() + w.getZ());
					*/
					p1.fillVectorVertices(vertices);
					v2->fillVectorVertices(vertices);
				}
				//copy the current vertex and the next one to draw a line between both
				//v1->fillVectorVertices(vertices);
				//v2->fillVectorVertices(vertices);
			}
		}
	}
	
    std::cout << "END add volume" << std::endl;
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

    Vect vDepart(0.0f, 0.0f, 1.0f);

    Vertex pointDepart(0.0f, 0.0f, 0.0f);
    t_data dataDepart;

	readParameter(dataDepart);

    Plant newPlant(&pointDepart, dataDepart, vDepart);

    //display our plant member variables


    newPlant.update();
    // std::cout << newPlant << "\n\nNumber unique vertex : " << newPlant.getNumberUniqueVertexPlant() << "\n";

    //Skeleton is an array of array
    //first dimension of the array is the branch
    //second is the vertex
    std::vector< std::vector<Vertex*> > skeleton;
    newPlant.fillSkeleton(skeleton);

    std::cout << "number branch " << newPlant.getNumberBranch() << std::endl;
    std::cout << "number element " << newPlant.getNumberElementPlant() << std::endl;
    //std::cout << newPlant << "Number unique vertex : " << newPlant.getNumberUniqueVertexPlant() << "\n";



    std::vector<GLfloat> vertices;
    addVolume(vertices, skeleton, PRIMITIVE);


    printSkeleton(skeleton);

    // //print vertices
    // for(uint i = 0 ; i  < vertices.size() ; ++i)
    // {
    //   if((i % 11) == 0)
    //      std::cout << std::endl;
    //   std::cout << vertices[i] << " ";

    // }





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
        //          Update tree
        //==================================

        //if SPACE is pressed go_update = true
        if(go_update)
        {
          newPlant.update();
          newPlant.fillSkeleton(skeleton);
          addVolume(vertices, skeleton, PRIMITIVE);
          glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

          //std::cout << "number branch " << newPlant.getNumberBranch() << std::endl;
          //std::cout << "number element " << newPlant.getNumberElementPlant() << std::endl;
          //std::cout << newPlant << "Number unique vertex : " << newPlant.getNumberUniqueVertexPlant() << "\n";


          //printSkeleton(skeleton);

          // //print vertices
          // for(uint i = 0 ; i  < vertices.size() ; ++i)
          // {
          //   if((i % 11) == 0)
          //      std::cout << std::endl;
          //   std::cout << std::setw(12) << vertices[i] << " ";

          // }

          go_update = false;
        }
		else if (go_update_graphic) {
			newPlant.fillSkeleton(skeleton);
			addVolume(vertices, skeleton, PRIMITIVE);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

			go_update_graphic = false;
		}

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

        //at the beginning, draw a simple line
        //number of edge to draw is equal to the number of vertices + 1 because there is no loop in this tree
        //Param : 1 type of primitive
        //        2 offset (how many vertices to skip)
        //        3 number of VERTICES not primitives

        if(PRIMITIVE == 0)
            glDrawArrays(GL_POINTS, 0, newPlant.getNumberElementPlant());
        if(PRIMITIVE == 1)
            glDrawArrays(GL_LINES, 0, newPlant.getNumberElementPlant() * 2);
		if (PRIMITIVE == 2)
			glDrawArrays(GL_LINES, 0, newPlant.getNumberElementPlant() * 2 * 360);


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
