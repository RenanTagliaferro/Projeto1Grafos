#include <iostream>
#include <fstream>
#include "TGrafo.h"
#include <vector>
#include <queue>
#include <stack>

// Construtor do TGrafo, responsável por 
// Criar a matriz de adjacência v x v do Grafo
TGrafo::TGrafo(int n)
{
    this->n = n;
    // No início dos tempos não há arestas
    this->m = 0;
    // aloca da matriz do TGrafo
    float** adjac = new float* [n];
    for (int i = 0; i < n; i++)
        adjac[i] = new float[n];
    adj = adjac;
    // Inicia a matriz com zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = INT_MAX;
}

// Destructor, responsável por
// liberar a memória alocada para a matriz
TGrafo::~TGrafo()
{//destrutor tava meio errado, não liberava tudo.
    for (int i = 0; i < n; i++)
        delete[] adj[i];

    delete[] adj;

    std::cout << "\nespaco liberado";
    adj = nullptr; // Set to nullptr after deletion
}

// Insere uma aresta no Grafo tal que
// v é adjacente a w
void TGrafo::insereA(int v, int w, float value)
{
    // testa se nao temos a aresta
    if (adj[v][w] == INT_MAX)
    {
        adj[v][w] = value;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w)
{
    // testa se temos a aresta
    if (adj[v][w] != INT_MAX)
    {
        adj[v][w] = INT_MAX;
        m--; // atualiza qtd arestas
    }
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida
void TGrafo::show()
{
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adj[i][w] == INT_MAX)
                std::cout << "Adj[" << i << "," << w << "]= inf" << " ";

            else std::cout << "Adj[" << i << "," << w << "]= " << adj[i][w] << " ";
    }
    std::cout << "\nfim da impressao do grafo." << std::endl;
}
void TGrafo::ShowMatrixOnly()
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (w == n-1)
            {
                if (adj[i][w] == INT_MAX)
                    std::cout << "0";

                else std::cout << "1";
            }
            else
            {
                if (adj[i][w] == INT_MAX)

                    std::cout <<"0" << ",";

                else std::cout  << "1" << ",";
            }
    }
    std::cout << "\nfim da impressao do grafo." << std::endl;
}

int TGrafo::inDegree(int v)
{
    if (v > n - 1 || v < 0)//checa se terá out-of-index
    {
        std::cout << "\nO vertice de indice (" << v << ") que foi passado de entrada nao existe: ";
        return -1;
    }

    int degree = 0; //o grau
    for (int i = 0; i < n; i++)//percorre cada vertice para ver se aresta vinda do v chega nele
        if (adj[i][v] != INT_MAX) // se for != INTMAX tem V chegando nele
            degree++; //incremente o grau
    return degree;
}

int TGrafo::outDegree(int v)
{
    if (v > n - 1 || v < 0)//checa se terá out-of-index
    {
        std::cout << "\nO vertice de indice (" << v << ") que foi passado de entrada nao existe: ";
        return -1;
    }

    int degree = 0; //o grau
    for (int i = 0; i < this->n; i++)//percorre as arestas na linha de vertice indicado
        if (adj[v][i] != INT_MAX) // se for != INTMAX tem alguem chegando nele
            degree++; //incremente o grau
    return degree;
}

int TGrafo::isSource(int v)
{
    //(grau de saída maior que zero e grau de entrada igual a 0)
    if (v > n - 1 || v < 0)//checa se terá out-of-index
    {
        std::cout << "\nO vertice de indice (" << v << ") que foi passado de entrada nao existe: ";
        return -1;
    }

    int inDegree = this->inDegree(v);
    if (inDegree > 0)
        return 0;

    int outDegree = this->outDegree(v);
    if (outDegree > 0)
        return 1;
}

int TGrafo::isSorv(int v)
{
    //(grau de entrada maior que zero e grau de saída igual a 0)
    if (v > n - 1 || v < 0)//checa se terá out-of-index
    {
        std::cout << "\nO vertice de indice (" << v << ") que foi passado de entrada nao existe: ";
        return -1;
    }
    int outDegree = this->outDegree(v);
    if (outDegree > 0)
        return 0;

    int inDegree = this->inDegree(v);
    if (inDegree > 0)
        return 1;
}

int TGrafo::isSymmetric()
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < m; j++)//simetria basta checar triangulo superior da matrix por isso o i+1 (mais eficiente)
            if (i != j && adj[i][j] != adj[j][i])//não precisa olhar se i = j caso do 0,0
                return 0;
    return 1;
}

TGrafo& TGrafo::FileToGraph(std::string fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        TGrafo grafo(0);
        return grafo;
    }
    int ignore;
    file >> ignore;//pula primeira linha.
    int a, v = 0;
    file >> v;// le a segunda linha == vertices
    for (int i = 0; i < v; i++)
        file >> ignore;//ja que o id e o numero da linnha são iguais o id é irrelevante de ser guardado

    file >> a;//le o num de arestas

    TGrafo* grafo = new TGrafo(v);

    // Lê as arestas do arquivo e atualiza a matriz, m é o num de linhas a serem lidas
    this->m = 0;
    for (int i = 0; i < a; ++i)
    {
        int x, y, z = 0;
        file >> x >> y >> z;
        grafo->insereA(x-1, y-1, z);//-1 pq o indice começa no zero, mas a linha no 1.
    }
    file.close();
    return *grafo;
}

void TGrafo::RemoveV(int v)
{
    float** oldMatrix = this->adj;
    float** newMatrix = new float* [n - 1];
    int newSize = this->n - 1;

    for (int i = 0, newRow = 0; i < n; ++i)
    {
        // pula a linha
        if (i == v)
            continue;

        newMatrix[newRow] = new float[newSize];
        for (int j = 0, newCol = 0; j < n; ++j)
        {
            // pula a coluna
            if (j == v)
                continue;

            // Copy the remaining values
            newMatrix[newRow][newCol] = oldMatrix[i][j];
            ++newCol;
        }
        ++newRow;
    }//assim ja deleta vertice e arestas, 

    for (int i = 0; i < n; ++i)
        delete[] oldMatrix[i];
    delete[] oldMatrix;

    this->adj = newMatrix;
    this->n = newSize;

    void RecountA();
}

void TGrafo::RecountA()//essa reconta as arestas
{
    this->m = 0;
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            if (this->adj[i][j] != INT_MAX)
                m++;
}

bool TGrafo::isComplete()
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
        {
            if (i == j)
                continue;
            if (i != j && this->adj[i][j] == INT_MAX)
                return false;
        }
    return true;
}

void TGrafo::complementarGraph()
{
    float** mTemp = adj;
    float** mComp = new float* [n];
    for (int i = 0; i < n; i++) {

        mComp[i] = new float[n];
        for (int j = 0; j < n; j++) {
            if (mTemp[i][j] == INT_MAX)
            {
                mComp[i][j] = 1;
            }
            else mComp[i][j] = INT_MAX;
        }
    }
    adj = mComp;

    RecountA();

    for (int i = 0; i < n; i++)
        delete[] mTemp[i];
    delete[] mTemp;
}

int TGrafo::graphCategory()
{
    if (this->isStronglyConnected())
        return 3;//c3
    else if (this->isSemiStronglyConnected())
        return 2;//c2
    else if (this->isConnected() == 0)
        return 1;//c1
    else
        return 0;//c0
}

int TGrafo::isConnected() {
    float** originalGraph = new float* [n];//copiando a amtrix para virar n direcionado temporariamente
    for (int i = 0; i < n; ++i)
    {
        originalGraph[i] = new float[n];
        for (int j = 0; j < n; ++j)
            originalGraph[i][j] = adj[i][j];
    }

    this->DirectedToNotDirected();// já que conectividade é só checar se há conexões, podemos transformá-lo em não direcionado.
    std::vector<bool> visitado(n, false); // marca os vértices já visitados
    std::queue<int> fila; // fila para a busca em largura

    // Verifica se o grafo está vazio
    if (n == 0) {
        std::cout << "Grafo vazio!" << std::endl;
        return 0; // Grafo vazio é considerado conexo
    }

    // Inicia a busca em largura a partir do vértice 0
    fila.push(0);
    visitado[0] = true;

    // Realiza a busca em largura
    while (!fila.empty()) {
        int vertice = fila.front();
        fila.pop();

        // Percorre todos os vizinhos do vértice atual
        for (int vizinho = 0; vizinho < n; ++vizinho) {
            if (adj[vertice][vizinho] != INT_MAX && !visitado[vizinho]) {
                fila.push(vizinho);
                visitado[vizinho] = true;
            }
        }
    }
    this->adj = originalGraph;//volta a ser direcionado
    // Verifica se todos os vértices foram visitados
    for (bool v : visitado) {
        if (!v) {
            return 1; // Grafo é desconexo
        }
    }

    return 0; // Grafo é conexo

}

void TGrafo::DirectedToNotDirected()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (this->adj[i][j] != INT_MAX)
                this->adj[j][i] = this->adj[i][j];

}

bool TGrafo::isStronglyConnected()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && (!isReachableSTR(i, j) || !isReachableSTR(j, i)))
                return false;
    return true;
}

bool TGrafo::isReachableSTR(int start, int end)
{
    bool* visited = new bool[n] {false};
    bool result = isReachableUtil(start, end, visited);
    delete[] visited;
    return result;
}

bool TGrafo::isReachableUtil(int start, int end, bool visited[])
{
    if (start == end)
        return true;

    visited[start] = true;

    for (int k = 0; k < n; ++k)
        if (!visited[k] && adj[start][k] != INT_MAX)
            if (isReachableUtil(k, end, visited))
                return true;

    return false;
}

bool TGrafo::isSemiStronglyConnected()
{//Para cada par de vértices (i, j), verifica se há um caminho direcionado de i para j ou um caminho direcionado de j para i.
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && !canReach(i, j) && !canReach(j, i))
                return false;
    return true;
}

bool TGrafo::canReach(int start, int end)
{// Verifica se há um caminho direcionado da origem para destino.
    std::vector<bool> visited(n, false);
    std::stack<int> stack;

    stack.push(start);
    visited[start] = true;

    while (!stack.empty())
    { // Percorre os vizinhos de v atual
        int current = stack.top();
        stack.pop();
        // Verifica se há uma aresta direcionada de v atual e vizinhos não visitados
        for (int neighbor = 0; neighbor < n; ++neighbor)
        {
            if (adj[current][neighbor] != INT_MAX && !visited[neighbor])
            {
                stack.push(neighbor);
                visited[neighbor] = true;
                // Se o vizinho ja for for o destino, ja esta conectado diretamente
                if (neighbor == end)
                    return true;
            }
        }
    }
    return false;
}


TGrafo& TGrafo::GetReducedMatrix()
{
    std::vector<std::vector<int>> scc = Kosaraju(this->adj);

    int index = 0;
    for (auto& component : scc)
    {

        std::cout << "Componente Fortemente Conectado encontrado, indice: " << index << " : Membros: ";
        for (int vertex : component)
            std::cout << vertex+1 << " ";

        index++;
        std::cout << std::endl;

    }

    int tamGReduzido = scc.size();

    float** sccMatrix = new float* [tamGReduzido];
    for (int i = 0; i < tamGReduzido; ++i)
    {
        sccMatrix[i] = new float[tamGReduzido];
        for (int j = 0; j < tamGReduzido; ++j)
            sccMatrix[i][j] = INT_MAX;  // inicializando matriz nova
    }

    // Itera em cada componente fortemente conectado
    for (int i = 0; i < tamGReduzido; ++i)
    {
        // Itera em cada vertice do componente fortemente conectado
        for (int vertex : scc[i])
        {
            // checa quem tinha aresta com ele na matrix original
            for (int neighbor = 0; neighbor < n; ++neighbor)
            {
                //se tinha aresta na matriz original
                if (this->adj[vertex][neighbor] != INT_MAX)
                {
                    //acha qual o componente com qual ele tem uma aresta
                    for (int j = 0; j < tamGReduzido; ++j)
                    {
                        // se achar o componente:
                        if (std::find(scc[j].begin(), scc[j].end(), neighbor) != scc[j].end())
                        {
                            // checa antes se não é ele mesmo
                            if (i != j)
                            {
                                sccMatrix[i][j] = 1; //adiciona a aresta na matriz nova
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    TGrafo* grafoReduzido = new TGrafo(tamGReduzido);
    grafoReduzido->adj = sccMatrix;
    grafoReduzido->n = (tamGReduzido);
    grafoReduzido->RecountA();
    return *grafoReduzido;

}

void TGrafo::BuscaProfund1(float** adj_matrix, int vertex, std::stack<int>& stack, std::vector<bool>& visited, int n)
{
    visited[vertex] = true;
    for (int neighbor = 0; neighbor < n; ++neighbor)
        if (adj_matrix[vertex][neighbor] != INT_MAX && !visited[neighbor])
            BuscaProfund1(adj_matrix, neighbor, stack, visited, n);

    stack.push(vertex);
}

void TGrafo::BuscaProfund2(float** adj_matrix, int vertex, std::vector<bool>& visited, std::vector<int>& scc, int n)
{
    visited[vertex] = true;
    scc.push_back(vertex);
    for (int neighbor = 0; neighbor < n; ++neighbor)
        if (adj_matrix[vertex][neighbor] != INT_MAX && !visited[neighbor])
            BuscaProfund2(adj_matrix, neighbor, visited, scc, n);

}

std::vector<std::vector<int>> TGrafo::Kosaraju(float** adj_matrix)
{
    int n = this->n;
    //1: pilha vazia, e todos os virtices não visitados
    std::stack<int> stack;
    std::vector<bool> visited(n, false);

    //2: pra cada vertice não visitado, faz percorre no metodo "depth-first" (profundidade).
    for (int vertex = 0; vertex < n; ++vertex)
        if (!visited[vertex])
            BuscaProfund1(adj_matrix, vertex, stack, visited, n);

    //3: Cria Grafo reverso, revertendo todos os arcos.
    float** reverse_adj_matrix = new float* [n];
    for (int i = 0; i < n; ++i)
        reverse_adj_matrix[i] = new float[n];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            reverse_adj_matrix[i][j] = adj_matrix[j][i];

    //4:Pop de todos os vertices da pilha, e faz outra busca "depth-first" (profundidade) no grafo invertido.
    visited.assign(n, false);//mesma coisa que rodar um loop pra colocar todos ns para false;
    std::vector<std::vector<int>> strongly_connected_components;
    while (!stack.empty())
    {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex])
        {
            std::vector<int> scc;
            BuscaProfund2(reverse_adj_matrix, vertex, visited, scc, n);
            strongly_connected_components.push_back(scc);
        }
    }
    //5: retorna a lista de fortemente conectados
    return strongly_connected_components;
}

void TGrafo::MatrixToFile(std::string filePath)
{
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) 
    {
        std::cerr << "Erro ao abrir aquivo" << std::endl;
        return;
    }
    outputFile <<  6 << std::endl;//poe to tipo do grafo
    outputFile << this->n << std::endl;//n
    for (int i = 0; i < this->n; ++i) 
        outputFile << i + 1 << std::endl;//ids dos vertices


    outputFile << this->m << std::endl;//m
    for (int i = 0; i < this->n; ++i) 
    {
        for (int j = 0; j < this->n; ++j) 
        {
            if (this->adj[i][j] != INT_MAX) 
            {
                outputFile << i + 1 << " " << j + 1 << " " << this->adj[i][j] << std::endl;
            }
        }
    }

    outputFile.close();
}
void TGrafo::InsertVertix()
{
    int v = this->n;
    std::cout << "\nNumero atual de vertices: " << v << ".\n";
    std::cout << "\nindice do novo vertice: " << v << ". Id do novo vertice: \n" << v + 1 << ".\n";
    int newSize = v + 1;
    float** oldMatrix = this->adj;
    float** newMatrix = new float* [newSize];

    for (int i = 0; i < newSize; ++i) 
    {
        newMatrix[i] = new float[newSize];
        for (int j = 0; j < newSize; ++j) 
        {
            if (i < v && j < v)
                // Copiar a matriz antiga
                newMatrix[i][j] = oldMatrix[i][j];

            else 
                // Inicializar novas células com INT_MAX
                newMatrix[i][j] = INT_MAX;
        }
    }

    // Deletar a matriz antiga
    for (int i = 0; i < v; ++i) 
        delete[] oldMatrix[i];
    delete[] oldMatrix;

    this->adj = newMatrix;
    this->n = newSize;
}

void TGrafo::GetAllDegrees()
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Vertice: " << i <<"\n";
        std::cout << "Grau Entrada: " << inDegree(i) << "\n";
        std::cout << "Grau Saida:" << outDegree(i) << "\n\n";
    }
}

void TGrafo::WelshPowell()
{
    std::vector<int> cores(n, -1); // Inicializa vetor de cores com -1 (indicando não colorido)
    std::vector<bool> naoColoridos(n, true); // Inicializa vetor de booleanos para indicar vértices não coloridos

    int k = 0; // Número atual da classe de cor

    // Enquanto houver vértices não coloridos
    while (std::find(naoColoridos.begin(), naoColoridos.end(), true) != naoColoridos.end())
    {
        std::vector<int> Ck; // Vetor de vértices da classe de cor k

        // Itera sobre os vértices não coloridos
        for (int i = 0; i < n; i++)
        {
            if (naoColoridos[i])
            {
                bool podeColorir = true;

                // Verifica se algum vizinho de i já foi colorido com a cor k
                for (int j = 0; j < n; j++)
                {
                    if (adj[i][j] != INT_MAX && cores[j] == k)
                    {
                        podeColorir = false;
                        break;
                    }
                }

                // Se nenhum vizinho foi colorido com a cor k, adiciona i à classe de cor k
                if (podeColorir)
                {
                    Ck.push_back(i);
                    cores[i] = k; // Marca i com a cor k
                    naoColoridos[i] = false; // Marca i como colorido
                }
            }
        }

        // Imprime os vértices da classe de cor k
        std::cout << "Cor " << k + 1 << " vertices {";
        for (size_t i = 0; i < Ck.size(); i++)
        {
            std::cout << Ck[i] + 1;
            if (i != Ck.size() - 1)
                std::cout << ",";
        }
        std::cout << "}" << std::endl;
        k++; // Avança para a próxima classe de cor
    }

    // Exibe as cores atribuídas aos vértices
    std::cout << "\nNumero de cores diferentes: " << k << "\n\n";
    for (int i = 0; i < n; i++)
        std::cout << "Vertice " << i + 1 << " tem a cor numero " << cores[i] + 1 << std::endl;

}