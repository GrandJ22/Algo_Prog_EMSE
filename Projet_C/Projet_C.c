#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define LAMBDA 0.25
#define BETA 0.3
#define GAMMA 0.3
#define DELTA 0.4
#define DUREE_INCUBATION 3
#define DUREE_ZOMBIE 3

typedef enum{
	sain,
	immunise,
	malade,
	mort,
	infecte,
	zombie
}status;

typedef struct _Arc{
	int num;
	struct _Arc* Suivant;
}Arc;

typedef struct{
	status etat;
	int temps_incubation;
}Personne;


typedef struct{
	int nb_sommets;
	Arc** voisins;
	Personne* population;
}Graphe;

void creation_graphe(Graphe* G, const char* grapheFileName);
void Afficher_Graphe(Graphe* G);
void Simulation(Graphe* G);
void Condition_Initiale(Graphe* G);
void Test_Sain(Graphe* G,int source);
void Journee(Graphe* G);

int main(void)
{
	Graphe G;
	srand(time(NULL));
	creation_graphe(&G,"graph.txt");
	Condition_Initiale(&G);
	printf("Veuillez sélectionner votre option :\n1 : Lancer la simulation\n");
	Simulation(&G);
	Afficher_Graphe(&G);
	return 0;
}

void creation_graphe(Graphe* G, const char* grapheFileName)
{
	FILE *fp;
	Arc* Constructeur;
	fp = fopen(grapheFileName, "r");
	
	if (fp != NULL)
	{
		int nb_sommets, nb_arcs, u, v;
		fscanf(fp, "%d%d", &nb_sommets, &nb_arcs);	
		G->nb_sommets=nb_sommets;
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


void Afficher_Graphe(Graphe* G)
{
	Arc* Curseur;
	char Etat_Lecture[10];
	for(int i=0;i<G->nb_sommets;i++)
	{
		switch(G->population[i].etat)
		{
			case sain :
			 strcpy(Etat_Lecture,"sain");
			break;
			case immunise :
			 strcpy(Etat_Lecture,"immunise");
			break;			
			case malade :
			 strcpy(Etat_Lecture,"malade");
			break;			
			case mort :
			 strcpy(Etat_Lecture,"mort");
			break;
			case infecte :
			 strcpy(Etat_Lecture,"infecte");
			break;
			case zombie : 
			 strcpy(Etat_Lecture,"zombie");
			break;
		}
		printf("Personne numéro %d Etat : %s Voisins : ",i+1,Etat_Lecture);
		Curseur=G->voisins[i];
		while(Curseur!=NULL)
		{
			printf("%d ",Curseur->num+1);
			Curseur=Curseur->Suivant;
		}
		printf("\n");
	}
}

void Condition_Initiale(Graphe* G)
{
	int Choix_Noeud,Choix=1;
	while(Choix==1)
	{	
		printf("Qui va mourir ce soir ?\n");
		scanf("%d", &Choix_Noeud);
		G->population[Choix_Noeud-1].etat=infecte;
		printf("Quelqu'un d'autre ?\nOui : 1\nNon : 2\n");
		scanf("%d", &Choix);
		printf("\n");
	}
}

void Test_Sain(Graphe* G,int source)
{
	float r;
	Arc* Curseur=G->voisins[source-1];
	while(Curseur!=NULL && G->population[source-1].etat!=infecte)
	{
		if(G->population[Curseur->num].etat==malade)
		{
			r=((float)rand())/RAND_MAX;
			if(r<=LAMBDA)
			{
				G->population[source-1].etat=infecte;
			}
		}
		Curseur=Curseur->Suivant;
	}
}


void Journee(Graphe* G)
{
	float r;
	for(int i=0;i<G->nb_sommets;i++)
	{
		switch(G->population[i].etat)
		{
			case sain :
			 Test_Sain(G,i+1);
			break;
			case infecte :
			 G->population[i].temps_incubation++;
			 if(G->population[i].temps_incubation>=3)
			 {
			 	G->population[i].etat=malade;
			 }
			break;
			case malade :
			 r=((float)rand())/RAND_MAX;
			 if(r<=BETA)
			 {
			 	G->population[i].etat=mort;
			 }
			 else if(r>BETA && r<=(BETA+GAMMA))
			 {
			 	G->population[i].etat=immunise;
			 }
			break;
		}
	}
}

void Simulation(Graphe* G)
{
	int choix=1;
	while(choix!=3)
	{
		Afficher_Graphe(G);
		printf("\nVoulez-vous :\n1 : Passer un jour\n2 : Passer cent jours\n3 : quitter\n");
		scanf("%d", &choix);
		if(choix==1)
		{
			Journee(G);
		}
		else if(choix==2)
		{
			for(int i=0;i<100;i++)
			{
				Journee(G);
			}
		}
	}
}





































