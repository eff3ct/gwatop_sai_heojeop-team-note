#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Point { double x, y; };
int ccw(Point, Point);
Point get_vector(Point, Point);

ll get_dist(Point& A, Point& B) { return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y); }

ll max_dist(vector<Point>& convex_hull) {
    if(convex_hull.size() == 1) return 0;
    if(convex_hull.size() == 2) return get_dist(convex_hull[0], convex_hull[1]);

    ll ret = 0;
    int a_idx = 1, b_idx = 2;

    Point a_start = convex_hull[0], a_end = convex_hull[1], b_start = convex_hull[1], b_end = convex_hull[2];
    while(true) {
        ret = max(ret, get_dist(a_start, b_start));

        Point v1 = get_vector(a_start, a_end);
        Point v2 = get_vector(b_start, b_end);

        if(ccw(v1, v2) > 0) {
            b_idx = (b_idx + 1) % convex_hull.size();
            b_start = b_end;
            b_end = convex_hull[b_idx];
        }
        else {
            a_idx++;

            if(a_idx == convex_hull.size()) {
                a_start = a_end;
                a_end = convex_hull[0];
            }
            else if(a_idx == convex_hull.size() + 1) break; //end condition

            a_start = a_end;
            a_end = convex_hull[a_idx];
        }
    }

    return ret;
}