#include "Day5.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>
#include <deque>

using Box = char;
using Stack = std::deque<Box>;

Stack stacks[9];

void PrintStacks()
{
  int maxSize = 0;
  for (int i = 0; i < 9; i++)
    if (stacks[i].size() > maxSize) maxSize = stacks[i].size();

  for (int i = maxSize - 1; i >= 0; i--)
  {
    for (int j = 0; j < 9; j++)
    {
      if (stacks[j].size() > i)
      {
        std::cout << stacks[j][i] << " ";
      }
      else
      {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }
  for (int i = 0; i < 9; i++)
  {
    std::cout << i + 1 << " ";
  }
  std::cout << std::endl;
}

void Day5::Run()
{
  std::ifstream input("src/Day5/Input.txt");

  if (input)
  {
    std::string line = "";

    while (std::getline(input, line))
    {
      // If move command
      if (line.find("move") < line.length())
      {
        PrintStacks();
        std::cout << line << std::endl;

        int numBoxesToBeMoved = 0;
        int fromIdx = 0;
        int toIdx = 0;

        std::stringstream ss(line);
        std::string dummy;

        ss >> dummy >> numBoxesToBeMoved >> dummy >> fromIdx >> dummy >> toIdx;
        fromIdx--;
        toIdx--;

        for (int i = numBoxesToBeMoved; i > 0; i--)
        {
          Box b = stacks[fromIdx].back();
          stacks[fromIdx].pop_back();
          stacks[toIdx].push_back(b);
        }

        std::reverse(stacks[toIdx].begin() + (stacks[toIdx].size() - numBoxesToBeMoved), stacks[toIdx].end());

      }
      else // fillStack
      {
        int counter = 0;
        for (int i = 0; i < line.length(); i += 4)
        {
          Box b = line[i + 1];

          if (b >= 'A' && b <= 'Z')
          {
            stacks[counter].push_front(b);
          }
          counter++;
        }
      }
    }

    PrintStacks();

    std::string topLevelBoxes = "";
    for (int i = 0; i < 9; i++)
    {
      if (stacks[i].empty())
        continue;
      topLevelBoxes += stacks[i].back();
    }

    std::ofstream output("src/Day5/Output.txt");


    if (output)
    {
      output << topLevelBoxes;
      output.close();
    }

    std::cout << topLevelBoxes << std::endl;

    input.close();
  }
}
