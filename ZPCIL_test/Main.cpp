#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//#include <fstream>
//#include <corecrt.h>
#include "DRM.h"
#include "VYVDR.h"
//#include "VYVDR.h"
//#include "CILEV.h"

using namespace std;

char IR[20] = {};  // ������������� ������� 

int IT = 0, IRV = 0, IPR = 6, IE = 1, ISR = 1, IN = 0;
float L = 0, WH = 0;      // ������, �����
float T1R = 0, TMAX = 0;     // ������ �� �������� ����, ��
float TQ[20] = {}, TC[20] = {}, RM[20] = {};


int main()
{

    DRM();
	VYVDR();

	return(0);
}
