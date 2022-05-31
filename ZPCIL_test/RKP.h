// ================ Расчет  кинематических параметров =================

#include <iostream>
using namespace std;

extern float Z1, Z2;                        // числа зубьев шестерни и колеса
extern float MN, BE, X1, X2, X[2];          // модуль, угол наклона, коэффициенты смещения

void RKP(float U, float DB[2], float TGAA[2], float ROP[2], float TGATW, float RL[2], float ROW[2], float TGAU[2], float PALF, float PX, float TETP[2], float TETV[2], float DZTP[2], float DZTV[2]) {
    double VFAN1[2], VFUN1[2], VFPN1[2], VFVN1[2], VSUN1[2], VSAN1[2];
    double PI = 3.1415926;
    
    for (int i = 0; i < 2; i++) {
        VFAN1[i] = PI / 60 * DB[i] * TGAA[i];
        if (i == 1) VFAN1[i] = VFAN1[i] / U;
        VFPN1[i] = PI / 30 * ROP[i];
        if (i == 1) VFPN1[i] = VFPN1[i] / U;
        VSAN1[i] = PI / 60 / U * DB[i] * (TGAA[i] - TGATW) * (U + 1.);
    }
    TETP[0] = -(TGAA[1] - TGATW) * (U + 1.) / (TGATW - U * (TGAA[1] - TGATW));
    TETP[1] = -(TGAA[0] - TGATW) * (U + 1.) / (U * TGATW - (TGAA[0] - TGATW));
    DZTP[0] = 1 / sqrt((1. - RL[1] / ROW[0]) * (1. + RL[1] / ROW[1]));
    DZTP[1] = 1 / sqrt((1. + RL[0] / ROW[0]) * (1. - RL[0] / ROW[1]));
    if (BE == 0) {
        for (int i = 0; i < 2; i++) {
            VFUN1[i] = PI / 60 * DB[i] * TGAU[i];
            if (i == 1) VFUN1[i] = VFUN1[i] / U;
            VFVN1[1 - i] = PI / 30 * (0.5 * (DB[0] + DB[1]) * TGATW - (ROP[i] + PALF));
            VSUN1[i] = PI / (60 * U) * DB[i] * (TGAU[i] - TGATW) * (U + 1.);       
        }

        VFVN1[1] = VFVN1[1] / U;

        TETV[0] = -(TGAU[1] - TGATW) * (U + 1.) / (TGATW - U * (TGAU[1] - TGATW));
        TETV[1] = -(TGAU[0] - TGATW) * (U + 1.) / (U * TGATW - (TGAU[0] - TGATW));
//      DZTV(1) = 1 / SQRT((1. - (PALF - RL(1)) / ROW(1)) * (1. + (PALF - RL(1)) / ROW(2)))
//      DZTV(2) = 1 / SQRT((1. + (PALF - RL(2)) / ROW(1)) * (1. - (PALF - RL(2)) / ROW(2)))
        DZTV[0] = 0.;
        DZTV[1] = 0.;
    }
}

/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C            Расчет  кинематических параметров                  C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
SUBROUTINE RKP(BET, U, DB, TGAA, ROP, TGATW, RL, ROW, TGAU,
    *PALF, PX, TETP, TETV, DZTP, DZTV)
    DIMENSION DB(2), RL(2), ROP(2),
    * TGAA(2), TGAU(2), ROW(2),
    * VFAN1(2), VFUN1(2), VFPN1(2), VFVN1(2), VSUN1(2), VSAN1(2),
    * TETP(2), TETV(2), DZTP(2), DZTV(2)
    SAVE
    C        print*, ' BET,U,DB,TGAA,ROP,TGATW,RL,ROW,TGAU'
    C        print*, BET, U, DB, TGAA, ROP, TGATW, RL, ROW, TGAU
    C        print*, ' PALF,PX  ', PALF, PX
    PI = 3.1415926
    DO 1 I = 1, 2
    VFAN1(I) = PI / 60 * DB(I) * TGAA(I)
    IF(I.EQ.2) VFAN1(I) = VFAN1(I) / U
    VFPN1(I) = PI / 30 * ROP(I)
    IF(I.EQ.2) VFPN1(I) = VFPN1(I) / U
    VSAN1(I) = PI / 60 / U * DB(I) * (TGAA(I) - TGATW) * (U + 1.)
    1 CONTINUE
    C        print*, ' VFAN1,VFPN1,VSAN1 '
    C        print*, VFAN1, VFPN1, VSAN1
    TETP(1) = -(TGAA(2) - TGATW) * (U + 1.) / (TGATW - U * (TGAA(2) - TGATW))
    TETP(2) = -(TGAA(1) - TGATW) * (U + 1.) / (U * TGATW - (TGAA(1) - TGATW))
    DZTP(1) = 1 / SQRT((1. - RL(2) / ROW(1)) * (1. + RL(2) / ROW(2)))
    DZTP(2) = 1 / SQRT((1. + RL(1) / ROW(1)) * (1. - RL(1) / ROW(2)))
    C        print*, ' TETP,DZTP  ', TETP, DZTP
    IF(BET.NE.0.) GOTO 3
    DO 2 I = 1, 2
    VFUN1(I) = PI / 60 * DB(I) * TGAU(I)
    IF(I.EQ.2) VFUN1(I) = VFUN1(I) / U
    VFVN1(2 / I) = PI / 30 * (0.5 * (DB(1) + DB(2)) * TGATW - (ROP(I) + PALF))
    VSUN1(I) = PI / (60 * U) * DB(I) * (TGAU(I) - TGATW) * (U + 1.)
    2 CONTINUE
    VFVN1(2) = VFVN1(2) / U
    C        print*, ' VFUN1,VFUN1,VSUN1 '
    C        print*, VFUN1, VFUN1, VSUN1
    TETV(1) = -(TGAU(2) - TGATW) * (U + 1.) / (TGATW - U * (TGAU(2) - TGATW))
    TETV(2) = -(TGAU(1) - TGATW) * (U + 1.) / (U * TGATW - (TGAU(1) - TGATW))
    C      DZTV(1) = 1 / SQRT((1. - (PALF - RL(1)) / ROW(1)) * (1. + (PALF - RL(1)) / ROW(2)))
    C      DZTV(2) = 1 / SQRT((1. + (PALF - RL(2)) / ROW(1)) * (1. - (PALF - RL(2)) / ROW(2)))
    DZTV(1) = 0.
    DZTV(2) = 0.
    C        print*, ' TETV,DZTV  ', TETV, DZTV
    3  CONTINUE
    RETURN
    END
*/

