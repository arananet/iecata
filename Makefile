# Makefile para las herramientas del IEC-ATA
# (c) 2015 @edu_arana basado en el código de
# Asbj�rn Djupdal 2002.
#
# Makefile perteneciente a la utilidad subir
# que permite subir al disco duro IEC-ATA los 
# ficheros directamente pasando como parámetro
# el fichero origen y destino.

CC = gcc

CFLAGS = -Wall -O -DUNIX
LDFLAGS = -Wall

OBJECTS = subir.o

subir : $(OBJECTS) Makefile
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)

unix.o : subir.c ../../dos-init.c ../../dos-dir.c ../../dos-file.c ../../iecata.h Makefile
	$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean :
	rm -rf *.hex *.out *.o *.map subir
