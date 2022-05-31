#include <iostream>
#include <math.h>
#include "CC.h"
#include "YFS.h"

using namespace std;

extern float DA1, DA2, DB1, DB2, ALFTW;
extern float Z1, Z2, U;                       
extern float MN, X1, X2, HA, AL;

// уточненный pасчет пpямозубых зубчатых колес

void KFAB0(float CAA[2], float CVV[2], float YFSA[2], float YFSU[2]) 
{
    float PI2 = 6.28318;
    float AA[2] = { 0,0 }, AP[2] = { 0,0 }, AV[2] = { 0,0 }, AU[2] = { 0,0 }, Z[2] = { 0,0 }, X[2] = { 0,0 };
    float HMA[2] = { 0,0 }, HMP[2] = { 0,0 }, HMV[2] = { 0,0 }, HMU[2] = { 0,0 }, DB[2] = { 0,0 };
    float CA[2] = { 0,0 }, CP[2] = { 0,0 }, CV[2] = { 0,0 }, CU[2] = { 0,0 };
 //   float CAA[2] = { 0,0 }, CVV[2] = { 0,0 }, YFSA[2] = { 0,0 }, YFSU[2] = { 0,0 };
  
    Z[0] = Z1;
    Z[1] = Z2;
    X[0] = X1;
    X[1] = X2;

    AA[0] = acos(DB1) / DA1;
    AA[1] = acos(DB2) / DA2;
    DB[0] = DB1;
    DB[1] = DB2;

    for (int i = 0; i < 2; i++) {
        //  J - COПPЯЖEHHOE ЗУБЧАТОЕ KOЛECO : I = 1  J = 2;   I = 2  J = 1;
        int j = i + 1;
        if(j == 2) j = 0;
        AP[i] = atan(tan(ALFTW) - (tan(AA[j]) - tan(ALFTW)) * Z[j] / Z[i]);
        AP[i] = atan(tan(ALFTW) - (tan(AA[j]) - tan(ALFTW)) * Z[j] / Z[i]);
        AV[i] = atan(tan(AA[i]) - PI2 / Z[i]);
        AU[i] = atan(tan(AP[i]) + PI2 / Z[i]);
        HMA[i] = 0.;
        HMP[i] = (1. / cos(AA[i]) - 1. / cos(AP[i])) * DB[i] * .5 / MN;
        HMV[i] = (1. / cos(AA[i]) - 1. / cos(AV[i])) * DB[i] * .5 / MN;
        HMU[i] = (1. / cos(AA[i]) - 1. / cos(AU[i])) * DB[i] * .5 / MN;
        
        CA[i] = CC(Z[i], X[i], HMA[i]);
        CP[i] = CC(Z[i], X[i], HMP[i]);
        CV[i] = CC(Z[i], X[i], HMV[i]);
        CU[i] = CC(Z[i], X[i], HMU[i]);
    }
    for (int i = 1; i < 2; i++) {
        int j = i + 1;
        if (j == 2) j = 0;
        
        CAA[i] = (CA[i] * CP[j]) / (CA[i] + CP[j]);
        CVV[i] = (CV[i] * CU[j]) / (CV[i] + CU[j]);
        YFSA[i] = YFS(Z[i], X[i], HMA[i], HA, AL);
        YFSU[i] = YFS(Z[i], X[i], HMU[i], HA, AL);
    }
   
}

/*
SUBROUTINE KFAB0(DA1, DA2, DB1, DB2, ALTW, Z1, Z2, X1, X2,
    *U, MN, HA, AL, CAA, CVV, YFSA, YFSU)
    C уточненный pасчет пpямозубых зубчатых колес
    IMPLICIT REAL(K - N)
    DIMENSION AA(2), AP(2), AV(2), AU(2), CA(2), CP(2), CV(2), CU(2),
    * CAA(2), CVV(2), DA(2), DB(2), X(2),
    * HMA(2), HMP(2), HMV(2), HMU(2), Z(2), YFSA(2), YFSU(2)
    EXTERNAL CC, YFS
    C        SAVE
    PI2 = 6.28318
    DA(1) = DA1
    DA(2) = DA2
    DB(1) = DB1
    DB(2) = DB2
    Z(1) = Z1
    Z(2) = Z2
    X(1) = X1
    X(2) = X2
    DO 10 I = 1, 2
    10 AA(I) = ACOS(DB(I) / DA(I))
    DO 20 I = 1, 2
    C  J - COПPЯЖEHHOE ЗУБЧАТОЕ KOЛECO : I = 1  J = 2;   I = 2  J = 1;
J = I + 1
IF(J.EQ.3) J = 1
AP(I) = ATAN(TAN(ALTW) - (TAN(AA(J)) - TAN(ALTW)) * Z(J) / Z(I))
AV(I) = ATAN(TAN(AA(I)) - PI2 / Z(I))
AU(I) = ATAN(TAN(AP(I)) + PI2 / Z(I))
HMA(I) = 0.
HMP(I) = (1. / COS(AA(I)) - 1. / COS(AP(I))) * DB(I) * .5 / MN
HMV(I) = (1. / COS(AA(I)) - 1. / COS(AV(I))) * DB(I) * .5 / MN
HMU(I) = (1. / COS(AA(I)) - 1. / COS(AU(I))) * DB(I) * .5 / MN
CA(I) = CC(Z(I), X(I), HMA(I))
CP(I) = CC(Z(I), X(I), HMP(I))
CV(I) = CC(Z(I), X(I), HMV(I))
CU(I) = CC(Z(I), X(I), HMU(I))
20 CONTINUE
DO 30 I = 1, 2
J = I + 1
IF(J.EQ.3) J = 1
CAA(I) = (CA(I) * CP(J)) / (CA(I) + CP(J))
CVV(I) = (CV(I) * CU(J)) / (CV(I) + CU(J))
YFSA(I) = YFS(Z(I), X(I), HMA(I), HA, AL)
YFSU(I) = YFS(Z(I), X(I), HMU(I), HA, AL)
30 CONTINUE
RETURN
*/
