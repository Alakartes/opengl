#ifndef _ARM_H
#define _ARM_H

#if defined(__APPLE__)
	#include <GLUT/glut.h>
	#define APIENTRY
#elif
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GLAPIENTRY APIENTRY
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define true  1
#define false 0

#define KEY_ESC 27

#define PI 3.1415926535898

void draw_forearm(int dl_forearm);
void draw_arm(int dl_arm);

#endif
