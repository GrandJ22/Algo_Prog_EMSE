//
// Created by magister on 07/04/19.
//

#ifndef ALGO_PROG_EMSE_PROJET_C_H
#define ALGO_PROG_EMSE_PROJET_C_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "graph.h"

#define LAMBDA 0.25
#define BETA 0.3
#define GAMMA 0.05


#define DUREE_INCUBATION 3


#define DUREE_ZOMBIE 3
#define ZOMBIE_LIFE_EXPENTANCY 3
#define DELTA 0.4




void creation_graphe(Graphe* G, const char* grapheFileName);
void Afficher_Graphe(Graphe* G);
void Simulation(Graphe* G, int Type_Graphe);
void Condition_Initiale(Graphe* G,Graphe* Gi);
void Test_Sain(Graphe* G,int source);
void Journee(Graphe* G);
void MetricsCalc(Graphe* Gi, Graphe *Gf);
void Vaccination(Graphe* G,int vaccinationNumber);


#endif //ALGO_PROG_EMSE_PROJET_C_H
