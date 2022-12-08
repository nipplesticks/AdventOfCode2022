#include "Day9.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>
#include <deque>

const std::string path = "src/Day9/";

void Day9::Run()
{
  std::ifstream input(path + "Input.txt");

  if (input)
  {
    std::string line = "";
    while (std::getline(input, line))
    {
      
    }

    std::ofstream output(path + "Output.txt");
    if (output)
    {
      //output << ;
      output.close();
    }

    //std::cout <<  << std::endl;

    input.close();
  }
}
