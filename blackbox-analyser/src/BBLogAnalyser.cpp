#include "BBLogStream.h"
#include <iostream>

int main()
{
	BBLogStream ls("D:\\Documents\\Nicolas\\Electronic\\Dronelogs\\LOG00068.TXT");
	ls.StartNextLog();
	//int rollgyroid = ls.GetFieldID("gyroADC[0]");
	//int rollrcid = ls.GetFieldID("rcCommand[0]");
	for(int i = 0; i < 2500; i++)
	{
		ls.NextStep();
		for(int j = 0; j < 18; j++)
			std::cout << ls.GetValue(j) << ",";
		std::cout << "0\n";
		//std::cout << ls.GetInt(0) << "," << ls.GetInt(1) << "," << ls.GetInt(rollgyroid) << "," << ls.GetInt(rollrcid) << "\n";
	}
	return 0;
}
