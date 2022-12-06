#include "Day4.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>

struct Range
{
  int start;
  int end;
  std::unordered_map<int, bool> section;

  void Apply()
  {
    for (int i = start; i <= end; i++)
      section[i] = true;
  }

  bool ContainsRange(const Range& other)
  {
    return other.start >= start && other.end <= end;
  }

  int GetOverLapping(Range& other)
  {
    for (auto& el : section)
    {
      int val = el.first;
      if (other.section[val])
        return 1;
    }


    return 0;
  }
};


void Day4::Run()
{
  std::ifstream input("src/Day4/Input.txt");

  if (input)
  {
    std::string line = "";
    int counter = 0;
    int totalOverlappingSections = 0;
    while (std::getline(input, line))
    {
      int seperator = line.find(',');
      int firstRange = line.find_first_of('-');
      int lastRange = line.find_last_of('-');
      Range a;
      a.start = std::atoi(line.substr(0, firstRange).c_str());
      a.end = std::atoi(line.substr(firstRange + 1, seperator - firstRange).c_str());
      a.Apply();
      Range b;
      b.start = std::atoi(line.substr(seperator + 1, lastRange - seperator).c_str());
      b.end = std::atoi(line.substr(lastRange + 1, line.size() - lastRange).c_str());
      b.Apply();
      counter += a.ContainsRange(b) || b.ContainsRange(a);
      totalOverlappingSections += a.GetOverLapping(b);
    }

    std::ofstream output("src/Day4/Output.txt");

    if (output)
    {
      output << totalOverlappingSections;
      output.close();
    }

    std::cout << totalOverlappingSections << std::endl;

    input.close();
  }
}
