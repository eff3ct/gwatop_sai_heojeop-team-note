#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const long double eps = 1e-7;

typedef struct _Point {
    long double x;
    long double y;
} Point;

Point getVector(Point& A, Point& B) {
    Point vec = {B.x - A.x, B.y - A.y};
    return vec;
}

int ccw(Point& v, Point& u) {
    ll val = v.x * u.y - v.y * u.x;
    if(val > 0) return 1;
    else if(val < 0) return -1;
    else return 0;
}

bool operator==(const Point& A, const Point& B) {
    return (abs(A.x - B.x) < eps && abs(A.y - B.y) < eps);
}

Point& operator/=(Point& A, const long double div) {
    A = {A.x / div, A.y / div};
    return A;
}

Point operator*(const Point& A, const long double mul) {
    Point X = A;
    X = {X.x * mul, X.y * mul};
    return X;
}


bool operator<=(const Point& A, const Point& B) {
    if(A.x < B.x) return true;
    else if(A.x == B.x && A.y <= B.y) return true;
    else return false;
}

int is_cross(Point& A, Point& B, Point& C, Point& D) {
    Point vecAB = getVector(A, B);
    Point vecCD = getVector(C, D);

    Point vecBC = getVector(B, C);
    Point vecBD = getVector(B, D);

    Point vecDA = getVector(D, A);
    Point vecDB = getVector(D, B);

    if(ccw(vecAB, vecBC) * ccw(vecAB, vecBD) == 0 && ccw(vecCD, vecDA) * ccw(vecCD, vecDB) == 0) {
        if(B <= A) swap(A, B);
        if(D <= C) swap(C, D);

        if(A <= D && C <= B) return 1;
        else return -1;
    }
    else if(ccw(vecAB, vecBC) * ccw(vecAB, vecBD) <= 0 && ccw(vecCD, vecDA) * ccw(vecCD, vecDB) <= 0) return 2;
    else return -1;
}

long double get_size(Point& vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Point get_meet(Point& A, Point& B, Point& C, Point& D) {
    Point ret;
    long double a, b, c, d, e, f;

    a = A.y - B.y;
    b = B.x - A.x;
    c = A.x * a + A.y * b;

    d = C.y - D.y;
    e = D.x - C.x;
    f = C.x * d + C.y * e;

    long double dn = a * e - b * d;

    ret = {((e * c - b * f) / dn), ((a * f - c * d) / dn)};

    return ret;
}

int main() {
    Point A, B, C, D;
    cin >> A.x >> A.y >> B.x >> B.y;
    cin >> C.x >> C.y >> D.x >> D.y;

    cout << fixed;
    cout.precision(15);

    if(is_cross(A, B, C, D) == 1) {
        cout << "1\n";

        Point unit_dir_vec_AB = {B.x - A.x, B.y - A.y};
        long double sz_AB = get_size(unit_dir_vec_AB);
        unit_dir_vec_AB /= sz_AB;

        Point unit_dir_vec_CD = {D.x - C.x, D.y - C.y};
        long double sz_CD = get_size(unit_dir_vec_CD);
        unit_dir_vec_CD /= sz_CD;

        if(unit_dir_vec_AB == unit_dir_vec_CD || unit_dir_vec_AB == unit_dir_vec_CD * (-1)) {
            if(B == C) cout << B.x << ' ' << B.y << '\n';
            else if(A == D) cout << A.x << ' ' << A.y << '\n';
        }
        else {
            if(A == C || A == D) cout << A.x << ' ' << A.y << '\n';
            else if(B == C || B == D) cout << B.x << ' ' << B.y << '\n';
        }
    }
    else if(is_cross(A, B, C, D) == 2) {
        cout << "1\n";
        
        Point X = get_meet(A, B, C, D);
        cout << X.x << ' ' << X.y << '\n';
    }
    else cout << "0\n";

    return 0;
}