#ifndef LIBPOISSON_H
#define LIBPOISSON_H

/**
 * @brief This function calculate the probability of a random variable that is Poisson distributed to be equal to some natural number
 * @param k The natural number to check against.
 * @param lambda The parameter for the Poisson distribution
 * @return P(X=k) For X~Poi(lambda)
 */
long double poisson(unsigned int k, long double lambda);

#endif
