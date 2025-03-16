/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "user_define.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif
static uint32_t g_ram_vector_table[256];            // RAM space to hold the vector table
static void flash_copy_vector_table(void);
volatile uint8_t    g_buf[FLASH_CF_MIN_PGM_SIZE];   // FLASH_CF_MIN_PGM_SIZE is larger the DF block size

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

flash_interrupt_event_t status = 0xff;
void u_cb_function(void *event) /* コールバック関数 */
{
flash_int_cb_args_t *ready_event = event;
/* ISRコールバック関数の処理 */

    switch (ready_event->event)
    {
    case FLASH_INT_EVENT_INITIALIZED:
        status = FLASH_INT_EVENT_INITIALIZED;
        break;
    case FLASH_INT_EVENT_ERASE_COMPLETE:
        status = FLASH_INT_EVENT_ERASE_COMPLETE;
        break;
    case FLASH_INT_EVENT_WRITE_COMPLETE:
        status = FLASH_INT_EVENT_WRITE_COMPLETE;
        break;
    case FLASH_INT_EVENT_BLANK:
        status = FLASH_INT_EVENT_BLANK;
        break;
    case FLASH_INT_EVENT_NOT_BLANK:
        status = FLASH_INT_EVENT_NOT_BLANK;
        break;
    case FLASH_INT_EVENT_TOGGLE_STARTUPAREA:
    case FLASH_INT_EVENT_SET_ACCESSWINDOW:
    case FLASH_INT_EVENT_LOCKBIT_WRITTEN:
    case FLASH_INT_EVENT_LOCKBIT_PROTECTED:
    case FLASH_INT_EVENT_LOCKBIT_NON_PROTECTED:
    case FLASH_INT_EVENT_ERR_DF_ACCESS:
    case FLASH_INT_EVENT_ERR_CF_ACCESS:
    case FLASH_INT_EVENT_ERR_SECURITY:
    case FLASH_INT_EVENT_ERR_CMD_LOCKED:
    case FLASH_INT_EVENT_ERR_LOCKBIT_SET:
    case FLASH_INT_EVENT_ERR_FAILURE:
    case FLASH_INT_EVENT_TOGGLE_BANK:
    case FLASH_INT_EVENT_END_ENUM:
    default:
        /* code */
        break;
    }
}


void main(void)
{
    uint32_t    i;
    uint32_t    addr;
    flash_err_t err;
    flash_res_t result;

    flash_interrupt_config_t cb_func_info;

    {
        R_Config_TMR0_Start();
    }

    /* Initialize data to write */
    for (i = 0; i < (sizeof(g_buf)); i++)
    {
        /* fill buffer with byte dummy data */
        g_buf[i] = (uint8_t)i;
    }

    /* Copy vector table to RAM if interrupts possible while erasing/writing ROM */
    //flash_copy_vector_table();


    /* APIの初期設定 */
    {
        err = R_FLASH_Open();
        /* エラーの確認 */
        if (FLASH_SUCCESS != err)
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
        /* コールバック関数と割り込み優先レベルの設定 */
        cb_func_info.pcallback = u_cb_function;
        cb_func_info.int_priority = 1;
        err = R_FLASH_Control(FLASH_CMD_SET_BGO_CALLBACK,(void *)&cb_func_info);
        if (FLASH_SUCCESS != err)
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
    }

    /* DATA FLASH */

    /* Erase data block */
    {
        status = 0xff;
        err = R_FLASH_Erase(FLASH_DF_BLOCK_0, 1);
        if (FLASH_SUCCESS != err)
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
        /* フラッシュモジュールのAPI関数の実行状態を確認 */
        while (status != FLASH_INT_EVENT_ERASE_COMPLETE)
        {
        /* 任意の処理を実施 */
        }
    }

    /* Verify erased */
    {
        status = 0xff;
        err = R_FLASH_BlankCheck(FLASH_DF_BLOCK_0, FLASH_DF_BLOCK_SIZE, &result);
        if ((FLASH_SUCCESS != err))
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
        /* フラッシュモジュールのAPI関数の実行状態を確認 */
        while (status != FLASH_INT_EVENT_BLANK)
        {
        /* 任意の処理を実施 */
        }
    }

    /* Erase all of data flash */
    {
        status = 0xff;
        err = R_FLASH_Erase(FLASH_DF_BLOCK_0, FLASH_NUM_BLOCKS_DF);
        if (FLASH_SUCCESS != err)
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
        /* フラッシュモジュールのAPI関数の実行状態を確認 */
        while (status != FLASH_INT_EVENT_ERASE_COMPLETE)
        {
        /* 任意の処理を実施 */
        }
    }

    /* Verify erased */
    {
        status = 0xff;
        err = R_FLASH_BlankCheck(FLASH_DF_BLOCK_0, FLASH_DF_BLOCK_SIZE, &result);
        if ((FLASH_SUCCESS != err))
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
        /* フラッシュモジュールのAPI関数の実行状態を確認 */
        while (status != FLASH_INT_EVENT_BLANK)
        {
        /* 任意の処理を実施 */
        }
    }

    /* Write to all of block 0 */
    addr = FLASH_DF_BLOCK_0;
    while (addr < (FLASH_DF_BLOCK_0 + FLASH_DF_BLOCK_SIZE))
    {
        /* cast byte buffer address to a uint32_t */
        status = 0xff;
        err = R_FLASH_Write((uint32_t)g_buf, addr, (sizeof(g_buf)));
        if(FLASH_SUCCESS != err)
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
        /* フラッシュモジュールのAPI関数の実行状態を確認 */
        while (status != FLASH_INT_EVENT_WRITE_COMPLETE)
        {
        /* 任意の処理を実施 */
        }

        /* Verify data write */
        for (i=0; i < (sizeof(g_buf)); i++)
        {
            /* check on a byte basis */
            if (g_buf[i] != (*((uint8_t *)(addr + i))))
            {
                while(1)
                {
                    ;   // inspect error code
                }
            }
        }

        addr += (sizeof(g_buf));
    }

    /* Erase all of data flash */
    {
        status = 0xff;
        err = R_FLASH_Erase(FLASH_DF_BLOCK_0, FLASH_NUM_BLOCKS_DF);
        if (FLASH_SUCCESS != err)
        {
            while(1)
            {
                ;       // inspect error code
            }
        }
        /* フラッシュモジュールのAPI関数の実行状態を確認 */
        while (status != FLASH_INT_EVENT_ERASE_COMPLETE)
        {
        /* 任意の処理を実施 */
        }
    }

    /* Write all of data flash */
    addr = FLASH_DF_BLOCK_0;
    while (addr < FLASH_DF_BLOCK_INVALID)
    {
        /* cast byte buffer address to a uint32_t */
        status = 0xff;
        err = R_FLASH_Write((uint32_t)g_buf, addr, (sizeof(g_buf)));
        if(FLASH_SUCCESS != err)
        {
            while(1)
            {
                ;   // inspect error code
            }
        }
        /* フラッシュモジュールのAPI関数の実行状態を確認 */
        while (status != FLASH_INT_EVENT_WRITE_COMPLETE)
        {
        /* 任意の処理を実施 */
        }

        /* Verify data write */
        for (i = 0; i < (sizeof(g_buf)); i++)
        {
            /* inspect on a byte basis */
            if (g_buf[i] != (*((uint8_t *)(addr + i))))
            {
                while(1)
                {
                    ;   // inspect error code
                }
            }

        }

        addr += (sizeof(g_buf));
    }

    while ( 1 )
    {

    }
}

static void flash_copy_vector_table(void)
{
    uint32_t *p_vect_table;

    /* cast to ensure get uint32_t pointer */
    p_vect_table = (uint32_t *)__sectop("C$VECT");
    g_ram_vector_table[23] = p_vect_table[23];

    /* set_intb() takes void pointer */
    set_intb((void *)g_ram_vector_table);
} /* end of function flash_copy_vector_table() */

#ifdef __cplusplus
void abort(void)
{

}
#endif
