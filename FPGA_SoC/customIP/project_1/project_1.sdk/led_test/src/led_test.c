/*
 * led_test.c
 *
 *  Created on: 2019. 5. 22.
 *      Author: user
 */

#include "xparameters.h"
#include "myip.h"
#include "xil_io.h"

#define REG_BASE XPAR_MYIP_0_S00_AXI_BASEADDR

int main(void)
{

	int reg=0;
	int state;

    xil_printf("----------------begin----------------\r\n\n");


    while(1){

    		state = MYIP_mReadReg(REG_BASE,  MYIP_S00_AXI_SLV_REG0_OFFSET);

			if (state==1)
				reg++;
			else
				reg--;


			xil_printf("Register Status : %x\r\n", reg);
			xil_printf("state Status : %x\r\n", state);

            MYIP_mWriteReg(REG_BASE, MYIP_S00_AXI_SLV_REG1_OFFSET, reg);

            sleep(1);
        }


    return 1;
}


