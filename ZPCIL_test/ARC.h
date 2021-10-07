// ???
#include <math.h>

using namespace std;

void ARC(float INV, float &A) {
    cout << "\nARC" << endl;
    float AO = .3490658;
    float C = 1;
	while (abs(C) > 0.00001) {
        cout << "\nARC: C = " << C << endl;
		C = cos(AO);
        float C2 = C * C;
		A = sin(AO) / C - AO - INV;
		A = AO - A * C2 / (1. - C2);
		C = A - AO;
		AO = A;
	}
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

