// перевод угла из Град.МинСек в радианы
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>

using namespace std;

float ZPGR(float AL)
{
    cout << "ZPGR: AL =" << AL << endl;
    int K = AL;
    float A = (AL - K) * 100;
    cout << "ZPGR: K =" << K << "    A =" << A << endl;

    if (A >= 60) { A = 0; K = K + 1;}

    int N = A;
    float AS = A - N;
    cout << "ZPGR: N =" << N << "    AS =" << AS << endl;
    
    if (AS >= 60) { AS = 0; N = N + 1;}

    AL = (K + (N + AS / 60. * 100.) / 60.) * 0.017453292;
    cout << "ZPGR: AL =" << AL << endl;
    return AL;
}

/*
    C     pEPEBOd uglA iz gPAd.MiH.CEK.B PAdiAHy
        IF(G.EQ.0.) GOTO 2
        K = INT(G)
        A = (G - K) * 100.
        IF(A.LT.61.) GOTO 3
        A = 0.
        K = K + 1
        3 N = INT(A)
        AS = A - N
        IF(AS.LT.0.61) GOTO 4
        AS = 0.
        N = N + 1
        4 G = (K + (N + AS / 60. * 100.) / 60.) * 0.017453292
        2 RETURN
        END
        */
