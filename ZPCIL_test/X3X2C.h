#include <iostream>
#include <math.h>

using namespace std;

//    функция определения положительного корня
//    полинома вида   X**3 - D * X**2 - C

float X3X2C(float D, float C) 
{
	float x3x2c = 0;
	float X = 60., DEL = 20., R1 = -1.0, R2 = 0, PR = 1.0;	
	float EPS = 1.0;
	// 1 continue
	while (X > 50 && X < 500) {
		X = X + DEL;
		if (X * X * (X - D) > C) {    //   переход через корень, перемена знака
			R1 = 1;
			PR = 2;
		}
		else R1 = -1.;

		DEL = DEL * R1 * R2 / PR;

		if (abs(DEL) <= EPS)  return X;
		if (abs(DEL) > EPS) {
			R1 = R2;
		}
	}
	cout << "X3X2C: решения нет  X = " << X << endl;
	return 0;
}
/*
C     pOdpPOgPAMMA OpPEdElEHiq pOlOviTElxHOgO
C     KOPHq pOliHOMA BidA   X** 3 - D * X * *2 - C
FUNCTION X3X2C(D, C)
REAL D, C
REAL X, DEL, R1, R2, PR
C       SAVE
EPS = 1.0
X = 60.0
DEL = 20.0
R1 = -1.0
PR = 1.0
1 X = X + DEL
IF(X * X * (X - D) - C.GT.0) GOTO 3
2 R2 = -1
GOTO 4
C     pEPEXOd ~EPEz KOPEHx.pEPEMEHA zHAKA
3 R2 = 1
PR = 2
4 DEL = DEL * R1 * R2 / PR
IF(ABS(DEL) - EPS) 5, 5, 6
5 X3X2C = X
GOTO 7
6 R1 = R2
IF(X.GT.500.0.OR.X.LT.50.)
* WRITE(1, 101)
101 FORMAT(/ 'PE{EHiq HET' / )
GOTO 1
7 RETURN
END
*/
