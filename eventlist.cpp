#include "eventlist.h"

EventList::EventList()
{

}

EventList::~EventList()
{

}

Event* EventList::Get(std::string name)
{
    for(Event* i : list)
    {
        if(i->getName().compare(name) == 0)
        {
            return i;
        }
    }
}

Event* EventList::Get(int index)
{
    return list[index];
}

void EventList::Push(Event* item)
{
    list.push_back(item);
}

void EventList::Pop(Event* item)
{
    int removeIndex = GetIndex(item);
    list.erase(list.begin() + removeIndex);
    delete item;
}

int EventList::GetIndex(Event* item)
{
    for(int i = 0; i < list.size(); i++)
    {
        if(list[i] == item){
            return i;
        }
    }
}
