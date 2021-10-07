// перевод угла из радиан в Град.МинСек
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>

using namespace std;

void ZPRGMS(float AL, float &GRM, int &SEC)
{
    // AL   - угол в радианах
    // GRM - Град.Мин угла
    // SEC  - Сек угла

    cout << "ZPRGMS: AL =" << AL << endl;

    GRM = AL * 57.295779;

    int K = GRM;
    float A = (GRM - K) * 60.;
    cout << "ZPRGMS: GRM = " << GRM << "     K = " << K << "     A = " << A << endl;

    int N = A;
    SEC = (A - N) * 60 + 0.5;
    cout << "ZPRGMS: N = " << N << "     SEC = " << SEC << endl;

    if (SEC >= 60) { SEC = 0; N = N + 1; }
    if (N >= 60) { N = 0; K = K + 1; }

    GRM = K + 0.01 * N;

    cout << "ZPRGMS: GRM = " << GRM << "   SEC = " << SEC << endl;
}

/*
          SUBROUTINE ZPRGMS(ALF,ALGM,ALS)


C     AL-ugOl B PAd.*ALGM-gPAd.MiH.uglA
C     ALS-CEK.uglA*pE~ATx ALGM pO F6.2;ALS pO F3.2
      AL=ALF
      IF(AL.EQ.0) GOTO 2
      AL=AL*57.295779
      K=INT(AL)
      A=(AL-K)*60.
      N=INT(A)
      ALS=(A-N)*0.6
      IF(ALS.LT.0.595) GOTO 3
      ALS=0.
      N=N+1
    3 IF(N.LT.60) GOTO 4
      N=0
      K=K+1
    4 ALGM=K+0.01*N
      GOTO 1
    2 ALGM=0.00
      ALS=0.00
    1 RETURN
      END
*/
    
