// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"
#include <list>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
  int numberOfCPUs = 5;
  MyScheduler scheduler = MyScheduler(PBS, numberOfCPUs);
	srand(time(NULL));
  int totalThreads = 60;
  
//  for (int i = 0; i < totalThreads; i++)
//  {
//    scheduler.CreateThread(i, (rand() % 20) + 1, priority, i);
//  }
  
  for (int i = 0; i < totalThreads; i++)
	{
		scheduler.CreateThread(i + rand() % 5, rand() % 40, rand() % 20, i);
	}

	scheduler.PrintThreads("Threads", scheduler.Threads);

	scheduler.Go();
  
	return 0;
}


