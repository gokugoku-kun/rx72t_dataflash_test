/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_PORT.c
* Component Version: 2.4.1
* Device(s)        : R5F572TFCxFP
* Description      : This file implements device driver for Config_PORT.
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_PORT.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_PORT_Create
* Description  : This function initializes the PORT
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_PORT_Create(void)
{
    /* Set PORT0 registers */
    PORT0.PODR.BYTE = _00_Pm1_OUTPUT_0;
    PORT0.ODR0.BYTE = _00_Pm1_CMOS_OUTPUT;
    PORT0.PCR.BYTE = _00_Pm0_PULLUP_OFF;
    PORT0.DSCR.BYTE = _00_Pm1_HIDRV_OFF;
    PORT0.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO;
    PORT0.PDR.BYTE = _00_Pm0_MODE_INPUT | _02_Pm1_MODE_OUTPUT;

    /* Set PORT1 registers */
    PORT1.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0;
    PORT1.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT;
    PORT1.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF;
    PORT1.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO;
    PORT1.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _FC_PDR1_DEFAULT;

    /* Set PORT2 registers */
    PORT2.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | 
                      _00_Pm7_OUTPUT_0;
    PORT2.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT2.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORT2.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm7_HIDRV_OFF;
    PORT2.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm7_PIN_GPIO;
    PORT2.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _80_Pm7_MODE_OUTPUT | _60_PDR2_DEFAULT;

    /* Set PORT3 registers */
    PORT3.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0;
    PORT3.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT3.ODR1.BYTE = _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORT3.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF;
    PORT3.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO;
    PORT3.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _30_PDR3_DEFAULT;

    /* Set PORT4 registers */
    PORT4.PODR.BYTE = _00_Pm3_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORT4.ODR0.BYTE = _00_Pm3_CMOS_OUTPUT;
    PORT4.ODR1.BYTE = _00_Pm7_CMOS_OUTPUT;
    PORT4.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO | _00_Pm7_PIN_GPIO;
    PORT4.PDR.BYTE = _00_Pm0_MODE_INPUT | _00_Pm1_MODE_INPUT | _00_Pm2_MODE_INPUT | _08_Pm3_MODE_OUTPUT | 
                     _00_Pm4_MODE_INPUT | _00_Pm5_MODE_INPUT | _00_Pm6_MODE_INPUT | _80_Pm7_MODE_OUTPUT;

    /* Set PORT5 registers */
    PORT5.PODR.BYTE = _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm5_OUTPUT_0;
    PORT5.ODR0.BYTE = _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT5.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT;
    PORT5.PMR.BYTE = _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO;
    PORT5.PDR.BYTE = _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | 
                     _03_PDR5_DEFAULT;

    /* Set PORT6 registers */
    PORT6.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | 
                      _00_Pm5_OUTPUT_0;
    PORT6.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT6.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT;
    PORT6.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO;
    PORT6.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT;

    /* Set PORT7 registers */
    PORT7.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | 
                      _00_Pm5_OUTPUT_0 | _00_Pm6_OUTPUT_0;
    PORT7.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT7.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT;
    PORT7.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF;
    PORT7.DSCR2.BYTE = _00_Pm1_LARGECUR_OFF | _00_Pm2_LARGECUR_OFF | _00_Pm3_LARGECUR_OFF | _00_Pm4_LARGECUR_OFF | 
                       _00_Pm5_LARGECUR_OFF | _00_Pm6_LARGECUR_OFF;
    PORT7.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO;
    PORT7.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _40_Pm6_MODE_OUTPUT;

    /* Set PORT8 registers */
    PORT8.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0;
    PORT8.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT;
    PORT8.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF;
    PORT8.DSCR2.BYTE = _00_Pm1_LARGECUR_OFF;
    PORT8.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO;
    PORT8.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT;

    /* Set PORT9 registers */
    PORT9.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | 
                      _00_Pm5_OUTPUT_0 | _00_Pm6_OUTPUT_0;
    PORT9.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORT9.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT;
    PORT9.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF;
    PORT9.DSCR2.BYTE = _00_Pm0_LARGECUR_OFF | _00_Pm1_LARGECUR_OFF | _00_Pm2_LARGECUR_OFF | _00_Pm3_LARGECUR_OFF | 
                       _00_Pm4_LARGECUR_OFF | _00_Pm5_LARGECUR_OFF;
    PORT9.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO;
    PORT9.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _40_Pm6_MODE_OUTPUT;

    /* Set PORTA registers */
    PORTA.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | 
                      _00_Pm5_OUTPUT_0;
    PORTA.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTA.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT;
    PORTA.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF;
    PORTA.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO;
    PORTA.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _C0_PDRA_DEFAULT;

    /* Set PORTB registers */
    PORTB.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm2_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | 
                      _00_Pm5_OUTPUT_0 | _00_Pm6_OUTPUT_0;
    PORTB.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm2_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTB.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT;
    PORTB.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm2_HIDRV_OFF | _00_Pm3_HIDRV_OFF | 
                      _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF | _00_Pm6_HIDRV_OFF;
    PORTB.DSCR2.BYTE = _00_Pm5_LARGECUR_OFF;
    PORTB.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO;
    PORTB.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _04_Pm2_MODE_OUTPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _40_Pm6_MODE_OUTPUT | _80_PDRB_DEFAULT;

    /* Set PORTD registers */
    PORTD.PODR.BYTE = _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm6_OUTPUT_0 | _00_Pm7_OUTPUT_0;
    PORTD.ODR0.BYTE = _00_Pm3_CMOS_OUTPUT;
    PORTD.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm6_CMOS_OUTPUT | _00_Pm7_CMOS_OUTPUT;
    PORTD.PCR.BYTE = _00_Pm2_PULLUP_OFF | _00_Pm5_PULLUP_OFF;
    PORTD.DSCR.BYTE = _00_Pm3_HIDRV_OFF | _00_Pm4_HIDRV_OFF | _00_Pm6_HIDRV_OFF | _00_Pm7_HIDRV_OFF;
    PORTD.DSCR2.BYTE = _00_Pm3_LARGECUR_OFF;
    PORTD.PMR.BYTE = _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | _00_Pm5_PIN_GPIO | _00_Pm6_PIN_GPIO | 
                     _00_Pm7_PIN_GPIO;
    PORTD.PDR.BYTE = _00_Pm2_MODE_INPUT | _08_Pm3_MODE_OUTPUT | _10_Pm4_MODE_OUTPUT | _00_Pm5_MODE_INPUT | 
                     _40_Pm6_MODE_OUTPUT | _80_Pm7_MODE_OUTPUT | _03_PDRD_DEFAULT;

    /* Set PORTE registers */
    PORTE.PODR.BYTE = _00_Pm0_OUTPUT_0 | _00_Pm1_OUTPUT_0 | _00_Pm3_OUTPUT_0 | _00_Pm4_OUTPUT_0 | _00_Pm5_OUTPUT_0;
    PORTE.ODR0.BYTE = _00_Pm0_CMOS_OUTPUT | _00_Pm1_CMOS_OUTPUT | _00_Pm3_CMOS_OUTPUT;
    PORTE.ODR1.BYTE = _00_Pm4_CMOS_OUTPUT | _00_Pm5_CMOS_OUTPUT;
    PORTE.DSCR.BYTE = _00_Pm0_HIDRV_OFF | _00_Pm1_HIDRV_OFF | _00_Pm3_HIDRV_OFF | _00_Pm4_HIDRV_OFF | _00_Pm5_HIDRV_OFF;
    PORTE.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm1_PIN_GPIO | _00_Pm2_PIN_GPIO | _00_Pm3_PIN_GPIO | _00_Pm4_PIN_GPIO | 
                     _00_Pm5_PIN_GPIO;
    PORTE.PDR.BYTE = _01_Pm0_MODE_OUTPUT | _02_Pm1_MODE_OUTPUT | _00_Pm2_MODE_INPUT | _08_Pm3_MODE_OUTPUT | 
                     _10_Pm4_MODE_OUTPUT | _20_Pm5_MODE_OUTPUT | _40_PDRE_DEFAULT;

    /* Set PORTH registers */
    PORTH.PMR.BYTE = _00_Pm0_PIN_GPIO | _00_Pm4_PIN_GPIO;
    PORTH.PDR.BYTE = _00_Pm0_MODE_INPUT | _00_Pm4_MODE_INPUT | _EE_PDRH_DEFAULT;

    R_Config_PORT_Create_UserInit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
