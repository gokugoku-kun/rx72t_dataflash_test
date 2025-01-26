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

//DATA FLASH
/* Please set the number of loops. */
#define LOOP_CNT (FLASH_DM_CFG_DF_DATA_NUM)
/* Please set the maximum data size. */
#define TEST_BUFF_NUM (256)

typedef enum _datfrx_status
{
    DATFRX_IDLE,
    DATFRX_RUN_FORMAT,
    DATFRX_SUCCESS_INIT,
    DATFRX_FINISH_FORMAT,
    DATFRX_FINISH_WRITE,
    DATFRX_FINISH_ERASE,
    DATFRX_FINISH_RECLAIM,
    DATFRX_ERR
} e_datfrx_status_t;

static void trap(uint32_t test_no);
static void test_data_set(uint8_t * p_buf, uint32_t cnt, uint32_t inc);
static void testinit(void);
static void testmain(void);
static void testwrite(void);
static void testmain_restoration(void);
static void ucb_function(void* error_code);
static uint32_t gs_flash_dm_work[(261 + (FLASH_DM_CFG_DF_DATA_NUM * 2))/sizeof(uint32_t)+1];

static uint8_t gs_test_w_buff[TEST_BUFF_NUM];
static uint8_t gs_test_r_buff[TEST_BUFF_NUM];

st_flash_dm_info_t g_flash_dm_info;
uint16_t g_data_num = FLASH_DM_CFG_DF_DATA_NUM - 1;
volatile uint32_t g_loop_cnt = 0;
volatile uint32_t g_proc_flag = DATFRX_IDLE;

#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
    {
        R_Config_TMR0_Start();
    }
    testmain();
    testmain_restoration();
    while ( 1 )
    {

    }
}


static void trap(uint32_t test_no)
{
    while(test_no)
    {
        /* Do Nothing. */
        nop();
    };
}

static void test_data_set(uint8_t * p_buf, uint32_t cnt, uint32_t inc)
{
    /* cast from uin32_t* to uint8_t* */
    uint32_t  i;
    
    for (i = 0; i < cnt; i++)
    {
        /* cast from uint32_t to uint8_t */
        *p_buf++ = (uint8_t)(i + inc);
    }
}

static void testwrite(void)
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    /* ==== WRITE ==== */
    test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
    g_flash_dm_info.data_no = g_data_num;
    /* cast from uint32_t to uint8_t* */
    g_flash_dm_info.p_data  = (uint8_t *)&gs_test_w_buff[0];
    ret = R_FLASH_DM_Write(&g_flash_dm_info);
    if(ret == FLASH_DM_ERR_REQUEST_ERASE)
    {
        ret = R_FLASH_DM_Erase();
        if(ret != FLASH_DM_ACCEPT)
        {
            trap(1);
        }
    }
    else if(ret != FLASH_DM_ACCEPT)
    {
        trap(4);
    }
    else
    {
        /* Do Nothing */
    }
}

static void testinit(void)
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    while(1)
    {
        /* ==== INITIALIZE ==== */
        ret = R_FLASH_DM_Init();
        if(ret == FLASH_DM_ADVANCE)
        {
            break;
        }
        else if(ret == FLASH_DM_ERR_BUSY)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else
        {
            trap(9);
        }
    }

    while(1)
    {
        ret = R_FLASH_DM_InitAdvance();
        if(ret == FLASH_DM_SUCCESS)
        {
            g_proc_flag = DATFRX_SUCCESS_INIT;
            break;
        }
        else if(ret == FLASH_DM_ADVANCE)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else if(ret == FLASH_DM_ERR_BUSY)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else if(ret == FLASH_DM_ERR_REQUEST_FORMAT)
        {
            ret = R_FLASH_DM_Format();
            if(ret != FLASH_DM_ACCEPT)
            {
                trap(10);
            }
            else
            {
                g_proc_flag = DATFRX_RUN_FORMAT;
            }
            break;
        }
        else
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            trap(11);
        }
    }
}

static void testmain(void)
{
    /* === OPEN ===*/
    if (FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        trap(12);
    }

    do
    {
        testinit();
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);

    g_data_num = 0;

    testwrite();

    do
    {
        /* Do nothing. */
    }
    while(g_loop_cnt < LOOP_CNT);

    /* ==== CLOSE ==== */
    while(FLASH_DM_SUCCESS != R_FLASH_DM_Close())
    {
        /* Do nothing. */
    }
}

static void ucb_function(void* error_code)
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    uint32_t i;
    uint32_t* pcfg;
    uint32_t data_size = 0;

    pcfg = &data_size;

    /* ==== SUCCESS ==== */
    /* cast from void* to e_flash_dm_status_t*/
    switch((e_flash_dm_status_t)error_code)
    {
        case FLASH_DM_FINISH_FORMAT:
        {
            g_proc_flag = DATFRX_FINISH_FORMAT;
            break;
        }
        break;

        case FLASH_DM_FINISH_WRITE :
        {
            g_proc_flag = DATFRX_FINISH_WRITE;
            /* ====  VERYFY ==== */
            g_flash_dm_info.data_no = g_data_num;
            /* cast from uint32_t to uint8_t* */
            g_flash_dm_info.p_data  = (uint8_t *)&gs_test_r_buff[0];
            ret = R_FLASH_DM_Read(&g_flash_dm_info);
            *pcfg = g_data_num;
            ret = R_FLASH_DM_Control(FLASH_DM_GET_DATA_SIZE, pcfg);
            test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
            for(i = 0; i < data_size ; i++)
            {
                if(gs_test_w_buff[i] != gs_test_r_buff[i])
                {
                    trap(16);
                }
            }

            /* ==== INCREASE COUNT & CLOSE CONFIRMATION ==== */
            if((++g_loop_cnt) >= LOOP_CNT)
            {
                break;
            };

            /* ==== Switch WRITTING DATANUMBER ==== */
            g_data_num = g_loop_cnt % FLASH_DM_CFG_DF_DATA_NUM;

            /* ==== WRITE ==== */
            test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
            g_flash_dm_info.data_no = g_data_num;
            /* cast from uint32_t to uint8_t* */
            g_flash_dm_info.p_data  = (uint8_t *)&gs_test_w_buff[0];
            ret = R_FLASH_DM_Write(&g_flash_dm_info);
            if(ret == FLASH_DM_ERR_REQUEST_ERASE)
            {
                ret = R_FLASH_DM_Erase();
                if(ret != FLASH_DM_ACCEPT)
                {
                    trap(17);
                }
            }

            else if(ret != FLASH_DM_ACCEPT)
            {
                trap(20);
            }
            else
            {
                /* Do Nothing */
            }
        }
        break;

        case FLASH_DM_FINISH_ERASE :
        {
            g_proc_flag = DATFRX_FINISH_ERASE;
            /* ==== ERASE ==== */
            ret = R_FLASH_DM_Erase();
            if(ret == FLASH_DM_NO_INVALID_BLOCK)
            {
                /* ==== Switch WRITTING DATANUMBER ==== */
                g_data_num = g_loop_cnt % FLASH_DM_CFG_DF_DATA_NUM;

                /* ==== WRITE ==== */
                test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
                g_flash_dm_info.data_no = g_data_num;
                /* cast from uint32_t to uint8_t* */
                g_flash_dm_info.p_data  = (uint8_t *)&gs_test_w_buff[0];
                ret = R_FLASH_DM_Write(&g_flash_dm_info);

                if(ret != FLASH_DM_ACCEPT)
                {
                    trap(23);
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else if(ret != FLASH_DM_ACCEPT)
            {
                trap(24);
            }
            else
            {
                /* Do Nothing */
            }
        }
        break;

        /* ==== FAILD ==== */
        case FLASH_DM_ERR_FORMAT:
        case FLASH_DM_ERR_WRITE :
        case FLASH_DM_ERR_ERASE :
        case FLASH_DM_ERR_RECLAIM:
        {
            g_proc_flag = DATFRX_ERR;
            trap(27);
        }
        break;
        default :
        {
            trap(28);
        }
        break;
    }
}

static void testmain_restoration(void)
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    /* === OPEN ===*/
    if (FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        trap(13);
    }

    do
    {
        testinit();
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);

    g_data_num = 0;

    do
    {
        /* ====  VERYFY ==== */
        g_flash_dm_info.data_no = g_data_num;
        /* cast from uint32_t to uint8_t* */
        g_flash_dm_info.p_data  = (uint8_t *)&gs_test_r_buff[0];
        ret = R_FLASH_DM_Read(&g_flash_dm_info);

        if(ret != FLASH_DM_SUCCESS)
        {
            trap(14);
        }
        else if(ret == FLASH_DM_ERR_DATA_NOT_PRESENT)
        {

            trap(15);
        }
        else
        {
            /* Do Nothing. */
            nop();
        }
        g_data_num++;
    }while(g_data_num < FLASH_DM_CFG_DF_DATA_NUM);

    /* ==== CLOSE ==== */
    while(FLASH_DM_SUCCESS != R_FLASH_DM_Close())
    {
        /* Do nothing. */
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
