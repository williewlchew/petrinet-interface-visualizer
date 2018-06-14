#include "events.h"

/*
 * Events
 */

Events::Events()
{
    name = "New Event";
}

Events::~Events()
{

}

void Events::setName(std::string nameInput){
    name = nameInput;
}

std::string Events::getName(){
    return name;
}
