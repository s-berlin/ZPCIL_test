#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//#include <fstream>
//#include <corecrt.h>
#include "CILEV.h"
#include "DRM.h"
#include "VYVDR.h"
//#include "DSR.h"
//#include "VYVODS.h"
//#include "CILEV.h"

using namespace std;

//========== Переменные по редуктору
char IR[20] = {};  // идентификатор расчета 
int IT = 0, IRV = 0, IPR = 6, IE = 1, ISR = 1, IN = 0;
float L = 0, WH = 0;      // ресурс, часов
float T1R = 0, TMAX = 0;     // момент на входящем валу, Нм
float TQ[20] = {}, TC[20] = {}, RM[20] = {};

fstream f_1;    // файл для результата    //***

//========== Переменные по ступени
int IVP = 0;                         // тип ступени
float Z1 = 0, Z2 = 0;                // числа зубьев шестерни и колеса
float MN = 0, BE = 0, X1, X2;        // модуль, угол наклона, коэффициенты смещения
int flaw;
float AW, B1, B2;                    // межосевое расстояние ширины шестерни и колеса
float AL, HA, HL, CZV;               // угол профиля, коэффициенты: высоты головки, граничной высоты, радиального зазора  
int IST1, IST2, IST3, IST4, IST5;    // степени точности по нормам: кинематики, плавности, контакта; вид сопряжения, вид допуска на боковой зазор
int IMD, IKG;                        // коэф. наличия массивных деталей, номер схемы по упрощенному методу
float SHLM1, SHPM1, SFLB1, SFPM1;    // шестерня: предел конт. выносливости, допуск. конт. напряжение при макс. нагрузке, баз. предел выносл-и при изгибе, предел. баз. напряжение изгиба при макс. нагрузке 
float SHLM2, SHPM2, SFLB2, SFPM2;    // колесо:   - " -    - " -    - " -    - " -
int IG1, IG2;                        // группы материала шестерни и колеса
float H1, HK1, HT1, SHER1, YZ1;      // шестерня: твердость поверхности, твердость сердцевины, толщина упрочненного слоя, шероховатость, коэф. способа получения заготовки
float YT1, YR1, SHV1;                // шестерня: технологический коэффициент, шероховатость переходной поверхности, коэф. запаса прочности
float H2, HK2, HT2, SHER2, YZ2;      // колесо: твердость поверхности, твердость сердцевины, толщина упрочненного слоя, шероховатость, коэф. способа получения заготовки
float YT2, YR2, SHV2;                // колесо: технологический коэффициент, шероховатость переходной поверхности, коэф. запаса прочности
int IMF1, IMF2, IVR;                 // признаки шлифования переходной поверхности шестерни и колеса, Признак задания коэф-та запаса по контактной выносливости
float CZ1, CZ2, KSP, KPD, PR;        // числа зацеплений за оборот шестерни и колеса, коэф. силового потока, КПД, вероятность неразрушения по изгибной выносливости
float LO = 0, S1 = 0, FKE = 0, GM;   // расстояние между опорами, расстояние от опоры со стороны подвода момента до центра шестерни, ?, ?
int IQ = 1, IP = 0, IZ1 = 0, IG = 0; // тип приложения момента, тип подшипника, ?, ?
float GRM = 0;
int SEC = 0;

int main()
{

    DRM();
	VYVDR();

//	CALL UPORTQ(IT, TQ, TC, RM, IRV, IPR, WH, L,
//		*IT1, TQ1, TC1, RM1, IT2, TQ2, TC2, RM2, TN, EV, IS)

//	DSR();
//	VYVODS();

//	----------Расчет цилиндрической передачи внешнего зацепления
// 
	IVP = 0;
	int JJ = 0;
	if (IVP == 0) CILEV();
//		IF(IVP.EQ.0)  CALL CILEV(JJ, IR, IVP, IS, ISR, L, WH, TMAX,
//			*IRV, IPR, IE, N1R, TNZ,
//			*IT1, TQ1, TC1, RM1, IN, IT, TQ, TC, RM, TN)

	return(0);
}
/*
		INTERFACE TO SUBROUTINE tim[C](kod)
		INTEGER kod [REFERENCE]
		END
	  PROGRAM ZPCIL
C  головная пpогpамма pасчет зубчатых пеpедач pедуктоpа
C
C
	PARAMETER(ITC=20,INC=10,ISRC=20)
	  REAL L,N1R
	  CHARACTER*20  FILNAM
	  CHARACTER*16 IR    ! идентификатор расчета
	  CHARACTER*30 STR
	  REAL  TQ(ITC*INC),TC(ITC*INC),RM(ITC*INC)
C ,UI(ISRC),KPDI(ISRC)
	  REAL TQ1(100),TC1(100),RM1(100)
	  REAL TQ2(100),TC2(100),RM2(100)
	  REAL  TQM(ITC),TCM(ITC,INC),RMM(INC)
	REAL U(5), KPD(5), KSP(5)
		integer kod
C------------Защита пакета---------------
C	call tim(kod)
	kod=0
	if(kod.NE.0) goto 999
C------------- Прочесть номер ступени --------------
	OPEN (UNIT=2,FILE='NOMST.DAT',STATUS='OLD')
	READ (2,*) IS
	CLOSE (2)
C--------------  Файл данных для валов и подшипников --------------
	WRITE(STR,102) IS
	FILNAM='FILE3_'//STR
		OPEN (UNIT=10,FILE=FILNAM,STATUS='UNKNOWN')
C--------------  Ввод исходных данных для pедуктоpа в целом -------

	FILNAM='MKV_'//STR
		OPEN (UNIT=2,FILE='FILE1',STATUS='OLD')
	  READ (2,100) STR
	  READ (2,101) IR
	  READ (2,100) STR
	  READ (2,*) L
		IF (L.LT.-1.)  OPEN(UNIT=4,FILE=FILNAM,STATUS='UNKNOWN')

	  CALL DRM(IR,L,RS,RC,CH,WH,T1R,IT,TQ,TC,RM,IRV,TMAX,
	 *        IN,TQM,RMM,TCM,N1R,TNZ,
	 *        IPR,ISR,IE,TN)
		CLOSE (2)
C---------------------------
	WRITE(STR,102) IS
	FILNAM='TABL'//STR
		OPEN (UNIT=3,FILE=FILNAM,STATUS='UNKNOWN')
	FILNAM='TAB_AC_'//STR
		OPEN (UNIT=8,FILE=FILNAM,STATUS='UNKNOWN')
C------------- Прочесть U , КПД  и  KSP --------------
	IF (IS.GT.1) THEN
		OPEN (UNIT=2,FILE='TIPST.ACC',STATUS='OLD')
				do 699 I=1,IS-1
		   READ (2,*) J, U(I), KPD(I), KSP(I)
  699		CONTINUE
C                READ (2,*)
C                READ (2,*) (U(I),I=1,IS-1)
C		IF (L.NE.0) READ (2,*) (KPD(I),I=1,IS-1)
C		IF (L.NE.0) READ (2,*) (KSP(I),I=1,IS-1)
		CLOSE (2)
	END IF
C---------------------------------------------------
	IF(IS.EQ.1)	write (10,*) ISR

	WRITE(STR,102) IS

	FILNAM=STR

	  OPEN (UNIT=7,FILE=FILNAM,STATUS='UNKNOWN')

		STR = '# '//IR
		WRITE(7,100) STR

		STR = ' '
		WRITE(7,100) STR


		WRITE(STR,103) IS

	IF(IS.EQ.1)       WRITE(7,700) L,WH,ISR
  700  FORMAT(' ZPCIL  af drm ==L,WH,ISR:  ',2F10.1,I3)

	FILNAM='REZULT'//STR
	  OPEN (UNIT=1,FILE=FILNAM,STATUS='UNKNOWN')

		CALL VYVDR(IR,L,RS,RC,CH,WH,T1R,IT,IN,TQ,TC,
	 *              RM,IRV,TMAX,IPR,ISR,IE,TN,N1R,TNZ)

	IF(IS.EQ.1)       WRITE(7,701) L,WH,ISR
  701  FORMAT(' ZPU  af VYVDR ==L,WH,IT,IN,ISR:  ',2F10.1,3I3)
	IF(L.LT.-1.) THEN
	DO 7 I=1,IT
	DO 6 J=1,IN
	   TQ(10*(I-1)+J)=TQM(I)
	   RM(10*(I-1)+J)=RMM(J)
	   IF(TQM(I).LT.0.) RM(10*(I-1)+J)=-RMM(J)
	   TC(10*(I-1)+J)=TCM(I,J)
	6	CONTINUE
	7   CONTINUE
	ITN=IT*IN
	DO 12 J=1,ITN
	   TC(J)=TC(J)/100.
   12	CONTINUE
	IT=ITN
	END IF
C   пpи  L = 0.   считается только  геометpия
	IF(IS.EQ.1)       WRITE(7,703) IT,IN
  703  FORMAT(' ZPU bef IF(L.EQ.0.)==IT,IN: ',2I3)
	EV=1.
	  IF(L.EQ.0.) GOTO 10
	   IF(IT.GT.1) THEN
C-------------- Преобразования циклограммы

			CALL UPORTQ(IT,TQ,TC,RM,IRV,IPR,WH,L,
	 *IT1,TQ1,TC1,RM1,IT2,TQ2,TC2,RM2,TN,EV,IS)
	ELSE
	IT1=IT
	TQ1(1)=TQ(1)
	  IF(IRV.EQ.-1) THEN
		TC1(1)=TC(1)*.5
		TN=1.
	  ELSE
	TC1(1)=TC(1)
	  END IF
	RM1(1)=RM(1)
	END IF
   10   OPEN (UNIT=2,FILE='FILE2',STATUS='OLD')
	IF(IS.EQ.1)       WRITE(7,704) L,WH,IT,IN
  704  FORMAT(' ZPU af UPORTQ=L,WH,IT,IN:',2F10.1,2I3)
	IF (IS.EQ.1) PRINT *,'   РАСЧЕТ ЗУБЧАТЫХ ПЕРЕДАЧ РЕДУКТОРА'

C---------- Пересчет нагрузок с учетом U , КПД и KSP предыдущих ступеней

	IF (IS.GT.1) THEN
	PRS=1
	UR=1
	DO J=1,IS-1
		PRS=PRS*U(J)*KPD(J)*KSP(J)
		UR=UR*U(J)
	END DO
		DO I=1,IT
		RM(I)=RM(I)/UR
		TQ(I)=TQ(I)*PRS
	END DO
		DO I=1,IT1
		RM1(I)=RM1(I)/UR
			TQ1(I)=TQ1(I)*PRS
	END DO
		  TMAX=TMAX*PRS
		  IF(L.LT.-1.) WH=WH/UR
	  IF(N1R.GT.1) N1R=N1R/UR
	END IF

	DO III=1,IS
	DO II=1,100
	READ (2,100) STR
	STR=STR(1:3)
	IF (STR.EQ.'IVP') GO TO 1111
	END DO
1111	CONTINUE
	END DO

C  ввод исходных данных по ступеням pедуктоpа (в цикле)-(T1)

		READ(2,*) IVP
	WRITE(10,11111)
11111	format ('*****')
	WRITE(10,*) IVP
		WRITE(*,333) IS
  333  FORMAT(/'  ИДЕТ РАСЧЕТ  ',I2,'-Й СТУПЕНИ РЕДУКТОРА')
		 JJ=0
C---------- Расчет цилиндрической передачи внешнего зацепления
		IF(IVP.EQ.0)  CALL CILEV (JJ,IR,IVP,IS,ISR,L,WH,TMAX,
	 * IRV,IPR,IE,N1R,TNZ,
	 * IT1,TQ1,TC1,RM1,IN,IT,TQ,TC,RM,TN)
		  CLOSE (2)
		  CLOSE (3)
		   IF(L.LT.-1.) CLOSE (4)
		  CLOSE (1)
		  CLOSE (7)
		  CLOSE (8)
		  CLOSE (10)

		IF (IS.EQ.ISR) WRITE(*,3331)
100    FORMAT(A30)
101    FORMAT(A16)
102	FORMAT('OTL',I1,'.txt')
103	FORMAT(I1)
 3331  FORMAT(/'         РАСЧЕТ ЗАКОНЧЕН')
  999	continue
	   STOP
	   END

*/