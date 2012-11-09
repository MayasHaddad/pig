#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GL/glut.h>    
#include <GL/glu.h>
#include <stdlib.h>     
#include <stdio.h>
#include <string.h> 

void Enable_shader(void);
GLuint LoadShader(GLenum type, const char *filename);
GLuint create_program(GLuint* shader_tab,int tab_size);
 
#endif


