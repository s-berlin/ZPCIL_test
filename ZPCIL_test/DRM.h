#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>

using namespace std;

extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN, N1R;
extern float L, WH;      // ������, �����
extern float T1R, TMAX;     // ������ �� �������� ����, ��
extern float TQ[20], TC[20], RM[20];


void DRM()
{
	string str;
	char ch = ' ';
	int i = 0;
	fstream fi;

	cout << "DRM" << endl;

	fi.open("FILE1", fstream::in);

	getline(fi, str);  // ���������� ������

	fi >> IR;	                                            // ������������� �������
	cout << "DRM: IR = " << IR << endl;

	getline(fi, str);         // ���������� ������
	getline(fi, str);         // ���������� ������
	
	fi >> L;                                            // ��� ������ � ����������
														// L = -1 ����������� - ���� � DRM ���������� ������ ���� ������� !!																		
														// L = -10  ���� ������� ��������																		
														// L = -20  ��� ������� �������� (������������� � �������������) - �������������� ��� ����������
	cout << "DRM: L = " << L << endl;

	getline(fi, str);	            // ���������� ������
	getline(fi, str);	            // ���������� ������

	if (L = -1)  fi >> WH >> T1R;                        // ������ (���),      ��. ������ (�*�)

	cout << "DRM: WH = " << WH << "   T1R = " << T1R << endl;

	getline(fi, str);	            // ���������� ������
	getline(fi, str);	            // ���������� ������


	fi >> TMAX >> IT >> IE >> IRV >> IPR >> ISR;

	cout << "DRM: TMAX = " << TMAX << "   IT = " << IT << " IE = " << IE << " IRV = " << IRV << " IPR = " << IPR << " ISR = " << ISR << endl; // IT - ���-�� �������� �����������

	getline(fi, str);	            // ���������� ������
	for (i = 0; i < 3; i++) { getline(fi, str); }  // ��������� 3 ������

	for (i = 0; i < IT; i++) fi >> TQ[i] >> TC[i] >> RM[i];  // ������(���.), ��������(���.), �������/���

	cout << "TQ[i]    TC[i]    RM[i]" << endl;
	for (i = 0; i < IT; i++) { cout << "   " << TQ[i] << "        " << TC[i] << "      " << RM[i] << endl; }
	
    fi.close(); // ��������� ����
}