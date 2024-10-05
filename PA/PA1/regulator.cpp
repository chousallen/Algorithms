#include <iostream>
#include <ctime>

using namespace std;

struct Time
{
    unsigned int micro = 0, milli = 0, sec = 0, min = 0, hour = 0;
};

void add_hour(Time &t)
{
    if(++t.hour == 0)
    {
        // add_day(t);
    }
}

void add_min(Time &t)
{
    if(++t.min == 0)
    {
        add_hour(t);
    }
}

void add_sec(Time &t)
{
    if(++t.sec == 0)
    {
        add_min(t);
    }
}

void add_milli(Time &t)
{
    cout << "Adding milli" << endl;
    if(++t.milli == 0)
    {
        add_sec(t);
    }
}

void add_micro(Time &t)
{
    if(++t.micro == 0)
    {
        add_milli(t);
    }
}

void add_time(Time &t)
{
    add_micro(t);
}

int main()
{
    Time t;

    while (t.hour == 0)
    {
        add_time(t);
    }
    

    return EXIT_SUCCESS;
}