#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct Points {
    float x;
    float y;
};

float randomNumber()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float length(Points v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

int main()
{
    int n = 1000; // liczba boków wielokąta
    Points mc;
    vector<Points> mc_points;
    vector<float> x_plus, x_minus, y_plus, y_minus;

    for (int j = 1010; j < 10001; j += 10000000)
    {
        float theta = 2 * M_PI / j;

        Points w_prev = {cos(theta) - 1, sin(theta)};
        Points last_point = {1, 0};
        Points vecZero = {0, 0};
        float ob = 0;

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

        float Sx_plus = 0, Sx_minus = 0, Sy_plus = 0, Sy_minus = 0;
        
        for (float x : x_plus)
            Sx_plus += x;
        for (float x : x_minus)
            Sx_minus += x;
        for (float y : y_plus)
            Sy_plus += y;
        for (float y : y_minus)
            Sy_minus += y;

        float sum_x = Sx_plus + Sx_minus;
        float sum_y = Sy_plus + Sy_minus;

        cout << j << "; " << 2*M_PI << "; " << ob << "; " << last_point.x << "; " << last_point.y << "; " << vecZero.x << "; " << vecZero.y << "; " << sum_x << "; " << sum_y;

        sort(x_plus.begin(), x_plus.end());
        sort(x_minus.begin(), x_minus.end(), greater<float>());
        sort(y_plus.begin(), y_plus.end());
        sort(y_minus.begin(), y_minus.end(), greater<float>());

        Sx_plus = 0; Sx_minus = 0; Sy_plus = 0; Sy_minus = 0;
        
        for (float x : x_plus)
            Sx_plus += x;
        for (float x : x_minus) 
            Sx_minus += x;
        for (float y : y_plus)
            Sy_plus += y;
        for (float y : y_minus)
            Sy_minus += y;

        float sum_x_sorted = Sx_plus + Sx_minus;
        float sum_y_sorted = Sy_plus + Sy_minus;

        cout << "; " << sum_x_sorted << "; " << sum_y_sorted;


        srand((unsigned)time(NULL));

        for (int i = 0; i < j; i++)
        {
            mc.x = randomNumber();
            mc.y = randomNumber();


            if (length(mc) < 1)
                mc_points.push_back(mc);
        }
        float estimatedPI = 4.0 * mc_points.size() / j;
        cout << "; " << j << "; " << estimatedPI << "; " << mc_points.size() << endl;
        mc_points.clear();
        x_plus.clear();
        x_minus.clear();
        y_plus.clear(); 
        y_minus.clear();
    }
}