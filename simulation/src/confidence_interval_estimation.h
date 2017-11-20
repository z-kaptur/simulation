/********************************************//**
 * \file   confidence_interval_estimation.h
 * \brief  Confidence interval estimation class.
 * \author Krzysztof Bakowski (krzysztof.bakowski@put.poznan.pl)
 * \date   2014-08-07
 ***********************************************/
#ifndef CONFIDENCE_INTERVAL_ESTIMATION_H_
#define CONFIDENCE_INTERVAL_ESTIMATION_H_
//***********************************************
/////////////////////////////////////////////////
/*! \brief Confidence interval estimation.
 *
 *  Definition of the confidence interval estimation.
 */
class ConfidenceIntervalEstimator
{
public:
	enum CONFIDENCE_LEVEL	//! Confidence level.
	{
		alpha0_1 = 0,		//!< 10%
		alpha0_05 = 1,		//!< 5%
		alpha0_025 = 2,		//!< 2.5%
		alpha0_01 = 3,		//!< 1%
		alpha0_005 = 4		//!< 0.5%
	};

	//! Default constructor.
	ConfidenceIntervalEstimator();

	//! Add realization of a random variable.
	void add_realization(double xi);

	//! Reset estimator.
	void reset();

	//! Get half of the width of the confidence interval.
	double get_delta(CONFIDENCE_LEVEL alpha);

	//! Get mean value.
	double get_mu();

	//! Get variance value.
	double get_variance();

	//! Get sigma value.
	double get_sigma();

private:
	//! Get Student's t distribution value.
	static double st_distribution(int i,int j);

	//! Student's t distribution table.
	static double student_t_distribution[31][5];

	int M;			//!< Number of observations.

	double sum_xi;	//!< Sum of the observed values.

	double sum_xi2;	//!< Sum of the squares of the observed values.
};
/////////////////////////////////////////////////
//***********************************************
#endif /* CONFIDENCE_INTERVAL_ESTIMATION_H_ */
