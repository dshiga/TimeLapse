#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "Schedule.h"

using namespace std;
using namespace boost::posix_time;

Schedule::Schedule(ptime origin, long period): origin(origin), period(period) {
}

ptime Schedule::getNextTime() {
    
    ptime now = second_clock::local_time();
    //printf("getNextTime(): now: %s\n", to_simple_string(now).c_str());
    
    time_duration diffTd = now - origin;
    //printf("getNextTime(): duration: %s\n", to_simple_string(diffTd).c_str());
    
    long long diff = diffTd.total_milliseconds();
    //printf("getNextTime(): diff: %lld\n", diff);
    
    long msToNextTime = period - (diff % period);
    //printf("getNextTime(): msToNextTime: %lu\n", msToNextTime);
    
    ptime nextTime = now + milliseconds(msToNextTime);
    
    return nextTime;
}

string Schedule::toString() {
    stringstream stream;
    
    stream.str("");
    stream << period;
    
    return string("Schedule: Origin: ") + to_simple_string(origin) + string(", ")
        + string("Period: ") + stream.str() + string("s");
}
