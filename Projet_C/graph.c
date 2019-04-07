#include "graph.h"

void creation_graphe(Graphe* G, const char* grapheFileName)
{
	FILE *fp;
	fp = fopen(grapheFileName, "r");
	
	if (fp != NULL) // le fichier est trouve
	{
		int nb_sommets, nb_arcs, u, v, w;
		fscanf(fp, "%d%d", &nb_sommets, &nb_arcs);	
		G->nb_sommets 	= nb_sommets;
		G->successeurs	= (Arc**)malloc(nb_sommets * sizeof(Arc*));

		for (int i = 0; i < nb_sommets; i++) 
			G->successeurs[i]	= NULL;

		for (int i = 0; i < nb_arcs; i++) 
		{
			fscanf(fp, "%d %d %d", &u, &v, &w);
			u--; // decrement pour gerer le decalage entre le numeros des sommets dans le fichiers et les index dans les tableaux
			v--;
			//ajout d'un arc (u,v) : un maillon est ajoute en debut de la liste de successeurs de u
			Arc* s		= (Arc*) malloc(sizeof(Arc));
			s->num		= v;
			s->Suivant			= G->successeurs[u];
			G->successeurs[u]	= s;
		}
	}
	else printf("Le fichier n'a pas �t� trouv�.");
	fclose(fp);
}


int parcours_largeur(Graphe* G, int sommet_id)
{
	File F = Initialiser();
	int sommet_out;
	int* marque = (int*) malloc(G->nb_sommets * sizeof(int));
	
	for (int i = 0; i < G->nb_sommets; i++)
		marque[i] = 0;

	sommet_id--; // gestion du decalage entre les numeros des sommmets et leur index dans le tableau
	marque[sommet_id] = 1;
	enfiler(&F, sommet_id);

	while( !est_vide(&F) ) 
	{ 
		sommet_out=defiler(&F);
		// parcours des successeurs du sommet sommet_out et ajout dans la file lorsqu'ils ne sont pas marque 
		Arc* fils = G->successeurs[sommet_out];
		while (fils != NULL) 
		{
			if (marque[fils->num] != 1)
			{
				marque[fils->num] = 1; 
				printf(" (%d) ", fils->num +1);			
				enfiler(&F, fils->num);	
			}
			fils = fils->Suivant;
		}
	} 
} 

void affichage_graphe(Graphe* G) 
{
	Arc* courant;

	for(int i = 0; i < G->nb_sommets; i++) 
	{
		printf("Sommet %d : ", i+1);
		courant = G->successeurs[i];
		while(courant != NULL)
		{
			printf("%d, ", courant->num +1);
			courant = courant->Suivant;
		} 
		printf("\n");
	}
}


