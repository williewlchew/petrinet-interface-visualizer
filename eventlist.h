#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <event.h>


class EventList
{
    public:
        EventList();
        ~EventList();

        Event* Get(std::string name);
        Event* Get(int index);
        void Push(Event* item);
        void Pop(Event* item);

     private:
        std::vector<Event*> list;
};

#endif // EVENTLIST_H
