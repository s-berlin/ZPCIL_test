#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>

using namespace std;
extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];

extern fstream f_1;    // файл для результата    //***

//========== Переменные по ступени
extern int IVP;                             // тип ступени
extern float Z1, Z2;                        // числа зубьев шестерни и колеса
extern float MN, BE, X1, X2;                // модуль, угол наклона, коэффициенты смещения
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
extern float GRM;
extern int SEC;

extern fstream f_1;    // файл для результата    //***

// печать pезультатов pасчета на контактную пpочность
// цилиндpических эвольвентных пеpедач

void  PRCPC(float PH1, float PH2, float PHM1, float PHM2,
            float SIGH, float SGHP1, float SGHP2, float SGHP, float SHF1, float SHF2, float SHMF1, float SHMF2,
            float SIGHM, float SGHPM1, float SGHPM2, float SHR1, float SGHPL1, float SGHPL2,
            float TQ1, float K01, float SIGH01, float VR,
            float ZH, float ZEPS, float KHV1, float KHB1, float OMEG1, float KNR, float KHA1,
            float SGHLM1, float SGHLM2, float SGHG1, float SGHG2, float SH1, float SH2,
            float ZN1, float ZN2, float ZV1, float ZV2, float ZX1, float ZX2, float ZR,
            float NHLIM1, float NHLIM2, float NHE1, float NHE2)
{
    string IE1[2]{ " Н * м   ", "кгс * мм" };
    string IE2[2]{ " MПа   ", "кгс / кв.мм" };

    float RTQ1 = 0;

    int I1 = 0;
    int I2 = 0;
    if (IE == 2) {
        I1 = 1;
        I2 = 1;
    }
  
    f_1 << "\n\n                 РАСЧЕТ НА ПРОЧНОСТЬ ПО  ГОСТ 21354-87 \n";
    
    if (IE == 2) {
        SIGH = SIGH / 9.81;
        SGHP1 = SGHP1 / 9.81;
        SGHP2 = SGHP2 / 9.81;
        SGHP = SGHP / 9.81;
        SIGHM = SIGHM / 9.81;
        SGHPM1 = SGHPM1 / 9.81;
        SGHPM2 = SGHPM2 / 9.81;
        SHR1 = SHR1 / 9.81;
        SGHPL1 = SGHPL1 / 9.81;
        SGHPL2 = SGHPL2 / 9.81;
        RTQ1 = TQ1 / 9.81;
        SIGH01 = SIGH01 / 9.81;
        SGHLM1 = SGHLM1 / 9.81;
        SGHLM2 = SGHLM2 / 9.81;
        SGHG1 = SGHG1 / 9.81;
        SGHG2 = SGHG2 / 9.81;
        K01 = K01 / 9.81;
    }
    else RTQ1 = TQ1;

    f_1 << "\n\n      KOHTAKTHAЯ BЫHOCЛИBOCTЬ \n";
    
    if (Z1 <= Z2) f_1 << "\n                                                ШЕСТЕРНЯ  КОЛЕСО \n";
    else          f_1 << "\n                                                КОЛЕСО  ШЕСТЕРНЯ \n";
 
    f_1 << "\n РАСЧЕТНОЕ   НАПРЯЖЕНИЕ, " << IE2[I2] << "      SIGH           " << SIGH << endl;

    if (BE == 0) {
        if (IVR <= 1) f_1 << "\n ДОПУСКАЕМЫЕ НАПРЯЖЕНИЯ, " << IE2[I2] << "      SGHP    " << SGHP1 << "     " << SGHP2 << endl;
        else {
            f_1 << "\n РАСЧЕТНЫЕ ЗАПАСЫ ПРОЧНОСТИ " << "      SHF    " << SHF1 << "     " << SHF2 << endl;
            f_1 << "\n РАСЧЕТНЫЕ ВЕРОЯТНОСТИ НЕРАЗРУШЕНИЯ " <<  "   PH   " << PH1 << "     " << PH2 << endl;
        }
    }
    
    if (BE != 0.) {
        if (IVR <= 1) f_1 << "\n ДОПУСКАЕМOЕ НАПРЯЖЕНИE, " << IE2[I2] << "      SGHP            " << SGHP << endl;     
        else {
            f_1 << "\n РАСЧЕТНЫЕ ЗАПАСЫ ПРОЧНОСТИ " << "      SHF    " << SHF1 << "     " << SHF2 << endl;
            f_1 << "\n РАСЧЕТНЫЕ ВЕРОЯТНОСТИ НЕРАЗРУШЕНИЯ " << "   PH   " << PH1 << "     " << PH2 << endl;
        }
    }
    f_1 << "\n КОНТАКТНАЯ ПРОЧНОСТЬ ПРИ ДЕЙСТВИИ МАКСИМАЛЬНОЙ НАГРУЗКИ";
    f_1 << "\n  МАКСИМАЛЬНОЕ НАПРЯЖЕНИЕ," << IE2[I2] << "     SIGHM            " << SIGHM;

    if (IVR <= 1) f_1 << "\n ДОПУСКАЕМЫЕ НАПРЯЖЕНИЯ, " << IE2[I2] << "      SGHPM    " << SGHPM1 << "     " << SGHPM2 << endl;
    else {
        f_1 << "\n РАСЧЕТНЫЕ ЗАПАСЫ ПРОЧНОСТИ " << "      SHF    " << SHMF1 << "     " << SHMF2 << endl;
        f_1 << "\n РАСЧЕТНЫЕ ВЕРОЯТНОСТИ НЕРАЗРУШЕНИЯ " << "   PH   " << PHM1 << "     " << PHM2 << endl;
    }
 
//           Пpовеpка на малоцикловую усталость

    if (SHR1 > SGHPL1) {
        f_1 << "\n ШЕСТЕРНЯ НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ ";
        f_1 << "\n РАСЧЕТНОЕ   НАПРЯЖЕНИЕ, " << IE2[I2] << "    SHR    " << SHR1 ;
        f_1 << "\n ДОПУСКАЕМОЕ МАЛОЦИКЛОВОЕ, " << IE2[I2] << "    SGHPL    " << SGHPL1 << endl;
    }

    if (SHR1 > SGHPL2) {      //*** ???
        f_1 << "\n КОЛЕСО НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ ";
        f_1 << "\n РАСЧЕТНОЕ   НАПРЯЖЕНИЕ, " << IE2[I2] << "    SHR    " << SHR1;
        f_1 << "\n ДОПУСКАЕМОЕ МАЛОЦИКЛОВОЕ, " << IE2[I2] << "    SGHPL    " << SGHPL2 << endl;
    }
 
    if (IPR > 3)  f_1 << "\n РАСЧЕТНЫЙ МОМЕНТ НА ВЕДУЩЕМ ВАЛУ, " << IE1[I1] << "      T1H    " << RTQ1;
 
    if (IPR > 3 && L >= - 1.) f_1 << "\n ОКРУЖНАЯ СКОРОСТЬ ПРИ РАСЧЕТНОЙ НАГРУЗКЕ,м/с  V " << VR;
  
    if (IPR > 6)  f_1 << "\n КОЭФФИЦИЕНТ НАГРУЖЕННОСТИ ПЕРЕДАЧИ, " << IE2[I2] << "    K0    " << K01;

    if (IPR > 3) {
        f_1 << "\nПАРАМЕТРЫ РАСЧЕТНОГО КОНТАКТНОГО НАПРЯЖЕНИЯ ";
        f_1 << "\n КОЭФФИЦИЕНТЫ: ";
        f_1 << "\n - ФОРМЫ СОПРЯЖЕННЫХ ПОВЕРХНОСТЕЙ        ZH         " << ZH;
        f_1 << "\n - ДЛИНЫ КОНТАКТНЫХ ЛИНИЙ                ZEPS       " << ZEPS;
    }
    if (IPR > 3 && L >= - 1.) f_1 << "\n - ДИНАМИЧЕСКОЙ НАГРУЗКИ                 KHV         " << KHV1;

    if (IPR > 3 && KNR < 0)   f_1 << "\n - РАСПРЕД.НАГРУЗКИ МЕЖДУ САТЕЛЛИТАМИ    OMEGA       " << OMEG1;

    if (IPR > 3) {
        f_1 << "\n - РАСПРЕД.НАГРУЗКИ ПО ДЛИНЕ КОНТ.ЛИНИЙ  KHB         " << KHB1;
        f_1 << "\n - РАСПРЕДЕЛЕНИЯ НАГРУЗКИ МЕЖДУ ЗУБЬЯМИ  KHA         " << KHA1;
    }
    if (IPR > 3) {
        f_1 << "\nПАРАМЕТРЫ ОГРАНИЧЕННОГО ПРЕДЕЛА КОНТАКТНОЙ ВЫНОСЛИВОСТИ ";
        f_1 << "\n ПРЕДЕЛЫ КОНТАКТНОЙ ";
        f_1 << "\n ВЫНОСЛИВОСТИ, " << IE2[I2] << "             SGMHLB    " << SGHLM1 << "     " << SGHLM2;
        f_1 << "\n ПОВРЕЖДАЮЩИЕ НАПРЯЖЕНИЯ, " << IE2[I2] << "    SGHG    " << SGHG1 << "     " << SGHG2;
    }

        if (IPR > 3 && IVR == 0) 
            f_1 << "\n - КОЭФФИЦИЕНТЫ БЕЗОПАСНОСТИ                SH         " << SH1 << "     " << SH2;

        if (IPR > 3) {
            f_1 << "\n - КОЭФФИЦИЕНТЫ ДОЛГОВЕЧНОСТИ               ZN         " << ZN1 << "     " << ZN2;
            f_1 << "\n - КОЭФФИЦИЕНТЫ ОКРУЖНОЙ СКОРОСТИ           ZV         " << ZV1 << "     " << ZV2;
            f_1 << "\n - КОЭФФИЦИЕНТЫ РАЗМЕРА ЗУБЧАТОГО КОЛЕСА    ZX         " << ZX1 << "     " << ZX2;

            f_1 << "\n - КОЭФФИЦИЕНТ ШЕРОХОВАТОСТИ  ";
            f_1 << "\n - РАБОЧИХ ПОВЕРХНОСТЕЙ                     ZR         " << ZR;

            f_1 << "\n - БАЗОВЫЕ ЧИСЛА ЦИКЛОВ, МЛН              NHLIM        " << NHLIM1 << "     " << NHLIM2;
            f_1 << "\n - ЭКВИВАЛЕНТНЫЕ ЧИСЛА ЦИКЛОВ, МЛН          NHE        " << NHE1 << "     " << NHE2;
        }
        
        if (IPR >= 3) f_1 << "\n ________________________ ";
}
/*
SUBROUTINE PRCPC(L, IVP, IPR, IE, BE, IVR, Z1, Z2,
    *PH1, PH2, PHM1, PHM2,
    *SIGH, SGHP1, SGHP2, SGHP, SHF1, SHF2, SHMF1, SHMF2,
    *SIGHM, SGHPM1, SGHPM2,
    *SHR1, SGHPL1, SGHPL2,
    *TQ1, K01, SIGH01, VR,
    *ZH, ZEPS, KHV1, KHB1, OMEG1, KNR, KHA1,
    *SGHLM1, SGHLM2, SGHG1, SGHG2, SH1, SH2,
    *ZN1, ZN2, ZV1, ZV2, ZX1, ZX2, ZR,
    *NHLIM1, NHLIM2, NHE1, NHE2)
    C                                                    C
    C печать pезультатов pасчета на контактную пpочность C
    C цилиндpических эвольвентных пеpедач                C
    REAL K01, KHV1, KHB1, KNR, KHA1, NHLIM1, NHLIM2, NHE1, NHE2, L
    CHARACTER * 8 IE1(2)
    CHARACTER * 10 IE2(2)
    SAVE
    DATA IE1 / ' Н*м    ', ' кгс*м  ' /
    DATA IE2 / ' MПа      ', 'кгс/кв.мм ' /
    WRITE(7, 706) ivr
    706  FORMAT(' prcpc: ivr  ', i3)
    I1 = 1
    IF(IE.EQ.2) I1 = 2
    I2 = 1
    IF(IE.EQ.2) I2 = 2
    WRITE(1, 100)
    100  FORMAT(/ 18X, 'РАСЧЕТ НА ПРОЧНОСТЬ ПО  ГОСТ 21354-87' / )
    C        WRITE(1, 111)
    111  FORMAT(11X, 'РЕЗУЛЬТАТЫ  РАСЧЕТА НА ПРОЧНОСТЬ ',
        *'АКТИВНЫХ ПОВЕРХНОСТЕЙ' / ) 
    IF(IE.NE.2) GOTO 1109
    SIGH = SIGH / 9.81
    SGHP1 = SGHP1 / 9.81
    SGHP2 = SGHP2 / 9.81
    SGHP = SGHP / 9.81
    SIGHM = SIGHM / 9.81
    SGHPM1 = SGHPM1 / 9.81
    SGHPM2 = SGHPM2 / 9.81
    SHR1 = SHR1 / 9.81
    SGHPL1 = SGHPL1 / 9.81
    SGHPL2 = SGHPL2 / 9.81
    RTQ1 = TQ1 / 9.81
    SIGH01 = SIGH01 / 9.81
    SGHLM1 = SGHLM1 / 9.81
    SGHLM2 = SGHLM2 / 9.81
    SGHG1 = SGHG1 / 9.81
    SGHG2 = SGHG2 / 9.81
    K01 = K01 / 9.81
    GOTO 1108
    1109 RTQ1 = TQ1
    1108   WRITE(1, 1110)
    1110  FORMAT(6X, 'KOHTAKTHAЯ BЫHOCЛИBOCTЬ')    
    IF(Z1.LE.Z2) THEN
    WRITE(1, 191)
    191 FORMAT(
        *48X, 'ШЕСТЕРНЯ  КОЛЕСО' / )
    ELSE
    WRITE(1, 192)
    192 FORMAT(
        *48X, ' КОЛЕСО  ШЕСТЕРНЯ' / )
    END IF
    WRITE(1, 1114) IE2(I2), SIGH
    1114  FORMAT(
        *' РАСЧЕТНОЕ   НАПРЯЖЕНИЕ,', A10, 7X, 'SIGH ', F13.0)

    IF(BE.EQ.0.) THEN
    IF(IVR.LE.1) THEN
    WRITE(1, 1111) IE2(I2), SGHP1, SGHP2
    1111  FORMAT(
        *' ДОПУСКАЕМЫЕ НАПРЯЖЕНИЯ,', A10, 7X, 'SGHP ', 2F10.0)
    ELSE
    WRITE(1, 1112)  SHF1, SHF2, PH1, PH2
    1112  FORMAT(
        *' РАСЧЕТНЫЕ ЗАПАСЫ ПРОЧНОСТИ  ', 12X, 'SHF  ', F7.2, F10.2 /
        *' РАСЧЕТНЫЕ ВЕРОЯТНОСТИ НЕРАЗРУШЕНИЯ', 6X, 'PH   ', 2F10.5)
    END IF
    END IF

    IF(BE.NE.0.) THEN
    IF(IVR.LE.1) THEN
    WRITE(1, 1113) IE2(I2), SGHP
    1113  FORMAT(
        *' ДОПУСКАЕМOЕ НАПРЯЖЕНИE,', A10, 7X, 'SGHP ', F13.0)
    ELSE
    WRITE(1, 1112)  SHF1, SHF2, PH1, PH2
    END IF
    END IF

    WRITE(1, 1338) IE2(I2), SIGHM
    1338 FORMAT(/ 6X,
        *'КОНТАКТНАЯ ПРОЧНОСТЬ ПРИ ДЕЙСТВИИ МАКСИМАЛЬНОЙ НАГРУЗКИ'//
        * ' МАКСИМАЛЬНОЕ НАПРЯЖЕНИЕ,', A10, 6X, 'SIGHM', F13.0)
        * 
    
    IF(IVR.LE.1.) THEN
    WRITE(1, 1339) IE2(I2), SGHPM1, SGHPM2
    1339 FORMAT(
        *' ДОПУСКАЕМЫЕ  НАПРЯЖЕНИЯ,', A10, 6X, 'SGHPM', 2F9.0)
    ELSE
    c	SHM1 = SGHPM1 / SIGHM
    c       SHM2 = SGHPM2 / SIGHM
    WRITE(1, 1112) SHMF1, SHMF2, PHM1, PHM2
    END IF

C           Пpовеpка на малоцикловую усталость

    IF(SHR1.GT.SGHPL1) WRITE(1, 201)
    * IE2(I2), SHR1, IE2(I2), SGHPL1
    201 FORMAT(/ ' ШЕСТЕРНЯ НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ' /
        *' РАСЧЕТНОЕ   НАПРЯЖЕНИЕ,', A10, 9X, 'SHR', F13.0 /
        *' ДОПУСКАЕМОЕ МАЛОЦИКЛОВОЕ,', A10, 5X, 'SGHPL', F13.0 / )

    IF(SHR1.GT.SGHPL2) WRITE(1, 202)
    * IE2(I2), SHR1, IE2(I2), SGHPL2
    202 FORMAT(/ ' КОЛЕСО НЕ ПРОХОДИТ ПО МАЛОЦИКЛОВОЙ УСТАЛОСТИ' /
        *' РАСЧЕТНОЕ   НАПРЯЖЕНИЕ,', A10, 9X, 'SHR', F13.0 /
        *' ДОПУСКАЕМОЕ  МАЛОЦИКЛОВОЕ,', A10, 5X, 'SGHPL', F13.0 / )
         
    IF(IPR.GT.3) WRITE(1, 550) IE1(I1), RTQ1
    550 FORMAT(/
        *' РАСЧЕТНЫЙ МОМЕНТ НА ВЕДУЩЕМ ВАЛУ,', A8, '     T1H', F10.1)
    IF(IPR.GT.3.AND.L.GE. - 1.) WRITE(1, 551) VR
    551 FORMAT(
        *' ОКРУЖНАЯ СКОРОСТЬ ПРИ РАСЧЕТНОЙ НАГРУЗКЕ,м/с  V', F12.1)
    IF(IPR.GT.6) WRITE(1, 552) IE2(I2), K01
    552 FORMAT(
        *' КОЭФФИЦИЕНТ НАГРУЖЕННОСТИ ПЕРЕДАЧИ,', A10, 'K0', F13.2)
         
    IF(IPR.GT.3) WRITE(1, 560) ZH, ZEPS
    560 FORMAT(/ 6X,
        *'ПАРАМЕТРЫ РАСЧЕТНОГО КОНТАКТНОГО НАПРЯЖЕНИЯ'//
        * ' КОЭФФИЦИЕНТЫ:' /
        *' - ФОРМЫ СОПРЯЖЕННЫХ ПОВЕРХНОСТЕЙ        ZH  ', F16.3 /
        *' - ДЛИНЫ КОНТАКТНЫХ ЛИНИЙ                ZEPS', F16.3)
   
    IF(IPR.GT.3.AND.L.GE. - 1.) WRITE(1, 561)  KHV1
    561 FORMAT(
        *' - ДИНАМИЧЕСКОЙ НАГРУЗКИ                 KHV ', F16.3)
    IF(IPR.GT.3.AND.KNR.LT.0.) WRITE(1, 5620) OMEG1
    5620 FORMAT(
        *' - РАСПРЕД.НАГРУЗКИ МЕЖДУ САТЕЛЛИТАМИ    OMEGA', F15.3)
    IF(IPR.GT.3) WRITE(1, 562) KHB1, KHA1
    562 FORMAT(
        *' - РАСПРЕД.НАГРУЗКИ ПО ДЛИНЕ КОНТ.ЛИНИЙ  KHB ', F16.3 /
        *' - РАСПРЕДЕЛЕНИЯ НАГРУЗКИ МЕЖДУ ЗУБЬЯМИ  KHA ', F16.3)

    IF(IPR.GT.3) WRITE(1, 570) IE2(I2), SGHLM1, SGHLM2,
    * IE2(I2), SGHG1, SGHG2
    570 FORMAT(/ 7X,
        *'ПАРАМЕТРЫ ОГРАНИЧЕННОГО ПРЕДЕЛА КОНТАКТНОЙ ВЫНОСЛИВОСТИ'//
        * ' ПРЕДЕЛЫ КОНТАКТНОЙ' /
        *' ВЫНОСЛИВОСТИ,', A10, 16X, 'SGMHLB', 2F10.0 /
        *' ПОВРЕЖДАЮЩИЕ НАПРЯЖЕНИЯ,', A10, 7X, 'SGHG', 2F10.0)
    IF(IPR.GT.3.AND.IVR.EQ.0) WRITE(1, 571) SH1, SH2
    571 FORMAT(
        *' КОЭФФИЦИЕНТЫ БЕЗОПАСНОСТИ                SH  ', 2F10.3)

    IF(IPR.GT.3) WRITE(1, 572) ZN1, ZN2, ZV1, ZV2, ZX1, ZX2, ZR,
    * NHLIM1, NHLIM2, NHE1, NHE2
    572 FORMAT(
        *' КОЭФФИЦИЕНТЫ ДОЛГОВЕЧНОСТИ               ZN  ', 2F10.3 /
        *' КОЭФФИЦИЕНТЫ ОКРУЖНОЙ СКОРОСТИ           ZV  ', 2F10.3 /
        *' КОЭФФИЦИЕНТЫ РАЗМЕРА ЗУБЧАТОГО КОЛЕСА    ZX  ', 2F10.3 /
        *' КОЭФФИЦИЕНТ ШЕРОХОВАТОСТИ ' /
        *' РАБОЧИХ ПОВЕРХНОСТЕЙ                     ZR  ', F15.3 /
        *' БАЗОВЫЕ ЧИСЛА ЦИКЛОВ, МЛН              NHLIM ', 2F10.3 /
        *' ЭКВИВАЛЕНТНЫЕ ЧИСЛА ЦИКЛОВ, МЛН          NHE ', 2F10.3)
    IF(IPR.GE.3) WRITE(1, 300)
    300 FORMAT(' __________ ')
    RETURN
    END

    */