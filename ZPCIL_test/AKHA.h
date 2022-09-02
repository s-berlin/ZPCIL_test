#include <iostream>
#include <math.h>
#include <iomanip>
#include "CE.h"
#include "FPB.h"

using namespace std;

//     pасчет коэф., учитывающего pаспpеделение нагpузки между зубьями

extern int IST2;
extern float ZVE1, ZVE2, X1, X2, X[2];

float AKHA(float EPSA, float EPSG, float MN, float D1, float D2, float BW, float FTH, float KV, float KBE, float AAL, float& FPB1, float& FPB2)
{
    cout << "   AKHA:                  EPSA, EPSG, MN, D1, D2, BW, FTH, KHV, KHB, AAL = " << EPSA << "  " << EPSG << "  " << MN << "  " << D1 << "  " << D2 << "  " << BW << "  " << FTH << "  " << KV<< "  " << KBE << "  " << AAL << endl;
    float CER = CE();
    float CG = CER * (.75 * EPSA + .25);
    float KA = 1.;
    float YA = 0.;
    FPB1 = FPB(IST2, MN, D1);
    FPB2 = FPB(IST2, MN, D2);
    float FPBE = sqrt(FPB1 * FPB1 + FPB2 * FPB2);
    float CKVA = CG * BW * (AAL * FPBE - YA) / (FTH * KA * KV * KBE);
    float akha = CKVA * sqrt(2. * (EPSG - 1.) / EPSG) * .4 + .9;
    if (EPSG < 2.) akha = EPSG * (.9 + .4 * CKVA) / 2.;
    cout << "   AKHA: ***  ZVE1 = " << ZVE1 << "    ZVE2 = " << ZVE2 << "   X[0] = " << X[0] << "    X[1] = " << setprecision(4) << X[1] << endl;
    cout << "   AKHA: ***  CER = " << CER << "   CG = " << CG << "   FPB1 = " << FPB1 << "   FPB2 = " << FPB2 << "   FPBE = " << FPBE << "   CKVA = " << CKVA << "   akha = " << akha << endl;
    return akha;
}

/*
FUNCTION AKHA(ZVE1, ZVE2, X1, X2, EPSA, EPSG, MN, D1, D2,
    *BW, FTH, KV, KBE, IST2, AAL, FPB1, FPB2)
    C     pасчет коэф., учитывающего pаспpеделение
    C     нагpузки между зубьями
 
    IMPLICIT REAL(K - N)
    EXTERNAL CE, FPB
    SAVE
    CER = CE(ZVE1, ZVE2, X1, X2)
    CG = CER * (.75 * EPSA + .25)
    KA = 1.
    YA = 0.
    FPB1 = FPB(IST2, MN, D1)
    FPB2 = FPB(IST2, MN, D2)
    FPBE = SQRT(FPB1 * FPB1 + FPB2 * FPB2)
    CKVA = CG * BW * (AAL * FPBE - YA) / (FTH * KA * KV * KBE)
    AKHA = CKVA * SQRT(2. * (EPSG - 1.) / EPSG) * .4 + .9
    IF(EPSG.LT.2.) AKHA = EPSG * (.9 + .4 * CKVA) / 2.
    RETURN
    END
*/
