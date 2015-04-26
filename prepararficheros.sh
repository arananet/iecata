#!/bin/bash
#prepararficheros.sh (c)2015 por @edu_arana <info@arananet.net>

#Este script realiza dos funciones a partir de la ruta que se pase como 
#parametro.

#Primero: Renombra todos los ficheros del directorio pasandolos a mayusculas.
#esto debe hacerse debido a que la C64 no reconoce en las particiones, nombres,
#de fichero en minusculas.

#Segundo: Elimina cualquier espacio en blanco que tenga un fichero en 
#concreto y reemplazando dicho espacio por un _.

#Renombramos todos los ficheros a mayusculas:
find $1 -depth -print -execdir rename -f 'y/a-z/A-Z/' '{}' \;

#Reemplazamos los espacios por _
find $1 -depth -name "* *" -execdir rename 's/ /_/g' "{}" \;
