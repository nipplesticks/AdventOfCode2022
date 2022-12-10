#include "Day10.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>
#include <deque>

const std::string path = "src/Day10/";

int gRegister = 1;
constexpr int ADD_X_CYCLES = 2;
int buffer[ADD_X_CYCLES];
int cycleCounter = 0;
int sumOfSignal = 0;

std::string CRT;

int CRT_WIDTH = 40;
int CRT_HEIGHT = 6;

void IterateCycle()
{
  int spritePosition = gRegister;
  int pixelPos = cycleCounter++ % CRT_WIDTH;
  
  if (spritePosition - 1 == pixelPos || spritePosition == pixelPos || spritePosition + 1 == pixelPos)
    CRT += "#";
  else
    CRT += " ";
}

void Day10::Run()
{
  memset(buffer, 0, sizeof(int) * ADD_X_CYCLES);
  std::ifstream input(path + "Input.txt");
  
  if (input)
  {
    std::string line = "";
    while (std::getline(input, line))
    {
      IterateCycle();

      std::stringstream ss(line);
      std::string command;
      ss >> command;
      if (command == "addx")
      {
        int value;
        ss >> value;
        IterateCycle();
        gRegister += value;
      }
    }

    input.close();

    std::ofstream output(path + "Output.txt");
    if (output)
    {
      for (int y = 0; y < CRT_HEIGHT; y++)
      {
        for (int x = 0; x < CRT_WIDTH; x++)
        {
          output << CRT[x + y * CRT_WIDTH];
          std::cout << CRT[x + y * CRT_WIDTH];
        }
        output << std::endl;
        std::cout << std::endl;
      }
      output.close();
    }
  }
}
