#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <corecrt.h>
#include <string>

using namespace std;

extern char IR[20];

extern int IT, IRV, IPR, IE, ISR, IN, N1R;
extern float L, WH;      // ресурс, часов
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