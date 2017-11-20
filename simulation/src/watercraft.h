/********************************************//**
 * \file   watercraft.h
 * \brief  Watercraft class.
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
#ifndef WATERCRAFT_H
#define WATERCRAFT_H
/////////////////////////////////////////////////
/*! \brief 
*
*	Watercraft class represents single ship/yacht
*
*/

class Watercraft:public Process
{
	friend class Queue;
	friend class QueueContainer;
	friend class Lane;
	friend class Canal;
	friend class Port;

public:

	//! Konstruktor
	Watercraft();

	//! Destruktor
	~Watercraft();

	void execute();

	//! Metoda wyswietlajaca ilosc zasobow poszczegolnych typow potrzebnych do obslugi jednostki w porcie (pomocniczo przy testowaniu stworzonych obiektow)
	void show_required_resources();

	//! Metoda sprawdzajaca czy w porcie znajduja sie wolne zasoby wystarczajace do obsluzenia jednostki
	bool checkResources();

	//! Metoda wywolywana przy zwolnieniu toru przez jednostke - poszukuje jednostki, ktora moglaby wykorzystac zwolniony tor, zwraca do niej wskaznik (jezeli nie znaleziono - zwraca NULL)
	Watercraft* LaneRelease(int lane_number);
	
	//! Metoda wywolywana przy zwolnieniu zasobu przez jednostke - poszukuje jednostki, ktora moglaby wykorzystac zwolnione zasoby, zwraca do niej wskaznik (jezeli nie znaleziono - zwraca NULL)
	Watercraft* ResourceRelease(Resource res);
	
	//! Metoda zwracajaca numer toru wybranego do wplyniecia (jezeli nie jest mozliwe wplyniecie do zadnego z torow zwracana jest wartosc -1) 
	int checkLanes();

	//! Metoda dokonujaca proby zajecia przez jednostke ktoregos z torow. Zwraca true w przypadku powodzenia
	bool allocateLane();

	//! Metoda realizujaca obsluge statku w porcie. Zwraca czas obslugi jednostki
	double Service();

	//! Wyswietlanie statystyk
	static void show_statistics();

	//! Wyswietlanie zawartosci kolejek
	static void show_queues();

	//! Dlugosc kolejki wejsciowej
	static int in_queue_length();

	//! Dlugosc kolejki wyjsciowej
	static int out_queue_length();

	//! Ustawianie parametru lambda
	static void setLambda(double in);
	
	//! Resetowanie statystyk
	static void reset_statistics();

	//! Resetowanie systemu
	static void reset();

	//! Resetowanie symulacji
	static void reset_simulation();

	//! Do zbierania statystyk o czasie obs³ugiwania jednostek
	static ofstream watercraft_stats;

	
	static ofstream weight_stats;

	static ofstream generator;

	//! Wyznaczanie œredniego czasu oczekiwania na obs³ugê
	static double get_mu_st(){ return waiting_time / serviced; }

	static unsigned int serviced;		//!< Liczba obsluzonych jednostek
	static unsigned int number_type[4];	//!< Liczba wygenerowanych jednostek poszczegolnych typow
	static unsigned int serviced_type[4];//!< Liczba obsluzonych jednostek poszczegolnych typow

	static double waiting_time;			//!< Laczny czas oczekiwania na obsluge
	static double waiting_time_type[4];	//!< Laczny czas oczekiwania na obsluge dla poszczegolnych jednostek
	static double max_wait_time;		//!< Maksymalny czas oczekiwania na obsluge

	static double get_lane_stats(int i);
	static double get_resource_stats(Resource res);

	static void show_available_resources();

private:

	Watercraft_type type;				//!< Typ jednostki plywajacej

	bool direction;						//!< Kierunek plyniecia (1-do portu, 0-z portu)
	double load_prob;					//!< Prawdopodobieñstwo za³adunku
	int required_resources[3];			//!< Tablica przechwowuj¹ca dane o potrzebnych zasobach dla jednostki
	int id;								//!< Identyfikator statku
	
	double weight;						//!< Waga jednostki plywajacej
	double load;						//!< Ladunek
	
	double arrival;						//!< Czas utworzenia jednostki i wprowadzenia jej do kolejki
	double start_service;				//!< Czas rozpoczecia obslugi
	double departure;					//!< Czas opuszczenia portu
	
	int id_afterservice;				//!<Identyfikator przydzielany po zakonczeniu obslugi
	int used_lane;						//!<Wykorzystywany tor (je¿eli =-1 jednostka nie przebywa w kanale)

	static QueueContainer* in_queue;	//!<Kolejka wejsciowa do portu
	static QueueContainer* out_queue;	//!<Kolejka wyjsciowa z portu
	static Port* port;					//!<Port
	static Canal* canal;				//!<Kanal

	static double lambda;				//!<Intensywnosc rozkladu wykladniczego
	static int seed_lambda;				//!<Ziarno dla generatora czasu pojawienia sie kolejnego statku
	static int seed_type;				//!<Ziarno dla generatora typow statkow
	static int seed_load[4];			//!<Tablica ziaren dla generatorow zaladunku
	static int seed_yacht_time;			//!<Ziarno dla generatora czasu pobytu jachtu w porcie
	static int seed_yacht_weight;		//!<Ziarno dla generatora masy jachtu
	static int seed_cargo_weight;		//!<Ziarno dla generatora masy drobnicowca
	static int seed_roro_weight;		//!<Ziarno dla generatora masy statku ro-ro
	static int seed_container_weight;	//!<Ziarno dla generatora masy kontenerowca

	static unsigned int counter;

	static unsigned int number;			//!< Liczba wygenerowanych jednostek




};	
/////////////////////////////////////////////////
//***********************************************
#endif /*WATERCRAFT_H*/
