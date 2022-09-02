#include <iostream>
#include <math.h>
#include "X3X2C.h"

using namespace std;

//  пюявер мю опеднрбпюыемхе дкхрекэмнцн йнмрюйрмнцн
//  пюгпсьемхъ дкъ желемрнбюммшу гсавюршу йнкея
//          опхкнфемхе  8  цняр
//
//  бундмше оюпюлерпш :
//
//  SIGH - хяундмне пюявермне мюопъфемхе
//  SIGHM - люйяхлюкэмне мюопъфемхе
//  ROV - опхбедеммши пюдхся йпхбхгмш
//  HT - рнкыхмю сопнвмеммнцн якнъ
//  HV - рбепднярэ онбепумнярх б едхмхжюу бхйепяю
//  HKV - рбепднярэ яепджебхмш б едхмхжюу бхйепяю
//
//  бшундмше оюпюлерпш :
// (рнкэйн б яксвюе мецюпюмрхпнбюммни мюдефмнярх)   C
//   SGHKPU - сякнбмне дносяй.цксахм.KOHTAKTHOE мюопъфемхе C
//   SIGH - пюявермне KOHTAKTHOE сCTAкOCTHOE HAопъфемхе  C
//   SIGHM - MAKCхMAкэHOE KOHTAKTHOE HAопъфемхе

extern fstream f_1;    // ТЮИК ДКЪ ПЕГСКЭРЮРЮ    //***

void SGMHKC(float SIGH, float SIGHM, float WHT, float ROV, float HT, float HV, float HKV, int IG, int I)
{
    float SHKMIN[7] = { 1.2, 1.3, 1.4, 1.4, 1.5, 1.4, 1.4 };
    float SGMHKP = 0, SGMHKM = 0;

    //      HH - ЦКСАХМЮ pЮЯОНКНФЕМХЪ ГНМШ МЮХАНКЭЬХУ
    //           ЦКСАХММШУ ЙЮЯЮРЕКЭМШУ МЮОpЪФЕМХИ
    float HH = 1.52 * sqrt(WHT * ROV / 2.1E+5);

    //      HTEF - ЩТТЕЙРХБМЮЪ БЕКХВХМЮ СОpНВМЕММНЦН ЯКНЪ
    float HTEF = HH + .2;
    
    //      HEFF - ЩТТЕЙРХМЮЪ РБЕpДНЯРЭ СОpНВМЕММНЦН ЯКНЪ
    float HEFF = HV / ((HV / HKV - 1.) * pow((HTEF / HT), 2) + 1.);

    cout << "SGMHKC:      HV = " << HV << "    HKV = " << HKV << "    HTEF = " << HTEF << "    HT = " << HT << endl;

    if (HEFF < HKV) HEFF = HKV;

        //   СЯКНБХЕ МЮУНФДЕМХЪ ГНМШ БНГЛНФМНЦН ОНБpЕФДЕМХЪ

        if (HT < HH)  SGMHKP = 3.6 * HKV;                             // НОЮЯМЮЪ ГНМЮ РНКЭЙН Б ЯЕpДЖЕБХМЕ
        if (HT == HH) SGMHKP = (pow((HT / HH), 2) * .8 + 2.8) * HKV;  // НОЮЯМЮЪ ГНМЮ МЮ ЦpЮМХЖЕ СОpНВМЕММНЦН ЯКНЪ
        if (HT > HH)  SGMHKP = SGMHKP = 3.6 * HEFF;                   // НОЮЯМЮЪ ГНМЮ Б СОpНВМЕММНЛ ЯКНЕ

        float SGHKPU = SGMHKP / SHKMIN[IG-1];

        cout << "SGMHKC     SGHKPU = " << SGHKPU << "    SIGH = " << SIGH << "    I = " << I << endl;

        if (SGHKPU < SIGH && I == 1) {
            f_1 << "\n\n    цксахммюъ йнмрюйрмюъ бшмнякхбнярэ ьеярепмх ме цюпюмрхпнбюмю\n";
            f_1 << "\n      сякнбмне дносяй. цксахммне мюопъфемхе, лОЮ   SGHKPU " << SGHKPU;
            f_1 << "\n      хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ      SIGH " << SIGH;
            }
        if (SGHKPU < SIGH && I == 2) {
            f_1 << "\n\n    цксахммюъ йнмрюйрмюъ бшмнякхбнярэ йнкеяю ме цюпюмрхпнбюмю\n";
            f_1 << "\n      сякнбмне дносяй. цксахммне мюопъфемхе, лОЮ   SGHKPU " << SGHKPU;
            f_1 << "\n      хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ      SIGH " << SIGH;
        }
        //  pЮЯВЕР ОpХ ЛЮЙЯХЛЮКЭМНИ МЮЦpСГЙЕ
        float WHTMAX = WHT * pow((SIGHM / SIGH), 2);
        float HHM = 1.52 * sqrt(WHTMAX * ROV / 2.1E+5);
        float HTEFM = HHM + .2;
        float HEFFM = HV / ((HV / HKV - 1.) * pow((HTEFM / HT), 2) + 1.);
        if (HEFFM < HKV) HEFF = HKV;

        
        if (HT < HHM)  SGMHKM = 7.2 * HKV;        // НОЮЯМЮЪ ГНМЮ РНКЭЙН Б ЯЕpДЖЕБХМЕ
        if (HT == HHM) {                          // НОЮЯМЮЪ ГЮМЮ МЮ ЦpЮМХЖЕ СОpНВМЕММНЦН ЯКНЪ
            float C = 1.6E+6 * HKV * pow((HT / ROV), 2);
            float D = .42 * HKV;
            SGMHKM = X3X2C(D, C);
        }
        if (HT > HHM) SGMHKM = 7.2 * HEFFM;       // НОЮЯМЮЪ ГНМЮ Б СОpНВМЕММНЛ ЯКНЕ
           
        float SGHKMU = SGMHKM / SHKMIN[IG - 1];

        if (SGHKMU < SIGHM && I == 1) {
            f_1 << "\n\n    цксахммюъ йнмрюйрмюъ опнвмнярэ ьеярепмх";
            f_1 << "\n      опх люйяхлюкэмни мюцпсгйе ме цюпюмрхпнбюмю\n"; 
            f_1 << "\n      сякнбмне дносяй. цксахммне мюопъфемхе, лОЮ   SGHKMU " << SGHKMU;
            f_1 << "\n      хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ     SIGHM " << SIGHM;
        }
        if (SGHKMU < SIGHM && I == 2) {
            f_1 << "\n\n    цксахммюъ йнмрюйрмюъ опнвмнярэ йнкеяю";
            f_1 << "\n      опх люйяхлюкэмни мюцпсгйе ме цюпюмрхпнбюмю";
            f_1 << "\n      сякнбмне дносяй. цксахммне мюопъфемхе, лОЮ   SGHKMU " << SGHKMU;
            f_1 << "\n      хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ     SIGHM " << SIGHM;
        }
               
}
/*
C
C       SUBROUTINE   SGMHKC
C   пюявер мю опеднрбпюыемхе дкхрекэмнцн йнмрюйрмнцн
C   пюгпсьемхъ дкъ желемрнбюммшу гсавюршу йнкея
C           опхкнфемхе  8  цняр
C
C   бундмше оюпюлерпш:
C
C   SIGH  - хяундмне пюявермне мюопъфемхе
C   SIGHM - люйяхлюкэмне мюопъфемхе
C   ROV   - опхбедеммши пюдхся йпхбхгмш
C   HT    - рнкыхмю сопнвмеммнцн якнъ
C   HV    - рбепднярэ онбепумнярх б едхмхжюу бхйепяю
C   HKV   - рбепднярэ яепджебхмш б едхмхжюу бхйепяю
C
C   бшундмше оюпюлерпш:
C         (рнкэйн б яксвюе мецюпюмрхпнбюммни мюдефмнярх)   C
C    SGHKPU - сякнбмне дносяй.цксахм.KOHTAKTHOE мюопъфемхе C
C    SIGH   - пюявермне KOHTAKTHOE сCTAкOCTHOE HAопъфемхе  C
C    SIGHM  - MAKCхMAкэHOE KOHTAKTHOE HAопъфемхе
C
C
      SUBROUTINE SGMHKC(SIGH,SIGHM,WHT,ROV,HT,HV,HKV,IG,I)
      REAL SHKMIN(7)
       EXTERNAL X3X2C
C        SAVE
      DATA SHKMIN /1.2,1.3,1.4,1.4,1.5,2*1.4/
C      HH - ЦКСАХМЮ pЮЯОНКНФЕМХЪ ГНМШ МЮХАНКЭЬХУ
C           ЦКСАХММШУ ЙЮЯЮРЕКЭМШУ МЮОpЪФЕМХИ
      HH=1.52*SQRT(WHT*ROV/2.1E+5)

C      HTEF - ЩТТЕЙРХБМЮЪ БЕКХВХМЮ СОpНВМЕММНЦН ЯКНЪ
      HTEF=HH+.2
C      HEFF - ЩТТЕЙРХМЮЪ РБЕpДНЯРЭ СОpНВМЕММНЦН ЯКНЪ

       WRITE(7,7771) HV, HKV, HTEF, HT, HH
7771	format ('contau 7771', 5F10.2)

      HEFF=HV/((HV/HKV-1.)*(HTEF/HT)**2+1.)

       WRITE(7,7772)
7772	format ('contau 7772')

         IF(HEFF.LT.HKV) HEFF=HKV
C   СЯКНБХЕ МЮУНФДЕМХЪ ГНМШ БНГЛНФМНЦН ОНБpЕФДЕМХЪ
      IF (HT-HH) 10,20,30
C   НОЮЯМЮЪ ГНМЮ РНКЭЙН Б ЯЕpДЖЕБХМЕ
   10 SGMHKP=3.6*HKV
      GOTO 40
C   НОЮЯМЮЪ ГНМЮ МЮ ЦpЮМХЖЕ СОpНВМЕММНЦН ЯКНЪ
   20 SGMHKP=((HT/HH)**2*.8+2.8)*HKV
      GOTO 40
C   НОЮЯМЮЪ ГНМЮ Б СОpНВМЕММНЛ ЯКНЕ
   30 SGMHKP=3.6*HEFF
   40 CONTINUE
      SGHKPU=SGMHKP/SHKMIN(IG)
      IF(SGHKPU.LT.SIGH.AND.I.EQ.1) WRITE(1,101) SGHKPU,SIGH
  101 FORMAT(//'  цксахммюъ йнмрюйрмюъ бшмнякхбнярэ ьеярепмх ',
     *'ме цюпюмрхпнбюмю'/
     *'  сякнбмне дносяй.цксахммне мюопъфемхе, лОЮ  SGHKPU',F9.1/
     *'  хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ    SIGH',F9.1/)
      IF(SGHKPU.LT.SIGH.AND.I.EQ.2) WRITE(1,102) SGHKPU,SIGH
  102 FORMAT(//'  цксахммюъ йнмрюйрмюъ бшмнякхбнярэ йнкеяю ',
     *'ме цюпюмрхпнбюмю'/
     *'  сякнбмне дносяй.цксахммне мюопъфемхе, лОЮ  SGHKPU',F9.1/
     *'  хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ    SIGH',F9.1/)
C  pЮЯВЕР ОpХ ЛЮЙЯХЛЮКЭМНИ МЮЦpСГЙЕ
      WHTMAX=WHT*(SIGHM/SIGH)**2
      HHM=1.52*SQRT(WHTMAX*ROV/2.1E+5)
      HTEFM=HHM+.2
      HEFFM=HV/((HV/HKV-1.)*(HTEFM/HT)**2+1.)
         IF(HEFFM.LT.HKV) HEFF=HKV
      IF (HT-HHM) 50,60,70
C  НОЮЯМЮЪ ГНМЮ РНКЭЙН Б ЯЕpДЖЕБХМЕ
   50    SGMHKM=7.2*HKV
         GOTO 80
C  НОЮЯМЮЪ ГЮМЮ МЮ ЦpЮМХЖЕ СОpНВМЕММНЦН ЯКНЪ
   60    C=1.6E+6*HKV*(HT/ROV)**2
         D=.42*HKV
         SGMHKM=X3X2C(D,C)
         GOTO 80
C  НОЮЯМЮЪ ГНМЮ Б СОpНВМЕММНЛ ЯКНЕ
   70    SGMHKM=7.2*HEFFM
   80 SGHKMU=SGMHKM/SHKMIN(IG)
      IF(SGHKMU.LT.SIGHM.AND.I.EQ.1) WRITE(1,103) SGHKMU,SIGHM
  103 FORMAT(//'  цксахммюъ йнмрюйрмюъ опнвмнярэ ьеярепмх '/
     *'  опх люйяхлюкэмни мюцпсгйе ме цюпюмрхпнбюмю'/
     *'  сякнбмне дносяй.цксахммне мюопъфемхе, лОЮ   SGHKMU',F9.1/
     *'  хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ    SIGHM',F9.1/)
      IF(SGHKMU.LT.SIGHM.AND.I.EQ.2) WRITE(1,104) SGHKMU,SIGHM
  104 FORMAT(//'  цксахммюъ йнмрюйрмюъ опнвмнярэ йнкеяю '/
     *'  опх люйяхлюкэмни мюцпсгйе ме цюпюмрхпнбюмю'/
     *'  сякнбмне дносяй.цксахммне мюопъфемхе, лОЮ   SGHKMU',F9.1/
     *'  хяундмне пюяверм.йнмрюйрм.мюопъфемхе, лОЮ    SIGHM',F9.1/)
       RETURN
       END

*/
