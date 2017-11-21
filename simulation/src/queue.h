/********************************************//**
 * \file   queue.h
 * \brief  Queue and queue element classes.
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
#ifndef QUEUE_H
#define QUEUE_H
//-----------------------------------------------
class Watercraft;
//-----------------------------------------------
/*! \brief 
*
* Klasa pomocnicza dla kolejki (Queue)
* Przechowuje wskaznik do jednostki plywajacej oraz do kolejnego elementu kolejki
*
*/

class QLink
{
	friend class Queue;

private:

	//! Konstruktor
	QLink(Watercraft*);

	QLink * next;		//!< Wskaznik na nastepny element kolejki
	Watercraft * data;	//!< Wskaznik na jednostke plywajaca
};
//-----------------------------------------------
/*! \brief
*
* Kolejka
*
*/
class Queue
{
	friend class QueueContainer;
	friend class Watercraft;
	friend class Port;

public:

	//! Konstruktor
	Queue();

	//! Dodawanie elementu do kolejki
	void push(Watercraft* pwc);
	
	//! Usuwanie elementu z kolejki
	Watercraft* pop();

	Watercraft* checkFirst();

	//! Wyswietlanie zawartosci kolejki
	void disp();

	bool is_empty();

	void make_empty();

private:

	QLink* first;				//!< Wskaznik na pierwszy element w kolejce
	QLink* last;				//!< Wskaznik na ostatni element w kolejce
		
	int length;					//!< Dlugosc kolejki
	double mean_length;			//!< Srednia dlugosc kolejki
	double last_change_time;	//!< Czas ostatniej zmiany dlugosci kolejki

	
};
//-----------------------------------------------
/*! \brief QueueContainer.
*
* Klasa do tworzenia zbiorczej kolejki - zawierajacej w sobie wiele kolejek 
*(podzial jednostek na rozne kolejki ze wzgledu na zanurzenie i/lub potrzebne zasoby)
*
*/
class QueueContainer
{
	friend class Watercraft;

public:

	//! Konstruktor
	QueueContainer(int n);
	
	//! Dodawanie elementu do odpowiedniej kolejki (na podstawie okreslonych kryteriow)
	void push(Watercraft* pwc);

	//! Usuwanie elementu z n-tej kolejki w tabeli kolejek
	Watercraft* pop(int n);

	//! Zwracanie wskaznika do pierwszego elementu z n-tej kolejki w tablicy kolejek
	Watercraft* checkFirst(int n);

	//! Zwracanie sumarycznej dlugosci wszystkich kolejek w kontenerze
	int length();
	
	//! Wyswietlanie zbioru kolejek
	void disp();

	bool is_empty();

	void make_empty();

private:

	int number;				//!< Liczba kolejek sk³adowych
	Queue* queueTable;		//!< Tablica kolejek
};
/////////////////////////////////////////////////
//***********************************************
#endif /*QUEUE_H*/
