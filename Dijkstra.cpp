#include <iostream>
using namespace std;
#include <bits/stdc++.h>

typedef int Valores;

class Grafo
{
private:
    int arestaNula;
    int maximoVertices;
    int numeroVertices;
    Valores *vertices;
    int **matrizAdjacencias;
    int origem, destino, pai, dist, peso[30], custo[30][30]; // matriz de custo(distancia)

public:
    Grafo(int max, int valorarestanula);
    void inserevertice(Valores valor);
    int obterindice(Valores valor);
    void inserearesta(Valores Nosaida, Valores Noentrada, int peso);
    int menorCaminho();
    void dijkstra(int origem);
    void imprimirTabelaDistancia(int dist[], int pai[]);
    int menorCaminho(int dist[], bool visitado[]);
    void imprimirMatriz();
};

Grafo::Grafo(int max, int valorArestaNula) // construtor
{
    numeroVertices = 0;
    maximoVertices = max;
    arestaNula = valorArestaNula;

    vertices = new Valores[maximoVertices];
    matrizAdjacencias = new int *[maximoVertices];
    for (int i = 0; i < maximoVertices; i++)
    {
        matrizAdjacencias[i] = new int[maximoVertices];
    }
    for (int i = 0; i < maximoVertices; i++)
    {
        for (int j = 0; j < maximoVertices; j++)
        {
            matrizAdjacencias[i][j] = arestaNula;
        }
    }
}
int Grafo::obterindice(Valores valor)
{
    int indice = 0;
    while (valor != vertices[indice])
    {
        indice++;
    }
    return indice;
}

void Grafo::inserevertice(Valores valor)
{
    vertices[numeroVertices] = valor;
    numeroVertices++;
}

void Grafo::inserearesta(Valores Nosaida, Valores Noentrada, int peso)
{
    int linha = obterindice(Nosaida);
    int coluna = obterindice(Noentrada);
    matrizAdjacencias[linha][coluna] = peso;
    matrizAdjacencias[coluna][linha] = peso;
}
// achar menor caminho
int Grafo::menorCaminho(int dist[], bool visitado[])
{
    int chave = 0;
    int min = INT_MAX; // inicialza no infinito
    /*/para cada aresta obter a distancia e entao verificar se a distancia e menor que o valor minimo, tambem  verificar se a aresta ja esta visitado/*/
    for (int i = 0; i < maximoVertices; i++)
    {
        if (!visitado[i] && dist[i] < min)
        {
            min = dist[i]; // atualizar valor minimo
            chave = i;
        }
    }
    return chave; // retorna a aresta correspondente
}

void Grafo::imprimirTabelaDistancia(int dist[], int pai[])
{
    for (int i = 0; i < maximoVertices; i++)
    {
        int temp = pai[i];
        cout << i << " <- ";
        while (temp != -1)
        {
            cout << temp << " <- ";
            temp = pai[temp];
        }
        cout << endl;
        cout << "::::Distancia = " << dist[i];
        cout << endl;
    }
}

void Grafo::dijkstra(int origem)
{
    int pai[30], dist[30];
    bool visitado[30] = {0};                    // se inicia em 0
    fill(dist, dist + maximoVertices, INT_MAX); // preencher de infinito

    dist[origem] = 0; //A distância do vértice de origem de si mesmo é sempre 0
    pai[origem] = -1;

    for (int g = 0; g < maximoVertices - 1; g++)
    {
        int u = menorCaminho(dist, visitado);
        visitado[u] = true;             // marcar como visitado
        cout << " Min = " << u << endl; 
        for (int v = 0; v < maximoVertices; v++)
        {
            if (!visitado[v] && (dist[u] + custo[u][v]) < dist[v] && custo[u][v] != 9999) //
            {
                pai[v] = u; //vertice pai recebe menor caminho
                dist[v] = dist[u] + custo[u][v];
            }
        }
    }

    imprimirTabelaDistancia(dist, pai);
}

void Grafo::imprimirMatriz()
{
    cout << "Matriz de adjacencias DIJSKSTRA:\n";
    for (int i = 0; i < maximoVertices; i++)
    {
        for (int j = 0; j < maximoVertices; j++)
        {
            cout << matrizAdjacencias[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int max = 30, valorarestanula = 0, origem;
    Grafo grafo1(max, valorarestanula);
    Valores item1[30], item2[30];
    int valor, peso[30];

    cout << "Inserindo Vertices...\n";
    for (int i = 0; i < max; i++)
    {
        srand(i);
        item1[i] = rand() % 1000;
        grafo1.inserevertice(item1[i]);
    }

    cout << "Inserindo Arestas...\n";
    for (int i = 0; i < 30; i++)
    {
        srand(i);
        valor = rand() % 30;
        item2[i] = item1[valor];
        peso[i] = rand() % 20;
        grafo1.inserearesta(item1[i], item2[i], peso[i]);
    }
    grafo1.imprimirMatriz();
  
    cout << "\n Origem: ";
    cin >> origem;
    grafo1.dijkstra(origem);

    return 0;
}