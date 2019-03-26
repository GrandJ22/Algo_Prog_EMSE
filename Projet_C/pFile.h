#ifndef PFILE_H
#define PFILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _cell 
{
	int val;
	int poid;
	struct	_cell* suivant;
} cell;

typedef struct 
{
	cell* tete;
	cell* queue; 
} File;

File Initialiser();
int est_vide(File* pF);
void enfiler(File *pF, int val);
int defiler(File *pF);
void detruire (File *pF);

#endif
