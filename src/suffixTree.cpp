#include "../includes/suffixTree.hpp"
#include "../includes/match.hpp"
#include <sys/time.h>
#include <sys/resource.h>
#define pb push_back
#define DEBUG false

node initializesNode(int vertex, int init, int end){
    node child;
    child.vertex = vertex;
    child.init = init;
    child.end = end;

    return child;
}

void printString(int init, int end, vector<char> &genomas){
    for(int i=init; i<=end; i++){
        cout << genomas[i];
    }
    cout << endl;
}

string returnString(int init, int end, vector<char> &genomas){
    string ans = "";
    for(int i=init; i<=end; i++){
        ans += genomas[i];
    }
    return ans;
}

/* Explicando as variáveis:
vertex - vértice que usaremos para começar a criar a árvore
suffix_init - início do sufixo que queremos inserir no momento
suffix_end - fim do sufixo que queremos inserir no momento
tree - árvore que vai armazenar os sufixos
genomas - vetor no qual estão armazenados os caracteres do genoma

Obs: Tentei utilizar o mesmo nome de variável para todas as váriaveis que tem o mesmo objetivo, nas diferentes funções
do arquivo. Por isso estou explicando-as apenas uma vez.
*/
void dfsBuild(int vertex, int suffix_init, int suffix_end, vector<vector<node> > &tree, vector<char> &genomas){
    bool noPrefix = true; /* Se for true, indica que não temos prefixo em comum entre o que queremos inserir e 
    o filho que estamos analisando. Caso ela se mantenha como true, indica que nenhum filho da match com
    o que queremos inserir, e portando podemos apenas criar um novo filho e adicionar essa substring. (Acontece no final)
    */

    for(int i = 0; i < tree[vertex].size(); i++){ // For que percorre os filhos do vértice em questão
        int vertexChild = tree[vertex][i].vertex; // Pega o filho 
        int vertex_init = tree[vertex][i].init; // Pega o inicio de onde comeca o filho
        int vertex_end = tree[vertex][i].end; // Pega o fim de onde termina o filho
        
        //Armazena o match parcial (caso houver). Se não houver, recebe o valor de suffix_init
        int matchAmount = checkPartialMatch(suffix_init, suffix_end, vertex_init, vertex_end, genomas);
        
        // Se não tem nenhum match com o filho em questao, só continua no loop.
        if(matchAmount == suffix_init){
            continue;
        } /* Se o filho em questão é prefixo do que queremos inserir, chama o dfs para os filhos desse filho, 
        mandando o resto da substring que queremos inserir */
        if((matchAmount-suffix_init) == (vertex_end-vertex_init+1)){
            noPrefix = false; // Seta como falso porque tem prefixo em comum
            if(DEBUG){ // Usado para debugar 
                cout << "----------------------";
                cout << "\nsufixo: ";
                printString(suffix_init, suffix_end, genomas);
                cout << "chamando dfs para: " ;
                printString(matchAmount, suffix_end, genomas);
            }
            dfsBuild(vertexChild, matchAmount, suffix_end, tree, genomas); // Chama o dfs para esse filho
        }else{  /* Se ocorre um match parcial entre filho em questão e que queremos inserir:
        - Cria um novo filho a partir do pai para armazenar o match;
        - Cria um filho a partir desse novo filho para receber o resto da substring que queremos inserir
        - Atualiza o filho em questão para receber a substring composta pelo que estava nele menos o match (ou seja, o resto)
        - Liga esse filho em questão ao filho que recebeu o match
        - Corta a ligação desse filho em questão com o pai 
        */
            noPrefix = false; // Seta como falso porque tem prefixo em comum
            if(DEBUG){ // Usado para debugar 
                cout << "----------------------";
                cout << "\nsufixo: ";
                printString(suffix_init, suffix_end, genomas);
                cout << "Filho antes da manipulacao: ";
                printString(vertex_init, vertex_end, genomas);
                cout << "\t Filho novo que recebe match parcial: ";
                printString(suffix_init, matchAmount-1, genomas);
                cout << "\t Filho que recebe resto do sufixo: ";
                printString(matchAmount, suffix_end, genomas);
                cout << "\t Atualiza valor do filho que testamos inicialmente: ";
                printString(vertex_init+matchAmount-suffix_init, vertex_end, genomas);
            }
            tree.pb(vector<node>()); // vai receber o match parcial
            tree[vertex].pb(initializesNode(tree.size()-1, suffix_init, matchAmount-1));
            int positionChild = tree.size()-1;
            tree.pb(vector<node>()); // crio um filho dele pra receber o resto de suffix
            tree[positionChild].pb(initializesNode(tree.size()-1, matchAmount, suffix_end));
            tree[positionChild].pb(initializesNode(vertexChild, vertex_init+matchAmount-suffix_init, vertex_end)); //coloco o filho que existia como filho do  match parcial atualizando seu valor
            tree[vertex].erase(tree[vertex].begin()+i); // tira a ligacao de pai e filho
            break;
        }
    }
    if(noPrefix){ // Caso nenhum filho de vertex de match com o que queremos inserir, cria um novo filho para vertex e adiciona essa substring
        if(DEBUG){ // Usado para debugar
            cout << "----------------------";
            cout << "\nsufixo: ";
            printString(suffix_init, suffix_end, genomas);
            cout << "Nao deu match com nenhum filho, insere como o filho novo: ";
            printString(suffix_init, suffix_end, genomas);
        }
        tree.pb(vector<node>());
        tree[vertex].pb(initializesNode(tree.size()-1, suffix_init, suffix_end));           
    }
}

void createsSuffixTree(vector<vector<node> > &tree, vector<char> &genomas){
    /*-----------------------------Variaveis de medida de tempo-------------------*/
    struct timeval inicio, fim;
    double totalmicroseg, totalseg;
    gettimeofday(&inicio, NULL);
    /*----------------------------------------------------------------------------*/

    // Adiciona o primeiro vértice na árvore de sufixos
    tree.pb(vector<node>()); // Adiciona a raiz
    tree.pb(vector<node>()); // Adiciona o primeiro vértice
    // Adiciona o primeiro índice de sufixo na árvore, a partir da raiz (o primeiro sufixo vai ser a ultima posicao do vetor + o indicador de fim $)
    tree[0].pb(initializesNode(1, genomas.size()-2, genomas.size()-1));
    if(DEBUG){ // Usado para debugar
        cout << "Primeiro sufixo inserido: ";
        printString(genomas.size()-2, genomas.size()-1, genomas);
        cout << "----------------------";
    }
    // Percorre o vetor de genomas e chama o dfs para construir a árvore
    for(int i = genomas.size()-3; i >= 0; i--){
        int suffix_init = i;
        int suffix_end = genomas.size()-1;
        dfsBuild(0,suffix_init, suffix_end, tree, genomas);
    }

    /*-----------------------------Variaveis de medida de tempo-------------------------------*/
    gettimeofday(&fim, NULL);
    totalseg = fim.tv_sec - inicio.tv_sec;
    totalmicroseg = fim.tv_usec - inicio.tv_usec;
    if (totalmicroseg <0){
        totalmicroseg += 1000000;
        totalseg -= 1;
    };
    cout << endl;
    cout << "***************************************************************\n";
    cout << "Tempo de processamento dos sufixos: "  << totalseg << " segundos e "<<  totalmicroseg << " microssegundos.\n"; 
    cout << "***************************************************************\n";
    cout << endl;
    /*-----------------------------------------------------------------------------------------*/
}

// Dfs para mostrar a árvore de sufixos completa
void dfsTreeVisualize(int vertex, vector<vector<node> > &tree, vector<char> &genomas, int space){

    for(int i=0; i<tree[vertex].size();i++){
        node vertexChild = tree[vertex][i];
        
        for(int j=0; j<space; j++){
            cout << " ";
        }
        printString(vertexChild.init, vertexChild.end, genomas);
        dfsTreeVisualize(vertexChild.vertex, tree, genomas, space+2);
    }
}

/*
Mantive essas duas variáveis como globais pois preciso usá-las em outras funções mas nao queria retornar as duas.
largestSubstringVertex - recebe o vértice no qual temos a maior substring que se repete
largerSubstringSize - recebe a quantidade de caracteres da maior substring que se repete
startOfSubstring - recebe o inicio da maior substring no vetor de genomas
startOfSubstring - recebe o fim da maior substring no vetor de genomas
pathSize - armazena a quantidade de caracteres encontrado no caminho percorrido até então
*/
int largestSubstringVertex;
int largerSubstringSize = 0;
int startOfSubstring;
int endOfSubstring;

// Dfs que acha o vertice com a maior substring e retorna o tamanho dessa substring
int dfsSearchLargestSubstringSize(int vertex, int pathSize, vector<vector<node> > &tree, vector<char> &genomas){

    for(int i=0; i<tree[vertex].size();i++){
        node vertexChild = tree[vertex][i];
        /*
            Essa primeira parte ignora vértices que possuem apenas um filho que indica fim da string e vértices
            que não possuem nenhum filho.
        */
        if(tree[vertexChild.vertex].size() <= 1){ 
            if(tree[vertexChild.vertex].size() == 1){ 
                if(genomas[tree[vertexChild.vertex][0].init] == '$') continue;
            }else continue;
        } 
       /*
            Essa segunda parte procura um vértice com a maior substring.
        */
        int vertexChildTamanho = vertexChild.end - vertexChild.init + 1; //Pega o tamanho do filho
        int pathActualSize = pathSize + vertexChildTamanho; // Soma com o tamanho do caminho ja percorrido ate chegar nele
        if(pathActualSize >= largerSubstringSize){ // Se for maior que o maior caminho ja encontrado troca seu valor
            largerSubstringSize = pathActualSize;
            largestSubstringVertex = vertexChild.vertex;  // E salva o vertice correspondente a esse maior caminho
        } 
        dfsSearchLargestSubstringSize(vertexChild.vertex, pathActualSize, tree, genomas); // Chama o dfs para descer nos filhos desse vertice
    }
    return largerSubstringSize; 
}

// Função que mostra a maior substring que se repete
string dfsSearchLargestSubstringVisualize(int vertex, vector<vector<node> > &tree, vector<char> &genomas){
    string largerSubstring = "",stringAux = "";

    /*
        Esse for percorre a árvore e acha o vértice que setamos na função de cima como sendo o vértice com 
        a maior substring.
    */
    for(int i=0; i<tree[vertex].size();i++){
        node vertexChild = tree[vertex][i];
        if(vertexChild.vertex == largestSubstringVertex) {
            /* Dado que eu cheguei nesse vértice, apenas vejo a quantidade de nós folhas que ele tem e printo
                como sendo a quantidade de ocorrencias distintas dessa substring no texto.
            */
            cout << "Ela ocorre ";
            cout << tree[vertexChild.vertex].size() <<  " vezes distintas no texto ";
            stringAux = returnString(vertexChild.init, vertexChild.end, genomas);
            endOfSubstring = vertexChild.end;
            return stringAux;
        }
        /*
            Quando acha, volta na recursão concatenando a substring desse vértice com as substrings
            de seu pai, avô , ... , até chegar na raiz.
        */
        largerSubstring = dfsSearchLargestSubstringVisualize(vertexChild.vertex, tree, genomas);
        if(largerSubstring != ""){
            stringAux = returnString(vertexChild.init, vertexChild.end, genomas);
            largerSubstring = stringAux + largerSubstring; 
            return largerSubstring;
        }
        
    }
    return "";
}

void returnPosition(){
    startOfSubstring  = endOfSubstring - largerSubstringSize + 1;
    cout << "A substring comeca na posicao " << startOfSubstring << " e termina na posicao " <<  endOfSubstring << endl;
}

