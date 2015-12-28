#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<stack>

using namespace std;

struct point
{
    double x;
    double y;
};

// Vector storing the points of the polygon
vector<point> p;

// Stack storing the points on the convex hull
stack<point> hull;

// Point with the lowest y coordinate
point pivot;

// Get point with min y and resolve ties by min x
bool compare_y(point i, point j)
{
    if (i.y != j.y) return i.y - j.y < 0;
    else return i.x - j.x < 0;
}

// Euclidean distance
double dist(point i, point j)
{
    return sqrt((i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y));
}

// Sort by polar angle, resolve ties by distance from pivot
bool compare_angle(point i, point j)
{
    double cross = (i.x - pivot.x) * (j.y - pivot.y) - (i.y - pivot.y) * (j.x - pivot.x);
    if(cross != 0) return cross > 0;
    else return dist(i, pivot) < dist(j, pivot);
}

// Return true if the turn is counterclockwise
bool counterclockwise(point s, point m, point e)
{
    return (m.x - s.x) * (e.y - m.y) - (m.y - s.y) * (e.x - m.x) >= 0;
}

/*
Works for all cases unless all points are collinear and there are 
duplicate points. The final stack doesn't exclude points on the 
non-corner boundary of the hull. The final stack contains a copy 
of the pivot at the end
*/
void graham_scan()
{
    pivot = *min_element(p.begin(), p.end(), compare_y);
    sort(p.begin(), p.end(), compare_angle);
    p.push_back(pivot);

    hull.push(p[0]);
    hull.push(p[1]);
    
    for(int i=2; i<p.size(); ++i)
    {
        point start, mid;
        do
        {
            mid = hull.top();
            hull.pop();
            start = hull.top();
        }
        while (!counterclockwise(start, mid, p[i]));
        hull.push(mid);
        hull.push(p[i]);
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    {
        double x, y;
        scanf("%lf %lf", &x, &y);
        point t;
        t.x = x;
        t.y = y;
        p.push_back(t);
    }
    graham_scan();
    double ans = 0;
    point prev = hull.top();
    hull.pop();
    while(!hull.empty())
    {
        point p = hull.top();
        ans += dist(prev, p);
        hull.pop();
        prev = p;
    }
    printf("%d\n", int(ans));
    return 0;
}
