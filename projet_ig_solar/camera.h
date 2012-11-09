#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <math.h>

/* Paramètres caméra de navigation */
float get_cam_rot_lr(void);
float get_cam_rot_ud(void);
void get_cam_coord(float* p_x,float* p_y,float* p_z,float* l_x,float* l_y,float* l_z);


void move_camera_lr(double speed);
void move_camera_fb(double speed);

void rotate_camera_xz(double speed);
void rotate_camera_yz(double speed);

#endif
