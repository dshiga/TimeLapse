#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/time.h>
#include <boost/shared_ptr.hpp>
#include <boost/date_time.hpp>
#include "RecurringTask.h"
#include "RecurringTaskList.h"
#include "Job.h"
#include "Schedule.h"

using namespace cv;
using namespace std;
using namespace boost;
using namespace boost::gregorian;
using namespace boost::posix_time;

// Defines the main loop that runs when TimeLapse is executed. Use Ctrl+C to stop.
// Also defines the RecurringTasks that determine when frame will be capture and 
// where they will be saved.

// Captures the frame immediately and saves it to disk, with folder and file name
// specified by job.
int captureFrame(shared_ptr<Job> job);

// Constructs the list of RecurringTasks.
RecurringTaskList initTaskList();

long MS_PER_S = 1000;
long MS_PER_MIN = 60 * MS_PER_S;
long MS_PER_HR = 60 * MS_PER_MIN;
long MS_PER_DAY = 24 * MS_PER_HR;

int main (int argc, char * const argv[]) {
	
    shared_ptr<Job> job;

    RecurringTaskList tasks = initTaskList();
    printf("%s\n\n", tasks.toString().c_str());
    
    while (true) {
    
        if (job != NULL) {
            captureFrame(job);
        }
        
        job = tasks.getNextJob();
    
        ptime now = second_clock::local_time();
    
        ptime nextJobTime = job->getTime();
    
        time_duration timeToNextJob = nextJobTime - now;
        printf("Current time: %s\n", to_simple_string(now).c_str());
        printf("Next %s\n", job->toString().c_str());
        printf("Time to next job: %s\n", to_simple_string(timeToNextJob).c_str());
    
        long s = timeToNextJob.total_seconds();

        // Sleep until it's time to capture the next frame.
        sleep((unsigned int) s);
    }
	
    return 0;
}

int captureFrame(shared_ptr<Job> job) {
    Mat frame;
    stringstream stream;
    
    // Construct a VideoCapture object using device number 1.
    VideoCapture cap(1);
    if (!cap.isOpened()) {
        return -1;
    }
    
    // Resolution to use when capturing the frame.
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 960);

    cap >> frame;
    
    int i = job->getIndex();
    
    stream.str("");
    stream.clear();
    stream << i;
    
    string paddedFileName = "";
    if (i < 100) {
        if (i < 10) {
            paddedFileName = "00" + stream.str();
        }
        else {
            paddedFileName = "0" + stream.str();
        }
    }
    else {
        paddedFileName = stream.str();
    }

    imwrite(job->getName() + "/" + paddedFileName + ".jpg", frame);
    
    printf("\n\nWrote frame: %s.\n\n", (job->getName() + "/" + paddedFileName + ".jpg").c_str());
    
    return 0;
}

RecurringTaskList initTaskList() {
    
    // 9 am
    string name0 = "9am";
    date d0(2012, Oct, 8);
    ptime origin0(d0, hours(9));
    long period0 = 1 * MS_PER_DAY;
    Schedule schedule0 = Schedule(origin0, period0);
    RecurringTask task0 = RecurringTask(name0, schedule0);
    
    // Sunrise
    string name1 = "sunrise";
    date d1(2012, Oct, 14);
    ptime origin1(d1, hours(6));
    long period1 = 1 * MS_PER_DAY + 64348;
    Schedule schedule1 = Schedule(origin1, period1);
    RecurringTask task1 = RecurringTask(name1, schedule1);
    
    // siderial day, 12:00 pm on Jun 20 (4:47 am on Oct 8)
    string name2 = "sid_summer";
    date d2(2012, Oct, 8);
    ptime origin2(d2, hours(4) + minutes(47) + seconds(30));
    long period2 = 23 * MS_PER_HR + 56 * MS_PER_MIN + 4 * MS_PER_S + 92;
    Schedule schedule2 = Schedule(origin2, period2);
    RecurringTask task2 = RecurringTask(name2, schedule2);
    
    // siderial day
    string name3 = "sid_fall";
    date d3(2012, Oct, 14);
    ptime origin3(d2, hours(18) + minutes(03));
    long period3 = 23 * MS_PER_HR + 56 * MS_PER_MIN + 4 * MS_PER_S + 92;
    Schedule schedule3 = Schedule(origin3, period3);
    RecurringTask task3 = RecurringTask(name3, schedule3);

    // 3 pm
    string name4 = "3pm";
    date d4(2012, Oct, 8);
    ptime origin4(d4, hours(15) + minutes(3));
    long period4 = 1 * MS_PER_DAY;
    Schedule schedule4 = Schedule(origin4, period4);
    RecurringTask task4 = RecurringTask(name4, schedule4);
    
    // Sunset
    Schedule schedule5 = Schedule(ptime(date(2012, Oct, 14), hours(17) + minutes(3)), 1 * MS_PER_DAY - 41739);
    RecurringTask task5 = RecurringTask(string("sunset"), schedule5);

    // Test
    //Schedule schedule6 = Schedule(ptime(date(2012, Nov, 18), hours(11) + minutes(53)), 1000 * 5);
    //RecurringTask task6 = RecurringTask(string("test"), schedule6);

    RecurringTaskList taskList;
    taskList.add(task0);
    taskList.add(task1);
    taskList.add(task2);
    taskList.add(task3);
    taskList.add(task4);
    taskList.add(task5);
    //taskList.add(task6);

    return taskList;
}
