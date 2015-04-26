/* Herramienta para subir ficheros al disco duro IEC-ATA (c) 2015 @edu_arana
# Basado en el código de Asbjørn Djupdal 2002.
#
# Esta utilidad recibe dos parametros: 
# 
# unidad /ruta/NOMBREDELFICHEROORIGEN.PRG NOMBREDELFICHERODESTINO.PRG
# 
# Ejemplo: sudo ./subir /dev/sdb /c64/IMPOSSIBLEMISSION.PRG IMPOSSIBLEMISSION.ORG
#
# Luego con la utilidad "consulta" podremos comprobar si la subida aparacere 
# correctamente en el disco duro IEC-ATA (el disco que utilizará la C64 para
# acceder a los ficheros que hemos subido.
*/

#include "../../iecata.h"

#include "../../dos-file.c"
#include "../../dos-dir.c"
#include "../../dos-init.c"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* variables **************************************************************/

FILE *fp; /* the HD */
block_t totalDiskSize = 100000; 

/* functions **************************************************************/

int main (int argc, char *argv[]) {
system("tput clear");

  if (argc != 1) {
  
    /* open file to the entire hard drive */
    if ((fp = fopen (argv[1], "r+b"))) {

      /* init file system */
      if (!dosInit()) {
        fprintf (stderr, "Disco duro para la interfaz IEC-ATA no formateado!\n");
      }

      /* main loop, accept and execute commands */
      while (TRUE) {
	
      // Aquí llamamos a la funcion de subida (import) y le pasamos como parámetro, los argumentos de la
     // linea de comandos.
	    FILE *fp2;
            char *name1 = argv[2];
            char *name2 = argv[3];

            if (name1 && name2) {
              if ((fp2 = fopen (name1, "rb"))) {
                if (openWrite (name2, PRG, 2)) {
                  bufferSize_t size = BLOCKSIZE;
                
                  channelTable[2].fileState = WRITE_FILE;

                  while (size == BLOCKSIZE) {
                    size = fread (&channelTable[2].buffer, 1, BLOCKSIZE, fp2);
                    if (size != BLOCKSIZE) {
                      channelTable[2].bufferPtr = size;
					  printf("Fichero %s subido correctamente!\n",argv[3]);
                    } else if (!writeFile (2)) {
                      fprintf (stderr, "Error al escribir\n");
                      break;
                    }
                  }
                  closeFile (2);
                }
                fclose (fp2);
              } else fprintf (stderr, "no puedo abrir el fichero\n");
            }
           exit (0);
      }
    } else fprintf (stderr, "No puedo abrir %s\n", argv[1]);
  } else fprintf (stderr, "Herramienta para subir ficheros al disco duro IEC por @edu_arana\n----------------------------------------------------------------\n\nParámetros: Unidad /ruta/FICHEROORIGEN.PRG FICHERODESTINO.PRG\n\nEjemplo: sudo ./subir /dev/sdb /c64/IMPOSSIBLEMISSION.PRG IMPOSSIBLEMISSION.ORG\n\n");
  exit (0);
}

void ataGetBlock (block_t blockNumber, uint8_t data[]) {
  if ((fseek (fp, blockNumber * BLOCKSIZE, SEEK_SET)) != -1) {
    if (fread (data, 1, BLOCKSIZE, fp) != BLOCKSIZE) {
      fprintf (stderr, "Error while reading block\n");
    }
  } else fprintf (stderr, "Can't seek to block\n");
}

void ataPutBlock (block_t blockNumber, uint8_t data[]) {
  if ((fseek (fp, blockNumber * BLOCKSIZE, SEEK_SET)) != -1) {
    if (fwrite (data, 1, BLOCKSIZE, fp) != BLOCKSIZE) {
      fprintf (stderr, "Error while writing block\n");
    }
  } else fprintf (stderr, "Can't seek to block\n");
}

