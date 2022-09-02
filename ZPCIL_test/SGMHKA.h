#include <iostream>
#include <fstream>
#include <math.h>
#include "KAPR.h"

using namespace std;
// ==============================================================
//       SUBROUTINE   SGMHKA
//   PAC�ET HA �������������� ���������� �����������
//   PA�P������ ��� ������������� �������� ������
//           ����������  8 �OCT
//
//   BXO���� �APAMETP� :
//
//   SIGH - �������� ��������� ����������
//   SHR(I) - ����������� ���������� ��� ��������� ������
//   NC(I) - MACC�B ����� ������
//   ROV - ���BE�EHH�� ������ ��������
//   HT - ������� ������������ ����
//   IHT - ����� ����������� ��������
//   HV - TBEP����� �OBEPXHOCT� � �������� ��������
//   HKV - TBEPdOCT� CEP��EB���  � �������� ��������
//
//   B������� ���������
//   SGHKPU - �C�OBHOE �����HHOE KOHTAKTHOE HA�����H�E
//   SIGH - PAC�ETHOE KOHTAKTHOE �CTA�OCTHOE HA����EH�E
// ==============================================================

extern fstream f_1;    // ���� ��� ����������    //***

void SGMHKA(float SIGH, float SHR[100], int ITH, float NC[100], float ROV, float HT, float HV, float HKV, int II)
{
    float FI = HT * 10000. / (ROV * HKV);
    //    AF - ����.�p�������� ��������� ����������� ���p������
    //        � �p�������� ��������� ��p������� ���p�������
    float AF = 0.82 * FI + 0.118 * FI * FI + 4.68;
    if (FI <= 0.56) AF = 5.18;
    if (FI > 2.94) AF = 0.954 * FI + 5.32;
    float AL = HV / HKV;
    float MUT = 1.;
    if (FI >= 1.) {
 //    MUT - ����.����������� ����������� ������������� �p����
 //        �� � ��p�������, � � ��p�������� ����
        float MUT18 = FUN(0.003433, -0.074833, 1.0714, FI);
        float MUT22 = FUN(0.004862, -0.073621, 1.10509, FI);
        float MUT26 = FUN(0.006714, -0.073643, 1.142142, FI);
        float MUT = KAPR(1.8, MUT18, 2.2, MUT22, 2.6, MUT26, AL);
    }
    if (MUT > 1.) MUT = 1.;
        //    NHK - ������� ����� ������ ���p������
    float NHK = (.0133 * HKV - 1.) * 10.;
        //    p����� ����� ������ �������.������.���p������  NEK
    float NEK = 0.;
    for (int i = 0; i < ITH; i++) NEK = NEK + NC[i] * pow((SHR[i] / SIGH), 18);
      
       //   ZLK - ����.��������� �������������
    float ZLK = (NHK / NEK) * .0555;
    if (ZLK < 1.) ZLK = 1.;
    float SGMHPK = 1.07 * HKV * AF * MUT * ZLK;
       //    SGHKPU - �������� ������.���������� ���p������
    float SGHKPU = SGMHPK / 1.4;
    cout << "SGMHKA     SGHKPU = " << SGHKPU << "    SIGH = " << SIGH << "    II = " << II << endl;
    if (SGHKPU < SIGH && II == 1) {
        f_1 << "\n\n          ��������� ���������� ������������ �������� �� �������������\n";
        f_1 << "\n            �������� ������. ��������� ����������, ���   SGHKPU " << SGHKPU;
        f_1 << "\n            �������� �������.��������.����������, ���      SIGH " << SIGH;
        }
    if (SGHKPU < SIGH && II == 2) {
        f_1 << "\n\n          ��������� ���������� ������������ ������ �� �������������\n";
        f_1 << "\n            �������� ������. ��������� ����������, ���   SGHKPU " << SGHKPU;
        f_1 << "\n            �������� �������.��������.����������, ���      SIGH " << SIGH;
    }
 
}


/*
C
C       SUBROUTINE   SGMHKA
C   PAC�ET HA �������������� ���������� �����������
C   PA�P������ ��� ������������� �������� ������
C           ����������  8 �OCT
C
C   BXO���� �APAMETP� :
C
C   SIGH - �������� ��������� ����������
C   SHR(I) - ����������� ���������� ��� ��������� ������
C   NC(I) - MACC�B ����� ������
C   ROV - ���BE�EHH�� ������ ��������
C   HT - ������� ������������ ����
C   IHT - ����� ����������� ��������
C   HV - TBEP����� �OBEPXHOCT� � �������� ��������
C   HKV - TBEPdOCT� CEP��EB���  � �������� ��������
C
C   B������� ���������
C   SGHKPU - �C�OBHOE �����HHOE KOHTAKTHOE HA�����H�E
C   SIGH - PAC�ETHOE KOHTAKTHOE �CTA�OCTHOE HA����EH�E
C
SUBROUTINE SGMHKA(SIGH, SHR, ITH, NC, ROV, HT, HV, HKV, II)
REAL NC(ITH), SHR(ITH)
REAL NHK, NEK, MUT, MUT18, MUT22, MUT26
C         SAVE
FUN(A, B, C, X) = A * X * X + B * X + C
FI = HT * 10000. / (ROV * HKV)
C    AF - ����.�p�������� ��������� ����������� ���p������
C        � �p�������� ��������� ��p������� ���p�������
AF = 0.82 * FI + 0.118 * FI * FI + 4.68
IF(FI.LE.0.56) AF = 5.18
IF(FI.GT.2.94) AF = 0.954 * FI + 5.32
AL = HV / HKV
MUT = 1.
IF(FI.LT.1.) GOTO 5
C    MUT - ����.����������� ����������� ������������� �p����
C        �� � ��p�������, � � ��p�������� ����
MUT18 = FUN(0.003433, -0.074833, 1.0714, FI)
MUT22 = FUN(0.004862, -0.073621, 1.10509, FI)
MUT26 = FUN(0.006714, -0.073643, 1.142142, FI)
CALL KAPR(1.8, MUT18, 2.2, MUT22, 2.6, MUT26, AL, MUT)
5 IF(MUT.GT.1.) MUT = 1.
C    NHK - ������� ����� ������ ���p������
NHK = (.0133 * HKV - 1.) * 10.
C    p����� ����� ������ �������.������.���p������  NEK
NEK = 0.
DO 10 I = 1, ITH
10 NEK = NEK + NC(I) * (SHR(I) / SIGH) * *18
C    ZLK - ����.��������� �������������
ZLK = (NHK / NEK) * .0555
IF(ZLK.LT.1.) ZLK = 1.
SGMHPK = 1.07 * HKV * AF * MUT * ZLK
C    SGHKPU - �������� ������.���������� ���p������
SGHKPU = SGMHPK / 1.4
IF(SGHKPU.LT.SIGH.AND.II.EQ.1) WRITE(1, 101) SGHKPU, SIGH
101 FORMAT(//'  ��������� ���������� ������������ ��������'/
    *'  �� �������������' /
    *'  �������� ������. ��������� ����������, ���   SGHKPU', F9.1 /
    *'  �������� �������.��������.����������, ���      SIGH', F9.1 / )
    IF(SGHKPU.LT.SIGH.AND.II.EQ.2) WRITE(1, 102) SGHKPU, SIGH
    102 FORMAT(//'  ��������� ���������� ������������ ������'/
        *'  �� �������������' /
        *'  �������� ������. ��������� ����������, ���   SGHKPU', F9.1 /
        *'  �������� �������.��������.����������, M��      SIGH', F9.1 / )
    RETURN
    END
*/
