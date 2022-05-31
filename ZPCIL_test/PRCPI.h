#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ПЕЯСПЯ, ВЮЯНБ
extern float T1R, TMAX;     // ЛНЛЕМР МЮ БУНДЪЫЕЛ БЮКС, мЛ
extern float TQ[20], TC[20], RM[20];

extern fstream f_1;    // ТЮИК ДКЪ ПЕГСКЭРЮРЮ    //***

//   ОЕВЮРЭ pЕГСКЭРЮРНБ pЮЯВЕРЮ МЮ ОpНВМЯРЭ ОpХ ХГЦХАЕ           
//   ЖХКХМДpХВЕЯЙНИ ЩБНКЭБЕМРМНИ ОЕpЕДЮВХ

void  PRCPI (float PR, float PF1, float PF2, float PFM1, float PFM2,
             float SIGF1, float SIGF2, float SGFP1, float SGFP2, float SFF1, float SFF2, float SFMF1, float SFMF2,
             float SIGFM1, float SIGFM2, float SGFPM1, float SGFPM2, float SF1, float SF2,
             float VR, float TQ1, float TQ2, float SIGF01, float SIGF02,
             float YF1, float YF2, float YBET, float YEPS, float KFV1, float KFB1, float KFA1,
             float SGFLM1, float SGFLM2, float SGFG1, float SGFG2, float YN1, float YN2, float YA1, float YA2,
             float YDLT, float YR1, float YR2, float YX1, float YX2, float NFE1, float NFE2)
{
    float RTQ1 = 0, RTQ2 = 0;
    
    string IE1[2]{ " м * Л   ", "ЙЦЯ * ЛЛ" };
    string IE2[2]{ " MоЮ   ", "ЙЦЯ / ЙБ.ЛЛ" };
    
    int I1 = 0;
    if (IE == 2) I1 = 1;
    int I2 = 0;
    if (IE == 2) I2 = 1;

    if (IE == 2) {
        SIGF1 = SIGF1 / 9.81;
        SIGF2 = SIGF2 / 9.81;
        SGFP1 = SGFP1 / 9.81;
        SGFP2 = SGFP2 / 9.81;
        SIGFM1 = SIGFM1 / 9.81;
        SIGFM2 = SIGFM2 / 9.81;
        SGFPM1 = SGFPM1 / 9.81;
        SGFPM2 = SGFPM2 / 9.81;
        RTQ1 = TQ1 / 9.81;
        RTQ2 = TQ2 / 9.81;
        SIGF01 = SIGF01 / 9.81;
        SIGF02 = SIGF02 / 9.81;
        SGFLM1 = SGFLM1 / 9.81;
        SGFLM2 = SGFLM2 / 9.81;
        SGFG1 = SGFG1 / 9.81;
        SGFG2 = SGFG2 / 9.81;
    }
    else {
        RTQ1 = TQ1;
        RTQ2 = TQ2;
    }

    if (YN1 == 0 && YN2 == 0.) {
        f_1 << "\n\n        рюй йюй бяе NC(J,I) < 1000 жхйкнб \n";
        f_1 << "        пюявер мю хгцхамсч бшмнякхбнярэ ме опнхгбндхряъ \n";
    }
    if (YN1 == 0 && YN2 != 0.) {
        f_1 << "\n\n        рюй йюй дкъ ьеярепмх бяе NC(1,I) < 1000 жхйкнб, \n";
        f_1 << " рн дкъ мее пюявер мю хгцхамсч бшмнякхбнярэ ме опнхгбндхряъ \n";
    }
    if (YN1 != 0 && YN2 == 0.) {
        f_1 << "\n\n        рюй йюй дкъ йнкеяю бяе NC(2,I) < 1000 жхйкнб, \n";
        f_1 << " рн дкъ мецн пюявер мю хгцхамсч бшмнякхбнярэ ме опнхгбндхряъ \n";
    }
    if (YN1 != 0 || YN2 != 0.) {
        f_1 << "\n      бшмнякхбнярэ гсаэеб опх хгцхае \n";
        f_1 << "\n    пюявермше   мюопъфемхъ, " << IE2[I2] << "      SIGF     " << SIGF1 << "       " << SIGF2 << endl;   
    }
    if (PR > 0.) {
        f_1 << "\n    дносяйюелше мюопъфемхъ, " << IE2[I2] << "     SIGFP     " << SGFP1 << "       " << SGFP2 << endl;
    }
    else {
        f_1 << "\n пюявермше гюоюяш опнвмнярх, " << IE2[I2] << "       SFF     " << SFF1 << "       " << SFF2 << endl;
        f_1 << "\n пюявермше бепнърмнярх мепюгпсьемхъ, " << IE2[I2] << "  PF     " << PF1 << "       " << PF2 << endl;
    }
    f_1 << "\n опнвмнярэ опх хгцхае люйяхлюкэмшни мюцпсгйни, " << endl;
    f_1 << "\n люйяхлюкэмше мюопъфемхъ, " << IE2[I2] << "      SIGFM     " << SIGFM1 << "       " << SIGFM2 << endl;

    if (PR > 0.) {
        f_1 << "\n дносяйюелше  мюопъфемхъ, " << IE2[I2] << "      SGFPM     " << SGFPM1 << "       " << SGFPM2 << endl;
    }
    else {       
        f_1 << "\n пюявермше гюоюяш опнвмнярх, " << IE2[I2] << "       SFF     " << SFMF1 << "       " << SFMF2 << endl;
        f_1 << "\n пюявермше бепнърмнярх мепюгпсьемхъ, " << IE2[I2] << "  PF     " << PFM1 << "       " << PFM1 << endl;
    }
    if (IPR > 3) {
        f_1 << "\n пюявермши лнлемр мю бедсыел бюкс, " << IE1[I1] << "  T1F     " << RTQ1 << "       " << RTQ2 << endl;
    }
    if (IPR > 3 && L <= -1.) {
        f_1 << "\n нйпсфмюъ яйнпнярэ опх пюявермни мюцпсгйе,Л/Я  V " << VR << endl;
    }
    if (IPR > 3) {
        f_1 << "\n\n      оюпюлерпш пюявермнцн мюопъфемхъ опх хгцхае \n              йнщттхжхемрш: \n";
        f_1 << "\n  - тнплш гсаю                              YFS " << YF1 << "       " << YF2 << endl;
        f_1 << "\n  - сцкю мюйкнмю                            YBET " << YBET << endl;
        f_1 << "\n  - дкхмш йнмрюйрмшу кхмхи                  YEPS " << YEPS << endl;
    }
    if (IPR > 3 && L >= -1.) {
        f_1 << "\n  - дхмюлхвеяйни мюцпсгйх                   KFV  " << KFV1 << endl;
    }
    if (IPR > 3) {
        f_1 << "\n  - пюяопед.мюцпсгйх он дкхме йнмр.кхмхи    KFB  " << KFB1 << endl;
        f_1 << "\n  - пюяопедекемхъ мюцпсгйх лефдс гсаэълх    KFA  " << KFA1 << endl;
    }
    if (IPR > 3) {
        f_1 << "\n\n      оюпюлерпш нцпюмхвеммнцн опедекю бшмнякхбнярх \n     опедекш бшмнякхбнярх \n";
        f_1 << "\n аюгнбше, нрмскебше, " << IE2[I2] << "       SGFLB0     " << SGFLM1 << "       " << SGFLM2 << endl;
        f_1 << "\n опедекш онбпефдюелнярх, " << IE2[I2] << "       SGFG     " << SGFG1 << "       " << SGFG2 << endl;
    }
    if (IPR > 3 && PR > 0.) {
        f_1 << "\n йнщттхжхемрш аегноюямнярх                  SF " << SF1 << "       " << SF2 << endl;
    }
    if (IPR > 3) {
        f_1 << "\n йнщттхжхемрш днкцнбевмнярх                 YN " << YN1 << "       " << YN2 << endl;
        f_1 << "\n щйбхбюкемрмше вхякю жхйкнб, ЛКМ            NFE " << NFE1 << "       " << NFE2 << endl;
    }
    if (IPR > 3) {
        f_1 << "\n\n   йнщттхжхемрш: \n";
        f_1 << "\n - дбсярнпнммецн опхкнфемхъ мюцпсгйх        YA " << YA1 << "       " << YA2 << endl;
        f_1 << "\n - цпюдхемрю мюопъфемхи                     YDLT " << YDLT << endl;
        f_1 << "\n - ьепнунбюрнярх оепеундмшу онбепумняреи    YR " << YR1 << "       " << YR2 << endl;
        f_1 << "\n - пюглепю гсавюрнцн йнкеяю                 YX " << YX1 << "       " << YX1 << endl;
    }

        if (IPR >= 3)  f_1 << "\n\n    __________ \n";

}
/*
      SUBROUTINE PRCPI(PR,PF1,PF2,PFM1,PFM2,
     * SIGF1,SIGF2,SGFP1,SGFP2,SFF1,SFF2,SFMF1,SFMF2,
     * SIGFM1,SIGFM2,SGFPM1,SGFPM2,SF1,SF2,
     * VR,TQ1,TQ2,SIGF01,SIGF02,
     * YF1,YF2,YBET,YEPS,KFV1,KFB1,KFA1,
     * SGFLM1,SGFLM2,SGFG1,SGFG2,YN1,YN2,YA1,YA2,
     * YDLT,YR1,YR2,YX1,YX2,NFE1,NFE2)
      CHARACTER*8 IE1(2)
      CHARACTER*10 IE2(2)
C                                                               C
C   ОЕВЮРЭ pЕГСКЭРЮРНБ pЮЯВЕРЮ МЮ ОpНВМЯРЭ ОpХ ХГЦХАЕ           C
C   ЖХКХМДpХВЕЯЙНИ ЩБНКЭБЕМРМНИ ОЕpЕДЮВХ                        C
        REAL L,KFV1,KFB1,KFA1,NFE1,NFE2
        SAVE
      DATA IE1/' м*Л    ',' ЙЦЯ*Л  '/
      DATA IE2/' лоЮ      ',' ЙЦЯ/ЙБ.ЛЛ'/
      I1 =1
      IF(IE.EQ.2) I1 =2
      I2 =1
      IF(IE.EQ.2) I2 =2
         IF(IE.NE.2) GOTO 1109
      SIGF1 =SIGF1 /9.81
      SIGF2 =SIGF2 /9.81
      SGFP1 =SGFP1 /9.81
      SGFP2 =SGFP2 /9.81
      SIGFM1=SIGFM1/9.81
      SIGFM2=SIGFM2/9.81
      SGFPM1=SGFPM1/9.81
      SGFPM2=SGFPM2/9.81
      RTQ1   =TQ1   /9.81
      RTQ2   =TQ2   /9.81
      SIGF01=SIGF01/9.81
      SIGF02=SIGF02/9.81
      SGFLM1 =SGFLM1 /9.81
      SGFLM2 =SGFLM2 /9.81
      SGFG1 =SGFG1 /9.81
      SGFG2 =SGFG2 /9.81
        GOTO 1000
 1109 RTQ1   =TQ1
      RTQ2   =TQ2
 1000   WRITE(7,111)

  111  FORMAT(/18X,' PRCPI: оевюрэ пегскэрюрнб пюяверю мю хгцха'/)
       IF(YN1.NE.0.AND.YN2.NE.0.)    GOTO 1108
        IF(YN1.NE.0.OR.YN2.NE.0.)    GOTO 1107
        WRITE (1,1001)
 1001   FORMAT(/'  рюй йюй бяе NC(J,I) < 1000 жхйкнб'/
     *  '  пюявер мю хгцхамсч бшмнякхбнярэ ме опнхгбндхряъ'/)
        GOTO  1110
 1107   IF(YN1.EQ.0.AND.YN2.NE.0.) WRITE(1,1002)
 1002   FORMAT(/'  рюй йюй дкъ ьеярепмх бяе NC(1,I) < 1000 жхйкнб,'/
     *  '  рн дкъ мее пюявер мю хгцхамсч бшмнякхбнярэ ме опнхгбндхряъ'/)
        IF(YN2.EQ.0.AND.YN1.NE.0.) WRITE(1,1003)
 1003   FORMAT(/'  рюй йюй дкъ йнкеяю бяе  NC(2,I) < 1000  жхйкнб,'/
     *'  рн дкъ мецн пюявер мю хгцхамсч бшмнякхбнярэ ме опнхгбндхряъ'/)
 1108   WRITE(1,1111) IE2(I2),SIGF1,SIGF2
 1111  FORMAT(6X,'бшмнякхбнярэ гсаэеб опх хгцхае'//
     *' пюявермше   мюопъфемхъ,',A10,9X,'  SIGF',2F9.0)
        IF(PR.GT.0.) THEN
        WRITE(1,1112) IE2(I2),SGFP1,SGFP2
 1112  FORMAT(
     *' дносяйюелше мюопъфемхъ,',A10,9X,' SIGFP',2F9.0)
    ELSE
        WRITE(1,1113) SFF1,SFF2,PF1,PF2
 1113  FORMAT(
     *' пюявермше гюоюяш опнвмнярх ',16X,'SFF ',F10.2,F9.2/
     *' пюявермше бепнърмнярх мепюгпсьемхъ',9X,'PF     ',F8.5,F9.5)
    END IF
 1110   WRITE(1,1338) IE2(I2),SIGFM1,SIGFM2
 1338 FORMAT(/6X,
     *' опнвмнярэ опх хгцхае люйяхлюкэмшни мюцпсгйни'//
     *' люйяхлюкэмше мюопъфемхъ,',A10,9X,'SIGFM',2F9.0)
        IF(PR.GT.0.) THEN
        WRITE(1,1114) IE2(I2),SGFPM1,SGFPM2
 1114 FORMAT(
     *' дносяйюелше  мюопъфемхъ,',A10,9X,'SGFPM',2F9.0)
    ELSE
        WRITE(1,1113) SFMF1,SFMF2,PFM1,PFM2
    END IF
      IF(IPR.GT.3) WRITE(1,550) IE1(I1),RTQ1,RTQ2
  550 FORMAT(/
     *' пюявермши лнлемр мю бедсыел бюкс,',A8,'   T1F',2F9.1)
      IF(IPR.GT.3.AND.L.GE.-1.) WRITE(1,551) VR
  551 FORMAT(
     *' нйпсфмюъ яйнпнярэ опх пюявермни мюцпсгйе,Л/Я  V  ',F10.1)
      IF(IPR.GT.3) WRITE(1,560) YF1,YF2,YBET,YEPS
  560 FORMAT(/11X,
     * 'оюпюлерпш пюявермнцн мюопъфемхъ опх хгцхае'//
     * ' йнщттхжхемрш:'/
     * ' - тнплш гсаю                              YFS ',2F10.3/
     * ' - сцкю мюйкнмю                            YBET',F15.3/
     * ' - дкхмш йнмрюйрмшу кхмхи                  YEPS',F15.3)
      IF(IPR.GT.3.AND.L.GE.-1.) WRITE(1,561)  KFV1
  561 FORMAT(
     * ' - дхмюлхвеяйни мюцпсгйх                   KFV ',F15.3)
      IF(IPR.GT.3) WRITE(1,562) KFB1,KFA1
  562 FORMAT(
     * ' - пюяопед.мюцпсгйх он дкхме йнмр.кхмхи    KFB ',F15.3/
     * ' - пюяопедекемхъ мюцпсгйх лефдс гсаэълх    KFA ',F15.3)
      IF(IPR.GT.3)
     * WRITE(1,256) IE2(I2),SGFLM1,SGFLM2,IE2(I2),SGFG1,SGFG2
  256 FORMAT(/10X,
     *' оюпюлерпш нцпюмхвеммнцн опедекю бшмнякхбнярх'//
     *' опедекш бшмнякхбнярх '/
     *' аюгнбше, нрмскебше, ',A10,9X,'SGFLB0',2F9.0/
     *' опедекш онбпефдюелнярх,',A10,8X,'SGFG',2F9.0)
      IF(IPR.GT.3.AND.PR.GT.0.) WRITE(1,2560) SF1,SF2
 2560 FORMAT(
     *' йнщттхжхемрш аегноюямнярх                  SF',2F10.3)
      IF(IPR.GT.3) WRITE(1,2561) YN1,YN2,NFE1,NFE2
 2561 FORMAT(
     *' йнщттхжхемрш днкцнбевмнярх                 YN',2F10.3/
     *' щйбхбюкемрмше вхякю жхйкнб, ЛКМ            NFE',F9.2,F10.2)
      IF(IPR.GT.3)
     * WRITE(1,257) YA1,YA2,YDLT,YR1,YR2,YX1,YX2
  257 FORMAT(' йнщттхжхемрш:'/
     *' -дбсярнпнммецн опхкнфемхъ мюцпсгйх         YA',2F10.3/
     *' -цпюдхемрю мюопъфемхи                      YDLT',F12.3/
     *' -ьепнунбюрнярх оепеундмшу онбепумняреи     YR',2F10.3/
     *' -пюглепю гсавюрнцн йнкеяю                  YX',2F10.3)
        IF(IPR.GE.3) WRITE(1,300)
  300 FORMAT(' __________ ')
       RETURN
       END

*/
