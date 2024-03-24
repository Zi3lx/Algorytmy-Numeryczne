#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int generateRandomNumber() 
{
    return rand() % 2; // 0-1
}

double monteCarlo(int n, int s, int N) 
{
    int safeReturns = 0;

    for (int i = 0; i < N; i++) 
    {
        int position = s;
        while (position != 0 && position != n + s) 
        {
            int direction = generateRandomNumber();

            if (direction == 0)
                position--; // Move south
            else
                position++; // Move north
        }

        if (position == 0)
            safeReturns++;
    }

    // Calculate the probability
    return static_cast<double>(safeReturns) / N;
}

int main() 
{
    int n = 2, s = 3;
    int tests = 10000;
    vector<vector<float>> matrix;
    
    srand((unsigned)time(NULL));
    double monte_carlo_proability = monteCarlo(n , s, tests);
    cout << monte_carlo_proability << endl;
}
