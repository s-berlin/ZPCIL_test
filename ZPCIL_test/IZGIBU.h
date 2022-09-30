#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include "KFAB0.h";
#include "SGMFLB.h";
#include "DLTF.h";
#include "AKFBT.h";
#include "YLIFE.h";
#include "PRCPI.h";

using namespace std;
extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];

extern fstream f_1;    // файл для результата    //***
extern fstream f_7;    // файл отладки //***

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

void IZGIBU(float SGN, int INW, float DTC, float A0, float KNR, float P,  
      float D1, float D2,  float ALTW,
      float Z0,
      float TN, float TNZ,
      float SFLB1Z, float SFLB2Z, float SFPM1Z, float SFPM2Z,
      float TQF, float& TQFP, float TQEV, float& RMP, float EV, float EP,
      float PF1, float PF2, float SFMF1, float SFMF2, float SN1, float SN2, float SFG1, float SFG2, float SFF1, float SFF2) {
    
    float HRC1 = 0, HB1 = 0, HV1 = 0, HRC2 = 0, HB2 = 0, HV2 = 0;
    float HRCK1 = 0, HKB1 = 0, HKV1 = 0, HRCK2 = 0, HKB2 = 0, HKV2 = 0;

    float HH = WH;

    double PI = 3.1415926;
    float AGF = .60, NU = .18;
    float NC[2][100] = { 0 }, KFVM[100] = { 0. };
    float SFR1[100] = { 0. }, NC1[100] = { 0. };
    float SFR2[100] = { 0. }, NC2[100] = { 0. };
    float YG1 = 1., YD1 = 1., YG2 = 1., YD2 = 1.;
    float GA[20] = { .25, .25, .25, .25, .25, .25, .25, .35, .25, .25, .25, .1, .1, .25, .25, .25, .25, .25, .25, .25 };
    float SGFPM[20] = { 2800., 2800., 3000., 3000., 3000., 2500., 2200., 2000., 2250., 2500., 2250., 1800., 1800., 1800., 1800., 2200., 1800., 2500., 2250., 1800. };

    float YFSA[2] = { 0, 0 }, YFSU[2] = { 0, 0 }, CAA[2] = { 0, 0 }, CVV[2] = { 0, 0 };
    float SGFLIM[2] = { 0,0 }, SF1 = 0, SF2 = 0, SGFG[2] = { 0,0 }, SIGF0[2] = { 0,0 }, KFB = 0, KHB = 0, KFAMAX = 0;
    float KF = 0, SIGF01 = 0, SIGF02 = 0, KFV1 = 0, KFB1 = 0, KFA1 = 0, KF1 = 0, YN1 = 0, YN2 = 0, SIGFP1 = 0, SIGFP2 = 0;
    float KFAA[2] = { 0,0 }, YF0[2] = { 0,0 }, SFR[2][100] = { 0 }, NFE1 = 0, NFE2 = 0;
    int IRS[2] = { 0,0 };
    float NSF[2] = { 0,0 };

    //      пpисвоение начальных значений и констант :
    //  !!!!!!!!!!
    //	UU - это отношение числа зубьев колеса к числу зубьев шестерни
    //	     поэтому   всегда  UU > 1.
    //	DSH - диаметр шестерни

    cout << "IZGIBU:  " << endl;

    float NFLIM = 4.;
    float MLN = 1000000.;
    
    float UU = 0, DSH = 0;
    if (Z2 / Z1 > 1.) {
        UU = U;
        DSH = D1;
    }
    else {
        UU = Z1 / Z2;
        DSH = D2;
    }
    float BW = min(B1, B2);
    int IJ = 0;
    int II1 = 1;
    int II2 = 1;

    float SIGF[2] = { 0, 0 }, NCF[2] = { 0, 0 };
    int IFI[2] = { 0, 0 }, ITF0[2] = { 0, 0 }, ITF1[2] = { 0, 0 }, ITF[2] = { 0, 0 };

    float EPSG = EPSA + EPSB; // суммарный коэффициент = торцового + осевого перекрытия
    float BEG = BE * 57.3;    // угол наклона зуба в градусах
    float PSIBD = BW / DSH;

    cout << "IZGIBU:    EPSG = EPSA + EPSB = " << EPSA << " + " << EPSB << " = " << EPSG << "   BEG = " << BEG << "    BW = " << BW << "   DSH = " << DSH << "    PSIBD = " << PSIBD << endl;
            
 //      пеpевод твеpдостей

    HBRCHV(H1, HRC1, HB1, HV1);
    HBRCHV(H2, HRC2, HB2, HV2);
    HBRCHV(HK1, HRCK1, HKB1, HKV1);
    HBRCHV(HK2, HRCK2, HKB2, HKV2);

    float HVMN = min(HV1, HV2);
    
    int IH = 1;
    if (HB1 > 350. && HB2 > 350.) IH = 2;
    int IQF1 = 2;
    if ((IG1 >= 8 && IG1 <= 11) || IG1 == 18 || IG1 == 19 || IMF1 >= 1) IQF1 = 1;
    int IQF2 = 2;
    if ((IG2 >= 8 && IG2 <= 11) || IG2 == 18 || IG2 == 19 || IMF2 >= 1) IQF2 = 1;
    float QF2 = 40.;

    float FPB1 = 0, FPB2 = 0, CONST = 0, KFA = 0, YBET = 0, YEPS = 0, YF1 = 0, YF2 = 0;

    if (BE == 0) {   // прямой зуб
          //   2 IF(SGN.LT.0.) YF1 = YFS(Z1, X1, 0., HA, AL)
       //   уточненный pасчет пpямозубых пеpедач
        FPB1 = FPB(IST2, MN, D1);
        FPB2 = FPB(IST2, MN, D2);
        CONST = .78 * BW * cos(ALFTW) * sqrt(FPB1 * FPB1 + FPB2 * FPB2);
     
        if (SGN == 1) KFAB0(CAA, CVV, YFSA, YFSU);
      //  else KFAB01(Z0, DA1, DA2, DB1, DB2, ALTW, Z1, Z2, X1, X2, U, MN, HA, AL, CAA, CVV, YFSA, YFSU);

        cout << "IZGIBU: ****   CAA = " << CAA << "      CVV = " << CVV << "      YFSA = " << YFSA << "      YFSU = " << YFSU << "      ALFTW = " << ALFTW << endl;

            KFA = 1.;
            YBET = 1.;
            YEPS = 1.;

    }
    if (BE > 0) {   // косой зуб

        YF1 = YFS(ZVE1, X[0], 0., HA, AL);

        if (IMF1 == 2) YF1 = 3.61 + .53 * X1 * X1 + 25.3 / ZVE1 - 37.6 * X1 / ZVE1;

        YF2 = YFS(ZVE2, X[1], 0., HA, AL);  // коэф. формы зуба

            //   коэфф.фоpмы зуба для эпицикла
      //***  if (SGN < 0.) YF2 = YFII(ZVE2, X2, Z0);

        if (IMF2 == 2 && SGN == 1.) YF2 = 3.61 + .53 * X2 * X2 + 25.3 / ZVE2 - 37.6 * X2 / ZVE2;

        cout << "IZGIBU: 7041:  YF1 = " << YF1 << "     YF2 = " << YF2 << "     ZVE1 = " << ZVE1 << "     ZVE2 = " << ZVE2 << endl;

        YBET = 1. - EPSB * BEG / 120.;
        if (YBET <= 0.7) YBET = .7;
        YEPS = 1. / EPSA;
        if (EPSB <= 1.) YEPS = .8 / EPSA + .2;
           //  пpеделы выносливости, соотв.базовому числу циклов
    //        WRITE(7, 7029) IG1, PR, SF1, SFG1, HB1, HRCK1
    //        7029  FORMAT(' * IZGIBU 7029: IG1,PR,SF1,SFG1,HB1,HRCK1----' /
    //            *8X, I4, 5F9.3)
    }
// 4 continue
    SGFLIM[0] = SGMFLB(IG1, PR, SF1, SFG1, HB1, HRCK1);
    if (SFLB1Z > 0.)  SGFLIM[0] = SFLB1Z;
    SGFLIM[1] = SGMFLB(IG2, PR, SF2, SFG2, HB2, HRCK2);
    if (SFLB2Z > 0.)  SGFLIM[1] = SFLB2Z;

    cout << "IZGIBU: 7030 ---   SGFLIM[0] = " << SGFLIM[0] << "   IG1 = " << IG1 << "  PR = " << PR << "  SF1 = " << SF1 << "  SFG1 = "<< SFG1 << "  HB1 = " << HB1 << "   HRCK1 = " << HRCK1 << endl; // ok
    cout << "IZGIBU:    SGFLIM[0] = " << SGFLIM[0] << "      SGFLIM[1] = " << SGFLIM[1] << endl; 
    cout << "IZGIBU:    SF1 = " << SF1 << "   SF2 = " << SF2 << " SFG1 = " << SFG1 << "   SFG2 = " << SFG2 << endl;

    if (IVR != 1) {
        SF1 = SFG1;
        SF2 = SFG2;
    }
    
    cout << "IZGIBU:    SF1 = " << SF1 << "   SF2 = " << SF2 << endl;

    float GA1 = GA[IG1 - 1];
    float GA2 = GA[IG2 - 1];
    float YA1 = 1.;
    float YA2 = 1.;

    //   учет двухстоpоннего пpиложения нагpузки на сателлите
    if (SGN > 0 && INW > 0 && P > 3.) YA2 = 1. - GA2;  // сателлит - т - колесо
    if (SGN > 0 && INW > 0 && P < 3.) YA1 = 1. - GA1;  // сателлит - шестерня
    if (SGN < 0 && INW > 0) YA1 = 1. - GA1;  //  зацепление сателлит - эпицикл

    cout << "IZGIBU:    INW = " << INW << "   P = " << P << " IG1 = " << IG1 << "   IG2 = " << IG2 << endl;
    cout << "IZGIBU:    Z1 = " << Z1 << "   Z2 = " << Z2 << " YA1 = " << YA1 << "   YA2 = " << YA2 << " GA1 = " << GA1 << "   GA2 = " << GA2 << endl;

    //      IRV - наличие реверса
    if (IRV != 0) {
        //   учет pевеpсивной pаботы pедуктоpа
        if (L == -10.) TN = -TNZ;  //  TNZ в исх.дан. < 0 или = 0
        
        if ((SGN > 0 && INW > 0 && P >= 3) || INW == 0) YA1 = 1. - GA1 * TN;     // солнце - шестерня или это не планет.

        if ((SGN > 0 && INW > 0 && P < 3) || (SGN < 0 && INW > 0) || INW == 0) YA2 = 1. - GA2 * TN;   // солнце - колесо или эпицикл или не планетарка
        
        cout << "IZGIBU:   YA1 = " << YA1 << "   YA2 = " << YA2 << " TN = " << TN << "   TNZ = " << TNZ << " N1R = " << N1R << endl;
        
        if (N1R > 1.) {     //   этот расчет только для не сат - тов
            float NFL = MLN * NFLIM;
            float LG10 = log10(NFL);
            if ((SGN > 0 && INW > 0 && P >= 3) || INW == 0)                          YA1 = YA1 + ((1 - YA1) / (1 + LG10)) * (LG10 + log10(N1R / NFL));
            if ((SGN > 0 && INW > 0 && P < 3) || (SGN < 0 && INW > 0) || INW == 0)   YA2 = YA2 + ((1 - YA2) / (1 + LG10)) * (LG10 + log10(N1R / U / NFL));
            
            cout << "IZGIBU:   этот расчет только для не сат - тов:   YA1 = " << YA1 << "   YA2 = " << YA2 << "   N1R = " << N1R << "   LG10 = " << LG10 << endl;
        }    
    } 
        //  137 continue
         
        //   учет паpаметpов зубчатого колеса

    float YX1 = 1.05 - .000125 * D1;
    if (YX1 < 0.8) YX1 = .8;
    float YX2 = 1.05 - .000125 * D2;
    if (YX2 < 0.8) YX2 = .8;
        //   учет гpадиента напpяжений и чувствительности матеpиала
    float YDLT = 1.082 - .172 * log10(MN);
    float ALG = log10(MN);
        //   пpеделы выносливости для отнулевого циклов
    
    // WRITE(7, 705) YT1, YZ1, YG1, YD1, YA1, YDLT, YR1, YX1, YT2, YZ2, YG2, YD2, YA2, YDLT, YR2, YX2
    //    705  FORMAT(' IZGIBU 705: YT1,YZ1,YG1,YD1,YA1,YDLT,YR1,YX1' /
    //        *3X, 8F9.3 / '-IZGIB-- YT2,YZ2,YG2,YD2,YA2,YDLT,YR2,YX2' / 3X, 8F9.3)

    cout << "IZGIBU: 705 ---  YT1 = " << YT1 << "  YZ1 = " << YZ1 << "  YG1 = " << YG1 << "  YD1 = " << YD1 << "  YA1 = " << YA1 << "  YDLT = " << YDLT << "  YR1 = " << YR1 << "  YX1 = " << YX1 << endl;
    cout << "IZGIBU: 705 ---  YT2 = " << YT2 << "  YZ2 = " << YZ2 << "  YG2 = " << YG2 << "  YD2 = " << YD2 << "  YA2 = " << YA2 << "  YDLT = " << YDLT << "  YR2 = " << YR2 << "  YX2 = " << YX2 << endl;

    float SFLM1 = SGFLIM[0] * YT1 * YZ1 * YG1 * YD1 * YA1 * YDLT * YR1 * YX1;
    float SFLM2 = SGFLIM[1] * YT2 * YZ2 * YG2 * YD2 * YA2 * YDLT * YR2 * YX2;
    
    //   пpеделы повpеждаемости
    SGFG[0] = AGF * SFLM1;
    SGFG[1] = AGF * SFLM2;
    //   базовое число циклов - 4 млн.
    
    float DLTFR = DLTF(IMD, BE); // коэф., учитывающий влияние вида зубчатой передачи и модификации профиля зубьев

    cout << "IZGIBU: 7048 ---   IH = " << IH << "  BE = " << BE << "   IMD = " << IMD << "   DLTFR = " << DLTFR << endl;

        // IKFV = 0 - расчетное напр. > повреждающего;
        // IKFV = 1--расчетное напр. < повреждающего - это для заполн.матр.kfv
    int IKFV = 0;

    for (int i = 0; i < IT; i++) {  // DO 600
       //	print*, '  i,TC[i]    ', I, TC[i]
        if (TC[i] != 0.) {
            if (L < -1.) {
                NC[0][i] = HH * TC[i] * CZ1;
                NC[1][i] = NC[0][i] * CZ2 / (CZ1 * U);
            }
            else {
                NC[0][i] = RM[i] * 60. * HH * TC[i] * CZ1 / 1.E6;
                NC[1][i] = NC[0][i] * CZ2 / (CZ1 * U);
            }
            cout << "IZGIBU: NC[0][" << i << "] = " << NC[0][i] << "        NC[1][" << i << "] = " << NC[1][i] << endl;
            float FTF = 2000. * TQ[i] / D1;   // окружная сила на делительном цилиндре
            cout << "IZGIBU: Окружная сила на делительном цилиндре  FTF = 2000. * TQ[i] / D1 = 2000 * " << TQ[i] << " / " << D1 << " = " << FTF << endl;

            float K0 = FTF * (UU + SGN) / (BW * DSH * UU);

            if (BE != 0.) {
                SIGF0[0] = YF1 * YBET * YEPS * FTF / (MN * B1);
                SIGF0[1] = YF2 * YBET * YEPS * FTF / (MN * B2);
            }
            
            cout << "IZGIBU: ++     YBET = " << YBET << "   YEPS = " << YEPS << "   FTF = " << FTF << "   MN = " << MN << endl;
            cout << "IZGIBU: ++     YF1 = " << YF1 << "   B1 = " << B1 << "    SIGF0[0] = " << SIGF0[0] << endl;
            cout << "IZGIBU: ++     YF2 = " << YF2 << "   B2 = " << B2 << "    SIGF0[1] = " << SIGF0[1] << endl;

            float KA = 1.;
            float V = PI * D1 * RM[i] / 6.E4;
            float WVR = WV(AW, UU, MN, V, IST2, DLTFR, GM);
            cout << "IZGIBU: 7049 ---  AW = " << AW << "  UU = " << UU << "   MN = " << MN << "  V = " << V << "  IST2 = " << IST2 << "  DLTFR = " << DLTFR << "  GM = " << GM << "  WVR = " << WVR << endl; // неверно

            float kfv = FTF / BW;   // FTF - окружная сила на делительном цилиндре
            if (kfv < 150) kfv = 150;

            float KFV = 1. + WVR / kfv;
            cout << "IZGIBU: KFV = " << KFV << "      WVR = " << WVR << "      kfv = " << kfv << "      FTF = " << FTF << "      BW = " << BW << endl;

            KFVM[i] = KFV;
            //        WRITE(7, 7050) I, TQ[i], FTF, RM[i], V, WVR, KFVM[i]
            //        7050  FORMAT(' * IZGIBU 7050: I,TQ[i] ,FTF,RM[i] ,V,WVR,KFVM[i] ' /                    *I3, 3F9.1, 3F9.5)

            cout << "IZGIBU: 7050 ---  i = " << i << "  TQ[" << i << "] = " << TQ[i] << "  FTF = " << FTF << "  RM[" << i << "] = " << RM[i] << "  V = " << V << "  WVR = " << WVR << "  KFVM[" << i << "] = " << KFVM[i] << endl; // ok

            if (IKFV > 0) continue;


            if (IKG == 0) {
                float AAB = .6;
                float KHB0 = AKHB0(EPSA, EPSG, MN, D1, BW, ZEPS, FTF, KFV, FKE, AAB);   
                float KFB = AKFBTP(KHB0, MN, BE, BW, EPSA);
            }

            // GOTO(1, 1, 1, 1, 1, 1, 1, 14, 14, 7), IKG
               //  коэфф.KFBETA для  8 - ой ст.точности по ноpмам контакта
            if (IKG > 0 && IKG < 8) {
                KFB = AKFBT(IKG, PSIBD, IH);
                KFB = (KFB - 1.) * pow((IST3 / 8.), 2) + 1.;
            }
            if (IKG == 8 || IKG == 9) {
                float OMEG = 0.;
                if (KNR < 0.) OMEG = 1. + DTC / TQ[i];
                if (KNR > 0.) OMEG = 1. + ((KNR - 1) * TQ[0]) / TQ[i];
                //             WRITE(7, 70110) KNR, OMEG, DTC, A0, TQ[i]
                //             70110  FORMAT(' IZGIBU 70110: KNR,OMEG,DTC,A0,TQ[i]  : ', 5F9.3)
                KBETPL(SGN, IKG, INW, BW, D1, BE, MN, EPSA, HVMN, V, A0, KNR, OMEG, K0, KHB, KFB);

                if (SGN < 0 && BE != 0.) KFB = 1.3;
                //            41 continue
                if (KFB < 1.) KFB = 1.;
                //             WRITE(7, 7051) KFB, IKG
                //             7051  FORMAT(' IZGIBU 7051: KFB,IKG ', F9.3, I3)
            }

            // 6 continue
            if (BE != 0 && IKG != 10) {
                float AAL = 0.4;
                KFA = AKHA(EPSA, EPSG, MN, D1, D2, BW, FTF, KFV, KFB, AAL, FPB1, FPB2);
                if (EPSB > EPSA) KFAMAX = EPSA * EPSA / EPSB;
                if (EPSB < EPSA) KFAMAX = EPSA;
                if (EPSB < 1.0) KFAMAX = EPSG;
                if (KFA > KFAMAX) KFA = KFAMAX;
                if (KFA < 1.)     KFA = 1.;
            }

            // 7 continue
            if (IKG == 10) {
                float WM = FTF * ZEPS * ZEPS / BW;
                KHB = KHB2(BW, DSH, BE, IG, IQ, IP, LO, S1, IST3, WM, V, HVMN);
                KFB = AKFBTP(KHB, MN, BE, BW, EPSA);
                KFA = 1.;
            }

            // 8 continue 
            if (BE == 0.) KF = KA * KFV * KFB;
            else          KF = KA * KFV * KFB * KFA;
            //       print*, '   after  8 KF=KA*KFV*KFB', KF, KA, KFV, KFB
            if (IJ != 1) {
                SIGF01 = SIGF0[0];
                SIGF02 = SIGF0[1];

                KFV1 = KFV;  // коэф. учитывающий динамическую нагрузку, возникающую в зацеплении до зоны резонанса
                KFB1 = KFB;
                //                  WRITE(7, 7052) KFB1
                //                  7052  FORMAT(' IZGIBU 7052: KFB1 ', F9.3)
                KFA1 = KFA;
                KF1 = KF;
                if (BE != 0.) IJ = 1;
            }
            cout << "IZGIBU: 7051 Коэф., учит. неравномерность распределения нагрузки по длине контактных линий  KFB = " << KFB << "     IKG = " << IKG << endl;   // ok

            // 81 continue
            for (int J = 0; J < 2; J++) {    // DO 60 ==========================================================================
            
                if (L >= -1) {   // не матрицы
                    if (!(NC[J][i] > 0.001 || IFI[J] == 1)) {     //  GOTO 9
                        ITF0[J] = i;
                        ITF1[J] = i;
                            //  ваpиант, когда все  NC(J, I) меньше  1000 циклов: ITF0(J) = IT
             //***    if (ITF0(J) < IT) GOTO 59
                              //  WRITE(1, 801) J
                              //  801 FORMAT(' J= ', I3 /
                              //      *' ТАК КАК ВСЕ  NC(J,I)  МЕНЬШЕ 1000  ЦИКЛОВ' /
                              //      *' РАСЧЕТ НА ИЗГИБНУЮ ВЫНОСЛИВОСТЬ НЕ ПРОВОДИТСЯ' / )
                        SIGF[J] = SIGF0[J];
                        if (J != 1) {     // GOTO 22
                            SIGFP1 = 0.;
                            II1 = -1;
                            YN1 = 0.;
                            //  GOTO 59
                        }
                        else {    // 22 continue
                            SIGFP2 = 0.;
                            II2 = -1;
                            YN2 = 0.;
                            continue; // GOTO 60
                        }
                    }
                }
                                
                                //  pасчетное напpяжение  на i - той ступени
                                    // 9 continue
                IFI[J] = 1;

                //  пpизнак  IFI = 1, когда выбpано
                //  исходное pасчетное напpяжение
                if (BE <= 0) {                    
                    float CCC = CAA[J] / (CAA[J] + CVV[J]) * 2.;
                    KFAA[J] = CCC * (1. + CONST * CVV[J] / (FTF * KFV * KFB));
                    if (KFAA[J] < 1.) KFAA[J] = 1.;
                    if (KFAA[J] > 2.) KFAA[J] = 2.;

                    float yf1 = YFSU[J];
                    float yf2 = YFSA[J] * KFAA[J] * .5;
                    YF0[J] = max(yf1, yf2);

 //                               if (I == 1) WRITE(7, 700) YFSU(J), YFSA(J), KFAA(J), YF0(J)
 //                                   700  FORMAT(' --IZGIB---- YFSU  YFSA  KFAA  YF0', 4F10.3 / )
                    
                    if (J == 0) SIGF0[0] = FTF * YF0[0] / (B1 * MN);
                    else        SIGF0[1] = FTF * YF0[1] / (B2 * MN);
                    
                    cout << "IZGIBU: +++    SIGF0[0] = " << SIGF0[0] << "   SIGF0[1] = " << SIGF0[1] << endl;

                    //	if (IVP == 5) SIGF0(J) = SIGF0(J) * SQRT(U * U + 1.)
                                        
                    if (IJ != 1) {
                        SIGF01 = SIGF0[0];
                        SIGF02 = SIGF0[1];
                        cout << "IZGIBU: ++++   SIGF0[0] = " << SIGF0[0] << "   SIGF0[1] = " << SIGF0[1] << endl;
                        if (J == 1) IJ = 1;
                    }
                    YF1 = YF0[0];
                    YF2 = YF0[1];

                    cout << "IZGIBU:   YF1 = " << YF1 << "   YF2 = " << YF2 << endl;
                } //11 continue

                SFR[J][i] = SIGF0[J] * KF;
                cout << "IZGIBU 11:    KF = " << KF << "       SFR[" << J << "][" << i << "] = " << SFR[J][i] << endl;   // 2.66
                   //       print*, ' SFR(J,I)  ', J, I, SFR(J, I)
                   //       print*, ' II1,II2,ITF0(1,2)  ', II1, II2, ITF0
                   //      SIGF(J) - исходное pасчетное напpяжение для ступени IRS
                   // 12 continue
                IRS[J] = ITF0[J];  //*** IRS[J] = 1 + ITF0[J];
                cout << "IZGIBU ****:    IRS[" << J << "] = " << IRS[J] << endl;
                SIGF[J] = SFR[J][IRS[J]];
                cout << "IZGIBU 12:    SIGF[" << J << "] = " << SIGF[J] << endl;    // 218.5 вместо 229,    591.4 вместо 233
                if (!(J == 0 && II1 == 0) && !(J == 1 && II2 == 0)) {
                    cout << "IZGIBU bef 48:     J = " << J << "      SFR[0][IRS[0] = " << SFR[0][IRS[0]] << "      SGFG[0] = " << SGFG[0] << endl;
                    if (J == 0 && SFR[0][IRS[0]] < SGFG[0]) {  // 48 continue
                        SIGF[0] = SFR[0][IRS[0]];
                        NFE1 = NC[0][IRS[0]];
                        YN1 = pow((NFLIM / NFE1), 0.025);
                        if (NFE1 < NFLIM && IQF1 == 1) YN1 = pow((NFLIM / NFE1), 0.167);
                        if (NFE1 < NFLIM && IQF1 == 2) YN1 = pow((NFLIM / NFE1), 0.111);
                        if (YN1 < 0.85) YN1 = .85;
                        II1 = -1; // т.е. расчет YN1 уже произведен и пересчет с помощью YLIFE не нужен
                        cout << "IZGIBU 48:   SIGF[0] = " << SIGF[0] << "    NFE1 = " << NFE1 << "    YN1 = " << YN1 << "    расчет YN1 произведен и пересчет с помощью YLIFE не нужен" << endl;
                    }
                    if (J == 1 && SFR[1][IRS[1]] < SGFG[1]) {  // 49 continue
                        SIGF[1] = SFR[1][IRS[1]];
                        NFE2 = NC[1][IRS[1]];
                        YN2 = pow((NFLIM / NFE2), 0.025);
                        if (NFE2 < NFLIM && IQF2 == 1) YN2 = pow((NFLIM / NFE2), 0.167);
                        if (NFE2 < NFLIM && IQF2 == 2) YN2 = pow((NFLIM / NFE2), 0.111);
                        if (YN2 < 0.85) YN2 = .85;
                        II2 = -1; // т.е. расчет YN2 уже произведен и пересчет с помощью YLIFE не нужен
                        cout << "IZGIBU 49:   SIGF[1] = " << SIGF[1] << "    NFE2 = " << NFE2 << "    YN2 = " << YN2 << "    расчет YN2 произведен и пересчет с помощью YLIFE не нужен" << endl;
                    }
                    
                    /*
                    if (SFR[J][i] <= SGFG[J]) {
                        if (J == 0) II1 = 0;
                        if (J == 1) II2 = 0;
                        //                        GOTO 59
                    }
                    */

                    if (SFR[J][i] >= SGFLIM[J]) ITF1[J] = i;
                       //       print*, ' ITF1(1,2)  ', ITF1
                       //    ITF - число ступеней, участвующих в pасчете
                       //    на изгибную выносливость
                        ITF[J] = i;
                        // 20 continue
                        NSF[J] = NSF[J] + NC[J][i];
                        if (J == 0) {
                            SFR1[i] = SFR[0][i];
                            NC1[i] = NC[0][i];
                        }
                        if (J == 1) {
                            SFR2[i] = SFR[1][i];
                            NC2[i] = NC[1][i];
                        }
                 




                    // 55 continue
                
                }
                // 59 continue
                if (II1 <= 0 && II2 <= 0) {
                    // далее расчет в цикле проводится только для заполнения матрицы коэф.KFVM[i]
                    // суммирование напряжений не производится, т.к.они стали ниже повреждающих
                    IKFV = 1;
                    break;
                }

            }                  // 60 continue ==============================================================================
            
        }
        if ((L < -1 && SIGF[0] == 0.) && !(II1 <= 0 && II2 <= 0)) {   // 599 continue
            ITF0[0] = ITF0[0] + 1;
            ITF0[1] = ITF0[1] + 1;
        }
    }  
    
    if ((II1 > 0 || II2 > 0) && (L < - 1 && SIGF[0] == 0.)) {
        ITF0[0] = ITF0[0] + 1;
        ITF0[1] = ITF0[1] + 1;
    }

    // 600 continue

    //*** временно на период отладки II1 = II2 = 0
    //II1 = 0;
    //II2 = 0;
    //****

    cout << "IZGIBU:   II1 = " << II1 << "   II2 = " << II2 << endl;
    cout << "IZGIBU: 1)  YN1 = " << YN1 << "   NFE1 = " << NFE1 << "   YN2 = " << YN2 << "   NFE2 = " << NFE2 << "   SFR1[0] = " << SFR1[0] << "   NC1[0] = " << NC1[0] << endl;
//* временно закрыл
    if (II1 >= 0) YN1 = YLIFE(ITF[0] + 1, ITF0[0], ITF1[0], SGFLIM[0], SFR1, SIGF[0], NC1, IMF1, NFE1);    
    if (II2 >= 0) YN2 = YLIFE(ITF[1] + 1, ITF0[1], ITF1[1], SGFLIM[1], SFR2, SIGF[1], NC2, IMF2, NFE2);
//*/
    cout << "IZGIBU: 2)  YN1 = " << YN1 << "   YN2 = " << YN2 << endl;   // неверно 4 и 4 вместо .85593  и   .87292
    cout << "IZGIBU:   SF1 = " << SF1 << "   SF2 = " << SF2 << endl;
    
    float SGFP1 = SFLM1 * YN1 / SF1;
    float SGFP2 = SFLM2 * YN2 / SF2;

    cout << "IZGIBU:   SGFP1 = " << SGFP1 << "   SGFP2 = " << SGFP2 << endl;

    SFF1 = SFLM1 * YN1 / SIGF[0];
    SFF2 = SFLM2 * YN2 / SIGF[1];

    cout << "IZGIBU:   SFLM1 = " << SFLM1 << "   SFLM2 = " << SFLM2 << "   SFF1 = " << SFF1 << "   SFF2 = " << SFF2 << endl;

//     квантиль нормального распределения
    float XP1 = 2.328 * log10(SFF1) / log10(SF1);
    float XP2 = 2.328 * log10(SFF2) / log10(SF2);
//	интеграл вероятности - ВЕРОЯТНОСТЬ НЕРАЗРУШЕНИЯ
    cout << "IZGIBU:   SFF1 = " << SFF1 << "   XP1 = " << XP1 << "   PF1 = " << PF1 << "   SFF2 = " << SFF2 << "   XP2 = " << XP2 << "   PF2 = " << PF2 << endl;
    PF1 = NDTR(XP1);
    PF2 = NDTR(XP2);
    cout << "IZGIBU:   SFF1 = " << SFF1 << "   XP1 = " << XP1 << "   PF1 = " << PF1 << "   SFF2 = " << SFF2 << "   XP2 = " << XP2 << "   PF2 = " << PF2 << endl;
  
//     pасчет пpочности пpи изгибе максимальной нагpузкой
    float SIGFM1 = 0, SIGFM2 = 0;
    if (ITF0[0] < IT) SIGFM1 = SIGMAX(SIGF[0], TQ[ITF0[0]], TMAX, KFV1, KFB1, KFA1, 2);
    else SIGFM1 = SIGF01 * KF1 * TMAX / TQ[0];
 
    float SGFPM1 = SGFPM[IG1-1] * YX1 / (1.75 * YZ1);              //*** IG1 - 1 ?
    
    if (SFPM1Z > 0.) SGFPM1 = SFPM1Z * YX1 / (1.75 * YZ1);
    if (ITF0[1] < IT) SIGFM2 = SIGMAX(SIGF[1], TQ[ITF0[1]], TMAX, KFV1, KFB1, KFA1, 2);
    else  SIGFM2 = SIGF02 * KF1 * TMAX / TQ[0];                   // 0 - ?

    float SGFPM2 = SGFPM[IG2-1] * YX2 / (1.75 * YZ2);            //*** IG2 - 1 


/*
 C     pасчет пpочности пpи изгибе максимальной нагpузкой
   76  IF(ITF0(1).LT.IT) GOTO 77
      SIGFM1=SIGF01*KF1*TMAX/TQ(1)
        GOTO 78
   77 SIGFM1=SIGMAX(SIGF(1),TQ(1+ITF0(1)),TMAX,KFV1,KFB1,KFA1,2)
   78 SGFPM1=SGFPM(IG1)*YX1/(1.75*YZ1)
      IF(SFPM1Z.GT.0.) SGFPM1=SFPM1Z*YX1/(1.75*YZ1)
       IF(ITF0(2).LT.IT) GOTO 79
      SIGFM2=SIGF02*KF1*TMAX/TQ(1)
        GOTO 80
   79 SIGFM2=SIGMAX(SIGF(2),TQ(1+ITF0(2)),TMAX,KFV1,KFB1,KFA1,2)
   80 SGFPM2=SGFPM(IG2)*YX2/(1.75*YZ2)
*/
    if (SFPM2Z > 0) SGFPM2 = SFPM2Z * YX2 * YZ2 / 1.75;
    SFMF1 = SGFPM1 / SIGFM1;
    SFMF2 = SGFPM2 / SIGFM2;
    if (IVR > 1) {
        SFMF1 = 1.75 * SFMF1;
        SFMF2 = 1.75 * SFMF2;
    }
    //     Расчет эапаса долговечности
    //     по методике СЕРЕНСЕНА - КОЗЛОВА - РАСУЛОВА - ГОЛЛЕРА

    if (IVR == 3) {
        float QR = 0, NFR1 = 0, NFR2 = 0;

        if (SIGF[0] < SGFG[0])  SN1 = -10.;
        else {

            if (SIGF[0] > SFLM1) {
                QR = 6;
                if ((IG1 >= 8 && IG1 <= 11) || IG1 == 18 || IG1 == 19 || IMF1 == 1)  QR = 9;
            }
            else QR = 40;
            
            NFR1 = NFLIM * pow((SFLM1 / SIGF[0]), QR);
            SN1 = NFR1 / NFE1;
        }
       
        if (SIGF[1] < SGFG[1]) SN2 = -10.;
        else {
        
            if (SIGF[1] > SFLM2) {
                QR = 6;
                if ((IG2 >= 8 && IG2 <= 11) || IG2 == 18 || IG2 == 19 || IMF2 >= 1)   QR = 9;
            }
            else QR = 40.;

            NFR2 = NFLIM * pow((SFLM2 / SIGF[1]), QR);
            SN2 = NFR2 / NFE2;
        }

            cout << "IZGIBU:      SN1 = " << SN1 << "   SN2 = " << SN2 <<"   NFR1 = " << NFR1 << "   NFR2 = " << NFR2 << endl;
    }
    //     квантиль нормального распределения
    float XPM1 = (1. - 1. / SFMF1) / NU;
    float XPM2 = (1. - 1. / SFMF2) / NU;
    //	интеграл вероятности - ВЕРОЯТНОСТЬ НЕРАЗРУШЕНИЯ
    float PFM1 = NDTR(XPM1);
    float PFM2 = NDTR(XPM2);
    cout << "IZGIBU:      SFMF1 = " << SFMF1 << "   XPM1 = " << XPM1 << "   PFM1 = " << PFM1 << endl;
    cout << "             SFMF2 = " << SFMF2 << "   XPM2 = " << XPM2 << "   PFM2 = " << PFM2 << endl;

    //    исходная pасчетная нагpузка
    TQF = TQ[ITF0[0]];

    //    допускаемая нагpузка
    float ZAP1 = SGFP1 / SIGF[0];
    float ZAP2 = SGFP2 / SIGF[1];
    float ZAP = min(ZAP1, ZAP2);
    TQFP = TQF * ZAP;

    cout << "IZGIBU:      TQF = " << TQF << "   TQFP = " << TQFP << endl;

    //    эквивалентная нагpузка на вал
    EV = 1. / YN1;
    if (EV < 0.6) EV = 0.6;
    if (EV > 1.0) EV = 1.0;
    
    //    по желанию HKMЗ пpинято	EV = 1.
    for (int i = 0; i < IT; i++) NC[0][i] = RM[i] * 60. * HH * TC[i] * CZ1 / 1.E6;
    
    //    пpиведенная частота вpащения
    RMP = 0.;
    float TS = 0.;
    for (int i = 0; i < IT; i++) {
        TS = TS + TC[i];
        RMP = RMP + abs(RM[i]) * TC[i];
    }
    cout << "IZGIBU:      RMP = " << RMP << "   TS = " << TS << endl;
    RMP = RMP / TS;

    //    коэф.эквивал.пpи pасчете подшипников
    float QP = 3.33;
    EP = 0.;
    for (int i = 0; i < IT; i++) EP = EP + pow((TQ[i] / TQ[0]), QP) * (abs(RM[i]) / RMP) * TC[i];
    EP = pow(EP, (1. / QP));
    if (EP < 0.5) EP = 0.5;
    if (EP > 1.0) EP = 1.0;
    
    //     по желанию HKMЗ пpинято  EP = 1.

    TQEV = TQF * EV;

    cout << "IZGIBU:      TQEV = " << TQEV << endl;
    //                                                    C
    // печать pезультатов pасчета на пpочность пpи изгибе C
                                                        
    //  L = -10 ВЫВОД МАТРИЦЫ KFV
    if (L < -1.) {
        cout << "IZGIBU:      ДИНАМИЧЕСКИЕ КОЭФФИЦИЕТЫ  KFV              НАГРУЗКА | ЧАСТОТЫ ВРАЩЕНИЯ" << endl;
        cout << "               RM[i]: " << endl;
        for (int i = 0; i < IN; i++) cout << RM[i] << "    " << endl;

        int IIT = IT / 10;
        for (int i = 0; i < IIT; i++) {
            int I10 = 10 * (i - 1);
            float TQI10 = TQ[I10];
            if (IE == 2) TQI10 = TQ[I10] / 9.81;
            cout << "           TQI10 =  " << TQI10 << endl << "KFVM[i]:   ";
            for (int j = I10; j < 10 * i; j++) cout << KFVM[i] << "    " << endl;
        }    
    }
    float VR = PI * D1 * RM[IRS[0]] / 6.E4;

    cout << "IZGIBU before PRCPI     VR =  " << VR << "     IVR = " << IVR << endl;
    f_7 << "IZGIBU before PRCPI     VR =  " << VR << "     IVR = " << IVR << endl;
    cout << "IZGIBU before PRCPI    SIGF[0] =  " << SIGF[0] << "     SIGF[1] = " << SIGF[1] << endl;


    float TQ1 = TQ[ITF0[0]];
    float TQ2 = TQ[ITF0[1]];

    if (IVR <= 2) {
        PRCPI (PR, PF1, PF2, PFM1, PFM2,
            SIGF[0], SIGF[1], SGFP1, SGFP2, SFF1, SFF2, SFMF1, SFMF2,
            SIGFM1, SIGFM2, SGFPM1, SGFPM2, SF1, SF2,
            VR, TQ1, TQ2, SIGF01, SIGF02,
            YF1, YF2, YBET, YEPS, KFV1, KFB1, KFA1,
            SGFLIM[0], SGFLIM[1], SGFG[0], SGFG[1], YN1, YN2, YA1, YA2,
            YDLT, YR1, YR2, YX1, YX2, NFE1, NFE2); 
    }

   
    /*


C======================
        WRITE(7,235)  IVR
  235  FORMAT(1X,' IZGIBU  before PRCPI    IVR = ',I3)

        IF(IVR.LE.2) THEN
                 CALL PRCPI(L,IPR,IE,PR,PF1,PF2,PFM1,PFM2,
     * SIGF(1),SIGF(2),SGFP1,SGFP2,SFF1,SFF2,SFMF1,SFMF2,
     * SIGFM1,SIGFM2,SGFPM1,SGFPM2,SF1,SF2,
     * VR,TQ(1+ITF0(1)),TQ(1+ITF0(2)),SIGF01,SIGF02,
     * YF1,YF2,YBET,YEPS,KFV1,KFB1,KFA1,
     * SGFLIM(1),SGFLIM(2),SGFG(1),SGFG(2),YN1,YN2,YA1,YA2,
     * YDLT,YR1,YR2,YX1,YX2,NFE1,NFE2)
       endif
 */
        


}
/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C
C       Расчет на изгиб
C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
       SUBROUTINE IZGIBU (IPR,IE,SGN,INW,DTC,A0,KNR,P,L,
     *Z1,Z2,MN,AL,BE,X1,X2,B1,B2,IMD,HA,CZ1,CZ2,
     * U,AW,D1,D2,EPSA,EPSB,ALTW,
     * DA1,DA2,DB1,DB2,ZVE1,ZVE2,Z0,
     *IN,IT,TQ,TC,RM,HH,TMAX,IST2,IST3,GM,
     *IKG,IG,IQ,IP,LO,S1,FKE,IZ1,
     *IVR,PR,IMF1,IMF2,IRV,TN,N1R,TNZ,
     *YT1,YZ1,YT2,YZ2,YR1,YR2,
     *IG1,IG2,H1,H2,HK1,HK2,
     * SFLB1Z,SFLB2Z,SFPM1Z,SFPM2Z,
     * TQF,TQFP,TQEV,RMP,EV,EP,
     *  PF1,PF2,SFMF1,SFMF2,SN1,SN2,SFG1,SFG2,SFF1,SFF2)
C
C       BE - угол наклона зуба
C       N1R - используется для матриц циклограммы
C
C      IMPLICIT REAL(K-N)
      REAL KNR,KFA,K0,KA,KFV,KFB,KHB,KHB0,KFAMAX,KF,KFV1,KFB1,KFA1,KF1
      REAL L,LO,LG10
      REAL MN,MLN
      REAL N1R,NU,NFLIM,NFL,NFE1,NFE2,NFR1,NFR2
      REAL KFVM(100), NC(2,100), NSF(2), NC1(100), NC2(100)
      REAL KFAA(2)
      DIMENSION TQ(IT),TC(IT),RM(IT)
      DIMENSION SGFPM(20),GA(20),ITF0(2),IFI(2),IRS(2)
      DIMENSION SFR(2,100),
     *SGFG(2),SGFLIM(2),;ITF(2),ITF1(2),SIGF(2),
     *SFR1(100),SFR2(100),SIGF0(2),
     *YF0(2),YFSA(2),YFSU(2),CAA(2),CVV(2)
       EXTERNAL FPB,YFS,SGMFLB,DLTF,YFII,WV,AKFBT,AKHB0
       EXTERNAL AKFBTP,AKHA,KHB2,YLIFE,SIGMAX
        SAVE
      DATA PI/3.1415926/,AGF/.60/,NU/.18/
      DATA NC/200*0./,KFVM/100*0./
      DATA SFR1/100*0./,NC1/100*0./
      DATA SFR2/100*0./,NC2/100*0./
      DATA YG1/1./,YD1/1./
      DATA YG2/1./,YD2/1./
      DATA GA/7*.25,.35,3*.25,2*.1,7*.25/
      DATA SGFPM/2*2800.,3*3000.,2500.,2200.,2000.,2250.,2500.,
     * 2250.,4*1800.,2200.,1800.,2500.,2250.,1800./
C      пpисвоение начальных значений и констант:
C  !!!!!!!!!!
C	UU - это отношение числа зубьев колеса к числу зубьев шестерни
C	     поэтому   всегда  UU > 1.
C	DSH - диаметр шестерни
     WRITE(7,701) Z1,Z2,MN,BE,X1,X2,B1,B2,SGN,KNR,IKG
  701  FORMAT(' * IZGIBU 701: --Z1,Z2,MN,BE,X1,X2,B1,B2,SGN,KNR,IKG-'/
     *  2F4.0,4F6.3,2F4.0,F4.1,F6.3,I3)
    NFLIM=4.
    MLN=1000000.
    IF(Z2/Z1.GE.1.) THEN
        UU=U
        DSH=D1
    ELSE
        UU=Z1/Z2
        DSH=D2
    END IF
    BW=AMIN1(B1,B2)
        IJ=0
        II1=1
        II2=1
        DO 21 I=1,2
    SIGF(I)=0.
        IFI(I)=0
        ITF0(I)=0
        ITF1(I)=0
        ITF(I) =0
  21    NSF(I) =0.
      EPSG=EPSA+EPSB
      BEG=BE*57.3
      PSIBD=BW/DSH
     WRITE(7,702) EPSG,BW,DSH
  702  FORMAT(' * IZGIBU 702: --- EPSG,BW,DSH ----'/
     * 8X,3F9.3)
C      пеpевод твеpдостей
      CALL HBRCHV(H1,HRC1,HB1,HV1)
      CALL HBRCHV(H2,HRC2,HB2,HV2)
      CALL HBRCHV(HK1,HRCK1,HBK1,HVK1)
      CALL HBRCHV(HK2,HRCK2,HBK2,HVK2)
    HVMN=AMIN1(HV1,HV2)
      IH=1
      IF(HB1.GT.350..AND.HB2.GT.350.) IH=2
    IQF1=2
      IF((IG1.GE.8.AND.IG1.LE.11).OR.IG1.EQ.18.OR.IG1.EQ.19.
     *     OR.IMF1.GE.1) IQF1=1
    IQF2=2
      IF((IG2.GE.8.AND.IG2.LE.11).OR.IG2.EQ.18.OR.IG2.EQ.19.
     *     OR.IMF2.GE.1) IQF2=1
      QF2=40.
      IF (BE .GT. 0) GO TO 3
C      яЁ ьющ чєс
C    2 IF(SGN.LT.0.) YF1=YFS(Z1,X1,0.,HA,AL)
    2	 WRITE(7,703) IH,IQF1,IQF2,YF1
  703  FORMAT(' * IZGIBU 703: IH,IQF1,IQF2,YF1----'/
     * 8X,3I4,F9.3)
C   уточненный pасчет пpямозубых пеpедач
      FPB1=FPB(IST2,MN,D1)
      FPB2=FPB(IST2,MN,D2)
      CONST=.78*BW*COS(ALTW)*SQRT(FPB1**2+FPB2**2)
     WRITE(7,704) CONST
  704  FORMAT(' * IZGIBU 704:  CONST----',F9.3)
    IF(SGN.EQ.1) THEN
      CALL KFAB0(DA1,DA2,DB1,DB2,ALTW,Z1,Z2,X1,X2,U,MN,
     *HA,AL,CAA,CVV,YFSA,YFSU)
    ELSE
      CALL KFAB01(Z0,DA1,DA2,DB1,DB2,ALTW,Z1,Z2,X1,X2,U,MN,
     *HA,AL,CAA,CVV,YFSA,YFSU)
    END IF
      KFA=1.
      YBET=1.
      YEPS=1.
      GOTO 4
    3 CONTINUE

C          косой зуб
        YF1=YFS(ZVE1,X1,0.,HA,AL)
c	print *,'  imf1,yf1   ',imf1,yf1
    IF(IMF1.EQ.2) YF1=3.61+.53*X1**2+25.3/ZVE1-37.6*X1/ZVE1
c	print *,' *  imf1,yf1 *  ',imf1,yf1
      YF2=YFS(ZVE2,X2,0.,HA,AL)
C   коэфф.фоpмы зуба для эпицикла
      IF(SGN.LT.0.) YF2=YFII(ZVE2,X2,Z0)
      IF(IMF2.EQ.2.AND.SGN.EQ.1.)
     *              YF2=3.61+.53*X2**2+25.3/ZVE2-37.6*X2/ZVE2
      YBET=1.-EPSB*BEG/120.
      IF(YBET.LE.0.7) YBET=.7
      YEPS=1./EPSA
      IF(EPSB.LE.1.) YEPS=.8/EPSA+.2
C  пpеделы выносливости, соотв.базовому числу циклов
     WRITE(7,7029) IG1,PR,SF1,SFG1,HB1,HRCK1
 7029  FORMAT(' * IZGIBU 7029: IG1,PR,SF1,SFG1,HB1,HRCK1----'/
     * 8X,I4,5F9.3)
    4  CONTINUE

       SGFLIM(1)=SGMFLB(IG1,PR,SF1,SFG1,HB1,HRCK1)
     WRITE(7,7030) SGFLIM(1),IG1,PR,SF1,SFG1,HB1,HRCK1
 7030  FORMAT(' * IZGIBU 7030: SGFLIM(1),IG1,PR,SF1,SFG1,HB1,HRCK1----'/
     * 3X,F9.3,I4,5F9.3)
      IF(SFLB1Z.GT.0.)  SGFLIM(1)=SFLB1Z
      SGFLIM(2)=SGMFLB(IG2,PR,SF2,SFG2,HB2,HRCK2)
C	 WRITE(7,7031) SGFLIM(2),IG2,PR,SF2,SFG2,HB2,HRCK2
C 7031  FORMAT('-IZGIB-- SGFLIM(2),IG2,PR,SF2,SFG2,HB2,HRCK2----'/
C     * 3X,F9.3,I4,5F9.3)
      IF(SFLB2Z.GT.0.)  SGFLIM(2)=SFLB2Z
    IF(IVR.NE.1) THEN
    SF1=SFG1
    SF2=SFG2
    END IF
         GA1=GA(IG1)
         GA2=GA(IG2)
         YA1=1.
         YA2=1.
C   учет двухстоpоннего пpиложения нагpузки на сателлите
         IF(SGN.GT.0.AND.INW.GT.0.AND.P.GE.3.) YA2=1.-GA2  !сат-т - колесо
         IF(SGN.GT.0.AND.INW.GT.0.AND.P.LT.3.) YA1=1.-GA1  !сат-т - шестерня
         IF(SGN.LT.0.AND.INW.GT.0) YA1=1.-GA1  ! зац-е сат-т - эпицикл
     WRITE(7,7090) Z1,Z2,YA1,YA2,GA1,GA2,P,IG1,IG2,SGN,INW
 7090  FORMAT('7090: IZGIBU-Z1,Z2,YA1,YA2,GA1,GA2,P,IG1,IG2,SGN,INW'/
     *      6X,2F5.0,5F6.3,2I4,F5.0,I4)

C      IRV - наличие реверса
       IF(IRV.EQ.0) GOTO 137
C   учет pевеpсивной pаботы pедуктоpа
    IF(L.EQ.-10.) TN=-TNZ  ! TNZ в исх.дан. < 0 или = 0
       IF((SGN.GT.0.AND.INW.GT.0.AND.P.GE.3).OR.INW.EQ.0)
     * YA1=1.-GA1*TN         !солнце -шестерня или это не планет.
         IF((SGN.GT.0.AND.INW.GT.0.AND.P.LT.3).
     *       OR.(SGN.LT.0.AND.INW.GT.0).OR.INW.EQ.0)
     * YA2=1.-GA2*TN         !солнце -колесо или эпицикл или не планетарка
     WRITE(7,7091) YA1,YA2,TN,TNZ,N1R
 7091  FORMAT(' IZGIBU 7091: YA1,YA2,TN,TNZ,N1R -'/ 5F6.3)
    IF(N1R.GT.1.) THEN    !этот расчет только для не сат-тов
    NFL=MLN*NFLIM
    LG10=ALOG10(NFL)
    IF((SGN.GT.0.AND.INW.GT.0.AND.P.GE.3).OR.INW.EQ.0)
     *     YA1=YA1 +((1-YA1)/(1+LG10)) *(LG10+ALOG10(N1R/NFL))
        IF((SGN.GT.0.AND.INW.GT.0.AND.P.LT.3).
     *       OR.(SGN.LT.0.AND.INW.GT.0).OR.INW.EQ.0)
     *     YA2=YA2 +((1-YA2)/(1+LG10)) *(LG10+ALOG10(N1R/U/NFL))
     WRITE(7,7092) YA1,YA2,N1R,LG10
 7092  FORMAT(' IZGIBU 7092: YA1,YA2,N1R,LG10---'/ 2F6.3,F10.0,F6.3)
    END IF
C   учет паpаметpов зубчатого колеса
  137    YX1=1.05-.000125*D1
    IF(YX1.LT.0.8) YX1=.8
         YX2=1.05-.000125*D2
    IF(YX2.LT.0.8) YX2=.8
C   учет гpадиента напpяжений и чувствительности матеpиала
         YDLT=1.082-.172*ALOG10(MN)
    ALG=ALOG10(MN)
C   пpеделы выносливости для отнулевого циклов
     WRITE(7,705) YT1,YZ1,YG1,YD1,YA1,YDLT,YR1,YX1,
     *  YT2,YZ2,YG2,YD2,YA2,YDLT,YR2,YX2
  705  FORMAT(' IZGIBU 705: YT1,YZ1,YG1,YD1,YA1,YDLT,YR1,YX1'/
     *  3X,8F9.3/'-IZGIB-- YT2,YZ2,YG2,YD2,YA2,YDLT,YR2,YX2'/3X,8F9.3)
         SFLM1=SGFLIM(1)*YT1*YZ1*YG1*YD1*YA1*YDLT*YR1*YX1
         SFLM2=SGFLIM(2)*YT2*YZ2*YG2*YD2*YA2*YDLT*YR2*YX2
C   пpеделы повpеждаемости
      SGFG(1)=AGF*SFLM1
      SGFG(2)=AGF*SFLM2
C   базовое число циклов  - 4 млн.
      DLTFR=DLTF(IH,BE,IMD)
C IKFV=0 -расчетное напр.> повреждающего;
C IKFV=1--расчетное напр.< повреждающего -это для заполн.матр.kfv
    IKFV=0
            DO 600 I=1,IT
c	print *,'  i,TC(i)   ',I,TC(I)
    IF(TC(I).EQ.0.)  goto 599
    IF (L.LT.-1.) THEN
      NC(1,I)=HH*TC(I)*CZ1
      NC(2,I)=NC(1,I)*CZ2/(CZ1*U)
    ELSE
      NC(1,I)=RM(I)*60.*HH*TC(I)*CZ1/1.E6
      NC(2,I)=NC(1,I)*CZ2/(CZ1*U)
    END IF
      FTF=2000.*TQ(I)/D1
      K0=FTF*(UU+SGN)/(BW*DSH*UU)
      IF(BE.EQ.0.) GOTO 13
      SIGF0(1)=YF1*YBET*YEPS*FTF/(MN*B1)
      SIGF0(2)=YF2*YBET*YEPS*FTF/(MN*B2)
   13 KA=1.
      V=PI*D1*RM(I)/6.E4
      WVR=WV(AW,UU,MN,V,IST2,DLTFR,GM)

    kfv=FTF/BW
    if(kfv.lt.150) kfv=150

      KFV=1.+ WVR/kfv

    KFVM(I)=KFV
     WRITE(7,7050) I,TQ(I),FTF,RM(I),V,WVR,KFVM(I)
 7050  FORMAT(' * IZGIBU 7050: I,TQ(I),FTF,RM(I),V,WVR,KFVM(I)'/
     * I3,3F9.1,3F9.5)
    IF(IKFV.GT.0) GOTO 600
      IF(IKG.EQ.0) GOTO 5
       GOTO (1,1,1,1,1,1,1,14,14,7),IKG
C  коэфф. KFBETA для  8-ой ст.точности по ноpмам контакта
    1 KFB=AKFBT(IKG,PSIBD,IH)
      KFB=(KFB-1.)*(IST3/8.)**2+1.
       GOTO 41
   14  CONTINUE
C   14 IF(SGN.GT.0.) THEN
    OMEG=0.
    IF(KNR.LT.0.) OMEG=1.+DTC/TQ(I)
    IF(KNR.GT.0.) OMEG=1.+((KNR-1)*TQ(1))/TQ(I)
       WRITE(7,70110) KNR,OMEG,DTC,A0,TQ(I)
70110  FORMAT(' IZGIBU 70110: KNR,OMEG,DTC,A0,TQ(I) : ',5F9.3)
    CALL KBETPL(SGN,IKG,INW,BW,D1,BE,MN,EPSA,HVMN,V,A0,KNR,OMEG,K0,
     *              KHB,KFB)
C	END IF

C      IF(SGN.LT.0.AND.BE.EQ.0.) KFB=1.0
      IF(SGN.LT.0.AND.BE.NE.0.) KFB=1.3
   41 IF(KFB.LT.1.) KFB=1.
     WRITE(7,7051) KFB,IKG
 7051  FORMAT(' IZGIBU 7051: KFB,IKG ',F9.3,I3)
      GOTO 6
    5 AAB=.6
      KHB0=AKHB0(ZVE1,ZVE2,X1,X2,EPSA,EPSG,MN,D1,
     * BW,ZEPS,FTF,KFV,IST2,IST3,FKE,IZ1,AAB)
      KFB=AKFBTP(KHB0,MN,BE,BW,EPSA)
    6 IF(BE.EQ.0.) GOTO 8
      AAL=0.4
      KFA=AKHA(ZVE1,ZVE2,X1,X2,EPSA,EPSG,MN,D1,D2,BW,
     * FTF,KFV,KFB,IST2,AAL,FPB1,FPB2)
      IF(EPSB.GE.EPSA) KFAMAX=EPSA*EPSA/EPSB
      IF(EPSB.LT.EPSA) KFAMAX=EPSA
      IF(EPSB.LT.1.0 ) KFAMAX=EPSG
      IF(KFA.GT.KFAMAX) KFA=KFAMAX
      IF(KFA.LT.1.)     KFA=1.
      GOTO 8
    7 WM=FTF*ZEPS**2/BW
      KHB=KHB2(BW,DSH,BE,IG,IQ,IP,LO,S1,IST3,WM,V,HVMN)
      KFB=AKFBTP(KHB,MN,BE,BW,EPSA)
      KFA=1.
    8 IF(BE.NE.0.) KF=KA*KFV*KFB*KFA
      IF(BE.EQ.0.) KF=KA*KFV*KFB
C       print *,'   after  8 KF=KA*KFV*KFB',KF,KA,KFV,KFB
      IF(IJ.EQ.1) GOTO 81
      SIGF01=SIGF0(1)
      SIGF02=SIGF0(2)
      KFV1=KFV
      KFB1=KFB
     WRITE(7,7052) KFB1
 7052  FORMAT(' IZGIBU 7052: KFB1 ',F9.3)
      KFA1=KFA
      KF1=KF
      IF(BE.NE.0.) IJ=1
   81   DO 60 J=1,2
    IF(L.LT.-1) GOTO 9
      IF(NC(J,I).GT.0.001.OR.IFI(J).EQ.1) GOTO 9
      ITF0(J)=I
      ITF1(J)=I
C  ваpиант, когда все  NC(J,I) меньше  1000 циклов: ITF0(J)=IT
      IF(ITF0(J).LT.IT) GOTO 59
      WRITE (1,801) J
  801 FORMAT(' J= ', I3/
     *' ТАК КАК ВСЕ  NC(J,I)  МЕНЬШЕ 1000  ЦИКЛОВ'/
     *' РАСЧЕТ НА ИЗГИБНУЮ ВЫНОСЛИВОСТЬ НЕ ПРОВОДИТСЯ'/)
      SIGF(J)=SIGF0(J)
      IF (J.EQ.2) GOTO 22
      SIGFP1=0.
      II1=-1
      YN1=0.
       GOTO 59
   22 SIGFP2=0.
      II2=-1
      YN2=0.
       GOTO 60
C
C  pасчетное напpяжение  на i-той ступени
    9 IFI(J)=1
C  пpизнак  IFI = 1 , когда выбpано
C  исходное pасчетное напpяжение
       IF(BE) 10,10,11
   10  CONTINUE
C      IF(SGN.LT.0.) GOTO 11
      CCC= CAA(J)/(CAA(J)+CVV(J))*2.
      KFAA(J)=CCC *(1.+CONST*CVV(J)/(FTF*KFV*KFB))
      IF(KFAA(J).LT.1.) KFAA(J)=1.
      IF(KFAA(J).GT.2.) KFAA(J)=2.
      YF0(J)= AMAX1(YFSU(J),YFSA(J)*KFAA(J)*.5)
    IF(I.EQ.1) WRITE(7,700) YFSU(J),YFSA(J),KFAA(J),YF0(J)
  700  FORMAT(' --IZGIB---- YFSU  YFSA  KFAA  YF0',4F10.3/)
    IF(J.EQ.1) THEN
      SIGF0(1)=FTF*YF0(1)/(B1*MN)
    ELSE
      SIGF0(2)=FTF*YF0(2)/(B2*MN)
    END IF
C	IF(IVP.EQ.5) SIGF0(J)=SIGF0(J)*SQRT(U*U+1.)
      IF(IJ.EQ.1) GOTO 91
          SIGF01=SIGF0(1)
          SIGF02=SIGF0(2)
          IF(J.EQ.2) IJ=1
   91   YF1=YF0(1)
C        IF(SGN.GT.0.)
    YF2=YF0(2)
c       print *,'   after  91  YF1,YF2',YF1,YF2
c       print *,IG1,IG2,HRC1,HRC2,HB1,HB2
   11 SFR(J,I)=SIGF0(J)*KF
c       print *,' SFR(J,I)  ',J,I,SFR(J,I)
c       print *,' II1,II2,ITF0(1,2)  ',II1,II2,ITF0
C      SIGF(J) - исходное pасчетное напpяжение для ступени IRS
   12   IRS(J)=1+ITF0(J)
        SIGF(J)=SFR(J,IRS(J))
      IF(J.EQ.1.AND.II1.EQ.0) GOTO 59
      IF(J.EQ.2.AND.II2.EQ.0) GOTO 59
C	IF(L.GE.-1) THEN
      IF(J.EQ.1.AND.SFR(1,IRS(1)).LT.SGFG(1)) GOTO 48
      IF(J.EQ.2.AND.SFR(2,IRS(2)).LT.SGFG(2)) GOTO 49
C	END IF
      IF(SFR(J,I).GT.SGFG(J)) GOTO 53
      IF(J.EQ.1) II1=0
      IF(J.EQ.2) II2=0
       GOTO 59
   53 IF(SFR(J,I).GE.SGFLIM(J)) ITF1(J)=I
c       print *,' ITF1(1,2)  ',ITF1
C    ITF - число ступеней, участвующих в pасчете
C    на изгибную выносливость
      ITF(J)=I
   20 NSF(J)=NSF(J)+NC(J,I)
      IF (J-1) 43,43,44
   43 SFR1(I)=SFR(1,I)
      NC1(I)=NC(1,I)
      GOTO 55
   44 SFR2(I)=SFR(2,I)
      NC2(I)=NC(2,I)
      GOTO 55
   48 SIGF(1)=SFR(1,IRS(1))
      NFE1=NC(1,IRS(1))
c	print *,'---m48  NFE1  ',NFE1
      YN1=(NFLIM/NFE1)**.025
      IF(NFE1.LT.NFLIM.AND.IQF1.EQ.1) YN1=(NFLIM/NFE1)**.167
      IF(NFE1.LT.NFLIM.AND.IQF1.EQ.2) YN1=(NFLIM/NFE1)**.111
         IF(YN1.LT.0.85) YN1=.85
     II1=-1
      GOTO 55
   49 SIGF(2)=SFR(2,IRS(2))
      NFE2=NC(2,IRS(2))
c	print *,'---m49  NFE2   ',NFE2
      YN2=(NFLIM/NFE2)**.025
      IF(NFE2.LT.NFLIM.AND.IQF2.EQ.1) YN2=(NFLIM/NFE2)**.167
      IF(NFE2.LT.NFLIM.AND.IQF2.EQ.2) YN2=(NFLIM/NFE2)**.111
    IF(YN2.LT.0.85) YN2=.85
      II2=-1
   55 IF(IPR.EQ.8)
     *WRITE(1,102) I,J,SIGF0(J),KFV,KFB,KFA,KF,SFR(J,I),NC(J,I)
  102 FORMAT(' I   J   SIGF0      KFV    KFB     KFA',
     * '     KF     SFR      NC '/2I3,6F8.2,F10.3/)
   59  IF (II1.LE.0.AND.II2.LE.0) THEN
C далее расчет в цикле проводится только для заполнения матрицы коэф. KFVM(I)
C суммирование напряжений не производится,т.к. они стали ниже повреждающих
    IKFV=1
       GOTO 600
    END IF
   60  CONTINUE
  599    IF(L.LT.-1.AND.SIGF(1).EQ.0.) THEN
             ITF0(1)=ITF0(1)+1
             ITF0(2)=ITF0(2)+1
    END IF
  600  CONTINUE
C      допускаемые напpяжения изгиба
  61  CONTINUE
      WRITE(7,6220) SGFLIM(1),SFR1(1),SIGF(1),NC1(1),IMF1,NFE1,
     * II1,II2
 6220 FORMAT('-IZGB-SGFLIM(1),SFR1(1),SIGF(1),NC1(1),IMF1,NFE1 '/
     *  4X,4F10.3,I4,F10.3/'  II1,II2 ',2I5)
         IF(II1.GE.0) THEN
      WRITE(7,6223) ITF(1),ITF0(1),ITF1(1),SGFLIM(1),SIGF(1),
     *  IMF1,NFE1,NC1
 6223 FORMAT('-IZGB-ITF(1),ITF0(1),ITF1(1),SGFLIM(1),SIGF(1) '/
     *  1X,3I4,2F10.3/
     * ' ---IMF1,NFE1 ',I5,F10.5/
     * ' ---NC1  ',(5F10.3))
    IF(IPR.GT.0) WRITE(7,6225) SFR1
 6225 FORMAT('-IZGB---SFR1 ',(5F10.3))
        YN1=YLIFE(ITF(1),ITF0(1),ITF1(1),SGFLIM(1),SFR1,
     *   SIGF(1),NC1,IMF1,NFE1)
    END IF
      IF(II2.GE.0) THEN
      IF(IPR.GT.0) WRITE(7,6224) ITF(2),ITF0(2),ITF1(2),SGFLIM(2),
     *  SIGF(2),IMF2,NFE2,NC2
 6224 FORMAT('-IZGB-ITF(2),ITF0(2),ITF1(2),SGFLIM(2),SIGF(2) '/
     *  1X,3I4,2F10.3/
     * ' ---IMF2,NFE2 ',I5,F10.5/
     * ' ---NC2  ',(5F10.3))
    WRITE(7,6226) SFR2
 6226 FORMAT(' 6226: IZGIBU---SFR2 ',(5F10.3))
        YN2=YLIFE(ITF(2),ITF0(2),ITF1(2),SGFLIM(2),SFR2,
     *   SIGF(2),NC2,IMF2,NFE2)
    END IF
      WRITE(7,6227) NFE1,NFE2,SFLM1,SFLM2,YN1,YN2,SIGF(1),SIGF(2)
 6227 FORMAT(' * IZGIBU 6227: NFE1,NFE2,SFLM1,SFLM2,YN1,YN2,
     *   SIGF(1),SIGF(2) ',/1X,8F11.5)
         SGFP1=SFLM1*YN1/SF1
         SGFP2=SFLM2*YN2/SF2
         SFF1=SFLM1*YN1/SIGF(1)
         SFF2=SFLM2*YN2/SIGF(2)
C     квантиль нормального распределения
C	XP1=(1.-1./SFF1)/NU
C	XP2=(1.-1./SFF2)/NU
     WRITE(7,706) SFF1,YN1,SFF2,YN2,SF1,SF2,SFLM1,SIGF(1)
  706  FORMAT(' * IZGIBU 706: SFF1,YN1,SFF2,YN2,SF1,SF2SFLM1,SIGF(1)--'/
     * 8X,8F8.3)
    XP1=2.328*ALOG10(SFF1)/ALOG10(SF1)
    XP2=2.328*ALOG10(SFF2)/ALOG10(SF2)
C	интеграл вероятности  -  ВЕРОЯТНОСТЬ НЕРАЗРУШЕНИЯ
    WRITE(7,622)  SFF1,XP1,PF1, SFF2,XP2,PF2
        CALL NDTR(XP1,PF1,DD1)
    CALL NDTR(XP2,PF2,DD2)
       WRITE(7,622)  SFF1,XP1,PF1, SFF2,XP2,PF2
  622  FORMAT(' *IZGIBU 622:  SFF1,XP1,PF1, SFF2,XP2,PF2 ',6F7.3)
C     pасчет пpочности пpи изгибе максимальной нагpузкой
   76  IF(ITF0(1).LT.IT) GOTO 77
      SIGFM1=SIGF01*KF1*TMAX/TQ(1)
        GOTO 78
   77 SIGFM1=SIGMAX(SIGF(1),TQ(1+ITF0(1)),TMAX,KFV1,KFB1,KFA1,2)
   78 SGFPM1=SGFPM(IG1)*YX1/(1.75*YZ1)
      IF(SFPM1Z.GT.0.) SGFPM1=SFPM1Z*YX1/(1.75*YZ1)
       IF(ITF0(2).LT.IT) GOTO 79
      SIGFM2=SIGF02*KF1*TMAX/TQ(1)
        GOTO 80
   79 SIGFM2=SIGMAX(SIGF(2),TQ(1+ITF0(2)),TMAX,KFV1,KFB1,KFA1,2)
   80 SGFPM2=SGFPM(IG2)*YX2/(1.75*YZ2)
      IF(SFPM2Z.GT.0.) SGFPM2=SFPM2Z*YX2*YZ2/1.75
          SFMF1=SGFPM1/SIGFM1
          SFMF2=SGFPM2/SIGFM2
    IF(IVR.GT.1) THEN
          SFMF1=1.75*SFMF1
          SFMF2=1.75*SFMF2
    END IF
c     Расчет эапаса долговечности
c       по методике СЕРЕНСЕНА-КОЗЛОВА-РАСУЛОВА-ГОЛЛЕРА
    IF(IVR.EQ.3) THEN
      IF(SIGF(1).LT.SGFG(1)) THEN
         SN1=-10.
         GOTO 333
      END IF
      IF(SIGF(1).GT.SFLM1) THEN
        QR=6.
            IF((IG1.GE.8.AND.IG1.LE.11).OR.IG1.EQ.18.OR.IG1.EQ.19.
     *      OR.IMF1.GE.1)  QR=9.
      ELSE
      QR=40.
      END IF
    NFR1=NFLIM*(SFLM1/(SIGF(1)))**QR
    SN1=NFR1/NFE1
  333  	  IF(SIGF(2).LT.SGFG(2)) THEN
         SN2=-10.
         GOTO 334
      END IF
      IF(SIGF(2).GT.SFLM2) THEN
        QR=6.
            IF((IG2.GE.8.AND.IG2.LE.11).OR.IG2.EQ.18.OR.IG2.EQ.19.
     *      OR.IMF2.GE.1)   QR=9.
      ELSE
      QR=40.
      END IF
    NFR2=NFLIM*(SFLM2/(SIGF(2)))**QR
    SN2=NFR2/NFE2
        WRITE(7,666)
  666  FORMAT('  SN1    SN2    NFR1    NFR2 ')
        WRITE(7,*) SN1,SN2,NFR1,NFR2
    END IF
C     квантиль нормального распределения
  334	XPM1=(1.-1./SFMF1)/NU
    XPM2=(1.-1./SFMF2)/NU
C	интеграл вероятности  -  ВЕРОЯТНОСТЬ НЕРАЗРУШЕНИЯ
    CALL NDTR(XPM1,PFM1,DDM1)
    CALL NDTR(XPM2,PFM2,DDM2)
       WRITE(7,6221)  SFMF1,XPM1,PFM1, SFMF2,XPM2,PFM2
 6221  FORMAT(' end IZGIBU   SFMF1,XPM1,PFM1, SFMF2,XPM2,PFM2 '/
     *  6X,6F7.3)
C    исходная pасчетная нагpузка
        TQF=TQ(1+ITF0(1))
C    допускаемая нагpузка
    ZAP1=SGFP1/SIGF(1)
    ZAP2=SGFP2/SIGF(2)
    ZAP=AMIN1(ZAP1,ZAP2)
        TQFP=TQF*ZAP
C        TQFP=TQF*SGFP1/SIGF(1)
C    эквивалентная нагpузка на вал
       EV=1./YN1
      IF(EV.LT.0.6) EV=0.6
      IF(EV.GT.1.0) EV=1.0
C    по желанию HKMЗ пpинято	EV=1.
C	                 EV=1.
         DO 33 I=1,IT
   33 NC(1,I)=RM(I)*60.*HH*TC(I)*CZ1/1.E6
C    пpиведенная частота вpащения
      RMP=0.
    TS=0.
       DO 37 I=1,IT
    TS=TS+TC(I)
   37 RMP=RMP+ABS(RM(I))*TC(I)
     WRITE(7,799) RMP,TS
  799  FORMAT('-IZGIB---- RMP,TS ----',F10.2,F10.5)
    RMP=RMP/TS
C    коэф. эквивал. пpи pасчете подшипников
      QP=3.33
      EP=0.
       DO 38 I=1,IT
   38 EP=EP+(TQ(I)/TQ(1))**QP*(ABS(RM(I))/RMP)*TC(I)
      EP=EP**(1./QP)
      IF(EP.LT.0.5) EP=0.5
      IF(EP.GT.1.0) EP=1.0
C     по желанию HKMЗ пpинято  EP=1.
C	             EP=1.
       TQEV=TQF*EV
C                                                    C
C печать pезультатов pасчета на пpочность пpи изгибе C
C                                                    C
C  L = -10 ВЫВОД МАТРИЦЫ KFV
    IF(L.LT.-1.) THEN
        WRITE(4,243)
  243  FORMAT(/24X,'ДИНАМИЧЕСКИЕ КОЭФФИЦИЕТЫ  KFV'//1X,78(1H-)/
     *' НАГРУЗКА |',21X,'ЧАСТОТЫ ВРАЩЕНИЯ')
        WRITE(4,2330)
        WRITE(4,233) (RM(I),I=1,IN)
  233  FORMAT(9X,10F7.1)
        WRITE(4,2330)
 2330  FORMAT(1X,78(1H-))
CCCCCCCCCCCCCCC
C	IIT=ITF(1)/10
c        print*,' izgibu-IIT ',IIT
C        DO 19 I=1,IIT
C	I10=1+10*(I-1)
C	TQI10=TQ(I10)
CCCCCCCCCCCC
    IIT=IT/10
        DO 19 I=1,IIT
    I10=1+10*(I-1)
    TQI10=TQ(I10)
    IF(IE.EQ.2) TQI10=TQ(I10)/9.81
    WRITE(4,234) TQI10,(KFVM(J),J=I10,10*I)
   19   CONTINUE
  234  FORMAT(1X,F8.1,10F7.3)
        WRITE(4,2330)
    END IF
       VR=PI*D1*RM(IRS(1))/6.E4
C======================
        WRITE(7,235)  IVR
  235  FORMAT(1X,' IZGIBU  before PRCPI    IVR = ',I3)

        IF(IVR.LE.2) THEN
                 CALL PRCPI(L,IPR,IE,PR,PF1,PF2,PFM1,PFM2,
     * SIGF(1),SIGF(2),SGFP1,SGFP2,SFF1,SFF2,SFMF1,SFMF2,
     * SIGFM1,SIGFM2,SGFPM1,SGFPM2,SF1,SF2,
     * VR,TQ(1+ITF0(1)),TQ(1+ITF0(2)),SIGF01,SIGF02,
     * YF1,YF2,YBET,YEPS,KFV1,KFB1,KFA1,
     * SGFLIM(1),SGFLIM(2),SGFG(1),SGFG(2),YN1,YN2,YA1,YA2,
     * YDLT,YR1,YR2,YX1,YX2,NFE1,NFE2)
       endif
C=====================
      RETURN
      END

*/
