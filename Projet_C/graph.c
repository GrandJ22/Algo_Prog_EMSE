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

void Afficher_Graphe_Quelconque(Graphe* G)
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

void Afficher_Graphe_Grille(Graphe* G)
{
	int taille = (int) sqrt( (double) G->nb_sommets );
	for(int i=0;i<taille;i++)
	{
		for(int j=0;j<taille;j++)
		{
			switch(G->population[taille*i+j].etat)
			{
				case infecte :
				 printf("\033[0;33m"); //Jaune
				break;
				case malade :
				 printf("\033[0;31m"); //Rouge
				break;
				case mort :
				 printf("\033[0;35m"); //Magenta
				break;
				case zombie :
				 printf("\033[0;32m"); //Vert
				break;
				case immunise :
				 printf("\033[0;36m"); //Cyan
				break;
			}
			printf("%d	", taille*i+j+1);
			printf("\033[0m");
		}
		printf("\n");
	}
	printf("\n");
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

void Creer_Graphe_Grille(int n)
{
	FILE* fichier=fopen("graph_grille.txt","w");
	int nb_arretes=4*n*(n-1);
	fprintf(fichier,"%d %d\n",n*n,nb_arretes);
	for(int i=0;i<n*n;i++)
	{
		if(i==0)
		{
			fprintf(fichier,"1 2\n");
			fprintf(fichier,"1 %d\n",n+1);
		}		
		else if(i==(n-1))
		{
			fprintf(fichier,"%d %d\n",n,n-1);
			fprintf(fichier,"%d %d\n",n,2*n);
		}		
		else if(i==n*(n-1))
		{
			fprintf(fichier,"%d %d\n",n*(n-1)+1,n*(n-1)+1-n);
			fprintf(fichier,"%d %d\n",n*(n-1)+1,n*(n-1)+2);
		}
		else if(i==n*n-1)
		{
		 	fprintf(fichier,"%d %d\n",n*n,n*n-1);
			fprintf(fichier,"%d %d\n",n*n,n*(n-1));
		}	
		else if( i>=1 && i<=(n-2) )
		{
			fprintf(fichier,"%d %d\n",i+1,i);
			fprintf(fichier,"%d %d\n",i+1,i+1+n);
			fprintf(fichier,"%d %d\n",i+1,i+2);
		}
		else if( i%n==0 )
		{
			fprintf(fichier,"%d %d\n",i+1,i+1-n);
			fprintf(fichier,"%d %d\n",i+1,i+2);
			fprintf(fichier,"%d %d\n",i+1,i+1+n);
		}
		else if( (i+1)%n==0 )
		{
			fprintf(fichier,"%d %d\n",i+1,i+1-n);
			fprintf(fichier,"%d %d\n",i+1,i);
			fprintf(fichier,"%d %d\n",i+1,i+1+n);
		}
		else if( i>=(n*(n-1)+1) && i<=(n*n-2))
		{
			fprintf(fichier,"%d %d\n",i+1,i);
			fprintf(fichier,"%d %d\n",i+1,i+1-n);
			fprintf(fichier,"%d %d\n",i+1,i+2);
		}
		else
		{
			fprintf(fichier,"%d %d\n",i+1,i+2);
			fprintf(fichier,"%d %d\n",i+1,i);
			fprintf(fichier,"%d %d\n",i+1,i+1+n);
			fprintf(fichier,"%d %d\n",i+1,i+1-n);
		}
	}
	fclose(fichier);
}

