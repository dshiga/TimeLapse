//  Created by David Shiga on 10/8/12.

#ifndef TimeLapse_RecurringTaskList_h
#define TimeLapse_RecurringTaskList_h

#include <list>
#include "RecurringTask.h"
#include "Job.h"
#include <boost/shared_ptr.hpp>

using namespace boost;

// The list of RecurringTasks that will be used to capture frames by TimeLapse.

class RecurringTaskList {
    list<RecurringTask> taskList;
    list<Job> getJobList();
public:
    // Returns a pointer to the Job that occurs soonest (after current time) based on the list of RecurringTasks.
    // For example, if the task list contains task1, which schedules jobs every hour on the hour
    // and task2, which schedules jobs every two hours on the hour (starting at 2:00 am), and it is currently 2:30 am,
    // this will return a Job scheduled for 3:00 am defined by task1.
    shared_ptr<Job> getNextJob();
    void add(RecurringTask task);
    string toString();
};

#endif
