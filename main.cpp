#include <fstream> 

#include "includes/suffixTree.hpp"
#define DEBUG false
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char *argv[])
{
    /*-----------------------------Variaveis de medida de tempo-------------------*/
    struct timeval inicio, fim;
    long totalmicroseg, totalseg;
    gettimeofday(&inicio, NULL);
    /*--------------------------------------------------------------------------*/

    vector<char> sarscov; // Cria um vetor para receber os caracteres do arquivo
    ifstream fin("sarscov2.fasta",ifstream::in); // Abre arquivo para leitura em modo texto
    char ch;
    
    while(fin.get(ch)) // Enquanto não for fim de arquivo, lê um caracter 
        if(ch != '\n') sarscov.push_back(ch); // Adiciona todos os caracteres, ignorando o \n
    sarscov.push_back('$'); // Adiciona o cifrão no fim do vetor de texto para indicar a última posicão

    /* A árvore de sufixos será um vetor dinâmico onde cada posição representa um vértice 
    dessa árvore e possui uma lista de adjacências do tipo Node, responsável por armazenar os 
    nós filhos do vértice em questão.
    */
    vector<vector<node> > tree;

    // Chama a função que vai criar a árvore de sufixos para a entrada fornecida
    createsSuffixTree(tree, sarscov);

    if(DEBUG){ // Só printo quando preciso debuggar
        dfsTreeVisualize(0, tree, sarscov, 0); // Printa a árvore de sufixos para visualização
    }
    
    // Chama a função que retorna a quantidade de caracteres da maior substring
    int largestSubstringSize = dfsSearchLargestSubstringSize(0, 0, tree, sarscov);
    cout << "A maior substring que se repete na árvore tem "<< largestSubstringSize << " caracteres"<< endl;

    // Chama a função que retorna os caracteres da maior substring
    string largestSubstringVisualize = dfsSearchLargestSubstringVisualize(0, tree, sarscov);
    cout << "e é representada por: " << largestSubstringVisualize << endl;

    returnPosition(); // Retorna a posicao inicial e final da substring no vetor 

    /*---------------------------------Funcao de medida de tempo total--------------------------*/
    gettimeofday(&fim, NULL);
    totalseg = fim.tv_sec - inicio.tv_sec;
    totalmicroseg = fim.tv_usec - inicio.tv_usec;
    if (totalmicroseg <0){
        totalmicroseg += 1000000;
        totalseg -= 1;
    };
    cout << endl;
    cout << "***************************************************************\n";
    cout << "Tempo total: "  << totalseg << " segundos e "<<  totalmicroseg << " microssegundos.\n"; 
    cout << "***************************************************************\n";
    cout << endl;
    /*-----------------------------------------------------------------------------------------*/
    
}
