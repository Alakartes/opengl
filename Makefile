NCPATH = -I /usr/local/include -I /usr/X11R6/include -I ./src
Libpath = -l /usr/local/lib -l /usr/x11r6/lib
library = -L/System/Library/Frameworks -framework GLUT -framework OpenGL -Wno-deprecated-declarations

CFLAGS = $(INCPATH)
LDFALGS = $(LIBPATH) $(LIBRARY)
GCC=gcc
SRC=src

all:
		@echo "Specifiez une cible"

%:$(SRC)/%.c
		$(GCC) $(library) -o $@ $< 

clean:
		@rm -f `/bin/ls *.o | grep -v Makefile | grep -v $(SRC)`
