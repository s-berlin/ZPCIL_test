#include <iostream>
#include <math.h>

using namespace std;

float ZV(float V, float HB)
{
	float zv = 1.;
	if (V <= 5.) return zv;
	zv = 0.85 * pow(V, 0.1);
	if (HB < 350.) return zv;
	zv = 0.925 * pow(V, 0.05);
	return zv;
}

/*
FUNCTION ZV(V, HB)
C        SAVE
ZV = 1.
IF(V.LE.5.)RETURN
ZV = .85 * (V * *0.1)
IF(HB.LT.350.) RETURN
ZV = .925 * (V * *0.05)
RETURN
END
*/
