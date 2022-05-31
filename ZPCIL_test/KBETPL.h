#include <math.h>
#include "AKFBTP.h"

//           PACЧET KOЭФ.HEPABHOMEPHOCTИ PACПPEДEАEHИЯ    
//          HAГРУЗKИ ПO ДЛИHE KOHTAKTHЫX ЛИHИЙ            
//          ПЛAHETAPHЫX ПEPEДАЧ                           
//                                                        
//  BXOДHЫE ПАPAMETPЫ : 
//                                                         
//  IKG - ИHДEKC KOHCTPУKTИBHOЙ CXEMЫ                      
//  NW - KOЛИЧECTBO CATEЛЛИTOB                            
//  BW - PAБOЧAЯ ШИPИHA BEHЦA                             
//  DA - ДEЛИT.ДИAMETP COЛHЦA                             
//  BE - УГOЛ HAKЛOHA ЗУБA                                
//  MN - MOДУЛЬ HOPMAЛЬHЫЙ                                
//  EPSA - KOЭФ.TOPЦOBOГO ПEPEKPЫTИЯ                      
//  HB - TBEPДOCTЬ MEHEE ТВЕPДОГO ЭЛEMEHTA                
//  V - OKPУЖAЯ CKOPOCTЬ                                 
//  A0 - ПAPAMETP HEPABHOMEPHOCTИ ЗAГPУЗKИ CATEЛЛИTOB    
//  K0 - KOЭФ.HАПРЯЖЕHHOCTИ                              
//
//  Учет неравном.по методике  Расулова(ММЗ) для планет.передач при
//  KNR = -1 (т.е.для кажд.яч.матрицы)
//  BЫXOДHЫE ПAPAMETPЫ : KHBE, KFBE                      
//                                                       
//----------------------------------------------------------
void  KBETPL(float SGN, int IKG, int NW, float BW, float DA, float BE, float MN, float EPSA, float HB, float V, float A0, float KNR, float OMG, float K0, float& KHBE, float& KFBE)
{
    float AT = 0, KHBE0 = 0;

    if (KNR == 0) {      // OMG еще не определена
        float A = A0 * K0;
        if (NW - 5 < 0)  OMG = .007 * A + 1.071;
        if (NW - 5 == 0) OMG = .023 * A + 1.064;
        if (NW - 5 > 0)  OMG = .053 * A + 1.042;
    }
    if (IKG == 8) AT = .5;
    if (IKG == 9) AT = 1.;
        
    if (SGN < 0) KHBE0 = 1.;
    else {
        float PSA = BW * AT / DA;
        int INW = NW - 1;
        if (BE > 0.01 && BE < 0.4) INW = NW + 5;

        if (INW == 12) KHBE0 = .24 * PSA * PSA - .02 * PSA + 1.03;
        if (INW == 13) KHBE0 = .16 * PSA * PSA + .36 * PSA + 0.88;
        if (INW == 14) KHBE0 = .16 * PSA * PSA + .50 * PSA + 0.84;
        if (INW == 15) KHBE0 = .24 * PSA * PSA + .56 * PSA + 0.82;
        if (INW == 16) KHBE0 = .30 * PSA * PSA + .55 * PSA + 0.85;
        if (INW == 22) KHBE0 = .22 * PSA * PSA + .21 * PSA + 0.92;
        if (INW == 23) KHBE0 = .28 * PSA * PSA + .28 * PSA + 0.95;
        if (INW == 24) KHBE0 = .44 * PSA * PSA + .24 * PSA + 0.97;
        if (INW == 25) KHBE0 = .20 * PSA * PSA + .86 * PSA + 0.76;
        if (INW == 26) KHBE0 = .38 * PSA * PSA + .75 * PSA + 0.82;

        if (KHBE0 < 1.) KHBE0 = 1.;
    }
        //     KW = KHW по методике OПИ
        float KHW = 1. - 20. / (pow((.01 * HB + 2.), 2) * pow((V + 4.), .25));
        KHBE = OMG + (KHBE0 - 1.) * KHW;
        KFBE = AKFBTP(KHBE, MN, BE, BW, EPSA);
}
/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                          C
C           PACЧET KOЭФ.HEPABHOMEPHOCTИ PACПPEДEАEHИЯ      C
C           HAГРУЗKИ ПO ДЛИHE KOHTAKTHЫX ЛИHИЙ             C
C           ПЛAHETAPHЫX ПEPEДАЧ                            C
C                                                          C
C   BXOДHЫE ПАPAMETPЫ:                                     C
C                                                          C
C   IKG - ИHДEKC KOHCTPУKTИBHOЙ CXEMЫ                      C
C   NW  - KOЛИЧECTBO CATEЛЛИTOB                            C
C   BW  - PAБOЧAЯ ШИPИHA BEHЦA                             C
C   DA  - ДEЛИT.ДИAMETP COЛHЦA                             C
C   BE  - УГOЛ HAKЛOHA ЗУБA                                C
C   MN  - MOДУЛЬ HOPMAЛЬHЫЙ                                C
C   EPSA- KOЭФ.TOPЦOBOГO ПEPEKPЫTИЯ                        C
C   HB  - TBEPДOCTЬ MEHEE ТВЕPДОГO ЭЛEMEHTA                C
C   V   - OKPУЖAЯ CKOPOCTЬ                                 C
C   A0  - ПAPAMETP HEPABHOMEPHOCTИ ЗAГPУЗKИ CATEЛЛИTOB     C
C   K0  - KOЭФ.HАПРЯЖЕHHOCTИ                               С

C Учет неравном. по методике  Расулова (ММЗ) для планет.передач при
C KNR=-1 (т.е. для кажд.яч.матрицы)
C   BЫXOДHЫE ПAPAMETPЫ:   KHBE,KFBE                        C
C                                                          C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      SUBROUTINE  KBETPL(SGN,IKG,NW,BW,DA,BE,MN,EPSA,HB,V,A0,KNR,OMG,
     *                   K0,KHBE,KFBE)
C     AT=1. - БOKOBOЙ ПOДBOД ВРАЩАЮЩЕГО MOMEHTA
C     AT=.5 - ЦEHTPAЛЬHЫЙ ПOДBOД ВРАЩАЮЩЕГО MOMEHTA
      REAL K0,KHBE0,KHBE,KFBE,KHW, MN,  KNR
       EXTERNAL AKFBTP
    IF(KNR.NE.0) GOTO 7      ! OMG уже определена
CCC	IF(A0.EQ.0.) THEN
CCC	OMG=KNR
CCC	GOTO 7
CCC	END IF
      A=A0*K0
      IF(NW-5) 4,5,6
    4   OMG=.007*A+1.071
        GOTO 7
    5   OMG=.023*A+1.064
        GOTO 7
    6   OMG=.053*A+1.042
    7 IF(IKG.EQ.8) AT=.5
      IF(IKG.EQ.9) AT=1.
    IF(SGN.LT.0) THEN
    KHBE0=1.
    GOTO 33
    END IF
    PSA=BW*AT/DA
      INW=NW-1
      IF(BE.GT.0.01.AND.BE.LT.0.4) INW=NW+5
      GOTO(12,13,14,15,16,22,23,24,25,26),INW
   12    KHBE0=.24*PSA*PSA-.02*PSA+1.03
         GOTO 17
   13    KHBE0=.16*PSA*PSA+.36*PSA+0.88
         GOTO 17
   14    KHBE0=.16*PSA*PSA+.50*PSA+0.84
         GOTO 17
   15    KHBE0=.24*PSA*PSA+.56*PSA+0.82
         GOTO 17
   16    KHBE0=.30*PSA*PSA+.55*PSA+0.85
         GOTO 17
   22    KHBE0=.22*PSA*PSA+.21*PSA+0.92
         GOTO 17
   23    KHBE0=.28*PSA*PSA+.28*PSA+0.95
         GOTO 17
   24    KHBE0=.44*PSA*PSA+.24*PSA+0.97
         GOTO 17
   25    KHBE0=.20*PSA*PSA+.86*PSA+0.76
         GOTO 17
   26    KHBE0=.38*PSA*PSA+.75*PSA+0.82
   17    IF(KHBE0.LT.1.) KHBE0=1.
C     KW=KHW по METOдике OПИ
   33     KHW=1.-20./    (  (   (.01*HB+2.)**2 )  *  (V+4.)**.25)
        KHBE=OMG+(KHBE0-1.)*KHW
        KFBE= AKFBTP(KHBE,MN,BE,BW,EPSA)
        WRITE(7,100) OMG,KHBE0,KHW,KHBE,KFBE
  100  FORMAT(' --KBETPL--omg,khbe0,khw,khbe,kfbe,--',5f10.5)
      RETURN
      END


*/
