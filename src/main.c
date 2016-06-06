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

#include "../headers/frame.h"
#include "../headers/head.h"
#include "../headers/arm.h"
#include "../headers/chest.h"
#include "../headers/foot.h"
#include "../headers/hand.h"
#include "../headers/leg.h"
#include "../headers/neck.h"
#include "../headers/shoulder.h"
#include "../headers/pectoral.h"
#include "../headers/chair.h"
#include "../headers/hat.h"
#include "../headers/buttocks.h"


/*#include "tiffio.h"    // Sam Leffler's libtiff library.
int writetiff(char *filename, char *description, int x, int y, int width, int height, int compression);*/

#define    windowWidth 800
#define    windowHeight 800

#define GLAPIENTRY APIENTRY
#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define true  1
#define false 0

#define KEY_ESC 27

#define PI 3.1415926535898

#define position_Ini 0.0

float t = 0.f;
float delta = 10.f;
float k = 0.001f;
float K = 0.002f;
int IdleRunning = true;
int TraceEcran = false;
int RangFichierStockage = 0;
float position = position_Ini;

#define NB_LISTS 10

enum lists{		dl_init	 	= 0,
					dl_head 		= 1,
					dl_chest 	= 2,
					dl_neck 		= 3,
					dl_hand 		= 4,
					dl_arm 		= 5,
					dl_calf 		= 6,
					dl_thigh		= 7,
					dl_foot 		= 8,
					dl_forearm 	= 9,
					dl_frame		= 10,
					dl_pectoral	= 11,
					dl_chair		= 12,
					dl_shoulder	= 13,
					dl_hat		= 14,
					dl_buttocks	= 15
			};
int dl_lists[NB_LISTS];

float cam_x = -22;
float cam_y = 17;
float cam_z = 24;

float po_x = 0;
float po_y = 0;
float po_z = 0;

enum laterality{left = 0, right = 1};

float angle_Bras[2];
float angle_AvantBras[2];
float angle_Cuisse[2];
float angle_Mollet[2];

float angle_Bras_Ini[2] = {-30.0, 15.0};
float angle_AvantBras_Ini[2] = {0.0, 15.0};
float angle_Cuisse_Ini[2] = {20.0, -20.0};
float angle_Mollet_Ini[2] = {0.0, -20.0};

float amplitude_Bras;
float amplitude_AvantBras;
float amplitude_Cuisse;
float amplitude_Mollet;
float med_Bras;
float med_AvantBras;
float med_Cuisse;
float med_Mollet;

static GLfloat mat_specular[] = { 1.0 , 1.0 , 1.0 , 1.0 };
static GLfloat mat_ambientanddiffuse[] = { 0.4, 0.4 , 0.0 , 1.0 };
static GLfloat mat_shininess[] = { 20.0};

static GLfloat light_position0[] = { 15.0 , 15.0 , 15.0 , 0.0 };
static GLfloat light_position1[] = { 15.0 , 15.0 , -15.0 , 0.0 };

static GLfloat ambient_light0[] = { 0.0 , 0.0 , 0.0 , 0.0 };
static GLfloat diffuse_light0[] = { 0.7 , 0.7 , 0.7 , 1.0 };
static GLfloat specular_light0[] = { 0.1 , 0.1 , 0.1 , 0.1 };

static GLfloat ambient_light1[] = { 0.50 , 0.50 , 0.50 , 1.0 };
static GLfloat diffuse_light1[] = { 0.5 , 1.0 , 1.0 , 1.0 };
static GLfloat specular_light1[] = { 0.5 , 1.0 , 1.0 , 1.0 };

int Step = 0;
int latence =4;

void init_scene();
void render_scene();
void init_gl_ids();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_timer();


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("openGL ET3");

    initGL();
    init_scene();

    glutDisplayFunc(&window_display);
    glutReshapeFunc(&window_reshape);
    glutKeyboardFunc(&window_key);
    glutTimerFunc(latence, &window_timer, Step);

    glutMainLoop();

    return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque

GLvoid initGL()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // propri�t�s mat�rielles des objets
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambientanddiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.2, 0.22, 0.25, ALPHA);
    // z-buffer
    glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
	draw_frame(dl_frame);

	draw_head(dl_head);
	draw_hat(dl_hat);
	draw_chest(dl_chest);

	draw_arm(dl_arm);
	draw_forearm(dl_forearm);
	draw_shoulder(dl_shoulder);

	draw_calf(dl_calf);
	draw_thigh(dl_thigh);
	draw_buttocks(dl_buttocks);

	amplitude_Bras = .5 * (angle_Bras_Ini[ right ] - angle_Bras_Ini[ left ]);
	amplitude_AvantBras = .5 * (angle_AvantBras_Ini[ right ] - angle_AvantBras_Ini[ left ]);
	amplitude_Cuisse = .5 * (angle_Cuisse_Ini[ right ] - angle_Cuisse_Ini[ left ]);
	amplitude_Mollet = .5 * (angle_Mollet_Ini[ right ] - angle_Mollet_Ini[ left ]);
	med_Bras = .5 * (angle_Bras_Ini[ right ] + angle_Bras_Ini[ left ]);
	med_AvantBras = .5 * (angle_AvantBras_Ini[ right ] + angle_AvantBras_Ini[ left ]);
	med_Cuisse = .5 * (angle_Cuisse_Ini[ right ] + angle_Cuisse_Ini[ left ]);
	med_Mollet = .5 * (angle_Mollet_Ini[ right ] + angle_Mollet_Ini[ left ]);
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cam_x, cam_y, cam_z, po_x, po_y, po_z, 0, 1, 0);

    render_scene();

    glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluPerspective(45, 1.333, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
    switch (key) {
    case KEY_ESC:
    exit(1);
    break;
    case ' ':
    if (IdleRunning) {
      glutTimerFunc(latence,NULL,Step);
      IdleRunning = false;
    }
    else {
      glutTimerFunc(latence,&window_timer,Step);
      IdleRunning = true;
    }
    break;
    case 's':
	 	delta+=70;
		position = position - 0.5;
    break;
    case 'z':
    	delta-=70;
	 	position = position + 0.5;
    break;
    case 'i':
	 	cam_y+=1;
    break;
    case 'k':
	 	cam_y-=1;
    break;
    case 'j':
	 	cam_z+=1;
    break;
    case 'l':
	 	cam_z-=1;
    break;
	 case 'o':
	 	cam_x-=1;
	 break;
	 case 'u':
	 	cam_x+=1;
		break;
	 case 'g':
	 	printf("%f:%f:%f\n", cam_x, cam_y, cam_z);
    default:
	 	printf ("La touche %d n'est pas active.\n", key);
    break;
    }
}

// fonction de call-back appel�e r�guli�rement

GLvoid window_timer()
{
    // On effecture une variation des angles de chaque membre
    // de l'amplitude associ�e et de la position m�diane
    angle_Bras[right] = sin(K*delta)*32.5-15;
    angle_AvantBras[right] = sin(K*delta)*25+15;
    angle_Bras[left] = -sin(K*delta)*32.5-15;
    angle_AvantBras[left] = -sin(K*delta)*25+15;

    angle_Cuisse[right] = sin(K*delta)*30;
    angle_Mollet[right] = sin(K*delta)*20-10;
    angle_Cuisse[left] = -sin(K*delta)*30;
    angle_Mollet[left] = -sin(K*delta)*20-10;

	 /*angle_Bras[right] = sin(K*delta)*15-15;
    angle_AvantBras[right] = sin(K*delta)*10+15;
    angle_Bras[left] = -sin(K*delta)*15-15;
    angle_AvantBras[left] = -sin(K*delta)*10+15;

    angle_Cuisse[right] = sin(K*delta)*10;
    angle_Mollet[right] = sin(K*delta)*5-10;
    angle_Cuisse[left] = -sin(K*delta)*10;
    angle_Mollet[left] = -sin(K*delta)*5-10;*/

    glutTimerFunc(latence,&window_timer,++Step);

    glutPostRedisplay();
}

void init_gl_ids() {
	int i;
	dl_lists[dl_init] = glGenLists(NB_LISTS);
	for(i = 1; i < NB_LISTS; i++) {
		dl_lists[i] = dl_lists[dl_init] + i;
	}
}

void render_scene()
{
	glPushMatrix();
		glCallList(dl_frame);
	glPopMatrix();
   // rotation de 90 degres autour de Ox pour mettre l'axe Oz
   // vertical comme sur la figure
   glRotatef(-90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);

   // d�placement horizontal selon l�axe Oy pour donner
	// une impression de d�placement horizontal accompagnant
   // la marche
   glTranslatef(0, position, 0);

   // trac� du tronc, aucune transformation n�est
   // requise
	glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		glCallList(dl_chest);
	glPopMatrix();
    // trac� de la t�te avec une translation positive
    // selon Oz pour la placer au-dessus du tronc
    // les appels � glPushMatrix et glPopMatrix servent
    // � sauvegarder et restaurer le contexte graphique
    glColor3f(1, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(0,0,9);
        glCallList(dl_head);
    glPopMatrix();

	 glPushMatrix();
	 	glTranslatef(0, 0, 9.5);
		glRotatef(-90, 0, 1, 0);
		glCallList(dl_hat);
	 glPopMatrix();

    // trac� de la cuisse righte avec une translation vers
    // la righte et une rotation de 180� autour de Ox
    // pour l�orienter vers le bas


	 glPushMatrix();
        glTranslatef(0,0,0.3);
        glRotatef(180,1.0,0,0);
        glCallList(dl_buttocks);
	 glPopMatrix();

    glColor3f(0, 0, 1.0);
    glPushMatrix();
        glTranslatef(1.25,0,0);
        glRotatef(angle_Cuisse[right],1.0,0,0);
        glCallList(dl_thigh);

    // pour tracer le mollet, on reste dans le m�me
    // contexte graphique et on translate de
    // +5 selon Oz afin de mettre le rep�re au niveau
    // du genou
        glPushMatrix();
            glTranslatef(3.5,0,0);
            glRotatef(angle_Mollet[right],0,0,1);
            glCallList(dl_calf);
        glPopMatrix();
    glPopMatrix();

    // cuisse et mollet s
    // seule la translation initiale change

	 glPushMatrix();
        glTranslatef(0,0,0.3);
        glRotatef(180,1.0,0,0);
		  glRotatef(180,0,1,0);
        glCallList(dl_buttocks);
	 glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.25,0,0);
        glRotatef(angle_Cuisse[left],1.0,0,0);
        glCallList(dl_thigh);
        glPushMatrix();
            glTranslatef(3.5,0,0);
            glRotatef(angle_Mollet[left],0,0,1);
            glCallList(dl_calf);
        glPopMatrix();
    glPopMatrix();

    // trac� du bras right avec une translation vers
    // la righte et vers le haut compos�e avec une
    // rotation de 180� autour de Ox pour l�orienter
    // vers le bas

	 glPushMatrix();
        glTranslatef(3.8,0,6.5);
        glRotatef(180,1,0,0);
		  glRotatef(180, 0, 1, 0);
        glCallList(dl_shoulder);
	 glPopMatrix();

    glPushMatrix();
        glTranslatef(3.5,0,6.9);
        glRotatef(angle_Bras[right],1.0,0,0);
        glColor3f(1, 0, 0);
        glCallList(dl_arm);

    // pour tracer l�avant-bras, on reste dans le m�me
    // contexte graphique et on translate de
    // +5 selon Oz afin de mettre le rep�re au niveau
    // du coude
        glPushMatrix();
            glTranslatef(3.7, -0.1, 0);
            glColor3f(1, 0.8, 0.6);
            glRotatef(angle_AvantBras[right],0,0,1);
            glCallList(dl_forearm);
        glPopMatrix();
    glPopMatrix();

    // bras et avant-bras lefts
    // seule la translation initiale change

	 glPushMatrix();
        glTranslatef(-3.8,0,6.5);
        glRotatef(180,1.0,0,0);
        glCallList(dl_shoulder);
	 glPopMatrix();

    glPushMatrix();
        glTranslatef(-3.5,0,6.9);
        glRotatef(angle_Bras[left],1.0,0,0);
        glColor3f(1.0, 0, 0);
        glCallList(dl_arm);
        glPushMatrix();
            glTranslatef(3.7, -0.1, 0);
            glColor3f(1, 0.8, 0.6);
            glRotatef(angle_AvantBras[left],0,0,1);
            glCallList(dl_forearm);
        glPopMatrix();
    glPopMatrix();

    // permutation des buffers lorsque le trac� est achev�
    glutSwapBuffers();
}
