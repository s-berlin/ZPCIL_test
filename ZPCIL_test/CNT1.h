#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

extern fstream f_7;    // ТЮИК НРКЮДЙХ //***
extern float BE;

//  KOHTPOкэ KAвECTBA гюжеокемхъ

int CNT1(float X[2], float XMIN[2], float DL[2], float DP[2], float SNA[2], float EPALF, float EPBET, float EPGAM)
{
    int II = 0;
    for (int i = 0; i < 2; i++) {
        if (X[i] <= XMIN[i]) {
            f_1 << "\nйнщттхжхемр мюхлемэьецн ялеыемхъ   XMIN  " << XMIN[0] << "   " << XMIN[1];     
            II = 3;
            if (i == 0)  f_1 << "\nондпегюмхе гсаю ьеярепмх: X1<XMIN1";
            if (i == 1)  f_1 << "\nондпегюмхе гсаю йнкеяю: X1<XMIN1";                        
        }

        if (DP[i] <= DL[i]) {
            f_1 << "\nдхюлерп цпюмхвмшу рнвей опнтхкъ   DL  " << DL[0] << "   " << DL[1];
            f_1 << "\nдхюлерп мхфмху юйрхбмшу рнвей     DP  " << DP[0] << "   " << DP[1];
            II = 3;
            if (i == 0)  f_1 << "\nхмрептепемжхъ мю гсае ьеярепмх: DP1 < DL1";
            if (i == 1)  f_1 << "\nхмрептепемжхъ мю гсае йнкеяю: DP2 < DL2";

        }

        if (SNA[i] <= 0) {
            f_1 << "\nмнплюкэмюъ рнкыхмю гсаю он бепьхме";
            f_1 << "\n(б днкъу лндскъ)             SNA  " << SNA[0] << "   " << SNA[1];
            II = 3;
            if (i == 0)  f_1 << "\nгюнярпемхе гсаю ьеярепмх:   SNA1 < 0";
            if (i == 1)  f_1 << "\nгюнярпемхе гсаю йнкеяю:  SNA2 < 0";
        }
    }
    if (EPALF <= 1) {
            f_1 << "\nйнщт.рнпжнбнцн оепейпшрхъ лемэье  1";
            II = 3;
    

        f_7 << "CNT1:     EPGAM = " << EPGAM << endl;
        if (BE == 0 || EPGAM <= 1) {
            f_1 << "\nясллюпмши йнщт.оепейпшрхъ лемэье  1";
            II = 3;
        }
    }
    if (II == 3) f_1 << "\nпюявер опейпюыем";
    return II;
};
/*
C  KOHTPOкэ KAвECTBA гюжеокемхъ
      SUBROUTINE CNT1(II,X,XMIN,DL,DP,SNA,EPALF,EPBET,EPGAM,BET,NSR)
      DIMENSION X(2),XMIN(2),DL(2),DP(2),SNA(2)
   40 DO 41 I=1,2
      IF(X(I).GT.XMIN(I)) GOTO 42
      WRITE(1,201)XMIN
  201 FORMAT(4X,'йнщттхжхемр мюхлемэьецн ялеыемхъ   XMIN',4X,2F11.3)
C	print *,'===XMIN==',XMIN
      II=3
      IF(I.EQ.1) WRITE(1,220)
  220 FORMAT(4X,'ондпегюмхе гсаю ьеярепмх: X1<XMIN1')
C	print *,'===X1<XMIN=='
      IF(I.EQ.2) WRITE(1,221)
  221 FORMAT(4X,'ондпегюмхе гсаю йнкеяю: X2<XMIN2')
   42 IF(DP(I).GT.DL(I)) GOTO 43
      WRITE(1,202)DL,DP
  202 FORMAT(4X,'дхюлерп цпюмхвмшу рнвей опнтхкъ',4X,'DL',
     *6X,2F11.3/
     *       4X,'дхюлерп мхфмху юйрхбмшу рнвей',6X,'DP',6X,2F11.3)
      II=3
      IF(I.EQ.1) WRITE(1, 222)
  222 FORMAT(4X,'хмрептепемжхъ мю гсае ьеярепмх: DP1 < DL1')
      IF(I.EQ.2) WRITE(1, 223)
  223 FORMAT(4X,'хмрептепемжхъ мю гсае йнкеяю: DP2 < DL2')
   43 IF(SNA(I).GT.0) GOTO 41
      WRITE(1, 203)SNA
  203 FORMAT(4X,'мнплюкэмюъ рнкыхмю гсаю он бепьхме'/
     *4X,'(б днкъу лндскъ)',19X,'SNA',5X,2F11.3)
      II=3
      IF(I.EQ.1) WRITE(1, 224)
  224 FORMAT(4X,'гюнярпемхе гсаю ьеярепмх:   SNA1 < 0')
      IF(I.EQ.2) WRITE(1, 225)
  225 FORMAT (4X,'гюнярпемхе гсаю йнкеяю:  SNA2 < 0')
   41 CONTINUE
   49 IF(EPALF.GT.1.) GOTO 45
      WRITE(1, 227)
  227 FORMAT(4X,'йнщт.рнпжнбнцн оепейпшрхъ лемэье  1')
      II=3
      IF(BET.NE.0.AND.EPGAM.GT.1) GOTO 45
      WRITE(1, 228)
  228 FORMAT(4X,'ясллюпмши йнщт.оепейпшрхъ лемэье  1')
      II=3
   45 CONTINUE
C  45 IF(II.EQ.3) WRITE(1,230)
  230 FORMAT(1X,/30X,'пюявер опейпюыем'/)
      RETURN

*/
