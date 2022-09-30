#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>

using namespace std;

extern fstream f_2;    // файл исходных данных для ступеней //***

//========== Переменные по ступени
extern int IVP;                             // тип ступени
extern float Z1, Z2;                          // числа зубьев шестерни и колеса
extern float MN, BE, X1, X2;                // модуль, угол наклона, коэффициенты смещения
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

//extern int IS;

void  DSR() 
{
    string str;
    char ch = ' ';
    int i = 0;
    //fstream fi;

    cout << "DSR" << endl;
    
    //fi.open("FILE2", fstream::in);
    /*
    if (IS == 1) {
        getline(f_2, str);  // пропустить строку
        cout << str << endl;
        getline(f_2, str);  // пропустить строку
        cout << str << endl;

        f_2 >> IVP;
    }
    */
    cout << "DSR: IVP = " << IVP << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> Z1 >> Z2 >> MN >> BE;
    cout << "      " << Z1 << "      " << Z2 << "      " << MN << "      " << BE << endl;
    
    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> flaw >> AW >> X1 >> X2 >> B1 >> B2 >> AL >> HA >> HL >> CZV;
    cout << "     " << flaw << "   " << AW << "  " << X1 << "     " << X2 << "      " << B1;
    cout << "      " << B2 << "     " << AL << "      " << HA << "     " << HL << "    " << CZV << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> IMD >> IST1 >> IST2 >> IST3 >> IST4 >> IST5;
    cout << "      " << IMD << "      " << IST1 << "       " << IST2 << "       " << IST3 << "       " << IST4 << "       " << IST5 << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> IKG;
    cout << "      " << IKG << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> CZ1 >> CZ2 >> GM >> IVR >> PR >> KPD >> KSP;
    cout << "      " << CZ1 << "      " << CZ2 << "        " << GM << "      " << IVR << "     " << PR << "    " << KPD << "     " << KSP << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> SHLM1 >> SHPM1 >>SFLB1>> SFPM1;
    cout << "      " << SHLM1 << "       " << SHPM1 << "        " << SFLB1 << "        " << SFPM1  << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> IG1 >> H1 >> HK1 >> HT1 >> SHER1 >> YZ1 >> YT1 >> YR1 >> IMF1 >> SHV1;
    cout << "      " << IG1 << "       " << H1 << "     " << HK1 << "      " << HT1 << "    " << SHER1 << "      " << YZ1 << "       " << YT1 << "       " << YR1 << "     " << IMF1 << "     " << SHV1 << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> SHLM2 >> SHPM2 >> SFLB2 >> SFPM2;
    cout << "      " << SHLM2 << "       " << SHPM2 << "        " << SFLB2 << "        " << SFPM2 << endl;

    getline(f_2, str);  // пропустить строку
    getline(f_2, str);  // пропустить строку
    cout << str << endl;

    f_2 >> IG2 >> H2 >> HK2 >> HT2 >> SHER2 >> YZ2 >> YT2 >> YR2 >> IMF2 >> SHV2;
    cout << "      " << IG2 << "       " << H2 << "     " << HK2 << "      " << HT2 << "    " << SHER2 << "      " << YZ2 << "       " << YT2 << "       " << YR2 << "     " << IMF2 << "     " << SHV2 << endl;


    f_2.close(); // закрываем файл
};

/*
SUBROUTINE DSR(JJ, IR, L, IS, ISR, IPR, Z1, Z2, MN, BE, X1, X2,
    *AW, B1, B2, AL, HA, HL, CZV, IMD, IST1, IST2, IST3, IST4, IST5,
    *IKG, FKE, IZ1, IG,
    *IQ, IP, LO, S1, CZ1, CZ2, GM, IVR, PR, KPD, KSP,
    *SHLM1, SHLM2, SHPM1, SHPM2, SFLB1, SFLB2, SFPM1, SFPM2,
    *IG1, H1, HK1, HT1, SHER1, YZ1, YT1, YR1, IMF1, SHV1,
    *IG2, H2, HK2, HT2, SHER2, YZ2, YT2, YR2, IMF2, SHV2)
    C  СЧИТЫВАНИЕ ИСХОДНЫХ ДАННЫХ РЕДУКТОРА В ЦИКЛЕ ПО СТУПЕНЯМ
    C  ИЗ FILE 'B1' В ОПЕРАТИВНУЮ ПАМЯТЬ
    REAL L
    REAL LO
    REAL KPD
    REAL KSP
    REAL MN
    CHARACTER * 65 A
    CHARACTER * 16 IR
    SAVE
    READ(2, 100) A
    READ(2, *) Z1, Z2, MN, BE
    READ(2, 100) A
    READ(2, *) iissmm, AW, X1, X2, B1, B2, AL, HA, HL, CZV

    C	B2 = B1
    C	AL = 20.
    C	HL = 1. + HA
    C	CZV = 0.25
    C      IF(X1.GT.10.) THEN
    C      AW = X1
    C	X1 = -5.
    C	X2 = -5.
    C       ELSE
    C      AW = 0.
    C        END IF
    READ(2, 100) A
    READ(2, *) IMD, IST1, IST2, IST3, IST4, IST5

    IF(L.EQ.0.) GOTO 12
    READ(2, 100) A
    READ(2, *) IKG
    IF(IKG.EQ.0.OR.IKG.EQ.10) READ(2, 100) A
    IF(IKG.EQ.0) READ(2, *) FKE, IZ1
    IF(IKG.EQ.10) READ(2, *) IG, IQ, IP, LO, S1
    READ(2, 100) A
    READ(2, *) CZ1, CZ2, GM, IVR, PR, KPD, KSP
    READ(2, 100) A
    READ(2, *) SHLM1, SHPM1, SFLB1, SFPM1
    READ(2, 100) A
    READ(2, *) IG1, H1, HK1, HT1, SHER1, YZ1, YT1, YR1, IMF1, SHV1
    READ(2, 100) A
    READ(2, *) SHLM2, SHPM2, SFLB2, SFPM2
    READ(2, 100) A
    READ(2, *) IG2, H2, HK2, HT2, SHER2, YZ2, YT2, YR2, IMF2, SHV2
    100 FORMAT(A65)
    12  RETURN
    END

*/