#include <iostream>
#include <math.h>
//#include "CE.h"
#include "FCBE.h"

using namespace std;

//     pасчет коэф., учитывающего pаспpеделение нагpузки между зубьями

extern int IST2, IST3, IZ1;
extern float ZVE1, ZVE2, X1, X2, X[2];

float AKHB0(float EPSA, float EPSG, float MN, float D1, float BW, float ZEPS, float FTH, float KHV, float FKE, float AAB)
{
    cout << "   AKHB0:       EPSA, EPSG, MN, D1, BW, ZEPS, FTH, KHV, FKE, IZ1, AAB = " << EPSA << "  " << EPSG << "  " << MN << "  " << D1 << "  " << BW << "  " << ZEPS << "  " << FTH << "  " << KHV << "  " << FKE << "  " << IZ1 << "  " << AAB << endl;
    
    float KK = 0;
    float KA = 1.;
    float CER = CE();

    float PSBD = BW / D1;
        //     IZ1 - признак расположения шестерни
        //          относительно входного момента

    if (IZ1 < 0) KK = -0.8;
    if (IZ1 == 0) KK = 0;
    if (IZ1 > 0) KK = 0.14;

    float FKZ = AAB * FCBE(IST2, BW);
    float FKY0 = FKE + FKZ;

    float akhb0 = .376 * BW * CER * FKY0 / (FTH * KA * KHV) + 1. + KK * PSBD * PSBD;

    return akhb0;
}
/*
FUNCTION AKHB0(ZVE1, ZVE2, X1, X2, EPSA, EPSG, MN, D1,
    *BW, ZEPS, FTH, KHV, IST2, IST3, FKE, IZ1, AAB)
    C     расчет коэф., учитывающего распределение
    C     нагрузки вдоль линии зацепления

    IMPLICIT REAL(K - N)
    SAVE
    KA = 1.
    CER = CE(ZVE1, ZVE2, X1, X2)



    WRITE(7, 7018) D1
    7018  FORMAT(' AKHB0: D1 ', 5X, 2F9.3)



    PSBD = BW / D1
    C     IZ1 - признак расположения шестерни
    C          относительно входного момента

    IF(IZ1) 10, 20, 30
    10   KK = -.8
    GOTO 40
    20   KK = .00
    GOTO 40
    30   KK = .14
    40 FKZ = AAB * FCBE(IST2, BW)
    FKY0 = FKE + FKZ


    WRITE(7, 7019) FTH, KA, KHV
    7019  FORMAT(' FTH, KA, KHV: AKHB0 ', 5X, 3F9.3)


    AKHB0 = .376 * BW * CER * FKY0 / (FTH * KA * KHV) + 1. + KK * PSBD * *2

    WRITE(7, 7020) AKHB0
    7020  FORMAT(' AKHB0: AKHB0 ', 5X, 2F9.3)

    RETURN
    END

*/