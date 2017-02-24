//myschedule.cpp
/*Define all the functions in 'myschedule.h' here.*/
#include "myscheduler.h"

void MyScheduler::CreateThread(int arriving_time, int remaining_time, int priority, int tid) //Thread ID not Process ID
{
	//Function to Create Thread(s) and insert them in the student
	//defined data structure
	ThreadsList *temp = new ThreadsList();
	temp->ThreadInfo.tid = tid;
	temp->ThreadInfo.arriving_time = arriving_time;
	temp->ThreadInfo.remaining_time = remaining_time;
	temp->ThreadInfo.priority = priority = priority;

	list<ThreadsList*>::iterator iter;
	iter = Threads.begin();

	while (iter != Threads.end() && (*iter)->ThreadInfo.arriving_time < temp->ThreadInfo.arriving_time)
	{
		iter++;
	}

	Threads.insert(iter, temp);
}

bool MyScheduler::Dispatch()
{
	// Moving threads that have arrived from Threads to ReadyQueue.
	list<ThreadsList*>::iterator threadsIter;
	while (Threads.size() != 0 && Threads.front()->ThreadInfo.arriving_time <= timer)
	{
		ThreadsList* temp = Threads.front();
		ReadyQueue.push_back(temp);
		Threads.pop_front();
	}

	//Todo: Check and remove finished threads
	//Todo: Check if all the threads are finished; if so, return false
	switch(policy)
	{
		case FCFS:		//First Come First Serve

			break;
		case STRFwoP:	//Shortest Time Remaining First, without preemption

			break;
		case STRFwP:	//Shortest Time Remaining First, with preemption

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