#include <random>
#include "config.h"
#include <sgg/graphics.h>

float sample_uniform(float lower_bound, float upper_bound)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distr(lower_bound, upper_bound);

	return distr(gen);
}

int sample_int_uniform(int lower_bound, int upper_bound)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(lower_bound, upper_bound);

	return distr(gen);
}
