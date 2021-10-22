void DXSP(float XS, float X[2])
{
	if (XS > 0) {
		X[0] = static_cast<float>(XS * 0.5);
		X[1] = static_cast<float>(XS * 0.5);
	}
	else {
		X[0] = XS;
		X[1] = 0;
	}
};
/*
C         SAVE
REAL  X(2)
IF(XS.LE.0.) GOTO1
X(1) = XS * .5
X(2) = XS * .5
RETURN
1  X(1) = XS
X(2) = 0.
RETURN
END
*/

void DXS1(float FX[2], float FXS)
{
	if (FXS > 1.5) {
		FX[0] = 0.75;
		FX[1] = static_cast<float>(FXS - 0.75);
	}
	else {
		FX[0] = 0.5;
		FX[1] = static_cast<float>(FXS - 0.5);
	}
};
/*
* DIMENSION FX(2)
C         SAVE
IF(FXS.GT.1.5) GOTO 1
FX(1) = .5
FX(2) = FXS - .5
GOTO 2
1 FX(1) = .75
FX(2) = FXS - .75
2 CONTINUE
RETURN
END
*/
void DXS(float FX[2], float FXS)
{
	if (FXS < 0) {
		FX[0] = 0;
		FX[1] = FXS;
	}
	else {
		if (FXS > 0.5) {
			FX[0] = 0.5;
			FX[1] = FXS - FX[0];
		}
		else {
			FX[0] = FXS;
			FX[1] = 0;
		}	
	}
};

/*
SUBROUTINE DXS(FX, FXS)
DIMENSION FX(2)
C       SAVE
IF(FXS.GE.0) GOTO1
FX(1) = 0
FX(2) = FXS
GOTO4
1 IF(FXS.GT.0.5) GOTO2
FX(1) = FXS
FX(2) = 0
GOTO4
2 FX(1) = 0.5
FX(2) = FXS - FX(1)
4 CONTINUE
RETURN
END
*/



