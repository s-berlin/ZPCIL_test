#include <iostream>
#include <math.h>

using namespace std;
//============================================================
//        � / �PO�PAMMA PA��ETA ��������� �����������         
//                                                          
//  BXO�H�E �APAMETP� : 
//  � - �������� ����������� �������������                 
//                                                         
//  B�XO�H�� �APAMETP� : 
//  � - �����������                                        
//  D - ��������� �����������                              
//                                                         
//============================================================
float NDTR(float X) 
{
	float AX = abs(X);
	float T = 1. / (1. + .2316419 * AX);
	float D = .3989423 * pow(2.7182818, -X * X / 2.);
	cout << "NDTR:      AX = " << AX << "    T = " << T << "    D = " << D << endl;
	float P = 1. - D * T * ((((1.330274 * T - 1.821256) * T + 1.781478) * T * -.3565638) * T + .3193815);
	if (X < 0.) P = 1. - P;
	
	cout << "NDTR:      X = " << X << "    P = " << P << "    D = " << D << endl;
	
	return P;
}

/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C        �/�PO�PAMMA PA��ETA ��������� �����������         C
C                                                          C
C   BXO�H�E �APAMETP�:                                     C
C   � - �������� ����������� �������������                 C
C                                                          C
C   B�XO�H�� �APAMETP�:                                    C
C   � - �����������                                        C
C   D - ��������� �����������                              C
C                                                          C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
	  SUBROUTINE NDTR (X,P,D)
	AX=ABS(X)
	T=1./(1.+.2316419*AX)
	D=.3989423*EXP(-X*X/2.)
	P=1.-D*T*((((1.330274*T-1.821256)*T+1.781478)*T
	 *    -.3565638)*T+.3193815)
	IF(X.LT.0.) P=1.-P
C       print *,'   X  D    P',X,D,P
	  RETURN
	  END

*/