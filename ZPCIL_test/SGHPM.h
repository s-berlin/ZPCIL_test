#include <iostream>
#include <math.h>

using namespace std;

float SGHPM(int KM, float HB, float HRC, float HV)
{
	float sghpm = 0;
	if ((KM >= 1 && KM <= 7) || (KM >= 14 && KM <= 17)) {
		sghpm = 44. * HRC;
		return sghpm;
	}
	if ((KM >= 8 && KM <= 11) || (KM >= 18 && KM <= 19)) {
		float SGMT = 2.5 * HB;
		float sghpm = 2.8 * SGMT;
		return sghpm;
	}
	if ((KM >= 12 && KM <= 13) || (KM >= 18 && KM <= 19)) {
		sghpm = 3. * HV;
		return sghpm;
	}
}
/*
C        SAVE
GO TO(1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 1, 1, 1, 1, 2, 2), KM
1   SGHPM = 44. * HRC
GO TO 7
2   CONTINUE
SGMT = 2.5 * HB
SGHPM = 2.8 * SGMT
GO TO 7
3   SGHPM = 3. * HV
7   RETURN
END
*/

