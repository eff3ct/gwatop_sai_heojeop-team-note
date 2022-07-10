#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

typedef struct _Point {
    int x;
    int y;
} Point;

//Standard Point to Sort
Point S;

Point get_vector(const Point& A, const Point& B) {
    Point v = {B.x - A.x, B.y - A.y};
    return v;
}

//ccw test
int ccw(const Point& v, const Point& u) {
    ll val = (ll)v.x * u.y - (ll)v.y * u.x; 
    if(val > 0) return 1;
    else if(val < 0) return -1;
    else return 0;
}

int ccw(const Point& A, const Point& B, const Point& C) {
    Point v = get_vector(A, B);
    Point u = get_vector(B, C);
    return ccw(v, u);
}

//to sort by ccw
bool comp(const Point& A, const Point& B) {
    Point v = get_vector(S, A);
    Point u = get_vector(S, B);

    if(ccw(v, u) > 0) return true;
    else if(ccw(v, u) < 0) return false;

    return (v.x == u.x) ? (v.y < u.y) : (v.x < u.x);
}

bool operator<(const Point& A, const Point& B) {
    return (A.x == B.x) ? (A.y < B.y) : (A.x < B.x);
}

//Graham's Scan Method
vector<Point> get_convex_hull(vector<Point>& A) {
    S = *min_element(A.begin(), A.end());
    sort(A.begin(), A.end(), comp);
    int n = (int)A.size();

    vector<Point> convex_hull;

    //get Convex Hull
    for(int i = 0; i < n; ++i) {
        while((int)convex_hull.size() > 1 
        && ccw(convex_hull[(int)convex_hull.size() - 2], convex_hull.back(), A[i]) <= 0) {
            convex_hull.pop_back();
        }
        convex_hull.push_back(A[i]);
    }
    
    return convex_hull;
}