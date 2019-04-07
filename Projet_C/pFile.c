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

void enfiler(File *pF, int num) 
{
	Arc* pelem = (Arc*) malloc(sizeof(Arc)); 
	pelem->num = num;
	pelem->Suivant = NULL; 
	 
	if (pF->tete == NULL) // enfiler dans une file nulle
		pF->tete = pF->queue = pelem; 
	else 
	{ 
		pF->queue->Suivant = pelem; 
		pF->queue = pelem;
	}	
}

int defiler(File *pF) 
{	
	int num = pF->tete->num;

	Arc* ptemp = pF->tete;
	pF->tete = pF->tete->Suivant;
	if (pF->tete == NULL) // file nulle apres avoir defile
		pF->queue = NULL;
	free(ptemp);
	return num;
}

void detruire (File *pF)
{
	while (!est_vide(pF))
		defiler(pF);
}