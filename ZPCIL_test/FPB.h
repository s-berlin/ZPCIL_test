#include <math.h>

float FPB(int IST, float AM, float D)
{
	float ZN = pow(1.4, IST - 8);
	float fpb = (1.25 * AM + .31 * sqrt(D) + 16.) * .94 * ZN;
	return fpb;
}
/*
FUNCTION FPB(IST, AM, D)
C         SAVE
C      print*, '  *FPB***'
ZN = 1.4 * *(IST - 8)
C      print*, '  *FPB***', ZN
FPB = (1.25 * AM + .31 * SQRT(D) + 16.) * .94 * ZN
C      print*, '  *FPB***', FPB
RETURN
END
*/
