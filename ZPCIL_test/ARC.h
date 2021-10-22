// ???
#include <math.h>
//#include <iostream>

using namespace std;

void ARC(float INV, float &A) {

    double AO = .3490658;
    double A_d;
    double C2 = 0;
    double C = 1;

    cout << "\nARC: sizeof(Ñ) = " << sizeof(C) << endl;

	while (abs(C) > 0.00001) {
        cout << "\nARC: C = " << C << endl;
		C = cos(AO);
        C2 = C * C;
		A_d = (sin(AO) / C - AO - INV);
		A_d = (AO - A_d * C2 / (1. - C2));
		C = A_d - AO;
		AO = A_d;
	}
    A = static_cast<float>(A_d);
};
/*
      SUBROUTINE ARC(INV,A)
      REAL INV
        SAVE
      AO= .3490658
    1 C=COS(AO)
      C2=C*C
      A=SIN(AO)/C-AO-INV
      A=AO-A*C2/(1.-C2)
      C=A-AO
      IF(ABS(C)-0.000001)2,2,3
    3 AO=A
      GOTO 1
    2 RETURN
      END
*/

