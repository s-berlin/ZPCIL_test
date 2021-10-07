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

//========== ���������� �� ���������
char IR[20] = {};  // ������������� ������� 
int IT = 0, IRV = 0, IPR = 6, IE = 1, ISR = 1, IN = 0;
float L = 0, WH = 0;      // ������, �����
float T1R = 0, TMAX = 0;     // ������ �� �������� ����, ��
float TQ[20] = {}, TC[20] = {}, RM[20] = {};

fstream f_1;    // ���� ��� ����������    //***

//========== ���������� �� �������
int IVP = 0;                         // ��� �������
float Z1 = 0, Z2 = 0;                // ����� ������ �������� � ������
float MN = 0, BE = 0, X1, X2;        // ������, ���� �������, ������������ ��������
int flaw;
float AW, B1, B2;                    // ��������� ���������� ������ �������� � ������
float AL, HA, HL, CZV;               // ���� �������, ������������: ������ �������, ��������� ������, ����������� ������  
int IST1, IST2, IST3, IST4, IST5;    // ������� �������� �� ������: ����������, ���������, ��������; ��� ����������, ��� ������� �� ������� �����
int IMD, IKG;                        // ����. ������� ��������� �������, ����� ����� �� ����������� ������
float SHLM1, SHPM1, SFLB1, SFPM1;    // ��������: ������ ����. ������������, ������. ����. ���������� ��� ����. ��������, ���. ������ ������-� ��� ������, ������. ���. ���������� ������ ��� ����. �������� 
float SHLM2, SHPM2, SFLB2, SFPM2;    // ������:   - " -    - " -    - " -    - " -
int IG1, IG2;                        // ������ ��������� �������� � ������
float H1, HK1, HT1, SHER1, YZ1;      // ��������: ��������� �����������, ��������� ����������, ������� ������������ ����, �������������, ����. ������� ��������� ���������
float YT1, YR1, SHV1;                // ��������: ��������������� �����������, ������������� ���������� �����������, ����. ������ ���������
float H2, HK2, HT2, SHER2, YZ2;      // ������: ��������� �����������, ��������� ����������, ������� ������������ ����, �������������, ����. ������� ��������� ���������
float YT2, YR2, SHV2;                // ������: ��������������� �����������, ������������� ���������� �����������, ����. ������ ���������
int IMF1, IMF2, IVR;                 // �������� ���������� ���������� ����������� �������� � ������, ������� ������� ����-�� ������ �� ���������� ������������
float CZ1, CZ2, KSP, KPD, PR;        // ����� ���������� �� ������ �������� � ������, ����. �������� ������, ���, ����������� ������������ �� �������� ������������
float LO = 0, S1 = 0, FKE = 0, GM;   // ���������� ����� �������, ���������� �� ����� �� ������� ������� ������� �� ������ ��������, ?, ?
int IQ = 1, IP = 0, IZ1 = 0, IG = 0; // ��� ���������� �������, ��� ����������, ?, ?
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

//	----------������ �������������� �������� �������� ����������
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
C  �������� �p��p���� p����� �������� ��p���� p������p�
C
C
	PARAMETER(ITC=20,INC=10,ISRC=20)
	  REAL L,N1R
	  CHARACTER*20  FILNAM
	  CHARACTER*16 IR    ! ������������� �������
	  CHARACTER*30 STR
	  REAL  TQ(ITC*INC),TC(ITC*INC),RM(ITC*INC)
C ,UI(ISRC),KPDI(ISRC)
	  REAL TQ1(100),TC1(100),RM1(100)
	  REAL TQ2(100),TC2(100),RM2(100)
	  REAL  TQM(ITC),TCM(ITC,INC),RMM(INC)
	REAL U(5), KPD(5), KSP(5)
		integer kod
C------------������ ������---------------
C	call tim(kod)
	kod=0
	if(kod.NE.0) goto 999
C------------- �������� ����� ������� --------------
	OPEN (UNIT=2,FILE='NOMST.DAT',STATUS='OLD')
	READ (2,*) IS
	CLOSE (2)
C--------------  ���� ������ ��� ����� � ����������� --------------
	WRITE(STR,102) IS
	FILNAM='FILE3_'//STR
		OPEN (UNIT=10,FILE=FILNAM,STATUS='UNKNOWN')
C--------------  ���� �������� ������ ��� p������p� � ����� -------

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
C------------- �������� U , ���  �  KSP --------------
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
C   �p�  L = 0.   ��������� ������  ������p��
	IF(IS.EQ.1)       WRITE(7,703) IT,IN
  703  FORMAT(' ZPU bef IF(L.EQ.0.)==IT,IN: ',2I3)
	EV=1.
	  IF(L.EQ.0.) GOTO 10
	   IF(IT.GT.1) THEN
C-------------- �������������� �����������

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
	IF (IS.EQ.1) PRINT *,'   ������ �������� ������� ���������'

C---------- �������� �������� � ������ U , ��� � KSP ���������� ��������

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

C  ���� �������� ������ �� �������� p������p� (� �����)-(T1)

		READ(2,*) IVP
	WRITE(10,11111)
11111	format ('*****')
	WRITE(10,*) IVP
		WRITE(*,333) IS
  333  FORMAT(/'  ���� ������  ',I2,'-� ������� ���������')
		 JJ=0
C---------- ������ �������������� �������� �������� ����������
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
 3331  FORMAT(/'         ������ ��������')
  999	continue
	   STOP
	   END

*/