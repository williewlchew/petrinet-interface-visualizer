///////////////////////////////////////////
/// Event List Object:
///     -Has the container of the list of events
///     -Has methods on how to manipulate the list
///     -can dislay the list of events on a list
///     -Can encode/decode a sequnce of events
//////////////////////////////////////////

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

        //helper methods
        int GetIndex(Event* item);
};

#endif // EVENTLIST_H
