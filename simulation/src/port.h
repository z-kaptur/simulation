/********************************************//**
 * \file   port.h
 * \brief  Port class.
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
#ifndef PORT_H
#define PORT_H
/////////////////////////////////////////////////
/*! \brief 
*
*	Port class represents resources available 
*
*/


class Port
{
	friend Canal;
	friend Watercraft;
public:
	
	//! Konstruktor
	Port(int* num_res);
	
	//! Metoda zwracajaca liczbe zasobow wybranego typu w porcie
	int get_number_of_resources(Resource res);

	//! Metoda zwracajaca liczbe wolnych zasobow wybranego typu w porcie
	int get_available_resources(Resource res);

	//! Metoda rozpoczynajaca obsluge jednostki, zwraca czas obslugi
	double startService(Watercraft* client, double time);

	//! Metoda wyswietlajaca ilosc dostepnych zasobow poszczegolnych typow (pomocniczo przy testowaniu stworzonych obiektow)
	void show_available_resources();

	//! Metoda wyswietlajaca jednostki znajdujace sie w porcie (pomocniczo przy testowaniu stworzonych obiektow)
	void showVisitors();

	//! Metoda zwracajaca liczbe jednostek w porcie (pomocniczo przy testowaniu stworzonych obiektow)
	int checkVisitors();

private:

	int number_of_resources[3];		//!< Liczba wszystkich zasobow poszczegolnych typow
	int available_resources[3];		//!< Liczba dostepnych zasobow poszczegolnych typow

	int l_wyw;
	string sth;
	static double unit_per_min[3];	//!< Ilosc przenoszonego towaru na minute dla poszczegolnych typow urzadzen portowych
	static double using_time[3];	//!< Czas uzycia posczegolnych typow urzadzen portowych
};
///////////////////////////////////////////////// 
//***********************************************
#endif /*PORT_H*/
