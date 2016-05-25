/*****************************************************************************
File: TD3-avatar-skel.c

Informatique Graphique IG1
IFIPS
Christian Jacquemin, Universit� Paris 11

Copyright (C) 2007 University Paris 11
This file is provided without support, instruction, or implied
warranty of any kind.  University Paris 11 makes no guarantee of its
fitness for a particular purpose and is not liable under any
circumstances for any damages or loss whatsoever arising from the use
or inability to use this file or items derived from it.
******************************************************************************/
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
/*#include "tiffio.h"    // Sam Leffler's libtiff library.
int writetiff(char *filename, char *description,
	      int x, int y, int width, int height, int compression);*/

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

#define position_Ini                   -60.0

float t = 0.f;
float delta = 10.f;
float k = 0.001f;
float K = 0.002f;
int IdleRunning = true;
int TraceEcran = false;
int RangFichierStockage = 0;
float position = position_Ini;

int  Ma_Tete;
int  Mon_Tronc;
int  Mon_Bras;
int  Mon_AvantBras;
int  Ma_Cuisse;
int  Mon_Mollet;
int  Mon_Repere;

float cam_x = 0;
float cam_y = 0;
float cam_z = 1;

float po_x = 0;
float po_y = 0;
float po_z = 0;

enum lateralite{ Gauche = 0, Droit };

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
void init_angles();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);
GLvoid window_timer();
void Faire_Composantes();
void Dessine_Repere();

int main(int argc, char **argv)
{
    // initialisation  des param�tres de GLUT en fonction
    // des arguments sur la ligne de commande
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    // d�finition et cr�ation de la fen�tre graphique
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Avatar animé");

    // initialisation de OpenGL et de la sc�ne
    initGL();
    init_scene();













    // choix des proc�dures de callback pour
    // le trac� graphique
    glutDisplayFunc(&window_display);
    // le redimensionnement de la fen�tre
    glutReshapeFunc(&window_reshape);
    // la gestion des �v�nements clavier
    glutKeyboardFunc(&window_key);
    // fonction appel�e r�guli�rement entre deux gestions d��v�nements
    glutTimerFunc(latence,&window_timer,Step);

    // la boucle prinicipale de gestion des �v�nements utilisateur
    glutMainLoop();

    return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque

GLvoid initGL()
{
    // initialisation de l��clairement

    // d�finition de deux source lumineuses
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light0);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    // activation de l��clairement
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // propri�t�s mat�rielles des objets
    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambientanddiffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_COLOR_MATERIAL);

    // initialisation du fond
    glClearColor(RED, GREEN, BLUE, ALPHA);
    // z-buffer
    glEnable(GL_DEPTH_TEST);
}

void init_scene()
{
    // initialise des display lists des composantes cylindriques du corps
    Faire_Composantes();

    amplitude_Bras
    = .5 * (angle_Bras_Ini[ Droit ] - angle_Bras_Ini[ Gauche ]);
    amplitude_AvantBras
    = .5 * (angle_AvantBras_Ini[ Droit ] - angle_AvantBras_Ini[ Gauche ]);
    amplitude_Cuisse
    = .5 * (angle_Cuisse_Ini[ Droit ] - angle_Cuisse_Ini[ Gauche ]);
    amplitude_Mollet
    = .5 * (angle_Mollet_Ini[ Droit ] - angle_Mollet_Ini[ Gauche ]);
    med_Bras
    = .5 * (angle_Bras_Ini[ Droit ] + angle_Bras_Ini[ Gauche ]);
    med_AvantBras
    = .5 * (angle_AvantBras_Ini[ Droit ] + angle_AvantBras_Ini[ Gauche ]);
    med_Cuisse
    = .5 * (angle_Cuisse_Ini[ Droit ] + angle_Cuisse_Ini[ Gauche ]);
    med_Mollet
    = .5 * (angle_Mollet_Ini[ Droit ] + angle_Mollet_Ini[ Gauche ]);
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(cam_x, cam_y, cam_z, po_x, po_y, po_z, 0, 1, 0);

    Dessine_Repere();
    render_scene();


    // trace la sc�ne grapnique qui vient juste d'�tre d�finie
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -1000, 1000);
    // glFrustum(-20, 20, -20, 20, 10, 1000);
    // glScalef(10, 10, 10);

    // toutes les transformations suivantes s�appliquent au mod�le de vue
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
    delta+=30;
    break;
    case 'z':
    delta-=30;
    break;
    case 'i':
      cam_x = 0;
      cam_y = 2;
      cam_z = 0;
    break;
    case 'k':
      cam_x = 1;
      cam_y = -1;
      cam_z = -1;
    break;
    case 'j':
      cam_x+=0.2;
      po_y+=0.2;
    break;
    case 'l':
      cam_x-=0.2;
      po_y-=0.2;
    break;
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
    angle_Bras[Droit] = sin(K*delta)*22.5-15;
    angle_AvantBras[Droit] = sin(K*delta)*15+15;
    angle_Bras[Gauche] = -sin(K*delta)*22.5-15;
    angle_AvantBras[Gauche] = -sin(K*delta)*15+15;

    angle_Cuisse[Droit] = sin(K*delta)*20;
    angle_Mollet[Droit] = sin(K*delta)*10-10;
    angle_Cuisse[Gauche] = -sin(K*delta)*20;
    angle_Mollet[Gauche] = -sin(K*delta)*10-10;

    // On d�place la position de l'avatar pour qu'il avance
    // ********* A FAIRE **************

    glutTimerFunc(latence,&window_timer,++Step);

    glutPostRedisplay();
}

// un cylindre
void Faire_Composantes() {
    GLUquadricObj* GLAPIENTRY qobj;

    // attribution des indentificateurs de display lists
    Ma_Tete =  glGenLists(6);
    Mon_Tronc = Ma_Tete + 1;
    Mon_Bras = Ma_Tete + 2;
    Mon_AvantBras = Ma_Tete + 3;
    Ma_Cuisse = Ma_Tete + 4;
    Mon_Mollet = Ma_Tete + 5;

    // compilation de la display list de la sph�re
    glNewList(Ma_Tete, GL_COMPILE);
    glutSolidSphere(1.5,8,8);
    glEndList();

    // allocation d�une description de quadrique
    qobj = gluNewQuadric();
    // la quadrique est pleine
    gluQuadricDrawStyle(qobj, GLU_FILL);
    // les ombrages, s�il y en a, sont doux
    gluQuadricNormals(qobj, GLU_SMOOTH);

    // compilation des display lists des cylindres
    glNewList(Mon_Tronc, GL_COMPILE);
    gluCylinder(qobj,2.5,2.5,7.0,100,100);
    glEndList();

    glNewList(Mon_Bras, GL_COMPILE);
    gluCylinder(qobj,0.5,0.5,5.0,100,100);
    glEndList();

    glNewList(Mon_AvantBras, GL_COMPILE);
    gluCylinder(qobj,0.5,0.25,5.0,100,100);
    glEndList();

    glNewList(Ma_Cuisse, GL_COMPILE);
    gluCylinder(qobj,1.25,0.75,5.0,100,100);
    glEndList();

    glNewList(Mon_Mollet, GL_COMPILE);
    gluCylinder(qobj,0.75,0.25,5.0,100,100);
    glEndList();

}

void  Dessine_Repere() {
    glNewList(Mon_Repere, GL_COMPILE);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-20 , 0 , 0);
    glVertex3f(20 , 0 , 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.4, 0.5);
      glVertex3f(20, -9, 20);
      glVertex3f(20, -9, -20);
      glVertex3f(-20, -9, -20);
      glVertex3f(-20, -9, 20);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0 , -20 , 0);
    glVertex3f(0 , 20 , 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0 , 0 , -20);
    glVertex3f(0 , 0 , 20);
    glEnd();

    glPointSize( 10.0 );
    glBegin(GL_POINTS);
    glColor3f(1.0, 0, 0);
    glVertex3f(20.0 , 0 , 0);
    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0, 1.0, 0);
    glVertex3f(0 , 20.0 , 0);
    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0, 0, 1.0);
    glVertex3f(0 , 0 , 20.0);
    glEnd();
    glEndList();
}

void render_scene()
{
    // rotation de 90 degres autour de Ox pour mettre l'axe Oz
    // vertical comme sur la figure
    glRotatef(-90, 1, 0, 0);

    // rotation de 160 degres autour de l'axe Oz pour faire
    // avancer l'avatar vers le spectateur
    glRotatef(-160, 0, 0, 1);

    // rotation de 25 degres autour de la bissectrice de $Oy$ pour
    // voir la figure en perspective
     glRotatef(25, 0, 0, 1);

    // d�placement horizontal selon l�axe Oy pour donner
    // une impression de d�placement horizontal accompagnant
    // la marche
    //glTranslatef( 0, position, 0);

    // trac� du tronc, aucune transformation n�est
    // requise
    glColor3f(1.0, 0, 0);
    glCallList(Mon_Tronc);

    // trac� de la t�te avec une translation positive
    // selon Oz pour la placer au-dessus du tronc
    // les appels � glPushMatrix et glPopMatrix servent
    // � sauvegarder et restaurer le contexte graphique
    glColor3f(1, 0.8, 0.6);
    glPushMatrix();
        glTranslatef(0,0,8.5);
        glCallList(Ma_Tete);
    glPopMatrix();

    // trac� de la cuisse droite avec une translation vers
    // la droite et une rotation de 180� autour de Ox
    // pour l�orienter vers le bas
    glColor3f(0, 0, 1.0);
    glPushMatrix();
        glTranslatef(1.25,0,0);
        glRotatef(180,1.0,0,0);
        glRotatef(angle_Cuisse[Droit],1.0,0,0);
        glCallList(Ma_Cuisse);

    // pour tracer le mollet, on reste dans le m�me
    // contexte graphique et on translate de
    // +5 selon Oz afin de mettre le rep�re au niveau
    // du genou
        glPushMatrix();
            glTranslatef(0,0,5.0);
            glRotatef(angle_Mollet[Droit],1.0,0,0);
            glCallList(Mon_Mollet);
        glPopMatrix();
    glPopMatrix();

    // cuisse et mollet gauches
    // seule la translation initiale change
    glPushMatrix();
        glTranslatef(-1.25,0,0);
        glRotatef(180,1.0,0,0);
        glRotatef(angle_Cuisse[Gauche],1.0,0,0);
        glCallList(Ma_Cuisse);
        glPushMatrix();
            glTranslatef(0,0,5.0);
            glRotatef(angle_Mollet[Gauche],1.0,0,0);
            glCallList(Mon_Mollet);
        glPopMatrix();
    glPopMatrix();

    // trac� du bras droit avec une translation vers
    // la droite et vers le haut compos�e avec une
    // rotation de 180� autour de Ox pour l�orienter
    // vers le bas
    glPushMatrix();
        glTranslatef(3.0,0,7);
        glRotatef(180,1.0,0,0);
        glRotatef(angle_Bras[Droit],1.0,0,0);
        glColor3f(1.0, 0, 0);
        glCallList(Mon_Bras);

    // pour tracer l�avant-bras, on reste dans le m�me
    // contexte graphique et on translate de
    // +5 selon Oz afin de mettre le rep�re au niveau
    // du coude
        glPushMatrix();
            glTranslatef(0,0,5);
            glColor3f(1, 0.8, 0.6);
            glRotatef(angle_AvantBras[Droit],1.0,0,0);
            glCallList(Mon_AvantBras);
        glPopMatrix();
    glPopMatrix();

    // bras et avant-bras gauches
    // seule la translation initiale change

    glPushMatrix();
        glTranslatef(-3.0,0,7);
        glRotatef(180,1.0,0,0);
        glRotatef(angle_Bras[Gauche],1.0,0,0);
        glColor3f(1.0, 0, 0);
        glCallList(Mon_Bras);
        glPushMatrix();
            glTranslatef(0,0,5.0);
            glColor3f(1, 0.8, 0.6);
            glRotatef(angle_AvantBras[Gauche],1.0,0,0);
            glCallList(Mon_AvantBras);
        glPopMatrix();
    glPopMatrix();

    // permutation des buffers lorsque le trac� est achev�
    glutSwapBuffers();
}
