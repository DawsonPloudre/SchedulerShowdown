#include "schedulers.h"

//Round Robin scheduler implementation. In general, this function maintains a double ended queue
//of processes that are candidates for scheduling (the ready variable) and always schedules
//the first process on that list, if available (i.e., if the list has members)
int RoundRobin(const int& curTime, const vector<Process>& procList, const int& timeQuantum)
{
    static int timeToNextSched = timeQuantum;  //keeps track of when we should actually schedule a new process
    static deque<int> ready;  //keeps track of the processes that are ready to be scheduled

    int idx = -1;

    // first look through the process list and find any processes that are newly ready and
    // add them to the back of the ready queue
    for(int i = 0, i_end = procList.size(); i < i_end; ++i)
    {
        if(procList[i].startTime == curTime)
        {
            ready.push_back(i);
        }
    }

    // now take a look the head of the ready queue, and update if needed
    // (i.e., if we are supposed to schedule now or the process is done)
    if(timeToNextSched == 0 || procList[ready[0]].isDone)
    {
        // the process at the start of the ready queue is being taken off of the
        // processor

        // if the process isn't done, add it to the back of the ready queue
        if(!procList[ready[0]].isDone)
        {
            ready.push_back(ready[0]);
        }

        // remove the process from the front of the ready queue and reset the time until
        // the next scheduling
        ready.pop_front();
        timeToNextSched = timeQuantum;
    }

    // if the ready queue has any processes on it
    if(ready.size() > 0)
    {
        // grab the front process and decrement the time to next scheduling
        idx = ready[0];
        --timeToNextSched;
    }
    // if the ready queue has no processes on it
    else
    {
        // send back an invalid process index and set the time to next scheduling
        // value so that we try again next time step
        idx = -1;
        timeToNextSched = 0;
    }

    // return back the index of the process to schedule next
    return idx;
}

int SPN(const int& curTime, const vector<Process>& procList){
    int shortestTime = 0;
    static int shortestPOS = -1;
    static bool running;

    if(curTime == 0 || (shortestPOS >= 0 && procList.at(shortestPOS).isDone)){ running = false; }

    if(!running){
    //Find the process with the shortest totaltimeNeeded
         for(size_t i = 0; i < procList.size(); i++){
            if(!procList.at(i).isDone && procList.at(i).startTime <= curTime && procList.at(i).totalTimeNeeded < shortestTime){
                shortestTime = procList.at(i).totalTimeNeeded;
                shortestPOS = i;
            }
         }
    }
    
    if(shortestPOS > -1){
        running = true;
    }

    //Process the process
    return shortestPOS;
}

int SRT(const int& curTime, const vector<Process>& procList){
    int shortestTime = 0;
    static int shortestPOS = -1;
    //Find the process with the shortest totaltimeNeeded
         for(size_t i = 0; i < procList.size(); i++){
            if(!procList.at(i).isDone && procList.at(i).startTime <= curTime && procList.at(i).totalTimeNeeded < shortestTime){
                shortestTime = procList.at(i).totalTimeNeeded;
                shortestPOS = i;
            }
         }

    //Process the process
    return shortestPOS;
}

//int HRRN(const int& curTime, const vector<Process>& procList){
//
//}

