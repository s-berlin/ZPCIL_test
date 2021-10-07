// Синус, косинус, тангенс угла А
#include <math.h>

void SCT(float A, float &SNA, float &CSA, float &TGA)
{
	SNA = sin(A);
	CSA = cos(A);
	if (A == 0.) TGA = 1.E-6;
	else TGA = SNA / CSA;	
}
