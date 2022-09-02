#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>

using namespace std;

extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float RS, RC, CH;     //
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];


void DRM()
{
	string str;
	char ch = ' ';
	int i = 0;
	fstream fi;

	cout << "DRM" << endl;

	fi.open("FILE1", fstream::in);

	getline(fi, str);  // пропустить строку

	fi >> IR;	                                            // идентификатор расчета
	cout << "DRM: IR = " << IR << endl;

	getline(fi, str);         // пропустить строку
	getline(fi, str);         // пропустить строку
	
	fi >> L;                                            // тип данных о нагружении
														// L = -1 циклограмма - пока в DRM реализован только этот вариант !!																		
														// L = -10  одна матрица нагрузок																		
														// L = -20  две матрицы нагрузок (положительная и отрицательная) - использовалось для метровагон
	cout << "DRM: L = " << L << endl;

	getline(fi, str);	            // пропустить строку
	getline(fi, str);	            // пропустить строку

	if (L = -1)  fi >> WH >> T1R;                        // ресурс (час),      вх. момент (н*м)

	cout << "DRM: WH = " << WH << "   T1R = " << T1R << endl;

	getline(fi, str);	            // пропустить строку
	getline(fi, str);	            // пропустить строку


	fi >> TMAX >> IT >> IE >> IRV >> IPR >> ISR;

	cout << "DRM: TMAX = " << TMAX << "   IT = " << IT << " IE = " << IE << " IRV = " << IRV << " IPR = " << IPR << " ISR = " << ISR << endl; // IT - кол-во ступеней циклограммы

	getline(fi, str);	            // пропустить строку
	for (i = 0; i < 3; i++) { getline(fi, str); }  // пропусить 3 строки

	for (i = 0; i < IT; i++) fi >> TQ[i] >> TC[i] >> RM[i];  // момент(отн.), частость(отн.), обороты/мин

	cout << "TQ[i]    TC[i]    RM[i]" << endl;
	for (i = 0; i < IT; i++) { cout << "   " << TQ[i] << "        " << TC[i] << "      " << RM[i] << endl; }
	
    fi.close(); // закрываем файл
}
/*
	  SUBROUTINE DRM(IR,L,RS,RC,CH,WH,T1R,IT,TQ,TC,RM,IRV,TMAX,
	 *        IN,TQM,RMM,TCM,N1R,TNZ,
	 *        IPR,ISR,IE,TN)
C  SCHITYVANIE ISH.DAN. DLQ REDUIKTORA IZ FAYLA 'B' V OPER.PAMYAT
	  REAL L,N1R
	  CHARACTER*1 AAA
	  CHARACTER*65 A
	  CHARACTER*16 IR
	  DIMENSION  TQ(20),TC(20),RM(20)
	  DIMENSION  TQM(20),TCM(20,10),RMM(10)
	  DIMENSION  TQM2(20),TCM2(20,10),RMM2(10)
		  SAVE
	DATA S /1.E4/
C------------- Прочесть номер ступени --------------
	OPEN (UNIT=1,FILE='NOMST.DAT',STATUS='OLD')
	READ (1,*) IS
	CLOSE (1)
C__________________________________________________
C      READ(2,100) A
C      READ(2,90) IR
C      READ(2,100) A
C      READ(2,*) L
	  AAA='-'

	  READ(2,100) A

C	write(7,33333)
33333	format('DRM: L=',F6.1)

	IF (L.EQ.0) GOTO 5
	IF (L.GT.0) GOTO 2
	TN=0.
	IF(L.GE.-1) THEN
	   READ(2,*) WH,T1R

	ELSE
C при L=-10. и =-20.  WH - число оборотов за весь срок службы
C при L=-10. задается 1 матрица накрузок, -20.- 2 матрицы (положит.и отриц.)
	   READ(2,*) WH,WH2,IT2,N1R,TNZ
	END IF
	   GOTO 3
	2 READ(2,*) RS,RC,CH
	3 READ(2,100) A
	  READ(2,*) TMAX,IT,IE,IRV,IPR,ISR
C при L=-20 IRV =0
	IF(L.LT.-1.) GOTO 50
	IN=1
	   DO 4 I=1,3
	4 READ(2,100) A
	  READ(2,*) (TQ(I),TC(I),RM(I),I=1,IT)
	GOTO 6
C  L = -10 ВВОД ОДНОЙ МАТРИЦЫ
   50   IN=10
	  OPEN(UNIT=3,FILE='MATR',STATUS='OLD')
	  READ(3,100) A
	  READ(3,100) A
	   READ(3,*) (RMM(J),J=1,IN)
	  READ(3,100) A
		DO 7 I=1,IT
	   READ(3,*) TQM(I),(TCM(I,J),J=1,IN)
	7  CONTINUE
	  IF(L.LT.-10.) THEN
c      READ(3,100) A
	  READ(3,100) A
	  READ(3,100) A
	   READ(3,*) (RMM2(J),J=1,IN)
	  READ(3,100) A
		DO 8 I=1,IT2
	   READ(3,*) TQM2(I),(TCM2(I,J),J=1,IN)
	8  CONTINUE
c-----
	S1=0.
	DO 54 I=1,IT
	DO 53 J=1,IN
	S1=S1+(TQM(I)/S)**6*TCM(I,J)
   53  CONTINUE
   54  CONTINUE
	S2=0.
	DO 56 I=1,IT2
	DO 55 J=1,IN
	S2=S2+(TQM2(I)/S)**6*TCM2(I,J)
   55  CONTINUE
   56  CONTINUE
	TN=(S2*WH2)/(S1*WH)
	TNN=TN
	IF(TNN.GT.1.) AAA='+'
	END IF
	IF(IS.EQ.1) THEN
		WRITE(4,243) IR
  243  FORMAT(/36X,A16//
	 *  14X,'ЗАДАННАЯ МАТРИЦА ЧАСТОСТЕЙ   (ПРОЦЕНТЫ)'//
	 *  1X,78(1H-)/
	 *' НАГРУЗКА |',21X,'ЧАСТОТЫ ВРАЩЕНИЯ')
		WRITE(4,2330) AAA
 2330  FORMAT(1X,A1,77(1H-))
		WRITE(4,233) IT,IT2,RMM
  233  FORMAT(1X,2I3,2X,10F7.1)
 2331  FORMAT(9X,10F7.1)
		WRITE(4,2332)
		DO 51 I=1,IT
	   WRITE(4,234) TQM(I),(TCM(I,J),J=1,IN)
   51  CONTINUE
  234  FORMAT(1X,F8.1,10F7.4)
		WRITE(4,2332)
	END IF
	IF(IS.EQ.1.AND.L.LT.-10.) THEN
		WRITE(4,2430)
 2430  FORMAT(/
	 *  14X,'ЗАДАННАЯ МАТРИЦА ЧАСТОСТЕЙ   (ПРОЦЕНТЫ)'/
	 *  14X,'         ( отрицательная )'//
	 *  1X,78(1H-)/
	 *' НАГРУЗКА |',21X,'ЧАСТОТЫ ВРАЩЕНИЯ')
		WRITE(4,2332)
 2332  FORMAT(1X,78(1H-))
		WRITE(4,2331) RMM2
		WRITE(4,2332)
		DO 52 I=1,IT2
	   WRITE(4,234) TQM2(I),(TCM2(I,J),J=1,IN)
   52  CONTINUE
		WRITE(4,2332)
	END IF
	IF (TNN.GT.1.AND.L.LT.-10.) THEN
	 IT=IT2
	DO 58 I=1,IT
	TQM(I)=TQM2(I)
	DO 57 J=1,IN
	TCM(I,J)=TCM2(I,J)
   57  CONTINUE
   58  CONTINUE
	DO 59 J=1,IN
	RMM(J)=RMM2(J)
   59  CONTINUE
	TN=(S1*WH)/(S2*WH2)
	WH=WH2
	IF(IS.EQ.1) WRITE(4,2431)
 2431  FORMAT(//
	 * '  В КАЧЕСТВЕ РАСЧЕТНОЙ ВЫБРАНА ОТРИЦАТЕЛЬНАЯ  МАТРИЦА '/)
		IF(IS.EQ.1) WRITE(4,2432) WH,TN
 2432  FORMAT(
	 * '  ОБЩЕЕ ЧИСЛО ОБОРОТОВ ЗА ВЕСЬ СРОК СЛУЖБЫ,млн   WH =',F8.2/
	 * '  КОЭФФИЦИЕНТ АСИММЕТРИИ НАГРУЗКИ                TN =',F9.3)
	END IF
	IF (TNN.LE.1.AND.L.LT.-10.) THEN
		IF(IS.EQ.1) WRITE(4,2433)
 2433  FORMAT(//
	 * '  В КАЧЕСТВЕ РАСЧЕТНОЙ ВЫБРАНА ПОЛОЖИТЕЛЬНАЯ  МАТРИЦА '/)
		IF(IS.EQ.1) WRITE(4,2432) WH,TN
	END IF
	IF(L.LT.-1.) CLOSE(3)
	   GOTO 6
	5 READ(2,*) IPR,ISR
	6 CONTINUE
   90 FORMAT(A16)
  100 FORMAT(A65)

	open(unit=20,file='drm.txt',status='unknown')
	write(20,*) 'ipr, C16,', ir
	write(20,*) 'isr, N1,', isr
	close(20)

	   RETURN
	   END


*/