#include "../headers/frame.h"



void draw_frame(int dl_frame) {
   int j;
   glNewList(dl_frame, GL_COMPILE);

   glColor3f(0.1, 0.5, 0.1);
   for(j = -100; j <= 100; j+=15) {
      glBegin(GL_LINES);
         glVertex3f(j, -10, -100);
         glVertex3f(j, -10, 100);
      glEnd();
   }
   for(j = -100; j <= 100; j+=15) {
      glBegin(GL_LINES);
         glVertex3f(-100, -10, j);
         glVertex3f(100, -10, j);
      glEnd();
   }


      /* X axis */
      glBegin(GL_LINES);
         glColor3f(1, 0, 0);
         glVertex3f(-5, 0, 0);
         glVertex3f(5, 0, 0);
      glEnd();

      /* Y axis */
      glBegin(GL_LINES);
         glColor3f(0, 1, 0);
         glVertex3f(0, -5, 0);
         glVertex3f(0, 5, 0);
      glEnd();

      /* Z axis */
      glBegin(GL_LINES);
         glColor3f(0, 0, 1);
         glVertex3f(0, 0, -5);
         glVertex3f(0, 0, 5);
      glEnd();

      glPointSize(10.0);

      glBegin(GL_POINTS);
         glColor3f(1, 0, 0);
         glVertex3f(5, 0, 0);
      glEnd();

      glBegin(GL_POINTS);
         glColor3f(0, 1, 0);
         glVertex3f(0, 5, 0);
      glEnd();

      glBegin(GL_POINTS);
         glColor3f(0, 0, 1);
         glVertex3f(0, 0, 5);
      glEnd();

   glEndList();
}
