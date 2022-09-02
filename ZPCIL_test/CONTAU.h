#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include "HBRCHV.h"
#include "SGMHLB.h"
#include "DLTH.h"
#include "WV.h"
#include "AKHBT.h"
#include "KBETPL.h"
#include "KHB2.h"
#include "PRCPC.h"
#include "AKHA.h"
#include "AKHB0.h"
#include "ZV.h"
#include "ZLIFE.h"
#include "SGHPBE.h"
#include "SGHPM.h"
#include "SIGMAX.h"
#include "NDTR.h"
#include "SGMHKA.h"
#include "SGMHKC.h"

using namespace std;
extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];

extern fstream f_1;    // файл для результата    //***

//========== Переменные по ступени
extern int IVP;                             // тип ступени
extern float Z1, Z2, U;                        // числа зубьев шестерни и колеса
extern float MN, BE, X1, X2, X[2];                // модуль, угол наклона, коэффициенты смещения
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
extern float YT2, YR2, SHV2;                // колесо: технологический коэффициент, шероховатость переходной поверхности, коэф. запаса прочностиdouble SIGH0
extern int IMF1, IMF2, IVR;                 // признаки шлифования переходной поверхности шестерни и колеса, Признак задания коэф-та запаса по контактной выносливости
extern float CZ1, CZ2, KSP, KPD, PR;        // числа зацеплений за оборот шестерни и колеса, коэф. силового потока, КПД, вероятность неразрушения по изгибной выносливости
extern float LO, S1, FKE, GM;               // расстояние между опорами, расстояние от опоры со стороны подвода момента до центра шестерни, ?, ?
extern int IQ, IP, IZ1, IG;                 // тип приложения момента, тип подшипника, ?, ?
extern float GRM;
extern int SEC;
extern float EPSA, EPSB, ZH, ZEPS;
extern float ZVE1, ZVE2;
extern float DA1, DA2, DB1, DB2, ALFTW;

extern fstream f_1;    // файл для результата    //***

void CONTAU(float& TQHP, float SGN, int INW, float A0, float DTC, float KNR, int IT1, float TQ1[100], float TC1[100], float N1[100]) {

    float SGH = 1., NUZ = .07, NUU = .04, AGH = .75;
    float SHD[20] = { 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.1, 1.1, 1.1, 1.1, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2 };
    float ZNM[20] = { 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 2.6, 2.6, 2.6, 2.6, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8, 1.8 };
    float UU = 0, DSH = 0;
    float SHR[100], SGHG[2], SGHLIM[2], SHR1[100], SHR2[100], SGHPL[2], NHLIM[2], NC1[100], NC2[100];
    int ITH[2], ITH1[2], NSH[2];
    float HRC1 = 0, HB1 = 0, HV1 = 0, HRC2 = 0, HB2 = 0, HV2 = 0;
    float HKRC1 = 0, HKB1 = 0, HKV1 = 0, HKRC2 = 0, HKB2 = 0, HKV2 = 0;
    float SHG1 = 0, SHG2 = 0, SH1 = 0, SH2 = 0;
    float OMEG = 0, OMEG1 = 0, WM = 0, KHB = 0, KHB1 = 0, KHA = 0, KHA1 = 0, KFBE = 0, KHW = 0, KHB0 = 0, KHAMAX = 0;
    int IRS = 0;
    double SIGH0 = 0, SIGH01 = 0, K0 = 0, K01 = 0, KHV = 0, KHV1 = 0;
    float KH = 0, KH1 = 0, V = 0, VR = 0, WHT = 0, ZN1 = 0, ZN2 = 0, NHE1 = 0, NHE2 = 0, ZV1 = 0, ZV2 = 0, ZX1 = 0, ZX2 = 0, ZR = 0;
    float FPB1 = 0, FPB2 = 0;

    double PI = 3.1415926;

    cout << "CONTAU:  " << endl;

 //   UU - это отношение числа зубьев колеса к числу зубьев шестерни
 //	     поэтому   всегда  UU > 1.
//       UU - ПЕРЕДАТОЧНОЕ ЧИСЛО
//	  DSH - диаметр шестерни

    cout << "CONTAU: IT, TQ[0], TC[0], RM1[0] = " <<  IT << "   " << TQ[0] << "   " << TC[0] << "   " << RM[0] << " ZH = " << ZH << " ZEPS = " << ZEPS << endl;

    if (Z2 / Z1 > 1.) {
        UU = U;
        DSH = D1;
    }
    else {
        UU = Z1 / Z2;
        DSH = D2;
    }

    int ITH0 = 0;

    for (int i = 0; i < 2; i++) {
        ITH1[i] = 0;
        ITH[i] = 0;
        NSH[i] = 0;
    }

    int IJ = 0;
    int II1 = 1;
    int II2 = 1;
    int II = 0;
    int I0 = 1;

    if (L <= -10.)  for (int i = 0; i < 20; i++) ZNM[i] = 10.;   

    float SIGH = 0.;
    float ROV = .17 * DSH * UU / ((UU + SGN) * pow(cos(BE), 2));
    float ZE = 190.; // коэф. учит. мех. св-ва сопряженных зуб. колес   ГОСТ Табл. 6 п. 1   исправлено ручкой 191.7 = 192
    float EPSG = EPSA + EPSB;

    cout << "CONTAU: D1, D2, DSH  = " << D1 << " , " << D2 << " , " << DSH << "     Z1 = " << Z1 << "  Z2 = " << Z2 << "  UU = " << UU << endl;
    cout << "CONTAU: ROV = " << ROV << endl;
    cout << "CONTAU: EPSG = EPSA + EPSB = " << EPSA << " + " << EPSB << " = " << EPSG << endl;
    
    float BW = min(B1, B2);
    float PSIBD = BW / DSH;
    
    HBRCHV(H1, HRC1, HB1, HV1);
    cout << "CONTAU: H1, HRC1, HB1, HV1= " << H1 << "   " << HRC1 << "   " << HB1 << "   " << HV1 << endl;
    HBRCHV(H2, HRC2, HB2, HV2);
    cout << "CONTAU: H2, HRC2, HB2, HV2= " << H2 << "   " << HRC2 << "   " << HB2 << "   " << HV2 << endl;

    HBRCHV(HK1, HKRC1, HKB1, HKV1);
    cout << "CONTAU: HK1, HKRC1, HKB1, HKV1= " << HK1 << "   " << HKRC1 << "   " << HKB1 << "   " << HKV1 << endl;
    HBRCHV(HK2, HKRC2, HKB2, HKV2);
    cout << "CONTAU: HK2, HKRC2, HKB2, HKV2= " << HK2 << "   " << HKRC2 << "   " << HKB2 << "   " << HKV2 << endl;

    float HBMN = min(HB1, HB2);
    float HVMN = min(HV1, HV2);
    int IH = 1;
    if (HB1 > 350 && HB2 > 350.) IH = 2;
    float QH1 = 6.;
    float QH2 = 20.;
    ITH0 = 0;
    if (IT == 1) ITH[0] = 1;
    
// если пределы прочности не заданы, то они вычисляются по группе материала и твердости
    if (SHLM1 == 0.) SGHLIM[0] = SGMHLB(IG1, HRC1, HB1);
    else SGHLIM[0] = SHLM1;

    if (SHLM2 == 0.) SGHLIM[1] = SGMHLB(IG2, HRC2, HB2);
    else SGHLIM[1] = SHLM2;

    cout << "CONTAU: ZNM = "; 
    for (int i = 0; i < 20; i++) cout << "  " << ZNM[i];
    cout << endl;

    float ZNM1 = ZNM[IG1 - 1];
    SGHPL[0] = SGHLIM[0] * ZNM1;
    float ZNM2 = ZNM[IG2];
    SGHPL[1] = SGHLIM[1] * ZNM2;
    cout << "CONTAU: IG1 = " << IG1 << "      IG2 = " << IG2 <<"     ZNM1 = " << ZNM1 << "      ZNM2 = " << ZNM2 << endl;
    cout << "CONTAU: SGHLIM[0] = " << SGHLIM[0] << "     SGHLIM[1] = " << SGHLIM[1] << "     SGHPL[0] = " << SGHPL[0] << "     SGHPL[1] = " << SGHPL[1] << endl;
//     IVR = 1 - коэф.безопасности назначается
//	Регламент.коэф.по ГОСТ 21354 - 87
    if (IVR != 1) {
        SHG1 = SHD[IG1];
        SHG2 = SHD[IG2];
        SH1 = SHG1;
        SH2 = SHG2;
    }
    else {
        SH1 = SHV1;
        SH2 = SHV2;
    }
    cout << "CONTAU: SH1 = " << SH1 << "      SH2 = " << SH2 << "     SHG1 = " << SHG1 << "      SHG2 = " << SHG2 << endl;
//	ДЛЯ ЭЗТМ  ПРИНЯТО IVR = 0
    float DLTHR = DLTH(IH, BE, IMD);  // 0.004 вместо 0.002
    cout << "CONTAU: IH, BE, IMD, DLTHR = " << IH << "   " << BE << "   " << IMD << "   " << DLTHR << endl;
    
    SGHG[0] = AGH * SGHLIM[0];
    SGHG[1] = AGH * SGHLIM[1];
    NHLIM[0] = 30. * pow(HB1, 2.4) / 1.E6;                     // ГОСТ стр.24
    if (NHLIM[0] > 120.) NHLIM[0] = 120.;
    NHLIM[1] = 30. * pow(HB2, 2.4) / 1.E6;
    if (NHLIM[1] > 120.) NHLIM[1] = 120.;
    cout << "CONTAU: NHLIM[0] = " << NHLIM[0] << "     NHLIM[1] = " << NHLIM[1] << endl;

    if (L < -1) {
        TC1[0] = 0.;
        for (int i = 0; i < 10; i++) TC1[i] = TC1[i] + WH * TC[i] * CZ1;
    }

    cout << "CONTAU:   ступеней циклограммы IT = " << IT << endl;
    for (int i = 0; i < IT; i++) {   //  DO 60 I = 1, IT   ***** Цикл по числу ступеней циклограммы =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

        if (TC[i] != 0) {

            if (L < -1.) {
                NC1[i] = WH * TC[i] * CZ1;
                NC2[i] = NC1[i] * CZ2 / (CZ1 * U);
            }
            else {
                NC1[i] = N1[i] * 60. * WH * TC[i] * CZ1 / 1.E6;
                NC2[i] = NC1[i] * CZ2 / (CZ1 * U);
                cout << "CONTAU:    L = " << L << "    NC1[i] = " << NC1[i] << "     NC2[i] = " << NC2[i] << endl;
            }

            double FTH = 2000. * TQ[i] / D1;  // Окружная сила на делительном цилиндре в торцовом сечении
            cout << "CONTAU:  Окружная сила на делительном цилиндре в торцовом сечении FTH = 2000. * TQ[i] / D1 = 2000 * " << TQ[i] << " / " << D1 << " = " << FTH << endl;

            K0 = FTH * (UU + SGN) / (BW * DSH * UU);
            cout << "CONTAU:    K0 = " << K0 << "   UU = " << UU << "   SGN = " << SGN << "   BW = " << BW << "   DSH = " << DSH << endl;

            if (IVP == 5) K0 = FTH * sqrt(pow(UU, 2) + 1.) / (BW * DSH * UU);
            SIGH0 = ZE * ZH * ZEPS * sqrt(K0);
            // ZEPS - коэф учета суммарной длины контактных линий

            cout << "CONTAU:    SIGH0 = " << SIGH0 << "   ZE = " << ZE << "   ZH = " << ZH << "   ZEPS = " << ZEPS << "   sqtr(" << K0 << ") = " << sqrt(K0) << endl;

            float KA = 1.;

            V = static_cast<float>(PI * D1 * N1[i] / 6.E4);

            float WVR = WV(AW, UU, MN, V, IST2, DLTHR, GM);

            double khv = FTH / BW;
            if (khv < 150) khv = 150;
            KHV = 1. + WVR / khv;
            cout << "CONTAU:    V = " << V << "    WVR = " << WVR << "    khv = " << khv << "    KHV = " << KHV << endl;  // WVR = 20 вместо 7.84

            cout << "CONTAU:    IKG = " << IKG << endl;
            if (IKG != 0) {                  // признак расположения зубчатых колес
                if (IKG >= 1 && IKG <= 7) {
                    KHB = AKHBT(IKG, PSIBD, IH);
                    KHB = (KHB - 1.) * pow((IST3 / 8.), 2) + 1.;
                    cout << "CONTAU:    KHB = " << KHB << endl;   // 1.0627
                }
                if (IKG >= 8 && IKG <= 9) {
                    OMEG = 0.;
                    if (KNR < 0.) OMEG = static_cast <float>(1. + DTC / TQ[i]);
                    if (KNR > 0.) OMEG = static_cast <float>(1. + ((KNR - 1) * TQ[0]) / TQ[i]);

                    KBETPL(SGN, IKG, INW, BW, D1, BE, MN, EPSA, HVMN, V, A0, KNR, OMEG, K0, KHB, KFBE);

                    if (SGN < 0 && BE != 0.) KHB = 1.3;
                }
                cout << "CONTAU:             KHB = " << KHB << endl;   // 
                if (KHB < 1) KHB = 1;

                cout << "CONTAU:    BE = " << BE << endl;
                if (BE <= 0) KHA = 1;
                if (BE > 0) {
                    float AAL = .3;
                    if (IH == 1) AAL = .2;

                    cout << "CONTAU:    EPSB = " << EPSB << "    ZEPS = " << ZEPS << "          X[1] = " << X[1] << endl;

                    cout << "CONTAU:    before AKHA    EPSA, EPSG, MN, D1, D2, BW, FTH, KHV, KHB, AAL = " << EPSA << "  " << EPSG << "  " << MN << "  " << D1 << "  " << D2 << "  " << BW << "  " << FTH << "  " << KHV << "  " << KHB << "  " << AAL << endl;
                    KHA = AKHA(EPSA, EPSG, MN, D1, D2, BW, FTH, KHV, KHB, AAL, FPB1, FPB2);
                    cout << "CONTAU:    after AKHA    KHA = " << KHA << "    KHB = " << KHB <<endl;

                    if (EPSB >= EPSA) KHAMAX = EPSA * EPSA * .95 / EPSB;
                    if (EPSB < EPSA) KHAMAX = EPSA * .95;
                    if (EPSB < 1.)   KHAMAX = EPSG / (EPSA * ZEPS * ZEPS);
                    if (KHA > KHAMAX) KHA = KHAMAX;
                    if (KHA < 1 || BE == 0) KHA = 1.;

                }


                if (IKG == 10) {
                    WM = FTH * ZEPS * ZEPS / BW;
                    KHB = KHB2(BW, DSH, BE, IG, IQ, IP, LO, S1, IST3, WM, V, HVMN);
                    KHA = 1.;
                }
            }
            else {                   // если группа не задана
                float AAB = .5;
                if (IH == 1) AAB = .3;
                // WRITE(7, 702) ZVE1, D1, MN, X1, X2, HBMN, V, FTH
                // 702  FORMAT(' CONTau  bef  KHB0:ZVE1,D1,MN,X1,X2,HBMN,V, FTH'     *5X, 8F9.4)

                KHB0 = AKHB0(EPSA, EPSG, MN, D1, BW, ZEPS, FTH, KHV, FKE, AAB);

                KHW = 1. - 20. / pow((.01 * HBMN + 2.), 2) / pow((V + 4.), .25);
                KHB = (KHB0 - 1.) * KHW + 1.;
                float AAL = .3;
                if (IH == 1) AAL = .2;


                // WRITE(7, 7018) EPSB, ZEPS
                //  7018  FORMAT(' CONTau 7018 before AKHA: EPSB,ZEPS ', 5X, 2F9.3)

//***                  KHA = AKHA(ZVE1, ZVE2, X1, X2, EPSA, EPSG, MN, D1, D2, BW, FTH, KHV, KHB, IST2, AAL, FPB1, FPB2);                  
                // KHA = AKHA(EPSA, EPSG, MN, D1, D2, BW, FTH, KHV, KHB, IST2, AAL, FPB1, FPB2);

                      //  WRITE(7, 7019) KHA
                      //  7019  FORMAT(' CONTau 7019 after AKHA: KHA ', 5X, F9.3)

                if (EPSB >= EPSA) KHAMAX = EPSA * EPSA * .95 / EPSB;
                if (EPSB < EPSA) KHAMAX = EPSA * .95;
                if (EPSB < 1.)   KHAMAX = EPSG / (EPSA * ZEPS * ZEPS);
                if (KHA > KHAMAX) KHA = KHAMAX;
                if (KHA < 1 || BE == 0) KHA = 1.;

            }

            // ---------- 8 ------------

            KH = KA * KHV * KHB * KHA;  // коэф. нагрузки  
            cout << "CONTAU: коэф. нагрузки KH = KA * KHV * KHB * KHA = " << KA << " * " << KHV << " * " << KHB << " * " << KHA << " = " << KH << "      SIGH0 = " << SIGH0 << endl;

            //        pасчетное напpяжение на i - той ступени

            SHR[i] = SIGH0 * sqrt(KH);  // контактное напряжение в полюсе зацепления - ГОСТ 21354-87 -стр.1
            cout << "CONTAU: SHR[" << i << "] = " << SIGH0 * sqrt(KH) << endl;

            //      пpовеpка : IJ = 0 - исходное pасчетное напряжение еще не выбрано
            //                 IJ = 1 - исходное pасчетное напpяжение выбрано

            cout << "CONTAU: IJ = " << IJ << "   L = " << L << endl;
            if (IJ != 1) {
                if (L >= -1) {

                    cout << "CONTAU: ***   NC1[0] = " << NC1[0] << "   NHLIM[0] = " << NHLIM[0] << "    NC2[0] = " << NC2[0] << "   NHLIM[1] = " << NHLIM[1] << endl;
                    if (!((NC1[0] > 0.03 * NHLIM[0] && NC2[0] > 0.03 * NHLIM[1]) || IT == 1 || ITH0 == 1)) {
                        //            cout << "CONTAU:    NC1[0] = " << NC1[0] << "   NHLIM[0] = " << NHLIM[0] << "    NC1[1] = " << NC1[1] << "   NHLIM[1] = " << NHLIM[1] << endl;

                        ITH0 = 1;
                        ITH1[0] = 1;
                        ITH1[1] = 1;

                        //       пpовеpка на малоцикловую усталость

                        if (II <= 1) {
                            if (SHR[0] > SGHPL[0] && IPR >= 6) {
                                f_1 << "\n ШЕСТЕРНЯ НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ";
                                f_1 << "\n   РАСЧЕТНОЕ НАПРЯЖЕНИЕ, Мпа        SHR" << SHR[0];
                                f_1 << "\n   ДОПУСКАЕМОЕ МАЛОЦИКЛОВОЕ, Мпа  SGHPL" << SGHPL[0];
                            }
                            if (SHR[0] > SGHPL[1] && IPR >= 6) {
                                f_1 << "\n КОЛЕСО НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ";
                                f_1 << "\n   РАСЧЕТНОЕ НАПРЯЖЕНИЕ, Мпа        SHR" << SHR[0];
                                f_1 << "\n   ДОПУСКАЕМОЕ МАЛОЦИКЛОВОЕ, Мпа  SGHPL" << SGHPL[1];
                            }
                        }
                        //goto m60;

                    }
                }
                else {
                    f_1 << "\nCONTAU:   L < -1";
                }

                // ---------- 9 ------------   выбоp исходного pасчетного напpяжения
                IRS = 1 + ITH0;
                cout << "CONTAU: ===   IRS = " << IRS << "   ITH0 = " << ITH0 << "    SHR[IRS] = " << SHR[IRS] << endl;
                cout << "CONTAU:    NC1[0] = " << NC1[0] << "   NHLIM[0] = " << NHLIM[0] << "    NC2[0] = " << NC2[0] << "   NHLIM[1] = " << NHLIM[1] << endl;
                SIGH = SHR[IRS - 1];   // SIGH - контактное напряжение в полюсе зацепления
                cout << "CONTAU: 9     SIGH = " << SIGH << endl;
                IJ = 1;
                SIGH01 = SIGH0;
                K01 = K0;
                KHV1 = KHV;
                OMEG1 = OMEG;
                KHB1 = KHB;
                KHA1 = KHA;
                if (IPR >= 6 && BE != 0.) f_1 << "\nПРЕДЕЛЬН.ОТКЛОНЕНИЕ ШАГА ЗАЦЕПЛ.мкм FPB  " << setprecision(3) << fixed << setw(10) << FPB1 << setw(10) << FPB2;
                VR = V;
                KH1 = KH;
                WHT = FTH * KH / BW;
            }
/*
            // ---------- 10 ------------   выбоp исходного pасчетного напpяжения исходное pасчетное напpяжение меньше повpеждаемого ?

            for (int J = 0; J < 2; J++) {


                if (!(J == 0 && II1 == 0)) {          //  II1, II2 - флаги
                    if (!(J == 1 && II2 == 0)) {

                        if (J == 0 && SIGH < SGHG[0]) { //======  48  =======
                            SHR1[i] = SHR[i];
                            NHE1 = NC1[IRS - 1];
                            ZN1 = pow((NHLIM[0] / NHE1), 0.05);
                            if (NHE1 < NHLIM[0]) ZN1 = pow((NHLIM[0] / NHE1), 0.167);
                            ITH[0] = 1 + ITH0;
                            II1 = 0;
                            cout << "CONTAU: 48     NHE1 = " << NHE1 << "    ZN1 = " << ZN1 << "    ITH[0] = " << ITH[0] << endl;
                        }




                        else {
                            if (J == 1 && SIGH < SGHG[1]) {  //======  49  =======
                                SHR2[i] = SHR[i];
                                NHE2 = NC2[IRS - 1];
                                ZN2 = pow((NHLIM[1] / NHE2), 0.05);
                                if (NHE2 < NHLIM[1]) ZN2 = pow((NHLIM[1] / NHE2), 0.167);
                                ITH[1] = 1 + ITH0;
                                II2 = 0;
                                cout << "CONTAU: 49     NHE2 = " << NHE2 << "    ZN2 = " << ZN2 << "    ITH[1] = " << ITH[1] << endl;
                            }
                            else {  //  пpовеpка : i - ое pасчетное напpяжение меньше повpеждаемого ?
                                if (J == 0 && SHR[i] < SGHG[0]) continue;
                                if (!(J == 1 && SHR[i] < SGHG[1])) {
                         //       if (!(J == 0 && SHR[i] < SGHG[0]) && !(J == 1 && SHR[i] < SGHG[1])) { //  пpовеpка: I - ое pасчетное напpяжение меньше пpедела усталости ?
                                    if (SHR[i] >= SGHLIM[J]) ITH1[J] = i;
                                    //       ITH1 - число ступеней на первом участке,  ITH - число ступеней,  (участвующих в pасчете на контактную выносливость
                                    ITH[J] = i + 1; // *** + 1
                                    SHR1[i] = SHR[i];
                                    SHR2[i] = SHR[i];
                                }
                            }
                        }

                        //======  55  =======        вариант, когда исходное pасчетное напpяжение меньше повpеждаемого

                        cout << "CONTAU: 55     IPR = " << IPR << "     J = " << J << endl;
                        if (IPR == 8 && J == 0) {
                            f_1 << "\n ШЕСТЕРНЯ";
                            f_1 << "\n   I    SIGH0       KHV      KHB       KHA     KH     SHR     NC \n";
                            f_1 << "   " <<  i << "    " << SIGH0 << "   " << KHV << "     " << KHB << "    " << KHA << "  " << KH << "  " << SHR1[i] << "  " << NC1[i] << endl;
                            ITH[J] = i;
                        }
                        if (IPR == 8 && J == 1) {
                            f_1 << "\n КОЛЕСО";
                            f_1 << "\n   I    SIGH0       KHV      KHB       KHA     KH     SHR     NC \n";
                            f_1 << "   " << i << "    " << SIGH0 << "   " << KHV << "     " << KHB << "    " << KHA << "  " << KH << "  " << SHR1[i] << "  " << NC1[i] << endl;
                        }

                    }
                }

                // ---------- 58 ------------
               // 58 IF(II1.EQ.0.AND.II2.EQ.0) GOTO 61

            }   // m59
            cout << "CONTAU: 59     NHE2 = " << NHE2 << endl;

*/
            // ---------- 10 ------------   выбоp исходного pасчетного напpяжения исходное pасчетное напpяжение меньше повpеждаемого ?

            for (int J = 0; J < 2; J++) {

                cout << "CONTAU: ========     J = " << J << "    II1 = " << II1 << "    II2 = " << II2 << endl;
                if ((J == 0 && II1 == 1) || (J == 1 && II2 == 1)) {          //  II1, II2 - флаги                    
                    cout << "CONTAU: ===========     SIGH = " << SIGH << "    SGHG[J] = " << SGHG[J] << "    SGHG[J] = " << SGHG[J] << endl;
                        if (J == 0 && SIGH < SGHG[0]) { //======  48  =======
                            SHR1[i] = SHR[i];
                            NHE1 = NC1[IRS - 1];                             
                            ZN1 = pow((NHLIM[0] / NHE1), 0.05);
                            if (NHE1 < NHLIM[0]) ZN1 = pow((NHLIM[0] / NHE1), 0.167);
                            ITH[0] = 1 + ITH0;
                            II1 = 0;
                            cout << "CONTAU: 48     NHE1 = " << NHE1 << "    ZN1 = " << ZN1 << "    ITH[0] = " << ITH[0] << endl;
                        } //*** GO TO 55
                        
                        if (J == 1 && SIGH < SGHG[1]) {  //======  49  =======
                            SHR2[i] = SHR[i];
                            NHE2 = NC2[IRS - 1];
                            ZN2 = pow((NHLIM[1] / NHE2), 0.05);
                            if (NHE2 < NHLIM[1]) ZN2 = pow((NHLIM[1] / NHE2), 0.167);
                            ITH[1] = 1 + ITH0;
                            II2 = 0;
                            cout << "CONTAU: 49     NHE2 = " << NHE2 << "    ZN2 = " << ZN2 << "    ITH[1] = " << ITH[1] << endl;
                        } //*** GO TO 55
                        
                        if (!(J == 0 && SHR1[i] < SGHG[0]) && !(J == 1 && SHR1[i] < SGHG[1])) {
                            if (SHR[i] >= SGHLIM[J]) ITH1[J] = i;
                                //       ITH1 - число ступеней на первом участке
                                //       ITH - число ступеней, участвующих в pасчете
                                //             на контактную выносливость

                            ITH[J] = i + 1; // *** + 1
                            SHR1[i] = SHR[i];
                            SHR2[i] = SHR[i];
                        }  
                        //======  55  =======        вариант, когда исходное pасчетное напpяжение меньше повpеждаемого

                        cout << "CONTAU: 55     IPR = " << IPR << "     J = " << J << endl;
                        if (IPR == 8 && J == 0) {
                            f_1 << "\n ШЕСТЕРНЯ";
                            f_1 << "\n   I    SIGH0       KHV      KHB       KHA     KH     SHR     NC \n";
                            f_1 << "   " << i << "    " << SIGH0 << "   " << KHV << "     " << KHB << "    " << KHA << "  " << KH << "  " << SHR1[i] << "  " << NC1[i] << endl;
                            ITH[J] = i;
                        }
                        if (IPR == 8 && J == 1) {
                            f_1 << "\n КОЛЕСО";
                            f_1 << "\n   I    SIGH0       KHV      KHB       KHA     KH     SHR     NC \n";
                            f_1 << "   " << i << "    " << SIGH0 << "   " << KHV << "     " << KHB << "    " << KHA << "  " << KH << "  " << SHR1[i] << "  " << NC1[i] << endl;
                        }                  
                }
                
                // ---------- 58 ------------                
                if (II1 != 0 || II2 != 0) {
                    //    59 CONTINUE
                    cout << "CONTAU: 59     NHE2 = " << NHE2 << endl;
                    if (L < -1 && SIGH == 0) ITH0 = ITH0 + 1;
                }

            }   
            

             /*
            for (int J = 0; J < 2; J++) {
                if (J == 0) {
                    if (II1 == 1 && SHR[i] < SGHG[0]) continue;
                    if (SHR[i] >= SGHLIM[J]) ITH1[J] = i;
                    //       ITH1 - число ступеней на первом участке
                    //       ITH - число ступеней, участвующих в pасчете
                    //             на контактную выносливость
                    ITH[J] = i;
                    SHR1[i] = SHR[i];
                    SHR2[i] = SHR[i];
                }
                else {
                    SHR1[i] = SHR[i];
                    NHE1 = NC1[IRS];
                    ZN1 = pow((NHLIM[0] / NHE1), 0.5);
                    if (NHE1 < NHLIM[0]) ZN1 = pow((NHLIM[0] / NHE1), 0.167);
                    ITH[0] = 1 + ITH0;
                    II1 = 0;
                }


                }
                if (J == 1) {
                    if (II2 == 1 && SHR[i] < SGHG[1]) continue;
                }
            
            }
                       
                


                      10       DO 59 J=1,2
C       пpовеpка: исходное pасчетное напpяжение
C       меньше повpеждаемого ?

      IF(J.EQ.1.AND.II1.EQ.0) GOTO 58
      IF(J.EQ.2.AND.II2.EQ.0) GOTO 58
      IF(J.EQ.1.AND.SIGH.LT.SGHG(1)) GOTO 48
      IF(J.EQ.2.AND.SIGH.LT.SGHG(2)) GOTO 49
C      пpовеpка: i -ое pасчетное напpяжение
C      меньше повpеждаемого ?

      IF(J.EQ.1.AND.SHR(I).LT.SGHG(1)) GOTO 59
      IF(J.EQ.2.AND.SHR(I).LT.SGHG(2)) GOTO 61
C       пpовеpка: I-ое pасчетное напpяжение
C       меньше пpедела усталости ?

      IF(SHR(I).GE.SGHLIM(J)) ITH1(J)=I
C       ITH1 - число ступеней на первом участке
C       ITH - число ступеней, участвующих в pасчете
C             на контактную выносливость
C       ITH1 - ўшёыю ёЄєяхэхщ эр яхЁтюь єўрёЄъх

      ITH(J)=I
      SHR1(I)=SHR(I)
      SHR2(I)=SHR(I)
      GOTO 55
C       вариант, когда исходное pасчетное напpяжение
C       меньше повpеждаемого

   48 SHR1(I)=SHR(I)
      NHE1=NC1(IRS)
       WRITE(7,7033) NHE1,IRS
 7033  FORMAT(' CONT  NHE1,IRS ',F10.3,I5)
      ZN1=(NHLIM(1)/NHE1)**.05
      IF(NHE1.LT.NHLIM(1)) ZN1=(NHLIM(1)/NHE1)**.167
      ITH(1)=1+ITH0
      II1=0
      GOTO 55
   49 SHR2(I)=SHR(I)
      NHE2=NC2(IRS)
      ZN2=(NHLIM(2)/NHE2)**.05
      IF(NHE2.LT.NHLIM(2)) ZN2=(NHLIM(2)/NHE2)**.167
      ITH(2)=1+ITH0
      II2=0
   55 IF((IPR.EQ.8).AND.J.EQ.1) WRITE(1,102)
     * I,SIGH0,KHV,KHB,KHA,KH,SHR1(I),NC1(I)
      ITH(J)=I
  102 FORMAT(/' ШЕСТЕРНЯ'/
     * '  I  SIGH0       KHV       KHB      KHA',
     * '      KH     SHR     NC'/I3,6F9.2,F10.3/)
      IF((IPR.EQ.8).AND.J.EQ.2) WRITE(1,103)
     * I,SIGH0,KHV,KHB,KHA,KH,SHR2(I),NC2(I)
  103 FORMAT(/' КОЛЕСО'/
     * '  I  SIGH0       KHV       KHB      KHA',
     * '      KH     SHR     NC'/I3,6F9.2,F10.3/)
   58 IF (II1.EQ.0.AND.II2.EQ.0) GOTO 61
   59 CONTINUE


  601 	IF(L.LT.-1.AND.SIGH.EQ.0) ITH0=ITH0+1
   60 CONTINUE
  333 FORMAT(
     *' ОКРУЖНАЯ СКОРОСТЬ ',
     *' НА РАСЧЕТН.СТУПЕНИ ЦИКЛОГРАММЫ, м/с   V',F13.3)
     * 
  61 continue 
  */
                    
   

        }
            
        if (L < - 1 && SIGH == 0) ITH0 = ITH0 + 1;
    
    } //  *************** = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - = - =
 // ============ 60 =============

    float PH1 = 0, PH2 = 0, PHM1 = 0, PHM2 = 0, SGHP1 = 0, SGHP2 = 0, SGHP = 0, SHF1 = 0, SHF2 = 0, SHMF1 = 0, SHMF2 = 0;
    float SIGHM = 0, SGHPM1 = 0, SGHPM2 = 0, TQH = 0;

 // ============ 61 =============
    ZX1 = sqrt(1.07 - D1 / 10000.);
    ZX2 = sqrt(1.07 - D2 / 10000.);
    if (ZX1 > 1) ZX1 = 1.;
    if (ZX1 < 0.75) ZX1 = 0.75;
    if (ZX2 > 1) ZX2 = 1.;
    if (ZX2 < 0.75) ZX2 = 0.75;
    // для ЭЗТМ SHER выбирается по колесу с большим Н     SHMAX = max(SHER1, SHER2)
    float SHMAX = SHER1;
    if (HB2 > HB1) SHMAX = SHER2;
    ZR = 0.95;
    if (SHMAX <= 1.60) ZR = 1.0;
    if (SHMAX > 2.50) ZR = .9;
    ZV1 = ZV(VR, HB1);
    ZV2 = ZV(VR, HB2);

    // Коэффициенты долговечности
    if (II1 != 0) {
        cout << "CONTAU:  --+-- II1 = " << II1 << endl;
        cout << "CONTAU:  --+-- ITH[0] = " << ITH[0] << "     ITH0 = " << ITH0 << "     ITH1[0] = " << ITH1[0] << "     SGHLIM[0] = " << SGHLIM[0] << endl;
        cout << "CONTAU:  --+-- SHR1[0] = " << SHR1[0] << "     SIGH = " << SIGH << "     NHLIM[0] = " << NHLIM[0] << "   NC1[0] = " << NC1[0] << "   HB1 = " << HB1 << "   NHE1 = " << NHE1 << endl;
        ZN1 = ZLIFE(ITH[0], ITH0, ITH1[0], SGHLIM[0], SHR1, SIGH, NHLIM[0], NC1, HB1, NHE1);
        cout << "CONTAU:  ==+== ZN1 = " << ZN1 << endl;
        if (ZN1 < 0.75) ZN1 = 0.75;
        if (ZN1 > ZNM1) ZN1 = ZNM1;
    }
    if (II2 != 0) {
        ZN2 = ZLIFE(ITH[1], ITH0, ITH1[1], SGHLIM[1], SHR2, SIGH, NHLIM[1], NC2, HB2, NHE2);
        cout << "CONTAU:  --+-- II2 != 0      ITH[1] = " << ITH[1] << "     ZN2 = " << ZN2 << endl;
        if (ZN2 < 0.75) ZN2 = 0.75;
        if (ZN2 > ZNM2) ZN2 = ZNM2;
    }
    SGHP1 = SGHLIM[0] * ZN1 * ZR * ZV1 * ZX1 / SH1;
    SGHP2 = SGHLIM[1] * ZN2 * ZR * ZV2 * ZX2 / SH2;

    cout << "CONTAU:  ---    SGHLIM[0] = " << SGHLIM[0] << "  ZN1 = " << ZN1 << "     ZV1 = " << ZV1 << "  ZX1 = " << ZX1 << "  ZR = " << ZR << endl;
    cout << "CONTAU:  ---    SGHLIM[1] = " << SGHLIM[1] << "  ZN2 = " << ZN2 << "     ZV2 = " << ZV2 << "  ZX2 = " << ZX2 << endl;
    cout << "CONTAU:  ---    SH1 = " << SH1 << "  SH2 = " << SH2 << "     SGHP1 = " << SGHP1 << "  SGHP2 = " << SGHP2 << endl;

    float AU = min(SGHP1, SGHP2);
    SGHP = AU;

    if (EPSB < 1) {
        SHF1 = SGHP1 * SH1 / SIGH;
        SHF2 = SGHP2 * SH2 / SIGH;
    } 
    else {
        //   интегpальный метод pасчета допускаемого контактного
        //   напpяжения для косозубой зубчатой пеpедачи

        cout << "CONTAU: ===    DB1 = " << DB1 << "  DA1 = " << DA1 << "    DB2 = " << DB2 << "      DA2 = " << DA2 << endl;
        float AA1 = acos(DB1 / DA1);
        float AA2 = acos(DB2 / DA2);
        float ALFT = ALFTW;

        cout << "CONTAU: === before SGHPBE   SGHP1 = " << SGHP1 << "  SGHP2 = " << SGHP2 << "    AA1 = " << AA1 << "     AA2 = " << AA2 << "      ALFT = " << ALFT << endl;
        cout << "CONTAU: === before SGHPBE      Z1 = " << Z1 << "        Z2 = " << Z2 << "     HB1 = " << HB1 << "     HB2 = " << HB2 << "        VR = " << VR << endl << endl;

        SGHP = SGHPBE(SGHP1, SGHP2, AA1, AA2, ALFT, Z1, Z2, HB1, HB2, VR);


        SHF1 = SGHP * SH1 / SIGH;
        SHF2 = SGHP * SH2 / SIGH;
    }
    SHF1 = SGHLIM[0] * ZN1 * ZR * ZV1 * ZX1 / SIGH;
    SHF2 = SGHLIM[1] * ZN2 * ZR * ZV2 * ZX2 / SIGH;
                                            
  //   pасчет на контактную пpочность пpи макс.нагpузке 
    SIGHM = SIGMAX(SIGH, TQ[ITH0], TMAX, KHV1, KHB1, KHA1, 1);
    SGHPM1 = SHPM1;
    if (SHPM1 == 0.) SGHPM1 = SGHPM(IG1, HB1, HRC1, HV1);
    SGHPM2 = SHPM2;
    if (SHPM2 == 0.) SGHPM2 = SGHPM(IG2, HB2, HRC2, HV2);
    SHMF1 = SGHPM1 / SIGHM;
    SHMF2 = SGHPM2 / SIGHM;
    cout << "CONTAU:  ---    II1 = " << II1 << "  II2 = " << II2 << "    SGHP = " << SGHP << "     SHMF1 = " << SHMF1 << "    SHMF2 = " << SHMF2 << endl;

       //     Расчет эапаса долговечности
       //       по методике СЕРЕНСЕНА - КОЗЛОВА - РАСУЛОВА - ГОЛЛЕРА

    float QR = 0, SN1 = 0, NHR1 = 0, SN2 = 0, NHR2 = 0, NU1 = 0, NU2 = 0, XP1 = 0, XP2 = 0, XPM1 = 0, XPM2 = 0;
    
    if (IVR == 3) {
        if (SIGH < SGHG[0]) SN1 = -10.;
        else {
            if (SIGH > SGHLIM[0]) QR = 6.;
            else QR = 20.;
            NHR1 = NHLIM[0] * pow((SGHLIM[0] / (SIGH)), QR);
            SN1 = NHR1 / NHE1;
        }
        // ============= 1333 =================== 
        if (SIGH < SGHG[1]) SN2 = -10.;
        else {
            if (SIGH > SGHLIM[1]) QR = 6.;
            else QR = 20.;
            NHR2 = NHLIM[1] * pow((SGHLIM[1] / (SIGH)), QR);
            SN2 = NHR2 / NHE2;
        }

    }
      //     квантиль нормального распределения
    if (IG1 >= 8 && IG1 <= 11) {
        NU1 = NUU;
        SHG1 = 1.1;
    }
    else {
        NU1 = NUZ;
        SHG1 = 1.2;
    }

    if (IG2 >= 8 && IG2 <= 11) {
        NU2 = NUU;
        SHG2 = 1.1;
    }
    else {
        NU2 = NUZ;
        SHG2 = 1.2;
    }
 
    XP1 = 2.328 * log10(SHF1) / log10(SHG1);
    XP2 = 2.328 * log10(SHF2) / log10(SHG2);
    XPM1 = (1. - 1. / SHMF1) / NU1;
    XPM2 = (1. - 1. / SHMF2) / NU2;

    cout << "CONTAU before NDTR:      XP1 = " << XP1 << "    XP2 = " << XP2 << "    XPM1 = " << XPM1 << "    XPM2 = " << XPM2 << endl;

    //	интеграл вероятности - ВЕРОЯТНОСТЬ НЕРАЗРУШЕНИЯ

    float DD1 = 0, DD2 = 0, DDM1 = 0, DDM2 = 0;
    

    PH1 = NDTR(XP1);
    cout << "CONTAU after NDTR:      XP1 = " << XP1 << "    PH1 = " << PH1 << endl;

    PH2 = NDTR(XP2);
    cout << "CONTAU after NDTR:      XP2 = " << XP2 << "    PH2 = " << PH2 << endl;
    
    PHM1 = NDTR(XPM1);
    cout << "CONTAU after NDTR:      XPM1 = " << XPM1 << "    PHM1 = " << PHM1 << endl;

    PHM2 = NDTR(XPM2);
    cout << "CONTAU after NDTR:      XPM2 = " << XPM2 << "    PHM2 = " << PHM2 << endl;
    

    cout << "CONTAU === 622 ===:      SHF1 = " << SHF1  << "    XP1 = " << XP1  << "    PH1 = " << PH1  << "    SHF2 = " << SHF2  << "   XP2 = " << XP2  << "   PH2 = " << PH2 << endl;
    cout << "CONTAU === 6220 ==:     SHMF1 = " << SHMF1 << "   XPM1 = " << XPM1 << "   PHM1 = " << PHM1 << "   SHMF2 = " << SHMF2 << "  XPM2 = " << XPM2 << "  PHM2 = " << PHM2 << endl;
    cout << "CONTAU before SGMHKA:     SIGH = " << SIGH << endl;
    //   pасчет на предотвpащение длительного контактного
    //   pазpушения для азотиpованных зубчатых колес
    //          пpиложение 8  ГОСТ


    if (IG1 == 12 || IG1 == 13) SGMHKA(SIGH, SHR1, ITH[0], NC1, ROV, HT1, HV1, HKV1, 1);     
    if (IG2 == 12 || IG2 == 13) SGMHKA(SIGH, SHR2, ITH[1], NC2, ROV, HT2, HV2, HKV2, 2);

        //   pасчет на пpедотвpащение длительного контактного
        //   pазpушения для цементованных колес
        //          пpиложение 8 ГОСТ

    if (IG1 < 8) SGMHKC(SIGH, SIGHM, WHT, ROV, HT1, HV1, HKV1, IG1, 1);
    if (IG2 < 8) SGMHKC(SIGH, SIGHM, WHT, ROV, HT2, HV2, HKV2, IG2, 2);

    //       исходная pасчетная нагpузк

    TQH = TQ[1 + ITH0 - 1];

//       допускаемая нагpузка

    TQHP = TQH * pow((SGHP / SIGH), 2);
            /*
            C                                                    C
C  печать pезультатов pасчета на конт.пpочность      C
C                                                    C


       WRITE(7,706) TQH, TQHP
  706  FORMAT(' CONTAW 706  bef  PRCPC: TQH,TQHP  ',2F10.3/)
C===================

    */
    cout << "CONTAU: 61     ZN1 = " << ZN1 << "    ZR = " << ZR << "    ZV1 = " << ZV1 << "    ZX1 = " << ZX1 << "   TQHP = " << TQHP << endl;
    cout << "CONTAU: 61     ZN1 = " << ZN1 << "    NHE1 = " << NHE1 << "    II1 = " << II1 << endl;
  
    cout << "CONTAU before PRCPC:    SIGH = " << SIGH << " AU = " << AU << " SHGP = " << SGHP << " SHGP1 = " << SGHP1 << " SHGP2 = " << SGHP2 << "    NHE2 = " << NHE2 << endl;
    if (IVR <= 2) PRCPC(PH1, PH2, PHM1, PHM2,
        SIGH, SGHP1, SGHP2, SGHP, SHF1, SHF2, SHMF1, SHMF2,
        SIGHM, SGHPM1, SGHPM2,
        SHR[0], SGHPL[0], SGHPL[1],
        TQH, K01, SIGH01, VR,
        ZH, ZEPS, KHV1, KHB1, OMEG1, KNR, KHA1,
        SGHLIM[0], SGHLIM[1], SGHG[0], SGHG[1], SH1, SH2,
        ZN1, ZN2, ZV1, ZV2, ZX1, ZX2, ZR,
        NHLIM[0], NHLIM[1], NHE1, NHE2);

/*
    if (IVR <= 2) PRCPC(L, IVP, IPR, IE, BE, IVR, Z1, Z2, PH1, PH2, PHM1, PHM2,
            SIGH, SGHP1, SGHP2, SGHP, SHF1, SHF2, SHMF1, SHMF2, SIGHM, SGHPM1, SGHPM2,
            SHR(1), SGHPL(1), SGHPL(2), TQH, K01, SIGH01, VR,
            ZH, ZEPS, KHV1, KHB1, OMEG1, KNR, KHA1, SGHLIM(1), SGHLIM(2), SGHG(1), SGHG(2), SH1, SH2,
            ZN1, ZN2, ZV1, ZV2, ZX1, ZX2, ZR, NHLIM(1), NHLIM(2), NHE1, NHE2);

*/
 
}

/*
      SUBROUTINE CONTAU (IVP,IPR,IE,SGN,INW,A0,DTC,KNR,L,
     *  Z1,Z2,MN,AL,BE,X1,X2,BW,IMD,HA,CZ1,CZ2,
     * U,AW,D1,D2,EPSA,EPSB,ALTW,ZH,ZEPS,DU1,DU2,
     * DA1,DA2,DB1,DB2,ZVE1,ZVE2,
     * IT,TQ,TC,N1,HH,TMAX,IST2,IST3,
     * IKG,IG,IQ,IP,L0,S1,FKE,IZ1,GM,
     * IG1,IG2,H1,H2,HK1,HK2,HT1,HT2,
     * SHER1,SHER2,IVR,SHV1,SHV2,
     * SHLM1Z,SHLM2Z,SHPM1Z,SHPM2Z,
     *    KFBE,TQH,TQHP,
     *    PH1,PH2,SHMF1,SHMF2,SN1,SN2,SHG1,SHG2,SHF1,SHF2)
      IMPLICIT REAL (K-N)
      DIMENSION TQ(IT),TC(IT),N1(IT)
      DIMENSION SHR(100),NSH(2),
     *  SGHG(2),SGHLIM(2),ITH(2),ITH1(2),NHLIM(2),
     *  SHR1(100),SHR2(100),NC1(100),NC2(100),SGHPL(2)
      DIMENSION SHD(20),ZNM(20)
      EXTERNAL DLTH,SGMHLB,WV,AKHBT,AKHB0,AKHA,KHB2,ZLIFE,SGHPBE
      EXTERNAL SIGMAX,SGHPM
         SAVE
      DATA SGH/1./,NUZ/.07/,NUU/.04/
      DATA SHD/7*1.2,4*1.1,9*1.2/,ZNM/7*1.8,4*2.6,9*1.8/
      DATA PI/3.1415926/,AGH/.75/
C	UU - это отношение числа зубьев колеса к числу зубьев шестерни
C	     поэтому   всегда  UU > 1.
C       UU - ПЕРЕДАТОЧНОЕ ЧИСЛО
C	DSH - диаметр шестерни

       WRITE(7,6559) IT,TQ(1),TC(1),N1(1)
 6559  FORMAT(' Cont 6559 IT1, TQ1(1), TC1(1), RM1(1) '/1X,I3,3F10.1)

    IF(Z2/Z1.GE.1.) THEN
        UU=U
        DSH=D1
    ELSE
        UU=Z1/Z2
        DSH=D2
    END IF
       ITH0=0
       WRITE(7,700) L,HH, IT, N1(1),TC(1),TQ(1)
  700  FORMAT(' Contau vhod ==L,WH,IT,N1(1),TC(1),TQ(1): '/
     *    10X,2F10.1,I3,3F10.3)
        DO 2 I=1,2
       ITH1(I)=0
       ITH(I) =0
    2  NSH(I)=0
        IJ=0
        II1=1
        II2=1
    II=0
    I0=1

    IF(L.LE.-10.) THEN
          DO 92 I=1,20
      ZNM(I)=10.
   92     CONTINUE
    END IF

    SIGH=0.
      ROV=.17*DSH*UU/((UU+SGN)*COS(BE)**2)
      ZE=190.
      EPSG=EPSA+EPSB
      PSIBD=BW/DSH
      CALL HBRCHV(H1,HRC1,HB1,HV1)
      CALL HBRCHV(H2,HRC2,HB2,HV2)
      CALL HBRCHV(HK1,HKRC1,HKB1,HKV1)
      CALL HBRCHV(HK2,HKRC2,HKB2,HKV2)
      HBMN=AMIN1(HB1,HB2)
      HVMN=AMIN1(HV1,HV2)
      IH=1
      IF(HB1.GT.350..AND.HB2.GT.350.) IH=2
      QH1=6.
      QH2=20.
      ITH0=0
      IF(IT.EQ.1) ITH(1)=1
      IF(SHLM1Z.EQ.0.) THEN
    SGHLIM(1)=SGMHLB(IG1,HRC1,HB1)
    ELSE
    SGHLIM(1)=SHLM1Z
    END IF
      IF(SHLM2Z.EQ.0.) THEN
        SGHLIM(2)=SGMHLB(IG2,HRC2,HB2)
    ELSE
    SGHLIM(2)=SHLM2Z
    END IF

      ZNM1=ZNM(IG1)
      SGHPL(1)=SGHLIM(1)*ZNM1
      ZNM2=ZNM(IG2)
      SGHPL(2)=SGHLIM(2)*ZNM2
C     IVR=1 - коэф. безопасности назначается
C	Регламент. коэф. по ГОСТ 21354-87


    IF(IVR.NE.1) THEN
        SHG1=SHD(IG1)
        SHG2=SHD(IG2)
    SH1=SHG1
    SH2=SHG2
    ELSE
     SH1=SHV1
         SH2=SHV2
    END IF
C	ДЛЯ ЭЗТМ  ПРИНЯТО IVR=0

      DLTHR=DLTH(IH,BE,IMD)
      SGHG(1)=AGH*SGHLIM(1)
      SGHG(2)=AGH*SGHLIM(2)
      NHLIM(1)=30.*HB1**2.4/1.E6
      IF(NHLIM(1).GT.120.) NHLIM(1)=120.
      NHLIM(2)=30.*HB2**2.4/1.E6
      IF(NHLIM(2).GT.120.) NHLIM(2)=120.
    IF(L.LT.-1) THEN
    TC1=0.
        DO 22 I=1,10
   22    TC1=TC1+HH*TC(I)*CZ1
    END IF
       WRITE(7,701) ITH0,I0
  701  FORMAT(' Contau  bef DO 60: ITH0 I0  ',2I5)
            DO 60 I=1,IT
    IF (TC(I).EQ.0.) goto 601
    IF (L.LT.-1.) THEN
      NC1(I)=HH*TC(I)*CZ1
      NC2(I)=NC1(I)*CZ2/(CZ1*U)
       WRITE(7,7011) NC1(I),HH,TC(I),CZ1
 7011  FORMAT(' Contau  NC1(I),HH,TC(I),CZ1  ',4F9.3)
    ELSE
      NC1(I)=N1(I)*60.*HH*TC(I)*CZ1/1.E6
      NC2(I)=NC1(I)*CZ2/(CZ1*U)
       WRITE(7,7011) NC1(I),HH,TC(I),CZ1
    END IF
      FTH=2000.*TQ(I)/D1

       WRITE(7,7012) FTH,TQ(I),D1
 7012  FORMAT(' Contau 7012 FTH,TQ(I),D1  : ',3F10.2)

      K0=FTH*(UU+SGN)/(BW*DSH*UU)
    IF(IVP.EQ.5) K0=FTH*SQRT(UU*UU+1.)/(BW*DSH*UU)
      SIGH0=ZE*ZH*ZEPS*SQRT(K0)
      KA=1.
      V=PI*D1*N1(I)/6.E4
      WVR=WV(AW,UU,MN,V,IST2,DLTHR,GM)

    khv=FTH/BW
    if(khv.lt.150) khv=150

      KHV=1.+ WVR/khv

      IF(IKG.EQ.0) GOTO 5
         GOTO (3,3,3,3,3,3,3,4,4,7),IKG
    3     KHB=AKHBT(IKG,PSIBD,IH)
          KHB=(KHB-1.)*(IST3/8.)**2+1.
          GOTO 41
    4   CONTINUE
C    4   IF(SGN.GT.0.) THEN
    OMEG=0.
    IF(KNR.LT.0.) OMEG=1.+DTC/TQ(I)
    IF(KNR.GT.0.) OMEG=1.+((KNR-1)*TQ(1))/TQ(I)
       WRITE(7,70110) KNR,OMEG,DTC,TQ(I),FTH,D1
70110  FORMAT(' Contau 70110 KNR,OMEG,DTC,TQ(I) : ',6F9.3)
    CALL KBETPL(SGN,IKG,INW,BW,D1,BE,MN,EPSA,HVMN,V,A0,KNR,OMEG,K0,
     *              KHB,KFBE)
C	END IF
C      IF(SGN.LT.0.AND.BE.EQ.0.) KHB=1.0
      IF(SGN.LT.0.AND.BE.NE.0.) KHB=1.3
   41   IF(KHB.LT.1.) KHB=1.0
        IF(BE) 52,52,6
   52   KHA=1.
        GOTO 8
    5   AAB=.5
        IF(IH.EQ.1) AAB=.3
       WRITE(7,702) ZVE1,D1,MN,X1,X2,HBMN,V, FTH
  702  FORMAT(' CONTau  bef  KHB0:ZVE1,D1,MN,X1,X2,HBMN,V, FTH'/
     * 5X,8F9.4)


      KHB0=AKHB0(ZVE1,ZVE2,X1,X2,EPSA,EPSG,MN,D1,
     * BW,ZEPS,FTH,KHV,IST2,IST3,FKE,IZ1,AAB)
      KHW=1.-20./(.01*HBMN+2.)**2/(V+4.)**.25
      KHB=(KHB0-1.)*KHW+1.
    6    AAL=.3
         IF(IH.EQ.1) AAL=.2


       WRITE(7,7018) EPSB,ZEPS
 7018  FORMAT(' CONTau 7018 before AKHA: EPSB,ZEPS ',5X, 2F9.3)

      KHA=AKHA(ZVE1,ZVE2,X1,X2,EPSA,EPSG,MN,D1,D2,BW,
     * FTH,KHV,KHB,IST2,AAL,FPB1,FPB2)

       WRITE(7,7019) KHA
 7019  FORMAT(' CONTau 7019 after AKHA: KHA ',5X, F9.3)

      IF(EPSB.GE.EPSA) KHAMAX=EPSA*EPSA*.95/EPSB
      IF(EPSB.LT.EPSA) KHAMAX=EPSA*.95
      IF(EPSB.LT.1.)   KHAMAX=EPSG/(EPSA*ZEPS*ZEPS)
      IF(KHA.GT.KHAMAX) KHA=KHAMAX
      IF(KHA.LT.1.OR.BE.EQ.0)     KHA=1.
      GOTO 8
    7 WM=FTH*ZEPS**2/BW
      KHB=KHB2(BW,DSH,BE,IG,IQ,IP,L0,S1,IST3,WM,V,HVMN)
      KHA=1.
    8 KH=KA*KHV*KHB*KHA
C        pасчетное напpяжение на i-той ступени

      SHR(I)=SIGH0*SQRT(KH)
C      пpовеpка:  IJ= 0 -исходное pасчетное напряжение еще не выбрано
C                 IJ= 1 -исходное pасчетное напpяжение выбрано
C      яpютхpър:  IJ= 0 -шёїюфэюх pрёўхЄэюх эряЁ цхэшх х∙х эх т√сЁрэю
C                 IJ= 1 -шёїюфэюх pрёўхЄэюх эряp цхэшх т√сЁрэю

      IF(IJ.EQ.1) GOTO 10
    IF(L.LT.-1) GOTO 9
C      IF(TC1.GT.0.03*NHLIM(1).OR.IT.EQ.1.OR.I.GE.11) GOTO 9
C       ITH0=10
C       ITH1(1)=10
C       ITH1(2)=10
C	ELSE
      IF((NC1(1).GT.0.03*NHLIM(1).AND.NC2(1).GT.0.03*NHLIM(2))
     *  .OR.IT.EQ.1.OR.ITH0.EQ.1) GOTO 9
       WRITE(7,7020) NC1(1),NHLIM(1), NC1(2),NHLIM(2)
 7020  FORMAT(' CONT  af goto 9:NC1(1),NHLIM(1), NC1(2),NHLIM(2)'/
     * 1X,4F10.4)
       ITH0=1
       ITH1(1)=1
       ITH1(2)=1
C	END IF
C       пpовеpка на малоцикловую усталость

    IF (II.LE.1) THEN
      IF(SHR(1).GT.SGHPL(1).AND.IPR.GE.6) WRITE(1,201) SHR(1),SGHPL(1)
  201 FORMAT('  ШЕСТЕРНЯ НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ'/
     * '  РАСЧЕТНОЕ НАПРЯЖЕНИЕ, Мпа        SHR',F10.2/
     * '  ДОПУСКАЕМОЕ МАЛОЦИКЛОВОЕ, Мпа  SGHPL',F10.2)
      IF(SHR(1).GT.SGHPL(2).AND.IPR.GE.6) WRITE(1,202) SHR(1),SGHPL(2)
  202 FORMAT('  КОЛЕСО НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ'/
     * '  РАСЧЕТНОЕ НАПРЯЖЕНИЕ, Мпа        SHR',F10.2/
     * '  ДОПУСКАЕМОЕ МАЛОЦИКЛОВОЕ, Мпа  SGHPL',F10.2)
    END IF
      GOTO 60
C       выбоp исходного pасчетного напpяжения

    9  IRS=1+ITH0
       WRITE(7,703) IRS,ITH0
  703  FORMAT(' CONT  af  9 irs=... IRS,ITH0',2I5)
       WRITE(7,7020) NC1(1),NHLIM(1), NC1(2),NHLIM(2)
       SIGH=SHR(IRS)
      IJ=1
      SIGH01=SIGH0
      K01=K0
      KHV1=KHV
      OMEG1=OMEG
      KHB1=KHB
      KHA1=KHA
    IF(IPR.GE.6.AND.BE.NE.0.) WRITE(1,334) FPB1,FPB2
    VR=V
  334 FORMAT(//
     *' ПРЕДЕЛЬН.ОТКЛОНЕНИЕ ШАГА ЗАЦЕПЛ.мкм FPB',2F10.3/)
      KH1=KH
           WHT=FTH*KH/BW
   10       DO 59 J=1,2
C       пpовеpка: исходное pасчетное напpяжение
C       меньше повpеждаемого ?

      IF(J.EQ.1.AND.II1.EQ.0) GOTO 58
      IF(J.EQ.2.AND.II2.EQ.0) GOTO 58
      IF(J.EQ.1.AND.SIGH.LT.SGHG(1)) GOTO 48
      IF(J.EQ.2.AND.SIGH.LT.SGHG(2)) GOTO 49
C      пpовеpка: i -ое pасчетное напpяжение
C      меньше повpеждаемого ?

      IF(J.EQ.1.AND.SHR(I).LT.SGHG(1)) GOTO 59
      IF(J.EQ.2.AND.SHR(I).LT.SGHG(2)) GOTO 61
C       пpовеpка: I-ое pасчетное напpяжение
C       меньше пpедела усталости ?

      IF(SHR(I).GE.SGHLIM(J)) ITH1(J)=I
C       ITH1 - число ступеней на первом участке
C       ITH - число ступеней, участвующих в pасчете
C             на контактную выносливость
C       ITH1 - ўшёыю ёЄєяхэхщ эр яхЁтюь єўрёЄъх

      ITH(J)=I
      SHR1(I)=SHR(I)
      SHR2(I)=SHR(I)
      GOTO 55
C       вариант, когда исходное pасчетное напpяжение
C       меньше повpеждаемого

   48 SHR1(I)=SHR(I)
      NHE1=NC1(IRS)
       WRITE(7,7033) NHE1,IRS
 7033  FORMAT(' CONT  NHE1,IRS ',F10.3,I5)
      ZN1=(NHLIM(1)/NHE1)**.05
      IF(NHE1.LT.NHLIM(1)) ZN1=(NHLIM(1)/NHE1)**.167
      ITH(1)=1+ITH0
      II1=0
      GOTO 55
   49 SHR2(I)=SHR(I)
      NHE2=NC2(IRS)
      ZN2=(NHLIM(2)/NHE2)**.05
      IF(NHE2.LT.NHLIM(2)) ZN2=(NHLIM(2)/NHE2)**.167
      ITH(2)=1+ITH0
      II2=0
   55 IF((IPR.EQ.8).AND.J.EQ.1) WRITE(1,102)
     * I,SIGH0,KHV,KHB,KHA,KH,SHR1(I),NC1(I)
      ITH(J)=I
  102 FORMAT(/' ШЕСТЕРНЯ'/
     * '  I  SIGH0       KHV       KHB      KHA',
     * '      KH     SHR     NC'/I3,6F9.2,F10.3/)
      IF((IPR.EQ.8).AND.J.EQ.2) WRITE(1,103)
     * I,SIGH0,KHV,KHB,KHA,KH,SHR2(I),NC2(I)
  103 FORMAT(/' КОЛЕСО'/
     * '  I  SIGH0       KHV       KHB      KHA',
     * '      KH     SHR     NC'/I3,6F9.2,F10.3/)
   58 IF (II1.EQ.0.AND.II2.EQ.0) GOTO 61
   59 CONTINUE
  601 	IF(L.LT.-1.AND.SIGH.EQ.0) ITH0=ITH0+1
   60 CONTINUE
  333 FORMAT(
     *' ОКРУЖНАЯ СКОРОСТЬ ',
     *' НА РАСЧЕТН.СТУПЕНИ ЦИКЛОГРАММЫ, м/с   V',F13.3)
  61  ZX1=SQRT(1.07-1.E-4*D1)
      ZX2=SQRT(1.07-1.E-4*D2)
      IF(ZX1.GT.1)    ZX1=1.
      IF(ZX1.LT..75)  ZX1=.75
      IF(ZX2.GT.1)    ZX2=1.
      IF(ZX2.LT..75)  ZX2=.75
C   для ЭЗТМ  SHER выбирается по колесу с большим H SHMAX=AMAX1(SHER1,SHER2)

      SHMAX=SHER1
      IF(HB2.GT.HB1) SHMAX=SHER2
         ZR=.95
         IF(SHMAX.LE.1.60) ZR=1.0
         IF(SHMAX.GT.2.50) ZR=.9
         ZV1=ZV(VR,HB1)
         ZV2=ZV(VR,HB2)
       WRITE(7,704) ZN1,NHE1,II1
  704  FORMAT(' CONT  bef  ZN1: ZN1,NHE1,II1 ',2F10.3,I3)
      IF(II1.NE.0)
     *   ZN1=ZLIFE(ITH(1),ITH0,ITH1(1),SGHLIM(1),SHR1,
     *   SIGH,NHLIM(1),NC1,HB1,NHE1)
         IF(ZN1.LT.0.75) ZN1=0.75
         IF(ZN1.GT.ZNM1) ZN1=ZNM1
       WRITE(7,7040) ZN2,NHE2,II2
 7040  FORMAT(' CONT  bef  ZN2: ZN2,NHE2,II2 ',2F10.3,I3)
      IF(II2.NE.0)
     *   ZN2=ZLIFE(ITH(2),ITH0,ITH1(2),SGHLIM(2),SHR2,
     *   SIGH,NHLIM(2),NC2,HB2,NHE2)
         IF(ZN2.LT.0.75) ZN2=0.75
         IF(ZN2.GT.ZNM2) ZN2=ZNM2
       WRITE(7,6560) SGHLIM(1),ZN1,ZR,ZV1,ZX1,SH1,
     *               SGHLIM(2),ZN2,ZR,ZV2,ZX2,SH2
 6560  FORMAT(' Contau 6560: SGHLIM(1),ZN1,ZR,ZV1,ZX1,SH1 '/6F10.3/
     *         'Contau 6560: SGHLIM(2),ZN2,ZR,ZV2,ZX2,SH2 '/6F10.3)
       SGHP1=SGHLIM(1)*ZN1*ZR*ZV1*ZX1/SH1
       SGHP2=SGHLIM(2)*ZN2*ZR*ZV2*ZX2/SH2
       WRITE(7,6561) SGHP1, SGHP2
 6561  FORMAT('Contau 6561: SGHP1, SGHP2  ,'2F10.3)
      AU=AMIN1(SGHP1,SGHP2)
      SGHP=AU
      IF(EPSB.GE.1) GO TO  64
      SHF1=SGHP1*SH1/SIGH
      SHF2=SGHP2*SH2/SIGH
       WRITE(7,6562) SGHP, SHF1,SHF2
 6562  FORMAT('contau 6562:  SGHP, SHF1,SHF2   ,'4F10.3)

      GOTO 65
   64 CONTINUE
C     SGHP=.45*(SGHP1+SGHP2)
C     IF(SGHP.GT.1.25*AU)  SGHP=1.25*AU
C   интегpальный метод pасчета допускаемого контактного
C   напpяжения для косозубой зубчатой пеpедачи

      AA1=ACOS(DB1/DA1)
      AA2=ACOS(DB2/DA2)
      SGHP=SGHPBE(SGHP1,SGHP2,AA1,AA2,ALTW,Z1,Z2,HB1,HB2,VR)
      SHF1=SGHP*SH1/SIGH
      SHF2=SGHP*SH2/SIGH
       WRITE(7,6563) SIGH, SGHP, SHF1,SHF2
 6563  FORMAT('contau 6563:  SIGH, SGHP, SHF1,SHF2   ,'4F10.3)

   65 SHF1=SGHLIM(1)*ZN1*ZR*ZV1*ZX1/SIGH
      SHF2=SGHLIM(2)*ZN2*ZR*ZV2*ZX2/SIGH
       WRITE(7,656) SIGH, SGHP, SHF1,SHF2
  656  FORMAT('contau 656:  SIGH, SGHP, SHF1,SHF2   ,'4F10.3)
CC                                                    C
C   pасчет на контактную пpочность пpи макс.нагpузке C
C                                                    C

        SIGHM=SIGMAX(SIGH,TQ(1+ITH0),TMAX,KHV1,KHB1,KHA1,1)
    SGHPM1=SHPM1Z
       IF(SHPM1Z.EQ.0.) SGHPM1=SGHPM(IG1,HB1,HRC1,HV1)
    SGHPM2=SHPM2Z
       IF(SHPM2Z.EQ.0.) SGHPM2=SGHPM(IG2,HB2,HRC2,HV2)
          SHMF1=SGHPM1/SIGHM
          SHMF2=SGHPM2/SIGHM
c     Расчет эапаса долговечности
c       по методике СЕРЕНСЕНА-КОЗЛОВА-РАСУЛОВА-ГОЛЛЕРА


    IF(IVR.EQ.3) THEN
      IF(SIGH.LT.SGHG(1)) THEN
         SN1=-10.
         GOTO 1333
      END IF
      IF(SIGH.GT.SGHLIM(1)) THEN
      QR=6.
      ELSE
      QR=20.
      END IF
    NHR1=NHLIM(1)*(SGHLIM(1)/(SIGH))**QR
    SN1=NHR1/NHE1
 1333	  IF(SIGH.LT.SGHG(1)) THEN
         SN1=-10.
         GOTO 1334
      END IF
      IF(SIGH.GT.SGHLIM(2)) THEN
      QR=6.
      ELSE
      QR=20.
      END IF
    NHR2=NHLIM(2)*(SGHLIM(2)/(SIGH))**QR
    SN2=NHR2/NHE2
 1334    WRITE(7,666)
  666  FORMAT(' CONTAU  SN1    SN2    NHR1    NHR2  ')
        WRITE(7,*) SN1,SN2,NHR1,NHR2
    END IF
C     квантиль нормального распределения

    IF(IG1.GE.8.AND.IG1.LE.11) THEN
     NU1=NUU
     SHG1=1.1
    ELSE
         NU1=NUZ
     SHG1=1.2
    END IF
    IF(IG2.GE.8.AND.IG2.LE.11) THEN
     NU2=NUU
     SHG2=1.1
    ELSE
         NU2=NUZ
     SHG2=1.2
    END IF
    XP1=2.328*ALOG10(SHF1)/ALOG10(SHG1)
    XP2=2.328*ALOG10(SHF2)/ALOG10(SHG2)
    XPM1=(1.-1./SHMF1)/NU1
    XPM2=(1.-1./SHMF2)/NU2
C	интеграл вероятности  -  ВЕРОЯТНОСТЬ НЕРАЗРУШЕНИЯ

    CALL NDTR(XP1,PH1,DD1)
    CALL NDTR(XP2,PH2,DD2)
    CALL NDTR(XPM1,PHM1,DDM1)
    CALL NDTR(XPM2,PHM2,DDM2)
       WRITE(7,7033) NHE1,IRS
       WRITE(7,622)  SHF1,XP1,PH1, SHF2,XP2,PH2
  622  FORMAT(' in end CONTAU  SHF1,XP1,PH1, SHF2,XP2,PH2 '/6F7.3)
       WRITE(7,6220)  SHMF1,XPM1,PHM1, SHMF2,XPM2,PHM2
 6220  FORMAT('  SHMF1,XPM1,PHM1, SHMF2,XPM2,PHM2 '/6F7.3)

 C   pасчет на предотвpащение длительного контактного
C   pазpушения для азотиpованных зубчатых колес
C          пpиложение 8  ГОСТ


       WRITE(7,705) SIGH, SGHP
  705  FORMAT(' CONT  bef  sgmhka: SIGH, SGHP', 2F10.3)
      
      IF(IG1.EQ.12.OR.IG1.EQ.13)
     *  CALL SGMHKA(SIGH,SHR1,ITH(1),NC1,ROV,HT1,HV1,HKV1,1)
      
      IF(IG2.EQ.12.OR.IG2.EQ.13)
     *  CALL SGMHKA(SIGH,SHR2,ITH(2),NC2,ROV,HT2,HV2,HKV2,2)
C   pасчет на пpедотвpащение длительного контактного
C   pазpушения для цементованных колес
C          пpиложение 8 ГОСТ


       WRITE(7,7777) HT1, HT2
7777	format ('contau 7777  HT1, HT2:',2F10.2)

      IF(IG1.LT.8)
     *  CALL SGMHKC(SIGH,SIGHM,WHT,ROV,HT1,HV1,HKV1,IG1,1)
      IF(IG2.LT.8)
     *  CALL SGMHKC(SIGH,SIGHM,WHT,ROV,HT2,HV2,HKV2,IG2,2)
C       исходная pасчетная нагpузк

        TQH=TQ(1+ITH0)

C       допускаемая нагpузк

        TQHP=TQH*(SGHP/SIGH)**2
C                                                    C
C  печать pезультатов pасчета на конт.пpочность      C
C                                                    C


       WRITE(7,706) TQH, TQHP
  706  FORMAT(' CONTAW 706  bef  PRCPC: TQH,TQHP  ',2F10.3/)
C===================
       IF(IVR.LE.2) CALL PRCPC(L,IVP,IPR,IE,BE,IVR,Z1,Z2,
     * PH1,PH2,PHM1,PHM2,
     * SIGH,SGHP1,SGHP2,SGHP,SHF1,SHF2,SHMF1,SHMF2,
     * SIGHM,SGHPM1,SGHPM2,
     * SHR(1),SGHPL(1),SGHPL(2),
     * TQH,K01,SIGH01,VR,
     * ZH,ZEPS,KHV1,KHB1,OMEG1,KNR,KHA1,
     * SGHLIM(1),SGHLIM(2),SGHG(1),SGHG(2),SH1,SH2,
     * ZN1,ZN2,ZV1,ZV2,ZX1,ZX2,ZR,
     * NHLIM(1),NHLIM(2),NHE1,NHE2)
C=====================
      RETURN
      END


*/