#include "RecurringTaskList.h"
#include "Job.h"
#include <list>
#include <boost/shared_ptr.hpp>

using namespace boost;

shared_ptr<Job> RecurringTaskList::getNextJob() {
    list<Job> jobs = getJobList();
    
    return shared_ptr<Job>(new Job(*jobs.begin()));
}

list<Job> RecurringTaskList::getJobList() {
    list<Job> jobs;
    
    for(list<RecurringTask>::iterator it = taskList.begin(); it != taskList.end(); it++) {
        jobs.push_back(it->getNextJob());
    }
  
    jobs.sort(Job::compare);
    
    return jobs;
}

void RecurringTaskList::add(RecurringTask task) {
    taskList.push_back(task);
}

string RecurringTaskList::toString() {
    string s = "RecurringTaskList: ";
    
    for(list<RecurringTask>::iterator it = taskList.begin(); it != taskList.end(); it++) {
        s += string("\n") + it->toString();
    }
    
    return s;
}
