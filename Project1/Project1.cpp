//

#include "myscheduler.h"
#include <list>
#include <time.h>

int main(int argc, char* argv[])
{
  int numberOfCPUs = 5;
  Policy policy = FCFS;
  string policyString = "FCFS";
  
  MyScheduler ms = MyScheduler(policy, numberOfCPUs);
  
	srand(time(NULL));
  
  int totalThreads = 60;
  
  cout << "Testbench via Adam Geiger\n\n";
  
  cout << "\tUsing " << policyString << ", " << numberOfCPUs << " CPUs, random remaining times and arrivial time and priorities\n";
  
  for (int i = 0; i < totalThreads; i++)
	{
		ms.CreateThread(i + rand() % 5, (rand() % 40) + 1, rand() % 20, i);
	}

	ms.PrintThreads("Threads", ms.Threads);

	ms.Go();
  
	return 0;
}


