#pragma once
//myschedule.h
/* Students need to define their own data structure to contain
   and access objects from 'thread class'. The 'CreateThread()' 
   function should insert the threads into the student defined
   data structure after creating them.
   They are allowed to add any additional functionality (only 
   declaration in this file, define in 'myschedule.cpp')
   which they might find helpful.*/

#include "scheduler.h"
#include <list>
#include <string>

class MyScheduler: public Scheduler {
public:
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {}
	bool Dispatch() override; //Function to implement scheduling policy and to keep a check on processed threads
	void CreateThread(int arriving_time, int remaining_time, int priority, int tid) override; //Function to create threads and insert them in student defined data structure
  
  // prints queue with name.
  //void PrintQueue(string name, list<ThreadsList*>);
  
	// a list of Threads ready to be executed.
	list<ThreadDescriptorBlock*> ReadyQueue;

	// a list of all the Threads;
	list<ThreadDescriptorBlock*> Threads;
  
  void PrintThreads(string name, list<ThreadDescriptorBlock*> threadList);
  
  void PrintCPUs(string note);
  
private:

  void InsertThreadByLeastRemainingTime(ThreadDescriptorBlock *temp, list<ThreadDescriptorBlock*> &ThreadList);
  
  // Inserts Thread into list with it's priority number is
  //  lower than all others.
  void InsertThreadByPriority(ThreadDescriptorBlock *temp, list<ThreadDescriptorBlock*> &ThreadList);
  
  void FirstComeFirstServed();
  
  // Shortest Time Remaining with Preemption.
  void ShortestTimeRemainingPreemption();
  
  // Shortest Time Remaining without Preemption.
  void ShortestTimeRemainingWithoutPreemption();
  
  // Priority Based Scheduling, with preemption
  void PrioritySchedulingWithPreemption();
  
  void PrintThreadBlock(const ThreadDescriptorBlock *ThreadBlock);
  
	//Declare additional methods(s) below if needed.
	/*
	*
	*
	*
	*
	*/
  
};
