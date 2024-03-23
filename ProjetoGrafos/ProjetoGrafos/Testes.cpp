#include "Testes.h"
#include "TGrafo.h"
#include <fstream>
std::string Exaux(int type)
{
    switch (type)
    {
    case 0:
        return "C0!\n";
    case 1:
        return "C1!\n";
    case 2:
        return "C2!\n";
    case 3:
        return "C3!\n";
    default:
        break;
    }
}
void PrintType2(int type)
{
    switch (type)
    {
    case 1:
        std::cout << "1 – grafo nao orientado com peso no vertice";
        break;
    case 2:
        std::cout << "2 – grafo nao orientado com peso na aresta";
        break;
    case 3:
        std::cout << "3 – grafo nao orientado com peso nos vertices e arestas";
        break;
    case 4:
        std::cout << "4 – grafo orientado sem peso";
        break;
    case 5:
        std::cout << "5 – grafo orientado com peso no vertice";
        break;
    case 6:
        std::cout << "6 - grafo orientado com peso na aresta";
        break;
    case 7:
        std::cout << "7 – grafo orientado com peso nos vértices e arestas";
        break;
    }
}

void PrintTxt2(std::string filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }

    int type, id = 0;
    file >> type;//le primeira linha.
    std::cout << "\nTipo do Grafo:\n";
    PrintType2(type);std::cout << "\n";
    int a, v = 0;

    file >> v;// le a segunda linha == vertices
    std::cout << "\nnumero de vertices: " << v << "\n";
    std::cout << "ids dos vertices: \n";
    for (int i = 0; i < v; i++)
    {
        id = 0;
        file >> id;
        if (i != v - 1)
            std::cout << id << ", ";
        else
            std::cout << id << ".";
    }

    file >> a;//le o num de arestas

    std::cout << "\n\nnumero de Arestas: " << a << "\n";
    std::cout << "conexoes das Arestas: (formato origem->destino|peso)\n";

    int x, y, z;
    for (int j = 0; j < a; j++)
    {
        file >> x >> y >> z;
        std::cout << x << "->" << y << "|Peso: " << z << "\n";
    }
    file.close();
}

void ExecutarTestes()
{
    std::cout << "Teste ex 1:";
    std::cout << "Lendo o arquivo e construindo matriz...\n";
    TGrafo grafo = grafo.FileToGraph("./Teste1.txt");
    std::cout << "\nmatriz 1 obtida a partir de arquivo\n";
    grafo.show();
    std::cout << "\n_________________________________________________________________________________\n";
    std::cout << "Lendo o arquivo e construindo matriz...\n";
    TGrafo grafo2 = grafo2.FileToGraph("./Teste2.txt");
    std::cout << "\nmatriz 2 obtida a partir de arquivo\n";
    grafo2.show();
    std::cout << "\n_________________________________________________________________________________\n";
    TGrafo grafo3(3);
    grafo3.insereA(0, 1, 1);
    grafo3.insereA(0, 2, 2);
    grafo3.insereA(1, 2, 5);
    grafo3.insereA(2, 1, 3);

    TGrafo grafo4(4);
    grafo4.insereA(0, 1, 5);
    grafo4.insereA(0, 3, 3);
    grafo4.insereA(2, 1, 2);
    grafo4.insereA(3, 2, 3);
    grafo4.insereA(3, 4, 1);

    grafo3.MatrixToFile("./Teste3.txt");
    grafo4.MatrixToFile("./Teste4.txt");
    std::cout << "\n_________________________________________________________________________________\n";
    std::cout << "\nGrafo 1 original: \n";
    grafo.show();
    grafo.InsertVertix();
    std::cout << "\nGrafo 1 apos insercao: \n";
    grafo.show();
    std::cout << "\nGrafo 2 original: \n";
    grafo2.show();
    grafo2.InsertVertix();
    std::cout << "\nGrafo 2 apos insercao: \n";
    grafo2.show();
    std::cout << "\n_________________________________________________________________________________\n";

    std::cout << "\nGrafo 1 atual: \n";
    grafo.show();
    grafo.insereA(1, 6, 3);
    std::cout << "\nGrafo 1 apos insercao: \n";
    grafo.show();

    std::cout << "\nGrafo 2 atual: \n";
    grafo2.show();
    grafo2.insereA(2, 4, 5);
    std::cout << "\nGrafo 2 apos insercao: \n";
    grafo2.show();
    std::cout << "\n_________________________________________________________________________________\n";

    std::cout << "\nGrafo 3 atual: \n";
    grafo3.show();
    grafo3.RemoveV(0);
    std::cout << "\nGrafo 3 apos insercao: \n";
    grafo3.show();

    std::cout << "\nGrafo 4 atual: \n";
    grafo4.show();
    grafo4.RemoveV(1);
    std::cout << "\nGrafo 4 apos insercao: \n";
    grafo4.show();
    std::cout << "\n_________________________________________________________________________________\n";

    std::cout << "\nGrafo 1 atual: \n";
    grafo.show();
    grafo.removeA(1,6);
    std::cout << "\nGrafo 1 apos insercao: \n";
    grafo.show();

    std::cout << "\nGrafo 2 atual: \n";
    grafo2.show();
    grafo2.removeA(0,1);
    std::cout << "\nGrafo 2 apos insercao: \n";
    grafo2.show();

    std::cout << "\n_________________________________________________________________________________\n";
    std::cout << "\nprint dos 4 arquivos:\n";
    std::cout << "\narquivo 1:\n";
    PrintTxt2("./teste1.txt");
    std::cout << "\narquivo 2:\n";
    PrintTxt2("./teste2.txt");
    std::cout << "\narquivo 3:\n";
    PrintTxt2("./teste3.txt");
    std::cout << "\narquivo 4:\n";
    PrintTxt2("./teste4.txt");

    std::cout << "\n_________________________________________________________________________________\n";

    std::cout << "\nMostrando Grafos:\n";
    std::cout << "\nGrafo 1:\n";
    grafo.show();
    std::cout << "\nGrafo 2:\n";
    grafo2.show();
    std::cout << "\n_________________________________________________________________________________\n";

    TGrafo grafoC1(4);
    grafoC1.insereA(1, 0, 1);
    grafoC1.insereA(2, 0, 1);
    grafoC1.insereA(2, 3, 1);
    grafoC1.insereA(2, 1, 1);
    int c1Result = grafoC1.graphCategory();
    std::cout << "\nGrafo imputado\n";
    grafoC1.show();
    std::cout << "\n(c1)Este Grafo eh do tipo : " << Exaux(c1Result);
    TGrafo grafoReduzido = grafoC1.GetReducedMatrix();
    grafoReduzido.show();
    std::cout << "________________________________\n";

    TGrafo grafoC3(4);
    grafoC3.insereA(0, 2, 1);
    grafoC3.insereA(1, 0, 1);
    grafoC3.insereA(2, 1, 1);
    grafoC3.insereA(2, 3, 1);
    grafoC3.insereA(3, 0, 1);
    int c3Result = grafoC3.graphCategory();
    std::cout << "\nGrafo imputado\n";
    grafoC3.show();
    std::cout << "\n(c3)Este Grafo eh do tipo : " << Exaux(c3Result);
    TGrafo grafoReduzido2 = grafoC3.GetReducedMatrix();
    grafoReduzido2.show();
    std::cout << "\n_________________________________________________________________________________\n";
}
