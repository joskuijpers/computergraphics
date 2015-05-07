#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>
#include <set>
#include <stack>
#include <vector>
#include <queue>

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
// Some types
typedef pair<int, int> line_t;
typedef pair<line_t, int> lineLoc_t;

/**
 * Find heighest surface in the linepiece.
 */
float findTop(vector<float> heights, line_t l)
{
	float max = 0.f;
	for(int i = l.first; i <= l.second; ++i) {
		if(max < heights[i])
			max = heights[i];
	}

	return max;
}

/**
 * Get whether the given linepiece is bound by walls at given level.
 */
bool isBound(vector<float> heights,lineLoc_t lineLoc)
{
	// A region is bound if, for both sides:
	// either the side is at least the height of the surface
	// or the wall outside is at least the height of the surface

	bool leftBound = false, rightBound = false;

	// Most left item
	if(heights[lineLoc.first.first] == lineLoc.second)
		leftBound = true;

	// Most right item
	if(heights[lineLoc.first.second] == lineLoc.second)
		rightBound = true;

	// Left wall
	if(!leftBound && heights[lineLoc.first.first-1] >= lineLoc.second)
		leftBound = true;

	// Right wall
	if(!rightBound && heights[lineLoc.first.second+1] >= lineLoc.second)
		rightBound = true;

	return leftBound && rightBound;
}

float WaterLevels(list<float> heights)
{
	// less than three surfaces can't hold a piece of water
	if(heights.size() < 3)
		return 0.f;

	// Convert to array, lists are annoying
	vector<float> vHeights;
	for(float v : heights)
		vHeights.push_back(v);

	float sum = 0.0;

	// stack of lines with heights.
	// A line is a begin and end pair.
	stack<lineLoc_t> lines;

	// Create a single line
	lines.push(lineLoc_t(line_t(1,heights.size()-2),INT_MAX));

	while(!lines.empty())
	{
		float top;
		lineLoc_t lineLoc;
		line_t line;

		// Take a horizontal line.
		lineLoc = lines.top();
		lines.pop();

		// Lower it to top in this segment
		top = findTop(vHeights,lineLoc.first);
		lineLoc.second = top;

		line = lineLoc.first;

		// check if bound
		if(isBound(vHeights,lineLoc)) {
			// calculate the contents of this 'lake'
			// for every surface in this linepiece, calculate diff between height
			// and height of the line.
			for(int i = line.first; i <= line.second; ++i)
				sum += top - vHeights[i];

			continue;
		}
		// otherwise, split up further

		// Find columns it touches

		// Split it at the columns it touches
		// before first top, between every top, and after last top
		int previous = line.first;
		for(int i = line.first; i <= line.second; ++i) {
			if(vHeights[i] != top)
				continue;

			// element from previous to i-1 at height top
			lineLoc_t newLine = lineLoc_t(line_t(previous,i-1),top);
			lines.push(newLine);

			previous = i + 1;
		}

		// Add line from previous to end
		if(previous != line.second && previous < line.second) {
			lineLoc_t newLine = lineLoc_t(line_t(previous,line.second),top);
			lines.push(newLine);
		}
	}

	return sum;
}

#pragma mark - Exercise 5
typedef std::pair<int, int> location;

int Labyrinth(set<pair<location, location>> labyrinth, int size)
{
	// Build a tree. Every node is a square, every edge a path from
	// a square to another square. Paths that are not possible are not made. (walls)



	// Execute Dijkstra

	return 0;
}

bool isWall(set<pair<location, location>> labyrinth, pair<location, location> path)
{
	//
	return false;
}

#endif