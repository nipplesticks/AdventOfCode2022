#include "Day8.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <array>
#include <deque>

const std::string path = "src/Day8/";

struct Tree
{
  Tree(int h)
  {
    height = h;
  }
  int height;
  bool isVisible = false;
};

void VisibleTreesFromOutside(std::vector<Tree>& treeGrid, size_t gridSizeX, size_t gridSizeY)
{
  // Check Top->Bot
  for (int x = 0; x < gridSizeX; x++)
  {
    int prevHeight = -1;
    for (int y = 0; y < gridSizeY; y++)
    {
      int idx = x + y * gridSizeX;
      if (treeGrid[idx].height > prevHeight)
      {
        prevHeight = treeGrid[idx].height;
        treeGrid[idx].isVisible = true;
      }
    }
  }
  // Check Bot->Top
  for (int x = 0; x < gridSizeX; x++)
  {
    int prevHeight = -1;
    for (int y = gridSizeY - 1; y >= 0; y--)
    {
      int idx = x + y * gridSizeX;
      if (treeGrid[idx].height > prevHeight)
      {
        prevHeight = treeGrid[idx].height;
        treeGrid[idx].isVisible = true;
      }
    }
  }
  // Check Left->Right
  for (int y = 0; y < gridSizeY; y++)
  {
    int prevHeight = -1;
    for (int x = 0; x < gridSizeX; x++)
    {
      int idx = x + y * gridSizeX;
      if (treeGrid[idx].height > prevHeight)
      {
        prevHeight = treeGrid[idx].height;
        treeGrid[idx].isVisible = true;
      }
    }
  }
  // Check Right->Left
  for (int y = 0; y < gridSizeY; y++)
  {
    int prevHeight = -1;
    for (int x = gridSizeX - 1; x >= 0; x--)
    {
      int idx = x + y * gridSizeX;
      if (treeGrid[idx].height > prevHeight)
      {
        prevHeight = treeGrid[idx].height;
        treeGrid[idx].isVisible = true;
      }
    }
  }
}

size_t CheckAllDirections(const std::vector<Tree>& treeGrid, size_t gridSizeX, size_t gridSizeY, int _x, int _y)
{
  if (_x == 0 || _y == 0 || _x == gridSizeX - 1 || _y == gridSizeY - 1)
    return 0;
  // Check Top->Bot
  size_t topBotC = 0;
  int treeHouseHeight = treeGrid[_x + _y * gridSizeX].height;
  for (int y = _y + 1; y < gridSizeY; y++)
  {
    topBotC++;
    int idx = _x + y * gridSizeX;
    if (treeGrid[idx].height >= treeHouseHeight)
      break;
  }
  // Check Bot->Top
  size_t botTopC = 0;
  for (int y = _y - 1; y >= 0; y--)
  {
    botTopC++;
    int idx = _x + y * gridSizeX;
    if (treeGrid[idx].height >= treeHouseHeight)
      break;
  }
  // Check Left->Right
  size_t leftRightC = 0;
  for (int x = _x + 1; x < gridSizeX; x++)
  {
    leftRightC++;
    int idx = x + _y * gridSizeX;
    if (treeGrid[idx].height >= treeHouseHeight)
      break;
  }
  // Check Right->Left
  size_t rightLeftC = 0;
  for (int x = _x - 1; x >= 0; x--)
  {
    rightLeftC++;
    int idx = x + _y * gridSizeX;
    if (treeGrid[idx].height >= treeHouseHeight)
      break;
  }

  return rightLeftC * leftRightC * topBotC * botTopC;
}

size_t GetBestTreeHouseScore(const std::vector<Tree>& treeGrid, size_t gridSizeX, size_t gridSizeY)
{
  size_t bestScore = 0;
  for (int y = 0; y < gridSizeY; y++)
  {
    for (int x = 0; x < gridSizeX; x++)
    {
      if (x > 0 && y > 0)
        int asd = 123;
      size_t tempScore = CheckAllDirections(treeGrid, gridSizeX, gridSizeY, x, y);
      if (tempScore > bestScore)
        bestScore = tempScore;
    }
  }
  return bestScore;
}


void Day8::Run()
{
  size_t gridSizeX = 0;
  size_t gridSizeY = 0;
  std::vector<Tree> treeGrid;
  std::ifstream input(path + "Input.txt");

  if (input)
  {
    std::string line = "";
    while (std::getline(input, line))
    {
      gridSizeX = line.size();
      for (const auto& t : line)
        treeGrid.push_back(t - '0');
      gridSizeY++;
    }
    input.close();

    VisibleTreesFromOutside(treeGrid, gridSizeX, gridSizeY);
    int vTrees = 0;
    for (auto& tree : treeGrid)
    {
      vTrees += tree.isVisible;
    }

    size_t bestTreeHouseScore = GetBestTreeHouseScore(treeGrid, gridSizeX, gridSizeY);

    std::ofstream output(path + "Output.txt");
    if (output)
    {
      output << bestTreeHouseScore;
      output.close();
    }

    std::cout << "Visible trees from outside the grid: " << vTrees << std::endl;
    std::cout << "Best Tree House score: " << bestTreeHouseScore << std::endl;
  }
}
