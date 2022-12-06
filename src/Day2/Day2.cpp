#include "Day2.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>

enum Shape
{
  Rock = 1,
  Paper = 2,
  Scissor = 3
};
enum Condition
{
  Lose = 0,
  Draw = 3,
  Win = 6
};

static inline int GetScoreRock(Condition condition)
{
  switch (condition)
  {
  case Lose:
    return Scissor + condition;
  case Draw:
    return Rock + condition;
  case Win:
    return Paper + condition;
  }
  return -1;
}
static inline int GetScorePaper(Condition condition)
{
  switch (condition)
  {
  case Lose:
    return Rock + condition;
  case Draw:
    return Paper + condition;
  case Win:
    return Scissor + condition;
  }
  return -1;
}
static inline int GetScoreScissor(Condition condition)
{
  switch (condition)
  {
  case Lose:
    return Paper + condition;
  case Draw:
    return Scissor + condition;
  case Win:
    return Rock + condition;
  }
  return -1;
}

static inline int GetScore(Shape opponent, Condition condition)
{
  switch (opponent)
  {
  case Rock:
    return GetScoreRock(condition);
  case Paper:
    return GetScorePaper(condition);
  case Scissor:
    return GetScoreScissor(condition);
  }
  return -1;
}

void Day2::Run()
{
  std::ifstream input("src/Day2/Input.txt");


  if (input)
  {
    std::string line = "";

    int myScore = 0;

    while (std::getline(input, line))
    {
      Shape other = Scissor;
      Condition condition = Win;
      {
      /*
      * A for Rock,
      * B for Paper,
      * C for Scissors
      *
      * X means you need to lose,
      * Y means you need to end the round in a draw,
      * Z means you need to win.
      */
        std::stringstream ss(line);
        char o, y;
        ss >> o >> y;
        if (o == 'A')
          other = Rock;
        else if (o == 'B')
          other = Paper;

        if (y == 'X')
          condition = Lose;
        else if (y == 'Y')
          condition = Draw;
      }

      myScore += GetScore(other, condition);
    }

    std::ofstream output("src/Day2/Output.txt");

    if (output)
    {
      output << myScore;
      output.close();
    }

    std::cout << myScore << std::endl;

    input.close();
  }
}
