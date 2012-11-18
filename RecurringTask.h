#ifndef TimeLapse_RecurringTask_h
#define TimeLapse_RecurringTask_h

#include "Schedule.h"
#include "Job.h"
#include <string>
using namespace std;

// Represents a command to capture frames according to a Schedule,
// to be saved in a folder named name.

class RecurringTask {
    // Name of task. Frames captured as part of this task will be saved in a folder
    // with this name.
    string name;
    // The Schedule to use to calculate Job times.
    Schedule schedule;
public:
    RecurringTask(string name, Schedule schedule);
    // Get the next frame capture Job that will occur after the current time.
    Job getNextJob();
    string toString();
    // Get the next number to be used as the file name. Returns 1 greater than the
    // highest number currently used as jpg a file name in the folder named name.
    // For example, if the folder contains 1.jpg, 2.jpg, and 3.jpg, this will return 4.
    int getNextIndex();
};

#endif
