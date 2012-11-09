
#include "shader.h"

void Enable_shader(void){
GLenum err = glewInit();
if (GLEW_OK != err)
{
    fprintf(stderr, "Error %s\n", glewGetErrorString(err));
    exit(1);
}
fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

if (GLEW_ARB_vertex_program)
    fprintf(stdout, "Status: ARB vertex programs available.\n");

if (glewGetExtension("GL_ARB_fragment_program"))
    fprintf(stdout, "Status: ARB fragment programs available.\n");

if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
    fprintf(stdout, "Status: ARB point sprites available.\n");
}

char* LoadSource(const char *filename)
{
    char *src = NULL;   /* code source de notre shader */
    FILE *fp = NULL;    /* fichier */
    long size;          /* taille du fichier */
    long i;             /* compteur */
    
    
    /* on ouvre le fichier */
    fp = fopen(filename, "r");
    /* on verifie si l'ouverture a echoue */
    if(fp == NULL)
    {
        fprintf(stderr, "impossible d'ouvrir le fichier '%s'\n", filename);
        return NULL;
    }
    
    /* on recupere la longueur du fichier */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    
    /* on se replace au debut du fichier */
    rewind(fp);
    
    /* on alloue de la memoire pour y placer notre code source */
    src = (char*) malloc(size+1); /* +1 pour le caractere de fin de chaine '\0' */
    if(src == NULL)
    {
        fclose(fp);
        fprintf(stderr, "erreur d'allocation de memoire!\n");
        return NULL;
    }
    
    /* lecture du fichier */
    for(i=0; i<size; i++)
        src[i] = fgetc(fp);
    
    /* on place le dernier caractere a '\0' */
    src[size] = '\0';
    
    fclose(fp);
    
    return src;
}

GLuint LoadShader(GLenum type, const char *filename)
{
    GLuint shader = 0;
    GLsizei logsize = 0;
    GLint compile_status = GL_TRUE;
    char *log = NULL;
    char *src = NULL;
    
    /* creation d'un shader de sommet */
    shader = glCreateShader(type);
    if(shader == 0)
    {
        fprintf(stderr, "impossible de creer le shader\n");
        return 0;
    }
    
    /* chargement du code source */
    src = LoadSource(filename);
    if(src == NULL)
    {    
        glDeleteShader(shader);
        return 0;
    }
    
    /* assignation du code source */
    glShaderSource(shader, 1, (const GLchar**)&src, NULL);
    
    /* compilation du shader */
    glCompileShader(shader);
    
    /* liberation de la memoire du code source */
    free(src);
    src = NULL;
    
    /* verification du succes de la compilation */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if(compile_status != GL_TRUE)
    {
        
        
        /* on recupere la taille du message d'erreur */
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        
        /* on alloue un espace memoire dans lequel OpenGL ecrira le message */
        log =(char*) malloc(logsize + 1);
      
        memset(log, '\0', logsize + 1);
        
        glGetShaderInfoLog(shader, logsize, &logsize, log);
        fprintf(stderr, "impossible de compiler le shader '%s' :\n%s", filename, log);
        
        free(log);
        glDeleteShader(shader);
        
        return 0;
    }
    
    return shader;
}

GLuint create_program(GLuint* shader_tab,int tab_size)
{

GLuint program = 0;
GLsizei logsize = 0;
GLint link_status = GL_TRUE;
char *log = NULL;    

//cree un program
program = glCreateProgram();
if(program == 0)
    {
        fprintf(stderr, "impossible de creer le program\n");
        return 0;
    }
/*load un shader
shader = LoadShader(GLenum type, const char *filename);
*/

//attache un shader a  un program
for(int i =0;i<tab_size;i++)
	glAttachShader(program,shader_tab[i]);
/*detache un shader
glDetachShader(program,shader);
*/
//liyage d'un program
glLinkProgram(program);

//* verification du succes de la linkage 
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if(link_status != GL_TRUE)
    {
        
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logsize);
        
        
        log =(char*) malloc(logsize + 1);
       
        memset(log, '\0', logsize + 1);
        
        glGetProgramInfoLog(program, logsize, &logsize, log);
        fprintf(stderr, "impossible de linker le program :\n%s", log);
        
       
        free(log);
        glDeleteProgram(program);
        
        return 0;
    }

return program;

}

