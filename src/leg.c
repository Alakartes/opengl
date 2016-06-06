#include "../headers/leg.h"



void draw_thigh(int dl_thigh) {
   int i;

   glNewList(dl_thigh, GL_COMPILE);
   glLineWidth(3);

   glColor3f(1, 0, 0);
   glScalef(1.6, 1.2, 1.4);
   glRotatef(90, 0, 1, 0);

   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);
         glVertex3f(0, 0, 0);
         glVertex3f(0.2, 0.45, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.2, 0.45, 0);
         glVertex3f(0.5, 0.50, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.5, 0.50, 0);
         glVertex3f(1, 0.55, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1, 0.55, 0);
         glVertex3f(2, 0.7, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2, 0.7, 0);
         glVertex3f(3, 0.60, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(3, 0.60, 0);
         glVertex3f(3.5, 0.50, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(3.5, 0.50, 0);
         glVertex3f(3.6, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glPushMatrix();

   glTranslatef(3, 0, 0);
   glColor3f(0.1, 0.5, 0.1);
   glScalef(0.3, 1, 1);

   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);
         glVertex3f(0, 0, 0);
         glVertex3f(0.2, 0.20, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.2, 0.20, 0);
         glVertex3f(0.5, 0.40, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.5, 0.40, 0);
         glVertex3f(1, 0.45, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1, 0.45, 0);
         glVertex3f(2, 0.55, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2, 0.55, 0);
         glVertex3f(3, 0.60, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(3, 0.60, 0);
         glVertex3f(3.5, 0.50, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(3.5, 0.50, 0);
         glVertex3f(3.6, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glPopMatrix();

   glEndList();
}

void draw_calf(int dl_calf) {
   int i;

   glNewList(dl_calf, GL_COMPILE);
   glLineWidth(3);

   glColor3f(0, 1, 1);

   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);
         glVertex3f(0, 0, 0);
         glVertex3f(0.2, 0.35, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.2, 0.35, 0);
         glVertex3f(0.5, 0.4, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.5, 0.4, 0);
         glVertex3f(1, 0.45, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1, 0.45, 0);
         glVertex3f(2, 0.5, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2, 0.5, 0);
         glVertex3f(3, 0.40, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(3, 0.40, 0);
         glVertex3f(3.2, 0.35, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(3.2, 0.35, 0);
         glVertex3f(3.25, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glEndList();
}
