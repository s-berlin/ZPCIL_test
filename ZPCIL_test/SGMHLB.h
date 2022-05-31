
float SGMHLB(int KM, float HRC, float HB)
{
//	float SHD[19] = { 7 * 1.2, 12 * 1.1 };
//  KM - KOÄ MATEPÈAËA  CMOTPÈ ÏO ÔAÉËÓ : KMC.SPR

    float SGMHLB = 0;

    if (KM >= 1 && KM <= 7)   SGMHLB = 23. * HRC;
    if (KM == 8)              SGMHLB = 2.0 * HB + 70.;
    if (KM >= 9 && KM <= 11)  SGMHLB = 18. * HRC + 150.;
    if (KM >= 12 && KM <= 13) SGMHLB = 1050.;
    if (KM >= 14 && KM <= 19) SGMHLB = 17. * HRC + 200.;
    return SGMHLB;
}
/*
FUNCTION SGMHLB(KM, HRC, HB)
C     DIMENSION SHD(19)
C     DATA SHD / 7 * 1.2, 12 * 1.1 /
C     KM - KOÄ MATEPÈAËA  CMOTPÈ ÏO ÔAÉËÓ : KMC.SPR
C        SAVE
GO TO(4, 4, 4, 4, 4, 4, 4, 1, 2, 2, 2, 5, 5, 3, 3, 3, 3, 3, 3) KM
4  SGMHLB = 23. * HRC
GO TO 10
1  SGMHLB = 2.0 * HB + 70.
GO TO 10
2  SGMHLB = 18. * HRC + 150.
GO TO 10
3  SGMHLB = 17. * HRC + 200.
GO TO 10
5  SGMHLB = 1050.
C 10  SH = SHD(KM)
10  RETURN
END*/

