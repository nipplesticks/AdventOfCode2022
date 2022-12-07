#include "Day6.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>
#include <deque>

void Day6::Run()
{
  std::ifstream input("src/Day6/Input.txt");

  if (input)
  {
    std::string line = "";

    int sqCount = 0;

    constexpr int uniqueChar = 14;

    while (std::getline(input, line))
    {
      int sqStart = 0;
      for (int sqEnd = uniqueChar; sqEnd < line.size(); sqEnd++, sqStart++)
      {
        std::unordered_map<char, bool> sqMap;
        for (int s = sqStart; s < sqEnd; s++)
        {
          sqMap[line[s]] = true;
        }

        if (sqMap.size() == uniqueChar)
        {
          sqCount = sqEnd;
          break;
        }
      }
    }

    std::ofstream output("src/Day6/Output.txt");


    if (output)
    {
      output << sqCount;
      output.close();
    }

    std::cout << sqCount << std::endl;

    input.close();
  }
}
