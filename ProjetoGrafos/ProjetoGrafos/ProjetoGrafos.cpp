
#include <iostream>
#include "TGrafo.h"


int main()
{
	TGrafo grafo = grafo.FileToGraph("./grafo.txt");
	grafo.ShowMatrixOnly();

	int option;
	int x, y, z;
	while (true)
	{
		do
		{
			std::cout << "\n****************************************************\n";
			std::cout << "*** PROJETO GRAFOS ***\n";
			std::cout << "*** Analise de interacoes no Instagram ***\n"
				<< "Digite o numero da opcao\n"
				<< "[1] Ler dados do arquivo grafo.txt e Criar Matriz de Adjacencia\n"
				<< "[2] Gravar Matriz de Adjacencia no arquivo grafo.txt\n"
				<< "[3] Inserir vértice"
				<< "[4] Inserir aresta"
				<< "[5] Remove vértice"
				<< "[6] Remove aresta"
				<< "[7] Mostrar conteúdo do arquivo"
				<< "[8] Mostrar grafo"
				<< "[9] Apresentar a conexidade do grafo e o reduzido"
				<< "[0] Encerrar a aplicação\nOption: ";
			std::cin >> option;
			std::cin.ignore();
			std::cout << '\n';

			switch (option)
			{
			case 1:
				grafo = grafo.FileToGraph("./in.txt");
				std::cout << "\nGrafo criado a partir do arquivo.\n";
				grafo.show();
				break;

			case 2:
				; 
				break;

			case 3:
				std::cout << "\n digite o vertice origem: ";
				std::cin >> x;
				std::cout << "\n digite o vertice destino: ";
				std::cin >> y;
				std::cout << "\n digite o peso da aresta: ";
				std::cin >> z;
				grafo.insereA(x,y,z); 
				break;

			case 4:
				; 
				break;

			case 5:
				; 
				break;

			case 6:
				; 
				break;

			case 7:
				; 
				break;

			case 8:
				; 
				break;

			case 9:
				; 
				break;

			}
			std::cout << '\n';
		} while (option != 0);
		return 0;
	}
	//TestEx14();
	return 0;
}