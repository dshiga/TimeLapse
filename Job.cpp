#include "Job.h"
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

Job::Job(string name, ptime time, int index) : name(name), time(time), index(index) {
}

bool Job::compare(Job job1, Job job2) {
    return job1.getTime() < job2.getTime();
}

string Job::toString() {
    stringstream stream;
    
    stream.str("");
    stream << index;
    
    return string("Job: ") + name + string(", ") + to_simple_string(time) + string(", ")
        + string("index: ") + stream.str();
}
