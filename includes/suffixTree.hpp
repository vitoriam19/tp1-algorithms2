#ifndef SUFFIXTREE_HPP
#define SUFFIXTREE_HPP

#include <iostream>
#include <vector>

using namespace std;

/* Estrutura que vai representar um nó da árvore
Parametros:
    vertex = representa o vértice correspondente
    init = posição do inicio da substring no vetor de genomas
    end = posição do fim da substring no vetor de genomas
*/
typedef struct Node {
    int vertex;
    int init;
    int end;
} node;

// Função que inicializa e preenche um nó filho
node initializesNode(int vertex, int init, int end);

// Função que cria a árvore de sufixos
void createsSuffixTree(vector<vector<node> > &tree, vector<char> &genomas);

// Dfs usado na construção da árvore de sufixo
void dfsBuild(int vertex, int suffix_init, int suffix_end, vector<vector<node> > &tree, vector<char> &genomas);

// Função que printa a árvore de sufixos para fins de visualização
void dfsTreeVisualize(int vertex, vector<vector<node> > &tree, vector<char> &genomas, int space);

// Função que printa uma substring do vetor de genomas dado seu inicio e fim
void printString(int init, int end, vector<char> &genomas);

// Função que retorna uma substring do vetor de genomas dado seu inicio e fim
string returnString(int init, int end, vector<char> &genomas);

// Função que retorna o tamanho (quantidade de caracteres) da maior substring que se repete 
int dfsSearchLargestSubstringSize(int vertex, int pathSize, vector<vector<node> > &tree, vector<char> &genomas);

// Função que retorna a maior substring que se repete 
string dfsSearchLargestSubstringVisualize(int vertex, vector<vector<node> > &tree, vector<char> &genomas);

// Função que printa o inicio e o fim da maior substring no vetor de caracteres
void returnPosition();
#endif