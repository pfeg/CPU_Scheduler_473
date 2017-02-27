//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	//Function to Create Thread(s) and insert them in the student
	//defined data structure
	ThreadDescriptorBlock *temp = new ThreadDescriptorBlock();
	temp->tid = tid;
	temp->arriving_time = arriving_time;
	temp->remaining_time = remaining_time;
	temp->priority = priority = priority;

	list<ThreadDescriptorBlock*>::iterator iter;
	iter = Threads.begin();

	while (iter != Threads.end() && (*iter)->arriving_time < temp->arriving_time)
	{
		iter++;
	}

	Threads.insert(iter, temp);
}

bool MyScheduler::Dispatch()
{
	
  
  // 1. Delete any threads that are finished.
  list<ThreadDescriptorBlock*>::iterator threadIter;
  threadIter = ReadyQueue.begin();
  while (threadIter != ReadyQueue.end()) {
    
    
    // thread is done.
    if ((*threadIter)->remaining_time == 0)
    {
      //delete thread.
      ReadyQueue.erase(threadIter);
    }
    threadIter++;
  }
  
  // 3. All threads are finished.
  if (Threads.size() == 0 && ReadyQueue.size() == 0)
  {
    int null_CPUs = 0;
    for(int cpu_i = 0; cpu_i < num_cpu; cpu_i++)
    {
      if (CPUs[cpu_i] == NULL)
      {
        null_CPUs++;
      }
    }
    if (null_CPUs == num_cpu)
    {
      return false;
    }
  }
  
  // 4. execute scheduling policy.
	switch(policy)
	{
		case FCFS:		//First Come First Serve

			break;
		case STRFwoP:	//Shortest Time Remaining First, without preemption

			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption
      
      SortestTimeRemainingPreemption();
      
			break;
		case PBS:		//Priority Based Scheduling, with preemption

			break;
		default :
			cout<<"Invalid policy!";
			throw 0;
	}
	
	if (timer > 100)
		return false;

	return true;
}



void MyScheduler::FirstComeFirstServed()
{
  
}


void MyScheduler::SortestTimeRemainingPreemption()
{
  // 1. for # of CPUs
  // check for an open CPU
  // if and open CPU
  //
  
  // Moving threads that have arrived from Threads to ReadyQueue and sorting them by remaining time.
  while (Threads.size() != 0 && Threads.front()->arriving_time <= timer)
  {
    ThreadDescriptorBlock* temp = Threads.front();
    
    InsertThreadByLeastRemainingTime(temp, ReadyQueue);
//    list<ThreadDescriptorBlock*>::iterator newThreadIter;
//    newThreadIter = ReadyQueue.begin();
//    
//    while (newThreadIter != ReadyQueue.end() &&
//           temp->remaining_time <= (*newThreadIter)->remaining_time )
//    {
//      newThreadIter++;
//    }
//    ReadyQueue.insert(newThreadIter, temp);
    Threads.pop_front();
  }
  
  
  //#debug
  cout<< "Time: " << timer << endl;
  PrintThreads("ReadyQueue after threads' arrival", ReadyQueue);
  PrintCPUs("CPUs before Algorithm.");
  
  
  // true if thread swap in cpu happens;
  bool did_swap = false;
  
  
  if (ReadyQueue.size() != 0)
  {
    do {
      // CPU with a thread currently with the largest
      // reamining time compared to the other cpus.
      // -1 means no CPU has a thread with remaining time greater
      //  than some thread in the readyqueue.
      int largest_cpu_remaining_time = -1;
      for (int cpu_i = 0; cpu_i < num_cpu; cpu_i++)
      {
        // check front of ReadyQueue.
        // if its remaining time is smaller than this cpu
        //  check if this cpu's remaining time is larger
        //  than previous.
        //  save CPU index.
        //
        
        // nothing in this cpu.
        if (CPUs[cpu_i] == NULL)
        {
          largest_cpu_remaining_time = cpu_i;
          
          //exit loop
          cpu_i = num_cpu;
        }
        else if (CPUs[cpu_i]->remaining_time > ReadyQueue.front()->remaining_time)
        {
          if (largest_cpu_remaining_time == -1 ||
              CPUs[largest_cpu_remaining_time]->remaining_time < CPUs[cpu_i]->remaining_time)
          {
            largest_cpu_remaining_time = cpu_i;
          }
        }
      }
      if (largest_cpu_remaining_time != -1)
      {
        // temporarly save thread coming out of CPU.
        ThreadDescriptorBlock *temp = CPUs[largest_cpu_remaining_time];
        // save reference to this thread in this cpu.
        CPUs[largest_cpu_remaining_time] = ReadyQueue.front();
        // take thread out of readyQueue.
        ReadyQueue.pop_front();
        // put thread that was in CPU back in readyQueue.
        if (temp != NULL)
        {
          InsertThreadByLeastRemainingTime(temp, ReadyQueue);
        }
        
        
      }
      else{
        did_swap = false;
      }
    } while (did_swap);
  }
  
  
  //#debug
  PrintCPUs("CPUs after algorithm.");
  PrintThreads("ReadyQueue after after algorithm.", ReadyQueue);
}

void MyScheduler::InsertThreadByLeastRemainingTime(ThreadDescriptorBlock *temp, list<ThreadDescriptorBlock*> &ThreadList)
{
  list<ThreadDescriptorBlock*>::iterator ThreadIter;
  ThreadIter = ThreadList.begin();
  while (ThreadIter != ThreadList.end() && temp->remaining_time > (*ThreadIter)->remaining_time)
  {
    ThreadIter++;
  }
  ThreadList.insert(ThreadIter, temp);
}


void MyScheduler::PrintThreads(string name, list<ThreadDescriptorBlock*> threadList)
{
  list<ThreadDescriptorBlock*>::iterator Threaditer;
  Threaditer = threadList.begin();
  cout << "------------" << endl;
  cout << name << endl;
  cout << "------------" << endl;
  
  while (Threaditer != threadList.end())
  {
    PrintThreadBlock((*Threaditer));
    cout << endl;
    Threaditer++;
  }
  cout << endl;
}

void MyScheduler::PrintCPUs(string note)
{
  cout << "------------" << endl;
  cout << note << endl;
  cout << "------------" << endl;
  
  for (int cpu_i = 0; cpu_i < num_cpu; cpu_i++) {
    cout << "CPU " << cpu_i << ": ";
    if (CPUs[cpu_i] != NULL)
    {
      PrintThreadBlock(CPUs[cpu_i]);

    }
    else
    {
        cout << "empty";
    }
    cout << endl;
  }
}

void MyScheduler::PrintThreadBlock(const ThreadDescriptorBlock *ThreadBlock)
{
  cout << "[id:" << ThreadBlock->tid << "|pr:" << ThreadBlock->priority << "|at:" << ThreadBlock->arriving_time << "|rt:" << ThreadBlock->remaining_time << "]->";
}
