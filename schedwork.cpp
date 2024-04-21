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
bool canSchedule(const AvailabilityMatrix& avail,
    DailySchedule& sched,
    std::vector<unsigned int> shiftsCount,
    const size_t dailyNeed,
    const size_t maxShifts,
    const size_t day,
    const size_t workerIdx,
    const size_t currentNeed);

void resizeSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, DailySchedule& sched);
void resizeShiftsCount(const AvailabilityMatrix& avail, std::vector<unsigned int>& shiftsCount);
bool isValid(const AvailabilityMatrix& avail, int index, const size_t day, std::vector<unsigned int> shiftsCount, const size_t maxShifts);
bool baseCase(const AvailabilityMatrix& avail, const size_t day);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    if(avail[0].size() == 0) {
        return false;
    }
    sched.resize(avail.size(), std::vector<Worker_T>(dailyNeed));
    std::vector<unsigned int> shiftsCount;
    shiftsCount.resize(avail[0].size(), 0);
    return canSchedule(avail, sched, shiftsCount, dailyNeed, maxShifts, 0, 0, 0);
}

bool canSchedule(const AvailabilityMatrix& avail,
    DailySchedule& sched,
    std::vector<unsigned int> shiftsCount,
    const size_t dailyNeed,
    const size_t maxShifts,
    const size_t day,
    const size_t workerIdx,
    const size_t currentNeed) {
        if(baseCase(avail, day)) return true;
        if(currentNeed == dailyNeed) return canSchedule(avail, sched, shiftsCount, dailyNeed, maxShifts, day+1, 0, 0);
        for(size_t i = workerIdx; i < avail[0].size(); i++) {
            if(isValid(avail, i, day, shiftsCount, maxShifts)) {
                sched[day][currentNeed] = i;
                shiftsCount[i] += 1;
                if(canSchedule(avail, sched, shiftsCount, dailyNeed, maxShifts, day, i+1, currentNeed+1)) {
                    return true;
                }
                shiftsCount[i] -= 1;
            }
        }
        return false;
    }

bool isValid(const AvailabilityMatrix& avail, int index, const size_t day, std::vector<unsigned int> shiftsCount, const size_t maxShifts) {
    return (avail[day][index]) && (shiftsCount[index] < maxShifts);
}

bool baseCase(const AvailabilityMatrix& avail, const size_t day) {
    return (day == avail.size());
}

