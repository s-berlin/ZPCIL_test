#include <iostream>
#include <math.h>

using namespace std;

float SIGMAX(float SIG, float TQ, float TMAX, float KV, float KB, float KA, int IHF)
{
    float sigmax = 0;

    float K = KV * KB * KA;
    float KVM = 1.;
    float KBM = (KB - 1.) * TQ / TMAX + 1.;
    float KAM = (KA - 1.) * TQ / TMAX + 1.;
    float KM = KVM * KBM * KAM;
    float PRG = TMAX * KM / (TQ * K);
    if (IHF == 1) sigmax = SIG * sqrt(PRG);
    if (IHF == 2) sigmax = SIG * PRG;
    return sigmax;
}

/*
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                          C
C   SIGMAX- PAC~ET HApPqvEHij pPi MAKCiMAlxHOj HAgPuzKE    C
C                                                          C
C   BXOdHyE pAPAMETPy:                                     C
C                                                          C
C   SIG - iCXOdHOE PAC~ETHOE HApPqvEHiE                    C
C   TQ  - iCXOdHAq PAC~ETHAq HAgPuzKA                      C
C   TMAX- MAKCiMAlxHAq HAgPuzKA                            C
C   KV  - diHAMi~ECKij KO|f.                               C
C   KB  - KO|f. KABETA                                     C
C   KA  - KO|f. KAAlxfA                                    C
C   IHF - pPizHAK PAC~ETA:  1 - KOHTAKT, 2 - izgib         C
C                                                          C
C   ByXOdHOj pAPAMETP  -  SIGMAX                           C
C                                                          C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
      FUNCTION SIGMAX(SIG,TQ,TMAX,KV,KB,KA,IHF)
      REAL K,KA,KAM,KB,KBM,KV,KVM,KM
        SAVE
      K=KV*KB*KA
      KVM=1.
      KBM=(KB-1.)*TQ/TMAX+1.
      KAM=(KA-1.)*TQ/TMAX+1.
      KM=KVM*KBM*KAM
      PRG=TMAX*KM/(TQ*K)
      IF(IHF.EQ.1) SIGMAX=SIG*SQRT(PRG)
      IF(IHF.EQ.2) SIGMAX=SIG*PRG
      RETURN
      END

*/
