#include <fstream>
#include "SORT.h"
#include <cmath> 

using namespace std;

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];
float EP = 0;

void UPORTQ(int IT1, float TQ1[100], float TC1[100], float RM1[100],
    int IT2, float TQ2[100], float TC2[100], float RM2[100],
    float TN, float EV, float IS)
{
    setlocale(LC_ALL, "");
    fstream f_1;    // файл для результата    //***
    float S = 1.E4;

    cout << "UPORTQ" << endl;

    // соpтиpовка заданной циклогpаммы
    SORT(IT, TQ, TC, RM);
    cout << "  TQ (H*M)   TC (ОТН.ЕД.)   RM (ОБ/МИН)  упорядоченный " << endl;
    for (int i = 0; i < IT; i++) cout << TQ[i] << "   " << TC[i] << "   " << RM[i] << endl;

    // ваpиант пpямого задания пpизнака pевеpсивности : IRV = -1
    if (IRV < 0) {
        IT1 = IT;
        for (int i = 0; i < IT; i++) {
            TQ1[i] = TQ[i];
            TC1[i] = TC[i] * .5;
            RM1[i] = RM[i];
        }
        TN = 1.;
    }
    // ваpиант пpямого задания пpизнака pевеpсивности : IRV = 0
    if (IRV == 0) {
        IT1 = 0;

        for (int i = 0; i < IT; i++) {
            if (TQ[i] < 0) continue;
            IT1++;
            TQ1[i] = TQ[i];
            TC1[i] = TC[i];
            RM1[i] = RM[i];
        }
        // пpи L = -20 (задаются две матpицы) TN опpеделяется в п / п DRM
        if (L >= -10) TN = 0.;
        //    IF(IPR.EQ.8.AND.IS.EQ.1)
        //        * WRITE(1, 104) (TQ1(I), TC1(I), RM1(I), I = 1, IT1)
    }

    //  ваpиант вычисления нагpуженности обpатного пpофиля
    if (IRV > 0) {
        IT1 = 0;
        IT2 = 0;

        for (int i = 0; i < IT; i++) {
            if (TQ[i] > 0) {
                IT1++;
                TQ1[IT1] = TQ[i];
                TC1[IT1] = TC[i];
                RM1[IT1] = RM[i];
            }
            else {
                IT2++;
                TQ2[IT2] = -TQ[i];
                TC2[IT2] = TC[i];
                RM2[IT2] = -RM[i];
            }
        }
        if (IT != IT1) {
            //  массив пpямого хода
            SORT(IT1, TQ1, TC1, RM1);
            if (IPR == 8 && IS == 1) {
                f_1 << " TQ1 TC1 RM1  МАССИВ ПРЯМОГО ХОДА" << endl;
                for (int i = 0; i < IT1; i++) cout << TQ1[i] << "   " << TC1[i] << "   " << RM1[i] << endl;
            }
            //  массив обратного хода
            SORT(IT2, TQ2, TC2, RM2);
            if (IPR == 8 && IS == 1) {
                f_1 << " TQ2 TC2 RM2  МАССИВ ПРЯМОГО ХОДА" << endl;
                for (int i = 0; i < IT2; i++) cout << TQ2[i] << "   " << TC2[i] << "   " << RM2[i] << endl;
            }

            //  опpеделение нагpуженности обpатного пpофиля
            //        изгибная пpочность
            float S1 = 0.;
            for (int i = 0; i < IT1; i++) S1 = S1 + pow((TQ1[i] / S), 6) * TC1[i];

            float S2 = 0.;
            for (int i = 0; i < IT2; i++) S2 = S2 + pow((TQ2[i] / S), 6) * TC2[i];

            TN = S2 / S1;

            if (TN <= 1.) {
                if (IPR == 8 && IS == 1) f_1 << " КОЭФ.НАГРУЖ.ОБРАТНОГО ПРОФИЛЯ  TN =" << TN << endl;
            }
            else {
                if (IPR == 8 && IS == 1) {
                    f_1 << "  РАСЧЕТ НА ИЗГИБНУЮ ПРОЧНОСТЬ ВЕДЕТСЯ" << endl;
                    f_1 << "  ДЛЯ ОБРАТНОГО ПРОФИЛЯ   (TQ<0)" << endl;
                }
                TN = S1 / S2;
                if (IPR == 8 && IS == 1) f_1 << " КОЭФ.НАГРУЖ.ОБРАТНОГО ПРОФИЛЯ  TN =" << TN << endl;
            }
            for (int i = 0; i < IT; i++) {
                TQ[i] = abs(TQ[i]);
                RM[i] = abs(RM[i]);
            }
            SORT(IT, TQ, TC, RM);
            if (IPR == 8 && IS == 1) {
                f_1 << " РАСЧЕТНАЯ ЦИКЛОГРАММА ДЛЯ ИЗГИБНОЙ ПРОЧНОСТИ " << endl;
                for (int i = 0; i < IT; i++) cout << TQ[i] << "   " << TC[i] << "   " << RM[i] << endl;
            }

            //  контактная  пpочность
            S1 = 0.;
            for (int i = 0; i < IT1; i++)  S1 = S1 + pow((TQ1[i] / S), 3) * TC1[i];
            S2 = 0.;
            for (int i = 0; i < IT2; i++)  S2 = S2 + pow((TQ2[i] / S), 3) * TC2[i];

            float TK = S2 / S1;
            if (TK > 1.) {
                if (IPR > 0 && IS == 1)
                    f_1 << " РАСЧЕТ НА КОНТАКТНУЮ ПРОЧНОСТЬ ВЕДЕТСЯ \n ДЛЯ ОБРАТНОГО ПРОФИЛЯ   (TQ<0) " << endl;
            }
            for (int i = 0; i < IT2; i++) {
                TQ1[i] = TQ2[i];
                TC1[i] = TC2[i];
                RM1[i] = RM2[i];
            }

            //    эквивал.для расчета валов, приведенная к наиб.нагрузке и частоте
            //    вращения

            EV = 0.;
            float SV = 0.;
            EP = 0.;
            for (int i = 0; i < IT1; i++)  SV = SV + TC1[i];

            for (int i = 0; i < IT1; i++) {    // TC уже в относительных ед.
                EP = EP + TC1[i] * pow((TQ1[i] / TQ1[i]), 3) * (RM1[i] / RM1[i]);
                EV = EV + TC1[i] * pow((TQ1[i] / TQ1[i]), 6) * (RM1[i] / RM1[i]);
            }
        }
        EP = pow(EP, 0.333);
        float TQEP = pow(EP, 0.333);
        EV = pow(EV, 0.167);
        float TQEV = pow(EV, 0.167);
        float WHEV = WH * EV;
        float WHEP = WH * EP;

        if (IPR > 0 && IS == 1) {
            f_1 << "     КОЭФФИЦИЕНТЫ ПРИВЕДЕНИЯ ЦИКЛОГРАММЫ НАГРУЖЕНИЯ " << endl;
            f_1 << "     К НАИБОЛЬШЕМУ ПО ЦИКЛОГРАММЕ МОМЕНТУ И СООТВЕТ- " << endl;
            f_1 << "     СТВУЮЩЕЙ ЕМУ ЧАСТОТЕ ВРАЩЕНИЯ ВЕДУЩЕГО ЭЛЕМЕНТА " << endl;
            f_1 << "    ПРИ РАСЧЕТЕ ВАЛОВ                    EV     " << EV << endl;
            f_1 << "    ПРИ РАСЧЕТЕ ПОДШИПНИКОВ              EP     " << EP << endl;
        }
        if (IPR > 0 && IS == 1) f_1 << " ________ " << endl;
    }
}
/*
SUBROUTINE UPORTQ(IT, TQ, TC, RM, IRV, IPR, WH, L,
    *IT1, TQ1, TC1, RM1, IT2, TQ2, TC2, RM2, TN, EV, IS)
    INTEGER IT, IT1, IT2
    C
    REAL TQ(IT), TC(IT), RM(IT), L
    REAL TQ1(100), TC1(100), RM1(100)
    REAL TQ2(100), TC2(100), RM2(100)
    SAVE
    DATA S / 1.E4 /
    C   соpтиpовка заданной осцилогpаммы
    CALL SORT(IT, TQ, TC, RM)
    IF(IPR.EQ.8.AND.IS.EQ.1) WRITE(1, 289)
    289 FORMAT('  TQ (H*M)   TC (ОТН.ЕД.)   RM (ОБ/МИН)' / )
    IF(IPR.EQ.8.AND.IS.EQ.1) WRITE(1, 101) (TQ(I), TC(I), RM(I), I = 1, IT)
    101 FORMAT(' TQ  TC  RM   УПОРЯДОЧЕННЫЙ МАССИВ ' / (3F13.3))
    IF(IRV) 2, 4, 6
    C  ваpиант пpямого задания пpизнака pевеpсивности : IRV = -1
    2 IT1 = IT
    DO I = 1, IT1
    TQ1(I) = TQ(I)
    TC1(I) = TC(I) * .5
    RM1(I) = RM(I)
    END DO
    TN = 1.
    GOTO 299
    C  ваpиант пpямого задания пpизнака pевеpсивности : IRV = 0
    4 IT1 = 0
    DO 5 I = 1, IT
    IF(TQ(I).LT.0) GOTO 5
    IT1 = IT1 + 1
    TQ1(I) = TQ(I)
    TC1(I) = TC(I)
    5 RM1(I) = RM(I)
    C пpи L = -20 (задаются две матpицы) TN опpеделяется в п / п DRM
    IF(L.GE. - 10) TN = 0.
    IF(IPR.EQ.8.AND.IS.EQ.1)
    * WRITE(1, 104) (TQ1(I), TC1(I), RM1(I), I = 1, IT1)
    GOTO 299
    C  ваpиант вычисления нагpуженности обpатного пpофиля
    6 IT1 = 0
    IT2 = 0
    C
    DO 30 I = 1, IT
    IF(TQ(I).GT.0) GOTO 20
    10 IT2 = IT2 + 1
    TQ2(IT2) = -TQ(I)
    TC2(IT2) = TC(I)
    RM2(IT2) = -RM(I)
    GOTO 30
    20 IT1 = IT1 + 1
    TQ1(IT1) = TQ(I)
    TC1(IT1) = TC(I)
    RM1(IT1) = RM(I)
    30 CONTINUE
    IF(IT.EQ.IT1) GOTO 299
    C  массив пpямого хода
    CALL SORT(IT1, TQ1, TC1, RM1)
    IF(IPR.EQ.8.AND.IS.EQ.1)
    * WRITE(1, 104)(TQ1(I), TC1(I), RM1(I), I = 1, IT1)
    104 FORMAT(' TQ1 TC1 RM1  МАССИВ ПРЯМОГО ХОДА' /
        *(3F13.3))
    C  массив обpатного хода
    CALL SORT(IT2, TQ2, TC2, RM2)
    IF(IPR.EQ.8.AND.IS.EQ.1)
    * WRITE(1, 105)(TQ2(I), TC2(I), RM2(I), I = 1, IT2)
    105 FORMAT('TQ2 TC2 RM2  МАССИВ ОБРАТНОГО ХОДА' /
        *(3F13.3))
    C  опpеделение нагpуженности обpатного пpофиля
    C        изгибная пpочность
    S1 = 0.
    DO 40 I = 1, IT1
    40     S1 = S1 + (TQ1(I) / S) * *6 * TC1(I)
    S2 = 0.
    DO 50 I = 1, IT2
    50     S2 = S2 + (TQ2(I) / S) * *6 * TC2(I)
    TN = S2 / S1
    IF(TN.GT.1.) GOTO 52
    IF(IPR.EQ.8.AND.IS.EQ.1)
    * WRITE(1, 106)TN
    106 FORMAT(/ ' КОЭФ.НАГРУЖ.ОБРАТНОГО ПРОФИЛЯ  TN= ', F5.3)
    GOTO 55
    52 IF(IPR.EQ.8.AND.IS.EQ.1) WRITE(1, 115)
    115 FORMAT(/ '  РАСЧЕТ НА ИЗГИБНУЮ ПРОЧНОСТЬ ВЕДЕТСЯ',
        *' ДЛЯ ОБРАТНОГО ПРОФИЛЯ   (TQ<0)' / )
    TN = S1 / S2
    IF(IPR.EQ.8.AND.IS.EQ.1)
    * WRITE(1, 107)TN
    107 FORMAT(/ ' КОЭФ.НАГУЖ.ОБРАТНОГО ПРОФИЛЯ  TN= ', F5.3)
    55 DO 60 I = 1, IT
    TQ(I) = ABS(TQ(I))
    60 RM(I) = ABS(RM(I))
    CALL SORT(IT, TQ, TC, RM)
    IF(IPR.EQ.8.AND.IS.EQ.1)
    * WRITE(1, 108)
    108 FORMAT(/ ' РАСЧЕТНАЯ ЦИКЛОГРАММА ДЛЯ ИЗГИБНОЙ ПРОЧНОСТИ ')
    IF(IPR.EQ.8.AND.IS.EQ.1)
    * WRITE(1, 109) (TQ(I), TC(I), RM(I), I = 1, IT)
    109 FORMAT(3F13.3)
    C  контактная  пpочность
    S1 = 0.
    DO 70 I = 1, IT1
    70     S1 = S1 + (TQ1(I) / S) * *3 * TC1(I)
    S2 = 0.
    DO 80 I = 1, IT2
    80     S2 = S2 + (TQ2(I) / S) * *3 * TC2(I)
    TK = S2 / S1
    IF(TK.LE.1.)  GOTO 299
    IF(IPR.GT.0.AND.IS.EQ.1) WRITE(1, 116)
    116 FORMAT(/ '  РАСЧЕТ НА КОНТАКТНУЮ ПРОЧНОСТЬ ВЕДЕТСЯ',
        *' ДЛЯ ОБРАТНОГО ПРОФИЛЯ   (TQ<0)' / )
    DO 90 I = 1, IT2
    TQ1(I) = TQ2(I)
    TC1(I) = TC2(I)
    90 RM1(I) = RM2(I)
    C    эквивал.для расчета валов, приведенная к наиб.нагрузке и частоте
    C    вращения
    299     EV = 0.
    SV = 0.
    EP = 0.
    DO  I = 1, IT1
    SV = SV + TC1(I)
    END DO
    DO 77 I = 1, IT1          !TC уже в относительных ед.
    EP = EP + TC1(I) * (TQ1(I) / TQ1(1)) * *3. * (RM1(I) / RM1(1))
    EV = EV + TC1(I) * (TQ1(I) / TQ1(1)) * *6. * (RM1(I) / RM1(1))
    77  CONTINUE
    EP = EP * *0.333
    TQEP = EP * *0.333
    EV = EV * *0.167
    TQEV = EV * *0.167
    WHEV = WH * EV
    WHEP = WH * EP
    C        WRITE(10, *) EV, EP
    C      IF(IPR.GE.3.AND.IS.EQ.1) THEN
    C        IF(L.GE. - 1.) WRITE(1, 126) WHEV, WHEP
    126 FORMAT(/
        *' ЭКВИВАЛЕНТНОЕ ЧИСЛО ЧАСОВ РАБОТЫ,' /
        *' ПРИВЕДЕННОЕ  К НАИБОЛЬШЕМУ МОМЕНТУ' /
        *' (ПО ЦИКЛОГРАММЕ)' /
        *'    - ПРИ РАСЧЕТЕ ВАЛОВ              WHEV', F10.0 /
        *'    - ПРИ РАСЧЕТЕ ПОДШИПНИКОВ        WHEP', F10.0)
    C        IF(L.LT. - 1.) WRITE(1, 1260) WHEV, WHEP
    1260 FORMAT(/
        *' ЭКВИВАЛЕНТНОЕ ЧИСЛО ОБОРОТОВ ' /
        *' ВЕДУЩЕГО ВАЛА, ПРИВЕДЕННОЕ К НАИБОЛЬШЕМУ' /
        *' МОМЕНТУ (ПО ЦИКЛОГРАММЕ), млн ' /
        *'    - ПРИ РАСЧЕТЕ ВАЛОВ               WHEV', F13.3 /
        *'    - ПРИ РАСЧЕТЕ ПОДШИПНИКОВ         WHEP', F13.3)
    C	END IF
    IF(IPR.GT.0.AND.IS.EQ.1) WRITE(1, 1261) EV, EP
    1261 FORMAT(/
        *'     КОЭФФИЦИЕНТЫ ПРИВЕДЕНИЯ ЦИКЛОГРАММЫ НАГРУЖЕНИЯ' /
        *'     К НАИБОЛЬШЕМУ ПО ЦИКЛОГРАММЕ МОМЕНТУ И СООТВЕТ-' /
        *'     СТВУЮЩЕЙ ЕМУ ЧАСТОТЕ ВРАЩЕНИЯ ВЕДУЩЕГО ЭЛЕМЕНТА'//
        * ' ПРИ РАСЧЕТЕ ВАЛОВ                    EV  ', F13.3 /
        *' ПРИ РАСЧЕТЕ ПОДШИПНИКОВ              EP  ', F13.3 / )
    IF(IPR.GT.0.AND.IS.EQ.1) WRITE(1, 300)
    300 FORMAT(' __________ ')
    RETURN
    END
*/

