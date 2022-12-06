#include "Day3.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>

using Item = char;
using Priority = unsigned int;
using ItemList = std::string;

struct Group
{
  std::array<ItemList, 3> rucksacks;

  ItemList GetPrioritySum()
  {
    ItemList il = "";
    std::unordered_map<Item, bool> hash[3];
    for (int i = 0; i < 3; i++)
    {
      for (const Item& item : rucksacks[i])
        hash[i][item] = true;
    }
    for (const Item& item : rucksacks[0])
    {
      if (hash[0][item] && hash[1][item] && hash[2][item])
      {
        hash[0][item] = hash[1][item] = hash[2][item] = false;
        il += item;
      }
    }

    return il;
  }
};


void Day3::Run()
{
  std::unordered_map<Item, Priority> priorityMap;
  {
    Priority priority = 1;
    for (Item c = 'a'; c <= 'z'; c++)
    {
      priorityMap[c] = priority++;
    }
    for (Item c = 'A'; c <= 'Z'; c++)
    {
      priorityMap[c] = priority++;
    }
  }


  std::ifstream input("src/Day3/Input.txt");

  if (input)
  {
    std::string line = "";
    unsigned int sumOfPriorities = 0;
    int counter = 0;
    Group aGroup;
    while (std::getline(input, line))
    {
      aGroup.rucksacks[counter++] = line;
      if (counter == 3)
      {
        if (line == "HSrvnQzQSMDlLzBCfg")
          int asd = 123;
        ItemList il = aGroup.GetPrioritySum();

        for (auto & c : il)
          sumOfPriorities += priorityMap[c];

        counter = 0;
      }
    }

    std::ofstream output("src/Day3/Output.txt");

    if (output)
    {
      output << sumOfPriorities;
      output.close();
    }

    std::cout << sumOfPriorities << std::endl;

    input.close();
  }
}
