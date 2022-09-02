#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ������, �����
extern float T1R, TMAX;     // ������ �� �������� ����, ��
extern float TQ[20], TC[20], RM[20];
extern float Z1, Z2, U;                        // ����� ������ �������� � ������

extern fstream f_1;    // ���� ��� ����������    //***

void RUZC(float TQ1, float TQH, float TQHP, float TQF, float TQFP, float AW, float ALTW, float BE, float KPD, float IE, float RMP, float TQEV, float EV, float EP, float PR)
{
    string IE1[2]{ " � * �   ", "��� * ��" };
    string IE2[2]{ " �   ", "���" };

    float UI = U;

    int I1 = 0;
    if (IE == 2) I1 = 1;
    int I2 = 0;
    if (IE == 2) I2 = 1;
    //    p����� ������ � ����������
    float DW1 = 2. * AW / (UI + 1.);
    if (TQEV < 0.) DW1 = 2. * AW / (UI - 1.);
        //   ���p���� ��� p������ ����� TQ1 = TQ(1) - ���������� �� �����������
        //   � ������������� ������ ����� ������ ��� �������� �������� ����
        //   (��� L < -1)  WHE(������������ � UPORTQ)
    float TQR = TQ1;
    float FT = 2000. * TQR / DW1;
    float FR = FT * tan(ALTW);
    float FA = FT * tan(BE);
        //    ���������� ������� �� ������ ����
    float TFA1 = FA * DW1 / 2000.;
    float TFA2 = TFA1 * UI;
        //    p�������� � ����������� ������� �� �������� ����
    float TQ2R = TQ1 * UI * KPD;
    float TQ2HP = TQHP * UI;
    float TQ2FP = TQFP * UI;
    /*
    C  ������ � file3 ��� �������� � ������ ����� (���� ������ � �*� � � )
       WRITE(10,*) FT,FR,FA
       WRITE(10,*) TFA1,TFA2
       WRITE(10,*) RMP,TQR
       WRITE(10,*) TQ2R
    */

    if (IE == 2) {
        FT = FT / 9.81;
        FR = FR / 9.81;
        FA = FA / 9.81;
        TQR = TQR / 9.81;
        TFA1 = TFA1 / 9.81;
        TFA2 = TFA2 / 9.81;
        TQ2R = TQ2R / 9.81;
        TQ2HP = TQ2HP / 9.81;
        TQ2FP = TQ2FP / 9.81;
    }
    
    cout << "RUZC: TQ2HP = " << TQ2HP << "   TQ2FP = " << TQ2FP << "   ALTW = " << ALTW << "   UI = " << UI << "   KPD = " << KPD << endl;

    f_1 << "\n        ������ ��� ������� ����� � �����������" << endl;
    f_1 << "\n                   ������ � ���������� \n" << endl;

    f_1 << "�������� ������,   " << IE2[I2] << "                  FT " << setprecision(1) << fixed << setw(15) << FT << endl;
    f_1 << "���������� ������, " << IE2[I2] << "                  FR " << setw(15) << FR << endl;
    f_1 << "������ ������,     " << IE2[I2] << "                  FX " << setw(15) << FA << endl;
  
    if (BE > 0.) {
        f_1 << "\n              ���������� ������� �� ������ ����" << endl;
        f_1 << "\n�� ������� ������, " << IE1[I1] << "            TFA1 " << setw(15) << TFA1 << endl;
        f_1 <<   "�� ������� ������, " << IE1[I1] << "            TFA2 " << setw(15) << TFA2 << endl;
    }


   // RMP = -1  ������ ���  IVP = 3  ���� !!!!!!!!!
    if (RMP > -1.) {

        f_1 << "\n\n����������� ������� ��������" << endl;
        f_1 << "�������� ����, ��/���                    RMP " << setw(15) << RMP << endl;
        f_1 << "�������� ������ �� ������� ���� ������� " << endl;
        f_1 << "���������� �� ����������� (��������)," << IE1[I1] << "TQ1 " << setw(10) << TQR << endl;

        if (PR > 0.) {
            f_1 << "\n             �������� ������� �� ������� ���� �������" << endl;
            f_1 << "\n���������� �� �����������(��������), " << IE1[I1] << "TQ2 " << setw(10) << TQ2R << endl;

            f_1 << "\n������. �� ���������� ������������, " << IE1[I1] << "T2HP " << setw(10) << TQ2HP << endl;
            float SH = TQ2HP / TQ2R;
            f_1 << "    ����� �� ���������� ������������           SH " << setprecision(2) << fixed << setw(10) << SH << endl;

            f_1 << "\n������. �� �������� ������������, " << IE1[I1] << "  T2FP " << setprecision(1) << fixed << setw(10) << TQ2FP << endl;
            float SF = TQ2FP / TQ2R;
            f_1 << "    ����� �� �������� ������������             SF " << setprecision(2) << fixed << setw(10) << SF << endl;
        }
        else{ 
            f_1 << "�������� ������ �� ������� ���� ������� " << endl;
            f_1 << "���������� �� ����������� (��������), " << IE1[I1] << "  TQ2 " << setprecision(1) << fixed << setw(10) << TQ2R << endl;
        }
    }
    f_1 << "\n_____________" << endl;
     //   WRITE(1, 300)
     //   300 FORMAT(' __________ ')



}

/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C             �p��p���� "RUZC"                          C
C    p����� ������ � ���������� ������p������� ��p����� C
C    ������ p���������� p������                         C
C    PR=0. -������.�������� ���(����������� ��p����.��p��.C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      SUBROUTINE RUZC(L,TQ1,TQH,TQHP,TQF,TQFP,UI,AW,ALTW,BE,KPD,
     *IE,RMP,TQEV,EV,EP,PR)
      REAL   KPD,L
      CHARACTER*8 IE1(2)
      CHARACTER*4 IE2(2)
       SAVE
      DATA IE1/' �*�    ',' ���*�  '/
      DATA IE2/' �  ',' ���'/
      I1 =1
      IF(IE.EQ.2) I1 =2
      I2 =1
      IF(IE.EQ.2) I2 =2
C    p����� ������ � ����������
      DW1=2.*AW/(UI+1.)
      IF(TQEV.LT.0.) DW1=2.*AW/(UI-1.)
C   ���p���� ��� p������ ����� TQ1=TQ(1) - ���������� �� �����������
C   � ������������� ������ ����� ������ ��� �������� �������� ����
C   (��� L<-1)  WHE (������������ � UPORTQ )
        TQR = TQ1
      FT=2000.*TQR/DW1
      FR=FT*TAN(ALTW)
      FA=FT*TAN(BE)
C    ���������� ������� �� ������ ����
      TFA1=FA*DW1/2000.
      TFA2=TFA1*UI
C    p�������� � ����������� ������� �� �������� ����
       TQ2R=TQ1*UI*KPD
       TQ2HP=TQHP*UI
       TQ2FP=TQFP*UI

C  ������ � file3 ��� �������� � ������ ����� (���� ������ � �*� � � )
       WRITE(10,*) FT,FR,FA
       WRITE(10,*) TFA1,TFA2
       WRITE(10,*) RMP,TQR
       WRITE(10,*) TQ2R

      IF(IE.NE.2) GOTO 1
      FT   =FT    /9.81
      FR   =FR    /9.81
      FA   =FA    /9.81
      TQR  =TQR   /9.81
      TFA1 =TFA1  /9.81
      TFA2 =TFA2  /9.81
      TQ2R =TQ2R  /9.81
      TQ2HP=TQ2HP /9.81
      TQ2FP=TQ2FP /9.81
    1  WRITE(1,111)
  111 FORMAT(/11X,'������ ��� ������� ����� � �����������'//
     * 19X,'������ � ����������'/)
        WRITE(1,113) IE2(I2),FT,IE2(I2),FR,IE2(I2),FA
  113  FORMAT(
     *' �������� ������,',A4,25X,'FT',2X,F12.1/
     *' ���������� ������,',A4,23X,'FR',2X,F12.1/
     *' ������ ������,',A4,27X,'FX',2X,F12.1/)
        IF(BE.GT.0.)   WRITE(1,114) IE1(I1),TFA1,IE1(I1),TFA2
  114  FORMAT(/10X,
     *' ���������� ������� �� ������ ����'//
     *' �� ������� ������,',A8,19X,'TFA1',F12.1/
     *' �� ������� ������,',A8,19X,'TFA2',F12.1/)

C RMP=-1  ������ ���  IVP=3  ���� !!!!!!!!!
    IF(RMP.GT.-1.) THEN
      WRITE(1,119) RMP,IE1(I1),TQR
  119 FORMAT(/
     *' ����������� ������� ��������'/
     *' �������� ����, ��/���                 ',7X,'RMP',F13.1/
     *' �������� ������ �� ������� ���� �������'/
     *' ���������� �� ����������� (��������),',A8,'TQ1',F13.1/)
      IF(PR.GT.0.) THEN
       WRITE(1,115)
  115 FORMAT(/12X,'�������� ������� �� ������� ���� �������'/)
      WRITE(1,116) IE1(I1),TQ2R
  116 FORMAT(
     *' ���������� �� ����������� (��������),',A8,'TQ2',F13.1/)
      SH = TQ2HP/TQ2R
      SF = TQ2FP/TQ2R
      WRITE(1,1160) IE1(I1),TQ2HP,SH,IE1(I1),TQ2FP,SF
 1160 FORMAT(
     *' ������. �� ���������� ������������,',A8,'  T2HP',F12.1/
     *'   ����� �� ���������� ������������             SH',F12.2/
     *' ������. �� �������� ������������,',A8,'    T2FP',F12.1/
     *'     ����� �� �������� ������������             SF',F12.2/)
    ELSE
      WRITE(1,1161) IE1(I1),TQ2R
 1161 FORMAT(
     *' �������� ������ �� ������� ���� �������'/
     *' ���������� �� ����������� (��������),',A8,'TQ2',F13.1/)
    END IF
    END IF
       WRITE(1,300)
  300 FORMAT(' __________ ')
      RETURN
      END

*/