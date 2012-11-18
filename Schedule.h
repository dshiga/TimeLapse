//  Created by David Shiga on 10/8/12.

#ifndef TimeLapse_Schedule_h
#define TimeLapse_Schedule_h

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;

// A Schedule is used to calculate Job times.

class Schedule {
    // Time of first occurrence.
    ptime origin;
    // Time between occurrences.
    long period;
public:
    Schedule(ptime origin, long period);
    ptime getOrigin() { return origin; };
    long getPeriod() { return period; };
    // Returns the time of the next occurrence after the current time.
    // For example, if the Schedule has an origin of 5 am on Nov 5, 2012 and a period of 2 hours 
    // and it is currently 6 am on Nov 5, 2012, the time returned will be 7 am on Nov 5, 2012.
    ptime getNextTime();
    string toString();
};

#endif
