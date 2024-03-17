
#include <iostream>
#include "TGrafo.h"

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

int main()
{
	TGrafo grafo = grafo.FileToGraph("./grafo_original.txt");
	//grafo.ShowMatrixOnly();
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
				<< "[0] Encerrar a aplicacao\nOption: ";
			std::cin >> option;
			std::cin.ignore();
			std::cout << '\n';

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
				// Permite inserir novos vértices juntamente com seus rótulos e peso (se for o caso).
				; 
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
				//Mostra o conteúdo atual do arquivo grafo.txt, ou seja, tipo do grafo, vértices e arestas em
				//um formato visualmente compreensivo e atraente;;
				break;

			case 8:
				std::cout << "\nMatrix de adjacencia do grafo:\n";
				grafo.show();
				break;

			case 9:
				x = grafo.graphCategory();
				std::string res = CategoryAux(x);
				std::cout << "\nEste Grafo eh do tipo: "<<res;
				std::cout << "\nSeu Grafo reduzido em forma de matrix de adjacencia eh:\n";
				TGrafo grafoReduzido = grafo.GetReducedMatrix();
				grafoReduzido.show();

				break;
				
			}
			std::cout << '\n';
		} while (option != 0);
		return 0;
	}
	//TestEx14();
	return 0;
}