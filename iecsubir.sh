#!/bin/bash
#Script para la subida automativa de ficheros al disco duro a utilizar 
#en la controladora IECATA.
#
#(c) 2015 @edu_arana - <info@arananet.net>
#
UNIDADDESTINO="$1"
DIR="$2"

# failsafe - fall back to current directory
[ "$DIR" == "" ] && DIR="."
 
# save and change IFS 
OLDIFS=$IFS
IFS=$'\n'
 
# read all file name into an array
fileArray=($(find $DIR -type f))
fileArray1=($(find $DIR  -type f -printf "%f\n"))
 
# restore it 
IFS=$OLDIFS
 
# get length of an array
tLen=${#fileArray[@]}
 
# use for loop read all filenames
for (( i=0; i<${tLen}; i++ ));
do
   sudo ./subir $1 ${fileArray[$i]} ${fileArray1[$i]}
done

