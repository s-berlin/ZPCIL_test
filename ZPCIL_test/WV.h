#include <math.h>
//     добавить 10, 11  степень точности
//     DLTR = DLTH или  DLTF задается на входе
//     изгиб DLTF : 0.006 - косозубые и шевронные передачи
//     0.011 и 0.016 - прямозубые с модификацией и без
//     предельные значения WHV и WFV; значения G0
float WV(float AW, float U, float AM, float V, int KCT, float DLTR, float GM)
{
    float WV = 0;
    float WVV[3][6] = { 160.,194.,250.,240.,310.,450.,380.,410.,590.,700.,880.,1050.,1200.,1500.,1800.,2200.,2800.,3300. };
    float G0[3][6] = { 38.,42.,48.,47.,53.,64.,56.,61.,73.,73.,82.,100.,100.,110.,135.,135.,150.,180. };
    int i = 1;
    if (AM > 3.55 && AM < 10.) i = 2;
    if (AM > 10.) i = 3;
    int j = KCT - 5;
    float WVHF = WVV[i][j];
    float GO = G0[i][j];
    WV = DLTR * GO * V * sqrt(AW / U);
    if (GM != 0.) WV = WV * sqrt((U * U + 1.) * GM / (U * U + GM));
    if (WV > WVHF) WV = WVHF;
    return WV;
}

/*
FUNCTION WV(AW, U, AM, V, KCT, DLTR, GM)
C     dObABiTx 10, 11  CTEpEHi TO~HOCTi
C     DLTR = DLTH ili DLTF zAdAETCq HA BXOdE
C     izgib DLTF : 0.006 - KOCOzubyE i{ EBPOHHyE pEPEdA~i
C     0.011 i 0.016 - pPqMOzubyE C MOdifiKAciEj i bEz
C     pPEdElxHyE zHA~EHiq WHV i WFV; zHA~EHiq G0
      DIMENSION WVV(3,6),G0(3,6)
C       SAVE
      DATA WVV / 160.,194.,250.,240.,310.,450.,380.,410.,590.,
     * 700.,880.,1050.,1200.,1500.,1800.,2200.,2800.,3300. /
      DATA G0 / 38.,42.,48.,47.,53.,64.,56.,61.,73.,
     * 73.,82.,100.,100.,110.,135.,135.,150.,180. /
      I = 1
C       print*,AW,U,V,KCT,DLTR,GM
      IF(AM.GT.3.55.AND.AM.LT.10.)I = 2
      IF(AM.GT.10.)I = 3
      J = KCT - 5
C       print*,I,J
      WVHF = WVV(I,J)
C       print*,WVHF
      GO = G0(I,J)
C       print*,GO
      WV = DLTR * GO * V * SQRT(AW / U)
C       print*,WV
      IF(GM.NE.0.) WV = WV * SQRT((U * U + 1.) * GM / (U * U + GM))
C       print*,WV
      IF(WV.GT.WVHF)WV = WVHF
C       print*,WV
      RETURN
      END

*/