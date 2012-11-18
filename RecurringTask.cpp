#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include "RecurringTask.h"
#include "Job.h"
#include "Schedule.h"

using namespace boost::posix_time;
using namespace boost::filesystem;

RecurringTask::RecurringTask(string name, Schedule schedule) : name(name), schedule(schedule) {
}

Job RecurringTask::getNextJob() {

    ptime time = schedule.getNextTime();
    int index = getNextIndex();
    
    Job job = Job(name, time, index);
    
    return job;
}

string RecurringTask::toString() {
    return string("RecurringTask: Name: ") + name + string(", ") + schedule.toString();
}

int RecurringTask::getNextIndex() {
    path p(name.c_str());
    //printf("%s \n", name.c_str());
    
    if (!exists(p)) {
        printf("Path does not exist.\n");
        return -1;
    }
    if (!is_directory(p)) {
        printf("Path is not a directory.\n");
        return -1;
    }
    
    vector<path> files;
    copy(directory_iterator(p), directory_iterator(), back_inserter(files));
    sort(files.begin(), files.end());

    int index = 0;
    for (vector<path>::reverse_iterator it = files.rbegin(); it != files.rend(); it++) {
        if (is_regular_file(*it)) {
            string filenameWithExtension = it->filename().c_str();
            size_t extensionStart = filenameWithExtension.find(".jpg");
            if (extensionStart == string::npos) {
                continue;
            }
            string filename = filenameWithExtension.substr(0, extensionStart);
            
            index = atoi(filename.c_str());
            printf("Existing file: %s/%d.jpg\n", name.c_str(), index);
            if (index > 0) {
                break;
            }
        }
    }
    
    if (index <= 0) {
        return 1;
    }
    else {
        index++;
        return index;
    }
}