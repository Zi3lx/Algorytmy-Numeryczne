#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct Pkt {
    float x;
    float y;
};

float randomNumber()
{
    return (2.0 * (float)rand() / (float)RAND_MAX - 1.0);
}

float lenOfPoint(float a, float b)
{
    return sqrt(pow(a, 2) + pow(b, 2));
}

float lenOfPoint(Pkt pkt)
{
    return sqrt(pow(pkt.x, 2) + pow(pkt.y, 2));
}

int checkTheSign(float k)
{
    if(k < 0)
        return 1;
    return 0;
}

int main()
{
    // zmien zeby nie była cała tablica a max 2 pkt/ 3
    unsigned long long n = 100000 + 4;
    vector<Pkt> pointArr;

    Pkt pkt[3];
    Pkt mc; // pkt pomocniczy do monte carlo
    Pkt vec;
    vector<float> a[4];

    for (int j = 4; j <= n; j += 2000)
    {
        for (int i = 0; i < 4; i++)
            a[i].clear();
        
        if (j != 4)
            j -= 4;

        float kt = 2 * M_PI / j;

        float sums[4];

        vec.x = cos(kt)-1;
        vec.y = sin(kt);

        int helpX = checkTheSign(vec.x);
        int helpY = checkTheSign(vec.y)+ 2;

        a[helpX].push_back(vec.x);
        a[helpY].push_back(vec.y);

        Pkt vec0 = {vec.x, vec.y};

        pkt[0].x = 1;
        pkt[0].y = 0;
        
        pkt[1].x = cos(kt);
        pkt[1].y = sin(kt);

        float suma = 0;

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
            } else 
            {
                pkt[1].x = pkt[0].x + vXO;
                pkt[1].y = pkt[0].y + vYO;
                pkt[2] = pkt[1];
            }
            suma += lenOfPoint(vXO, vYO);

            vec.x = vXO;
            vec.y = vYO;

            vec0.x += vec.x;
            vec0.y += vec.y;

            int helpX = checkTheSign(vec.x);
            int helpY = checkTheSign(vec.y)+ 2;

            a[helpX].push_back(vec.x);
            a[helpY].push_back(vec.y);

            pkt[2].x += vec.x;
            pkt[2].y += vec.y;
        }

        for (int i = 0; i < 4; i++)
            sort(a[i].begin(), a[i].end());

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < a[i].size(); j++)
                sums[i] += a[i][j];

        //cout << "" << j << ";"<< 2 * M_PI << "; " << suma << endl;
        //cout << "" << pkt[2].x << "; " << pkt[2].y << "" << endl;
        //cout << vec0.x << "; " <<  vec0.y << endl;
        //cout << sums[0] + sums[1] << "; " << sums[2] + sums[3] << endl;
    }



    srand((unsigned)time(NULL));
    for (int j = 4; j <= n; j += 2000)
    {
        if (j != 4)
            j -= 4;
            
        for (int i = 0; i <= j; i++)
        {
            mc.x = randomNumber();
            mc.y = randomNumber();

            if (lenOfPoint(mc) < 1)
                pointArr.push_back(mc);
        }
        float estimatedPI = 4.0 * pointArr.size() / j;
        cout << j << "; " << pointArr.size() << "; " << M_PI << "; " << estimatedPI << endl;
        pointArr.clear();
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