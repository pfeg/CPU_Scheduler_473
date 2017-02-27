// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"
#include <list>
#include <iostream>
#include <time.h>

using namespace std;


int main(int argc, char* argv[])
{
	
  int numberOfCPUs = 3;
  
  MyScheduler scheduler = MyScheduler(STRFwP, numberOfCPUs);

	srand(time(NULL));

	
  int totalThreads = 20;
  
  
  
  int priority = 3;
  
  
  for (int i = 0; i < totalThreads; i++)
  {
    scheduler.CreateThread(i, (rand() % 20) + 1, priority, i);
  }
//  for (int i = 0; i < totalThreads; i++)
//	{
//		scheduler.CreateThread(i + (rand() % numberOfCPUs + 1), 100, numberOfCPUs, 7);
//	}

	scheduler.PrintThreads("Threads", scheduler.Threads);

	scheduler.Go();



	return 0;
}


