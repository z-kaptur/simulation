
#include "sc.h"
#ifndef NULL
#define NULL 0
#endif
using namespace simulation;
//===============================================
QLink::QLink(Watercraft* pwc) : data(pwc)
{
	next = NULL;
}
//===============================================
Queue::Queue() 
{
	first = last = NULL;
	length = mean_length = 0;
}
//----------------------------------------------
void Queue::push(Watercraft* pwc)
{
	mean_length+=(sim_clock-last_change_time)*length++;

	if (first == NULL)
	{
		first = last = new QLink(pwc);
		last_change_time = sim_clock;
		return;
	}

		last = last->next = new QLink(pwc);
		last_change_time = sim_clock;
}
//-----------------------------------------------
Watercraft* Queue::pop()
{
	if (first == NULL)
	{
		cout << "Kolejka jest pusta! " << endl;
		return NULL;
	}

	Watercraft * pwc;

	if (first == last)
	{
		pwc= first->data;
		delete first;
		first = last = NULL;

		mean_length += (sim_clock - last_change_time)*length--;
		last_change_time = sim_clock;

		return pwc;
	}

	pwc = first->data;
	QLink* temp = first;

	first = first->next;
	delete temp;

	mean_length += (sim_clock - last_change_time)*length--;
	last_change_time = sim_clock;

	return pwc;
}
//----------------------------------------------
Watercraft* Queue::checkFirst()
{
	if (first == NULL) return NULL;
	return first->data;
}
//----------------------------------------------
void Queue::disp()
{
	QLink* temp = first;
	int n = 1;
	while (n <= length)
	{
		cout << n << ") Typ: " << temp->data->type << " Waga: " << temp->data->weight << " ID: " << temp->data->id << " arrv " << temp->data->arrival << endl;
		n++;
		temp = temp->next;
	}
	cout << endl;
}
//----------------------------------------------
bool Queue::is_empty()
{
	if (first == NULL) return true;
	return false;
}
//----------------------------------------------
void Queue::make_empty()
{
	while (!is_empty())
	{
		Watercraft* temp = pop();
		delete temp;
	}
}
//===============================================
void QueueContainer::disp()
{
	for (int i = 0; i < number; i++)
	{
		cout << "Kolajka " << i << endl;
		queueTable[i].disp();
	}
}
//----------------------------------------------
QueueContainer::QueueContainer(int n) :number(n)
{
	queueTable = new Queue[n];
}
//----------------------------------------------
void QueueContainer::push(Watercraft* pwc)
{
	if (pwc->direction == 1)
	{
		switch (pwc->type)
		{
		case cargo: 
		case roro:
			if (pwc->weight < 2000) {queueTable[0].push(pwc); return;}
			queueTable[1].push(pwc);
			return;
		case container_ship1:
			if (pwc->weight < 2000) { queueTable[2].push(pwc); return; }
			queueTable[3].push(pwc);
			return;
		case yacht:
			queueTable[4].push(pwc);
			return;
		}
	}
	if (pwc->weight < 2000) { queueTable[0].push(pwc); return; }
	queueTable[1].push(pwc);
}
//----------------------------------------------
Watercraft* QueueContainer::checkFirst(int n)
{
	return queueTable[n].checkFirst();
}
//----------------------------------------------
Watercraft* QueueContainer::pop(int n)
{
	return queueTable[n].pop();
}
//----------------------------------------------
int QueueContainer::length()
{
	int result = 0;
	for (int i = 0; i < number; i++)
	{
		cout << i << ": " << queueTable[i].length << endl;
		result += queueTable[i].length;
	}
	return result;
}
//----------------------------------------------
void QueueContainer::make_empty()
{
	for (int i = 0; i < number; i++)
	{
		queueTable[i].make_empty();
	}
}
//----------------------------------------------
bool QueueContainer::is_empty()
{
	for (int i = 0; i < number; i++)
	{
		if (!queueTable[i].is_empty()) return false;
	}
	return true;
}
/////////////////////////////////////////////////
//***********************************************
