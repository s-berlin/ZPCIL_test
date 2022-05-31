#include <math.h>
//     опpеделение KFBET по KHBET по CЭB и новому ГOCT

float AKFBTP(float AKHBT, float AM, float BET, float BW, float EPALF)
{
    float H = 2. * AM;
    if (BET == 0) H = H / EPALF;
    float BH = BW / H;
    float FN = pow(BH, 2) / (pow(BH, 2) + BH + 1.);
    float AKFBTP = pow(AKHBT, FN);
    if (AKFBTP < 1.) AKFBTP = 1.;
    return AKFBTP;
}
/*
      FUNCTION AKFBTP(AKHBT,AM,BET,BW,EPALF)
C     опpеделение KFBET по KHBET по CЭB и новому ГOCT
C     юяpхфхыхэшх KFBET яю KHBET яю C▌B ш эютюьє ├OCT
       SAVE
      H=2.*AM
      IF(BET.EQ.0) H=H/EPALF
      BH=BW/H
      FN=BH**2/(BH**2+BH+1.)
      AKFBTP=AKHBT**FN
       WRITE(7,70110) FN,AKHBT,AKFBTP
70110  FORMAT(' AKFBTP fn,akhbt,akfbtp  : ',3f9.3)
        IF(AKFBTP.LT.1.) AKFBTP=1.
      RETURN
      END

*/

