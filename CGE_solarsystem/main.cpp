///*
// * ---------------- www.spacesimulator.net --------------
// *   ---- Space simulators and 3d engine tutorials ----
// *
// * Original Author: Damiano Vitulli
// * Porting to OpenGL3.3: Movania Muhammad Mobeen
// * Shaders Functions: Movania Muhammad Mobeen
// *
// * This program is released under the BSD licence
// * By using this program you agree to licence terms on spacesimulator.net copyright page
// *
// */
//#include <iostream>
//#define GLM_FORCE_RADIANS 
//#include <gl/glew.h>
//#include <freeglut.h>
//
//#include "GLSLShader.h"
//#include "tutorial4.h"
//#include "texture.h"
//#include "3dsloader.h"
//
//#include <glm/glm.hpp>
////#include <glm/gtc/matrix_projection.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <cassert>
//
//#pragma comment(lib, "glew32.lib")
// /* Pragma ist präprozessor / Compiler Abrakadabra, pragma's sind die Zaubersprüche des verzweifelten C-Programmierers 
// die man aus obskuren Quellen mit einem Stoßgebet zu kernighan und ritchie 
// in seinen Code einfügt und dann hoffentlich dazu führen dass alles plötzlich komplimiert^^*/
//
//#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);
//
//using namespace std; 
//
//int screen_width=640;
//int screen_height=480;
//
//GLuint vboVerticesID, vboTexCoordID, vboIndicesID, vaoID;
//
//GLsizei stride = sizeof(GLfloat)*3;
//GLSLShader shader;
//
//int filling=1;
//
////Now the object is generic, the cube has annoyed us a little bit, or not?
//obj_type object;
//
//// Absolute rotation values (0-359 degrees) and rotiation increments for each frame
//float rotation_x=0, rotation_x_increment=0.1f;
//float rotation_y=0, rotation_y_increment=0.05f;
//float rotation_z=0, rotation_z_increment=0.03f;
// 
//glm::mat4 P;	//projection matrix;
//
//void InitShaders(void)
//{
//	shader.LoadFromFile(GL_VERTEX_SHADER, "shader.vert");
//	shader.LoadFromFile(GL_FRAGMENT_SHADER, "shader.frag");
//	shader.CreateAndLinkProgram();
//	shader.Use();	
//		shader.AddAttribute("vVertex");
//		shader.AddAttribute("vUV");
//		shader.AddUniform("MVP");
//		shader.AddUniform("textureMap");
//		glUniform1i(shader("textureMap"),0);
//	shader.UnUse();
//
//	GL_CHECK_ERRORS
//}
//void InitVAO() {
//	GL_CHECK_ERRORS
//	//Create vao and vbo stuff
//	glGenVertexArrays(1, &vaoID);
//	glGenBuffers (1, &vboVerticesID);
//	glGenBuffers (1, &vboTexCoordID);
//	glGenBuffers (1, &vboIndicesID);
//
//	GL_CHECK_ERRORS
//
//	glBindVertexArray(vaoID);	 
//		glBindBuffer (GL_ARRAY_BUFFER, vboVerticesID);
//		glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat)*3*object.vertices_qty, &object.vertex[0], GL_STATIC_DRAW);
//		GL_CHECK_ERRORS
//		glEnableVertexAttribArray(shader["vVertex"]);
//		glVertexAttribPointer (shader["vVertex"], 3, GL_FLOAT, GL_FALSE,stride,0);
//		GL_CHECK_ERRORS
//		glBindBuffer (GL_ARRAY_BUFFER, vboTexCoordID);
//		glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat)*2*object.vertices_qty, &object.mapcoord[0], GL_STATIC_DRAW);
//		GL_CHECK_ERRORS
//		glEnableVertexAttribArray(shader["vUV"]);
//		glVertexAttribPointer (shader["vUV"], 2, GL_FLOAT, GL_FALSE,sizeof(GLfloat)*2,0);
//		GL_CHECK_ERRORS
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*3*object.polygons_qty, &object.polygon[0], GL_STATIC_DRAW);
//
//	glBindVertexArray(0);
//
//	GL_CHECK_ERRORS
//}
//void InitGL() {
//	glGetError();
//	GL_CHECK_ERRORS
//	glClearColor(0.0f,0.0f,0.2f,0.0f);	
//	GL_CHECK_ERRORS
//	
//	Load3DS (&object,"shipA_3DS.3ds");
//	InitShaders();	
//	InitVAO();
//	
//	glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
//    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)	
//	GL_CHECK_ERRORS
//	
//    object.id_texture=LoadBitmap("spaceshiptexture.bmp"); // The Function LoadBitmap() return the current texture ID
//	 // If the last function returns -1 it means the file was not found so we exit from the program
//    if (object.id_texture==-1)
//    {
//        cerr<<"Image file: texture1.bmp not found"<<endl;
//        exit (EXIT_FAILURE);
//    }
//	GL_CHECK_ERRORS
//}
//
//void OnRender() {
//	GL_CHECK_ERRORS
//	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
//	//setup matrices
//	glm::mat4 T		= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -300));
//	glm::mat4 Rx	= glm::rotate(T,  rotation_x, glm::vec3(1.0f, 0.0f, 0.0f));
//	glm::mat4 Ry	= glm::rotate(Rx, rotation_y, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 MV	= glm::rotate(Ry, rotation_z, glm::vec3(0.0f, 0.0f, 1.0f));
//    glm::mat4 MVP	= P*MV;
//
//	glBindVertexArray(vaoID);
//	shader.Use();				
//		glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));		
//		glDrawElements(GL_TRIANGLES, object.polygons_qty*3, GL_UNSIGNED_SHORT, 0);
//	shader.UnUse();
//	glBindVertexArray(0);
//
//	glutSwapBuffers();
//}
//
//void OnResize(int w, int h)
//{
//	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
//	//setup the projection matrix
//	P = glm::perspective(45.0f, (GLfloat)w/h, 10.f, 10000.f);
//}
//
//void OnShutdown() { 
//	glDeleteTextures(1, &object.id_texture);
//	glDeleteBuffers(1, &vboVerticesID);
//	glDeleteBuffers(1, &vboTexCoordID);
//	glDeleteBuffers(1, &vboIndicesID);
//	glDeleteVertexArrays(1, &vaoID);
//}
//void OnKey(unsigned char key, int x, int y)
//{        
//    switch (key)
//	{  
//        case ' ':
//            rotation_x_increment=0;
//            rotation_y_increment=0;
//            rotation_z_increment=0;
//        break;
//        case 'r': case 'R':
//            if (filling==0)
//            {
//                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
//                filling=1;
//            }   
//            else 
//            {
//                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
//                filling=0;
//            }
//        break;
//    }
//}
//void OnSpecialKey(int key, int x, int y)
//{        
//    switch (key)
//    {
//        case GLUT_KEY_UP:
//            rotation_x_increment = rotation_x_increment +50.0f;
//        break;
//        case GLUT_KEY_DOWN:
//            rotation_x_increment = rotation_x_increment -50.0f;
//        break;
//        case GLUT_KEY_LEFT:
//            rotation_y_increment = rotation_y_increment +50.0f;
//        break;
//        case GLUT_KEY_RIGHT:
//            rotation_y_increment = rotation_y_increment -50.0f;
//        break;
//    }
//}
//void OnIdle() {
//	/*rotation_x = rotation_x + rotation_x_increment;
//    rotation_y = rotation_y + rotation_y_increment;
//    rotation_z = rotation_z + rotation_z_increment;
//
//    if (rotation_x > 359) rotation_x = 0;
//    if (rotation_y > 359) rotation_y = 0;
//    if (rotation_z > 359) rotation_z = 0;*/
//	
//	glutPostRedisplay();
//}
//
//void main(int argc, char** argv) {
//	atexit(OnShutdown);
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);	
//	glutInitContextVersion (3, 3);
//	glutInitContextFlags (GLUT_CORE_PROFILE | GLUT_DEBUG);
//	glutInitWindowSize(screen_width, screen_height);
//	glutCreateWindow("Tutorial 4 - OpenGL 3.3");
//	
//	glewExperimental = GL_TRUE;
//	GLenum err = glewInit();
//
//	InitGL();
//	glutDisplayFunc(OnRender);
//	glutReshapeFunc(OnResize);
//	//glutKeyboardFunc(OnKey);
//	//glutSpecialFunc(OnSpecialKey);
//	//glutIdleFunc(OnIdle);
//	glutMainLoop();
//}