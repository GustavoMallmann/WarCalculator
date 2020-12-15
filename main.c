#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRIES 10000
#define DADOS 3
#define MANY 26

int mortosA = 0;
int mortosD = 0;
int dadosA[DADOS];
int dadosD[DADOS];

int batalha(int at, int def);
void rolagem(int at, int def, int* dadosA, int* dadosD);
void ordenar(int* dice, int qte);
void troca(int* dice);


int main(){

    int xwins;
    int i, a, b;
    float winpercent;
    FILE* fp;
    fp = fopen("warCalculatorTable.txt", "w");
    srand(time(NULL));
    for(a = 2; a < MANY; a++){
    	for(b = 2; b < MANY; b++){
    		if(a/(b*3) == 0 && a>=b){
    			xwins = 0;
    			for(i = 0; i < TRIES; i++){
        			xwins += batalha(a, b);
    			}
    			winpercent = 100*(float)xwins/TRIES;
    			fprintf(fp,"%d:%d\t%2.2f%%\n", a, b, winpercent);
    		}
		}
		fprintf(fp,"\n");
	}
    fprintf(fp,"\n");
    system("pause");
    return 0;
   }



int batalha(int at, int def){

    int menor = at;
    int i;
    //
    if(def > at){ // não atacar em minoria
        return 0;
    }
    //
    if(def < at)
        menor = def;
    if(menor > DADOS)
        menor = DADOS;
    rolagem(at, def, dadosA, dadosD);
    for(i = 0; i < menor; i++){
        if(dadosA[i] > dadosD[i]){
            def--;
            mortosD++;
        }else{
            at--;
            mortosA++;
        }
    }
    if(at > 0 && def > 0)
        return batalha(at, def);
    else{
        if(at > def)
            return 1;
        else
            return 0;
    }
}

void rolagem(int at, int def, int* dadosA, int* dadosD){

    int qteA, qteD;
    int i;

    if(at >= DADOS)
        qteA = DADOS;
    else
        qteA = at;
    if(def >= DADOS)
        qteD = DADOS;
    else
        qteD = def;

    for(i = 0; i < qteA; i++){
        dadosA[i] = rand()%6;
    }
    for(i = 0; i < qteD; i++){
        dadosD[i] = rand()%6;
    }
    ordenar(dadosA, qteA);
    ordenar(dadosD, qteD);
    return;
}

void ordenar(int* dice, int qte){

    int i, j;

    for(i = 0; i < qte - 1; i++){
        for(j = 0; j < qte - i - 1; j++){
            if(dice[j] < dice[j+1])
                troca(dice + j);
        }
    }
    return;
}

void troca(int* dice){

    int aux;

    aux = *dice;
    *(dice) = *(dice + 1);
    *(dice + 1) = aux;
    return;
}
