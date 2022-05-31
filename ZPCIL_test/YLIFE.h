#include <iostream>
#include <math.h>

using namespace std;

float YLIFE(int ITF, int ITF0, int ITF1, float SFLIM, float SFR[100], float SFRR, float NC[100], int IMF, float NFE)
{
    cout << "YLIFE:   ITF = " << ITF << "   ITF0 = " << ITF0 << "   ITF1 = " << ITF1 << "   SFLIM = " << SFLIM << "   SFRR = " << SFRR << "   IMF = " << IMF << "   NFE = " << NFE << endl;
    for (int i = 0; i < ITF; i++) cout << "    NC[" << i << "] = " << NC[i] << endl;
    for (int i = 0; i < ITF; i++) cout << "   SFR[" << i << "] = " << SFR[i] << endl;

    NFE = 0.;
    float NFLIM = 4.;
    float QF1 = 6.;
    if (IMF == 1) QF1 = 9.;
    float QF2 = 40.;
    int I0 = 1 + ITF0;

    cout << "YLIFE:   I0 = " << I0 << endl;

    for (int i = I0 - 1; i < ITF; i++) {
        if (ITF1 <= ITF0) NFE = NFE + NC[i] * pow((SFR[i] / SFRR), QF2);
        if (ITF1 > ITF0 && i <= ITF1) NFE = NFE + NC[i] * pow((SFR[i] / SFRR), QF1);
        if (ITF1 > ITF0 && i > ITF1) {
            float KS = pow((SFLIM / SFRR), QF2);
            NFE = NFE + NC[i] * pow((SFR[i] / SFRR), QF1) * KS;
        }
    }
    float YN = 0;
    if (NFE <= NFLIM && IMF == 0)   YN = pow((NFLIM / NFE), 0.167);
    if (NFE <= NFLIM && IMF == 1)   YN = pow((NFLIM / NFE), 0.111);
    if (NFE > NFLIM)   YN = pow((NFLIM / NFE), 0.05);
    if (IMF == 0 && YN > 4.0) YN = 4.0;
    if (IMF == 1 && YN > 2.5) YN = 2.5;
    float ylife = YN;

    return ylife; 
}

/*
        FUNCTION YLIFE(ITF,ITF0,ITF1,SFLIM,SFR,SFRR,
     *  NC,IMF,NFE)
      IMPLICIT REAL(K-N)
      DIMENSION SFR(ITF),NC(ITF)
       SAVE
C     ITF1- количество ступеней, в к-рых  SHR < SHLIM
C
      WRITE(7,6223) ITF,ITF0,ITF1,SFLIM,SFRR,
     *   IMF,NFE,NC
 6223 FORMAT('-ylife-ITF,ITF0,ITF1,SFLIM,SFRR '/
     *  1X,3I4,2F10.3/
     * ' ---IMF,NFE ',I5,F10.5/
     * ' ---NC  ',(5F10.3))
    WRITE(7,6226) SFR
 6226 FORMAT('-ILIFE---SFR ',(5F10.3))
      NFE=0.
      NFLIM=4.
      QF1=6.
      IF(IMF.EQ.1) QF1=9.
      QF2=40.
      I0=1+ITF0
      WRITE(7,6224) I0,ITF
 6224 FORMAT('-ylife-I0,ITF',2I4)
          DO 10 I=I0,ITF
      IF(ITF1-ITF0) 5,5,6
    5 NFE=NFE+NC(I)*(SFR(I)/SFRR)**QF2
      GOTO 10
    6 IF(I.GT.ITF1) GOTO 8
      NFE=NFE+NC(I)*(SFR(I)/SFRR)**QF1
      GOTO 10
    8 KS=(SFLIM/SFRR)**QF2
      NFE=NFE+NC(I)*(SFR(I)/SFRR)**QF1*KS
   10 CONTINUE
      WRITE(7,6222) NFE,I0,ITF,ITF0,ITF1
 6222 FORMAT('-ylife-NFE,I0,ITF,ITF0,ITF1 '/
     *  4X,F11.5,4I4)
      IF(NFE.LE.NFLIM.AND.IMF.EQ.0)   YN=(NFLIM/NFE)**.167
      IF(NFE.LE.NFLIM.AND.IMF.EQ.1)   YN=(NFLIM/NFE)**.111
      IF(NFE.GT.NFLIM)   YN=(NFLIM/NFE)**.05
      IF(IMF.EQ.0.AND.YN.GT.4.0) YN=4.0
      IF(IMF.EQ.1.AND.YN.GT.2.5) YN=2.5
      YLIFE=YN
      RETURN
      END
*/