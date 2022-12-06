#include "Day1.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void Day1::Run()
{
  std::ifstream input("src/Day1/Input.txt");

  struct Elf
  {
    unsigned int ElfNumber = -1;
    unsigned int NumCalories = 0;
    bool operator<(const Elf& other)
    {
      return NumCalories < other.NumCalories;
    }
  };

  if (input)
  {
    std::string line = "";
    std::vector<Elf> elfs;
    Elf elf;
    elf.ElfNumber = 0;
    elfs.push_back(elf);

    while (std::getline(input, line))
    {
      if (line == "")
      {
        unsigned int next = elfs.back().ElfNumber + 1;
        elf.ElfNumber = next;
        elf.NumCalories = 0;
        elfs.push_back(elf);
      }
      else
      {
        elfs.back().NumCalories += std::atoi(line.c_str());
      }
    }
    std::sort(elfs.begin(), elfs.end());
    std::reverse(elfs.begin(), elfs.end());

    int food = 0;

    for (int i = 0; i < 3; i++)
    {
      food += elfs[i].NumCalories;
    }

    std::ofstream output("src/Day1/Output.txt");
    if (output)
    {
      output << food;
      output.close();
    }

    input.close();
  }
}
