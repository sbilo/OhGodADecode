// Copyright (c) 2017 OhGodACompany - OhGodAGirl & OhGodAPet

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "ohgodadecode.h"
const float version=1.01;
// Parameter len is the size in bytes of asciistr, meaning rawstr
// must have (len >> 1) bytes allocated
// Maybe asciistr just NULL terminated?
// Returns length of rawstr in bytes
int ASCIIHexToBinary(void *rawstr, const char *asciistr, size_t len)
{
	for(int i=0, j = 0; i < len; ++i)
	{
		char tmp=asciistr[i];
		if(tmp < 'A') tmp -= '0';
		else if(tmp < 'a') tmp=(tmp - 'A') + 10;
		else tmp=(tmp - 'a') + 10;
		
		if(i & 1) ((uint8_t *)rawstr)[j++] |= tmp & 0x0F;
		else ((uint8_t *)rawstr)[j]=tmp << 4;
	}
	
	return(len >> 1);
}

#ifdef STRAP_R9
#define VBIOS_STRAP VBIOS_STRAP_R9
#else
#define VBIOS_STRAP VBIOS_STRAP_RX
#endif

int main(int argc, char **argv)
{
	uint32_t buf[12];
	VBIOS_STRAP *Timings=(VBIOS_STRAP*)buf;
		
	// Short circuited logic should prevent a segfault.
	if(argc != 2 || strlen(argv[1]) != 96)
	{
		printf("OhGodADecode v%.02f\n", version);
		printf("Usage: %s <96-char hex string>\n", argv[0]);
		return(1);
	}
	
	ASCIIHexToBinary(buf, argv[1], 96);

#ifdef DEBUG
    printf("Timings = %d bytes.\n", sizeof(*Timings));
#endif
		
	printf("MC_SEQ_RAS_TIMING: 0x%08X\n", Timings->SEQ_RAS_TIMING);
	printf("TRCDW=%d ", Timings->SEQ_RAS_TIMING.TRCDW);
	printf("TRCDWA=%d ", Timings->SEQ_RAS_TIMING.TRCDWA);
	printf("TRCDR=%d ", Timings->SEQ_RAS_TIMING.TRCDR);
	printf("TRCDRA=%d ", Timings->SEQ_RAS_TIMING.TRCDRA);
	printf("TRRD=%d ", Timings->SEQ_RAS_TIMING.TRRD);
	printf("TRC=%d ", Timings->SEQ_RAS_TIMING.TRC);
	printf("Pad0=%d\n\n", Timings->SEQ_RAS_TIMING.Pad0);
	
	printf("MC_SEQ_CAS_TIMING: 0x%08X\n", Timings->SEQ_CAS_TIMING);
	printf("TNOPW=%d ", Timings->SEQ_CAS_TIMING.TNOPW);
	printf("TNOPR=%d ", Timings->SEQ_CAS_TIMING.TNOPR);
	printf("TR2W=%d ", Timings->SEQ_CAS_TIMING.TR2W);
	printf("TCCDL=%d ", Timings->SEQ_CAS_TIMING.TCCDL);
	printf("TCCDS=%d ", Timings->SEQ_CAS_TIMING.TCCDS);
	printf("TW2R=%d ", Timings->SEQ_CAS_TIMING.TW2R);
	printf("Pad0=%d ", Timings->SEQ_CAS_TIMING.Pad0);
	printf("TCL=%d ", Timings->SEQ_CAS_TIMING.TCL);
	printf("Pad1=%d\n\n", Timings->SEQ_CAS_TIMING.Pad1);
	
	printf("MC_SEQ_MISC_TIMING: 0x%08X\n", Timings->SEQ_MISC_TIMING);
	printf("TRP_WRA=%d ", Timings->SEQ_MISC_TIMING.TRP_WRA);
	printf("TRP_RDA=%d ", Timings->SEQ_MISC_TIMING.TRP_RDA);
	printf("TRP=%d ", Timings->SEQ_MISC_TIMING.TRP);
	printf("TRFC=%d ", Timings->SEQ_MISC_TIMING.TRFC);
	printf("Pad0=%d \n\n", Timings->SEQ_MISC_TIMING.Pad0);
	
	printf("MC_SEQ_MISC_TIMING2: 0x%08X\n", Timings->SEQ_MISC_TIMING2);
	printf("PA2RDATA=%d ", Timings->SEQ_MISC_TIMING2.PA2RDATA);
	printf("Pad0=%d ", Timings->SEQ_MISC_TIMING2.Pad0);
	printf("PA2WDATA=%d ", Timings->SEQ_MISC_TIMING2.PA2WDATA);
	printf("Pad1=%d ", Timings->SEQ_MISC_TIMING2.Pad1);
	printf("TFAW=%d ", Timings->SEQ_MISC_TIMING2.TFAW);
	printf("TCRCRL=%d ", Timings->SEQ_MISC_TIMING2.TCRCRL);
	printf("TCRCWL=%d ", Timings->SEQ_MISC_TIMING2.TCRCWL);
	printf("T32AW=%d\n\n", Timings->SEQ_MISC_TIMING2.T32AW);
	
	printf("MC_SEQ_PMG_TIMING: 0x%08X\n", Timings->SEQ_PMG_TIMING);
	printf("MC_SEQ_MISC1 (MR1/MR0): 0x%08X\n", Timings->SEQ_MISC1);
	printf("MC_SEQ_MISC3: (MR5/MR4)0x%08X\n", Timings->SEQ_MISC3);
	printf("MC_SEQ_MISC8: 0x%08X\n\n", Timings->SEQ_MISC8);
	
	printf("MC_ARB_DRAM_TIMING: 0x%08X\n", Timings->ARB_DRAM_TIMING);
	printf("ACTRD=%d ", Timings->ARB_DRAM_TIMING.ACTRD);
	printf("ACTWR=%d ", Timings->ARB_DRAM_TIMING.ACTWR);
	printf("RASMACTRD=%d ", Timings->ARB_DRAM_TIMING.RASMACTRD);
	printf("RASMACTWR=%d\n\n", Timings->ARB_DRAM_TIMING.RASMACTWR);
	
	printf("MC_ARB_DRAM_TIMING2: 0x%08X\n", Timings->ARB_DRAM_TIMING2);
	printf("RAS2RAS=%d ", Timings->ARB_DRAM_TIMING2.RAS2RAS);
	printf("RP=%d " , Timings->ARB_DRAM_TIMING2.RP);
	printf("WRPLUSRP=%d ", Timings->ARB_DRAM_TIMING2.WRPLUSRP);
	printf("BUS_TURN=%d\n\n", Timings->ARB_DRAM_TIMING2.BUS_TURN);
	
	return(0);
}
