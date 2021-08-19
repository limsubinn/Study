/*
 * 0529.c
 *
 *  Created on: 2019. 5. 29.
 *      Author: user
 */
#include "sleep.h"
#include "xtime_l.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "xscugic.h"

#define INTC_DEVICE_ID 			XPAR_PS7_SCUGIC_0_DEVICE_ID

#define LEDS_DEVICE_ID			XPAR_GPIO_LED_DEVICE_ID

#define BTNS_DEVICE_ID			XPAR_GPIO_BTN_DEVICE_ID
#define INTC_GPIO_INTERRUPT_ID 	XPAR_FABRIC_GPIO_BTN_IP2INTC_IRPT_INTR


/* Bit definitions for the interrupt status register and interrupt enable registers.*/
/* Mask for the 1st channel */
#define BTN_INT 				XGPIO_IR_CH1_MASK



XScuGic INTCInst;

XGpio LEDInst, BTNInst;


static int InterruptSystemSetup(XScuGic *XScuGicInstancePtr);
static int IntcInitFunction(u16 DeviceId, XGpio *GpioInstancePtr);

static int BTN_Intr_Handler(void *baseaddr_p);


int interrupt=0;

XTime tCur,tEnd;

int main (void)
{
	  XGpio switches;
	  int switches_check;

	  xil_printf("-- Start of the Program -- \r\n");

	  XGpio_Initialize(&switches, XPAR_GPIO_DIP_SW_DEVICE_ID);
	  XGpio_SetDataDirection(&switches,1,0xff);

	  int status;

	  status = XGpio_Initialize(&LEDInst, LEDS_DEVICE_ID); //LED �ʱ�ȭ
	  if(status != XST_SUCCESS) return XST_FAILURE;
	  XGpio_SetDataDirection(&LEDInst, 1, 0x00); //LED�� ������� ����

	  status = XGpio_Initialize(&BTNInst, BTNS_DEVICE_ID); //BTN �ʱ�ȭ
	  if(status != XST_SUCCESS) return XST_FAILURE;
	  XGpio_SetDataDirection(&BTNInst, 1, 0xFF); //BTN�� �Է����� ����

	  status = IntcInitFunction(INTC_DEVICE_ID, &BTNInst);
	  if(status != XST_SUCCESS) return XST_FAILURE;

	  while(1)
	  {

	  xil_printf("START \r\n");

	  XTime_GetTime(&tCur);

	  while(1)
	  {
		  switches_check = XGpio_DiscreteRead(&switches,1);

		  if (switches_check == 0)
		  {
			  xil_printf("OK  %x\r\n", switches_check);
			  while (1) {
				  switches_check = XGpio_DiscreteRead(&switches,1);
				  if (switches_check == 1) break;
			  }
			  XGpio_DiscreteWrite(&LEDInst,1,switches_check);

			  if (switches_check == 1)
			  {
				    xil_printf("OK  %x\r\n", switches_check);
			     	while (1) {
			     		switches_check = XGpio_DiscreteRead(&switches,1);
			     		if (switches_check == 2) break;
			  		}
			  		XGpio_DiscreteWrite(&LEDInst,1,switches_check);

			  		if (switches_check == 2)
			  		{
			  			     xil_printf("OK  %x\r\n", switches_check);
			  				 while (1) {
			  					switches_check = XGpio_DiscreteRead(&switches,1);
			  					if (switches_check == 3) break;
			  		         }
			  				 XGpio_DiscreteWrite(&LEDInst,1,switches_check);

			  				 if (switches_check == 3)
			  				 {
			  					 xil_printf("OK  %x\r\n", switches_check);
			  					 XGpio_DiscreteWrite(&LEDInst,1,switches_check);
			  					 while (1) {
			  						 //switches_check = XGpio_DiscreteRead(&switches,1);

			  						 if (interrupt)
			  						 {
			  									 XTime_GetTime(&tEnd);
			  									 break;
			  						 }




			  					 }

			  				 }

			  		}
			  }
		  }
		  else if (interrupt) break;
	  }
	  xil_printf("     response time %u \n", (tEnd-tCur)*1000);
	  interrupt=0;

	  }
}



int InterruptSystemSetup(XScuGic *XScuGicInstancePtr)
{
	// Enable interrupt
	XGpio_InterruptEnable(&BTNInst, XPAR_FABRIC_GPIO_BTN_IP2INTC_IRPT_INTR);
	XGpio_InterruptGlobalEnable(&BTNInst); //��ġ ���ͷ�Ʈ ��� enable

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
	 	 		 XScuGicInstancePtr); //���ͷ�Ʈ �߻��ϸ� ȣ���� ��ġ ����̹� �ڵ鷯 ����

	Xil_ExceptionEnable(); //��ġ ����̹� �ڵ鷯 ó��


	return XST_SUCCESS;

}

int IntcInitFunction(u16 DeviceId, XGpio *GpioInstancePtr)
{
	XScuGic_Config *IntcConfig;
	int status;

	// Interrupt controller initialization
	IntcConfig = XScuGic_LookupConfig(DeviceId); //DeviceId�� ������� ��ġ ���� ã��
	status = XScuGic_CfgInitialize(&INTCInst, IntcConfig, IntcConfig->CpuBaseAddress); //���ͷ�Ʈ ��Ʈ�ѷ� ����̹� �ʱ�ȭ
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Call to interrupt setup
	status = InterruptSystemSetup(&INTCInst);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Connect GPIO interrupt to handler
	status = XScuGic_Connect(&INTCInst,
					  	  	 INTC_GPIO_INTERRUPT_ID,
					  	  	 (Xil_ExceptionHandler)BTN_Intr_Handler,
					  	  	 (void *)GpioInstancePtr); //GPIO�� ���� ���ͷ�Ʈ�� �߻��� �� ȣ��� ��ġ ����̹� �ڵ鷯 ����
	if(status != XST_SUCCESS) return XST_FAILURE;


	// Enable GPIO interrupts interrupt
	XGpio_InterruptEnable(GpioInstancePtr, 1);
	XGpio_InterruptGlobalEnable(GpioInstancePtr);

	// Enable GPIO interrupts in the controller
	XScuGic_Enable(&INTCInst, INTC_GPIO_INTERRUPT_ID);

	return XST_SUCCESS;
}

int BTN_Intr_Handler(void *InstancePtr)
{

	// Disable GPIO interrupts
	XGpio_InterruptDisable(&BTNInst, BTN_INT); //BTN�� ���� ���ͷ�Ʈ disable
	// Ignore additional button presses
	if ((XGpio_InterruptGetStatus(&BTNInst) & BTN_INT) != BTN_INT) {
		return;
	}

	interrupt=1;

    (void)XGpio_InterruptClear(&BTNInst, BTN_INT);
    // Enable GPIO interrupts
    XGpio_InterruptEnable(&BTNInst, BTN_INT); //BTN�� ���� ���ͷ�Ʈ enable
}
