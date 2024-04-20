#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedValidity(const AvailabilityMatrix& avail, map<Worker_T, int>& workShifts, size_t maxShifts, int dayIndx, Worker_T worker);
bool scheduleDay(size_t dayInd, const AvailabilityMatrix& avail, DailySchedule& sched, map<Worker_T, int> workShifts, size_t maxShifts, size_t dailyNeed);



// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U|| avail[0].empty()){
        return false;
    }
    size_t days = avail.size();
    size_t workers = avail[0].size();
    sched.resize(days, vector<Worker_T>(dailyNeed));
    sched.clear();
    sched.resize(days);
    map<Worker_T, int> workShift;
    return scheduleDay(0, avail, sched, workShift, maxShifts, dailyNeed);
}

    // Add your code below
    bool scheduleDay(size_t dayIndx, const AvailabilityMatrix& avail, DailySchedule& sched, map<Worker_T, int> workShifts, size_t maxShifts, size_t dailyNeed) {
    if (dayIndx == avail.size()) {
        return true;  
    }
    size_t workers = avail[dayIndx].size();
    for (Worker_T i=0; i<workers; ++i) {
         
        if (schedValidity(avail, workShifts, maxShifts, dayIndx, i)) {
            sched[dayIndx].push_back(i);
            if(sched[dayIndx].size() == dailyNeed) {
                if(scheduleDay(dayIndx+1, avail, sched, workShifts, maxShifts, dailyNeed)) {
                    return true;
                }
                sched[dayIndx].pop_back();
                workShifts[i]-=1;
            }
            else {
                if(scheduleDay(dayIndx, avail, sched, workShifts, maxShifts, dailyNeed)) {
                    return true;
                }
                sched[dayIndx].pop_back();
                workShifts[i]-=1;
            }

        }
        
    }

    return false;

}

bool schedValidity(const AvailabilityMatrix& avail, map<Worker_T, int>& workShifts, size_t maxShifts, int dayIndx, Worker_T worker){
    int shifts = workShifts[worker];
    if(!avail[dayIndx][worker]) {
        return false;
    }
    if(shifts >= maxShifts) {
        return false;
    } else {
        workShifts[worker] += 1;
        return true;
    }

}





