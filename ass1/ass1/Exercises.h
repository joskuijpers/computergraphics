#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>
#include <set>
#include <stack>

using namespace std;

#pragma mark - Exercise 1
std::pair<float, float> Statistics(const std::list<float>& values)
{
	if(values.size() == 0)
		return std::pair<float, float>(0.f, 0.f);

	const size_t len = values.size();
	float sum = 0, sd = 0.0, avg;

	// calculate the average
	for(float v : values)
		sum += v;
	avg = sum / (float)len;

	// calculate the sd: sqrt(sum((v_i - avg)^2) / n)
	for(float v : values)
		sd += powf(v - avg,2);
	sd = sqrtf(sd / (float)len);

	return std::pair<float, float>(avg, sd);
}

#pragma mark - Exercise 2
class TreeVisitor {
public:
	float visitTree(const Tree& tree, bool countOnlyEvenLevels)
	{
		// recursive approach
//		return levelVisitor(tree, countOnlyEvenLevels, 0);

		// iterative approach
		stack<pair<Tree, int>> queue;
		float sum = 0.0;

		// add first element
		queue.push(pair<Tree,int>(tree,0));

		// loop until list is empty (depth first, because of stack)
		while(!queue.empty()) {
			pair<Tree,int> current = queue.top();
			queue.pop();

			// if even, add element
			if(!countOnlyEvenLevels || current.second % 2 == 0)
				sum += current.first.value;

			for(Tree t : current.first.children)
				queue.push(pair<Tree,int>(t,current.second + 1));
		}

		return sum;
	}

	// recursive approach
	float levelVisitor(const Tree& tree, bool countOnlyEvenLevels, int level)
	{
		float sum = 0.0;

		// If need to count, add the value
		if(!countOnlyEvenLevels || level % 2 == 0)
			sum += tree.value;

		// walk over all nodes
		for(Tree t : tree.children)
			sum += levelVisitor(t, countOnlyEvenLevels, level + 1);

		return sum;
	}
};

#pragma mark - Exercise 3
class Complex {
public:
	Complex(float real, float imaginary) : real(real),im(imaginary) {};

	float real, im;

	Complex operator- (const Complex other)
	{
		return Complex(real - other.real,im - other.im);
	};

	Complex operator+ (const Complex other)
	{
		return Complex(real + other.real,im + other.im);
	};

	Complex operator* (const Complex other)
	{
		//(a+bi) (c+di) = (ac-bd) + (bc+ad)i
		return Complex(real * other.real - im * other.im,
					   im * other.real + real * other.im);
	};
};

#pragma mark - Exercise 4
float WaterLevels(std::list<float> heights)
{
	return 0;
}

#pragma mark - Exercise 5
typedef std::pair<int, int> location;

int Labyrinth(std::set<std::pair<location, location> > labyrinth, int size)
{
	return 0;
}
//////////////////////////////////////////////////////////////////

#endif