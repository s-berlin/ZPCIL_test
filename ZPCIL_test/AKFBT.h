#include <iostream>
#include <math.h>

using namespace std;

float AKFBT(int KC, float PSIBD, int KH) {
    float AB[2][14] = { .5184, 1.233, .893, 1.333, .35, .89, .437, .524,
     .241, .428, .08, .148, .2, .133, .02, .264, .041, .067, .12, .222, .015, .02, .075, .2, .033, .035, .04, .075 };

    int J = (KC - 1) * 2 + 1;
    float akfbt = 1. + AB[KH - 1][J - 1] * PSIBD + AB[KH - 1][J] * pow(PSIBD, 2);
    return akfbt;

}

/*
      FUNCTION AKFBT(KC,PSIBD,KH)
C     KH=1 - �p�p�����������, 2 - �� �p�p�����������

      DIMENSION AB(2,14)
    SAVE
      DATA AB/.5184,1.233,.893,1.333,.35,.89,.437,.524,
     *.241,.428,.08,.148,.2,.133,.02,.264,.041,.067,
     *.12,.222,.015,.02,.075,.2,.033,.035,.04,.075/
      J=(KC-1)*2+1
      AKFBT=1.+AB(KH,J)*PSIBD+AB(KH,J+1)*(PSIBD**2)
      RETURN
      END
*/