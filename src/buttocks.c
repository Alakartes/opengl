#include "../headers/buttocks.h"



void draw_buttocks(int dl_buttocks) {
   int i;

   glPushMatrix();

   glNewList(dl_buttocks, GL_COMPILE);
   glLineWidth(3);
   glScalef(2.3, 1.5, 1.7);

   glColor3f(0.1, 0.4, 0);

   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);
         glVertex3f(0, 0, 0);
         glVertex3f(0, 0.5, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0, 0.5, 0);
         glVertex3f(0.2, 0.7, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.2, 0.7, 0);
         glVertex3f(0.5, 0.8, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.5, 0.8, 0);
         glVertex3f(0.8, 0.7, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.8, 0.7, 0);
         glVertex3f(1, 0.5, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1, 0.5, 0);
         glVertex3f(1.1, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glEndList();

   glPopMatrix();
}
