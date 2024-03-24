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

vector<double> gauss_seidel(const vector<vector<double>>& A, const vector<double>& b, vector<double> x0, double tol = 1e-6, int max_iter = 1000) {
    int n = b.size();
    vector<double> x = x0;
    for (int iter = 0; iter < max_iter; iter++) 
    {
        vector<double> x_new(n, 0.0);
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) 
            {
                if (j != i)
                    sum += A[i][j] * x_new[j];
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        double error = 0.0;
        for (int i = 0; i < n; i++) 
        {
            error += abs(x_new[i] - x[i]);
        }
        if (error < tol) {
            return x_new;
        }
        x = x_new;
    }
    return x;
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

    srand((unsigned)time(NULL));
    double monte_carlo_proability = monteCarlo(n , s, tests);
    cout << monte_carlo_proability << endl;
}
