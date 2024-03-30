#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

struct Points {
    double x;
    double y;
};

double randomNumber()
{
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

double length(Points v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

double length(double a, double b) {
    return sqrt(a*a + b*b);
}

int main()
{
    int n = 2030001; // liczba boków wielokąta
    Points mc;
    vector<Points> mc_points;
    vector<double> x_plus, x_minus, y_plus, y_minus;

    for (int j = 10000; j < n; j += 10000)
    {
        double theta = 2 * M_PI / j;

        Points w_prev = {cos(theta) - 1, sin(theta)};
        Points last_point = {1, 0};
        Points vecZero = {0, 0};
        double ob = 0;

        for (int i = 0; i < j; i++) 
        {
            Points vec = {
                cos(theta) * w_prev.x - sin(theta) * w_prev.y,
                sin(theta) * w_prev.x + cos(theta) * w_prev.y
            };
            last_point.x += vec.x;
            last_point.y += vec.y;
            vecZero.x += vec.x;
            vecZero.y += vec.y;
            (vec.x > 0) ? x_plus.push_back(vec.x) : x_minus.push_back(vec.x);
            (vec.y > 0) ? y_plus.push_back(vec.y) : y_minus.push_back(vec.y);
            ob += length(vec);
            w_prev = vec;
        }

        double Sx_plus = 0, Sx_minus = 0, Sy_plus = 0, Sy_minus = 0;
        
        for (double x : x_plus)
            Sx_plus += x;
        for (double x : x_minus)
            Sx_minus += x;
        for (double y : y_plus)
            Sy_plus += y;
        for (double y : y_minus)
            Sy_minus += y;

        double sum_x = Sx_plus + Sx_minus;
        double sum_y = Sy_plus + Sy_minus;

        double lengthOfSum = length(sum_x, sum_y);

        cout << j << "; "<< fixed << setprecision(16) << 2*M_PI << "; " << ob << ";"<< last_point.x << "; " << last_point.y << "; " << vecZero.x << "; " << vecZero.y << "; " << sum_x << "; " << sum_y;

        sort(x_plus.begin(), x_plus.end());
        sort(x_minus.begin(), x_minus.end(), greater<double>());
        sort(y_plus.begin(), y_plus.end());
        sort(y_minus.begin(), y_minus.end(), greater<double>());

        Sx_plus = 0; Sx_minus = 0; Sy_plus = 0; Sy_minus = 0;
        
        for (double x : x_plus)
            Sx_plus += x;
        for (double x : x_minus) 
            Sx_minus += x;
        for (double y : y_plus)
            Sy_plus += y;
        for (double y : y_minus)
            Sy_minus += y;
        
        double sum_x_sorted = Sx_plus + Sx_minus;
        double sum_y_sorted = Sy_plus + Sy_minus;

        double lengthSortedSum = length(sum_x_sorted, sum_x_sorted);

        cout << "; " << sum_x_sorted << "; " << sum_y_sorted;

        priority_queue<double, vector<double>, greater<double> > x_plus_queue(x_plus.begin(), x_plus.end());
        priority_queue<double, vector<double>, greater<double> > y_plus_queue(y_plus.begin(), y_plus.end());

        Sx_plus = 0; Sx_minus = 0; Sy_plus = 0; Sy_minus = 0;
        
        while (!x_plus_queue.empty()) {
            Sx_plus += x_plus_queue.top();
            x_plus_queue.pop();
        }
        while (!x_minus.empty()) {
            Sx_minus += x_minus.back();
            x_minus.pop_back();
        }
        while (!y_plus_queue.empty()) {
            Sy_plus += y_plus_queue.top();
            y_plus_queue.pop();
        }
        while (!y_minus.empty()) {
            Sy_minus += y_minus.back();
            y_minus.pop_back();
        }

        double x_queue_sum = Sx_plus + Sx_minus;
        double y_queue_sum = Sy_plus + Sy_minus;
        double lenOfQueue = length(x_queue_sum, y_queue_sum);

        cout << ";" << x_queue_sum << ";" << y_queue_sum << ";" << lengthOfSum << ";" << lengthSortedSum << ";" << ((lengthSortedSum < lengthOfSum) ? 1 : 0) << ";" << lenOfQueue << ";" << ((lenOfQueue < lengthOfSum) ? 1 : 0) << "; bład" << abs(2*M_PI - ob) << ";" << endl;
        srand((unsigned)time(NULL));

        /*for (int i = 0; i < j; i++)
        {
            mc.x = randomNumber();
            mc.y = randomNumber();


            if (length(mc) < 1)
                mc_points.push_back(mc);
        }
        double estimatedPI = 4.0 * mc_points.size() / j;
        cout << j << ";" << estimatedPI << "; " << mc_points.size() << endl;
        mc_points.clear();
        x_plus.clear();
        x_minus.clear();
        y_plus.clear(); 
        y_minus.clear();*/
    }
}