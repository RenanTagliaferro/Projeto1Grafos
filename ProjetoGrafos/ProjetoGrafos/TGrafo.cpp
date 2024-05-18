/*Lucas Meres  	10395777
Renan Tagliaferro	10395211
Thiago Leandro Liporace	10395816
*/
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

bool TGrafo::EulerianPossible()
{
    int grauImpar = 0;
    int somaGrau = 0;
    int con = this->isConnected();
    if (con == 1)
    {
        std::cout << "Grafo desconexo\n";
        return false;
    }
    for (int i = 0; i < n; ++i)
    {
        int degree = 0;
        for (int j = 0; j < n; ++j)
        {
            if (adj[i][j] != INT_MAX)
                degree++;
        }
        somaGrau += degree;
        if (degree % 2 != 0)
            grauImpar++;
    }
    //Em qualquer grafo existe sempre um número par de vértices de grau impar &&
    //Um grafo conexo ou categoria C3 apresenta um caminho Euleriano(aberto ou
    //fechado) se e somente se não ocorrer nenhum ou existir no máximo dois vértices com grau ímpar.
    if (grauImpar > 2 || grauImpar == 1)
    {
        std::cout << "Grafo com numero de vertices de grau impar, impar("<<grauImpar <<") \n";
        return false;
    }

    if (somaGrau != n * 2)//a soma dos graus dos vértices em um grafo é igual a duas vezes o número de arestas
    {
        std::cout << "Grafo com a soma dos graus dos vertices diferente de 2 vezes o numero de arestas"
            " soma dos Graus: " << somaGrau << "n arestas:" << m << " \n";
        return false;
    }
    return true;
}

void TGrafo::EulerianCycleStart()
{
    float** originalGraph = new float* [n];//copiando a matrix
    for (int i = 0; i < n; ++i)
    {
        originalGraph[i] = new float[n];
        for (int j = 0; j < n; ++j)
            originalGraph[i][j] = adj[i][j];
    }

    int originalM = this->m, totalEdges, start, end;//setando variaveis utilizadas para checagem de ciclo válido
    bool foundECycle = false;

    for (int i = 0; i < this->n; i++)//para cada vertice, ele tenta achar um ciclo válido
    {
        start = i;//marca o inicio
        totalEdges = 0;//marca quantos vetices foram percorridos
        this->EulerianCycle(0,totalEdges,end);//tenta achar ciclo para a variável atual
        if (totalEdges == originalM && start == end)//se TODOS os verices foram percorridos E se o inicia for igual ao fim(ciclo)
        {
            std::cout << "\nCAMINHO ACEITO, ESTE CAMINHO EH UM CICLO EULERIANO VALIDO\n";
            foundECycle = true;
            break;//sai do for pois já achou um ciclo
        }
    }

    if(!foundECycle)//printa caso não foram achados ciclos válidos
        std::cout << "NAO FOI POSSIVEL ENCONTRAR UM CAMINHO EULERIANO VALIDO";

    this->adj = originalGraph;//restaurando a matriz
    this->m = originalM;
}
void TGrafo::EulerianCycle(int v,int &totalEdges, int& last)
{
    for (int i = 0; i < n; ++i)//a apartir do v inicial
    {
        if (adj[v][i] != INT_MAX)
        {
            std::cout << v << " -> " << i << std::endl;
            removeA(v, i);//remove a aresta existente
            totalEdges++;//conta mais uma nas removidas
            EulerianCycle(i, totalEdges, last);//recursivamente tenta chegar até o fim.
        }
    }
    last = v;//ultimo ponto encontrado na recursão.
}

void TGrafo::dijkstra(int src)
{
    std::vector<int> dist(this->n, INT_MAX); // Distância da origem a i
    std::vector<bool> F(this->n, false); // Se o vértice i está fechado
    std::vector<int> rot(this->n, -1); // Predecessor de i no caminho mais curto

    dist[src] = 0; // Distância do vértice de origem para si mesmo é 0

    for (int count = 0; count < this->n - 1; count++)
    {
        // Encontrar o vértice mais próximo (min_index) do conjunto de vértices ainda não processados
        int min = INT_MAX, min_index = 0;

        for (int v = 0; v < this->n; v++)
            if (F[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;

        int u = min_index;
        F[u] = true; // Marca o vértice como processado
        // Atualizar a distância dos vértices adjacentes do vértice selecionado
        for (int v = 0; v < this->n; v++)
            // Atualizar dist[v] apenas se não estiver em F, houver uma aresta de
            // u a v, e o peso total do caminho de src a v através de u é menor
            // que o valor atual de dist[v]
            if (!F[v] && adj[u][v] && dist[u] != INT_MAX
                && dist[u] + adj[u][v] < dist[v])
            {
                dist[v] = dist[u] + adj[u][v];
                rot[v] = u;
            }
    }
    // Imprimir as distâncias e caminhos
    std::cout << "\nVertice\t|Menor Distancia da Origem\t|Caminho" << std::endl;
    for (int i = 0; i < this->n; i++)
    {
        std::cout << i + 1 << "\t|" << dist[i] << "\t\t\t\t|";
        PrintRota(rot, i);
        std::cout << "\n";
    }
}

void TGrafo::PrintRota(std::vector<int>& rot, int j)
{
    // Base case: se j é a origem
    if (rot[j] == -1)
    {
        std::cout << j + 1;
        return;
    }
    PrintRota(rot, rot[j]);
    std::cout << " -> " << j + 1;
}

bool TGrafo::bfs(int** rGraph, int s, int t, int parent[]) 
{
    bool visited[60];
    memset(visited, 0, sizeof(visited));

    std::queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) 
        {
            if (visited[v] == false && rGraph[u][v] > 0) 
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

int TGrafo::FordFulkerson(int s, int t) 
{
    int** rGraph = new int* [n];
    for (int i = 0; i < n; i++)
        rGraph[i] = new int[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rGraph[i][j] = adj[i][j];

    int parent[60];
    int max_flow = 0;

    // Enquanto houver um caminho de aumento do vértice de origem para o vértice de destino
    while (bfs(rGraph, s, t, parent)) 
    {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) 
        {
            int u = parent[v];
            path_flow = std::min(path_flow, rGraph[u][v]);
        }

        // Atualiza as capacidades residuais do caminho encontrado
        for (int v = t; v != s; v = parent[v]) 
        {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Adiciona o fluxo de caminho ao fluxo máximo
        max_flow += path_flow;

        // Imprime o caminho encontrado
        std::cout << "Caminho encontrado:";
        for (int v = t; v != s; v = parent[v]) 
        {
            int u = parent[v];
            std::cout << " " << u +1 << "->" << v + 1;
        }
        std::cout << std::endl;

        // Imprime o fluxo máximo atual
        std::cout << "Fluxo maximo atual: " << max_flow << std::endl;
    }

    // Libera a memória alocada para a matriz residual
    for (int i = 0; i < n; i++)
        delete[] rGraph[i];
    delete[] rGraph;

    return max_flow;
}