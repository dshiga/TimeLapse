#ifndef TimeLapse_Job_h
#define TimeLapse_Job_h

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

// A Job represents a command to capture and save a frame from the camera at a specific time.

class Job {
    // Name of the job. Frame will be saved in a folder matching this name.
    string name;
    // The time at which to capture the frame.
    ptime time;
    // A number to be used as the file name when the frame is saved.
    int index;
public:
    Job(string name, ptime time, int index);
    // Comparison function. True if job1's time is earlier than job2's time.
    static bool compare(Job job1, Job job2);
    string getName() { return name; } ;
    ptime getTime() { return time; } ;
    int getIndex() { return index; } ;
    // Returns a human readable representation of the Job.
    string toString();
};

#endif
