#include "BBLogStream.h"
#include <iostream>
#include "streamprocessor/ExampleSource.h"
#include "streamprocessor/StreamTarget.h"
#include "streamprocessor/nodes/Arithmetic.h"

int main()
{
	/*
	BBLogStream ls("LOG00068.TXT");
	ls.StartNextLog();
	//int rollgyroid = ls.GetFieldID("gyroADC[0]");
	//int rollrcid = ls.GetFieldID("rcCommand[0]");
	//for(int i = 0; i < 2500; i++)
	while(ls.NextStep())
	{
		//ls.NextStep();
		for(int j = 0; j < 18; j++)
			std::cout << ls.GetValue(j) << ",";
		std::cout << "0\n";
		//std::cout << ls.GetInt(0) << "," << ls.GetInt(1) << "," << ls.GetInt(rollgyroid) << "," << ls.GetInt(rollrcid) << "\n";
	}
	*/

	ExampleSource src;
	StreamTarget tgt(3);
	Arithmetic a;
	a.SetProperty("operator", "*");
	Pipe p1(&src, 0, &tgt, 0);
	Pipe p2(&src, 1, &tgt, 1);
	Pipe p3(&src, 0, &a, 0);
	Pipe p4(&src, 1, &a, 1);
	Pipe p5(&a, 0, &tgt, 2);
	while(src.NextStep());
	return 0;
}
