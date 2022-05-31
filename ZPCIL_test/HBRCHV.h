// Пересчет твердости
void HBRCHV(float H, float &HRC, float &HB, float &HV) {
// C     MODE = 1 - задано HRC, 2 - задано HB, 3 - HV
	int MODE = 2;
	if (H < 100) MODE = 1;
	if (H > 400) MODE = 3;

	float H2 = H * H;
	float H3 = H2 * H;
	switch (MODE) {
	case 1:
		HRC = H;
		HB = .118508 * H2 + .440352 * H + 149.565;
		HV = 5.11658E-3 * H3 - .333507 * H2 + 13.8183 * H + 19.1313;
		break;
	case 2:
		HB = H;
		HRC = 3.04464E-7 * H3 - 4.90661E-4 * H2 + .335311 * H - 30.7401;
		HV = 3.34122E-6 * H3 - 2.84455E-3 * H2 + 1.92568 * H - 107.371;
		break;
	case 3:
		HV = H;
		HRC = 1.26065E-7 * H3 - 2.87764E-4 * H2 + .250318 * H - 19.4517;
		HB = -3.45636E-8 * H3 - 4.11717E-4 * H2 + 1.15007 * H - 11.2462;
	}
	return;
}
/*
SUBROUTINE HBRCHV(H, HRC, HB, HV)
C     MODE = 1 - zAdAHO HRC, 2 - zAdAHO HB, 3 - HV
C        SAVE
MODE = 2
IF(H.LT.100.) MODE = 1
IF(H.GT.400.) MODE = 3
H2 = H * H
H3 = H2 * H
GO TO(10, 20, 30), MODE
10 HRC = H
HB = .118508 * H2 + .440352 * H + 149.565
HV = 5.11658E-3 * H3 - .333507 * H2 + 13.8183 * H + 19.1313
GO TO 40
20 HB = H
HRC = 3.04464E-7 * H3 - 4.90661E-4 * H2 + .335311 * H - 30.7401
HV = 3.34122E-6 * H3 - 2.84455E-3 * H2 + 1.92568 * H - 107.371
GO TO 40
30 HV = H
HRC = 1.26065E-7 * H3 - 2.87764E-4 * H2 + .250318 * H - 19.4517
HB = -3.45636E-8 * H3 - 4.11717E-4 * H2 + 1.15007 * H - 11.2462
40 RETURN
END

*/

