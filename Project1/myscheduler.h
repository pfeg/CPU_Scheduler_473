
// Group Members: Adam Geiger, Keegan Killen, Thomas Phegley

#pragma once
//myschedule.h
#include "scheduler.h"
#include <list>
#include <string>

class MyScheduler: public Scheduler {
public:
	MyScheduler(Policy p, unsigned int n) : Scheduler(p, n) {enable_debug = false;}
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
  
  void PrintTimer();
  
  const int getTimer();
  
  bool enable_debug;
  
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
  
};
