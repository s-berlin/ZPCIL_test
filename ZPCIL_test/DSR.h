#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>

using namespace std;

//========== ���������� �� �������
extern int IVP;                             // ��� �������
extern float Z1, Z2;                          // ����� ������ �������� � ������
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

void  DSR() 
{
    string str;
    char ch = ' ';
    int i = 0;
    fstream fi;

    cout << "DSR" << endl;
    
    fi.open("FILE2", fstream::in);

    getline(fi, str);  // ���������� ������
    cout << str << endl;
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> IVP;	                                            // ������������� �������
    cout << "DSR: IVP = " << IVP << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> Z1 >> Z2 >> MN >> BE;
    cout << "      " << Z1 << "      " << Z2 << "      " << MN << "      " << BE << endl;
    
    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> flaw >> AW >> X1 >> X2 >> B1 >> B2 >> AL >> HA >> HL >> CZV;
    cout << "     " << flaw << "   " << AW << "  " << X1 << "     " << X2 << "      " << B1;
    cout << "      " << B2 << "     " << AL << "      " << HA << "     " << HL << "    " << CZV << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> IMD >> IST1 >> IST2 >> IST3 >> IST4 >> IST5;
    cout << "      " << IMD << "      " << IST1 << "       " << IST2 << "       " << IST3 << "       " << IST4 << "       " << IST5 << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> IKG;
    cout << "      " << IKG << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> CZ1 >> CZ2 >> GM >> IVR >> PR >> KPD >> KSP;
    cout << "      " << CZ1 << "      " << CZ2 << "        " << GM << "      " << IVR << "     " << PR << "    " << KPD << "     " << KSP << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> SHLM1 >> SHPM1 >>SFLB1>> SFPM1;
    cout << "      " << SHLM1 << "       " << SHPM1 << "        " << SFLB1 << "        " << SFPM1  << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> IG1 >> H1 >> HK1 >> HT1 >> SHER1 >> YZ1 >> YT1 >> YR1 >> IMF1 >> SHV1;
    cout << "      " << IG1 << "       " << H1 << "     " << HK1 << "      " << HT1 << "    " << SHER1 << "      " << YZ1 << "       " << YT1 << "       " << YR1 << "     " << IMF1 << "     " << SHV1 << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> SHLM2 >> SHPM2 >> SFLB2 >> SFPM2;
    cout << "      " << SHLM2 << "       " << SHPM2 << "        " << SFLB2 << "        " << SFPM2 << endl;

    getline(fi, str);  // ���������� ������
    getline(fi, str);  // ���������� ������
    cout << str << endl;

    fi >> IG2 >> H2 >> HK2 >> HT2 >> SHER2 >> YZ2 >> YT2 >> YR2 >> IMF2 >> SHV2;
    cout << "      " << IG2 << "       " << H2 << "     " << HK2 << "      " << HT2 << "    " << SHER2 << "      " << YZ2 << "       " << YT2 << "       " << YR2 << "     " << IMF2 << "     " << SHV2 << endl;


    fi.close(); // ��������� ����
};

/*
SUBROUTINE DSR(JJ, IR, L, IS, ISR, IPR, Z1, Z2, MN, BE, X1, X2,
    *AW, B1, B2, AL, HA, HL, CZV, IMD, IST1, IST2, IST3, IST4, IST5,
    *IKG, FKE, IZ1, IG,
    *IQ, IP, LO, S1, CZ1, CZ2, GM, IVR, PR, KPD, KSP,
    *SHLM1, SHLM2, SHPM1, SHPM2, SFLB1, SFLB2, SFPM1, SFPM2,
    *IG1, H1, HK1, HT1, SHER1, YZ1, YT1, YR1, IMF1, SHV1,
    *IG2, H2, HK2, HT2, SHER2, YZ2, YT2, YR2, IMF2, SHV2)
    C  ���������� �������� ������ ��������� � ����� �� ��������
    C  �� FILE 'B1' � ����������� ������
    REAL L
    REAL LO
    REAL KPD
    REAL KSP
    REAL MN
    CHARACTER * 65 A
    CHARACTER * 16 IR
    SAVE
    READ(2, 100) A
    READ(2, *) Z1, Z2, MN, BE
    READ(2, 100) A
    READ(2, *) iissmm, AW, X1, X2, B1, B2, AL, HA, HL, CZV

    C	B2 = B1
    C	AL = 20.
    C	HL = 1. + HA
    C	CZV = 0.25
    C      IF(X1.GT.10.) THEN
    C      AW = X1
    C	X1 = -5.
    C	X2 = -5.
    C       ELSE
    C      AW = 0.
    C        END IF
    READ(2, 100) A
    READ(2, *) IMD, IST1, IST2, IST3, IST4, IST5

    IF(L.EQ.0.) GOTO 12
    READ(2, 100) A
    READ(2, *) IKG
    IF(IKG.EQ.0.OR.IKG.EQ.10) READ(2, 100) A
    IF(IKG.EQ.0) READ(2, *) FKE, IZ1
    IF(IKG.EQ.10) READ(2, *) IG, IQ, IP, LO, S1
    READ(2, 100) A
    READ(2, *) CZ1, CZ2, GM, IVR, PR, KPD, KSP
    READ(2, 100) A
    READ(2, *) SHLM1, SHPM1, SFLB1, SFPM1
    READ(2, 100) A
    READ(2, *) IG1, H1, HK1, HT1, SHER1, YZ1, YT1, YR1, IMF1, SHV1
    READ(2, 100) A
    READ(2, *) SHLM2, SHPM2, SFLB2, SFPM2
    READ(2, 100) A
    READ(2, *) IG2, H2, HK2, HT2, SHER2, YZ2, YT2, YR2, IMF2, SHV2
    100 FORMAT(A65)
    12  RETURN
    END

*/