#include "camera.h"

/* Paramètres caméra de navigation */
float up_down = -1.57;
float left_right = -1.57;
float cam_pos_x = 0.0;
float cam_pos_z = 30.0;
float cam_pos_y = 10.0;
float cam_look_x = 0.0;
float cam_look_z = 0.0;
float cam_look_y = 5.0;
float vect_x = 0.0;
float vect_z = 0.0;
float vect_y = 0.0;

float get_cam_rot_lr(void)
{
return left_right;
}

float get_cam_rot_ud(void)
{
return up_down;
}

void get_cam_coord(float* p_x,float* p_y,float* p_z,float* l_x,float* l_y,float* l_z)
{
*p_x = cam_pos_x;
*p_y = cam_pos_y;
*p_z = cam_pos_z;
*l_x = cam_look_x;
*l_y = cam_look_y;
*l_z = cam_look_z;
}


void move_camera_lr(double speed)
{
	cam_pos_x += speed;	
	cam_look_x += speed;	
	
}

void move_camera_fb(double speed)
{
	vect_x = cam_look_x - cam_pos_x;
	vect_z = cam_look_z - cam_pos_z;
	
	cam_pos_x += vect_x * speed;
	cam_pos_z += vect_z * speed;

	cam_look_x += vect_x * speed;	
	cam_look_z += vect_z * speed;
}

void rotate_camera_xz(double speed)
{
	vect_x = cam_look_x - cam_pos_x;
	vect_z = cam_look_z - cam_pos_z;

	float cosTheta = (float)cos(speed);
	float sinTheta = (float)sin(speed);

	double new_x = sqrt(pow(vect_x,2) + pow(vect_z,2)) * cosTheta;
	double new_z = sqrt(pow(vect_x,2) + pow(vect_z,2)) * sinTheta;
	
	cam_look_x = cam_pos_x + new_x;
	cam_look_z = cam_pos_z + new_z;
	left_right = speed;
}

void rotate_camera_yz(double speed)
{
	vect_y = cam_look_y - cam_pos_y;
	vect_z = cam_look_z - cam_pos_z;

	float cosTheta = (float)cos(speed);
	float sinTheta = (float)sin(speed);

	double new_y = sqrt(pow(vect_y,2) + pow(vect_z,2)) * cosTheta;
	double new_z = sqrt(pow(vect_y,2) + pow(vect_z,2)) * sinTheta;
	
	cam_look_y = cam_pos_y + new_y;
	cam_look_z = cam_pos_z + new_z;
	up_down = speed;
}
