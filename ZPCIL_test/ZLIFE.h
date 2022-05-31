#include <iostream>
#include <math.h>

using namespace std;

float ZLIFE(int ITH, int ITH0, int ITH1, float SHLIM, float SHR[100], float SHRR, float NHLIM, float NC[100], float HB, float NHE)
{
    //	ITH - количество ступеней циклограммы
    //  ITH1 - количество ступеней, в которых  SHR > SHLIM
    float zlife = 0., ZN = 0.;
    NHE = 0.;
    float QH1 = 6;
    float QH2 = 20;
    //  I0 - начальная ступень суммирования усталости
    int I0 = 1 + ITH0;

    cout << "ZLIFE: I0 = " << I0 << "   ITH = " << ITH << endl;

    for (int i = I0; i < ITH; i++) {

        //  при  ITH1 - ITH0 = 0 все суммируемые напряжения меньше предела усталости
        //         print*, ' ZLIFE (bef IF..)***ITH1,ITH0 ', ITH1, ITH0
        
        if (ITH1 - ITH0 <= 0) { // ================ 5 ===============
            NHE = NHE + NC[i] * pow((SHR[i] / SHRR), QH2);
            if (NHE <= NHLIM)  ZN = pow((NHLIM / NHE), 0.167);
            if (NHE > NHLIM)   ZN = pow((NHLIM / NHE), 0.05);
            cout << "ZLIFE: === 5 ===    NHE = " << NHE << "   NHLIM = " << NHLIM << "   ZN = " << ZN << endl;
        }
        // при  I > ITH1  суммируемое напряжение меньше предела усталости
        if (ITH1 - ITH0 > 0) { // ================ 6 ===============
            if (i <= ITH1) {
                NHE = NHE + NC[i] * pow((SHR[i] / SHRR), QH1);
                ZN = pow((NHLIM / NHE), 0.167);
                cout << "ZLIFE: === 6 ===    NHE = " << NHE << "   NHLIM = " << NHLIM << "   ZN = " << ZN << endl;
            }
            else { // ================ 8 ===============
                float SS = pow((SHR[i] / SHLIM), (QH2 - QH1));
                NHE = NHE + NC[i] * pow((SHR[i] / SHRR), QH1) * SS;
                ZN = pow((NHLIM / NHE), 0.167);
                cout << "ZLIFE: === 8 ===    NHE = " << NHE << "   NHLIM = " << NHLIM << "   ZN = " << ZN << endl;
            }
        }     
    }
    zlife = ZN;
    return zlife;
}
/*
    INTEGER QH1, QH2
    REAL NHE, NC, NHLIM
    DIMENSION SHR(ITH), NC(ITH)
    C         SAVE
    C	ITH - количество ступеней циклограммы
    C     ITH1 - количество ступеней, в которых  SHR > SHLIM
    NHE = 0.
    QH1 = 6
    QH2 = 20
    C     I0 - начальная ступень суммирования усталости
    I0 = 1 + ITH0

    WRITE(7, 101) I0, ITH
    101	FORMAT('Zlife    I0, ITH:', 2I8)

    DO 10 I = I0, ITH
    C  при  ITH1 - ITH0 = 0 все суммируемые напряжения меньше предела усталости
    C         print*, ' ZLIFE (bef IF..)***ITH1,ITH0 ', ITH1, ITH0
    IF(ITH1 - ITH0) 5, 5, 6
    5 NHE = NHE + NC(I) * (SHR(I) / SHRR) * *QH2
    IF(NHE.LE.NHLIM)      ZN = (NHLIM / NHE) * *.167
    IF(NHE.GT.NHLIM)      ZN = (NHLIM / NHE) * *.05
    C         print*, ' ZLIFE (метка 5 )**NHE,NHLIM,ZN ', NHE, NHLIM, ZN
    GOTO 10
    C  при  I > ITH1  суммируемое напряжение меньше предела усталости
    6 IF(I.GT.ITH1) GOTO 8
    NHE = NHE + NC(I) * (SHR(I) / SHRR) * *QH1
    ZN = (NHLIM / NHE) * *.167
    C         print*, ' ZLIFE (метка 6 )**NHE,NHLIM,ZN ', NHE, NHLIM, ZN
    GOTO 10
    8 SS = (SHR(I) / SHLIM) * *(QH2 - QH1)
    NHE = NHE + NC(I) * (SHR(I) / SHRR) * *QH1 * SS
    ZN = (NHLIM / NHE) * *.167
    C         print*, ' ZLIFE (метка 8 )**NHE,NHLIM,ZN ', NHE, NHLIM, ZN
    10 CONTINUE
    ZLIFE = ZN
    C         print*, '   ZLIFE (end)****', ZLIFE
    RETURN
    END
    */

