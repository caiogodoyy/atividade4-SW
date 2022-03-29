#include <stdio.h>
#define MAX 999

int main(int argc, char const *argv[])
{
    int processos, quantum, arrTime[MAX], burTime[MAX], temp[MAX];
    //Quantidade de processos e o quantum que vai ser usado no Round Robin
    scanf("%d %d", &processos, &quantum);
    for(int i = 0; i < processos; i++) {
        //Arrival Time e Burst Time
        scanf("%d %d", &arrTime[i], &burTime[i]);
        temp[i] = burTime[i];
    }

    int tempoAtivo = 0, tempoAtivoTotal = 0, tempoResposta = 0, tempoEspera = 0;
    int j = processos, chave = 0;
    for(int i = 0, tempoAtivo = 0; j != 0;) {
        if(temp[i] <= quantum && temp[i] > 0) {
            tempoAtivo = tempoAtivo + temp[i];
            temp[i] = 0;
            chave = 1;
        }
        else if(temp[i] > 0) {
            temp[i] = temp[i] - quantum;
            tempoAtivo = tempoAtivo + quantum;
        }
        
        if(temp[i] == 0 && chave == 1) {
            j--;
            tempoAtivoTotal = tempoAtivoTotal + tempoAtivo;
            tempoResposta = tempoResposta + tempoAtivo - arrTime[i];
            tempoEspera = tempoEspera + (tempoAtivo - arrTime[i]) - burTime[i];
            chave = 0;
        }
        
        if(i == processos - 1)
            i = 0;
        else if(arrTime[i + 1] <= tempoAtivo)
            i++;
        else
            i = 0;
    }
    float mediaTempoAtivo, mediaTempoResposta, mediaTempoEspera;
    mediaTempoAtivo = tempoAtivoTotal / processos;
    mediaTempoResposta = tempoResposta / processos;
    mediaTempoEspera = tempoEspera / processos;
    printf("RR %.1f %.1f %.1f", mediaTempoAtivo, mediaTempoResposta, mediaTempoEspera);
    return 0;
}