#include "random.h"

Random::Random(int seed)
{
	generator.seed(seed);
}

double Random::next()
{
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	return dis(generator);
}

double Random::operator() ()
{
	return next();
}