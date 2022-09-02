#include <iostream>
#include <math.h>

using namespace std;

//     удельная ноpмальная жесткость паpы зубьев, N / MM.MKM

extern float ZVE1, ZVE2, X1, X2, X[2];

float CE()
{

	float X11 = X[0] * X[0];
	float X22 = X[1] * X[1];
	float ce = .05139 + .1425 / ZVE1 + .1860 / ZVE2 - .01 * X[0] - .1027 * X[0] / ZVE1 + .00455 * X[1] + .3762 * X[1] / ZVE2 + .00734 * X11 - .00054 * X22;
	ce = 1. / ce;
	
	cout << "   CE:    ZVE1, ZVE2, X1, X2, X[0], X[1], X11, X22 = " << ZVE1 << "  " << ZVE2 << "  " << X1 << "  " <<  X2 << "  " << X[0] << "  " << X[1] << "  " << X11 << "  " << X22 << "     ce = " << ce << endl;

	return ce;
}
/*
FUNCTION CE(ZVE1, ZVE2, X1, X2)
C     удельная ноpмальная жесткость
C     паpы зубьев, N / MM.MKM

C         SAVE
C      print*, '   *CE***'
X11 = X1 * X1
X22 = X2 * X2
C      print*, '   *CE***', X11, X22
CE = .05139 + .1425 / ZVE1 + .1860 / ZVE2 - .01 * X1 - .1027 * X1 / ZVE1
* +.00455 * X2 + .3762 * X2 / ZVE2 + .00734 * X11 - .00054 * X22
C      print*, '   *CE***', CE
CE = 1. / CE
C      print*, '   *CE***', CE
RETURN
END
*/
