#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Relation 
{
  int source_id;
  int destination_id;
  int weight;
};

int main() 
{
  std::ifstream inFile("ResultadoWebScrapComIds.txt");
  std::ofstream outFile("in.txt");

  if (!inFile.is_open() || !outFile.is_open()) 
  {
    std::cerr << "erro de endereco de arquivo." << std::endl;
    return 1;
  }

  std::vector<std::vector<int>> relations;
  std::vector<Relation> nonZeroRelations;

  std::string line;
  int numLines = 0;

  while (std::getline(inFile, line)) 
  {
    std::istringstream iss(line);
    std::vector<int> nums;

    int id;
    char delim;
    iss >> id;//id do vertice origem
    
    while (iss >> delim >> id) 
      nums.push_back(id);//pega o peso

    relations.push_back(nums);
    numLines++;
  }

  // num de linhas n
  outFile << numLines << std::endl;

  // Writing line IDs
  for (int i = 0; i < numLines; ++i) 
    outFile << i + 1 << std::endl; // coloca o vertice 1

  // pega os pesos != 0
  int numRelations = 0;
  for (int i = 0; i < numLines; ++i) 
  {
    for (int j = 0; j < numLines; ++j) 
    {
      int weight = relations[i][j];
      if (weight != 0) 
      {
        numRelations++;
        nonZeroRelations.push_back({i + 1, j + 1, weight}); // +1 pra começar do id 1
      }
    }
  }
    // valor de "m"
    outFile << numRelations << std::endl;

    // escreve os pesos != 0
    for (const auto& relation : nonZeroRelations) 
      outFile << relation.source_id << " " << relation.destination_id << " " << relation.weight << std::endl;

    inFile.close();
    outFile.close();

    return 0;
}
