#include <iostream>
#include <string>
#include <cstdlib>
#include "json.hpp";
#include <fstream>

using json = nlohmann::json;

int main(int argc, char *argv[]) {
  
  system("mpstat -o JSON > stat.json");

  std::ifstream stats("stat.json");
  
  if (!stats){
    std::cout<< "Failed to read" <<std::endl;
  }

  


}
