#include <iostream>
#include <math.h>
#include "FUN.h"

using namespace std;

//     Квадратичная апроксимация

float KAPR(float X1, float Y1, float X2, float Y2, float X3, float Y3, float XK)
{
	float YK = 0;
	if (XK == 0 && YK == 0.) {
		cout << "KAPR:  ВНИМАНИЕ!    XK = 0     YK = 0" << endl;
		return 0;
	}
	float DLT = (X3 - X1) * (X2 * X2 - X1 * X1) - (X2 - X1) * (X3 * X3 - X1 * X1);
	float DLTA = (Y2 - Y1) * (X3 - X1) - (Y3 - Y1) * (X2 - X1);
	float DLTB = (X2 * X2 - X1 * X1) * (Y3 - Y1) - (X3 * X3 - X1 * X1) * (Y2 - Y1);
	float A = DLTA / DLT;
	float B = DLTB / DLT;
	float C = Y1 - X1 * X1 * A - X1 * B;
	//     Контрольная точка
	YK = FUN(A, B, C, XK);
	cout << "KAPR:      XK = " << XK <<"     YK = " << YK << endl;
	return YK;

}

/*
SUBROTINE KAPR(X1, Y1, X2, Y2, X3, Y3, XK, YK)
C     KBAdPATi~HAq ApPOKCiMAciq
C        SAVE
FUN(A, B, C, X) = A * X * *2 + B * X + C
IF(XK.EQ.0.AND.YK.EQ.0.) GOTO 555
DLT = (X3 - X1) * (X2 * X2 - X1 * X1) - (X2 - X1) * (X3 * X3 - X1 * X1)
DLTA = (Y2 - Y1) * (X3 - X1) - (Y3 - Y1) * (X2 - X1)
DLTB = (X2 * X2 - X1 * X1) * (Y3 - Y1) - (X3 * X3 - X1 * X1) * (Y2 - Y1)
A = DLTA / DLT
B = DLTB / DLT
C = Y1 - X1 * X1 * A - X1 * B
C     KOHTPOlxHAq TO~KA
YK = FUN(A, B, C, XK)
GOTO 777
555  print*, '   ВНИМАНИЕ  !!!   XK = 0. ,  YK = 0.'
777       RETURN
END
*/