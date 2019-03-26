#include "pFile.h"

File Initialiser() 
{
	File filevide;
	filevide.tete = NULL;
	filevide.queue = NULL;
	return filevide;
}

int est_vide(File* pF) 
{
	return (pF->tete == NULL);
}

void enfiler(File *pF, int val) 
{
	cell* pelem = (cell*) malloc(sizeof(cell)); 
	pelem->val = val;
	pelem->suivant = NULL; 
	 
	if (pF->tete == NULL) // enfiler dans une file nulle
		pF->tete = pF->queue = pelem; 
	else 
	{ 
		pF->queue->suivant = pelem; 
		pF->queue = pelem;
	}	
}

int defiler(File *pF) 
{	
	int val = pF->tete->val;

	cell* ptemp = pF->tete;
	pF->tete = pF->tete->suivant;
	if (pF->tete == NULL) // file nulle apres avoir defile
		pF->queue = NULL;
	free(ptemp);
	return val;
}

void detruire (File *pF)
{
	while (!est_vide(pF))
		defiler(pF);
}