#include <random>
class Random
{
private:
	std::default_random_engine generator;
public:
	Random(int seed);
	double next();
	double operator() ();
};