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
    const unsigned long long n = 1000000;
    int nDraws = 10000;
    vector<Pkt> a;

    Pkt pkt[3];
    Pkt mc; // pkt pomocniczy do monte carlo

    Pkt vec;

    for (int j = 0; j <= n; j += 100000)
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
                pkt[2] = pkt[1];
            } else {
                pkt[1].x = pkt[0].x + vXO;
                pkt[1].y = pkt[0].y + vYO;
                pkt[2] = pkt[1];
            }
            suma += sqrt(pow(vXO, 2) + pow(vYO, 2));

            vec.x = vXO;
            vec.y = vYO;
            pkt[2].x += vec.x;
            pkt[2].y += vec.y;
        }

        cout << "Dla n: " << j << " 2PI: "<< 2 * M_PI << " My 2PI: " << suma << endl;
        cout << "Pkt koncowy: " << pkt[2].x << " " << pkt[2].y << "\n" << endl;
    }

    srand((unsigned)time(NULL));
    for (int j = 4; j <= n; j += 100000)
    {
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

    Dla n: 100000 2PI: 6.28319 My 2PI: 6.28312
    Pkt koncowy: 1 -2.7068e-07

    Dla n: 200000 2PI: 6.28319 My 2PI: 6.28316
    Pkt koncowy: 1 -1.554e-06

    Dla n: 300000 2PI: 6.28319 My 2PI: 6.28316
    Pkt koncowy: 0.999997 4.0669e-06

    Dla n: 400000 2PI: 6.28319 My 2PI: 6.28318
    Pkt koncowy: 1 7.8939e-06

    Dla n: 500000 2PI: 6.28319 My 2PI: 6.28319
    Pkt koncowy: 1 9.62964e-06

    Dla n: 600000 2PI: 6.28319 My 2PI: 6.28319
    Pkt koncowy: 1 -5.25781e-05

    Dla n: 700000 2PI: 6.28319 My 2PI: 6.28321
    Pkt koncowy: 1 -1.10911e-05

    Dla n: 800000 2PI: 6.28319 My 2PI: 6.2832
    Pkt koncowy: 1 -1.76424e-05

    Dla n: 900000 2PI: 6.28319 My 2PI: 6.28321
    Pkt koncowy: 1 4.46791e-05

    Dla n: 1000000 2PI: 6.28319 My 2PI: 6.28321
    Pkt koncowy: 1 -5.8419e-06

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