/********************************************//**
* \file   event_scheduling.cpp
* \brief  Events list implementation.
* \author Krzysztof Bakowski (krzysztof.bakowski@put.poznan.pl)
* \date   2013-05-08
***********************************************/

#include "sc.h"
/////////////////////////////////////////////////
template <class object> void Link<object>::follow(Link* item)
{
	this->prev = item;			// The item becomes as previous element on the list.
	this->next = item->next;	// The next element assignment.
	item->next = this->next->prev = this;
}
//----------------------------------------------
template <class object> void Link<object>::remove()
{
	prev->next = this->next;
	next->prev = this->prev;
	delete this;
}
//===============================================
EventList::EventList()
{
	head = new Link<Event>(new nil());
}
//----------------------------------------------
Event* EventList::first()
{
	return head->next->data;
}
//----------------------------------------------
Event* EventList::remove_first()
{
	Event* current = first();      // Pointer to the first event on the list.
	head->next->remove();		   // Remove the indicated element of the link class.
	return current;
}
//----------------------------------------------
void EventList::schedule(Event * to_occur)
{
	Link<Event>* n = NULL;
	// Searching from the end.
	for (n = head->prev; n->data->event_time > to_occur->event_time; n = n->prev);

	(new Link<Event>(to_occur))->follow(n);

}
//----------------------------------------------
bool EventList::on_list(unsigned int pid)
{
	bool present = false;

	Link<Event> * current = head;
	while (current->next->data->proc)
	{
		if (current->next->data->proc->get_pid() == pid)
		{
			present = true;
			break;
		}
		current = current->next;
	}

	return present;
}
//----------------------------------------------
bool EventList::empty()
{
	return head->next == head;
}
//----------------------------------------------
void EventList::make_empty()
{
	while (!empty()) delete (remove_first())->proc;
}

void EventList::show()
{
	cerr <<endl<< "AGENDA" << endl;
	for (Link<Event>* n = head->next; n != head; n = n->next)
	{
		cerr << n->data->event_time << endl;
	}
	cerr << "~AGENDA" << endl<<endl;
}
/////////////////////////////////////////////////
//***********************************************
