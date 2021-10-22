// Синус, косинус, тангенс угла А
#include <math.h>

void SCT(double A, float &SNA, float &CSA, float &TGA)
{
	SNA = static_cast<float>(sin(A));
	CSA = static_cast<float>(cos(A));
	if (A == 0.) TGA = static_cast<float>(1.E-6);
	else TGA = SNA / CSA;	
}
