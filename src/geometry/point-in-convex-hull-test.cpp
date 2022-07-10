#include <bits/stdc++.h>

using namespace std;

typedef struct _Point {
    int x;
    int y;
} Point;

Point get_vector(const Point& A, const Point& B);
int ccw(const Point& v, const Point& u);
int ccw(const Point& A, const Point& B, const Point& C);

//convext_hull size >= 3
bool isInside(vector<Point>& convext_hull, Point& A) {
    int O = 0;
    int L = 1, R = (int)convext_hull.size() - 1;
    int M = (L + R) / 2;

    Point vecOL = get_vector(convext_hull[O], convext_hull[L]);
    Point vecOA = get_vector(convext_hull[O], A);
    Point vecOR = get_vector(convext_hull[O], convext_hull[R]);
    Point vecOM = get_vector(convext_hull[O], convext_hull[M]);

    if(ccw(vecOL, vecOA) < 0) return false;
    if(ccw(vecOR, vecOA) > 0) return false;

    while(L + 1 != R) {
        M = (L + R) / 2;
        vecOM = get_vector(convext_hull[O], convext_hull[M]);

        if(ccw(vecOM, vecOA) > 0) L = M;
        else R = M;
    }

    if(ccw(convext_hull[L], A, convext_hull[R]) <= 0) return true; 
    else return false;
}