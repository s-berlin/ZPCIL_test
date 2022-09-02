#include <iostream>
#include <math.h>

using namespace std;
//=============================================================
//                                                          
//         FUNCTION   SGHPBE                                
//   интегальный метод pасчета допускаемого контактного     
//   напpяжения для косозубой зубчатой пеpедачи             
//                                                          
//   BXOДHЫE ПАPAMETPЫ : 
//                                                          
//   SGHP1 - допускаемое напpяжение для матеpиала шестеpни  
//   SGHP2 - колеса    
//   AA1, AA2 - углы пpофиля пpи веpшине шестеpни и колеса   
//   ALTW - угол зацепления                                
//   Z1, Z2 - числа зубьев ш - ни и к - са
//   HB1, HB2 - твеpдости повеpхности
//   V - окpужная скоpость, M / C
//                                                          
//   BЫXOДHOЙ ПAPAMETP : C
//   SGHPBE - интегpальное доп.напpяжение
//                                                          
//===========================================================

float SGHPBE(float SGHP1, float SGHP2, float AA1, float AA2, float ALTW, float Z1, float Z2, float HB1, float HB2, float V)
{
    float sghpbe;
    float FIMP = 0;
    float PI2 = 6.28318;
    int IH = 1;
    if (HB1 > 350 && HB2 > 350.) IH = 2;
    float U = Z2 / Z1;
    float TGATW = tan(ALTW);
    float EPA1 = Z1 * (tan(AA1) - TGATW) / PI2;
    float EPA2 = Z2 * (tan(AA2) - TGATW) / PI2;
    float EPSA = EPA1 + EPA2;
 // коэф., учитывающие геом.параметры зац - я
    float K1 = PI2 * EPA1 / (Z1 * tan(ALTW));
    float K2 = K1 * EPA2 / EPA1;
    float DLT1 = 1. + K1 * .5 - K1 * .5 / U - .333 * K1 * K1 / U;
    float DLT2 = 1. - K2 * .5 + K2 * .5 / U - .333 * K2 * K2 / U;
 // коэф.увеличения доп.контактных нап - й головок зубьев
    float MUK1 = 1.6;
    if (HB1 > 200.) MUK1 = pow((200. / HB1), 0.25) * 1.6;
    float MUK2 = 1.6;
    if (HB2 > 200.) MUK2 = pow((200. / HB2), 0.25) * 1.6;
//  доп.напряжения в зонах зацепления
    float SGHZ1 = min(SGHP1 * MUK1, SGHP2);
    float SGHZ2 = min(SGHP1, SGHP2 * MUK2);
    float SGMAX = max(SGHZ1, SGHZ2);
    float SGMIN = min(SGHZ1, SGHZ2);
//  коэф.ограничения повышенных допускаемых напряжений
    float FIP = SGMAX / SGMIN;
       //	print*, ' *SGHPBE**IH,V,FIP,AA1,AA2,ALTW,DLT1,DLT2,K1,K2,U '
       //	print*, IH, V, FIP, AA1, AA2, ALTW, DLT1, DLT2, K1, K2, U
    if (IH == 2 && V >= 9.) FIMP = 1.;
    if (IH == 2 && V < 9.) FIMP = sqrt(1.9 - .1 * V);
    if (IH == 1 && V < 15.) FIMP = sqrt(2.7 - .1 * V);
    if (IH == 1 && V >= 15.) FIMP = 1.12;
    
    if (FIP > FIMP) {
        FIP = FIMP;
        if (SGHZ2 > SGHZ1) SGHZ2 = SGHZ1 * FIP;
        else SGHZ1 = SGHZ2 * FIP;
    }
    float SS = EPA1 * DLT1 * SGHZ1 * SGHZ1 + EPA2 * DLT2 * SGHZ2 * SGHZ2;

    cout << "SGHPBE:      SS = " << SS << "    DLT1 = " << DLT1 << "    DLT2 = " << DLT2 << "    U = " << U << "    K1 = " << K1 << "    EPA1 = " << EPA1 << "    Z1 = " << Z1 << "    ALTW = " << ALTW << endl;

    sghpbe = sqrt(SS / EPSA);
    float SGPMIN = min(SGHP1, SGHP2);

    cout << "SGHPBE: ***  SGHP1 = " << SGHP1 << "    SGHP2 = " << SGHP2 <<  "    sghpbe = " << sghpbe << "    SGPMIN = " << SGPMIN << endl;

    if (sghpbe < SGPMIN) sghpbe = SGPMIN;

    cout << "SGHPBE:      SS = " << SS << "    FIP = " << FIP << "    SGMAX = " << SGMAX << "    SGMIN = " << SGMIN << "    sghpbe = " << sghpbe << endl;
        
    return sghpbe;
}
/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                          C
C         FUNCTION   SGHPBE                                C
C   интегальный метод pасчета допускаемого контактного     C
C   напpяжения для косозубой зубчатой пеpедачи             C
C                                                          C
C   BXOДHЫE ПАPAMETPЫ:                                     C
C                                                          C
C   SGHP1 - допускаемое напpяжение для матеpиала шестеpни  C
C   SGHP2 -                                      колеса    C
C   AA1,AA2 - углы пpофиля пpи веpшине шестеpни и колеса   C
C   ALTW  - угол зацепления                                C
C   Z1,Z2 - числа зубьев ш-ни и к-са
C   HB1,HB2 - твеpдости повеpхности
C   V     - окpужная скоpость, M/C
C                                                          C
C   BЫXOДHOЙ ПAPAMETP:                                     C
C   SGHPBE - интегpальное доп.напpяжение
C                                                          C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C
C
      FUNCTION SGHPBE(SGHP1,SGHP2,AA1,AA2,ALTW,Z1,Z2,HB1,HB2,V)
      IMPLICIT REAL (K-M)
C         SAVE
      PI2=6.28318
        IH=1
        IF(HB1.GT.350.AND.HB2.GT.350.) IH=2
      U=Z2/Z1
      TGATW=TAN(ALTW)
      EPA1=Z1*(TAN(AA1)-TGATW)/PI2
      EPA2=Z2*(TAN(AA2)-TGATW)/PI2
      EPSA=EPA1+EPA2
C  коэф.,учитывающие геом.параметры зац-я
      K1=PI2*EPA1/(Z1*TAN(ALTW))
      K2=K1*EPA2/EPA1
      DLT1=1.+K1*.5-K1*.5/U-.333*K1*K1/U
      DLT2=1.-K2*.5+K2*.5/U-.333*K2*K2/U
C   коэф. увеличения доп.контактных нап-й головок зубьев
      MUK1=1.6
      IF(HB1.GT.200.) MUK1=(200./HB1)**.25*1.6
      MUK2=1.6
      IF(HB2.GT.200.) MUK2=(200./HB2)**.25*1.6
C    доп. напряжения в зонах зацепления
      SGHZ1=AMIN1(SGHP1*MUK1,SGHP2)
      SGHZ2=AMIN1(SGHP1,SGHP2*MUK2)
      SGMAX=AMAX1(SGHZ1,SGHZ2)
      SGMIN=AMIN1(SGHZ1,SGHZ2)
C  коэф.ограничения повышенных допукаемых напряжений
      FIP=SGMAX/SGMIN
c	print *,' *SGHPBE**IH,V,FIP,AA1,AA2,ALTW,DLT1,DLT2,K1,K2,U '
c	print *,IH,V,FIP,AA1,AA2,ALTW,DLT1,DLT2,K1,K2,U
      IF(IH.EQ.2.AND.V.GE.9.) FIMP=1.
      IF(IH.EQ.2.AND.V.LT.9.) FIMP=SQRT(1.9-.1*V)
      IF(IH.EQ.1.AND.V.LT.15.) FIMP=SQRT(2.7-.1*V)
      IF(IH.EQ.1.AND.V.GE.15.) FIMP=1.12
      IF(FIP-FIMP) 25,25,5
   5  FIP=FIMP
      IF(SGHZ2-SGHZ1) 10,10,20
   10 SGHZ1=SGHZ2*FIP
      GOTO 25
   20 SGHZ2=SGHZ1*FIP
   25 SS=EPA1*DLT1*SGHZ1**2+EPA2*DLT2*SGHZ2**2
c	print *,' *SGHPBE*(25)*SS,SGHZ1,SGHZ2 ',SS,SGHZ1,SGHZ2
      SGHPBE=SQRT(SS/EPSA)
      SGPMIN=AMIN1(SGHP1,SGHP2)
      IF(SGHPBE.LT.SGPMIN) SGHPBE=SGPMIN
      RETURN
      END

*/
