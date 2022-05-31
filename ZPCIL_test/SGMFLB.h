#include <iostream>
#include <math.h>
#include "NDTRI.h"

using namespace std;

// пересчет SF   от  PR = .99 (таблицы 12 - 15 ГОСТ)

float SGMFLB(int IG, float PR, float& SF, float& SFG, float HB, float HRCC)
{
    float NU = 0.18;
    float SFD99[20] = { 1.55, 1.55, 1.65, 1.7, 1.7, 1.55, 1.55, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7, 1.7 };
    float SGMB[20] = { 950., 820., 800., 780., 680., 1000., 750., -8., 580., 500., 460., -12., -13., 870., 730., 680., 580., 580., 480., 390. };
    float sgmflb = 0;
    float XP = 0, D = 0, ie = 0;

    
    SFG = SFD99[IG - 1];
    SF = SFG;

    if (PR > 0 && PR != 0.99) {
        NDTRI(PR, XP, D, ie);
        float SL = log10(SFG) * XP / 2.328;
        SF = pow(10, SL);
    }
    cout << "   SGMFLB:   PR = " << PR << "    XP = " << XP << "    SF = " << SF << "    SFG = " << SFG << endl;
    

    sgmflb = SGMB[IG - 1];
    if (IG == 8) sgmflb = 1.75 * HB;
    if (IG == 12 || IG == 13) sgmflb = 290. + 12. * HRCC;
    
    return sgmflb;
}
/*
c  PROGRAMMA   "SGMFLB" (pereschet SF   ot  PR = .99 )
        FUNCTION SGMFLB(IG,PR,SF,SFG,HB,HRCC)
C   tablici  12 - 15  GOST
    REAL NU
         DIMENSION SFD99(20),SGMB(20)
         SAVE
      DATA  NU/.18/
      DATA SFD99 /2*1.55,1.65,2*1.70,2*1.55,13*1.70/
      DATA SGMB /950.,820.,800.,780.,680.,
     * 1000.,750.,-8.,580.,500.,460.,-12.,
     * -13.,870.,730.,680.,2*580.,480.,390./
      SFG=SFD99(IG)
    SF=SFG
        IF(PR.GT.0.AND.PR.NE.0.99) THEN
        CALL NDTRI(PR,XP,D,IE)
    SL=ALOG10(SFG)*XP/2.328
    SF=10.**SL
       WRITE(7,622)  PR,XP, SF,SFG
  622  FORMAT('  in SGMFLB   PR , XP, SF  SFG ',4F7.3)
    END IF
      SGMFLB=SGMB(IG)
      IF(IG.EQ.8) SGMFLB=1.75*HB
      IF(IG.EQ.12.OR.IG.EQ.13) SGMFLB=290.+12.*HRCC
      RETURN
      END

*/
