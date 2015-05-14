#ifndef EXERCISES_H
#define EXERCISES_H

#include <list>
#include <set>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

////////////////// Exercise 1 ////////////////////////////////////
std::pair<float, float> Statistics(const std::list<float>& values)
{
    float avg = 0, stddev = 0, sum = 0;
    size_t size = values.size();

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
	float visitTree(const Tree& tree, bool countOnlyEvenLevels) {
        return visitLevel(tree, countOnlyEvenLevels, 0);
    }

    float visitLevel(const Tree& tree, bool countOnlyEvenLevels, int level) {
        float sum = 0;

        if (!countOnlyEvenLevels || level % 2 == 0) {
            sum += tree.value;
        }

        for (Tree t : tree.children)
            sum += visitLevel(t, countOnlyEvenLevels, level + 1);

        return sum;
    }
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex {
public:
    Complex(float real, float imaginary) : real(real), im(imaginary){};

	float real, im;

    Complex operator+(const Complex& c2) {
        return Complex(real + c2.real, im + c2.im);
    }

    Complex operator-(const Complex& c2) {
        return Complex(real - c2.real, im - c2.im);
    }

    Complex operator*(const Complex& c2) {
        return Complex(real * c2.real - im * c2.im, real * c2.im + im * c2.real);
    }
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
typedef pair<int, int> line_t;

pair<float, int> max(line_t line, vector<float> levels) {
    pair<float, int> max = pair<float, int>(numeric_limits<float>::min(), -1);

    for (int i = line.first; i <= line.second; i++) {
        if (levels[i] > max.first) {
            max.first = levels[i];
            max.second = i;
        }
    }

    return max;
}

pair<float, int> max2(line_t line, vector<float> levels) {
    pair<float, int> max = pair<float, int>(numeric_limits<float>::min(), -1);

    for (int i = line.first + 1; i < line.second; i++) {
        if (levels[i] > max.first) {
            max.first = levels[i];
            max.second = i;
        }
    }

    return max;
}

float volume(line_t line, vector<float> levels) {
    float volume = 0.f;
    float edge = min(levels[line.first], levels[line.second]);

    for (int i = line.first + 1; i < line.second; i++)
        volume += edge - levels[i];

    return volume;
}

pair<line_t, line_t> split(line_t line, vector<float> levels) {
    pair<line_t, line_t> l = pair<line_t, line_t>();
    pair<float, int> m = max(line, levels);

    l.first = line_t(line.first, m.second);
    l.second = line_t(m.second, line.second);

    cout << "Splitting...(" << m.first << ", " << m.second << ")" << endl;

    return l;
}

float WaterLevels(std::list<float> heights)
{
    vector<float> levels {heights.begin(), heights.end()};
    queue<line_t> q = queue<line_t>();
    float v = 0.f;

    q.push(line_t(0, levels.size() - 1));

    while(!q.empty()) {
        line_t l = q.front();
        q.pop();

        pair<float, int> m = max(l, levels);

        cout << "(" << l.first << ", " << l.second << ") ";
        cout << m.first << ", " << m.second << endl;

        // Max is on the edge
        if (levels[l.first] == m.first || m.first == levels[l.second]) {
            cout << "Calculating volume..." << endl;

            // Calculate volume
            float p =  volume(l, levels);
            cout << "Volume: " << p << endl;

            v += p;
        } else {
            // Split
            pair<line_t, line_t> s = split(l, levels);

            q.push(s.first);
            q.push(s.second);
        }
    }

    cout << "Total volume: " << v << endl;

    return v;
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