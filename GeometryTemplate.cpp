#include<bits/stdc++.h>

using namespace std;
#define ll long long
#define PI acos(-1)
ll INF = 1e18;
struct Point{
    ll x , y;
    Point(ll _x , ll _y){
        x = _x; y = _y;
    }
};
vector < Point > points;

double radianToDegree(double x){
    return (x * 180)/PI;
}

/// areaOfTriangle of polygon
double polygonareaOfTriangle(int n) {
    double areaOfTriangle = 0.0;
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        areaOfTriangle += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i;
    }
    return abs(areaOfTriangle / 2.0);
}
///areaOfTriangle of triangle
double areaOfTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

///Three points are collinear
bool collinear(int x1, int y1, int x2,  int y2, int x3, int y3) {
    if ((y3 - y2) * (x2 - x1) ==  (y2 - y1) * (x3 - x2))
        return true;
    else
        return false;
}


/// Given three colinear points p, q, r, the function checks if
/// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    else return false;
}

/// To find orientation of ordered triplet (p, q, r).
/// The function returns following values
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  /// colinear
    return (val > 0)? 1: 2; /// clock or counterclock wise
}


/// The function that returns true if line segment 'p1q1'
/// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}

/// Returns true if the point p lies inside the polygon[] with n vertices
bool ispointInPolygon(Point polygon[], int n, Point p) {
    // There must be at least 3 vertices in polygon[]
    if (n < 3)  return false;

    // Create a point for line segment from p to infinite
    Point extreme = {INF, p.y};

    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;

        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[next]) == 0)
               return onSegment(polygon[i], p, polygon[next]);

            count++;
        }
        i = next;
    } while (i != 0);

    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
}

/// function to find if given point
/// lies inside a given rectangle or not.
/// bottom-left and top-right corners of rectangle and the points
bool FindPointInRactangle(int x1, int y1, int x2, int y2, int x, int y) {
    if (x > x1 and x < x2 and y > y1 and y < y2)
        return true;
    else return false;
}

///* A function to check whether point P(x, y) lies inside the triangle formed
///   by A(x1, y1), B(x2, y2) and C(x3, y3) */
bool pointInTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y){
   /* Calculate areaOfTriangle of triangle ABC */
   double A = areaOfTriangle (x1, y1, x2, y2, x3, y3);

   /* Calculate areaOfTriangle of triangle PBC */
   double A1 = areaOfTriangle (x, y, x2, y2, x3, y3);

   /* Calculate areaOfTriangle of triangle PAC */
   double A2 = areaOfTriangle (x1, y1, x, y, x3, y3);

   /* Calculate areaOfTriangle of triangle PAB */
   double A3 = areaOfTriangle (x1, y1, x2, y2, x, y);

   /* Check if sum of A1, A2 and A3 is same as A */
   return (A == A1 + A2 + A3);
}
/// ax + by = c
/// It will return {c , {a, b}} that will indicate line.
pair < ll , pair < ll , ll > >lineByTwoPoint(pair < ll , ll > a , pair < ll , ll > b){
    if(a.first == b.first){
        return make_pair(a.first,make_pair(0,0));
    }
    if(a.second == b.second){
        return make_pair(a.second,make_pair(1,0));
    }
    auto w = a;
    auto e = b;
    if(w.first > e.first)swap(w,e);
    ll dx = e.first - w.first;
    ll dy = e.second - w.second;
    ll we = __gcd(dx,dy);
    dx /= we;
    dy /= we;
    ll poi = dx*w.second + (dy)*(-w.first);
    return make_pair(poi,make_pair(dx,dy));
}
///Square length of two point
ll lengthSquare(pair<ll,ll> X, pair<ll,ll> Y) {
    ll xDiff = X.first - Y.first;
    ll yDiff = X.second - Y.second;
    return xDiff*xDiff + yDiff*yDiff;
}

/// Return angle of triangle in degree.
pair < double , pair < double , double > > allAngleOfTriange(pair<ll,ll> A, pair<ll,ll> B, pair<ll,ll> C){
// Square of lengths be a2, b2, c2
    ll a2 = lengthSquare(B,C);
    ll b2 = lengthSquare(A,C);
    ll c2 = lengthSquare(A,B);
    pair < double , pair < double , double > > res;
    // lenght of sides be a, b, c
    double a = sqrt(a2);
    double b = sqrt(b2);
    double c = sqrt(c2);

    // From Cosine law
    double alpha = acos((b2 + c2 - a2)/(2*b*c));
    double betta = acos((a2 + c2 - b2)/(2*a*c));
    double gamma = acos((a2 + b2 - c2)/(2*a*b));

    // Converting to degree
    alpha = alpha * 180 / PI;
    betta = betta * 180 / PI;
    gamma = gamma * 180 / PI;

    // printing all the angles
    res.first = alpha;
    res.second.first = betta;
    res.second.second = gamma;
    return res;
}

///Overlapping area of rectangle

int overlappingArea(Point l1, Point r1,Point l2, Point r2){
    // Area of 1st Rectangle
    int area1 = abs(l1.x - r1.x) *
                abs(l1.y - r1.y);

    // Area of 2nd Rectangle
    int area2 = abs(l2.x - r2.x) *
                abs(l2.y - r2.y);

    // Length of intersecting part i.e
    // start from max(l1.x, l2.x) of
    // x-coordinate and end at min(r1.x,
    // r2.x) x-coordinate by subtracting
    // start from end we get required
    // lengths
    int areaI = (min(r1.x, r2.x) -
                 max(l1.x, l2.x)) *
                (min(r1.y, r2.y) -
                 max(l1.y, l2.y));

    return (area1 + area2 - areaI);
}


/*
Circumcenter of triangle: https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
Third side of Triangle : https://www.geeksforgeeks.org/program-find-third-side-triangle-using-law-cosines/








*/

int main()
{

}

