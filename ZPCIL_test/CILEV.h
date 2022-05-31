#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string>
#include "DSR.h"
#include "VYVODS.h"
#include "GEOM.h"
#include "CONTAU.h"
#include "IZGIBU.h"

using namespace std;

//========== Переменные по редуктору
extern char IR[20];
extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];

extern fstream f_1;    // файл для результата    //***

//========== Переменные по ступени
extern int IVP;                             // тип ступени
extern float Z1, Z2;                        // числа зубьев шестерни и колеса
extern float MN, BE, X1, X2, X[2];          // модуль, угол наклона, коэффициенты смещения
extern int flaw;
extern float AW, B1, B2, D1, D2;            // межосевое расстояние ширины шестерни и колеса
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
extern float EPSA, EPSB, ZH, ZEPS;
extern float DA1, DA2, DB1, DB2, ALFTW;

void CILEV(int IT1, float TQ1[100], float TC1[100], float RM1[100])
{
    float BBWW[2] = {0,0}, BW = 0;
    float SGN = 0;
    float A0 = 0;

    DSR(); // чтение исходных данных о ступени редуктора
    VYVODS(); // вывод исходных данных о ступени редуктора

    BBWW[0] = B1;
    BBWW[1] = B2;
    BW = B1;
    if (B2 < BW) BW = B2;

    int IAX = 1;
    if (X1 >= -5. && X2 >= -5.) IAX = 0;     //    !Aw = 0 - ­не задано
    if (X1 <= -5. && X2 <= -5.) IAX = 3;     //    !Aw > 0 - задано
    if (AW > 0. && X2 > -5.)  IAX = 2;
    
    int NW = 0;  // число сателлитов


    GEOM(NW);
    cout << "CILEV: after GEOM:    ZH = " << ZH << "   ZEPS = " << ZEPS << "   D1 = " << D1 << "   D2 = " << D2 << endl;

    //    if (IAX == 4)  GOTO 96
  m42:
    if (L != 0) {
  m85:
        SGN = 1;
        A0 = 0;
    }
 //   for (int i = 0; i < IT1; i++) TQ1[i] = TQ1[i] * KSP;
    for (int i = 0; i < IT; i++) TQ[i] = TQ[i] * KSP;
    TMAX = TMAX * KSP;
    float DTC = 0.;
    float KNR = 1.;

 //==== вызов подпpогpаммы пpочностного pасчета активных повеpхностей зубьев по контакту ===============
    CONTAU(SGN, NW, A0, DTC, KNR, IT1, TQ1, TC1, RM1);
    /*
     if (IVR == 3) {  // расчет для дифференциала
     

     }
    */

        // - вызов подпpогpаммы пpочностного pасчета зубьев пpи изгибе

 //       WRITE(7, 705) WH, AW, ALTW, Z1, Z2
 //       705  FORMAT(' CILEV bef izgb: WH,AW,ALTW,z1,z2: ' /
 //           *3F9.3, 2F4.0)
 //       IF(L.LT. - 1.) WRITE(4, 106) IS
 //       106 FORMAT(/ 23X, I2, ' - п бвгЇҐ­м '//
 //           * 9X, '( жЁ«Ё­¤аЁзҐбЄ п нў®«мўҐ­в­ п ЇҐаҐ¤ з ', /
 //           *9X, '          ў­Ґи­ҐЈ® § жҐЇ«Ґ­Ёп )')
    float Z0 = 20.;
    float P = 0;
    float ALTW = 0;
    float TN = 0, TNZ = 0;
    float SFLB1Z = 0, SFLB2Z = 0, SFPM1Z = 0, SFPM2Z = 0;
    float TQF = 0, TQFP = 0, TQEV = 0, RMP = 0, EV = 0, EP = 0;
    float PF10 = 0, PF20 = 0, SFMF1 = 0, SFMF2 = 0, SFN10 = 0, SFN20 = 0, SFG1 = 0, SFG2 = 0, SFF10 = 0,  SFF20 = 0;

    IZGIBU(SGN, 0, DTC, A0, KNR, P,
        D1, D2, ALTW,
        Z0,
        TN, TNZ,
        SFLB1, SFLB2, SFPM1, SFPM2,
        TQF, TQFP, TQEV, RMP, EV, EP,
        PF10, PF20, SFMF1, SFMF2, SFN10, SFN20, SFG1, SFG2, SFF10, SFF20);
    
};
/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                          C
C               подпpогpамма  "CILEV"                      C
C    pасчета цилиндpических эвольвентных пеpедач           C
C               внешнего зацепления                        C
C                                                          C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

SUBROUTINE CILEV(JJ, IR, IVP, IS, ISR, L, WH, TMAX,
    *IRV, IPR, IE, N1R, TNZ,
    *IT1, TQ1, TC1, RM1, IN, IT, TQ, TC, RM, TN)
    CHARACTER * 16 IR
    REAL L, LO, MN, KPD, KSP, KFBE, KNR, N1R
    REAL BBWW(2)
    REAL SHR(11), SFR(11), TQR[FAR](100)
    DIMENSION TQ(IT), RM(IT), TC(IT)
    DIMENSION TQ1(100), TC1(100), RM1(100)
    SAVE
    WRITE(7, 700) L, WH
    700  FORMAT(' CILEV bef dsr ==L,WH:  ', 2F10.1)
    CALL DSR(JJ, IR, L, IS, ISR, IPR, Z1, Z2, MN, BE, X1, X2,
        *AW, B1, B2, AL, HA, HL, CZV, IMD, IST1, IST2, IST3, IST4, IST5,
        *IKG, FKE, IZ1, IG,
        *IQ, IP, LO, S1, CZ1, CZ2, GM, IVR, PR, KPD, KSP,
        *SHLM1, SHLM2, SHPM1, SHPM2, SFLB1, SFLB2, SFPM1, SFPM2,
        *IG1, H1, HK1, HT1, SHER1, YZ1, YT1, YR1, IMF1, SHV1,
        *IG2, H2, HK2, HT2, SHER2, YZ2, YT2, YR2, IMF2, SHV2)

    BBWW(1) = B1
    BBWW(2) = B2

    WRITE(7, 701) L, WH
    701  FORMAT(' CILEV bef vyvods ==L,WH:  ', 2F10.1)
    CALL VYVODS
    * (IVP, L, WH, IS, IR, IPR, IE, ISR, KPD, KSP,
        *Z1, Z2, MN, BE, X1, X2, AW, B1, B2, AL, HA, HL, CZV, IMD, IST1, IST2,
        *IST3, IST4, IST5, IKG, FKE, IZ1, IG, IQ, IP, LO, S1, CZ1, CZ2, GM,
        *IVR, PR,
        *SHLM1, SHLM2, SHPM1, SHPM2, SFLB1, SFLB2, SFPM1, SFPM2,
        *IG1, H1, HK1, HT1, SHER1, YZ1, YT1, YR1, IMF1, SHV1,
        *IG2, H2, HK2, HT2, SHER2, YZ2, YT2, YR2, IMF2, SHV2)
    C
    C  p бзҐв ЈҐ®¬ҐвpЁЁ
    C--------------pасчет геометpии
    C
    WRITE(7, 702) IS, ISR, IPR, IVP, Z1, Z2, MN, AL, BE, X1, X2
    702  FORMAT(' CILEV  bef  geom:IS,ISR,IPR,IVP,Z1,Z2,MN,AL,BE,X1,X2' /
        *5X, 4I2, 2F4.0, 5F8.4)
    BW = AMIN1(B1, B2)
    IAX = 1
    IF(X1.GT. - 5..AND.X2.GT. - 5.) IAX = 0    !Aw = 0 - ­Ґ § ¤ ­®
    IF(X1.LE. - 5..AND.X2.LE. - 5.) IAX = 3    !Aw > 0 - § ¤ ­®
    IF(AW.GT.0..AND.X2.GT. - 5.)  IAX = 2
    C	PRINT*, ' IAX= ', IAX
    NW = 0
    CALL GEOM(IR, IPR, IVP, Z1, Z2, MN, AL, BE, X1, X2, IAX, NW,
        *AW, BBWW, HA, HL, CZV, IMD, IST1, IST2, IST3, IST4, IST5,
        *U, D1, D2, EPSA, EPSB, ALTW, ZH, ZEPS, DU1, DU2,
        *DA1, DA2, DB1, DB2, ZVE1, ZVE2)
    C	PRINT*, ' IAX= ', IAX
    WRITE(7, 2022) Z1, Z2, MN, AL, ALTW, BE, X1, X2, HA, AW
    2022	FORMAT(' --- Z1,Z2,MN,AL,ALTW,BE,X1,X2,HA,AW' /
        *2F5.1, 7F8.5, F10.4)
    IF(IAX.EQ.4)  GOTO 96
    42  IF(L.EQ.0.) GOTO 99
    85       SGN = 1.
    A0 = 0.
    DO 43 I = 1, IT1
    43   TQ1(I) = TQ1(I) * KSP
    DO 44 I = 1, IT
    44   TQ(I) = TQ(I) * KSP
    TMAX = TMAX * KSP
    C---- - ўл§®ў Ї®¤Їp®Јp ¬¬л Їp®з­®бв­®Ј® p бзҐв 
    C---- - ЄвЁў­ле Ї®ўҐpе­®бвҐ© §гЎмҐў Ї® Є®­в Євг
    C---- - вызов подпpогpаммы пpочностного pасчета
    C---- - активных повеpхностей зубьев по контакту

    WRITE(7, 704) WH, AW, ALTW, Z1, Z2
    704  FORMAT(' CILEV bef cont: WH,AW,ALTW,z1,z2: ' /
        *3F9.3, 2F4.0)
    DTC = 0.
    KNR = 1.
    CALL CONTAU(IVP, IPR, IE, SGN, NW, A0, DTC, KNR, L,
        *Z1, Z2, MN, AL, BE, X1, X2, BW, IMD, HA, CZ1, CZ2,
        *U, AW, D1, D2, EPSA, EPSB, ALTW, ZH, ZEPS, DU1, DU2,
        *DA1, DA2, DB1, DB2, ZVE1, ZVE2,
        *IT1, TQ1, TC1, RM1, WH, TMAX, IST2, IST3,
        *IKG, IG, IQ, IP, LO, S1, FKE, IZ1, GM,
        *IG1, IG2, H1, H2, HK1, HK2, HT1, HT2,
        *SHER1, SHER2, IVR, SHV1, SHV2,
        *SHLM1, SHLM2, SHPM1, SHPM2,
        *KFBE, TQH, TQHP,
        *PH10, PH20, SHMF1, SHMF2, SHN10, SHN20, SHG1, SHG2, SHF10, SHF20)
    WRITE(7, 655) SHN1, SHN2, SHG1, SHG2, SHF10, SHF20
    655  FORMAT(' SHN1,SHN2,SHG1,SHG2,SHF1,SHF20 ' / 1X, 6F10.5)
    WRITE(7, 6550) PH10, PH20, SHMF1, SHMF2
    6550  FORMAT(' PH10,PH20,SHMF1,SHMF2 ' / 1X, 4F10.5)
    
    IF(IVR.EQ.3) THEN  // дифференциал =========================================================
    c------ - ђ бзҐв ¤Ґ©бвўЁвҐ«м­®Ј® Є®нддЁжЁҐ­в  н Ї б  Їа®з­®бвЁ
    c------ - Ї® ¬Ґв®¤ЁЄҐ ‘…ђ…Ќ‘…ЌЂ - ЉЋ‡‹Ћ‚Ђ - ђЂ‘“‹Ћ‚Ђ - ѓЋ‹‹…ђЂ
    c------ - Расчет действительного коэффициента эапаса прочности
    c------ - по методике СЕРЕНСЕНА - КОЗЛОВА - РАСУЛОВА - ГОЛЛЕРА

        DO 677 I2 = 1, 2
        IF(I2.EQ.1) SHF = SHF10
        IF(I2.EQ.2) SHF = SHF20
        WRITE(7, 658) I2, IT1, SHF
        658   FORMAT(' <CILEV1> I2  IT1  SHF=   ', 2I5, F10.2)
        IF(SHF.LT.1.05.AND.SHF.GT.0.95) GOTO 59
        SHR(1) = SHF
        WRITE(7, 659) SHR(1)
        659   FORMAT(' <CILEV1>  SHR(1)=   ', F10.2)
        DO 53 II = 1, 10
            DO 51 I = 1, IT1
                IF(II.EQ.1) THEN
                    TQR(I) = TQ1(I) * SHR(II) * *2
                ELSE
                    TQR(I) = TQR(I) * SHR(II) * *2
                END IF
            51        CONTINUE
            WRITE(7, 661) (TQR(I), I = 1, IT1)
            661   FORMAT('   TQR   ', 5F10.2)
            CALL CONTAU(IVP, IPR, IE, SGN, NW, A0, DTC, KNR, L,
                    *Z1, Z2, MN, AL, BE, X1, X2, BW, IMD, HA, CZ1, CZ2,
                    *U, AW, D1, D2, EPSA, EPSB, ALTW, ZH, ZEPS, DU1, DU2,
                    *DA1, DA2, DB1, DB2, ZVE1, ZVE2,
                    *IT1, TQR, TC1, RM1, WH, TMAX, IST2, IST3,
                    *IKG, IG, IQ, IP, LO, S1, FKE, IZ1, GM,
                    *IG1, IG2, H1, H2, HK1, HK2, HT1, HT2,
                    *SHER1, SHER2, IVR, SHV1, SHV2,
                    *SHLM1, SHLM2, SHPM1, SHPM2,
                    *KFBE, TQH, TQHP,
                    *PH1, PH2, SHMF1, SHMF2, SHN1, SHN2, SHG1, SHG2, SHF1, SHF2)
    
            IF(I2.EQ.1)  SHR(II + 1) = SHF1
            IF(I2.EQ.2)  SHR(II + 1) = SHF2
            WRITE(7, 668) II, SHR(II + 1)
            668   FORMAT('  II  SHR(ii+1) ', I5, F10.2)
    
            IF(SHR(ii + 1).LT.1.05.AND.SHR(ii + 1).GT.0.95) THEN
                IIR = II
                GOTO 55
            END IF
        53  CONTINUE
    
        55  SHF = SHR(1)
        WRITE(7, 662) (SHR(I), I = 1, 10)
        662   FORMAT('   SHR(i=1,10)   ', 5F10.2)
        DO 58 I = 1, IIR
            SHF = SHF * SHR(I + 1)
            WRITE(7, 663) SHF
            663   FORMAT(' from  SHF(2) to  SHF(iir)  ', F15.3)
        58        CONTINUE
    
        59  IF(I2.EQ.1) THEN
            SHR1 = SHF
            WRITE(7, 664) IIR, SHF
            664       FORMAT(' ‚…„“™……   IIR   SHF1  ', I5, F10.3)
        ELSE
            SHR2 = SHF
            WRITE(7, 665) IIR, SHF
            665       FORMAT(' ‚…„ЋЊЋ…   IIR   SHF2  ', I5, F10.3)
        END IF
    
        677   CONTINUE
        CALL PRCPC3(IVP, PH10, PH20, SHMF1, SHMF2,
            *SHN10, SHN20, SHF10, SHF20, SHR1, SHR2)
    END IF // ==============================================================
    
    C---- - ўл§®ў Ї®¤Їp®Јp ¬¬л Їp®з­®бв­®Ј® p бзҐв 
    C---- - §гЎмҐў ЇpЁ Ё§ЈЁЎҐ
    C---- - вызов подпpогpаммы пpочностного pасчета
    C---- - зубьев пpи изгибе

    WRITE(7, 705) WH, AW, ALTW, Z1, Z2
    705  FORMAT(' CILEV bef izgb: WH,AW,ALTW,z1,z2: ' /
        *3F9.3, 2F4.0)
    IF(L.LT. - 1.) WRITE(4, 106) IS
    106 FORMAT(/ 23X, I2, ' - п бвгЇҐ­м '//
        * 9X, '( жЁ«Ё­¤аЁзҐбЄ п нў®«мўҐ­в­ п ЇҐаҐ¤ з ', /
        *9X, '          ў­Ґи­ҐЈ® § жҐЇ«Ґ­Ёп )')
    Z0 = 20.
    CALL IZGIBU(IPR, IE, SGN, 0, DTC, A0, KNR, P, L,
        *Z1, Z2, MN, AL, BE, X1, X2, B1, B2, IMD, HA, CZ1, CZ2,
        *U, AW, D1, D2, EPSA, EPSB, ALTW,
        *DA1, DA2, DB1, DB2, ZVE1, ZVE2, Z0,
        *IN, IT1, TQ1, TC1, RM1, WH, TMAX, IST2, IST3, GM,
        *IKG, IG, IQ, IP, LO, S1, FKE, IZ1,
        *IVR, PR, IMF1, IMF2, IRV, TN, N1R, TNZ,
        *YT1, YZ1, YT2, YZ2, YR1, YR2,
        *IG1, IG2, H1, H2, HK1, HK2,
        *SFLB1, SFLB2, SFPM1, SFPM2,
        *TQF, TQFP, TQEV, RMP, EV, EP,
        *PF10, PF20, SFMF1, SFMF2, SFN10, SFN20, SFG1, SFG2, SFF10, SFF20)
    WRITE(7, 755) SFN1, SFN2
    755  FORMAT(' SFN1  SFN2 ', 2F20.1)
    IF(IVR.EQ.3) THEN
    c     ђ бзҐв ¤Ґ©бвўЁвҐ«м­®Ј® Є®нддЁжЁҐ­в  н Ї б  Їа®з­®бвЁ
    c       Ї® ¬Ґв®¤ЁЄҐ ‘…ђ…Ќ‘…ЌЂ - ЉЋ‡‹Ћ‚Ђ - ђЂ‘“‹Ћ‚Ђ - ѓЋ‹‹…ђЂ
    DO 777 I2 = 1, 2
    IF(I2.EQ.1) SFF = SFF10
    IF(I2.EQ.2) SFF = SFF20
    WRITE(7, 758) I2, IT1, SFF
    758   FORMAT(' <CILEV> I2  IT1  SFF=   ', 2I5, F10.2)
    IF(SFF.LT.1.05.AND.SFF.GT.0.95) GOTO 559
    SFR(1) = SFF
    WRITE(7, 759) SFR(1)
    759   FORMAT(' <CILEV>  SFR(1)=   ', F10.2)
    DO 553 II = 1, 10
    DO 551 I = 1, IT1
    IF(II.EQ.1) THEN
    TQR(I) = TQ1(I) * SFR(II)
    ELSE
    TQR(I) = TQR(I) * SFR(II)
    END IF
    551        CONTINUE
    WRITE(7, 761) (TQR(I), I = 1, IT1)
    761   FORMAT('   TQR   ', 5F10.2)
    CALL IZGIBU(IPR, IE, SGN, 0, DTC, A0, KNR, P, L,
        *Z1, Z2, MN, AL, BE, X1, X2, B1, B2, IMD, HA, CZ1, CZ2,
        *U, AW, D1, D2, EPSA, EPSB, ALTW,
        *DA1, DA2, DB1, DB2, ZVE1, ZVE2, Z0,
        *IN, IT1, TQR, TC1, RM1, WH, TMAX, IST2, IST3, GM,
        *IKG, IG, IQ, IP, LO, S1, FKE, IZ1,
        *IVR, PR, IMF1, IMF2, IRV, TN, N1R, TNZ,
        *YT1, YZ1, YT2, YZ2, YR1, YR2,
        *IG1, IG2, H1, H2, HK1, HK2,
        *SFLB1, SFLB2, SFPM1, SFPM2,
        *TQF, TQFP, TQEV, RMP, EV, EP,
        *PF1, PF2, SFMF1, SFMF2, SFN1, SFN2, SFG1, SFG2, SFF1, SFF2)
    IF(I2.EQ.1)  SFR(II + 1) = SFF1
    IF(I2.EQ.2)  SFR(II + 1) = SFF2
    WRITE(7, 768) II, SFR(II + 1)
    768   FORMAT('  II  SFR(ii+1) ', I5, F10.2)
    IF(SFR(ii + 1).LT.1.05.AND.SFR(ii + 1).GT.0.95) THEN
    IIR = II
    GOTO 555
    END IF
    553  CONTINUE
    555  SFF = SFR(1)
    WRITE(7, 762) (SFR(I), I = 1, 10)
    762   FORMAT('   SFR(i=1,10)   ', 5F10.2)
    DO 558 I = 1, IIR
    SFF = SFF * SFR(I + 1)
    WRITE(7, 763) SFF
    763   FORMAT(' from  SFF(2) to  SFF(iir)  ', F15.3)
    558        CONTINUE
    559   IF(I2.EQ.1) THEN
    SFR1 = SFF
    WRITE(7, 764) IIR, SFF
    764       FORMAT(' ‚…„“™……   IIR   SHF1  ', I5, F10.3)
    ELSE
    SFR2 = SFF
    WRITE(7, 765) IIR, SHF
    765       FORMAT(' ‚…„ЋЊЋ…   IIR   SFF2  ', I5, F10.3)
    END IF
    777   CONTINUE
    CALL PRCPI3(IVP, PF10, PF20, SFMF1, SFMF2,
        *SFN10, SFN20, SFF10, SFF20, SFR1, SFR2)
    END IF
    C
    WRITE(7, 706) WH, TQ(1), TQEV
    706  FORMAT(' CILEV bef ruzc: WH,TQ(1),TQEV: ', 3F9.3)
    C      p бзҐв гбЁ«Ё© ў § жҐЇ«Ґ­ЁЁ
    CALL  NAGRSEC(TQ(1), 1, IVP, AL, D1, BE, 1, 0., 0.)
    IF(IPR.GE.3) CALL RUZC(L, TQ(1), TQH, TQHP, TQF, TQFP, U,
        *AW, ALTW, BE, KPD, IE, RMP, TQEV, EV, EP, PR)

    96	IF(IS.NE.ISR) THEN
    C      Џ…ђ…‘—…’ ЌЂ ‘‹…„“ћ™“ћ ‘’“Џ…Ќњ ђ…„“Љ’ЋђЂ
    PRS = U * KPD
    DO 97 I = 1, IT
    RM(I) = RM(I) / U
    97     TQ(I) = TQ(I) * PRS
    DO 98 I = 1, IT1
    RM1(I) = RM1(I) / U
    98     TQ1(I) = TQ1(I) * PRS
    TMAX = TMAX * PRS
    IF(N1R.GT.1) N1R = N1R / U
    IF(L.LT. - 1.) WH = WH / U
    END IF
    99  CONTINUE
    RETURN
    END
    */
