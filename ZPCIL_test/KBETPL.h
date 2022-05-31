#include <math.h>
#include "AKFBTP.h"

//           PAC�ET KO��.HEPABHOMEPHOCT� PAC�PE�E�EH��    
//          HA����K� �O ���HE KOHTAKTH�X ��H��            
//          ��AHETAPH�X �EPE���                           
//                                                        
//  BXO�H�E ��PAMETP� : 
//                                                         
//  IKG - �H�EKC KOHCTP�KT�BHO� CXEM�                      
//  NW - KO���ECTBO CATE���TOB                            
//  BW - PA�O�A� ��P�HA BEH�A                             
//  DA - �E��T.��AMETP CO�H�A                             
//  BE - ��O� HAK�OHA ���A                                
//  MN - MO���� HOPMA��H��                                
//  EPSA - KO��.TOP�OBO�O �EPEKP�T��                      
//  HB - TBEP�OCT� MEHEE ���P���O ��EMEHTA                
//  V - OKP��A� CKOPOCT�                                 
//  A0 - �APAMETP HEPABHOMEPHOCT� �A�P��K� CATE���TOB    
//  K0 - KO��.H������HHOCT�                              
//
//  ���� ��������.�� ��������  ��������(���) ��� ������.������� ���
//  KNR = -1 (�.�.��� ����.��.�������)
//  B�XO�H�E �APAMETP� : KHBE, KFBE                      
//                                                       
//----------------------------------------------------------
void  KBETPL(float SGN, int IKG, int NW, float BW, float DA, float BE, float MN, float EPSA, float HB, float V, float A0, float KNR, float OMG, float K0, float& KHBE, float& KFBE)
{
    float AT = 0, KHBE0 = 0;

    if (KNR == 0) {      // OMG ��� �� ����������
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
        //     KW = KHW �� �������� O��
        float KHW = 1. - 20. / (pow((.01 * HB + 2.), 2) * pow((V + 4.), .25));
        KHBE = OMG + (KHBE0 - 1.) * KHW;
        KFBE = AKFBTP(KHBE, MN, BE, BW, EPSA);
}
/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                          C
C           PAC�ET KO��.HEPABHOMEPHOCT� PAC�PE�E�EH��      C
C           HA����K� �O ���HE KOHTAKTH�X ��H��             C
C           ��AHETAPH�X �EPE���                            C
C                                                          C
C   BXO�H�E ��PAMETP�:                                     C
C                                                          C
C   IKG - �H�EKC KOHCTP�KT�BHO� CXEM�                      C
C   NW  - KO���ECTBO CATE���TOB                            C
C   BW  - PA�O�A� ��P�HA BEH�A                             C
C   DA  - �E��T.��AMETP CO�H�A                             C
C   BE  - ��O� HAK�OHA ���A                                C
C   MN  - MO���� HOPMA��H��                                C
C   EPSA- KO��.TOP�OBO�O �EPEKP�T��                        C
C   HB  - TBEP�OCT� MEHEE ���P���O ��EMEHTA                C
C   V   - OKP��A� CKOPOCT�                                 C
C   A0  - �APAMETP HEPABHOMEPHOCT� �A�P��K� CATE���TOB     C
C   K0  - KO��.H������HHOCT�                               �

C ���� ��������. �� ��������  �������� (���) ��� ������.������� ���
C KNR=-1 (�.�. ��� ����.��.�������)
C   B�XO�H�E �APAMETP�:   KHBE,KFBE                        C
C                                                          C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      SUBROUTINE  KBETPL(SGN,IKG,NW,BW,DA,BE,MN,EPSA,HB,V,A0,KNR,OMG,
     *                   K0,KHBE,KFBE)
C     AT=1. - �OKOBO� �O�BO� ���������� MOMEHTA
C     AT=.5 - �EHTPA��H�� �O�BO� ���������� MOMEHTA
      REAL K0,KHBE0,KHBE,KFBE,KHW, MN,  KNR
       EXTERNAL AKFBTP
    IF(KNR.NE.0) GOTO 7      ! OMG ��� ����������
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
C     KW=KHW �� METO���� O��
   33     KHW=1.-20./    (  (   (.01*HB+2.)**2 )  *  (V+4.)**.25)
        KHBE=OMG+(KHBE0-1.)*KHW
        KFBE= AKFBTP(KHBE,MN,BE,BW,EPSA)
        WRITE(7,100) OMG,KHBE0,KHW,KHBE,KFBE
  100  FORMAT(' --KBETPL--omg,khbe0,khw,khbe,kfbe,--',5f10.5)
      RETURN
      END


*/
