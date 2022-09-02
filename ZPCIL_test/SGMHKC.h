#include <iostream>
#include <math.h>
#include "X3X2C.h"

using namespace std;

//  ������ �� �������������� ����������� �����������
//  ���������� ��� ������������� �������� �����
//          ����������  8  ����
//
//  ������� ��������� :
//
//  SIGH - �������� ��������� ����������
//  SIGHM - ������������ ����������
//  ROV - ����������� ������ ��������
//  HT - ������� ������������ ����
//  HV - ��������� ����������� � �������� �������
//  HKV - ��������� ���������� � �������� �������
//
//  �������� ��������� :
// (������ � ������ ����������������� ����������)   C
//   SGHKPU - �������� ������.������.KOHTAKTHOE ���������� C
//   SIGH - ��������� KOHTAKTHOE �CTA�OCTHOE HA��������  C
//   SIGHM - MAKC�MA��HOE KOHTAKTHOE HA��������

extern fstream f_1;    // ���� ��� ����������    //***

void SGMHKC(float SIGH, float SIGHM, float WHT, float ROV, float HT, float HV, float HKV, int IG, int I)
{
    float SHKMIN[7] = { 1.2, 1.3, 1.4, 1.4, 1.5, 1.4, 1.4 };
    float SGMHKP = 0, SGMHKM = 0;

    //      HH - ������� p����������� ���� ����������
    //           ��������� ����������� ���p������
    float HH = 1.52 * sqrt(WHT * ROV / 2.1E+5);

    //      HTEF - ����������� �������� ��p��������� ����
    float HTEF = HH + .2;
    
    //      HEFF - ���������� ���p����� ��p��������� ����
    float HEFF = HV / ((HV / HKV - 1.) * pow((HTEF / HT), 2) + 1.);

    cout << "SGMHKC:      HV = " << HV << "    HKV = " << HKV << "    HTEF = " << HTEF << "    HT = " << HT << endl;

    if (HEFF < HKV) HEFF = HKV;

        //   ������� ���������� ���� ���������� ���p�������

        if (HT < HH)  SGMHKP = 3.6 * HKV;                             // ������� ���� ������ � ��p�������
        if (HT == HH) SGMHKP = (pow((HT / HH), 2) * .8 + 2.8) * HKV;  // ������� ���� �� �p����� ��p��������� ����
        if (HT > HH)  SGMHKP = SGMHKP = 3.6 * HEFF;                   // ������� ���� � ��p�������� ����

        float SGHKPU = SGMHKP / SHKMIN[IG-1];

        cout << "SGMHKC     SGHKPU = " << SGHKPU << "    SIGH = " << SIGH << "    I = " << I << endl;

        if (SGHKPU < SIGH && I == 1) {
            f_1 << "\n\n    ��������� ���������� ������������ �������� �� �������������\n";
            f_1 << "\n      �������� ������. ��������� ����������, ���   SGHKPU " << SGHKPU;
            f_1 << "\n      �������� �������.��������.����������, ���      SIGH " << SIGH;
            }
        if (SGHKPU < SIGH && I == 2) {
            f_1 << "\n\n    ��������� ���������� ������������ ������ �� �������������\n";
            f_1 << "\n      �������� ������. ��������� ����������, ���   SGHKPU " << SGHKPU;
            f_1 << "\n      �������� �������.��������.����������, ���      SIGH " << SIGH;
        }
        //  p����� �p� ������������ ���p����
        float WHTMAX = WHT * pow((SIGHM / SIGH), 2);
        float HHM = 1.52 * sqrt(WHTMAX * ROV / 2.1E+5);
        float HTEFM = HHM + .2;
        float HEFFM = HV / ((HV / HKV - 1.) * pow((HTEFM / HT), 2) + 1.);
        if (HEFFM < HKV) HEFF = HKV;

        
        if (HT < HHM)  SGMHKM = 7.2 * HKV;        // ������� ���� ������ � ��p�������
        if (HT == HHM) {                          // ������� ���� �� �p����� ��p��������� ����
            float C = 1.6E+6 * HKV * pow((HT / ROV), 2);
            float D = .42 * HKV;
            SGMHKM = X3X2C(D, C);
        }
        if (HT > HHM) SGMHKM = 7.2 * HEFFM;       // ������� ���� � ��p�������� ����
           
        float SGHKMU = SGMHKM / SHKMIN[IG - 1];

        if (SGHKMU < SIGHM && I == 1) {
            f_1 << "\n\n    ��������� ���������� ��������� ��������";
            f_1 << "\n      ��� ������������ �������� �� �������������\n"; 
            f_1 << "\n      �������� ������. ��������� ����������, ���   SGHKMU " << SGHKMU;
            f_1 << "\n      �������� �������.��������.����������, ���     SIGHM " << SIGHM;
        }
        if (SGHKMU < SIGHM && I == 2) {
            f_1 << "\n\n    ��������� ���������� ��������� ������";
            f_1 << "\n      ��� ������������ �������� �� �������������";
            f_1 << "\n      �������� ������. ��������� ����������, ���   SGHKMU " << SGHKMU;
            f_1 << "\n      �������� �������.��������.����������, ���     SIGHM " << SIGHM;
        }
               
}
/*
C
C       SUBROUTINE   SGMHKC
C   ������ �� �������������� ����������� �����������
C   ���������� ��� ������������� �������� �����
C           ����������  8  ����
C
C   ������� ���������:
C
C   SIGH  - �������� ��������� ����������
C   SIGHM - ������������ ����������
C   ROV   - ����������� ������ ��������
C   HT    - ������� ������������ ����
C   HV    - ��������� ����������� � �������� �������
C   HKV   - ��������� ���������� � �������� �������
C
C   �������� ���������:
C         (������ � ������ ����������������� ����������)   C
C    SGHKPU - �������� ������.������.KOHTAKTHOE ���������� C
C    SIGH   - ��������� KOHTAKTHOE �CTA�OCTHOE HA��������  C
C    SIGHM  - MAKC�MA��HOE KOHTAKTHOE HA��������
C
C
      SUBROUTINE SGMHKC(SIGH,SIGHM,WHT,ROV,HT,HV,HKV,IG,I)
      REAL SHKMIN(7)
       EXTERNAL X3X2C
C        SAVE
      DATA SHKMIN /1.2,1.3,1.4,1.4,1.5,2*1.4/
C      HH - ������� p����������� ���� ����������
C           ��������� ����������� ���p������
      HH=1.52*SQRT(WHT*ROV/2.1E+5)

C      HTEF - ����������� �������� ��p��������� ����
      HTEF=HH+.2
C      HEFF - ���������� ���p����� ��p��������� ����

       WRITE(7,7771) HV, HKV, HTEF, HT, HH
7771	format ('contau 7771', 5F10.2)

      HEFF=HV/((HV/HKV-1.)*(HTEF/HT)**2+1.)

       WRITE(7,7772)
7772	format ('contau 7772')

         IF(HEFF.LT.HKV) HEFF=HKV
C   ������� ���������� ���� ���������� ���p�������
      IF (HT-HH) 10,20,30
C   ������� ���� ������ � ��p�������
   10 SGMHKP=3.6*HKV
      GOTO 40
C   ������� ���� �� �p����� ��p��������� ����
   20 SGMHKP=((HT/HH)**2*.8+2.8)*HKV
      GOTO 40
C   ������� ���� � ��p�������� ����
   30 SGMHKP=3.6*HEFF
   40 CONTINUE
      SGHKPU=SGMHKP/SHKMIN(IG)
      IF(SGHKPU.LT.SIGH.AND.I.EQ.1) WRITE(1,101) SGHKPU,SIGH
  101 FORMAT(//'  ��������� ���������� ������������ �������� ',
     *'�� �������������'/
     *'  �������� ������.��������� ����������, ���  SGHKPU',F9.1/
     *'  �������� �������.��������.����������, ���    SIGH',F9.1/)
      IF(SGHKPU.LT.SIGH.AND.I.EQ.2) WRITE(1,102) SGHKPU,SIGH
  102 FORMAT(//'  ��������� ���������� ������������ ������ ',
     *'�� �������������'/
     *'  �������� ������.��������� ����������, ���  SGHKPU',F9.1/
     *'  �������� �������.��������.����������, ���    SIGH',F9.1/)
C  p����� �p� ������������ ���p����
      WHTMAX=WHT*(SIGHM/SIGH)**2
      HHM=1.52*SQRT(WHTMAX*ROV/2.1E+5)
      HTEFM=HHM+.2
      HEFFM=HV/((HV/HKV-1.)*(HTEFM/HT)**2+1.)
         IF(HEFFM.LT.HKV) HEFF=HKV
      IF (HT-HHM) 50,60,70
C  ������� ���� ������ � ��p�������
   50    SGMHKM=7.2*HKV
         GOTO 80
C  ������� ���� �� �p����� ��p��������� ����
   60    C=1.6E+6*HKV*(HT/ROV)**2
         D=.42*HKV
         SGMHKM=X3X2C(D,C)
         GOTO 80
C  ������� ���� � ��p�������� ����
   70    SGMHKM=7.2*HEFFM
   80 SGHKMU=SGMHKM/SHKMIN(IG)
      IF(SGHKMU.LT.SIGHM.AND.I.EQ.1) WRITE(1,103) SGHKMU,SIGHM
  103 FORMAT(//'  ��������� ���������� ��������� �������� '/
     *'  ��� ������������ �������� �� �������������'/
     *'  �������� ������.��������� ����������, ���   SGHKMU',F9.1/
     *'  �������� �������.��������.����������, ���    SIGHM',F9.1/)
      IF(SGHKMU.LT.SIGHM.AND.I.EQ.2) WRITE(1,104) SGHKMU,SIGHM
  104 FORMAT(//'  ��������� ���������� ��������� ������ '/
     *'  ��� ������������ �������� �� �������������'/
     *'  �������� ������.��������� ����������, ���   SGHKMU',F9.1/
     *'  �������� �������.��������.����������, ���    SIGHM',F9.1/)
       RETURN
       END

*/
