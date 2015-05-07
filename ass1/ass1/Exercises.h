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
typedef set<pair<location, location>> walls_t;

typedef struct labyrinth_node_s
{
	location loc;
	location parent;
	labyrinth_node_s *children[4];
	int numChildren;
} labyrinth_node_t;


bool isWall(walls_t walls, location from, location to)
{
	for(pair<location,location> wall : walls) {
		if((wall.first == from && wall.second == to)
		   || (wall.first == to && wall.second == from))
			return true;
	}
	return false;
}

labyrinth_node_t *buildTree(walls_t walls, int size, list<location> parents, location current)
{
	// current node becomes a parent: copy parents, push current node
	list<location> newParents = parents;
	newParents.push_back(current);

	labyrinth_node_t *node = new labyrinth_node_t;
	node->loc = current;
	node->numChildren = 0;
	if(parents.size() > 0)
		node->parent = parents.back();

	//	find all neighbors where neightbor is any...
	// for every neighbor, (4 directions)
	for(int i = 0; i < 4; ++i) {
		int x = current.first;
		int y = current.second;

		switch(i) {
			case 0: ++x; break; // right
			case 1: --x; break; // left
			case 2: ++y; break; // down
			case 3: --y; break; // up
		};

		// ...except...

		// ...outside boundaries,...
		if(x < 0 || x >= size || y < 0 || y >= size)
			continue;

		// ...wall boundaries, ...
		if(isWall(walls, current, location(x,y)))
			continue;

		// ... or already in parent list.
		bool inList = false;

		for(location l : parents) {
			if(l == location(x,y)) {
				inList = true;
				break;
			}
		}
		if(inList)
			continue;

//		cout << "path from (" << current.first << "," << current.second << ") to (" << x << "," << y << ")" << endl;

		// Node is an accessable path node, find subtree
		labyrinth_node_t *child = buildTree(walls, size, newParents, location(x,y));

		// Add subtree to children
		node->children[node->numChildren++] = child;
	}

	return node;
}

int Labyrinth(walls_t labyrinth, int size)
{
	location start(0,0), finish(size-1,size-1);

	// Build a tree. Every node is a square, every edge a path from
	// a square to another square. Paths that are not possible are not made. (walls)

	// Start building at 0,0
	labyrinth_node_t *root = buildTree(labyrinth, size, list<location>(), start);

	// Execute a simple algorithm (we assume the graphs are reasonably small).
	// This is kind of bruteforce, but optimized.
	// Do a DFS on the tree, keeping track of the shortest path.
	// If the current path is going to be > the shortest, skip it
	int shortestPath = INT_MAX;

	// Stack for DFS (queue for BFS)
	stack<pair<labyrinth_node_t *,int>> queue;
	queue.push(pair<labyrinth_node_t *,int>(root,1));

	while(!queue.empty()) {
		pair<labyrinth_node_t *,int> queueItem = queue.top();
		queue.pop();

		labyrinth_node_t *node = queueItem.first;

		if(node->loc == finish) {
			// Update shortest path
			if(queueItem.second < shortestPath)
				shortestPath = queueItem.second;

			// Do not process any children
			continue;
		} else if(queueItem.second >= shortestPath) // length of this path can't ever be smaller than shortest found path
			continue;

		// Process all children
		for(int i = 0; i < node->numChildren; ++i)
			queue.push(pair<labyrinth_node_t *,int>(node->children[i],queueItem.second+1));
	}


	// TODO: memory cleanup :). It is a mess, really.
	// This is the last exercise, and after execution the program is ended,
	// cleaning up all memory. So practically it is not needed to clean it up.
	// it is also annoying to do so I am skipping it.
	// What I should do, is use a class with a destructor :)

	return shortestPath;
}

#endif