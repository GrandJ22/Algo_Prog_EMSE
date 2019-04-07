#include "Projet_C.h"

int main(void)
{
	Graphe G;
	Graphe Gi;
	srand(time(NULL));
	creation_graphe(&G,"graph.txt");
	creation_graphe(&Gi,"graph.txt");
	Condition_Initiale(&G,&Gi);
	printf("Veuillez sélectionner votre option :\n1 : Lancer la simulation\n");
	Simulation(&G);
	MetricsCalc(&Gi,&G);

	return 0;
}


void Condition_Initiale(Graphe* G,Graphe* Gi)
{
	int Choix_Noeud,Choix=1;
	while(Choix==1)
	{	
		printf("Qui va mourir ce soir ?\n");
		scanf("%d", &Choix_Noeud);
		G->population[Choix_Noeud-1].etat=infecte;
		G->metrics->healthyCount--;
		G->metrics->infectedCount++;
		Gi->population[Choix_Noeud-1].etat=infecte;
		Gi->metrics->healthyCount--;
		Gi->metrics->infectedCount++;
		G->population[Choix_Noeud-1].infection_date=0;
		printf("Quelqu'un d'autre ?\nOui : 1\nNon : 2\n");
		scanf("%d", &Choix);
		printf("\n");
	}
}

void Test_Sain(Graphe* G,int source)
{
	float r=((float)rand())/RAND_MAX;
	int sickCounter = 0, zombieCounter = 0;
	Arc* Curseur=G->voisins[source];

	while(Curseur!=NULL)
	{
		if(G->population[Curseur->num].etat==malade){
			sickCounter++;
		}
		else if(G->population[Curseur->num].etat==zombie){
			zombieCounter++;
		}
		Curseur=Curseur->Suivant;
	}
	if(r<=LAMBDA*sickCounter+DELTA*zombieCounter)
	{
		G->population[source].etat=infecte;
		G->metrics->healthyCount--;
		G->metrics->infectedCount++;
		G->population[source].infection_date=G->metrics->simulationDuration;
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
			 	Test_Sain(G,i);
			    break;
			case infecte :
			 	G->population[i].temps_incubation++;
				r=((float)rand())/RAND_MAX;
			 	if(G->population[i].temps_incubation>=DUREE_INCUBATION)
			 	{
			 		G->population[i].etat=malade;
					G->metrics->infectedCount--;
					G->metrics->sickCount++;
					break;
			 	}
				if(r<=GAMMA)
				{
					G->population[i].etat=immunise;
					G->metrics->infectedCount--;
					G->metrics->immuneCount++;
				}
			    break;

			case malade :
			    if (G->population[i].sickness_duration == DUREE_ZOMBIE){
                    G->population[i].etat=zombie;
					G->metrics->sickCount--;
					G->metrics->zombieCount++;
                    break;
			    }
			 	r=((float)rand())/RAND_MAX;
			 	if(r<=BETA)
			 	{
			 		G->population[i].etat=mort;
					G->metrics->sickCount--;
					G->metrics->deadCount++;
			 	}
                G->population[i].sickness_duration++;
			    break;
			case zombie :
				if(G->population[i].zombie_lifelength == ZOMBIE_LIFE_EXPENTANCY){
					G->population[i].etat=mort;
					G->metrics->zombieCount--;
					G->metrics->deadCount++;
				}
				G->population[i].zombie_lifelength++;
				break;
		}
	}
}

void Simulation(Graphe* G)
{
	int choix;
	int vaccinationNumber = 0;
	while(choix!=4)
	{
		Afficher_Graphe(G);
		printf("Voulez-vous :\n1 : Passer un jour\n2 : Passer cent jours\n3 : Vacciner une partie de la population\n4 : quitter\n");
		scanf("%d", &choix);
		switch(choix){
		    case 1 :
                Journee(G);
                G->metrics->simulationDuration++;
		        break;
		    case 2 :
                for(int i=0;i<100;i++)
                {
                    Journee(G);
                    G->metrics->simulationDuration++;
                }
		        break;
		    case 3 :
		        printf("Combien de personnes souhaitez-vous vacciner ?\n");
		        scanf("%d",&vaccinationNumber);
		        Vaccination(G,vaccinationNumber);
		        break;
		    default:
		        break;



		}
	}
}

void MetricsCalc(Graphe* Gi, Graphe* Gf){
	FILE *file;
	Gf->metrics->avgInfectionDate=0;
	int unhealthyCount = 0, pathSum = 0, pathLength;

	file = fopen("Métriques.txt","w");
	fprintf(file,"Temps de simulation total : %d jours\n",Gf->metrics->simulationDuration);
	fprintf(file,"Probabilité d'être infecté (lambda) : %f \n",LAMBDA);
	fprintf(file,"Probabilité d'être immunisé (gamma) : %f \n",GAMMA);
	fprintf(file,"Probabilité de mourir (beta) : %f \n",BETA);
	fprintf(file,"Proportion finale d'individus sains  : %f%% \n",(float)Gf->metrics->healthyCount*100/Gf->nb_sommets);
	fprintf(file,"Proportion finale d'individus immunisés  : %f%% \n",(float)Gf->metrics->immuneCount*100/Gf->nb_sommets);
	fprintf(file,"Proportion finale d'individus infectés  : %f%%\n",(float)Gf->metrics->infectedCount*100/Gf->nb_sommets);
	fprintf(file,"Proportion finale d'individus malades  : %f%%\n",(float)Gf->metrics->sickCount*100/Gf->nb_sommets);
	fprintf(file,"Proportion finale d'individus zombies  : %f%%\n",(float)Gf->metrics->zombieCount*100/Gf->nb_sommets);
	fprintf(file,"Proportion finale d'individus morts  : %f%%\n",(float)Gf->metrics->deadCount*100/Gf->nb_sommets);
	for(int i=0;i<Gi->nb_sommets;i++){
		fprintf(file,"Individu n°%d initialement %s finalement %s\n",i+1,statusToStr(Gi->population[i].etat),statusToStr(Gf->population[i].etat));
		if(Gf->population[i].etat != sain && Gf->population[i].etat !=immunise)
		{
			pathLength = parcours_largeur(Gi,i);
			pathSum+=pathLength;
			Gf->metrics->avgInfectionDate+=Gf->population[i].infection_date*pathLength;
			unhealthyCount++;
		}
	}
	fprintf(file,"Temps moyen de contamination, pondéré par la distance initiale au plus proche infecté : %f jours\n",Gf->metrics->avgInfectionDate/pathSum);
	fclose(file);
	printf("Les métriques ont été générées dans le fichier Métriques.txt");

}

void Vaccination(Graphe* G,int vaccinationNumber){
    int toVaccinate;
    int i = 0,k = 0;
    while (vaccinationNumber != 0){
        toVaccinate = (rand()%G->metrics->healthyCount) + 1;
        do{
            if(G->population[i].etat == sain){
                k++;
            }
            i++;
        }while(k != toVaccinate);
        Afficher_Graphe(G);
        printf("%d %d %d\n",i,k,toVaccinate);
        G->population[i-1].etat=immunise;
        vaccinationNumber--;
        G->metrics->immuneCount++;
        G->metrics->healthyCount--;
		i = 0;
		k = 0;
    }
}

































