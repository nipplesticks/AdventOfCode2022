#pragma once

class iDay
{
public:
  virtual void Run() = 0;

  static void RunDay(unsigned int dayNumber);

};