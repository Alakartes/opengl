#include "../headers/chest.h"



void draw_chest(int dl_chest) {
   int i;

   glPushMatrix();

   glNewList(dl_chest, GL_COMPILE);
   glLineWidth(3);
   glScalef(1, 0.7, 1);


   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(0, 0.2, 0);
         glVertex3f(0.4, 1.2, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(0.4, 1.2, 0);
         glVertex3f(0.7, 2.2, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(0.7, 2.2, 0);
         glVertex3f(1, 2, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(1, 2, 0);
         glVertex3f(3, 2.1, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(3, 2.1, 0);
         glVertex3f(4, 2.4, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(4, 2.4, 0);
         glVertex3f(5, 2.8, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(5, 2.8, 0);
         glVertex3f(6, 3.2, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(6, 3.2, 0);
         glVertex3f(7, 2.7, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0, (float)127/255);
         glVertex3f(7, 2.7, 0);
         glVertex3f(7.4, 1.3, 0);
      glEnd();

      glBegin(GL_LINES);
         glColor3f(1, 0.8, 0.6);
         glVertex3f(7.4, 1.25, 0);
         glVertex3f(7.5, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glEndList();

   glPopMatrix();
}
