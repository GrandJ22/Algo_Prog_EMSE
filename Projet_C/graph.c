#include "graph.h"

void creation_graphe(Graphe* G, const char* grapheFileName)
{
	FILE *fp;
	Arc* Constructeur;
	fp = fopen(grapheFileName, "r");
	G->metrics=(metricsArray*) malloc(sizeof(metricsArray));
	if (fp != NULL)
	{
		int nb_sommets, nb_arcs, u, v;
		fscanf(fp, "%d%d", &nb_sommets, &nb_arcs);
		G->nb_sommets=nb_sommets;
		G->metrics->healthyCount=nb_sommets;
		G->voisins=(Arc**) malloc(nb_sommets*sizeof(Arc*));
		for (int i = 0; i < nb_sommets; i++)
		{
			G->voisins[i]=NULL;
		}
		for (int i = 0; i < nb_arcs; i++)
		{
			fscanf(fp, "%d %d", &u, &v);
			u--;
			v--;
			Constructeur = (Arc*) malloc(sizeof(Arc));
			Constructeur->num=v;
			Constructeur->Suivant=G->voisins[u];
			G->voisins[u]=Constructeur;
		}
		G->population=(Personne*) malloc(G->nb_sommets*sizeof(Personne));
		for(int i=0;i<nb_sommets;i++)
		{
			G->population[i].etat=sain;
			G->population[i].temps_incubation=0;

		}
	}
	else
	{
		printf("Le fichier n'a pas été trouvé.");
	}
	fclose(fp);
}


int parcours_largeur(Graphe* G, int sommet_id)
{
	File F = Initialiser();
	int sommet_out;
	int* marque = (int*) malloc(G->nb_sommets * sizeof(int));
	
	for (int i = 0; i < G->nb_sommets; i++)
		marque[i] = 0;
	// gestion du decalage entre les numeros des sommets et leur index dans le tableau
	marque[sommet_id] = 1;
	enfiler(&F, sommet_id);
	sommet_out=defiler(&F);
	while( G->population[sommet_out].etat != infecte )
	{ 

		// parcours des successeurs du sommet sommet_out et ajout dans la file lorsqu'ils ne sont pas marque 
		Arc* fils = G->voisins[sommet_out];
		while (fils != NULL) 
		{
			if (marque[fils->num] == 0)
			{
				marque[fils->num] = marque[sommet_out] + 1;
				enfiler(&F, fils->num);	
			}
			fils = fils->Suivant;
		}
		sommet_out=defiler(&F);
	}
	return marque[sommet_out] - 1;
}

void Afficher_Graphe(Graphe* G)
{
	Arc* Curseur;
	for(int i=0;i<G->nb_sommets;i++)
	{
		printf("Personne numéro %d Etat : %s\tVoisins : ",i+1,statusToStr(G->population[i].etat));
		Curseur=G->voisins[i];
		while(Curseur!=NULL)
		{
			printf("%d ",Curseur->num+1);
			Curseur=Curseur->Suivant;
		}
		printf("\n");
	}
}

char* statusToStr(status s){
	switch(s) {
		case sain :
			return "sain";
		case immunise :
			return "immunisé";
		case malade :
			return "malade";
		case mort :
			return "mort";
		case infecte :
			return "infecté";
		case zombie :
			return "zombie";
	}
}
