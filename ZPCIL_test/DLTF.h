#include <iostream>
#include <math.h>

using namespace std;

float DLTF(int MD, float BET) {
    // *** � ����� ������������ � 10 ��� ������!
    //     MD = 0 - ��� �����������
    float dltf = 0.006;
    if (BET == 0) {
        dltf = 0.016;
        if (MD != 0) dltf = 0.011;
    }
    return dltf;
}

/*
      FUNCTION DLTF(MD,BET)
C         SAVE
C     MD=0 - HET MOdifiKAcii
      DLTF=0.006
      IF(BET.NE.0) GO TO 20
      DLTF=0.016
      IF(MD.NE.0) DLTF=0.011
  20  RETURN
      END
*/
