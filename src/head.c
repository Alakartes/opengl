#include "../headers/head.h"



void draw_head(int dl_head) {
   glNewList(dl_head, GL_COMPILE);
      glScalef(1, 1, 1.3);
      glutSolidSphere(1.4 ,8 ,8);
   glEndList();
}
