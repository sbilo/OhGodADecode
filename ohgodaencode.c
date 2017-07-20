// Copyright (c) 2017 OhGodACompany - OhGodAGirl & OhGodAPet

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <libconfig.h>

#include "ohgodaencode.h"
const float version=1.01;

// see https://stackoverflow.com/a/10599161
void ASCIIBinaryToHex(char *result, const uint8_t *data, size_t len)
{
	size_t j = 0;
	for(; j < len; ++j)
	    //sprintf(&result[2*j], "%02X", data[j]);
	    printf("%02X", data[j]);
	result[j] = 0;
	
	printf("\n");
}

#ifdef STRAP_R9
#define VBIOS_STRAP VBIOS_STRAP_R9
#else
#define VBIOS_STRAP VBIOS_STRAP_RX
#endif

#define READ_CFG_VAL(GROUP, KEY) \
	if(config_lookup_int(&cfg, #KEY, &tmp)) \
		Timings->GROUP.KEY = tmp;

int main(int argc, char **argv)
{
	uint32_t buf[12];
	VBIOS_STRAP *Timings=(VBIOS_STRAP*)buf;
	
	memset(buf, 0, 96);

	buf[0] = 0x00007077;
	buf[2] = 0x009D3322;

	Timings->SEQ_RAS_TIMING.TRCDW = 14;
	Timings->SEQ_RAS_TIMING.TRCDWA = 14;
	Timings->SEQ_RAS_TIMING.TRCDR = 20;
	Timings->SEQ_RAS_TIMING.TRCDRA = 20;
	Timings->SEQ_RAS_TIMING.TRRD = 6;
	Timings->SEQ_RAS_TIMING.TRC = 61;
	Timings->SEQ_RAS_TIMING.Pad0 = 0;
	
	Timings->SEQ_CAS_TIMING.TNOPW = 0;
	Timings->SEQ_CAS_TIMING.TNOPR = 0;
	Timings->SEQ_CAS_TIMING.TR2W = 25;
	Timings->SEQ_CAS_TIMING.TCCDL = 2;
	Timings->SEQ_CAS_TIMING.TR2R = 5;
	Timings->SEQ_CAS_TIMING.TW2R = 17;
	Timings->SEQ_CAS_TIMING.Pad0 = 0;
	Timings->SEQ_CAS_TIMING.TCL = 18;
	Timings->SEQ_CAS_TIMING.Pad1 = 0;
	
	Timings->SEQ_MISC_TIMING.TRP_WRA = 48;
	Timings->SEQ_MISC_TIMING.TRP_RDA = 22;
	Timings->SEQ_MISC_TIMING.TRP = 19;
	Timings->SEQ_MISC_TIMING.TRFC = 148;
	Timings->SEQ_MISC_TIMING.Pad0 = 0;
	
	Timings->SEQ_MISC_TIMING2.PA2RDATA = 0;
	Timings->SEQ_MISC_TIMING2.Pad0 = 0;
	Timings->SEQ_MISC_TIMING2.PA2WDATA = 0;
	Timings->SEQ_MISC_TIMING2.Pad1 = 0;
	Timings->SEQ_MISC_TIMING2.TFAW = 10;
	Timings->SEQ_MISC_TIMING2.TCRCRL = 2;
	Timings->SEQ_MISC_TIMING2.TCRCWL = 6;
	Timings->SEQ_MISC_TIMING2.TFAW32 = 7;
	
	Timings->SEQ_MISC1 = 0x20140174;
	Timings->SEQ_MISC3 = 0xA000896A;
	Timings->SEQ_MISC8 = 0x20310002;
	
	Timings->ARB_DRAM_TIMING.ACTRD = 21;
	Timings->ARB_DRAM_TIMING.ACTWR = 15;
	Timings->ARB_DRAM_TIMING.RASMACTRD = 41;
	Timings->ARB_DRAM_TIMING.RASMACTWR = 47;

	Timings->ARB_DRAM_TIMING2.RAS2RAS = 148;
	Timings->ARB_DRAM_TIMING2.RP = 39;
	Timings->ARB_DRAM_TIMING2.WRPLUSRP = 49;
	Timings->ARB_DRAM_TIMING2.BUS_TURN = 22;
	
	// init config reader
	config_t cfg;
	config_setting_t *setting;
	config_init(&cfg);

	/* Read the file. If there is an error, report it and exit. */
	if(!config_read_file(&cfg, "timings.cfg"))
	{
	    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
	            config_error_line(&cfg), config_error_text(&cfg));
    	config_destroy(&cfg);
    	return(-1);
	}

	// read config
	int tmp;
	READ_CFG_VAL(SEQ_RAS_TIMING, TRCDW);
	READ_CFG_VAL(SEQ_RAS_TIMING, TRCDWA);
	READ_CFG_VAL(SEQ_RAS_TIMING, TRCDR);
	READ_CFG_VAL(SEQ_RAS_TIMING, TRCDRA);
	READ_CFG_VAL(SEQ_RAS_TIMING, TRRD);
	READ_CFG_VAL(SEQ_RAS_TIMING, TRC);
	
	READ_CFG_VAL(SEQ_CAS_TIMING, TNOPW);
	READ_CFG_VAL(SEQ_CAS_TIMING, TNOPR);
	READ_CFG_VAL(SEQ_CAS_TIMING, TR2W);
	READ_CFG_VAL(SEQ_CAS_TIMING, TCCDL);
	READ_CFG_VAL(SEQ_CAS_TIMING, TR2R);
	READ_CFG_VAL(SEQ_CAS_TIMING, TW2R);
	READ_CFG_VAL(SEQ_CAS_TIMING, TCL);
	
	READ_CFG_VAL(SEQ_MISC_TIMING, TRP_WRA);
	READ_CFG_VAL(SEQ_MISC_TIMING, TRP_RDA);
	READ_CFG_VAL(SEQ_MISC_TIMING, TRP);
	READ_CFG_VAL(SEQ_MISC_TIMING, TRFC);
	
	READ_CFG_VAL(SEQ_MISC_TIMING2, PA2RDATA);
	READ_CFG_VAL(SEQ_MISC_TIMING2, PA2WDATA);
	READ_CFG_VAL(SEQ_MISC_TIMING2, TFAW);
	READ_CFG_VAL(SEQ_MISC_TIMING2, TCRCRL);
	READ_CFG_VAL(SEQ_MISC_TIMING2, TCRCWL);
	READ_CFG_VAL(SEQ_MISC_TIMING2, TFAW32);
	
	READ_CFG_VAL(ARB_DRAM_TIMING, ACTRD);
	READ_CFG_VAL(ARB_DRAM_TIMING, ACTWR);
	READ_CFG_VAL(ARB_DRAM_TIMING, RASMACTRD);
	READ_CFG_VAL(ARB_DRAM_TIMING, RASMACTWR);

	READ_CFG_VAL(ARB_DRAM_TIMING2, RAS2RAS);
	READ_CFG_VAL(ARB_DRAM_TIMING2, RP);
	READ_CFG_VAL(ARB_DRAM_TIMING2, WRPLUSRP);
	READ_CFG_VAL(ARB_DRAM_TIMING2, BUS_TURN);
	
	config_destroy(&cfg);

	// print timings
	printf("TRCDW=%d ", Timings->SEQ_RAS_TIMING.TRCDW);
	printf("TRCDWA=%d ", Timings->SEQ_RAS_TIMING.TRCDWA);
	printf("TRCDR=%d ", Timings->SEQ_RAS_TIMING.TRCDR);
	printf("TRCDRA=%d ", Timings->SEQ_RAS_TIMING.TRCDRA);
	printf("TRRD=%d ", Timings->SEQ_RAS_TIMING.TRRD);
	printf("TRC=%d ", Timings->SEQ_RAS_TIMING.TRC);
	printf("Pad0=%d\n\n", Timings->SEQ_RAS_TIMING.Pad0);
	
	printf("TNOPW=%d ", Timings->SEQ_CAS_TIMING.TNOPW);
	printf("TNOPR=%d ", Timings->SEQ_CAS_TIMING.TNOPR);
	printf("TR2W=%d ", Timings->SEQ_CAS_TIMING.TR2W);
	printf("TCCDL=%d ", Timings->SEQ_CAS_TIMING.TCCDL);
	printf("TR2R=%d ", Timings->SEQ_CAS_TIMING.TR2R);
	printf("TW2R=%d ", Timings->SEQ_CAS_TIMING.TW2R);
	printf("Pad0=%d ", Timings->SEQ_CAS_TIMING.Pad0);
	printf("TCL=%d ", Timings->SEQ_CAS_TIMING.TCL);
	printf("Pad1=%d\n\n", Timings->SEQ_CAS_TIMING.Pad1);
	
	printf("TRP_WRA=%d ", Timings->SEQ_MISC_TIMING.TRP_WRA);
	printf("TRP_RDA=%d ", Timings->SEQ_MISC_TIMING.TRP_RDA);
	printf("TRP=%d ", Timings->SEQ_MISC_TIMING.TRP);
	printf("TRFC=%d ", Timings->SEQ_MISC_TIMING.TRFC);
	printf("Pad0=%d \n\n", Timings->SEQ_MISC_TIMING.Pad0);
	
	printf("PA2RDATA=%d ", Timings->SEQ_MISC_TIMING2.PA2RDATA);
	printf("Pad0=%d ", Timings->SEQ_MISC_TIMING2.Pad0);
	printf("PA2WDATA=%d ", Timings->SEQ_MISC_TIMING2.PA2WDATA);
	printf("Pad1=%d ", Timings->SEQ_MISC_TIMING2.Pad1);
	printf("TFAW=%d ", Timings->SEQ_MISC_TIMING2.TFAW);
	printf("TCRCRL=%d ", Timings->SEQ_MISC_TIMING2.TCRCRL);
	printf("TCRCWL=%d ", Timings->SEQ_MISC_TIMING2.TCRCWL);
	printf("TFAW32=%d\n\n", Timings->SEQ_MISC_TIMING2.TFAW32);
	
	printf("MC_SEQ_MISC1: 0x%08X\n", Timings->SEQ_MISC1);
	printf("MC_SEQ_MISC3: 0x%08X\n", Timings->SEQ_MISC3);
	printf("MC_SEQ_MISC8: 0x%08X\n\n", Timings->SEQ_MISC8);
	
	printf("ACTRD=%d ", Timings->ARB_DRAM_TIMING.ACTRD);
	printf("ACTWR=%d ", Timings->ARB_DRAM_TIMING.ACTWR);
	printf("RASMACTRD=%d ", Timings->ARB_DRAM_TIMING.RASMACTRD);
	printf("RASMACTWR=%d\n\n", Timings->ARB_DRAM_TIMING.RASMACTWR);
	
	printf("RAS2RAS=%d ", Timings->ARB_DRAM_TIMING2.RAS2RAS);
	printf("RP=%d " , Timings->ARB_DRAM_TIMING2.RP);
	printf("WRPLUSRP=%d ", Timings->ARB_DRAM_TIMING2.WRPLUSRP);
	printf("BUS_TURN=%d\n\n", Timings->ARB_DRAM_TIMING2.BUS_TURN);

	// print results
	char hex[97];
	ASCIIBinaryToHex(hex, buf, 48);
	
	return(0);
}
