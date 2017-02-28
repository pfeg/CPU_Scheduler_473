//

#include "myscheduler.h"
#include <time.h>

double AvgFromList(list<int> data);
void CreateListOfThreads(list<ThreadDescriptorBlock*> &ThreadList, int size);
void TrialsTestBench();
void RandomTestBench();

int main(int argc, char* argv[])
{
  TrialsTestBench();
  
  
  //RandomTestBench();
  
  
  
	return 0;
}

void RandomTestBench()
{
  srand(time(NULL));
  
  
  int numberOfCPUs = 3;
  // just change the policy to try different ones.
  MyScheduler ms = MyScheduler(Policy::PBS, numberOfCPUs);
  
  ms.enable_debug = true;
  
  int totalThreads = 60;
  
  cout << "Testbench via Adam Geiger\n\n";
  
  cout << "\tUsing PBS, 5, random remaining times and arrivial time and priorities\n";
  
  int t_arriving_time;
  int t_remaining_time;
  int t_priority;
  int t_tid;
  
  for (int i = 0; i < totalThreads; i++)
  {
    t_arriving_time = i + rand() % 5;
    t_remaining_time = rand() % 40 + 1;
    t_priority = rand() % 20;
    t_tid = i;
    
    cout << "Thread Created: ";
    cout << "Arriving Time: " << t_arriving_time << " ";
    cout << "Remaining Time: " << t_remaining_time << " ";
    cout << "Priority: " << t_priority << " ";
    cout << "tid: " << t_tid << endl;
    
    ms.CreateThread(t_arriving_time, t_remaining_time, t_priority, t_tid);
  }
  
  ms.Go();
}

void TrialsTestBench()
{
  int numberOfCPUs = 5;
  Policy policy = FCFS;
  string policyString;
  
  
  
  list<int> FCFSResults;
  list<int> STRFwPResults;
  list<int> STRFwoPResults;
  list<int> PSwPResults;
  
  list<int> Results[4];
  
  Results[0] = FCFSResults;
  Results[1] = STRFwPResults;
  Results[2] = STRFwoPResults;
  Results[3] = PSwPResults;
  
  list<ThreadDescriptorBlock*> all_threads;
  
  srand(time(NULL));
  
  int totalThreads = 60;
  
  cout << "Testbench via Adam Geiger\n\n";
  
  //  cout << "\tUsing " << policyString << ", " << numberOfCPUs << " CPUs, random remaining times and arrivial time and priorities\n";
  
  int trials = 20;
  
  for (int trial_i = 0; trial_i < trials; trial_i++)
  {
    CreateListOfThreads(all_threads, totalThreads);
    for (int policy_i = 0; policy_i < 4; policy_i++)
    {
      policy = (Policy)policy_i;
      cout << "-----------" << endl;
      cout << "policy: " << policy_i << " trial: " << trial_i << endl;
      cout << "-----------" << endl;
      
      MyScheduler ms = MyScheduler(policy, numberOfCPUs);
      ms.enable_debug = false;
      
      list<ThreadDescriptorBlock*>::iterator threadIter;
      threadIter = all_threads.begin();
      while(threadIter != all_threads.end())
      {
        
        ms.CreateThread((*threadIter)->arriving_time, (*threadIter)->remaining_time, (*threadIter)->priority, (*threadIter)->tid);
        threadIter++;
      }
      
      ms.PrintThreads("Threads", ms.Threads);
      
      ms.Go();
      
      Results[policy_i].push_front(ms.getTimer());
    }
    all_threads.clear();
  }
  
  cout << "-----------" << endl;
  cout << "AVG TIME" << endl;
  cout << "-----------" << endl;
  for (int policy_i = 0; policy_i < 4; policy_i++)
  {
    cout << "\t "
    << policy_i << " "
    << AvgFromList(Results[policy_i]) << endl;
    
  }
  
  cout << endl;
}



double AvgFromList(list<int> data)
{
  int sum = 0;
  list<int>::iterator dataInter;
  dataInter = data.begin();
  while (dataInter != data.end())
  {
    sum += (*dataInter);
    dataInter++;
  }
  return sum / data.size();
}

void CreateListOfThreads(list<ThreadDescriptorBlock*> &ThreadList, int size)
{
  for (int thread_i = 0; thread_i < size; thread_i++)
  {
    ThreadDescriptorBlock *temp = new ThreadDescriptorBlock();
    temp->tid = thread_i;
    temp->arriving_time = thread_i + rand() % 5;
    temp->remaining_time = rand() % 40 + 1;
    temp->priority = rand() % 20;
    ThreadList.push_back(temp);
  }
  
}



