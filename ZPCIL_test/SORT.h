//extern int IT;
//extern float TQ[20], TC[20], RM[20];

void SORT(int IT1, float TQ1[100], float TC1[100], float RM1[100])
{
	int i, j, ITT, I1;
	if (IT1 == 1) return;
	ITT = IT1 - 1;
	for (i = 0; i < ITT - 1; i++) {
		I1 = i + 1;
		for (j = I1; j < IT1; j++) {
			if (TQ1[i] < TQ1[j]) {
				float A = TQ1[i];
				TQ1[i] = TQ1[j];
				TQ1[j] = A;
				A = TC1[i];
				TC1[i] = TC1[j];
				TC1[j] = A;
				A = RM1[i];
				RM1[i] = RM1[j];
				RM1[j] = A;
			}
		}
	}
	return;
}
/*
SUBROUTINE SORT(IT, TQ, TC, RM)
C     COPTiPOBKA MACCibOB TQ, TC, RM
REAL TQ(1), TC(1), RM(1), A
INTEGER IT, I, J, ITT, I1

IF(IT.EQ.1) RETURN
ITT = IT - 1
DO 20 I = 1, ITT
I1 = I + 1
DO 10 J = I1, IT
IF(TQ(I).GE.TQ(J)) GOTO 10
A = TQ(I)
TQ(I) = TQ(J)
TQ(J) = A
A = TC(I)
TC(I) = TC(J)
TC(J) = A
A = RM(I)
RM(I) = RM(J)
RM(J) = A
10    CONTINUE
20  CONTINUE
RETURN
END
*/
