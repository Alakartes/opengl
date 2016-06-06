#include "../headers/hat.h"



void draw_hat(int dl_hat) {
   int i;

   glPushMatrix();

   glNewList(dl_hat, GL_COMPILE);
   glLineWidth(3);
   glScalef(0.6, 0.6, 0.6);

   glColor3f((float)203/255, (float)174/255, (float)93/255);

   for(i = 0; i < 360; i++) {
      glBegin(GL_LINES);

         glVertex3f(0, 0, 0);
         glVertex3f(0.3, 6, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(0.3, 3, 0);
         glVertex3f(1, 2.7, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(1, 2.7, 0);
         glVertex3f(2, 2, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2, 2, 0);
         glVertex3f(2.4, 0.4, 0);
      glEnd();

      glBegin(GL_LINES);
         glVertex3f(2.4, 0.4, 0);
         glVertex3f(2.5, 0, 0);
      glEnd();

      glRotatef(1, 1, 0, 0);
   }

   glEndList();

   glPopMatrix();
}
