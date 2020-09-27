#include "../includes/match.hpp"

int checkPartialMatch(int suffix_init, int suffix_end, int vertex_init, int vertex_end, vector<char> &genomas){
    int aux = suffix_init; // Começa recebendo o inicio da substring de interesse
    for(int i = vertex_init; i <= vertex_end; i++){
        if(genomas[i] == genomas[aux]){
            aux++; // Caso ocorra match, "anda" na substring de interesse
        }
        else break;
    }
    return aux; // Retorna a posição da substring de interesse onde o match termina
}