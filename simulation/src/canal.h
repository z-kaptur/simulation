/********************************************//**
 * \file   canal.h
 * \brief  Canal and Lane classes.
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
#ifndef CANAL_H
#define CANAL_H

/////////////////////////////////////////////////

const double Tt = 10;
/*! \brief 
*
*	Single lane in a canal
*
*/

class Lane
{
	friend class Canal;
	friend class Watercraft;
public:
	//! Kontruktor
	Lane(double i_depth);

	//! Konstruktor domyslny
	Lane();

	//! Metoda wyznaczajaca czas plyniecia przez tor
	double SailTime(Watercraft* pwc);

	//! Metoda wyznaczajaca stan toru (potrzebny do obliczenia czasu plyniecia) w zaleznosci od kierunku plyniecia jednostki
	int getState(Watercraft* pwc);

	//! Metoda sprawdzajaca czy tor jest dostepny dla danej jednostki
	bool isAvailable(Watercraft* candidate);

private:
	bool free;					//!< Zajetosc toru (1 - wolny, 0 - zajety) 
	double depth;				//!< Glebokosc toru
	double last_use_time;		//!< Czas ostatniego uzycia
	bool last_use_direction;	//!< Kierunek ostatniego uzycia (1 - do portu, 0 - z portu)
	Watercraft* current;		//!< Jednostka aktualnie korzystajaca z toru

	double lane_using_time;		//!< Calkowity czas wykorzystania toru
};

/////////////////////////////////////////////////
/*! \brief 
*
*	Whole canal including all the lanes
*
*/
class Canal
{
	friend class Lane;
	friend class Watercraft;

public:

	//! Konstruktor
	Canal(int num_lanes);
	
	//! Ustawianie glebokosci poszczegolnych torow
	void setDepth(int n, double i_depth);
	
	//! Metoda dokonujaca proby zajecia toru przez jednostke. W przypadku powodzenia funkcja zwraca numer zajetego toru, w przcywnym razie zwraca wartosc -1
	int checkLanes(Watercraft*candidate, double SimTime, Port* port);
	
	//! Metoda sprawdzajaca czy wybrany tor jest wolny (pomocniczo przy testowaniu stworzonych obiektow)
	bool isFree(int lane_number);

	//! Metoda wyswietlajaca zajetosc poszczegolnych torow w kanale (pomocniczo przy testowaniu stworzonych obiektow)
	void disp();

	//! Zwracanie glebokosci wybranego toru w kanale
	double getDepth(int n);

private:
	int number_of_lanes;			//!< Liczba torow
	Lane* lane_table;				//!< Tablica torow

	static double canal_using_time;	//!< Calkowity czas uzycia kanalu - wszystkich torow lacznie
	
};
/////////////////////////////////////////////////
//***********************************************
#endif /*CANAL_H*/
