#ifndef MATCH_HPP
#define MATCH_HPP

#include <iostream>
#include <vector>

using namespace std;

/* Verifica se existe um match parcial entre o sufixo que queremos 
adicionar e a string presente do vértice que estamos visitando

Essa função retorna a posição onde ocorreu o match na string que queremos adicionar na árvore.
Caso não exista match entre essa string e o vértice que estamos comparando, essa função vai
retornar a posição inicial da string de interesse
*/
int checkPartialMatch(int suffix_init, int suffix_end, int vertex_init, int vertex_end, vector<char> &genomas);

#endif