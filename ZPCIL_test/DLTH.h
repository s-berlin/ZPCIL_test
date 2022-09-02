float DLTH(int IH, float BET, int IM)
//   IH = 1 - прирабатывается, 2 - не прирабатывается
//   IM = 0 - модификация отсутствует
{
	// ГОСТ таб 8 стр 22 
	float DLH[2][3] = { .006, .004, .002, .014,  .010,  .004 };
	
	int i = 1;
	if (BET == 0 && IM != 0) i = 2;
	if (BET != 0) i = 3;
	float DLTH = DLH[IH-1][i-1]; // ???
	return DLTH;
}

/*
FUNCTION DLTH(IH, BET, IM)
C     IH = 1 - pPiPAbATyBA`TCq, 2 - HE pPiPAbATyBA`TCq
C     IM = 0 - MOdifiKAciq OTCuTCTBuET
REAL DLH(2, 3)
C        SAVE
DATA DLH / .006, .014, .004, .010, .002, .004 /
J = 1
IF(BET.EQ.0.AND.IM.NE.0)J = 2
IF(BET.NE.0)J = 3
DLTH = DLH(IH, J)
RETURN
END
*/



