#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];
extern float Z1, Z2, U;                        // числа зубьев шестерни и колеса

extern fstream f_1;    // файл для результата    //***

void RUZC(float TQ1, float TQH, float TQHP, float TQF, float TQFP, float AW, float ALTW, float BE, float KPD, float IE, float RMP, float TQEV, float EV, float EP, float PR)
{
    string IE1[2]{ " Н * м   ", "кгс * мм" };
    string IE2[2]{ " Н   ", "кгс" };

    float UI = U;

    int I1 = 0;
    if (IE == 2) I1 = 1;
    int I2 = 0;
    if (IE == 2) I2 = 1;
    //    pасчет усилий в зацеплении
    float DW1 = 2. * AW / (UI + 1.);
    if (TQEV < 0.) DW1 = 2. * AW / (UI - 1.);
        //   нагpузка для pасчета валов TQ1 = TQ(1) - наибольшая по циклограмме
        //   с эквивалентным числом часов работы или оборотов ведущего вала
        //   (при L < -1)  WHE(определяется в UPORTQ)
    float TQR = TQ1;
    float FT = 2000. * TQR / DW1;
    float FR = FT * tan(ALTW);
    float FA = FT * tan(BE);
        //    изгибающие моменты от осевой силы
    float TFA1 = FA * DW1 / 2000.;
    float TFA2 = TFA1 * UI;
        //    pасчетные и допускаемые моменты на выходном валу
    float TQ2R = TQ1 * UI * KPD;
    float TQ2HP = TQHP * UI;
    float TQ2FP = TQFP * UI;
    /*
    C  запись в file3 для передачи в расчет валов (пока только в Н*м и Н )
       WRITE(10,*) FT,FR,FA
       WRITE(10,*) TFA1,TFA2
       WRITE(10,*) RMP,TQR
       WRITE(10,*) TQ2R
    */

    if (IE == 2) {
        FT = FT / 9.81;
        FR = FR / 9.81;
        FA = FA / 9.81;
        TQR = TQR / 9.81;
        TFA1 = TFA1 / 9.81;
        TFA2 = TFA2 / 9.81;
        TQ2R = TQ2R / 9.81;
        TQ2HP = TQ2HP / 9.81;
        TQ2FP = TQ2FP / 9.81;
    }
    
    cout << "RUZC: TQ2HP = " << TQ2HP << "   TQ2FP = " << TQ2FP << "   ALTW = " << ALTW << "   UI = " << UI << "   KPD = " << KPD << endl;

    f_1 << "\n        ДАННЫЕ ДЛЯ РАСЧЕТА ВАЛОВ И ПОДШИПНИКОВ" << endl;
    f_1 << "\n                   УСИЛИЯ В ЗАЦЕПЛЕНИИ \n" << endl;

    f_1 << "ОКРУЖНОЕ УСИЛИЕ,   " << IE2[I2] << "                  FT " << setprecision(1) << fixed << setw(15) << FT << endl;
    f_1 << "РАДИАЛЬНОЕ УСИЛИЕ, " << IE2[I2] << "                  FR " << setw(15) << FR << endl;
    f_1 << "ОСЕВОЕ УСИЛИЕ,     " << IE2[I2] << "                  FX " << setw(15) << FA << endl;
  
    if (BE > 0.) {
        f_1 << "\n              ИЗГИБАЮЩИЕ МОМЕНТЫ ОТ ОСЕВОЙ СИЛЫ" << endl;
        f_1 << "\nНА ВЕДУЩЕМ КОЛЕСЕ, " << IE1[I1] << "            TFA1 " << setw(15) << TFA1 << endl;
        f_1 <<   "НА ВЕДОМОМ КОЛЕСЕ, " << IE1[I1] << "            TFA2 " << setw(15) << TFA2 << endl;
    }


   // RMP = -1  только для  IVP = 3  пока !!!!!!!!!
    if (RMP > -1.) {

        f_1 << "\n\nПРИВЕДЕННАЯ ЧАСТОТА ВРАЩЕНИЯ" << endl;
        f_1 << "ВЕДУЩЕГО ВАЛА, об/мин                    RMP " << setw(15) << RMP << endl;
        f_1 << "КРУТЯЩИЙ МОМЕНТ НА ВЕДУЩЕМ ВАЛУ СТУПЕНИ " << endl;
        f_1 << "НАИБОЛЬШИЙ ПО ЦИКЛОГРАММЕ (ЗАДАННЫЙ)," << IE1[I1] << "TQ1 " << setw(10) << TQR << endl;

        if (PR > 0.) {
            f_1 << "\n             КРУТЯЩИЕ МОМЕНТЫ НА ВЕДОМОМ ВАЛУ СТУПЕНИ" << endl;
            f_1 << "\nНАИБОЛЬШИЙ ПО ЦИКЛОГРАММЕ(ЗАДАННЫЙ), " << IE1[I1] << "TQ2 " << setw(10) << TQ2R << endl;

            f_1 << "\nДОПУСК. ПО КОНТАКТНОЙ ВЫНОСЛИВОСТИ, " << IE1[I1] << "T2HP " << setw(10) << TQ2HP << endl;
            float SH = TQ2HP / TQ2R;
            f_1 << "    ЗАПАС ПО КОНТАКТНОЙ ВЫНОСЛИВОСТИ           SH " << setprecision(2) << fixed << setw(10) << SH << endl;

            f_1 << "\nДОПУСК. ПО ИЗГИБНОЙ ВЫНОСЛИВОСТИ, " << IE1[I1] << "  T2FP " << setprecision(1) << fixed << setw(10) << TQ2FP << endl;
            float SF = TQ2FP / TQ2R;
            f_1 << "    ЗАПАС ПО ИЗГИБНОЙ ВЫНОСЛИВОСТИ             SF " << setprecision(2) << fixed << setw(10) << SF << endl;
        }
        else{ 
            f_1 << "КРУТЯЩИЙ МОМЕНТ НА ВЕДОМОМ ВАЛУ СТУПЕНИ " << endl;
            f_1 << "НАИБОЛЬШИЙ ПО ЦИКЛОГРАММЕ (ЗАДАННЫЙ), " << IE1[I1] << "  TQ2 " << setprecision(1) << fixed << setw(10) << TQ2R << endl;
        }
    }
    f_1 << "\n_____________" << endl;
     //   WRITE(1, 300)
     //   300 FORMAT(' __________ ')



}

/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C             пpогpамма "RUZC"                          C
C    pасчет усилий в зацеплении цилиндpической пеpедачи C
C    печать pезультатов pасчета                         C
C    PR=0. -ДОПУСК.МОМЕНТОВ НЕТ(вычисляются веpоятн.неpаз.C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      SUBROUTINE RUZC(L,TQ1,TQH,TQHP,TQF,TQFP,UI,AW,ALTW,BE,KPD,
     *IE,RMP,TQEV,EV,EP,PR)
      REAL   KPD,L
      CHARACTER*8 IE1(2)
      CHARACTER*4 IE2(2)
       SAVE
      DATA IE1/' Н*м    ',' кгс*м  '/
      DATA IE2/' Н  ',' кгс'/
      I1 =1
      IF(IE.EQ.2) I1 =2
      I2 =1
      IF(IE.EQ.2) I2 =2
C    pасчет усилий в зацеплении
      DW1=2.*AW/(UI+1.)
      IF(TQEV.LT.0.) DW1=2.*AW/(UI-1.)
C   нагpузка для pасчета валов TQ1=TQ(1) - наибольшая по циклограмме
C   с эквивалентным числом часов работы или оборотов ведущего вала
C   (при L<-1)  WHE (определяется в UPORTQ )
        TQR = TQ1
      FT=2000.*TQR/DW1
      FR=FT*TAN(ALTW)
      FA=FT*TAN(BE)
C    изгибающие моменты от осевой силы
      TFA1=FA*DW1/2000.
      TFA2=TFA1*UI
C    pасчетные и допускаемые моменты на выходном валу
       TQ2R=TQ1*UI*KPD
       TQ2HP=TQHP*UI
       TQ2FP=TQFP*UI

C  запись в file3 для передачи в расчет валов (пока только в Н*м и Н )
       WRITE(10,*) FT,FR,FA
       WRITE(10,*) TFA1,TFA2
       WRITE(10,*) RMP,TQR
       WRITE(10,*) TQ2R

      IF(IE.NE.2) GOTO 1
      FT   =FT    /9.81
      FR   =FR    /9.81
      FA   =FA    /9.81
      TQR  =TQR   /9.81
      TFA1 =TFA1  /9.81
      TFA2 =TFA2  /9.81
      TQ2R =TQ2R  /9.81
      TQ2HP=TQ2HP /9.81
      TQ2FP=TQ2FP /9.81
    1  WRITE(1,111)
  111 FORMAT(/11X,'ДАННЫЕ ДЛЯ РАСЧЕТА ВАЛОВ И ПОДШИПНИКОВ'//
     * 19X,'УСИЛИЯ В ЗАЦЕПЛЕНИИ'/)
        WRITE(1,113) IE2(I2),FT,IE2(I2),FR,IE2(I2),FA
  113  FORMAT(
     *' ОКРУЖНОЕ УСИЛИЕ,',A4,25X,'FT',2X,F12.1/
     *' РАДИАЛЬНОЕ УСИЛИЕ,',A4,23X,'FR',2X,F12.1/
     *' ОСЕВОЕ УСИЛИЕ,',A4,27X,'FX',2X,F12.1/)
        IF(BE.GT.0.)   WRITE(1,114) IE1(I1),TFA1,IE1(I1),TFA2
  114  FORMAT(/10X,
     *' ИЗГИБАЮЩИЕ МОМЕНТЫ ОТ ОСЕВОЙ СИЛЫ'//
     *' НА ВЕДУЩЕМ КОЛЕСЕ,',A8,19X,'TFA1',F12.1/
     *' НА ВЕДОМОМ КОЛЕСЕ,',A8,19X,'TFA2',F12.1/)

C RMP=-1  только для  IVP=3  пока !!!!!!!!!
    IF(RMP.GT.-1.) THEN
      WRITE(1,119) RMP,IE1(I1),TQR
  119 FORMAT(/
     *' ПРИВЕДЕННАЯ ЧАСТОТА ВРАЩЕНИЯ'/
     *' ВЕДУЩЕГО ВАЛА, об/мин                 ',7X,'RMP',F13.1/
     *' КРУТЯЩИЙ МОМЕНТ НА ВЕДУЩЕМ ВАЛУ СТУПЕНИ'/
     *' НАИБОЛЬШИЙ ПО ЦИКЛОГРАММЕ (ЗАДАННЫЙ),',A8,'TQ1',F13.1/)
      IF(PR.GT.0.) THEN
       WRITE(1,115)
  115 FORMAT(/12X,'КРУТЯЩИЕ МОМЕНТЫ НА ВЕДОМОМ ВАЛУ СТУПЕНИ'/)
      WRITE(1,116) IE1(I1),TQ2R
  116 FORMAT(
     *' НАИБОЛЬШИЙ ПО ЦИКЛОГРАММЕ (ЗАДАННЫЙ),',A8,'TQ2',F13.1/)
      SH = TQ2HP/TQ2R
      SF = TQ2FP/TQ2R
      WRITE(1,1160) IE1(I1),TQ2HP,SH,IE1(I1),TQ2FP,SF
 1160 FORMAT(
     *' ДОПУСК. ПО КОНТАКТНОЙ ВЫНОСЛИВОСТИ,',A8,'  T2HP',F12.1/
     *'   ЗАПАС ПО КОНТАКТНОЙ ВЫНОСЛИВОСТИ             SH',F12.2/
     *' ДОПУСК. ПО ИЗГИБНОЙ ВЫНОСЛИВОСТИ,',A8,'    T2FP',F12.1/
     *'     ЗАПАС ПО ИЗГИБНОЙ ВЫНОСЛИВОСТИ             SF',F12.2/)
    ELSE
      WRITE(1,1161) IE1(I1),TQ2R
 1161 FORMAT(
     *' КРУТЯЩИЙ МОМЕНТ НА ВЕДОМОМ ВАЛУ СТУПЕНИ'/
     *' НАИБОЛЬШИЙ ПО ЦИКЛОГРАММЕ (ЗАДАННЫЙ),',A8,'TQ2',F13.1/)
    END IF
    END IF
       WRITE(1,300)
  300 FORMAT(' __________ ')
      RETURN
      END

*/