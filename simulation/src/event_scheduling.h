/********************************************//**
* \file   event_scheduling.h
* \brief  Events list implementation.
* \author Krzysztof Bakowski (krzysztof.bakowski@put.poznan.pl)
* \date   2013-05-08
 ***********************************************/

#ifndef EVENT_SCHEDULING_H
#define EVENT_SCHEDULING_H
/////////////////////////////////////////////////
class Process;
//----------------------------------------------
/*! \brief Event.
*
*	Event class represents the time event.
*
*/
class Event
{
public:
	//! Constructor.
	Event(Process  * ptr) : event_time(-1.0), proc(ptr){}

	double event_time; //!< Time of the occurrence of the event.

	Process * proc;	   //!< Process pointer.
};
//----------------------------------------------
// Link class template declaration.
// The link lass is responsible for storage of elements on the queue and linking its elements.
template <class object> class Link;
//----------------------------------------------
/*! \brief Event list.
*
*	Event lists implementation.
*
*/
class EventList
{
public:
	//! Constuctor.
	EventList();

	//! Return pointer to the first element on the list.
	Event* first();

	//! Remove the first element on the list and return pointer to it.
	Event* remove_first();

	//! Insert a new event on the events list.
	void schedule(Event*);

	//! Check if the events list is empty.
	bool empty();

	//! Remove all element from the list.
	void make_empty();

	//! Check if process is in the agenda.
	bool on_list(unsigned int pid);

	void show();

private:

	Link<Event>* head;		//!< Pointer to the first element of the list.
};
//----------------------------------------------
template <class object> class Link
{
	friend class EventList;

public:
	//! Constructor.
	Link(object* ptr) : data(ptr) { next = prev = this; }

	//! Insert a new link on the list after the provided element.
	void follow(Link* item);

	//! Remove the link element from the list.
	void remove();

private:

	Link<object>* next;	//!< Pointer to the next element on the list.
	Link<object>* prev;	//!< Pointer to the previous element on the list.
	object* data;		//!< Pointer to the stored object.
};
//----------------------------------------------
/*! \brief The empty element of the list.
*
*	Implementation of the constant element on the event list.
*
*/
struct nil : public Event
{
	nil(Process * ptr = NULL) : Event(ptr){}
};
/////////////////////////////////////////////////
//***********************************************
#endif /*EVENT_SCHEDULING_H*/
