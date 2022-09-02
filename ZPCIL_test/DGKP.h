// =====+= ������ �������������� �������������� � �������������� ���������� =================

#include <iostream>
using namespace std;

extern float Z1, Z2;                        // ����� ������ �������� � ������
extern float MN, BE, X1, X2, X[2];          // ������, ���� �������, ������������ ��������

extern fstream f_1;    // ���� ��� ����������    //***

void DGKP(int I12, float DB[2], float BETB, float DP[2], float ROP[2], float DL[2], float ROL[2], float DELZV, float DG[2], float ROG[2], float DU[2], float DV[2],
          float RLM, float RLMIN, float RKEPS, float PALF, float PX, float SNA[2], float TETP[2], float TETV[2], float DZTP[2], float DZTV[2]) 
{
    f_1 << "\n\n          �������������� �������������� � " << endl;
    f_1 << "          �������������� ��������� ";

    if (I12 == 0)     f_1 << "\n                                           ��������  ������ ";   // ��������
             else f_1 << "\n                                              ������  �������� ";   // ��������������

    f_1 << "\n�������� ��������                    DB " << setw(10) << DB[0] << setw(10) << DB[1];
    f_1 << "\n�������� ����������� ������";
    f_1 << "\n�������� ����� �������               DP " << setw(10) << DP[0] << setw(10) << DP[1];
    f_1 << "\n������� �������� ���������";
    f_1 << "\n������� ���� � ������ �����         ROP " << setw(10) << ROP[0] << setw(10) << ROP[1];

    f_1 << "\n�������� ����������� ���������";
    f_1 << "\n����� �������                        DL " << setw(10) << DL[0] << setw(10) << DL[1];
    f_1 << "\n������� �������� ������� ����";
    f_1 << "\n��������� �����                     ROL " << setw(10) << ROL[0] << setw(10) << ROL[1];

    if (DELZV != 0.) {
        f_1 << "\n�������� ����������� �����������";
        f_1 << "\n������� ������                        DG " << setw(10) << DG[0] << setw(10) << DG[1];
        f_1 << "\n������� �������� ������� ����";
        f_1 << "\n� ��������� ����� �����������         ROG " << setw(10) << ROG[0] << setw(10) << ROG[1];

    }
    if (BE == 0.) {
        f_1 << "\n�������� ����������� ������� ������-";
        f_1 << "\n��� ����� ����������� ����������      DU " << setw(10) << DU[0] << setw(10) << DU[1];
        f_1 << "\n�������� ����������� ������ ������-";
        f_1 << "\n��� ����� ����������� ����������      DV " << setw(10) << DV[0] << setw(10) << DV[1];
    }

    f_1 << "\n\n��� ����������                     PALF " << setw(14) << PALF;
            
    ZPRGMS(BETB, GRM, SEC);

    if (BE != 0.) {
        f_1 << "\n\n������ ���                           PX " << setw(14) << PX;
        f_1 << "\n\n�������� ���� ������� ����� ���� BETB  " << setprecision(2) << fixed << setw(13) << GRM << "." << setw(2) << SEC << endl;
    }
    f_1 << "\n������������ ���������� �������" << endl;
    f_1 << "���� �� ����������� ������          SNA " << setprecision(3) << fixed << setw(10) << SNA[0] << setw(10) << SNA[1] << endl;
    f_1 << "�������� ���������� � ������" << endl;
    f_1 << "����� ��������� �������            TETP " << setw(10) << TETP[0] << setw(10) << TETP[1] << endl;

    if (BE == 0.) {
        f_1 << "\n�������� ���������� � ������ ������-" << endl;
        f_1 << "��� ����� ����������� ����������    TETV " << setw(10) << TETV[0] << setw(10) << TETV[1] << endl;
    }
    if (BE != 0.) {
        f_1 << "\n������� ��������� �����" << endl;
        f_1 << "���������� �����                     LM " << setw(14) << RLM << endl;
        f_1 << "���������� ��������� �����" << endl;
        f_1 << "���������� �����                   LMIN " << setw(14) << RLMIN << endl;
        f_1 << "����������� �������� ���������" << endl;
        f_1 << "��������� ����� ���������� �����   KEPS " << setw(14) << RKEPS << endl;
    }

}

/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                   �PO�PAMMA   " DGKP "			C
C            ������ �������������� ��������������		C
C            � �������������� ����������                        C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
SUBROUTINE DGKP(I12, DB, BET, BETB, DP, ROP, DL, ROL, DELZV, DG, ROG,
    *DU, DV, RLM, RLMIN, RKEPS, PALF, PX, SNA, TETP, TETV, DZTP, DZTV)
    DIMENSION DB(2),
    * DG(2), DL(2), ROL(2), DP(2), ROG(2), ROP(2), DU(2), DV(2),
    * DS(2), ROS(2),
    * TETP(2), TETV(2), DZTP(2), DZTV(2)
    DIMENSION SNA(2)
    WRITE(1, 100)
    100 FORMAT(/
        *11X, '�������������� �������������� �', /
        *11X, '�������������� ���������' / )
    IF(I12.LT.1) THEN
    C I12 = 0 - ��������
    WRITE(1, 191)
    191 FORMAT(
        *43X, '��������  ������')
    ELSE
    C I12 = 1 - ��������������
    WRITE(1, 192)
    192 FORMAT(
        *43X, ' ������  ��������')
    END IF
    WRITE(1, 101) DB, DP, ROP
    101 FORMAT(
        *' �������� ��������                    DB', 2F10.3 /
        *' �������� ����������� ������ ' /
        *' �������� ����� �������               DP', 2F10.3 /
        *' ������� �������� ��������� ' /
        *' ������� ���� � ������ �����         ROP', 2F10.3)
    WRITE(1, 102) DL, ROL
    102 FORMAT(
        *' �������� ����������� ���������' /
        *' ����� �������                        DL', 2F10.3 /
        *' ������� �������� ������� ����' /
        *' � ��������� �����                   ROL', 2F10.3)
    IF(DELZV.NE.0.) WRITE(1, 103) DG, ROG
    103 FORMAT(
        *' �������� ����������� �����������' /
        *' ������� ������                       DG', 2F10.3 /
        *' ������� �������� ������� ���� ' /
        *' � ��������� ����� �����������       ROG', 2F10.3)
    IF(BET.EQ.0.) WRITE(1, 104) DU, DV
    104 FORMAT(
        *' �������� ����������� ������� ������-' /
        *' ��� ����� ����������� ����������     DU', 2F10.3 /
        *' �������� ����������� ������ ������-' /
        *' ��� ����� ����������� ����������     DV', 2F10.3)
    CALL ZPRGMS(BETB, GRM, SEC)
    WRITE(1, 105) PALF
    105 FORMAT(/
        *' ��� ����������                     PALF', F13.3)
    IF(BET.NE.0.) WRITE(1, 1050) PX, GRM, SEC
    1050 FORMAT(/
        *' ������ ���                           PX', F13.3//
        * ' �������� ���� ������� ����� ����   BETB', F12.2, F3.2)
    WRITE(1, 1051) SNA, TETP
    1051 FORMAT(/
        *' ������������ ���������� �������' /
        *' ���� �� ����������� ������          SNA', 2F10.3//
        * ' �������� ���������� � ������' /
        *' ����� ��������� �������            TETP', 2F10.3)
    IF(BET.EQ.0.) WRITE(1, 106) TETV
    106 FORMAT(
        *' �������� ���������� � ������ ������-' /
        *' ��� ����� ����������� ����������   TETV', 2F10.3 / )
    IF(BET.NE.0.) WRITE(1, 107) RLM, RLMIN, RKEPS
    107 FORMAT(/
        *' ������� ��������� ����� ' /
        *' ���������� �����                     LM', F13.3 /
        *' ���������� ��������� ����� ' /
        *' ���������� �����                   LMIN', F13.3 /
        *' ����������� �������� ��������� ' /
        *' ��������� ����� ���������� �����   KEPS', F13.3 / )
    RETURN
    END
*/
