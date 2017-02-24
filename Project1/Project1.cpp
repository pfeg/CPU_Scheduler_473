// Project1.cpp : Defines the entry point for the console application.
//

#include "myscheduler.h"
#include <list>
#include <iostream>
#include <time.h>

using namespace std;

void PrintThreads(list<ThreadsList*> threadList);

int main(int argc, char* argv[])
{
	MyScheduler scheduler = MyScheduler(FCFS, 1);

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		scheduler.CreateThread(rand() % 100, 100, 1, 7);
	}

	PrintThreads(scheduler.Threads);

	scheduler.Go();

	PrintThreads(scheduler.ReadyQueue);

	return 0;
}

void PrintThreads(list<ThreadsList*> threadList)
{
	list<ThreadsList*>::iterator iter;
	iter = threadList.begin();

	while (iter != threadList.end())
	{
		cout << "[" << (*iter)->ThreadInfo.tid << "|" << (*iter)->ThreadInfo.priority << "|" << (*iter)->ThreadInfo.arriving_time << "|" << (*iter)->ThreadInfo.remaining_time << "]->" << endl;
		iter++;
	}

	cout << endl << endl;
}

