#include <iostream>
#include <math.h>

using namespace std;

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC//
//П / ПPOГPAMMA PAСЧETA КВАНТИЛЯ                      C
//            ИЗ ИНТЕГРАЛА ВЕРОЯТНОСТИ                      C
//                                                         C
//  BXOДHЫE ПAPAMETPЫ : C
//  Р - вероятность                                        C
//                                                         C
//  BЫXOДHЫЕ ПAPAMETPЫ : C
//  Х - квантиль нормального распределения                 C
//  D - плотность вероятности                              C
//                                                         C
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
void NDTRI(float P, float& X, float& D, float& ie)
{
	ie = 0.;
	if (P < 0) { ie = -1; return; }
	if (P == 0) { X = -.999999E+24; D = 0.; return; }
	if (P > 0) {
		if (P > 1) { ie = -1; return; }
		if (P == 1) { X = -.999999E+24; D = 0.; return; }
		if (P < 1) {
			D = P;
			if (D > 0.5) D = 1. - D;
			float T2 = log(1. / (D * D));
			float T = sqrt(T2);
			X = T - (2.515517 + .802853 * T + .010328 * T2) / (1. + 1.432788 * T + .189269 * T2 + .001308 * T * T2);
			if (P <= 0.5) 	X = -X;
			D = .3989423 * exp(-X * X / 2.);
			cout << "NDTRI:    X = " << X << "   D = " << D << "   P = " << P << "   ie = " << ie << endl;
			return;
		}
	}
}

/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C        П/ПPOГPAMMA PAСЧETA КВАНТИЛЯ                      C
C            ИЗ ИНТЕГРАЛА ВЕРОЯТНОСТИ                      C
C                                                          C
C   BXOДHЫE ПAPAMETPЫ:                                     C
C   Р - вероятность                                        C
C                                                          C
C   BЫXOДHЫЕ ПAPAMETPЫ:                                    C
C   Х - квантиль нормального распределения                 C
C   D - плотность вероятности                              C
C                                                          C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
	  SUBROUTINE NDTRI (P,X,D,IE)
	IE=0.
	IF(P) 1,4,2
	1   IE=-1
	  RETURN
	2	IF(P-1.) 7,6,1
	4   X=-.999999E+24
	5   D=0.
	  RETURN
	6   X=0.999999E+24
	GOTO 5
	7   D=P
	IF(D.GT.0.5) 	D=1.-D
	T2=ALOG(1./(D*D))
	T=SQRT(T2)
	X=T-(2.515517+.802853*T+.010328*T2)/
	 *    (1.+1.432788*T+.189269*T2+.001308*T*T2)
	IF(P.LE.0.5) 	X=-X
	D=.3989423*EXP(-X*X/2.)
	  WRITE(7,10)  X,D,P,IE
  10  FORMAT('  X  D  P  IE ',3F10.5,I5)
	  RETURN
	  END

*/