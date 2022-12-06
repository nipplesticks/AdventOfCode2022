#include "Day5.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>

void Day5::Run()
{
  std::ifstream input("src/Day4/Input.txt");

  if (input)
  {
    std::string line = "";

    while (std::getline(input, line))
    {
    
    }

    std::ofstream output("src/Day4/Output.txt");

    if (output)
    {
    //  output << totalOverlappingSections;
      output.close();
    }

    //std::cout << totalOverlappingSections << std::endl;

    input.close();
  }
}
