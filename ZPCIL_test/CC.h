#include <iostream>
#include <math.h>

using namespace std;

float CC(float Z, float X, float HM)
{
    float cc;

    float PSI = log10(Z);
    float C = (9.671 - 7.521 * X + 1.626 * X * X - .041 * X * X * X - 3.878 * PSI + 4.662 * X * PSI - .457 * X * X * PSI
        + 1.557 * PSI * PSI - .734 * X * PSI * PSI - .224 * PSI * PSI * PSI - 3.44 * HM + 2.674 * X * HM - .515 * X * X * HM
        - 2.18 * PSI * HM - .737 * X * PSI * HM + .338 * PSI * PSI * HM + 2.042 * HM * HM
        - .298 * X * HM * HM + .529 * PSI * HM * HM + .573 * HM * HM * HM) * 0.01;

    cc = 1. / C;
    return cc;
}
/*
FUNCTION CC(Z, X, HM)
C Удельная номальная жесткость зуба зубчатого колеса

C       SAVE
Y2(Y) = Y * Y
Y3(Y) = Y * *3
PSI = ALOG10(Z)
C = (9.671 - 7.521 * X + 1.626 * Y2(X) - .041 * Y3(X)
    * -3.878 * PSI + 4.662 * X * PSI - .457 * Y2(X) * PSI
    * +1.557 * Y2(PSI) - .734 * X * Y2(PSI) - .224 * Y3(PSI)
    * -3.44 * HM + 2.674 * X * HM - .515 * Y2(X) * HM
    * -2.18 * PSI * HM - .737 * X * PSI * HM
    * +.338 * Y2(PSI) * HM + 2.042 * Y2(HM)
    * -.298 * X * Y2(HM) + .529 * PSI * Y2(HM) + .573 * Y3(HM)) * 0.01
    CC = 1. / C
    RETURN
    END
*/