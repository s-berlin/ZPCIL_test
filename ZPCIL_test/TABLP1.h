﻿#include <fstream>

//========== Переменные по редуктору
extern char IR[20];
extern int IT, IRV, IPR, IE, ISR, IN;
extern float L, WH, N1R;      // ресурс, часов
extern float T1R, TMAX;     // момент на входящем валу, Нм
extern float TQ[20], TC[20], RM[20];

using namespace std;

extern fstream f_1;    // файл для результата    //***

//========== Переменные по ступени
extern int IVP;                             // тип ступени
extern float Z1, Z2;                        // числа зубьев шестерни и колеса
extern float MN, BE, X1, X2, X[2];          // модуль, угол наклона, коэффициенты смещения
extern int flaw;
extern float AW, B1, B2;                    // межосевое расстояние ширины шестерни и колеса
extern float AL, HA, HL, CZV;               // угол профиля, коэффициенты: высоты головки, граничной высоты, радиального зазора  
extern int IST1, IST2, IST3, IST4, IST5;    // степени точности по нормам: кинематики, плавности, контакта; вид сопряжения, вид допуска на боковой зазор
extern int IMD, IKG;                        // коэф. наличия массивных деталей, номер схемы по упрощенному методу
extern float SHLM1, SHPM1, SFLB1, SFPM1;    // шестерня: предел конт. выносливости, допуск. конт. напряжение при макс. нагрузке, баз. предел выносл-и при изгибе, предел. баз. напряжение изгиба при макс. нагрузке 
extern float SHLM2, SHPM2, SFLB2, SFPM2;    // колесо:   - " -    - " -    - " -    - " -
extern int IG1, IG2;                        // группы материала шестерни и колеса
extern float H1, HK1, HT1, SHER1, YZ1;      // шестерня: твердость поверхности, твердость сердцевины, толщина упрочненного слоя, шероховатость, коэф. способа получения заготовки
extern float YT1, YR1, SHV1;                // шестерня: технологический коэффициент, шероховатость переходной поверхности, коэф. запаса прочности
extern float H2, HK2, HT2, SHER2, YZ2;      // колесо: твердость поверхности, твердость сердцевины, толщина упрочненного слоя, шероховатость, коэф. способа получения заготовки
extern float YT2, YR2, SHV2;                // колесо: технологический коэффициент, шероховатость переходной поверхности, коэф. запаса прочности
extern int IMF1, IMF2, IVR;                 // признаки шлифования переходной поверхности шестерни и колеса, Признак задания коэф-та запаса по контактной выносливости
extern float CZ1, CZ2, KSP, KPD, PR;        // числа зацеплений за оборот шестерни и колеса, коэф. силового потока, КПД, вероятность неразрушения по изгибной выносливости
extern float LO, S1, FKE, GM;               // расстояние между опорами, расстояние от опоры со стороны подвода момента до центра шестерни, ?, ?
extern int IQ, IP, IZ1, IG;                 // тип приложения момента, тип подшипника, ?, ?

void TABLP1(float Z[2], int KST[3], int KST4, int KST5, float DLTH[2], float SC[2],
	float HH[2], float SY[2], float HAY[2], float D[2], float DA[2], float HZ, float EHS[2], float TH[2], float IIW1, float IIW2)
{
//	float BBWW[2] = { 0,0 }, BW = 0;
//	float DW[2] = {}, D[2] = {}, DA[2] = {}, DB[2] = {}, DF[2] = {};
//	float DL[2] = {}, DP[2] = {}, DG[2] = {};
//	float DLTH[2] = {}, TGAA[2] = {}, EA[2] = {}, HZ = 0;
//	float ROG[2] = {}, TGAG[2] = {}, ROL[2] = {}, ROP[2] = {}, ZN[2];
//	float W[2] = {}, ROWN[2] = {}, DWN[2] = {};
//	float XMIN[2] = {}, XMINR[2] = {}, BETA[2] = {}, SNA[2] = {};
//	float DU[2] = {}, TGAU[2] = {}, ROW[2] = {}, TGAV[2] = {}, DV[2] = {}, RL[2] = {};
//	float SC[2] = {}, ROS[2] = {}, DS[2] = {}, HH[2] = {};
//	float DY[2] = {}, TGALY = 0, STY = 0, CSBY, PSIYV = 0, SY[2] = {}, HAY[2] = {};
	float FR[2] = {}, TWM[2] = {}, TW[2] = {}, ECS[2] = {}, TC_[2] = {};
	float EWS1[2] = {}, EWS2[2] = {}, EWS[2] = {};
	float DLTHMN[2] = {}, DLTHMX[2] = {};

	float EPBET, EPGAM, BETB, EPAM;

	//  таблица паpаметов цилиндpического зубчатого колеса
    //    ECKД ГOCT 2.403 - 75
	string KT[6] = { " - A", " - B", " - C", " - D", " - E", " - H" };
	char KT5[8] = { 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'h' };
//	int KST[3];

	cout << "TABLP1" << endl;

	DOP1L(MN, D, KST, IST4, IST5, FR, EHS, TH, EWS1, EWS2, EWS, TWM, TW, ECS, TC_);

}





	/*
	  SUBROUTINE TABLP1(IR,M,Z,BET,X,KST,KST4,KST5,DLTH,
	 * W,SC,HH,SY,HAY,D,DA,HZ,EHS,TH,IIW1,IIW2,
	 * AL,HA,HL,CZV)
C   таблица паpаметов цилиндpического зубчатого колеса
C     ECKД ГOCT 2.403-75
	  REAL M
	   CHARACTER*16 IR
	   CHARACTER*4 KTS
	   CHARACTER*30 STR
	   CHARACTER*6 STR6
	   CHARACTER*7 STR7
	   CHARACTER*3 KT(6)
	   CHARACTER*1 KT5(8)
	  DIMENSION Z(2),X(2),KST(3),DLTH(2),W(2),D(2),DA(2)
	  DIMENSION SC(2),HH(2),SY(2),HAY(2),
	 *EWS1(2),EWSTW(2),ECS(2),ECSTC(2),DLTHMX(2),DLTHMN(2)
	  DIMENSION EHS(2),TH(2),EWS2(2),TW(2),TWM(2),FR(2),
	 *TC(2),EWS(2),EWSTWM(2)
	   SAVE
	  DATA KT/'- A','- B','- C','- D','- E','- H'/
	  DATA KT5/'x','y','z','a','b','c','d','h'/
c      print *,'  dop1***',M,D(1),D(2),KST(1),KST(2),KST(3),KST4,DLTH(1)
	KTS=KT(KST4)
	IF(KST5.EQ.8.AND.(KST4.EQ.5.OR.KST4.EQ.6)) GO TO 5
	   IF(KST5.NE.(KST4+3)) KTS=KT(KST4)//KT5(KST5)
	5 CONTINUE
	  CALL DOP1L (M,D,KST,KST4,KST5,FR,EHS,TH,EWS1,EWS2,
	 * EWS,TWM,TW,ECS,TC)
	  DO 20 I=1,2
	  DLTHMN(I)=-DLTH(I)-EHS(I)
	  DLTHMX(I)=DLTHMN(I)+TH(I)
	  EWSTW(I)=EWS1(I)-TW(I)
	  EWSTWM(I)=EWS(I)-TWM(I)
	  ECSTC(I)=ECS(I)-TC(I)
   20 CONTINUE
C------------------------------------------------------------
	write(20,5553) m
	write(20,5551) z(1)
	write(20,5552) z(2)
5553	format('MN,N5.2,',F5.2)
5551	format('Z1,N4.0,',F4.0)
5552	format('Z2,N4.0,',F4.0)

	  CALL ZPRGMS(BET,GRM,SEC)
		WRITE(20,5554) GRM,SEC
		WRITE(20,55541) GRM
		WRITE(20,55542) SEC
5554	format('BE,C8,',F5.2,F3.2)
55541	format('BE_GRM,N5.2,',F5.2)
55542	format('BE_SEC,N5.2,',F5.2)

	   CALL ZPRGMS(AL,GRM,SEC)
		IF(HA.EQ.1..AND.GRM.EQ.20..AND.CZV.EQ.0.25) THEN
		  WRITE(20,55543)
55543		format('GOST,C30,ГОСТ 13755-81')
	ELSE
		  WRITE(20,55544)
55544		format('GOST,C30,     ')
	END IF

		WRITE(20,55545) GRM,SEC
	WRITE(20,55546) HA
	WRITE(20,55547) HL
	WRITE(20,55548) CZV
55545		format('ALFA,C10,',F5.2,F3.2)
55546		format('HA,N7.3,',F7.3)
55547		format('HAZV,N7.3,',F7.3)
55548		format('CZV,N7.3,',F7.3)

	write(20,5555) x(1)
	write(20,5556) x(2)
	write(20,5557) kst(1),kst(2),kst(3)
	write(20,5558) kts
5555	format('X1,N5.3,',F5.3)
5556	format('X2,N5.3,',F5.3)
5557	format('KST1,N2,',I2/'KST2,N2,',I2/'KST3,N2,',I2)
5558	format('KTS,C4,',A4)

C       Предельные показания танг. зубомера

	write(20,55581) dlthmn(1)
	write(20,55582) dlthmx(1)
	write(20,55583) dlthmn(2)
	write(20,55584) dlthmx(2)
55581	format('DLTHMN1,N6.3,',F6.3)
55582	format('DLTHMX1,N6.3,',F6.3)
55583	format('DLTHMN2,N6.3,',F6.3)
55584	format('DLTHMX2,N6.3,',F6.3)

C	Длина общей нормали

		WRITE(20,5561) W(1),EWS1(1),EWSTW(1)
		WRITE(20,5562) W(2),EWS1(2),EWSTW(2)
5561  format('W1,N7.2,',F7.2/'WP1,N6.3,',F6.3/'WM1,N6.3,',F6.3)
5562  format('W2,N7.2,',F7.2/'WP2,N6.3,',F6.3/'WM2,N6.3,',F6.3)

C	Средняя длина общей нормали

		WRITE(20,5563) W(1),EWS(1),EWSTWM(1)
		WRITE(20,5564) W(2),EWS(2),EWSTWM(2)
5563  format('WS1,N7.2,',F7.2/'WSP1,N6.3,',F6.3/'WSM1,N6.3,',F6.3)
5564  format('WS2,N7.2,',F7.2/'WSP2,N6.3,',F6.3/'WSM2,N6.3,',F6.3)

C	Постоянная хорда

		WRITE(20,5565) SC(1),ECS(1),ECSTC(1)
		WRITE(20,5566) SC(2),ECS(2),ECSTC(2)
5565  format('SC1,N7.2,',F7.2/'SCP1,N6.3,',F6.3/'SCM1,N6.3,',F6.3)
5566  format('SC2,N7.2,',F7.2/'SCP2,N6.3,',F6.3/'SCM2,N6.3,',F6.3)

C	Высота до постоянной хорды

	write(20,5567) HH(1),HH(2)
5567	format('HC1,N7.2,',F7.2/'HC2,N7.2,',F7.2)

C	Толщина по хорде

		WRITE(20,5568) SY(1),ECS(1),ECSTC(1)
		WRITE(20,5569) SY(2),ECS(2),ECSTC(2)
5568  format('SY1,N7.2,',F7.2/'SYP1,N6.3,',F6.3/'SYM1,N6.3,',F6.3)
5569  format('SY2,N7.2,',F7.2/'SYP2,N6.3,',F6.3/'SYM2,N6.3,',F6.3)

C	Высота до хорды

	write(20,5570) hay(1),hay(2)
5570	format('HAY1,N6.2,',F6.2/'HAY2,N6.2,',F6.2)

C	Делительный диаметр

	write(20,5571) d(1),d(2)
5571	format('D1,N7.2,',F7.2/'D2,N7.2,',F7.2)

C	Высота зуба

	write(20,5572) hz
5572	format('HZ,N6.2,',F6.2)

C------------------------------------------------------------
	  WRITE(3,113)IR,IR
  113 FORMAT(1X,'ИДЕНТИФИКАТОР РАСЧЕТА - ',A16,3X,
	 * 'ИДЕНТИФИКАТОР РАСЧЕТА - ',A16/)
	  WRITE(3,101)
  101 FORMAT(1X,'┌',24(1H─),'┬',3H───,'┬',13(1H─),'┐┌',
	 * 24(1H─),'┬',3H───,'┬',13(1H─),'┐')
	  WRITE(3,102)M,M
  102 FORMAT(1X,'│  МОДУЛЬ',16X,'│ m │',3X,F6.2,4X,'│',
	 *'│  МОДУЛЬ',16X,'│ m │',3X,F6.2,4X,'│')
	  WRITE(3,103)
  103 FORMAT(1X,'├',24(1H─),'┼',3H───,'┼',13(1H─),'┤├',
	 * 24(1H─),'┼',3H───,'┼',13(1H─),'┤')
	  WRITE(3,104)Z(1),Z(2)
  104 FORMAT(1X,'│  ЧИСЛО ЗУБЬЕВ',10X,'│ z │',3X,F4.0,6X,'│',
	 *'│  ЧИСЛО ЗУБЬЕВ',10X,'│ z │',3X,F4.0,6X,'│')
	  WRITE(3,103)
	  CALL ZPRGMS(BET,GRM,SEC)
	  IF(BET.NE.0) WRITE(3,105)GRM,SEC,GRM,SEC
  105 FORMAT(1X,'│  УГОЛ НАКЛОНА',10X,'│   │',
	 *3X,F5.2,F3.2,2X,'│',
	 *'│  УГОЛ НАКЛОНА',10X,'│   │',3X,F5.2,F3.2,2X,'│')
	  IF(BET.NE.0) WRITE(3,103)
	  IF(BET.NE.0) WRITE(3,106)
  106 FORMAT(1X,'│  НАПРАВЛЕНИЕ ЛИНИИ ЗУБА│ - │',13X,'│',
	 *'│  НАПРАВЛЕНИЕ ЛИНИИ ЗУБА│ - │',13X,'│')
	  IF(BET.NE.0) WRITE(3,103)
	   CALL ZPRGMS(AL,GRM,SEC)
		IF(HA.NE.1..OR.GRM.NE.20..OR.CZV.NE.0.25) THEN
		WRITE(3,2140) GRM,SEC,GRM,SEC
 2140 FORMAT(
	 * 1X,'│  УГОЛ ПРОФИЛЯ          │   │',3X,F5.2,F3.2,2X,'│',
	 *    '│  УГОЛ ПРОФИЛЯ          │   │',3X,F5.2,F3.2,2X,'│')
	WRITE(3,103)
		WRITE(3,2141) HA,HA
 2141 FORMAT(
	 * 1X,'│  КОЭФ.ВЫСОТЫ ГОЛОВКИ   │ha*│',3X,F7.3,3X,'│',
	 *    '│  КОЭФ.ВЫСОТЫ ГОЛОВКИ   │ha*│',3X,F7.3,3X,'│')
	WRITE(3,103)
		WRITE(3,2142) HL,HL
 2142 FORMAT(
	 * 1X,'│  КОЭФ.ГРАНИЧНОЙ ВЫСОТЫ │hl*│',3X,F7.3,3X,'│',
	 *    '│  КОЭФ.ГРАНИЧНОЙ ВЫСОТЫ │hl*│',3X,F7.3,3X,'│')
	WRITE(3,103)
		WRITE(3,2143) CZV,CZV
 2143 FORMAT(
	 * 1X,'│ КОЭФ.РАДИАЛЬНОГО ЗАЗОРА│c* │',3X,F7.3,3X,'│',
	 *    '│ КОЭФ.РАДИАЛЬНОГО ЗАЗОРА│c* │',3X,F7.3,3X,'│')
	WRITE(3,103)
	ELSE
	  WRITE(3,107)
  107 FORMAT(1X,'│  НОРМАЛЬНЫЙ',12X,'│   │',5X,'ГОСТ',4X,'│',
	 *'│  НОРМАЛЬНЫЙ',12X,'│   │',5X,'ГОСТ',4X,'│'/
	 *1X,'│  ИСХОДНЫЙ КОНТУР',7X,'│ - │  13755-81   │',
	 *'│  ИСХОДНЫЙ КОНТУР',7X,'│ - │  13755-81   │')
	  WRITE(3,103)
	END IF
	  WRITE(3,108)X(1),X(2)
  108 FORMAT(1X,'│  КОЭФФИЦИЕНТ СМЕЩЕНИЯ  │ x │',
	 *3X,F7.3,3X,'│',
	 *'│  КОЭФФИЦИЕНТ СМЕЩЕНИЯ  │ x │',3X,F7.3,3X,'│')
	  WRITE(3,103)
	  IF((KST(1)-KST(2))+(KST(1)-KST(3)))7,8,7
	7 WRITE(3,109)
  109 FORMAT(1X,'│  СТЕПЕНЬ ТОЧНОСТИ',6X,'│ - │',13X,'│',
	 *'│  СТЕПЕНЬ ТОЧНОСТИ',6X,'│ - │',13X,'│')
	  WRITE(3,110)KST(1),KST(2),KST(3),KTS,
	 *KST(1),KST(2),KST(3),KTS
  110 FORMAT(
	 *1X,'│  ПО ГОСТ 1643-81',7X,'│   │',1X,
	 *I2,'-',I2,'-',I2,A4,'│',
	 *'│  ПО ГОСТ 1643-81',7X,'│   │',1X,
	 *I2,'-',I2,'-',I2,A4,'│')

	  GOTO 9
	8 WRITE(3,109)
	  WRITE(3,111)KST(1),KTS,KST(1),KTS
  111 FORMAT(1X,'│  ПО ГОСТ 1643-81',7X,'│   │',
	 *4X,I2,A4,3X,'│',
	 *'│  ПО ГОСТ 1643-81',7X,'│   │',4X,I2,A4,3X,'│')

	9 WRITE(3,103)
	  CONTINUE
	  WRITE(3,122)DLTHMN(1),DLTHMN(2),DLTHMX(1),DLTHMX(2)
  122 FORMAT(1X,
	 *   '│  ПРЕДЕЛЬНЫЕ ПОКАЗАНИЯ  │ - │',4X,F6.3,3X,'│',
	 *   '│  ПРЕДЕЛЬНЫЕ ПОКАЗАНИЯ  │ - │',4X,F6.3,3X,'│'/
	 *1X,'│  ТАНГЕНЦ. ЗУБОМЕРА     │   │',4X,F6.3,3X,'│',
	 *   '│  ТАНГЕНЦ. ЗУБОМЕРА     │   │',4X,F6.3,3X,'│')

	  WRITE(3,103)
   10 CONTINUE

	 IF(IIW2.EQ.0.AND.IIW1.EQ.0)
	 * WRITE(3,123)  W(1),EWS1(1),W(2),EWS1(2),EWSTW(1),EWSTW(2)
  123 FORMAT(1X,
	 *'│  ДЛИНА ОБЩЕЙ НОРМАЛИ   │ W │',F7.2,F6.3,'│',
	 *'│  ДЛИНА ОБЩЕЙ НОРМАЛИ   │ W │',F7.2,F6.3,'│'/
	 *1X,'│',24X,'│   │',7X,F6.3,'│','│',
	 *24X,'│   │',7X,F6.3,'│')
	IF(IIW1.GT.0.AND.IIW2.EQ.0)
	 * WRITE(3,1230) W(2),EWS1(2),EWSTW(2)
 1230 FORMAT(1X,
	 *'│                        │   │',13X,'│',
	 *'│  ДЛИНА ОБЩЕЙ НОРМАЛИ   │ W │',F7.2,F6.3,'│'/
	 *1X,'│',24X,'│   │',13X,'│','│',
	 *24X,'│   │',7X,F6.3,'││')
	 IF(IIW2.GT.0.AND.IIW1.EQ.0)
	 * WRITE(3,1231) W(1),EWS1(1),EWSTW(1)
 1231 FORMAT(1X,
	 *'│  ДЛИНА ОБЩЕЙ НОРМАЛИ   │ W │',F7.2,F6.3,'│',
	 *'│                        │   │',13X,'│'/
	 *1X,'│',24X,'│   │',7X,F6.3,'│','│',
	 *24X,'│   │',13X,'│')
	 IF(IIW2.EQ.0.OR.IIW1.EQ.0) WRITE(3,103)
   11 CONTINUE
	 IF(IIW2.EQ.0.AND.IIW1.EQ.0)
	 * WRITE(3,124) W(1),EWS(1),W(2),EWS(2),EWSTWM(1),EWSTWM(2)
  124 FORMAT(1X,
	 *   '│  СРЕДНЯЯ ДЛИНА         │ W │',F7.2,F6.3,'│',
	 *   '│  СРЕДНЯЯ ДЛИНА         │ W │',F7.2,F6.3,'│'/
	 *1X,'│  ОБЩЕЙ НОРМАЛИ         │   │',7X,F6.3,'│',
	 *   '│  ОБЩЕЙ НОРМАЛИ         │   │',7X,F6.3,'│')
	IF(IIW1.GT.0.AND.IIW2.EQ.0)
	 * WRITE(3,1240) W(2),EWS(2),EWSTWM(2)
 1240 FORMAT(1X,
	 *   '│  СРЕДНЯЯ ДЛИНА         │ W │',13X,'│',
	 *   '│  СРЕДНЯЯ ДЛИНА         │ W │',F7.2,F6.3,'│'/
	 *1X,'│  ОБЩЕЙ НОРМАЛИ         │   │',13X,'│',
	 *   '│  ОБЩЕЙ НОРМАЛИ         │   │',7X,F6.3,'│')
	 IF(IIW2.GT.0.AND.IIW1.EQ.0)
	 * WRITE(3,1241) W(1),EWS(1),EWSTWM(1)
 1241 FORMAT(1X,
	 *   '│  СРЕДНЯЯ ДЛИНА         │ W │',F7.2,F6.3,'│',
	 *   '│  СРЕДНЯЯ ДЛИНА         │ W │',13X,'│'/
	 *1X,'│  ОБЩЕЙ НОРМАЛИ         │   │',7X,F6.3,'│',
	 *   '│  ОБЩЕЙ НОРМАЛИ         │   │',13X,'│')
	 IF(IIW2.EQ.0.OR.IIW1.EQ.0) WRITE(3,103)
	  WRITE(3,125)SC(1),ECS(1),SC(2),ECS(2),ECSTC(1),ECSTC(2)
  125 FORMAT(1X,
	 *   '│  ПОСТОЯННАЯ ХОРДА      │ _ │',F7.2,F6.3,'│',
	 *   '│  ПОСТОЯННАЯ ХОРДА      │ _ │',F7.2,F6.3,'│'/
	 *1X,'│',24X,'│ Sc│',7X,F6.3,'││',24X,'│ Sc│',
	 *7X,F6.3,'│')
	  WRITE(3,103)
	  WRITE(3,126)HH(1),HH(2)
  126 FORMAT(1X,
	 *   '│  ВЫСОТА ДО ПОСТ. ХОРДЫ │ hc│',3X,F6.2,4X,'│',
	 *   '│  ВЫСОТА ДО ПОСТ. ХОРДЫ │ hc│',3X,F6.2,4X,'│')
	  WRITE(3,103)
	  WRITE(3,127)SY(1),ECS(1),SY(2),ECS(2),ECSTC(1),ECSTC(2)
  127 FORMAT(1X,
	 *   '│  ТОЛЩИНА ПО ХОРДЕ      │ _ │',F7.2,F6.3,'│',
	 *   '│  ТОЛЩИНА ПО ХОРДЕ      │ _ │',F7.2,F6.3,'│'/
	 *1X,'│',24X,'│ Sy│',7X,F6.3,'││',24X,'│ Sy│',
	 *7X,F6.3,'│')
	  WRITE(3,103)
	  WRITE(3,128)HAY(1),HAY(2)
  128 FORMAT(1X,
	 *   '│  ВЫСОТА ДО ХОРДЫ       │hay│',3X,F6.2,4X,'│',
	 *   '│  ВЫСОТА ДО ХОРДЫ       │hay│',3X,F6.2,4X,'│')
	  WRITE(3,103)
   21 CONTINUE
	  WRITE(3,130)D(1),D(2)
  130 FORMAT(1X,
	 *   '│  ДЕЛИТЕЛЬНЫЙ ДИАМЕТР   │ d │',2X,F7.2,4X,'│',
	 *   '│  ДЕЛИТЕЛЬНЫЙ ДИАМЕТР   │ d │',2X,F7.2,4X,'│')
	  WRITE(3,103)
	  WRITE(3,131)HZ,HZ
  131 FORMAT(1X,
	 *   '│  ВЫСОТА ЗУБА           │ h │',3X,F6.2,4X,'│',
	 *   '│  ВЫСОТА ЗУБА           │ h │',3X,F6.2,4X,'│')
	  WRITE(3,103)
	  WRITE(3,135)
  135 FORMAT(1X,
	 *   '│  ОБОЗНАЧЕНИЕ ЧЕРТЕЖА   │   │',13X,'│',
	 *   '│  ОБОЗНАЧЕНИЕ ЧЕРТЕЖА   │   │',13X,'│'/
	 *1X,'│  СОПРЯЖЕННОГО ЗУБЧАТОГО│ - │',13X,'│',
	 *   '│  СОПРЯЖЕННОГО ЗУБЧАТОГО│ - │',13X,'│'/
	 *1X,'│  КОЛЕСА',16X,'│   │',13X,'│',
	 *   '│  КОЛЕСА',16X,'│   │',13X,'│')
	  WRITE(3,100)
  100 FORMAT(1X,'└',24(1H─),'┴',3H───,'┴',13(1H─),'┘└',
	 * 24(1H─),'┴',3H───,'┴',13(1H─),'┘')
	  WRITE(3,140)
  140 FORMAT(/)
	  WRITE(3,112)
  112 FORMAT(15X,'ПРИМЕЧАНИЕ.'/)
	  CONTINUE
	  WRITE(3,141)DA(1),DA(2)
  141 FORMAT(1X,'ПОКАЗАНИЯ ТАНГЕНЦИАЛЬНОГО ЗУБОМЕРА ДАНЫ ДЛЯ'/
	 *' ДИАМЕТРОВ ВЕРШИН ШЕСТЕРНИ',2X,F7.2,' MM  И ',
	 *' КОЛЕСА',2X,F7.2,' MM.'//
	 *' В ТАБЛИЦЕ ПАРАМЕТРОВ УКАЗАТЬ ОБОЗНАЧЕНИЯ ПАРАМЕТРОВ')
C
	  IF(BET.NE.0) WRITE(3,142)
  142 FORMAT(' И НАПРАВЛЕНИЕ ЛИНИИ ЗУБА.')
	  WRITE(3,140)
C------------------------------------------------------------
	write (8,1002) M
1002	format (' MN = ',F6.2)

	write (8,1004) Z(2)
1004	format (' Z2 = ',F6.0)

	write (8,1005) BET
1005	format (' BE = ',F10.7)

	write (8,1008) X(2)
1008	format (' X2 = ',F6.3)

C--------------- Степень точности (IST) ---------------------
	if (KST(1).eq.KST(2).and.KST(1).eq.KST(3)) then
		write (STR6,'(I2)') KST(1)
		j=1
		do i=1,6
		if(str6(i:i).ne.' ') then
		 STR(j:j)=STR6(i:i)
		 j=j+1
		end if
		end do
		str(j:j)='-'
		str(j+1:j+2)=KTS(3:4)
	else
		j=1
		do ii=1,3
		write (STR6,'(I2)') KST(ii)
		do i=1,6
		if(str6(i:i).ne.' ') then
		 STR(j:j)=STR6(i:i)
		 j=j+1
		end if
		end do
		str(j:j)='-'
		end do
		 STR(j+1:j+2)=KTS(3:4)
	end if
	write (8,1011) STR
1011	format (' IST = ',A30)

C---------------- Показания тангенциального зубомера (DLTH2) -----
	j=1
	str='░'
	if( DLTHMN(2).gt.0) then
	 j=j+1
	 str(j:j)='+'
	end if

	write(str6,'(F6.3)') DLTHMN(2)
	do i=2,6
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.' ')str6(i-1:i-1)='0'
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.'-') then
			str6(i-1:i-1)='0'
			str6(i-2:i-2)='-'
	end if
	end do
	j=j+1
	do i=1,6
	if(str6(i:i).ne.' ') then
	 STR(j:j)=STR6(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='▒'

	if( DLTHMX(2).gt.0) then
	 j=j+1
	 str(j:j)='+'
	end if

	write(str6,'(F6.3)') DLTHMX(2)
	do i=2,6
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.' ')str6(i-1:i-1)='0'
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.'-') then
			str6(i-1:i-1)='0'
			str6(i-2:i-2)='-'
	end if
	end do
	j=j+1
	do i=1,6
	if(str6(i:i).ne.' ') then
	 STR(j:j)=STR6(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='▓'

	do i=1,30
	if(str(i:i).eq.'.') str(i:i)=','
	end do
	write (8,1022) str
1022	format (' DLTH2 = ',A30)

C---------------- Длина общей нормали (W2) ----------------------
	str=' '
	j=1
	write(str7,'(F7.2)') W(2)
	do i=1,7
	if(str7(i:i).ne.' ') then
	 STR(j:j)=STR7(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='░'
	if( EWS1(2).gt.0) then
	 j=j+1
	 str(j:j)='+'
	end if
	write(str6,'(F6.3)') EWS1(2)
	do i=2,6
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.' ')str6(i-1:i-1)='0'
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.'-') then
			str6(i-1:i-1)='0'
			str6(i-2:i-2)='-'
	end if
	end do
	j=j+1
	do i=1,6
	if(str6(i:i).ne.' ') then
	 STR(j:j)=STR6(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='▒'

	if( EWSTW(2).gt.0) then
	 j=j+1
	 str(j:j)='+'
	end if
	write(str6,'(F6.3)') EWSTW(2)
	do i=2,6
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.' ')str6(i-1:i-1)='0'
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.'-') then
			str6(i-1:i-1)='0'
			str6(i-2:i-2)='-'
	end if
	end do
	j=j+1
	do i=1,6
	if(str6(i:i).ne.' ') then
	 STR(j:j)=STR6(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='▓'

	do i=1,30
	if(str(i:i).eq.'.') str(i:i)=','
	end do

	write (8,1023) str
1023	format (' W2 = ',A30)

C---------------- Постоянная хорда (SC2) ----------------------
	STR=' '
	j=1
	write(str6,'(F6.3)') SC(2)
	do i=2,6
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.' ')str6(i-1:i-1)='0'
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.'-') then
			str6(i-1:i-1)='0'
			str6(i-2:i-2)='-'
	end if
	end do
	do i=1,6
	if(str6(i:i).ne.' ') then
	 STR(j:j)=STR6(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='░'
	if( ECS(2).gt.0) then
	 j=j+1
	 str(j:j)='+'
	end if
	write(str6,'(F6.3)') ECS(2)
	do i=2,6
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.' ')str6(i-1:i-1)='0'
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.'-') then
			str6(i-1:i-1)='0'
			str6(i-2:i-2)='-'
	end if
	end do
	j=j+1
	do i=1,6
	if(str6(i:i).ne.' ') then
	 STR(j:j)=STR6(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='▒'

	if( ECSTC(2).gt.0) then
	 j=j+1
	 str(j:j)='+'
	end if
	write(str6,'(F6.3)') ECSTC(2)
	do i=2,6
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.' ')str6(i-1:i-1)='0'
	if(str6(i:i).eq.'.'.AND.str6(i-1:i-1).eq.'-') then
			str6(i-1:i-1)='0'
			str6(i-2:i-2)='-'
	end if
	end do
	j=j+1
	do i=1,6
	if(str6(i:i).ne.' ') then
	 STR(j:j)=STR6(i:i)
	 j=j+1
	end if
	end do
	str(j:j)='▓'

	do i=1,30
	if(str(i:i).eq.'.') str(i:i)=','
	end do

	write (8,1024) str
1024	format (' SC2 = ',A30)
C---------------------------------------------------------
	write (8,1025) D(2)
1025	format (' D2 = ',F7.2)

	write (8,1026) HZ
1026	format (' H2 = ',F7.2)

	  RETURN
	  END


*/
