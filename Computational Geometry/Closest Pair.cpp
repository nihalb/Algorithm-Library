#include<stdio.h>
#include<algorithm>
#include<set>
#include<math.h>

using namespace std;

const int max_n = 10000 + 5;
const double infinity = 1000000000;

struct point
{
    point() : x(0), y(0) {}
    point(double a, double b) : x(a), y(b) {}
    double x;
    double y;
};

bool compare_x(point a, point b)
{
    return a.x < b.x;
}

struct compare_y
{
    bool operator () (const point& a, const point& b) const
    {
        return a.y < b.y;
    }
};

int N;
point pts[max_n];

double euclidean_dist(point a, point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double closest_pair()
{
    // Sort pts by X Coordinate
    sort(pts, pts + N, compare_x);

    // Sweep Line
    double h = infinity;
    int left = 0;
    set<point, compare_y> active_set;
    active_set.insert(pts[0]);
    for(int i=1; i<N; ++i)
    {
        while(pts[left].x < pts[i].x - h) active_set.erase(pts[left++]);
        set<point>::iterator itlow = active_set.lower_bound(point(0, pts[i].y - h));
        set<point>::iterator itup = active_set.upper_bound(point(0, pts[i].y + h));
        for(set<point>::iterator it = itlow; it != itup; ++it) h = min(h, euclidean_dist(*it, pts[i]));
        active_set.insert(pts[i]);
    }

    return h;
}

int main()
{
    return 0;
}

