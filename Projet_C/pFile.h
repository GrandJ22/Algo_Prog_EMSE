#ifndef PFILE_H
#define PFILE_H

#include <stdio.h>
#include <stdlib.h>



typedef struct _Arc{
	int num;
	struct _Arc* Suivant;
}Arc;

typedef struct 
{
	Arc* tete;
	Arc* queue;
} File;

File Initialiser();
int est_vide(File* pF);
void enfiler(File *pF, int val);
int defiler(File *pF);
void detruire (File *pF);

#endif
