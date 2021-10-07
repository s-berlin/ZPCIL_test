#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>
#include "ZPGR.h"
#include "ZPRGMS.h"

using namespace std;
extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN, N1R;
extern float L, WH;      // ������, �����
extern float T1R, TMAX;     // ������ �� �������� ����, ��
extern float TQ[20], TC[20], RM[20];

extern fstream f_1;    // ���� ��� ����������    //***

//========== ���������� �� �������
extern int IVP;                             // ��� �������
extern float Z1, Z2;                        // ����� ������ �������� � ������
extern float MN, BE, X1, X2;                // ������, ���� �������, ������������ ��������
extern int flaw;
extern float AW, B1, B2;                    // ��������� ���������� ������ �������� � ������
extern float AL, HA, HL, CZV;               // ���� �������, ������������: ������ �������, ��������� ������, ����������� ������  
extern int IST1, IST2, IST3, IST4, IST5;    // ������� �������� �� ������: ����������, ���������, ��������; ��� ����������, ��� ������� �� ������� �����
extern int IMD, IKG;                        // ����. ������� ��������� �������, ����� ����� �� ����������� ������
extern float SHLM1, SHPM1, SFLB1, SFPM1;    // ��������: ������ ����. ������������, ������. ����. ���������� ��� ����. ��������, ���. ������ ������-� ��� ������, ������. ���. ���������� ������ ��� ����. �������� 
extern float SHLM2, SHPM2, SFLB2, SFPM2;    // ������:   - " -    - " -    - " -    - " -
extern int IG1, IG2;                        // ������ ��������� �������� � ������
extern float H1, HK1, HT1, SHER1, YZ1;      // ��������: ��������� �����������, ��������� ����������, ������� ������������ ����, �������������, ����. ������� ��������� ���������
extern float YT1, YR1, SHV1;                // ��������: ��������������� �����������, ������������� ���������� �����������, ����. ������ ���������
extern float H2, HK2, HT2, SHER2, YZ2;      // ������: ��������� �����������, ��������� ����������, ������� ������������ ����, �������������, ����. ������� ��������� ���������
extern float YT2, YR2, SHV2;                // ������: ��������������� �����������, ������������� ���������� �����������, ����. ������ ���������
extern int IMF1, IMF2, IVR;                 // �������� ���������� ���������� ����������� �������� � ������, ������� ������� ����-�� ������ �� ���������� ������������
extern float CZ1, CZ2, KSP, KPD, PR;        // ����� ���������� �� ������ �������� � ������, ����. �������� ������, ���, ����������� ������������ �� �������� ������������
extern float LO, S1, FKE, GM;               // ���������� ����� �������, ���������� �� ����� �� ������� ������� ������� �� ������ ��������, ?, ?
extern int IQ, IP, IZ1, IG;                 // ��� ���������� �������, ��� ����������, ?, ?
extern float GRM;
extern int SEC;

extern fstream f_1;    // ���� ��� ����������    //***

void  VYVODS()
{
    fstream fi;     // ���� ��� ������
    int IS = 0;
    string KM[2] = { "���", "����" };
    string KPM[2] = { "����", "����" };
    string KT[6] = { " - A", " - B", " - C", " - D", " - E", " - H" };
    char KT5[8] = { 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'h'};
    string IE2[2]{ " M��     ", "���/��.��" };
    int I2 = 0;
    if (IE = 2) I2 = 1;

    cout << "VYVODS" << endl;

    //------------ - �������� ����� ������� �������--------------

    fi.open("NOMST.DAT", fstream::in);
    fi >> IS;
    fi.close();

    f_1 << "\n\n                " << IS << " - �  ������� \n";
    f_1 << "\n" << " ( �������������� ������������ �������� �������� ���������� )\n";
    f_1 << "\n     �������� ������ ��� �������\n\n";
    f_1 << "                                         �������� ������\n";
    f_1 << "                                         �������  �������\n";
    f_1 << "\n����� ������                           Z       " << Z1 << "      " << Z2;
    f_1 << "\n������                                 MN      " << MN;
    
    BE = ZPGR(BE); // �������������� � �������
    ZPRGMS(BE, GRM, SEC);
    f_1 << "\n���� ������� ���� (����.���.���)       BE      " << GRM << SEC;
    if(AW == 0)
    f_1 << "\n������������ ��������                  X  " << X1 << "      " << X2;
    if(AW != 0)
    f_1 << "\n��������� ����������                   AW      " << AW;

    f_1 << "\n������ ��������� �����                 B       " << B1 << "      " << B2;
    f_1 << "\n�����. ������ ������� ����             HA      " << HA;
    f_1 << "\n������� ����������� ������� ����       IMD     " << KM[IMD];  //IM �� ����� IMD !!! ��� �������� IM ?????
    if(IST1 == IST2 && IST1 == IST3)
    f_1 << "\n������� �������� �� ���� 1643-81       IST     " << IST1 << KT[IST4] << " - " << KT5[IST5];
    else
    f_1 << "\n������� �������� �� ���� 1643-81       IST     " << IST1 << " - " << IST2 << " - " << IST3 << KT[IST4] << " - " << KT5[IST5];

    if (IMD == 0 && HA == 1 && AL == 20)
        f_1 << "\n�������� ������ �� ���� 13755-81\n (��� ����������� �������)";

    if (IMD != 0 && HA == 1 && AL == 20)
        f_1 << "\n�������� ������ �� ���� 13755-81";

    AL = ZPGR(AL); // �������������� � �������
    ZPRGMS(AL,GRM,SEC);

    cout << "VYVODS: GRM = " << GRM << "   SEC = " << SEC;

    if (HA != 1 || GRM != 20 || CZV != 0.2 || IPR >= 6)
        f_1 << "\n��������� ��������� �������" << "\n alfa = " << GRM << "." << SEC << "    ha* = " << HA << "    hl* = " << HL << "    c* = " << CZV;

    if (L != 0)   // L = 0 ���� ��� ������� �� ��������� (������ ���������)
    {
        f_1 << "\n������� ������������ \n�������� �����                         IKG     " << IKG;
        
        if (IKG == 0)
        {
            f_1 << "\n���������� ��������� \n���������� �����                       FKE     " << FKE;
            f_1 << "\n������� ������������ ��������          IZ1     " << IZ1;
        }
        if (IKG == 10)
        {
            f_1 << "\n����� ����� �� ����.16 ����            IG      " << IG;
            f_1 << "\n���������� �������                     IQ      " << IQ << "   " << KPM[IP] << "���������";
 //           f_1 << "\n  1 - ������������� \n -1 - ������������� ";

            f_1 << "\n��� ����������                         IP      " << IP;
            f_1 << "\n 0 - ��������� ���������� \n 1 - ��������� \n 2 - ���������";

            f_1 << "\n���������� ����� �������               L0      " << LO;
            f_1 << "\n���������� �� ����� �� ������� \n������� ������� �� �������� \n��������                               S1      " << S1;

            f_1 << "\n����� ���������� �� ������             CZ      " << CZ1 << "      " << CZ2;
            f_1 << "\n������� ������� ��������� �������      GM      " << GM;
            f_1 << "\n������� ������� ������������ ������          ";
            f_1 << "\n��������� �� ���������� ��������.      IVR     " << IVR;

         /*
            0 - �p��������� �� ����. 11, �.2 �OCT
            1 - �������� ������������� SHV1, SHV2
            2 - SH1, SH2 � ����������� ��������. - ������������ � ���������
                ��� IVR = 2 PR = 0. � ����������� � ���������
         */
             if (PR > 0)
            f_1 << "\n����������� ������������   ";
            f_1 << "\n�� �������� ��������.                  PR      " << PR;

            f_1 << "\n����������� ��������� ��������         KPD     " << KPD;
            f_1 << "\n����������� �������� ������            KSP     " << KSP;

            f_1 << "\n����� ������ ���������                 IG      " << IG1 << "      " << IG2;
            f_1 << "\n��������� �����������                  H       " << H1 << "     " << H2;
            f_1 << "\n��������� ����������                   HK      " << HK1 << "     " << HK2;
            f_1 << "\n������� ������������ ����              HT      " << HT1 << "    " << HT2;
            f_1 << "\n������������� ����������� ����         SHER    " << SHER1 << "    " << SHER2;
            f_1 << "\n�����. ������� ��������� ���������     YZ      " << YZ1 << "      " << YZ2;
            f_1 << "\n��������������� �����������            YT      " << YT1 << "      " << YT2;

            f_1 << "\n������������ �������������    ";
            f_1 << "\n���������� �����������                 YR      " << YR1 << "      " << YR2;
            if (IMF1 != 0 || IMF2 != 0) {
                f_1 << "\n������� ������� ����������    ";
                f_1 << "\n���������� �����������                 IMF     " << IMF1 << "     " << IMF2;
            }
            if (IVR == 1) {
                f_1 << "\n���������� ����. ������ ���������    ";
                f_1 << "\n�� ���������� ������������             SHV     " << SHV1 << "     " << SHV2;
            }
            if (SHLM1 > 0 || SHLM2 > 0) {
                f_1 << "\n���������O� ���������� ���������E    ";
                f_1 << "\n��� ������������ �������� " << IE2[I2] << "    SGHPM   " << SHPM1 << "    " << SHPM2;
            }
            if (SFLB1 > 0 || SFLB2 > 0) {
                f_1 << "\n������� ������ ������������    ";
                f_1 << "\n������ ��� ������         " << IE2[I2] << "    SGFLB   " << SFLB1 << "     " << SFLB2;
            }
            if (SFPM1 > 0 || SFPM2 > 0) {
                f_1 << "\n���������O� ���������� ��� ������    ";
                f_1 << "\n���� ������������ ��������� " << IE2[I2] << "  SGFPM   " << SFPM1 << "    " << SFPM2;
            }
            if (IE == 2) {
                SHLM1 = SHLM1 * 9.81;
                SHLM2 = SHLM2 * 9.81;
                SHPM1 = SHPM1 * 9.81;
                SHPM2 = SHPM2 * 9.81;
                SFLB1 = SFLB1 * 9.81;
                SFLB2 = SFLB2 * 9.81;
                SFPM1 = SFPM1 * 9.81;
                SFPM2 = SFPM2 * 9.81;
            }
            if (IPR >=3 ) f_1 << "\n___________________";
        }
    }
 /*



 */
}

/*
        SUBROUTINE VYVODS
     * (IVP,L,WH,IS,IR,IPR,IE,ISR,KPD,KSP,
     * Z1,Z2,MN,BE,X1,X2,AW,B1,B2,AL,HA,HL,CZV,IMD,IST1,IST2,
     * IST3,IST4,IST5,IKG,FKE,IZ1,IG,IQ,IP,LO,S1,CZ1,CZ2,GM,
     * IVR,PR,
     *    SHLM1,SHLM2,SHPM1,SHPM2,SFLB1,SFLB2,SFPM1,SFPM2,
     *    IG1,H1,HK1,HT1,SHER1,YZ1,YT1,YR1,IMF1,SHV1,
     *    IG2,H2,HK2,HT2,SHER2,YZ2,YT2,YR2,IMF2,SHV2)
C                                                               C
C  ����� ������.���. �� �������� p������p� (� �����)            C
C                                                               C
       CHARACTER*16 IR
       CHARACTER*4 KTS
       CHARACTER*3 KT(6)
       CHARACTER*1 KT5(8)
       CHARACTER*4 KM(2),KPM(2)
       CHARACTER*10 KP(3)
       CHARACTER*9 IE2(2)
       REAL MN
       REAL L
       REAL LO
       REAL KPD
       REAL KSP
        SAVE
      DATA KT/'- A','- B','- C','- D','- E','- H'/
      DATA KT5/'x','y','z','a','b','c','d','h'/
      DATA KM/'����','��� '/
      DATA KPM/'����','����'/
      DATA KP/'����������','��������� ',
     * '��������� '/
      DATA IE2/' M��     ','���/��.��'/
      I2 =1
      IF(IE.EQ.2) I2 =2
        KTS=KT(IST4)
    IF(IST5.EQ.8.AND.(IST4.EQ.5.OR.IST4.EQ.6)) GO TO 5
       IF(IST5.NE.(IST4+3)) KTS=KT(IST4)//KT5(IST5)
    5 CONTINUE
      IM=1
      IF(IMD.EQ.0) IM=2
      IPM=1
      IF(IQ.EQ.-1) IPM=2
       IF(IP-1) 10,11,12
   10 IP1=1
      GOTO 13
   11 IP1=3
      GOTO 13
   12 IP1=2
   13   WRITE(1,106) IS
  106 FORMAT(/20X,I2,' - �  ������� '//
     * 9X,'( �������������� ������������ �������� '/
     * 9X,'          �������� ���������� )'/)
        WRITE(1,107)
  107 FORMAT(5X,'�������� ������ ��� �������'/
     * 46X,'�������� ������'/
     * 46X,'�������  �������'/)
        CALL ZPGR(BE)
        CALL ZPRGMS(BE,GRM,SEC)
        WRITE(1,108) Z1,Z2,MN,GRM,SEC
  108 FORMAT(
     *   ' ����� ������                         Z    ',2F8.0/
     *   ' ������                               MN   ',F13.3/
     *   ' ���� ������� ���� (����.���.���)     BE   ',F12.2,F3.2)
        IF(AW.EQ.0.) WRITE(1,114) X1,X2
  114 FORMAT(
     *   ' ������������ ��������                X    ',F12.4,F8.4)
      IF(AW.NE.0.) WRITE(1,109) AW
  109 FORMAT(
     *   ' ��������� ����������                 AW   ',F11.1)
        WRITE(1,110) B1,B2,KM(IM)
  110 FORMAT(
     *   ' ������ ��������� �����               B    ',F9.1,F8.1/
C    *   ' �����. ������ ������� ����           HA   ',F12.2/
     *   ' ������� ����������� ������� ����     IMD  ',8X,A4)
      IF((IST1-IST2)+(IST1-IST3))7,8,7
    7 WRITE(1,116) IST1,IST2,IST3,KTS
  116 FORMAT(
     *   ' ������� �������� �� ���� 1643-81     IST  ',4X,
     *I2,'-',I2,'-',I2,A4)
      GOTO 9
    8 WRITE(1,117) IST1,KTS
  117 FORMAT(
     *   ' ������� �������� �� ���� 1643-81     IST  ',8X,I2,A4)
    9 CONTINUE
      IF(IMD.EQ.0.AND.HA.EQ.1.AND.AL.EQ.20.0) WRITE(1,212)
  212 FORMAT(
     *   ' �������� ������ �� ���� 13755-81'/
     *   ' (��� ����������� �������)')
      IF(IMD.NE.0.AND.HA.EQ.1.AND.AL.EQ.20.0) WRITE(1,213)
  213 FORMAT(
     *   ' �������� ������ �� ���� 13755-81')
       CALL ZPGR(AL)
       CALL ZPRGMS(AL,GRM,SEC)
C       HL=2.*HA
      IF(HA.NE.1..OR.GRM.NE.20..OR.CZV.NE.0.2.OR.IPR.GE.6)
     * WRITE(1,214) GRM,SEC,HA,HL,CZV
  214 FORMAT(
     *   ' ��������� ��������� �������:'/
     *   ' alfa = ',F5.2,F3.2,', ha* = ',F5.2,
     *   ', hl* = ',F5.2,', c* = ',F5.2)
           IF(L.EQ.0.) RETURN
       WRITE(1,215) IKG
  215 FORMAT(
     *   ' ������� ������������  '/
     *   ' �������� �����                       IKG  ',I10)
C                                                              C
C  �p�  IKG=0 �������� �������������:                          C
C                                                              C
      IF(IKG.EQ.0) WRITE(1,200) FKE,IZ1
  200 FORMAT(
     *   ' ���������� ���������  '/
     *   ' ���������� �����                     FKE  ',F13.3/
     *   ' ������� ������������ ��������        IZ1  ',I10)
C                                                              C
C  �p�  IKG=10 �������� �������������:                         C
C                                                              C
      IF(IKG.EQ.10) WRITE(1,201) IG,KPM(IPM),
     *  KP(IP1),LO,S1
  201 FORMAT(
     *   ' ����� ����� �� ����.16 ����          IG   ',I10/
     *   ' ���������� �������                   IQ     ',A4,'���������'/
C    1 - �������p�����
C   -1 - �������p�����
     *   ' ��� ����������                       IP     ',A10/
C    0 - ��������� ���������
C    1 -           ��p������
C    2 -           p��������
     *   ' ���������� ����� �������             LO   ',F12.2/
     *   ' ���������� �� ����� �� �������'/
     *   ' ������� ������� �� �������� '/
     *   ' ��������                             S1   ',F12.2)
        WRITE(1,111) CZ1,CZ2
  111 FORMAT(
     *   ' ����� ���������� �� ������           CZ   ',F8.0,F9.0)
        IF(GM.GT.0.) WRITE(1,1110) GM
 1110 FORMAT(
     *   ' ������� ������� ��������� �������    GM   ',F11.1)
         WRITE(1,1111) IVR
 1111 FORMAT(
     *   ' ������� ������� ������������ ������ '/
     *   ' ��������� �� ���������� ��������.    IVR   ',I10)
C    0 - �p��������� �� ����. 11, �.2 �OCT
C    1 - �������� ������������� SHV1,SHV2
C    2 - SH1,SH2 � ����������� ��������.-������������ � ���������
C  ��� IVR=2 PR=0. � ����������� � ���������
         IF(PR.GT.0.) WRITE(1,1112) PR
 1112 FORMAT(
     *   ' ����������� ������������'/
     *   ' �� �������� ������������             PR   ',F13.3)
        WRITE(1,1113) KPD,KSP
 1113 FORMAT(
     *   ' ����������� ��������� ��������       KPD  ',F13.3/
     *   ' ����������� �������� ������          KSP  ',F13.3/)
        WRITE(1,112) IG1,IG2,H1,H2,HK1,HK2
  112 FORMAT(
     *   ' ����� ������ ���������               IG   ',I7,I8/
     *   ' ��������� �����������                H    ',2F9.1/
     *   ' ��������� ����������                 HK   ',2F9.1)
        IF(HT1.NE.0..OR.HT2.NE.0.) WRITE(1,1120) HT1,HT2
 1120 FORMAT(
     *   ' ������� ������������ ����            HT   ',2F9.3)
        WRITE(1,1121) SHER1,SHER2,YZ1,YZ2,YT1,YT2,YR1,YR2
 1121 FORMAT(
     *   ' ������������� ����������� ����       SHER ',2F9.3/
     *   ' �����. ������� ��������� ���������   YZ   ',2F9.3/
     *   ' ��������������� �����������          YT   ',2F9.3/
     *   ' ������������ �������������'/
     *   ' ���������� �����������               YR   ',2F9.3)
       IF(IMF1.NE.0.OR.IMF2.NE.0)  WRITE(1,1122) IMF1,IMF2
 1122 FORMAT(
     *   ' ������� ������� ����������'/
     *   ' ���������� �����������               IMF  ',I7,I8)
       IF(IVR.EQ.1) WRITE(1,113) SHV1,SHV2
  113 FORMAT(
     *   ' ���������� ����. ������ ���������'/
     *   ' �� ���������� ������������           SHV  ',2F9.3)
      IF(SHLM1.GT.0..OR.SHLM2.GT.0.) WRITE(1,1114) IE2(I2),SHLM1,SHLM2
 1114  FORMAT(
     *   ' ������ ���������� '/
     *   ' ������������, ',A9,'              SGHLM ',2F8.0)
      IF(SHPM1.GT.0..OR.SHPM2.GT.0.)
     * WRITE(1,1115) IE2(I2),SHPM1,SHPM2
 1115  FORMAT(
     *   ' ���������O� ���������� ���������E'/
     *   ' ��� ������������ ��������,',A9,'  SGHPM ',2F8.0)
      IF(SFLB1.GT.0..OR.SFLB2.GT.0.) WRITE(1,1116) IE2(I2),SFLB1,SFLB2
 1116  FORMAT(
     *   ' ������� ������ ������������'/
     *   ' ������ ��� ������, ',A9,'         SGFLB ',2F8.0)
      IF(SFPM1.GT.0..OR.SFPM2.GT.0.)
     * WRITE(1,1117) IE2(I2),SFPM1,SFPM2
 1117  FORMAT(
     *   ' ���������O� ���������� ��� ������'/
     *   ' ���� ������������ ���������,',A9,'SGFPM ',2F8.0)
      IF(IE.NE.2) GOTO 1000
      SHLM1 =SHLM1 *9.81
      SHLM2 =SHLM2 *9.81
      SHPM1 =SHPM1 *9.81
      SHPM2 =SHPM2 *9.81
      SFLB1 =SFLB1 *9.81
      SFLB2 =SFLB2 *9.81
      SFPM1 =SFPM1 *9.81
      SFPM2 =SFPM2 *9.81
 1000   IF(IPR.GE.3) WRITE(1,300)
  300 FORMAT(' __________ ')
      RETURN
      END


*/