#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>
#include <set>

////////////////// Exercise 1 ////////////////////////////////////
std::pair<float, float> Statistics(const std::list<float>& values)
{
    float avg = 0, stddev = 0, sum = 0;
    int size = values.size();
    
    if (size == 0)
        return std::pair<float, float>(avg, stddev);
    
    for (float v : values)
        sum += v;
    
    avg = sum / size;
    
    for (float v: values)
        stddev += powf(v - avg, 2);
    
    stddev /= size;
    stddev = sqrtf(stddev);
    
    return std::pair<float, float>(avg, stddev);
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 2 ////////////////////////////////////
class TreeVisitor {
public:
	float visitTree(const Tree& tree, bool countOnlyEvenLevels){ return 0.f; }
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex {
public:
	Complex(float real, float imaginary){};

	float real, im;
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(std::list<float> heights)
{
	return 0;
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
typedef std::pair<int, int> location;

int Labyrinth(std::set<std::pair<location, location> > labyrinth, int size)
{
	return 0;
}
//////////////////////////////////////////////////////////////////

#endif