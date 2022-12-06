#include "iDay.h"
#include "Day1/Day1.h"
#include "Day2/Day2.h"
#include "Day3/Day3.h"


void iDay::RunDay(unsigned int dayNumber)
{
	iDay* day_p = nullptr;
	switch (dayNumber)
	{
	case 1:
		day_p = new Day1();
		break;
	case 2:
		day_p = new Day2();
		break;
	case 3:
		day_p = new Day3();
		break;
	default:
		break;
	}

	if (day_p)
	{
		day_p->Run();
		delete day_p;
	}
}
