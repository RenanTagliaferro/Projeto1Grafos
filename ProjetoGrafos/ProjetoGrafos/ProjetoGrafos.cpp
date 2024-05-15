
#include <iostream>
#include "TGrafo.h"
#include <fstream>
#include "Testes.h"

std::string CategoryAux(int x)
{
	switch (x)
	{
		case 0:
			return "Desconexo!";
			break;
		case 1:
			return "Simplesmente Conexo!";
			break;
		case 2:
			return "Semi-Fortemente Conexo!";
			break;
		case 3:
			return "Fortemente Conexo!";
			break;
	}
}

void PrintType(int type)
{
	switch (type)
	{
		case 1:
			std::cout << "1 � grafo nao orientado com peso no vertice";
			break;
		case 2:
			std::cout << "2 � grafo nao orientado com peso na aresta";
			break;
		case 3:
			std::cout << "3 � grafo nao orientado com peso nos vertices e arestas";
			break;
		case 4:
			std::cout << "4 � grafo orientado sem peso";
			break;
		case 5:
			std::cout << "5 � grafo orientado com peso no vertice";
			break;
		case 6:
			std::cout << "6 - grafo orientado com peso na aresta";
			break;
		case 7:
			std::cout << "7 � grafo orientado com peso nos v�rtices e arestas";
			break;
	}
}

void PrintTxt(std::string filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Erro ao abrir o arquivo." << std::endl;
	}

	int type,id = 0;
	file >> type;//le primeira linha.
	std::cout << "\nTipo do Grafo:\n";
	PrintType(type);std::cout << "\n";
	int a, v = 0;

	file >> v;// le a segunda linha == vertices
	std::cout << "\nnumero de vertices: "<<v<<"\n";
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


int main()
{
	TGrafo grafo = grafo.FileToGraph("./grafo_original.txt");
	//grafo.ShowMatrixOnly(); //descomentar para printar matrix de adjacencia como zeros e uns.
	//ExecutarTestes(); //descomentar para executar testes 
	int option;
	int x, y, z;
	while (true)
	{
		do
		{
			x, y, z = 0;
			std::cout << "\n****************************************************\n";
			std::cout << "*** PROJETO GRAFOS ***\n";
			std::cout << "*** Analise de interacoes no Instagram ***\n"
				<<"Atencao, o programa ja gerou o grafo original a partir do arquivo txt ao iniciar!(ou seja opcao 1 ja rodada)\n"
				<< "Digite o numero da opcao\n"
				<< "[1] Ler dados do arquivo grafo.txt e Criar Matriz de Adjacencia\n"
				<< "[2] Gravar Matriz de Adjacencia no arquivo grafo.txt\n"
				<< "[3] Inserir vertice\n"
				<< "[4] Inserir aresta\n"
				<< "[5] Remove vertice\n"
				<< "[6] Remove aresta\n"
				<< "[7] Mostrar conteudo do arquivo\n"
				<< "[8] Mostrar grafo\n"
				<< "[9] Apresentar a conexidade do grafo e o grafo reduzido\n"
				<< "[10] PARTE 2 PROJETO: Grau dos vertices:\n"
				<< "[11] PARTE 2 PROJETO: Coloracao :\n"
				<< "[12] PARTE 2 PROJETO: Percurso/Grafo Euleriano :\n"
				<< "[13] PARTE 2 PROJETO: DJIKSTRA APLICADO AO GRAFO. :\n"
				<< "[14] PARTE 2 PROJETO: FORD-FULKERSON. :\n"
				<< "[0] Encerrar a aplicacao\nOption: ";
			std::cin >> option;
			std::cin.ignore();
			std::cout << '\n';
			x = grafo.graphCategory();
			std::string res = CategoryAux(x);
			TGrafo grafoReduzido(0);
			TGrafo grafoND(60);
			int maxflux;
			switch (option)
			{
				case 1:
					grafo = grafo.FileToGraph("./grafo.txt");
					std::cout << "\nGrafo criado a partir do arquivo.\n";
					grafo.show();
					break;

				case 2:
					grafo.MatrixToFile("./grafo.txt");
					std::cout << "\nGrafo novo inserido no arquivo!\n";
					break;

				case 3:
					std::cout << "\nVertice sera inserido ao fim da matriz de adjacencia\n";
					grafo.InsertVertix();
					std::cout << "\nVertice inserido com sucesso!\n";
					break;

				case 4:
					std::cout << "\n digite o vertice origem: ";
					std::cin >> x;
					std::cout << "\n digite o vertice destino: ";
					std::cin >> y;
					std::cout << "\n digite o peso da aresta: ";
					std::cin >> z;
					grafo.insereA(x, y, z); 
					break;

				case 5:
					std::cout << "\n digite o vertice a ser removido: ";
					std::cin >> x;
					grafo.RemoveV(x);
					break;

				case 6:
					std::cout << "\n digite o vertice origem: ";
					std::cin >> x;
					std::cout << "\n digite o vertice destino: ";
					std::cin >> y;
					grafo.removeA(x, y);
					break;

				case 7:
					std::cout << "\nConteudo do .txt:\n";
					PrintTxt("./grafo.txt");
					break;

				case 8:
					std::cout << "\nMatrix de adjacencia do grafo:\n";
					grafo.show();
					break;

				case 9:
					std::cout << "\nEste Grafo eh do tipo: "<<res;
					std::cout << "\nSeu Grafo reduzido em forma de matrix de adjacencia eh:\n";
					grafoReduzido = grafo.GetReducedMatrix();
					grafoReduzido.show();
					break;
				case 10:
					std::cout << "\nGRAUS DE TODOS OS VERTICES: \n\n";
					grafo.GetAllDegrees();
					break;
				case 11:
					std::cout << "\nCOLORACAO COMPLETA DO GRAFO: ";
					grafo.WelshPowell();
					break;
				case 12:
					std::cout << "Ciclo Euleriano :\n";
					if (!grafo.EulerianPossible())
					{
						std::cout << "O grafo NAO eh euleriano, mas pode ter Ciclo Valido...\n";
						std::cout << "\npressione ENTER para iniciar busca por ciclo valido.\n";
						std::getchar();
					}
					else
					{
						std::cout << "O grafo eh euleriano! encontrando Ciclo Valido.\n";
						std::cout << "\npressione ENTER para iniciar busca por ciclo valido.\n";
						std::getchar();
					}

						std::cout << "Ciclo Euleriano: \n";
						grafo.EulerianCycleCall(0);
						grafo.FileToGraph("./grafo.txt");

					break;
				case 13:
					std::cout << "\n DJIKSTRA APLICADO AO GRAFO, A PARTIR DO VERTICE 20";
					std::cout << "\nTabela de menores caminhos a partir do vertice 20 do Grafo: \n";
					grafo.dijkstra(19);
					break;
				case 14:
					std::cout << "\n FORD-FULKERSON UTILIZANDO 1 COMO ORIGEM E 60 COMO SUMIDOURO";
					int maxflux = grafo.FordFulkerson(0,59);
					std::cout << "\n\n Fluxo maximo encontrado = " << maxflux<<"\n\n";
					break;
			}
			std::cout << '\n';
		} while (option != 0);
		return 0;
	}
	//TestEx14();
	return 0;
}