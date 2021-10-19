#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include "SCT.h"
#include "ARC.h"
#include "DXS.h"
#include "CNT1.h"
#include "DOP1L.h"

using namespace std;

//========== Переменные по редуктору
extern char IR[20];
extern int IT, IRV, IPR, IE, ISR, IN, N1R;
extern float L, WH;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];

extern fstream f_1;    // файл для результата    //***

//========== Переменные по ступени
extern int IVP;                             // тип ступени
extern float Z1, Z2;                        // числа зубьев шестерни и колеса
extern float MN, BE, X1, X2, X[2];          // модуль, угол наклона, коэффициенты смещения
extern int flaw;
extern float AW, B1, B2;                    // межосевое расстояние ширины шестерни и колеса
extern float AL, HA, HL, CZV;               // угол профиля, коэффициенты: высоты головки, граничной высоты, радиального зазора  
extern int IST1, IST2, IST3, IST4, IST5;    // степени точности по нормам: кинематики, плавности, контакта; вид сопряжения, вид допуска на боковой зазор
extern int IMD, IKG;                        // коэф. наличия массивных деталей, номер схемы по упрощенному методу
extern float SHLM1, SHPM1, SFLB1, SFPM1;    // шестерня: предел конт. выносливости, допуск. конт. напряжение при макс. нагрузке, баз. предел выносл-и при изгибе, предел. баз. напряжение изгиба при макс. нагрузке 
extern float SHLM2, SHPM2, SFLB2, SFPM2;    // колесо:   - " -    - " -    - " -    - " -
extern int IG1, IG2;                        // группы материала шестерни и колеса
extern float H1, HK1, HT1, SHER1, YZ1;      // шестерня: твердость поверхности, твердость сердцевины, толщина упрочненного слоя, шероховатость, коэф. способа получения заготовки
extern float YT1, YR1, SHV1;                // шестерня: технологический коэффициент, шероховатость переходной поверхности, коэф. запаса прочности
extern float H2, HK2, HT2, SHER2, YZ2;      // колесо: твердость поверхности, твердость сердцевины, толщина упрочненного слоя, шероховатость, коэф. способа получения заготовки
extern float YT2, YR2, SHV2;                // колесо: технологический коэффициент, шероховатость переходной поверхности, коэф. запаса прочности
extern int IMF1, IMF2, IVR;                 // признаки шлифования переходной поверхности шестерни и колеса, Признак задания коэф-та запаса по контактной выносливости
extern float CZ1, CZ2, KSP, KPD, PR;        // числа зацеплений за оборот шестерни и колеса, коэф. силового потока, КПД, вероятность неразрушения по изгибной выносливости
extern float LO, S1, FKE, GM;               // расстояние между опорами, расстояние от опоры со стороны подвода момента до центра шестерни, ?, ?
extern int IQ, IP, IZ1, IG;                 // тип приложения момента, тип подшипника, ?, ?

void GEOM(int NW)
{
    fstream fi;
    float BBWW[2] = { 0,0 }, BW = 0;
    float DW[2] = {}, D[2] = {}, DA[2] = {}, DB[2] = {}, DF[2] = {};
    float DL[2] = {}, DP[2] = {}, DG[2] = {};
    float DLTH[2] = {}, TGAA[2] = {}, EA[2] = {}, HZ = 0;
    float ROG[2] = {}, TGAG[2] = {}, ROL[2] = {}, ROP[2] = {}, ZN[2];
    float W[2] = {}, ROWN[2] = {}, DWN[2] = {};
    float XMIN[2] = {}, XMINR[2] = {}, BETA[2] = {}, SNA[2] = {};
    float DU[2] = {}, TGAU[2] = {}, ROW[2] = {}, TGAV[2] = {}, DV[2] = {}, RL[2] = {};
    float SC[2] = {}, ROS[2] = {}, DS[2] = {}, HH[2] = {};
    float DY[2] = {}, TGALY = 0, STY = 0, CSBY, PSIYV = 0, SY[2] = {}, HAY[2] = {};
    float FR[2] = {}, TH[2] = {}, TWM[2] = {}, TW[2] = {}, ECS[2] = {}, TC_[2] = {}, EHS[2] = {};
    float EWS1[2] = {}, EWS2[2] = {}, EWS[2] = {};
    float DLTHMN[2] = {}, DLTHMX[2] = {};

    float EPBET, EPGAM, BETB, EPAM;
    float PI = 3.1415927;
    int KST[3] = {0,0,0};
    float Z[2] = {0,0}, X[2] = {0,0};
    float ALF = 0;
    float SNAL = 0, CSAL = 0, TGAL = 0, SNB = 0, CSB = 0, TGB = 0, SNAT = 0, CSAT = 0, TGAT = 0;
    float UU = 0;
    int I12 = 0, iZNR = 0, IIW1 = 0, IIW2 = 0;
    float XS = 0;
    float ALFTW = 0, SNATW = 0, CSATW = 0, TGATW = 0;

    cout << "\nGEOM" << endl;

    BBWW[0] = B1;
    BBWW[1] = B2;
    BW = B1;
    if (B2 < BW) BW = B2;

    if (IVP == 0) fi.open("geomc.txt", fstream::out);
    else          fi.open("geomp.txt", fstream::out);
    fi << IVP;
    ALF = AL;
    Z[0] = Z1;
    Z[1] = Z2;
    X[0] = X1;
    X[1] = X2;
    KST[0] = IST1;
    KST[1] = IST2;
    KST[2] = IST3;

    //  ПАРАМЕТРЫ ИСХОДНОГО КОНТУРА  ГОСТ 13755 - 81
    //      HLZV = 2. * HAZV
    //      CZV = 0.25
    float HGZV = 0.2;
    float DELZV = 0.02;
    if (IMD == 0) DELZV = 0.;
    
    f_1 << "\n\n\n                     РАСЧЕТ ГЕОМЕТРИИ ПО ГОСТ 16532-70" << endl;
 
    float AWZ = AW;

    SCT(ALF, SNAL, CSAL, TGAL);
    SCT(BE, SNB, CSB, TGB);

    float ALFT = atan(TGAL / CSB);
    SCT(ALFT, SNAT, CSAT, TGAT);
    float INVAT = TGAT - ALFT;
    float ZS = Z[0] + Z[1];
    float A = 0.5 * ZS * MN / CSB;
    float U = 1. * Z[1] / Z[0];
    cout << "\nGEOM: TGAL, ALFT, INVAT, ZS, A, MN, CSB, U = " << TGAL << ", " << ALFT << ", " << INVAT << ", " << ZS << ", " << A << ", " << MN << ", " << CSB << ", " << U << endl;

    f_1 << "\n       ОСНОВНЫЕ ГЕОМЕТРИЧЕСКИЕ ПАРАМЕТРЫ" << endl;

    if (Z[0] <= Z[1]) {
        UU = U;
        I12 = 0;                 //редуктор
        f_1 << "                                          ШЕСТЕРНЯ  КОЛЕСО" << endl;
        }
    else {
        UU = 1. / U;
        I12 = 1;                 //мультипликатор
        f_1 << "                                          КОЛЕСО  ШЕСТЕРНЯ" << endl;
    }
    
    if (AW == 0) {
        XS = X[0] + X[1];
        float INVATW = (2. * XS * TGAL) / ZS + INVAT;

        ARC(INVATW, ALFTW);
        cout << "\nGEOM: INVATW, ALFTW =" << INVATW << ", " << ALFTW << endl;
        SCT(ALFTW, SNATW, CSATW, TGATW);
        AW = ZS * MN * CSAT / (2. * CSB * CSATW);
        
        f_1 <<     "\nМЕЖОСЕВОЕ РАССТОЯНИЕ                       AW      " << AW;

        ZPRGMS(ALFTW, GRM, SEC);
        if (IPR >= 3) {
            f_1 << "\nПЕРЕДАТОЧНОЕ ЧИСЛО                          U      " << UU;
            f_1 << "\nУГОЛ ЗАЦЕПЛЕНИЯ (ГРАД.МИН.СЕК)          ALFTW      " << GRM << SEC << endl;
        }
     }
    else {   // если AW не равно 0
        CSATW = A * CSAT / AW;
        cout << "\nGEOM: A, CSATW = " << A << "  " << CSATW << endl;
        SNATW = sqrt(1 - CSATW * CSATW);
        TGATW = SNATW / CSATW;
        float INVATW = TGATW - atan(TGATW);
        XS = ZS * (INVATW - INVAT) * 0.5 / TGAL;
        int IDXS = 0;
        cout << "\nGEOM: XS = " << XS << endl;

        if (flaw == 0) f_1 << "\nМЕЖОСЕВОЕ РАССТОЯНИЕ                 AW       " << AW;
     //   if (flaw > 0)  
            f_1 <<            "\nКОЭФФИЦИЕНТ СУММЫ СМЕЩЕНИЙ           XS       " << round(XS * 1000) / 1000;
     
        if (X1 >= -5.) X[1] = XS - X1;
        else {
            if (X2 > -5) X[0] = XS - X2;
            else {
                if (XS < -0.5 || XS > 2) {
                    f_1 << "\nКОЭФФИЦИЕНТ СУММЫ СМЕЩЕНИЙ            XS " << round(XS * 1000) / 1000 << endl;
                    f_1 << " (вне допустимых пределов)" << endl;
                    f_1 << "\nразбивка коэф. суммы смещений не производится      " << endl;
                    f_1 << "\nРАСЧЕТ ПРЕКРАЩЕН" << endl;
                    return;
                }
                else {
                    if (IVP != 0) DXSP(XS, X);
                    else {
                        if (XS > 1 || (BE != 0 && XS > 0.5)) { DXS1(X, XS); IDXS = 1; }
                        else DXS(X, XS);
                    }
                }
            }
        }
        f_1 << "\nКОЭФФИЦИЕНТЫ СМЕЩЕНИЯ                 X      " << round(X[0] * 1000) / 1000 << "   " << round(X[1] * 1000) / 1000;

        ALFTW = atan(TGATW);
        ZPRGMS(ALFTW, GRM, SEC);
        if (IPR >= 3) {
            f_1 << "\nПЕРЕДАТОЧНОЕ ЧИСЛО                    U      " << UU;
            f_1 << "\nУГОЛ ЗАЦЕПЛЕНИЯ (ГРАД.МИН.СЕК)    ALFTW     " << GRM << SEC << endl;
        }

   
    }
    if (U >= 1) {
        DW[0] = 2. * AW / (U + 1.);
        DW[1] = 2. * AW * U / (U + 1.);
        A = 0.5 * ZS * MN / CSB;
        float Y = (AW - A) / MN;
        float DELY = XS - Y;

        for (int i = 0; i < 2; i++) {
            D[i] = Z[i] * MN / CSB;
            DA[i] = D[i] + 2 * (HA + X[i] - DELY) * MN;
            DB[i] = D[i] * CSAT;
            DF[i] = D[i] - 2 * (HA + CZV - X[i]) * MN;

            DLTH[i] = DELY * MN;
            TGAA[i] = sqrt(DA[i] * DA[i] - DB[i] * DB[i]) / DB[i];
            EA[i] = Z[i] * (TGAA[i] - TGATW) / (2 * PI);
            HZ = (DA[i] - DF[i]) / 2;
        }
        f_1 << "\nДЕЛИТЕЛЬНЫЕ ДИАМЕТРЫ                  D  " << D[0] << "    " << D[1];
        f_1 << "\nНАЧАЛЬНЫЕ ДИАМЕТРЫ                   DW  " << DW[0] << "    " << DW[1];
        f_1 << "\nДИАМЕТРЫ ВЕРШИН                      DA  " << DA[0] << "    " << DA[1];
        f_1 << "\nДИАМЕТРЫ ВПАДИН                      DF  " << DF[0] << "    " << DF[1];
        
        float DELZV = 0.02;
        if (IMD == 0) DELZV = 0;

        for (int i = 0; i < 2; i++) {
            if (DELZV != 0) {
                ROG[i] = 0.5 * D[i] * SNAT + (HA - HGZV + X[i]) * MN / SNAT;
                TGAG[i] = ROG[i] / DB[i] * 2;
            }
            ROL[i] = 0.5 * D[i] * SNAT - (HL - HA - X[i]) * MN / SNAT;
            ROP[1-i] = AW * SNATW - 0.5 * DB[i] * TGAA[i];
        }

        if (IVP >= 2 && IVP <= 4) {
            float RLA = 2 * AW * sin(PI / NW);
            if (DA[1] >= RLA) {
                f_1 << "\nНарушено условие соседства: (Da)g < 2*Aw*sin(3.14/nw)  " << endl;
                f_1 << "\n   (Da)g = " << DA[1] << "  2*Aw*sin(3.14/nw) = "  << RLA;
                }                   
        } 
        for (int i = 0; i < 2; i++) {
            DL[i] = sqrt(DB[i] * DB[i] + 4 * ROL[i] * ROL[i]);
            DP[i] = sqrt(DB[i] * DB[i] + 4 * ROP[i] * ROP[i]);
            if (DELZV != 0)  DG[i] = sqrt(DB[i] * DB[i] + 4 * ROG[i] * ROG[i]);
        }
        for (int i = 0; i < 2; i++) {
            XMIN[i] = HL - HA - Z[i] * SNAT * SNAT / 2 / CSB;
            XMINR[i] = HL - HA - (Z[i] + 2) * SNAT * SNAT / 2 / CSB;
        }
        for (int i = 0; i < 2; i++) {
            float CSBA = 1 / sqrt(1 + (DA[i] * TGB / D[i]) * (DA[i] * TGB / D[i]));
            BETA[i] = acos(CSBA);
            SNA[i] = (DA[i] * ((PI / 2 + 2 * X[i] * TGAL) / Z[i] + INVAT - (TGAA[i] - atan(TGAA[i]))) * CSBA) / MN;
        }

        if (SNA[0] <= 0 && IPR > 6) f_1 << "\n   ЗAOCTPEHИE ЗУБА ШЕСТЕРНИ   SNA1 = " << SNA[0];
        if (SNA[0] > 0 && SNA[0] < 0.3 && IPR > 6) {
            f_1 << "\n   НОРМАЛЬНАЯ ТОЛЩИНА ЗУБА ШЕСТЕРНИ НА ПОВЕРХНОСТИ " << SNA[0];
            f_1 << "\n   ВЕРШИН (В ДОЛЯХ МОДУЛЯ)  SNA1 = " << SNA[0] << " МЕНЬШЕ  0.3";
        }

        if (SNA[1] <= 0 && IPR > 6) f_1 << "\n   ЗAOCTPEHИE ЗУБА КОЛЕСА   SNA2 = " << SNA[1];
        if (SNA[1] > 0 && SNA[1] < 0.3 && IPR > 6) {
            f_1 << "\n   НОРМАЛЬНАЯ ТОЛЩИНА ЗУБА КОЛЕСА НА ПОВЕРХНОСТИ " << SNA[1];
            f_1 << "\n   ВЕРШИН (В ДОЛЯХ МОДУЛЯ)  SNA2 = " << SNA[1] << " МЕНЬШЕ  0.3";
        }
        
        float EPALF = EA[0] + EA[1];
        if (IPR >= 3) f_1 << "\nКОЭФФ. ТОРЦОВОГО ПЕРЕКРЫТИЯ       EPALF      " << EPALF;
        
        for (int i = 0; i < 2; i++) {
            float ROU = ROP[i] + PI * MN * CSAL;
            DU[i] = sqrt(DB[i] * DB[i] + 4 * ROU * ROU);
            TGAU[i] = 2 * ROU / DB[i];
            ROW[i] = 0.5 * DW[i] * SNATW;
            TGAV[1 - i] = 2 * (AW * SNATW - ROU) / DB[1 - i];
            DV[1 - i] = DB[1 - i] / cos(atan(TGAV[1 - i]));
            RL[i] = 0.5 * DB[i] * (TGAA[i] - TGATW) / (2 * PI);
        }

        if (BE != 0) {
            EPBET = BW / (PI * MN / SNB);
            EPGAM = EPBET + EPALF;
            BETB = atan(SNB * CSAL / sqrt(1 - (SNB * CSAL) * (SNB * CSAL)));
            if (BE != 0 && EPBET >= 1 && IPR >= 3)  f_1 << "\nКОЭФФ. ОСЕВОГО ПЕРЕКРЫТИЯ         EPBET      " << EPBET;
            if (BE != 0 && EPBET < 1 && IPR >= 3)   f_1 << "\nКОЭФФ. ОСЕВОГО ПЕРЕКРЫТИЯ   EPBET (МЕНЬШЕ 1) " << EPBET;
          
        }
        if (BE == 0) {
            BETB = 0;
            if (DELZV != 0) {
                EPAM = (Z[0] * TGAG[0] + Z[1] * TGAG[1] - ZS * TGATW) / 2 / PI;
                if (IPR >= 3) {
                    f_1 << "\nЧАСТЬ КОЭФФ. ТОРЦОВОГО ПЕРЕКРЫТИЯ";
                    f_1 << "\nПРИ МОДИФИКАЦИИ ПРОФИЛЯ ЗУБЬЕВ     EPAM " << EPAM;
                }
            }


        }
        int II = CNT1(X, XMIN, DL, DP, SNA, EPALF, EPBET, EPGAM);  extern float BE;     //  KOHTPOЛЬ KAЧECTBA ЗАЦЕПЛЕНИЯ
     
        cout << "GEOM: II = " << II << endl;  // организовать прерывывание, если II == 3:    IF(II.EQ.3)  GOTO 61
        
        for (int i = 0; i < 2; i++) {
            SC[i] = (PI * CSAL * CSAL / 2 + X[i] * sin(2 * ALF)) * MN;
            ROS[i] = 0.5 * (DB[i] * TGAT + SC[i] * cos(BETB) / CSAL);
            DS[i] = sqrt(DB[i] * DB[i] + 4 * ROS[i] * ROS[i]);
            HH[i] = 0.5 * (DA[i] - D[i] - SC[i] * TGAL);
        }
        if (IPR >= 3) {
            f_1 << "\n\n      ЗУБОМЕРНЫЕ ПАРАМЕТРЫ" << endl;
            f_1 << "\nПОСТОЯННАЯ ХОРДА ЗУБА                SC   " << round(SC[0] * 1000) / 1000 << "    " << round(SC[1] * 1000) / 1000;
            f_1 << "\nВЫСОТА ДО ПОСТОЯННОЙ ХОРДЫ           HC   " << round(HH[0] * 1000) / 1000 << "    " << round(HH[1] * 1000) / 1000 << endl;
        }
        
        for (int i = 0; i < 2; i++) {
            float CSALX = Z[i] * CSAT / (Z[i] + 2 * X[i] * CSB);
            
            if (CSALX >= 1) ZN[i] = 3;

            if (CSALX < 1) {
                float ZNR = Z[i] / PI * (sqrt(1 - CSALX * CSALX) / CSALX / cos(BETB) - 2 * X[i] * TGAL / Z[i] - INVAT) + 0.5;
                iZNR = ZNR;
                float TB = ZNR - iZNR;  // AINT() - усечение - целая часть?
                if (TB < 0.5) ZN[i] = iZNR;
                if (TB >= 0.5) ZN[i] = iZNR + 1;
            }            
            
     m32:   W[i] = (PI * (ZN[i] - 0.5) + 2 * X[i] * TGAL + Z[i] * INVAT) * MN * CSAL;
            ROWN[i] = 0.5 * W[i] * cos(BETB);
            DWN[i] = sqrt(DB[i] * DB[i] + 4 * ROWN[i] * ROWN[i]);
            
            if (DWN[i] >= DA[i]) {
                ZN[i] = ZN[i] - 1;
                goto m32;
            }
            if (DWN[i] <= DP[i]) {
                ZN[i] = ZN[i] + 1;
                goto m32;
            }
            if (DELZV != 0 && DWN[i] <= DG[i]) {
                ZN[i] = ZN[i] - 1;
                goto m32;
                // ----IF(W[i].GE.A) THEN    подумать !!!!!
            }
        }
       
        A = 0;
        if (BE > 0) A = BW / sin(BETB);
        if (IPR > 3) {
            IIW1 = 0;
            IIW2 = 0;

            if (BE > 0 && W[0] >= A && IPR >= 7) {
                f_1 << "\nИзмерение длины общей нормали ведущего зубчатого";
                f_1 << "\nколеса невозможно, т.к.  не выполняется дополни-";
                f_1 << "\nтельное условие для косозубых передач: ";
                f_1 << "\nW2 < A={В/sin(betb)}   W2= " << W[0] << "   A = " << A;
                IIW1 = 1;
            }

            if (IIW1 > 0 && IIW2 == 0 && IPR >= 3) {
                f_1 << "\nДЛИНА ОБЩЕЙ НОРМАЛИ                   W   " << W[1];
                f_1 << "\nЧИСЛО ЗУБЬЕВ В ДЛИНЕ ОБЩЕЙ НОРМАЛИ   ZW   " << ZN[1];
            }
            if (IIW2 > 0 && IIW1 == 0 && IPR >= 3) {
                f_1 << "\nДЛИНА ОБЩЕЙ НОРМАЛИ                   W   " << W[0];
                f_1 << "\nЧИСЛО ЗУБЬЕВ В ДЛИНЕ ОБЩЕЙ НОРМАЛИ   ZW   " << ZN[0];
            }
            if (IIW1 == 0 && IIW2 == 0 && IPR >= 3) {
                f_1 << "\nДЛИНА ОБЩЕЙ НОРМАЛИ                   W   " << round(W[0] * 1000) / 1000 << "   " << round(W[1] * 1000) / 1000;
                f_1 << "\nЧИСЛО ЗУБЬЕВ В ДЛИНЕ ОБЩЕЙ НОРМАЛИ   ZW       " << ZN[0] << "       " << ZN[1];
            }
        }        
        
        for (int i = 0; i < 2; i++) {
            DY[i] = D[i];
            TGALY = sqrt(DY[i] * DY[i] - DB[i] * DB[i]) / DB[i];
            STY = DY[i] * ((PI / 2 + 2 * X[i] * TGAL) / Z[i] + INVAT - (TGALY - atan(TGALY)));
            CSBY = 1 / sqrt(1 + (DY[i] * TGB / D[i]) * (DY[i] * TGB / D[i]));
            PSIYV = STY * CSBY * CSBY * CSBY / DY[i];
            SY[i] = DY[i] * sin(PSIYV) / (CSBY * CSBY);
            HAY[i] = 0.5 * (DA[i] - DY[i] + DY[i] * (1 - cos(PSIYV)) / (CSBY * CSBY));
        }
        
        if (IPR >= 3) {
            f_1 << "\nТОЛЩИНА ПО ХОРДЕ ЗУБА ДЕЛИТЕЛЬНАЯ     S     " << round(SY[0] * 1000) / 1000 << "    " << round(SY[1] * 1000) / 1000;    
            f_1 << "\nВЫСОТА ДО ХОРДЫ ЗУБА ДЕЛИТЕЛЬНАЯ     HA     " << round(HAY[0] * 1000) / 1000 << "    " << round(HAY[1] * 1000) / 1000 << endl;  // получились значения на 0.001 меньшие
        }

        int KST4 = IST4;
        int KST5 = IST5;
        
        DOP1L(MN, D, KST, KST4, KST5, FR, EHS, TH, EWS1, EWS2, EWS, TWM, TW, ECS, TC_);
        
        cout << "D = " << D[0] << "    " << D[1] << endl;
        cout << "DLTH = " << DLTH[0] << "    " << DLTH[1] << endl;
        cout << "EHS = " << EHS[0] << "    " << EHS[1] << endl;
        cout << "TH = " << TH[0] << "    " << TH[1] << endl;

        for (int i = 0; i < 2; i++) {

            DLTHMN[i] = -DLTH[i] - EHS[i];
            DLTHMX[i] = DLTHMN[i] + TH[i];
        }
        if (IPR >= 3) { //WRITE(1, 219) DLTHMN, DLTHMX
            f_1 << "\nПРЕДЕЛЬНЫЕ ПОКАЗАНИЯ ТАНГЕН- ";
            f_1 << "\nЦИАЛЬНОГО ЗУБОМЕРА                 DLTH   " << round(DLTHMN[0] * 1000) / 1000 << "       " << round(DLTHMN[1] * 1000) / 1000;  // 0.8    0.9    вместо   0.2      0.25
            f_1 << "\n                                          " << round(DLTHMX[0] * 1000) / 1000 << "       " << round(DLTHMX[1] * 1000) / 1000;  // 1.7    1.8             0.6      0.65
        }


        /*
  DO 37 I = 1, 2
        C      DY(I) = DA(I) - 2 * M
        DY(I) = D(I)
        TGALY = SQRT(DY(I) * *2 - DB(I) * *2) / DB(I)
        STY = DY(I) * ((PI / 2 + 2 * X(I) * TGAL) / Z(I) +
            *INVAT - (TGALY - ATAN(TGALY)))
        CSBY = 1 / SQRT(1 + (DY(I) * TGB / D(I)) * *2)

        PSIYV = STY * CSBY * *3 / DY(I)
        SY(I) = DY(I) * SIN(PSIYV) / CSBY * *2
        HAY(I) = 0.5 * (DA(I) - DY(I) + DY(I) *
            *(1 - COS(PSIYV)) / CSBY * *2)
        37 CONTINUE

    */

   /*
        CALL DOP1L(M, D, KST, KST4, KST5, FR, EHS, TH,
            *EWS1, EWS2, EWS, TWM, TW, ECS, TC)
        DO 100 I = 1, 2
        DLTHMN(I) = -DLTH(I) - EHS(I)
        100 DLTHMX(I) = DLTHMN(I) + TH(I)
        IF(IPR.GE.3) WRITE(1, 219) DLTHMN, DLTHMX
        219 FORMAT(
            *' ПРЕДЕЛЬНЫЕ ПОКАЗАНИЯ ТАНГЕН-' /
            *' ЦИАЛЬНОГО ЗУБОМЕРА                 DLTH', 2F10.3 /
            *'                                        ', 2F10.3)
        IF(IDXS.EQ.1.AND.BET.NE.0.AND.IPR.GT.6) WRITE(1, 232) XS
        232 FORMAT(/ 1X, 'КОЭФ.СУММЫ СМЕЩЕНИЙ ВНЕ РЕКОМЕНДУЕМЫХ ПРЕДЕЛОВ' /
            *' ОТ -0.5 ДО 0.5', 5X, 'XS = ', F6.3//
            C      IF(IDXS.EQ.1) WRITE(1, 231)
            * ' РЕКОМЕНДУЕТСЯ ИЗМЕНИТЬ ПАРАМЕТРЫ ПЕРЕДАЧИ ',
            *'(ЧИСЛО ЗУБЬЕВ,УГОЛ НАКЛОНА)' / )

 
        */

    }

    
    
    
    /*
  C	IF(U.GE.1.) THEN





 */

    
    fi.close();
};
/*
SUBROUTINE GEOM(IR, IPR, IVP, Z1, Z2, M, ALF, BET, X1, X2, IAX, NW,
    *AW, BBWW, HAZV, HLZV, CZV, IMD, KST1, KST2, KST3, KST4, KST5,
    *U, D1, D2, EPSA, EPSB, ALFTW, ZH, ZEPS, DU1, DU2,
    *DA1, DA2, DB1, DB2, ZVE1, ZVE2)
    C     РАСЧЕТ ГЕОМЕТРИИ ПО ГОСТ 16532 - 70
    C     ПЕЧАТЬ РЕЗУЛЬТАТОВ РАСЧЕТА
    CHARACTER * 16 IR
    REAL INVAT, INVATW, M
    DIMENSION BBWW(2), Z(2), ZN(2), X(2), D(2), DA(2), DB(2), DF(2),
    * DG(2), DL(2), RL(2), DP(2), DW(2), ROW(2), ROG(2), ROL(2),
    * ROP(2), DU(2), TGAU(2), TGAV(2), DV(2),
    * EA(2), TGAA(2), HH(2), DLTH(2), EWS1(2), EWS2(2), EWS(2),
    * DS(2), DWN(2), DY(2), HAY(2), ROS(2), ROWN(2),
    * FR(2), TH(2), TWM(2), TW(2), ECS(2),
    * TC(2), EHS(2),
    * SC(2), SY(2), W(2), KST(3),
    * TETP(2), TETV(2), DZTP(2), DZTV(2)
    DIMENSION XMIN(2), XMINR(2), SNA(2), TGAG(2)
    *, BETA(2), DLTHMN(2), DLTHMX(2)

    B1 = BBWW(1)
    B2 = BBWW(2)
    BW = AMIN1(B1, B2)

    if (ivp.EQ.0)	then
        OPEN(UNIT = 20, FILE = 'geomc.txt', STATUS = 'UNKNOWN')
    else
        OPEN(UNIT = 20, FILE = 'geomp.txt', STATUS = 'UNKNOWN')
        end if

        write(20, 5550) ivp

        CCC	print*, ' IAX= ', IAX
        PI = 3.1415927

        AL = ALF
        Z(1) = Z1
        Z(2) = Z2
        X(1) = X1
        X(2) = X2
        KST(1) = KST1
        KST(2) = KST2
        KST(3) = KST3
        C  ПАРАМЕТРЫ ИСХОДНОГО КОНТУРА  ГОСТ 13755 - 81
        C      HLZV = 2. * HAZV
        C      CZV = 0.25
        HGZV = 0.2
        DELZV = 0.02
        IF(IMD.EQ.0) DELZV = 0.
        WRITE(1, 197)
        197 FORMAT(/ 18X,
            *'РАСЧЕТ ГЕОМЕТРИИ ПО ГОСТ 16532-70' / )
        47 AWZ = AW
        CALL SCT(ALF, SNAL, CSAL, TGAL)
        CALL SCT(BET, SNB, CSB, TGB)
        ALFT = ATAN(TGAL / CSB)
        CALL SCT(ALFT, SNAT, CSAT, TGAT)
        INVAT = TGAT - ALFT
        ZS = Z(1) + Z(2)
        A = 0.5 * ZS * M / CSB
        U = 1. * Z(2) / Z(1)
        WRITE(1, 190)
        190 FORMAT(6X,
            *'ОСНОВНЫЕ ГЕОМЕТРИЧЕСКИЕ ПАРАМЕТРЫ')
        IF(Z(1).LE.Z(2)) THEN
        UU = U
        I12 = 0                  !редуктор
        WRITE(1, 191)
        191 FORMAT(
            *43X, 'ШЕСТЕРНЯ  КОЛЕСО')
        ELSE
        UU = 1. / U
        I12 = 1                  !мультипликатор
        WRITE(1, 192)
        192 FORMAT(
            *43X, ' КОЛЕСО  ШЕСТЕРНЯ')
        END IF
        IF(AW.EQ.0.)GOTO 10
        1 CSATW = A * CSAT / AW
        SNATW = SQRT(1 - CSATW * *2)
        TGATW = SNATW / CSATW
        INVATW = TGATW - ATAN(TGATW)
        XS = ZS * (INVATW - INVAT) * 0.5 / TGAL
        IDXS = 0
        IF(IAX.EQ.0) WRITE(1, 200) AW
        IF(IAX.GT.0) WRITE(1, 216) XS
        216 FORMAT(
            *' КОЭФФИЦИЕНТ СУММЫ СМЕЩЕНИЙ', 11X, 'XS', F13.3)
        IF(X1.GT. - 5.) THEN
        X(2) = XS - X1
        GOTO 4
        END IF
        IF(X2.GT. - 5.) THEN
        X(1) = XS - X2
        GOTO 4
        END IF
        IF(XS.LT. - 0.5.OR.XS.GT.2.) GOTO 6
        IF(IVP.EQ.0) GOTO 7
        CALL DXSP(XS, X)
        GOTO 4
        7 IF(XS.GT.1.) GOTO 2
        IF(BET.NE.0.AND.XS.GT.0.5) GOTO 2
        GOTO 3
        6 WRITE(1, 218) XS
        218 FORMAT(/ 7X, 'XS = ', F7.3, 3X, '(вне допустимых пределов)' /
            *'   разбивка коэф. суммы смещений не производится'//
            * 28X, 'РАСЧЕТ ПРЕКРАЩЕН' / )
        II = 4
        CCC	IAX = II        !для передачи в головную программу
        CCC	PRINT*, ' IAX =', IAX
        CCC         RETURN
        GOTO 61
        2 CALL DXS1(X, XS)
        IDXS = 1
        GOTO 4
        3 CALL DXS(X, XS)
        4  WRITE(1, 5) X
        5 FORMAT(
            *' КОЭФФИЦИЕНТЫ СМЕЩЕНИЯ', 17X, 'X', 2F10.3)
        ALFTW = ATAN(TGATW)
        CALL ZPRGMS(ALFTW, GRM, SEC)
        IF(IPR.GE.3) WRITE(1, 203) UU, GRM, SEC
        GOTO 25
        10 XS = X(1) + X(2)
        INVATW = (2. * XS * TGAL) / ZS + INVAT
        CALL ARC(INVATW, ALFTW)
        CALL SCT(ALFTW, SNATW, CSATW, TGATW)
        AW = ZS * M * CSAT / (2. * CSB * CSATW)
        WRITE(1, 200) AW
        200 FORMAT(
            *' МЕЖОСЕВОЕ РАССТОЯНИЕ                 AW', F13.3)
        CALL ZPRGMS(ALFTW, GRM, SEC)
        IF(IPR.GE.3) WRITE(1, 203) UU, GRM, SEC
        203 FORMAT(
            *' ПЕРЕДАТОЧНОЕ ЧИСЛО                    U', F13.3 /
            *' УГОЛ ЗАЦЕПЛЕНИЯ (ГРАД.МИН.СЕК)    ALFTW', F12.2,
            *F3.2 / )
        25 CONTINUE
        C	IF(U.GE.1.) THEN
        DW(1) = 2. * AW / (U + 1.)
        DW(2) = 2. * AW * U / (U + 1.)
        C	ELSE
        C      DW(2) = 2. * AW / (U + 1.)
        C      DW(1) = 2. * AW * U / (U + 1.)
        C	END IF
        A = 0.5 * ZS * M / CSB
        Y = (AW - A) / M
        DELY = XS - Y
        DO 13I = 1, 2
        D(I) = Z(I) * M / CSB
        DA(I) = D(I) + 2. * (HAZV + X(I) - DELY) * M
        DB(I) = D(I) * CSAT
        DF(I) = D(I) - 2 * (HAZV + CZV - X(I)) * M
        WRITE(7, 701) DF(I), D(I), HAZV, CZV, X(I), M, DB(I)
        701  FORMAT(' Geom=1= DF(I),D(I),HAZV,CZV,X(I),M,DB(I) : ' / 7F9.4)
        DLTH(I) = DELY * M
        TGAA(I) = SQRT(DA(I) * *2 - DB(I) * *2) / DB(I)
        EA(I) = Z(I) * (TGAA(I) - TGATW) / (2 * PI)
        HZ = (DA(1) - DF(1)) / 2
        13 CONTINUE
        WRITE(1, 199) D, DW, DA, DF
        199 FORMAT(
            *' ДЕЛИТЕЛЬНЫЕ ДИАМЕТРЫ                  D', 2F10.3 /
            *' НАЧАЛЬНЫЕ ДИАМЕТРЫ                   DW', 2F10.3 /
            *' ДИАМЕТРЫ ВЕРШИН                      DA', 2F10.3 /
            *' ДИАМЕТРЫ ВПАДИН                      DF', 2F10.3 / )
        DO 14 I = 1, 2
        IF(DELZV.EQ.0.)GO TO 12
        11 ROG(I) = 0.5 * D(I) * SNAT + (HAZV - HGZV + X(I)) * M / SNAT
        TGAG(I) = ROG(I) / DB(I) * 2
        12 ROL(I) = 0.5 * D(I) * SNAT - (HLZV - HAZV - X(I)) * M / SNAT
        ROP(2 / I) = AW * SNATW - 0.5 * DB(I) * TGAA(I)
        14 CONTINUE

        IF(IVP.EQ.2.OR.IVP.EQ.3.OR.IVP.EQ.4) THEN
          PRINT*, '  geom  NW ', NW
          RLA = 2 * AW * SIN(PI / NW)
          IF(DA(2).GE.RLA) WRITE(1, 1992) DA(2), RLA
          1992 FORMAT(/ ' Нарушено условие соседства: (Da)g < 2*Aw*sin(3.14/nw)' /
            *'   (Da)g =', F9.2, '  2*Aw*sin(3.14/nw) =', F9.2 / )
        END IF
        DO 15 I = 1, 2
        DL(I) = SQRT(DB(I) * *2 + 4 * ROL(I) * *2)
        DP(I) = SQRT(DB(I) * *2 + 4 * ROP(I) * *2)
        IF(DELZV.EQ.0) GOTO15
        DG(I) = SQRT(DB(I) * *2 + 4 * ROG(I) * *2)
        15 CONTINUE

        DO 22 I = 1, 2
        XMIN(I) = HLZV - HAZV - Z(I) * SNAT * SNAT / 2 / CSB
        22 XMINR(I) = HLZV - HAZV - (Z(I) + 2) * SNAT * SNAT / 2 / CSB
        DO 21 I = 1, 2
        CSBA = 1 / SQRT(1 + (DA(I) * TGB / D(I)) * *2)
        BETA(I) = ACOS(CSBA)
        21 SNA(I) = (DA(I) * ((PI / 2 + 2 * X(I) * TGAL) / Z(I) +
            *INVAT - (TGAA(I) - ATAN(TGAA(I)))) * CSBA) / M


        IF(SNA(1).LE.0..AND.IPR.GT.6) WRITE(1, 666) SNA(1)
           666   FORMAT(/ '  ЗAOCTPEHИE ЗУБА ШЕСТЕРНИ   SNA1=', F8.3 / )
           IF(SNA(1).GT.0..AND.SNA(1).LT.0.3.AND.IPR.GT.6) THEN
           WRITE(1, 2031) SNA(1)
           2031 FORMAT(/
            *'  НОРМАЛЬНАЯ ТОЛЩИНА ЗУБА ШЕСТЕРНИ НА ПОВЕРХНОСТИ' /
            *'  ВЕРШИН (В ДОЛЯХ МОДУЛЯ)  SNA1=', F8.3, ' МЕНЬШЕ  0.3/')
        END IF

        IF(SNA(2).LE.0..AND.IPR.GT.6) WRITE(1, 6660) SNA(2)
        6660  FORMAT(/ '  ЗAOCTPEHИE ЗУБА КОЛЕСА   SNA2=', F8.3 / )
        IF(SNA(2).GT.0..AND.SNA(2).LT.0.3.AND.IPR.GT.6) THEN
        WRITE(1, 2030) SNA(2)
        2030 FORMAT(/
            *'  НОРМАЛЬНАЯ ТОЛЩИНА ЗУБА КОЛЕСА НА ПОВЕРХНОСТИ' /
            *'  ВЕРШИН (В ДОЛЯХ МОДУЛЯ)  SNA2=', F8.3, ' МЕНЬШЕ  0.3' / )
        END IF
        EPALF = EA(1) + EA(2)
        IF(IPR.GE.3) WRITE(1, 201) EPALF
        201 FORMAT(
            *' КОЭФФ. ТОРЦОВОГО ПЕРЕКРЫТИЯ       EPALF', F13.3)
        DO 18 I = 1, 2
        ROU = ROP(I) + PI * M * CSAL
        DU(I) = SQRT(DB(I) * *2 + 4 * ROU * *2)
        TGAU(I) = 2 * ROU / DB(I)
        ROW(I) = 0.5 * DW(I) * SNATW
        TGAV(2 / I) = 2 * (AW * SNATW - ROU) / DB(2 / I)
        DV(2 / I) = DB(2 / I) / COS(ATAN(TGAV(2 / I)))
        RL(I) = 0.5 * DB(I) * (TGAA(I) - TGATW) / (2 * PI)
        18 CONTINUE



        IF(BET.NE.0) GOTO19
        BETB = 0.
        GOTO20
        19 EPBET = BW / (PI * M / SNB)
        EPGAM = EPBET + EPALF
        BETB = ATAN(SNB * CSAL / SQRT(1 - (SNB * CSAL) * *2))
        IF(BET.NE.0.AND.EPBET.GE.1..AND.IPR.GE.3) WRITE(1, 221) EPBET
        221 FORMAT(
            *' КОЭФФ. ОСЕВОГО ПЕРЕКРЫТИЯ         EPBET', F13.3)
        IF(BET.NE.0.AND.EPBET.LT.1..AND.IPR.GE.3) WRITE(1, 223) EPBET
        223 FORMAT(' КОЭФФ.ОСЕВОГО ПЕРЕКРЫТИЯ',
            *12X, 'EPBET  (МЕНЬШЕ 1 ) ', F6.3)
        20 IF(DELZV.EQ.0) GOTO 39
        EPAM = (Z(1) * TGAG(1) + Z(2) * TGAG(2) - ZS * TGATW) / 2 / PI
        IF(DELZV.NE.0..AND.IPR.GE.3) WRITE(1, 222) EPAM
        222 FORMAT(
            *' ЧАСТЬ КОЭФФ. ТОРЦОВОГО ПЕРЕКРЫТИЯ' /
            *' ПРИ МОДИФИКАЦИИ ПРОФИЛЯ ЗУБЬЕВ     EPAM', F13.3)
        39 CONTINUE


        CALL CNT1(II, X, XMIN, DL, DP, SNA, EPALF, EPBET, EPGAM, BET, NSR)


        45 IF(II.EQ.3)  GOTO 61
        DO 31 I = 1, 2
        SC(I) = (PI * CSAL * *2 / 2 + X(I) * SIN(2 * ALF)) * M
        ROS(I) = 0.5 * (DB(I) * TGAT + SC(I) * COS(BETB) / CSAL)
        DS(I) = SQRT(DB(I) * *2 + 4 * ROS(I) * *2)
        31 HH(I) = 0.5 * (DA(I) - D(I) - SC(I) * TGAL)
        IF(IPR.GE.3)  WRITE(1, 215) SC, HH
        215 FORMAT(/ 6X,
            *'ЗУБОМЕРНЫЕ ПАРАМЕТРЫ'//
            * ' ПОСТОЯННАЯ ХОРДА ЗУБА                SC', 2F10.3 /
            *' ВЫСОТА ДО ПОСТОЯННОЙ ХОРДЫ           HC', 2F10.3 / )
        DO 33 I = 1, 2
        CSALX = Z(I) * CSAT / (Z(I) + 2 * X(I) * CSB)
        IF(CSALX.LT.1)GOTO34
        ZN(I) = 3
        GOTO32
        34 ZNR = Z(I) / PI * (SQRT(1 - CSALX * *2) / CSALX / COS(BETB) -
            *2 * X(I) * TGAL / Z(I) - INVAT) + 0.5
        CCC	CBB = COS(BETB)
        TB = ZNR - AINT(ZNR)
        IF(TB.LT.0.5) ZN(I) = AINT(ZNR)
        IF(TB.GE.0.5) ZN(I) = AINT(ZNR) + 1
        CCC      print*, ' I, Z(I), CSALX, COS(BETB), INVAT, TGAL , ZNR, ZN(I),TB'
        CCC	print*, I, Z(I), CSALX, CBB, INVAT, TGAL, ZNR, ZN(I), TB
        32 W(I) = (PI * (ZN(I) - 0.5) + 2 * X(I) * TGAL + Z(I) * INVAT) *
        *M * CSAL
        ROWN(I) = 0.5 * W(I) * COS(BETB)
        DWN(I) = SQRT(DB(I) * *2 + 4 * ROWN(I) * *2)
        IF(DWN(I).LT.DA(I))  GOTO35
        ZN(I) = ZN(I) - 1
        GOTO32
        35 IF(DWN(I).GT.DP(I))  GOTO36
        ZN(I) = ZN(I) + 1
        GOTO32
        36 IF(DELZV.EQ.0) GOTO 33
        IF(DWN(I).LT.DG(I)) GOTO 33
        ZN(I) = ZN(I) - 1
        GOTO32
        C----IF(W(I).GE.A) THEN    подумать !!!!!
        33 CONTINUE
        A = 0.
        IF(BET.GT.0.) A = BW / SIN(BETB)
        IF(IPR.GE.3.) THEN
        IIW1 = 0
        IIW2 = 0
        IF(BET.GT.0..AND.W(1).GE.A.AND.IPR.GE.7) THEN
        WRITE(1, 2260) W(1), A
        2260 FORMAT(/ '  Измерение длины общей нормали ведущего зубчатого' /
            *'  колеса невозможно, т.к.  не выполняется дополни-' /
            *'  тельное условие для косозубых передач: ' /
            *'  W1 < A={В/sin(betb)}   W1=', F8.3, '  A=', F8.3 / )
        IIW1 = 1
        END IF
        IF(BET.GT.0..AND.W(2).GE.A.AND.IPR.GE.7) THEN
        WRITE(1, 2261) W(2), A
        2261 FORMAT(/ '  Измерение длины общей нормали ведомого зубчатого' /
            *'  колеса невозможно, т.к.  не выполняется дополни-' /
            *'  тельное условие для косозубых передач: ' /
            *'  W2 < A={В/sin(betb)}   W2=', F8.3, '  A=', F8.3 / )
        IIW2 = 1
        END IF
        IF(IIW1.GT.0.AND.IIW2.EQ.0.AND.IPR.GE.3)
        * WRITE(1, 2262) W(2), ZN(2)
        2262 FORMAT(
            *' ДЛИНА ОБЩЕЙ НОРМАЛИ                   W', 10X, F10.3 /
            *' ЧИСЛО ЗУБЬЕВ В ДЛИНЕ ОБЩЕЙ НОРМАЛИ   ZW', 7X, F10.0)
        IF(IIW2.GT.0.AND.IIW1.EQ.0.AND.IPR.GE.3)
        * WRITE(1, 2263) W(1), ZN(1)
        2263 FORMAT(
            *' ДЛИНА ОБЩЕЙ НОРМАЛИ                   W', F10.3 /
            *' ЧИСЛО ЗУБЬЕВ В ДЛИНЕ ОБЩЕЙ НОРМАЛИ   ZW', F7.0)
        IF(IIW1.EQ.0.AND.IIW2.EQ.0) WRITE(1, 226) W, ZN(1), ZN(2)
        226 FORMAT(
            *' ДЛИНА ОБЩЕЙ НОРМАЛИ                   W', 2F10.3 /
            *' ЧИСЛО ЗУБЬЕВ В ДЛИНЕ ОБЩЕЙ НОРМАЛИ   ZW', F7.0, F10.0)
        END IF


        DO 37 I = 1, 2
        C      DY(I) = DA(I) - 2 * M
        DY(I) = D(I)
        TGALY = SQRT(DY(I) * *2 - DB(I) * *2) / DB(I)
        STY = DY(I) * ((PI / 2 + 2 * X(I) * TGAL) / Z(I) +
            *INVAT - (TGALY - ATAN(TGALY)))
        CSBY = 1 / SQRT(1 + (DY(I) * TGB / D(I)) * *2)
        PSIYV = STY * CSBY * *3 / DY(I)
        SY(I) = DY(I) * SIN(PSIYV) / CSBY * *2
        HAY(I) = 0.5 * (DA(I) - DY(I) + DY(I) *
            *(1 - COS(PSIYV)) / CSBY * *2)
        37 CONTINUE


        IF(IPR.GE.3) WRITE(1, 217) SY, HAY
        217 FORMAT(
            C * ' ДИАМЕТР ИЗМЕРЕНИЯ ПО ХОРДЕ ЗУБА      DY', 2F10.3 /
            *' ТОЛЩИНА ПО ХОРДЕ ЗУБА ДЕЛИТЕЛЬНАЯ     S', 2F10.3 /
            *' ВЫСОТА ДО ХОРДЫ ЗУБА ДЕЛИТЕЛЬНАЯ     HA', 2F10.3 / )
        CALL DOP1L(M, D, KST, KST4, KST5, FR, EHS, TH,
            *EWS1, EWS2, EWS, TWM, TW, ECS, TC)
        DO 100 I = 1, 2
        DLTHMN(I) = -DLTH(I) - EHS(I)
        100 DLTHMX(I) = DLTHMN(I) + TH(I)
        IF(IPR.GE.3) WRITE(1, 219) DLTHMN, DLTHMX
        219 FORMAT(
            *' ПРЕДЕЛЬНЫЕ ПОКАЗАНИЯ ТАНГЕН-' /
            *' ЦИАЛЬНОГО ЗУБОМЕРА                 DLTH', 2F10.3 /
            *'                                        ', 2F10.3)
        IF(IDXS.EQ.1.AND.BET.NE.0.AND.IPR.GT.6) WRITE(1, 232) XS
        232 FORMAT(/ 1X, 'КОЭФ.СУММЫ СМЕЩЕНИЙ ВНЕ РЕКОМЕНДУЕМЫХ ПРЕДЕЛОВ' /
            *' ОТ -0.5 ДО 0.5', 5X, 'XS = ', F6.3//
            C      IF(IDXS.EQ.1) WRITE(1, 231)
            * ' РЕКОМЕНДУЕТСЯ ИЗМЕНИТЬ ПАРАМЕТРЫ ПЕРЕДАЧИ ',
            *'(ЧИСЛО ЗУБЬЕВ,УГОЛ НАКЛОНА)' / )
        C Длина контактных линий
        IF(BET.NE.0.) THEN
        NA = EPALF - AINT(EPALF)
        NB = EPBET - AINT(EPBET)
        RLM = BW * EPALF / COS(BETB)
        IF((NA + NB).LE.1.) THEN
        RLMIN = RLM * (1. - NA * NB / EPALF / EPBET)
        ELSE
        RLMIN = RLM * (1. - (1 - NA) * (1 - NB) / EPALF / EPBET)
        END IF
        RKEPS = RLMIN / RLM
        ELSE
        RLM = 0.
        RLMIN = 0.
        RKEPS = 0.
        END IF
        C Шаги зацепления и осевой
        PALF = PI * M * CSAL
        IF(BET.NE.0.) THEN
        PX = PI * M / SNB
        ELSE
        PX = 100.
        END IF
        IF(IPR.EQ.7) THEN
        CALL RKP(BET, U, DB, TGAA, ROP, TGATW, RL, ROW, TGAU,
            *PALF, PX, TETP, TETV, DZTP, DZTV)

        CALL DGKP(I12, DB, BET, BETB, DP, ROP, DL, ROL, DELZV, DG, ROG,
            *DU, DV, RLM, RLMIN, RKEPS, PALF, PX, SNA, TETP, TETV, DZTP, DZTV)
        END IF
        151 FORMAT(//)

            PRINT*, '  geom before TABLP1 '

            CALL TABLP1(IR, M, Z, BET, X, KST, KST4, KST5, DLTH, W, SC,
                *HH, SY, HAY, D, DA, HZ, EHS, TH, IIW1, IIW2,
                *ALF, HAZV, HLZV, CZV)
     61     X1 = X(1)
            X2 = X(2)
            D1 = D(1)
            D2 = D(2)
            DU1 = DU(1)
            DU2 = DU(2)
            DA1 = DA(1)
            DA2 = DA(2)
            DB1 = DB(1)
            DB2 = DB(2)
            ZVE1 = Z(1) / CSB
            ZVE2 = Z(2) / CSB
            EPSA = EPALF
            EPSB = EPBET
            BE = BET
            ZH = SQRT(2. * COS(BETB) / TGATW) / CSAT
            ZEPS = SQRT((4. - EPSA) / 3.)
            IF(BE.EQ.0.) GO TO 1010
            ZEPS = SQRT(1. / EPSA)
            IF(EPSB.LT.1.) ZEPS = SQRT((4. - EPSA) * (1. - EPSB) / 3.
                * +EPSB / EPSA)
            1010  CONTINUE
            CCC	PRINT*, 'IAX=', IAX
            IF(IPR.GE.3) WRITE(1, 300)
            300 FORMAT(' __________ ')


            write(20, 55571) B1
            write(20, 55572) B2
            write(20, 5558) aw

            write(20, 5574)  UU

            write(20, 5561) Dw(1)
            write(20, 5562) Dw(2)
            write(20, 5563) Da(1)
            write(20, 5564) Da(2)
            write(20, 5565) Df(1)
            write(20, 5566) Df(2)

            write(20, 5582) ZN(1), ZN(2), HAY(1), HAY(2)

            CLOSE(20)

            5550	format('IVP,N2,', I2, '.')
            55541	format('ALFA,C8,', F5.2, F3.2)

            55571	format('B1,N7.2,', F7.2)
            55572	format('B2,N7.2,', F7.2)
            5558	format('AW,N7.2,', F7.2)

            5574	format('U,N8.3,', F8.3)
            5575	format('GRM,N8.3,', F8.3)
            5576	format('SEC,N8.3,', F8.3)

            5561	format('DW1,N8.3,', F8.3)
            5562	format('DW2,N8.3,', F8.3)
            5563	format('DA1,N8.3,', F8.3)
            5564	format('DA2,N8.3,', F8.3)
            5565	format('DF1,N8.3,', F8.3)
            5566	format('DF2,N8.3,', F8.3)

            5582	format('ZW1,N7.2,', f7.3 / ' ZW2,N7.2,', f7.3 /
                *' HA1,N7.2,', f7.3 / ' HA2,N7.2,', f7.3)


            RETURN
            END
*/