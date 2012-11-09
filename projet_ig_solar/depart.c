
#include "depart.h"

#define DIRSHADER "/home/amghar/Projet_ig/shaders"
#define N_TEX 5
#define FIX 0

GLuint vshader = 0;
GLuint fshader = 0;
GLuint texid = 0;
GLuint texid1 = 0;
GLuint tex_tab[N_TEX];
GLuint planet_pgm = 0;
GLuint solar_pgm = 0;
int tm = 0;
int id_tmp;
int id_tms;
int id_tex_tab[N_TEX];
int light_id;

float rotat =0.0;
float x=5;
float z=-10;
// Parametre terre
#define EXT_TER 0.016718
#define A 15
#define B 7


/* Paramètres caméra de navigation */
float lup_down ;
float lleft_right ;
float lcam_pos_x ;
float lcam_pos_z ;
float lcam_pos_y ;
float lcam_look_x;
float lcam_look_z ;
float lcam_look_y ;



/* Position et composante ambiante de la source de lumière */
GLfloat light_position[] = {0.0f, 5.0f, 0.0f, 1.0f };
GLfloat lightambiant[] = { 0.1f, 0.1f, 0.1f, 0.1f};
GLfloat lightdiffuse[] = { 1.0f, 1.0f,1.0f, 1.0f};

GLfloat light_p[] = {0.0f, 5.0f, -5.0f, 1.0f };
GLfloat light_d[] = { 1.0f, 1.0f, 1.0f, 1.0f};

/* Definition matériaux */
GLfloat mat_specularWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_ambientWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_diffuseWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_shininessWHITE[] ={128.0 * 0.4};

GLfloat mat_specularWHITE_2[] ={1.0,1.0,1.0,1.0};
GLfloat mat_ambientWHITE_2[] ={1.0,1.0,1.0,1.0};
GLfloat mat_diffuseWHITE_2[] ={1.0,1.0,1.0,1.0};
GLfloat mat_shininessWHITE_2[] ={128.0 * 0.4};

GLfloat mat_specularBLUE[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientBLUE[] ={0,0,1,1.0};
GLfloat mat_diffuseBLUE[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessBLUE[] ={128.0 };

GLfloat mat_specularLIGHT_BLUE[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientLIGHT_BLUE[] ={0,0.0,0.9,1.0};
GLfloat mat_diffuseLIGHT_BLUE[] ={0.90,0.90,0.90,1.0};
GLfloat mat_shininessLIGHT_BLUE[] ={128.0};

GLfloat mat_specularYELLOW[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientYELLOW[] ={1,1,0,1.0};
GLfloat mat_diffuseYELLOW[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessYELLOW[] ={128.0};


/* code ASCII pour la touche escape*/
#define ESCAPE 27

/* Idantifiant de la fenêtre GLUT */
int window; 

/*header*/
void load_textures(void);
void terre(void);
void espace(void);
void soleil(void);
void set_material(GLfloat amb[], GLfloat diff[], GLfloat spec[], GLfloat shin[]);

/* Fonction d'initialisation */
void InitGL(int Width, int Height)	        
{
	// Couleur d'effacement du buffer de couleur
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		

	// paramètrage du Z-buffer
	glClearDepth(1.0f);	
	glDepthFunc(GL_LESS);	
	glEnable(GL_DEPTH_TEST);	

	// Activation de l'éclairage **
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 	
	
	glEnable(GL_LIGHT1); 
	
	// Activation du lissage
	glShadeModel(GL_SMOOTH);			

	// Projection perceptive
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				
	gluPerspective(45.0f, (GLfloat)Width/(GLfloat)Height, 0.1f, 100.0f);	

	// Normalisation des normales
	glEnable(GL_NORMALIZE);

	load_textures();


	glMatrixMode(GL_MODELVIEW);
}

/* Fonction de redimensionnement de la fenêtre */
void ReSizeGLScene(int Width, int Height)
{
	if(Height==0)				
	{
		Height=1;
	}

	glViewport(0, 0, Width, Height);		

	// Projection perceptive
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				
	gluPerspective(45.0f, (GLfloat)Width/(GLfloat)Height, 0.1f, 100.0f);	

	glMatrixMode(GL_MODELVIEW);
}

/* Focntion de dessin */
void DrawGLScene()
{
	// Effacement du buffer de couleur et de profondeur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

	glLoadIdentity();
	get_cam_coord(&lcam_pos_x,&lcam_pos_y,&lcam_pos_z,&lcam_look_x,&lcam_look_y,&lcam_look_z);
	gluLookAt(lcam_pos_x,lcam_pos_y,lcam_pos_z,lcam_look_x,lcam_look_y,lcam_look_z,0.0,1.0,0.0);
	
	// lumieres
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightambiant);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_p);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_d);
	
	rotat += 0.0001;
	if(rotat > 360.0) rotat = 0.0;
	x = A * cos(rotat);
	z = B * sin(rotat);
	// acriver les textures
	glEnable (GL_TEXTURE_2D);
	// le shader pour les planetes
	glUseProgram(planet_pgm);

	//glUniform4f(light_id,-20.0f, 10.0f, 20.0f, 1.0f);
	espace();	
	
	terre();
	
	glUseProgram(0);

	// le shader pour le soleil
	glDisable(GL_LIGHTING);
	soleil();	
	glEnable (GL_LIGHTING);

	glDisable (GL_TEXTURE_2D);

	tm++;
	// Permutation des buffers
	glutPostRedisplay();
	glutSwapBuffers();
}

/* Fonction de gestion du clavier */
void special(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_RIGHT:
			move_camera_lr(0.08);
			break;
		case GLUT_KEY_LEFT:
			move_camera_lr(-0.08);
			break;
		case GLUT_KEY_UP:
			move_camera_fb(0.02);
			break;
		case GLUT_KEY_DOWN:
			move_camera_fb(-0.02);
			break;
		default:
			break;
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		
		case 'q':
			lleft_right = get_cam_rot_lr();
			lleft_right -= 0.03;
			rotate_camera_xz(lleft_right);
			break;
		case 'z':
			lup_down = get_cam_rot_ud();
			lup_down+= 0.03;
			rotate_camera_yz(lup_down);
			break;
		case 's':
			lup_down = get_cam_rot_ud();
			lup_down-= 0.03;
			rotate_camera_yz(lup_down);
			break;
		
		case 'd':
			lleft_right = get_cam_rot_lr();
			lleft_right += 0.03;
			rotate_camera_xz(lleft_right);
			break;
		case ESCAPE :
			{
				glutDestroyWindow(window);
				exit(EXIT_SUCCESS);
			}
		default:
			break;
	}	
	glutPostRedisplay();
	glutSwapBuffers();
}


int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	  
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

	glutInitWindowSize(640, 480);  

	glutInitWindowPosition(0, 0);  

	window = glutCreateWindow("Solar System");  

	glutDisplayFunc(&DrawGLScene);  

	glutReshapeFunc(&ReSizeGLScene);

	glutSpecialFunc(&special);

	glutKeyboardFunc(&keyboard);

	InitGL(640, 480);
	
	Enable_shader();	 
	GLuint tabsh[1] ; 
	tabsh[0] = LoadShader(GL_VERTEX_SHADER, "/home/amghar/Projet_ig/shaders/phong.vs");
	tabsh[1] = LoadShader(GL_FRAGMENT_SHADER, "/home/amghar/Projet_ig/shaders/phong.fs");		 
		
	planet_pgm = create_program(tabsh,2);
	id_tex_tab[0] = glGetUniformLocation(planet_pgm, "image0");
	id_tex_tab[1] = glGetUniformLocation(planet_pgm, "image1");
	id_tmp = glGetUniformLocation(planet_pgm, "time");

	tabsh[0] = LoadShader(GL_VERTEX_SHADER, "/home/amghar/Projet_ig/shaders/solar.vs");
	tabsh[1] = LoadShader(GL_FRAGMENT_SHADER, "/home/amghar/Projet_ig/shaders/solar.fs");
	solar_pgm = create_program(tabsh,2);
	id_tex_tab[2] = glGetUniformLocation(solar_pgm, "image0");
	id_tex_tab[3] = glGetUniformLocation(solar_pgm, "image1");
	id_tms = glGetUniformLocation(solar_pgm, "time");	
	
	
	light_id = glGetUniformLocation(planet_pgm, "light");
	/* Lancement de la boucle OpenGL */  
	glutMainLoop();  

	return 1;
}

float get_ro(float ext, float angle,float patit_demi_axe)
{
return (patit_demi_axe/sqrt(1.0-pow(ext,2)-pow(cos(angle),2)));
}

void load_textures(void)
{
// Textures 
	/* Load PNG texture from file*/
  	tex_tab[0] = loadPNGTexture ("/home/amghar/Projet_ig/textures/earth_day.png");
  	if (!tex_tab[0])
   		exit (EXIT_FAILURE);
	tex_tab[1] = loadPNGTexture ("/home/amghar/Projet_ig/textures/earth_clouds.png");
  	if (!tex_tab[1])
   		exit (EXIT_FAILURE);
	tex_tab[2] = loadPNGTexture ("/home/amghar/Projet_ig/textures/sun_3.png");
  	if (!tex_tab[2])
   		exit (EXIT_FAILURE);
	tex_tab[3] = loadPNGTexture ("/home/amghar/Projet_ig/textures/sun_6.png");
  	if (!tex_tab[3])
   		exit (EXIT_FAILURE);
	tex_tab[4] = loadPNGTexture ("/home/amghar/Projet_ig/textures/space.png");
  	if (!tex_tab[4])
   		exit (EXIT_FAILURE);


}

void terre(void)
{
	//set_material(mat_ambientWHITE, mat_diffuseWHITE, mat_specularWHITE, mat_shininessWHITE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, tex_tab[0]);
	glUniform1i(id_tex_tab[0],0);
	
	glActiveTexture(GL_TEXTURE1);
 	glBindTexture (GL_TEXTURE_2D,tex_tab[1]);
	glUniform1i(id_tex_tab[1],1);
	 
	glUniform1i(id_tmp,tm);

	glPushMatrix();
	glTranslatef (x, 5.0, z);
	glRotatef(-90.0,1.0,0.0,0.0);
	GLUquadric* sphere = gluNewQuadric();
	gluQuadricTexture(sphere,GL_TRUE);	
	gluSphere( sphere ,2, 40, 40);
	glPopMatrix();
	gluDeleteQuadric(sphere);

}

void espace(void)
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture (GL_TEXTURE_2D, tex_tab[4]);
	glUniform1i(id_tex_tab[0],2);
	
	glUniform1i(id_tex_tab[1],2);
	 
	glUniform1i(id_tmp,FIX);
	///////////////////////////////////////////////////////
	//// background
	glPushMatrix();
	glTranslatef(lcam_pos_x,lcam_pos_y,lcam_pos_z);
	glRotatef(-90.0,1.0,0.0,0.0);
	glRotatef(180.0,1.0,0.0,0.0);
	set_material(mat_ambientWHITE, mat_diffuseWHITE, mat_specularWHITE, mat_shininessWHITE);	
	GLUquadric* params_globe = gluNewQuadric();
	gluQuadricOrientation(params_globe,GLU_INSIDE);
	gluQuadricTexture(params_globe,GL_TRUE);
	gluSphere(params_globe,100.0,50,50);
	gluDeleteQuadric(params_globe);
	glPopMatrix();
}
void soleil(void)
{
	glUseProgram(solar_pgm);
	//glUniform4fv(light_id,lightdiffuse);
	GLfloat solar[] = {255.0,255.0,255.0,255.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,solar);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,solar);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,2); 	
	///set_material(mat_ambientWHITE_2, mat_diffuseWHITE_2, mat_specularWHITE_2, mat_shininessWHITE_2);
	//glEnable(GL_BLEND);
	//glBlendFunc(0,1);
	glActiveTexture(GL_TEXTURE3);
 	glBindTexture (GL_TEXTURE_2D, tex_tab[2]);
	
	glUniform1i(id_tex_tab[2],3);
	
	glActiveTexture(GL_TEXTURE4);
 	glBindTexture (GL_TEXTURE_2D,tex_tab[3]);
	glUniform1i(id_tex_tab[3],4);
	 
	glUniform1i(id_tms,tm);
	
	glPushMatrix();
	glTranslatef (0.0, 5.0, 0.0);
	glRotatef(-90.0,1.0,0.0,0.0);
	GLUquadric* sphere2 = gluNewQuadric();
	gluQuadricTexture(sphere2,GL_TRUE);	
	gluSphere( sphere2 ,5,40 ,40);
	glPopMatrix();
	gluDeleteQuadric(sphere2);	
	glUseProgram(0);
	//glDisable(GL_BLEND);
}
void set_material(GLfloat amb[], GLfloat diff[], GLfloat spec[], GLfloat shin[])
{
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);                  
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shin);
                    
}

