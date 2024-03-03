#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>

using namespace std;

struct Pkt {
    float x;
    float y;
};

int lenOfPoint(Pkt pkt)
{
    return sqrt(pow(pkt.x, 2) + pow(pkt.y, 2));
}

int main()
{
    // zmien zeby nie była cała tablica a max 2 pkt/ 3
    const unsigned long long n = 1000000 + 4;
    int nDraws = 10000;
    vector<Pkt> a;

    Pkt pkt[2];
    Pkt mc; // pkt pomocniczy do monte carlo

    Pkt vec;

    for (int j = 4; j <= n; j += 100000)
    {
        double kt = 2 * M_PI / j;

        vec.x = cos(kt)-1;
        vec.y = sin(kt);

        pkt[0].x = 1;
        pkt[0].y = 0;
        
        pkt[1].x = cos(kt);
        pkt[1].y = sin(kt);

        double suma = 0;

        for (int i = 2; i <= j; i++)
        {
            int help = i % 2;

            float vXO = cos(kt) * vec.x - (sin(kt) * vec.y);
            float vYO = sin(kt) * vec.x + (cos(kt) * vec.y);
            
            if (help == 0)
            {
                pkt[0].x = pkt[1].x + vXO;
                pkt[0].y = pkt[1].y + vYO;
            } else {
                pkt[1].x = pkt[0].x + vXO;
                pkt[1].y = pkt[0].y + vYO;
            }
            suma += sqrt(pow(vXO, 2) + pow(vYO, 2));

            vec.x = vXO;
            vec.y = vYO;
        }

        cout << "Dla n: " << j << " 2PI: "<< 2 * M_PI << " My 2PI: " << suma << endl;
        cout << "Pkt koncowy: " << pkt[1].x << " " << pkt[1].y << "\n" << endl;
    }
    for (int j = 4; j <= n; j += 100000)
    {
        srand((unsigned)time(NULL));
        for (int i = 0; i < j; i++)
        {
            mc.x = (2.0 * (double)rand() / (double)RAND_MAX - 1.0);
            mc.y = (2.0 * (double)rand() / (double)RAND_MAX - 1.0);

            if (lenOfPoint(mc) < 1)
                a.push_back(mc);
        }
        double estimatedPI = 4.0 * a.size() / j;
        cout << "Ilosc lososwanych: "<< j << " Ilość pkt < 1: " << a.size() << endl;
        cout << "PI: " << M_PI << " My PI: " << estimatedPI << "\n" << endl;
        a.clear();
    }
}

/*
H1. TAK
    Dla n: 4 2PI: 6.28319 My 2PI: 4.24264
    Pkt koncowy: 0 -1

    Dla n: 100004 2PI: 6.28319 My 2PI: 6.28313
    Pkt koncowy: 1 -6.37789e-05

    Dla n: 200004 2PI: 6.28319 My 2PI: 6.28316
    Pkt koncowy: 1 -3.28444e-05

    Dla n: 300004 2PI: 6.28319 My 2PI: 6.28317
    Pkt koncowy: 0.999997 -1.61865e-05

    Dla n: 400004 2PI: 6.28319 My 2PI: 6.28318
    Pkt koncowy: 1 -6.63241e-06

    Dla n: 500004 2PI: 6.28319 My 2PI: 6.28319
    Pkt koncowy: 1 -2.83046e-06

    Dla n: 600004 2PI: 6.28319 My 2PI: 6.28319
    Pkt koncowy: 0.999999 -6.40076e-05

    Dla n: 700004 2PI: 6.28319 My 2PI: 6.28321
    Pkt koncowy: 1 -1.74119e-05

    Dla n: 800004 2PI: 6.28319 My 2PI: 6.2832
    Pkt koncowy: 1 -2.35032e-05

    Dla n: 900004 2PI: 6.28319 My 2PI: 6.28321
    Pkt koncowy: 0.999999 3.81297e-05

    Dla n: 1000004 2PI: 6.28319 My 2PI: 6.28321
    Pkt koncowy: 1 -1.25445e-05

H2.

H3.

H4. Z moich testw wynika ze NIE
    Ilosc lososwanych: 4 Ilość pkt < 1: 2
    PI: 3.14159 My PI: 2

    Ilosc lososwanych: 100004 Ilość pkt < 1: 78546
    PI: 3.14159 My PI: 3.14171

    Ilosc lososwanych: 200004 Ilość pkt < 1: 156936
    PI: 3.14159 My PI: 3.13866

    Ilosc lososwanych: 300004 Ilość pkt < 1: 235385
    PI: 3.14159 My PI: 3.13842

    Ilosc lososwanych: 400004 Ilość pkt < 1: 313936
    PI: 3.14159 My PI: 3.13933

    Ilosc lososwanych: 500004 Ilość pkt < 1: 392424
    PI: 3.14159 My PI: 3.13937

    Ilosc lososwanych: 600004 Ilość pkt < 1: 470966
    PI: 3.14159 My PI: 3.13975

    Ilosc lososwanych: 700004 Ilość pkt < 1: 549267
    PI: 3.14159 My PI: 3.13865

    Ilosc lososwanych: 800004 Ilość pkt < 1: 627605
    PI: 3.14159 My PI: 3.13801

    Ilosc lososwanych: 900004 Ilość pkt < 1: 706131
    PI: 3.14159 My PI: 3.13835

    Ilosc lososwanych: 1000004 Ilość pkt < 1: 784622
    PI: 3.14159 My PI: 3.13848
*/