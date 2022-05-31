#include <iostream>
#include <math.h>

using namespace std;

float FCBE(int IST, float BW)
{
	float ZN = pow(1.4, IST - 8);
	float fcbe = (2. * sqrt(BW) + 10.) * ZN;
	return fcbe;
}
/*
FUNCTION FCBE(IST, BW)
C         SAVE
ZN = 1.4 * *(IST - 8)
FCBE = (2. * SQRT(BW) + 10.) * ZN
RETURN
END
*/