/*
Implementação de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjacência
e métodos para utilização de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___
#include <iostream>
#include <vector>
#include <stack>

class TGrafoLista;//para evitar referencia circular

// definição de uma estrutura para armezanar um grafo
// Também seria possível criar um arquivo grafo.h 
// e fazer a inclusão "#include <grafo.h>"
class TGrafo
{
private:
	int n; // quantidade de vértices
	int m; // quantidade de arestas
	float** adj; //matriz de adjacência

	void RecountA();
	bool isSemiStronglyConnected();
	bool isStronglyConnected();
	bool isReachableSTR(int start, int end);
	bool isReachableUtil(int start, int end, bool visited[]);
	std::vector<std::vector<int>> Kosaraju(float** adj_matrix);
	void BuscaProfund1(float** adj_matrix, int vertex, std::stack<int>& stack, std::vector<bool>& visited, int n);
	void BuscaProfund2(float** adj_matrix, int vertex, std::vector<bool>& visited, std::vector<int>& scc, int n);
	void DirectedToNotDirected();
public:
	TGrafo(int n);
	void insereA(int v, int w, float value);
	void removeA(int v, int w);
	void show();
	void ShowMatrixOnly();
	~TGrafo();

	int inDegree(int v);
	int outDegree(int v);
	int isSource(int v);
	int isSorv(int v);
	int isSymmetric();
	TGrafo& FileToGraph(std::string fileName);
	void RemoveV(int v);
	bool isComplete();
	void complementarGraph();
	int isConnected();
	int graphCategory();
	bool canReach(int start, int end);
	TGrafo& GetReducedMatrix();
	void MatrixToFile(std::string filePath);
	void InsertVertix();
};
#endif
