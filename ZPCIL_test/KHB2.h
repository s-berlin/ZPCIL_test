#include <math.h>
float KHB2(float BW, float D1, float BE, int IG, int IQ, int IP, float L, float S1, int IST, float WM, float V, float HVM)
//   расчет коэффициента KHBET по методике  Opi
// Дополнительные исходные данные:
//  L - расстояние между опорами шестерни
//  S1 - расстояние от опоры со стороны
//       подвода T1 до середины шестерни      
//  Признаки:
//  IQ - приложение момента : 1 - одностороннее, -1 - разностороннее
//  IP - тип подшипника:  0 - скольжения  1 - ролик  2 - шарик
//  IG - соседняя ступень : 0 - отсутствует, в ост. случаях по TAbl
   //   IMPLICIT REAL(K - M)
{
    float KT[2], KS[2], KB[2], KFC[2], KQ[2], KK[2], KBC[2];
    float AC[5] = { .024, -.017, .06, 0., .02 };
    float AL[5] = { .2, 6., 1.65, 0., 3. };
    float AB[5] = { 3., 7.5, 1.3, 10.6, 9. };
    float AT = 0, B = 0;

    float BETG = BE;
    int IS = IG;

    float PS = BW / D1;
    float P2 = pow(PS, 2);
    float P33 = pow(PS, 3.3);
    float P35 = pow(PS, 3.5);
    float P033 = pow(PS, .33);
    float P07 = pow(PS, .7);
    float P075 = pow(PS, .75);
    float PLB = L / BW;
    float PL2 = pow(PLB, 2);
    float PSL = S1 / L;
    float AA = .5 - PSL;
    float AP = pow(abs(AA), .75);
    
    if (IQ == -1) AT = 8.;
    if (IQ == 1) AT = 12.;

    if (IP == 0) B = 0;
    if (IP == 1) B = 5;
    if (IP == 2) B = 16;

    // учет вида зубьев
    float KZ = 1. - .02 * BETG;

    // учет кручения
    KT[0] = (5. + AT) * P2 * .01 * KZ;
    KT[1] = (5. - AT) * P2 * .01 * KZ;

    // учет изгиба
    float KF = (PLB + 4.) * P2 * .0375;

    // цикл по торцам: 1 - со стороны Q, 2 - с противоположной
    for (int i = 0; i < 2; i++) {
        KFC[i] = 0.;
        KBC[i] = 0.;
    }
    // учет расположения шестерни
    if (AA >= 0) KS[0] = AP * P33 * PL2 * .16;
    else KS[0] = -1 * AP * P33 * PL2 * .16;
    KS[1] = -KS[0];
 
    // учет осадки подшипника
    KB[0] = (PSL - .5) / pow((PLB + 1.), 1.5) * P075 * B;
    KB[1] = -KB[0];

    // учет точности передачи
    KQ[0] = pow(IST, 2) * P033 * 1.6 / WM;
    KQ[1] = -KQ[0];

    // учет приработки передачи
    float KW = 1. - 20. / (pow((.01 * HVM + 2.), 2) * pow((V + 4.), .25));

    // учет соседней ступени
    if (IS != 0) {
        KFC[0] = pow((PLB - AL[IS]), 2) * P35 * AC[IS];
        KFC[1] = -KFC[0];
        KBC[0] = pow((PLB - 8.), 2) * AB[IS] * B * P07 * .0001;
        KBC[1] = -KBC[0];
    }

    // цикл по торцам: 1 - со стороны Q, 2 - с противоположной
    for (int i = 0; i < 2; i++) 
        KK[i] = (KT[i] + KF + KS[i] + KB[i] + KFC[i] + KBC[i] + KQ[i]) * KW + 1.;

    float KHB2 = KK[0];
    if (KK[1] > KK[0]) KHB2 = KK[1];
    
    return KHB2;
}
          
/*

                FUNCTION KHB2(BW,D1,BE,IG,IQ,IP,L,S1,IST,WM,V,HVM)
C   PAC~ET KO | fficiEHTA  KHBET pO METOdiKE  Opi
C  dOpOlHiTElxHyE iCXOdHyE dAHHyE :
C  L - PACCTOqHiE MEvdu OpOPAMi{ECTEPHi
C  S1 - PACCTOqHiE OT OpOPy CO CTOPOHy
C       pOdBOdA T1 dO CEPEdiHy {ECTEPHi      pPizHAKi
C  IQ - pPilOvEHiE MOMEHTA : 1 - OdHOCTOPOHHEE - 1 - PAzHOCTOPOHHEE
C  IP - Tip pOd{ipHiKA:  0 - CKOlxvEHiq  1 - POliK  2 - {APiK
C  IG - COCEdHqq CTupEHx : 0 - OTCuTCTBuET,B OCT.Clu~AqX - pO TAbl
      IMPLICIT REAL(K - M)
      DIMENSION KT(2),KS(2),KB(2),KFC(2),KQ(2),KK(2),KBC(2)
     *,AC(5),AL(5),AB(5)
C        SAVE
      DATA AC / .024,-.017,.06,0.,.02 / , AL / .2,6.,1.65,0.,3. / ,
     * AB / 3.,7.5,1.3,10.6,9. /
      BETG = BE
      IS = IG
    3 PS = BW / D1
      P2 = PS * *2
      P33 = PS * *3.3
      P35 = PS * *3.5
      P033 = PS * *.33
      P07 = PS * *.7
      P075 = PS * *.75
      PLB = L / BW
      PL2 = PLB * *2
      PSL = S1 / L
      AA = .5 - PSL
      AP = ABS(AA) * *.75
      IF(IQ.EQ. - 1) AT = 8.
      IF(IQ.EQ.1) AT = 12.
      IF(IP.EQ.0) B = 0.
      IF(IP.EQ.1) B = 5.
      IF(IP.EQ.2) B = 16.
C        u~ET BidA zubxEB
      KZ = 1. - .02 * BETG
C        u~ET KPu~EHiq
      KT(1) = (5. + AT) * P2 * .01 * KZ
      KT(2) = (5. - AT) * P2 * .01 * KZ
C        u~ET izgibA
      KF = (PLB + 4.) * P2 * .0375
C        ciKl pO TOPcAM : 1 - CO CTOPOHy Q
C                         2 - C pPOTiBOpOlOvHOj
           DO 1 I = 1,2
      KFC(I) = 0.
    1 KBC(I) = 0.
C        u~ET PACpOlOvEHiq {ECTEPHi
      KS(1) = SIGN(1.,AA) * AP * P33 * PL2 * .16
      KS(2) = -KS(1)
C        u~ET OCAdKi pOd{ipHiKA
      KB(1) = (PSL - .5) / (PLB + 1.) * *1.5 * P075 * B
      KB(2) = -KB(1)
C        u~ET TO~HOCTi pEPEdA~i
      KQ(1) = IST * *2 * P033 * 1.6 / WM
      KQ(2) = -KQ(1)
C        u~ET pPiPAbOTKi pEPEdA~i
      KW = 1. - 20. / ((.01 * HVM + 2.) * *2 * (V + 4.) * *.25)
C        u~ET COCEdHEj CTupEHi
      IF(IS.EQ.0) GOTO 5
      KFC(1) = (PLB - AL(IS)) * *2 * P35 * AC(IS)
      KFC(2) = -KFC(1)
      KBC(1) = (PLB - 8.) * *2 * AB(IS) * B * P07 * .0001
      KBC(2) = -KBC(1)
C        ciKl pO TOPcAM : 1 - CO CTOPOHy Q
C                         2 - C pPOTiBOpOlOvHOj
    5 DO 10 I = 1,2
      KK(I) = (KT(I) + KF + KS(I) + KB(I) +
     *KFC(I) + KBC(I) + KQ(I)) * KW + 1.
   10 CONTINUE
                KHB2 = AMAX1(KK(1),KK(2))
   20 CONTINUE
C     PRINT 101,IQ,IP,IS,L,S1,KHB2
C 101 FORMAT(1X,'IQ IP IS',3I4,'L  S1',2F8.1,5X,'KHBE=',F6.2 / )
      RETURN
      END

*/
