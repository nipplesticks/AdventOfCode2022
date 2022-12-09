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
#include <algorithm>
#include <math.h>

constexpr bool disablePrint = true;
const std::string path = "src/Day9/";
void print();

struct Tile
{
  int numTVisits = 0;
  int numHVisits = 0;
};


using Grid = std::vector<Tile>;
constexpr int GRID_SIZE = 512;
constexpr int ROPE_LENGTH = 9;
constexpr int TAIL_INDEX = ROPE_LENGTH - 1;

struct Marker
{
  int x = GRID_SIZE / 2;
  int y = GRID_SIZE / 2;
};
Grid grid = Grid(GRID_SIZE * GRID_SIZE);
Marker T[ROPE_LENGTH];
Marker H;

int clamp(int v, int _min, int _max)
{
  return std::max(std::min(v, _max), _min);
}

void moveTail(const Marker& before, int index)
{
  if (index == ROPE_LENGTH)
    return;
  if (!(abs(before.x - T[index].x) <= 1 && abs(before.y - T[index].y) <= 1))
  {
    if (before.x == T[index].x) // Same Col -> Move in Y
    {
      int d = before.y - T[index].y;
      d = clamp(d, -1, 1);
      T[index].y += d;
    }
    else if (before.y == T[index].y) // Same Row -> Move in X
    {
      int d = before.x - T[index].x;
      d = clamp(d, -1, 1);
      T[index].x += d;
    }
    else // Not in same row nor same Col -> Move in Y and X
    {
      int dx = before.x - T[index].x;
      int dy = before.y - T[index].y;

      dx = clamp(dx, -1, 1);
      dy = clamp(dy, -1, 1);

      T[index].x += dx;
      T[index].y += dy;
    }

    moveTail(T[index], index + 1);

    if (index == TAIL_INDEX)
      grid[T[index].x + T[index].y * GRID_SIZE].numTVisits++;
  }
}

void move(char direction, int steps)
{
  //std::cout << direction << " " << steps << std::endl;
  if (direction == 'L')
  {
    for (int i = 0; i < steps; i++)
    {
      H.x--;
      grid[H.x + H.y * GRID_SIZE].numHVisits++;
      moveTail(H, 0);
      print();
    }
  }
  else if (direction == 'R')
  {
    for (int i = 0; i < steps; i++)
    {
      H.x++;
      grid[H.x + H.y * GRID_SIZE].numHVisits++;
      moveTail(H, 0);
      print();
    }
  }
  else if (direction == 'D')
  {
    for (int i = 0; i < steps; i++)
    {
      H.y++;
      grid[H.x + H.y * GRID_SIZE].numHVisits++;
      moveTail(H, 0);
      print();
    }
  }
  else
  {
    for (int i = 0; i < steps; i++)
    {
      H.y--;
      grid[H.x + H.y * GRID_SIZE].numHVisits++;
      moveTail(H, 0);
      print();
    }
  }
  //std::cout << "\n===\n";
}

int startIndex = T[TAIL_INDEX].x + T[TAIL_INDEX].y * GRID_SIZE;

void print()
{
  if (disablePrint)
    return;

  for (int y = 0; y < GRID_SIZE; y++)
  {
    for (int x = 0; x < GRID_SIZE; x++)
    {
      bool found = false;
      int idx = x + y * GRID_SIZE;
      if (idx == (H.x + H.y * GRID_SIZE))
      {
        std::cout << "H ";
        found = true;
      }
      else
      {
        for (int i = 0; i < ROPE_LENGTH; i++)
        {
          if (idx == (T[i].x + T[i].y * GRID_SIZE))
          {
            std::cout << i + 1 << " ";
            found = true;
            break;
          }
        }
      }
      if (!found)
      {
        if (idx == startIndex)
        {
          std::cout << "s ";
        }
        else
        {
          std::cout << ". ";
        }
      }
    }
    std::cout << "\n";
  }
  std::cout << "===\n";
}

void Day9::Run()
{
  std::ifstream input(path + "Input.txt");
  for (int i = 0; i < ROPE_LENGTH; i++)
    T[i] = Marker();

  grid[T[TAIL_INDEX].x + T[TAIL_INDEX].y * GRID_SIZE].numTVisits++;
  grid[H.x + H.y * GRID_SIZE].numHVisits++;

  if (input)
  {
    std::string line = "";
    while (std::getline(input, line))
    {
      char dir;
      int steps;
      std::stringstream ss(line);
      ss >> dir >> steps;
      move(dir, steps);
    }

    int visitCounter = 0;
    for (auto& t : grid)
      visitCounter += t.numTVisits > 0;

    std::ofstream output(path + "Output.txt");
    if (output)
    {
      output << visitCounter;
      output.close();
    }

    std::cout << visitCounter << std::endl;

    input.close();
  }
}
