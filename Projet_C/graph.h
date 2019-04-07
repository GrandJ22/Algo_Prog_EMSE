#ifndef GRAPH_H
#define GRAPH_H

#include "pFile.h"

// graphe : defini par son nombre de sommets et un tableau contenant une liste de successeurs pour chaque sommet
// chaque case du tableau contient un pointeur vers un maillon de liste (le premier de la liste, ou NULL si la liste est vide)



typedef enum{
	sain,
	immunise,
	malade,
	mort,
	infecte,
	zombie
}status;



typedef struct{
	status etat;
	int temps_incubation;
	int infection_date;
	int sickness_duration;
	int zombie_lifelength;
}Personne;

typedef struct{
	int simulationDuration;
	int initialInfectedCount;
	float avgInfectionDate;
	int healthyCount;
	int immuneCount;
	int infectedCount;
	int sickCount;
	int deadCount;
	int zombieCount;
}metricsArray;

typedef struct{
	int nb_sommets;
	Arc** voisins;
	Personne* population;
	metricsArray* metrics;
}Graphe;

void creation_graphe(Graphe* G, const char* grapheFileName); // creation du graphe a partir du fichier
void Afficher_Graphe(Graphe* G);  // affichage du graphe, en affichant les listes de successeurs
int parcours_largeur(Graphe* G, int sommet_id); // affichage des sommets dans l'ordre du parcours en largeur
char* statusToStr(status s);
#endif 
