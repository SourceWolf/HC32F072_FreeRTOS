/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file dac.h
 **
 ** Header file for dac Converter functions
 ** @link DAC Group Some description @endlink
 **
 **   - 2019-04-10      First Version
 **
 ******************************************************************************/
#ifndef __DAC_H__
#define __DAC_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif
  
/**
 ******************************************************************************
 ** \brief ʹ�ܻ��߽�ָֹ��
 ******************************************************************************/ 
typedef enum 
{
	DISABLE  = 0u,         //��ֹ
	ENABLE   = 1u          //ʹ��
}en_en_state_t;

/**
 ******************************************************************************
 ** \brief ʹ�ܻ��߽�ֹDAC0ͨ�����������         DAC_CR0��BOFF0
 ******************************************************************************/ 
typedef enum 
{
	Boff_Disable = 1u,
	Boff_Enable  = 0u
}en_dac_boff_t;

/**
 ******************************************************************************
 ** \brief ʹ�ܻ��߽�ֹDAC0ͨ������ʹ��           DAC_CR0: TEN0
 ******************************************************************************/ 
typedef enum
{
	Ten_Disable = 0u,
	Ten_Enable  = 1u
}en_dac_ten_t;

/**
 ******************************************************************************
 ** \brief DAC0ͨ������ѡ��                       DAC_CR0: TSEL0
 ******************************************************************************/ 
typedef enum 
{
	Tim0_Tradc = 0u,      //TIM0_TRADC����
	Tim1_Tradc = 1u,      //TIM1_TRADC����
	Tim2_Tradc = 2u,      //TIM2_TRADC����
	Tim3_Tradc = 3u,      //TIM3_TRADC����
	Tim4_Tradc = 4u,      //TIM4_TRADC����
	Tim5_Tradc = 5u,      //TIM5_TRADC����
	Sw_Triger  = 6u,      //�������
	ExPort_Triger = 7u    //�ⲿ�˿ڴ���
}en_dac_tsel_t;

/**
 ******************************************************************************
 ** \brief DAC0ͨ������/���ǲ�����ʹ�ܻ��ֹ      DAC_CR0: WAVE0
 ******************************************************************************/ 
typedef enum
{
	Wave_Disable  = 0u,   //��ֹ������
	Noise_Enable  = 1u,   //ʹ������������
	TrWave_Enable = 2u    //ʹ���������ǲ�
}en_dac_wave_t;

/**
 ******************************************************************************
 ** \brief DACxͨ������/���ѡ����                DAC_CR0: MAMP0 & MAMP1
 ******************************************************************************/
typedef enum
{
	Memp01   = 0u,
	Menp03   = 1u,
	Menp07   = 2u,
	Menp15   = 3u,
	Menp31   = 4u,
	Menp63   = 5u,
	Menp127  = 6u,
	Menp255  = 7u,
	Menp511  = 8u,
	Menp1023 = 9u,
	Menp2047 = 10u,
	Menp4095 = 11u
}en_dac_mamp_t;

/**
 ******************************************************************************
 ** \brief DACxͨ��DMAʹ�ܻ��ֹ                 DAC_CR0: DMAEN0 & DMAEN1
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief DACxͨ��DMA�����ж�ʹ�ܻ��ֹ         DAC_CR0: DMAUDRIE0 & DMAUDRIE1
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief DACx�ο���ѹѡ��                       DAC_CR0: SREF0 & SREF1
 ******************************************************************************/
typedef enum
{
	Voltage1V5   = 0u,   //�ڲ�1.5V
	Voltage2V5   = 1u,   //�ڲ�2.5V
	VoltageExRef = 2u,   //�ⲿ�ο���ѹExRef(PB01)
	VoltageAvcc  = 3u    //AVCC��ѹ
}en_dac_sref_t;

/**
 ******************************************************************************
 ** \brief DACx����ѡ��Ĵ���DAC_ETRS              DAC_ETRS
 ******************************************************************************/
typedef enum
{
	Port_Trig_PA9 = 0u,      //�����˿�ΪPA9
	Port_Trig_PB9 = 1u,      //�����˿�ΪPB9
	Port_Trig_PC9 = 2u,      //�����˿�ΪPC9
	Port_Trig_PD9 = 3u,      //�����˿�ΪPD9
	Port_Trig_PE9 = 4u,      //�����˿�ΪPE9
	Port_Trig_PF9 = 5u       //�����˿�ΪPF9
}en_port_trig_t;

/**
 ******************************************************************************
 ** \brief ���뷽ʽ              
 ******************************************************************************/
typedef enum
{
	Right_Align = 0u,        //�Ҷ���
	Left_Align  = 1u         //�����
}en_align_t;

/**
 ******************************************************************************
 ** \brief ����λ��          
 ******************************************************************************/
typedef enum
{
	Bit8  = 0u,               //8λ
	Bit12 = 1u                //12λ
}en_bitno_t;

/**
 ******************************************************************************
 ** \brief ��ʼ�����ýṹ��         
 ******************************************************************************/
typedef struct
{
	en_dac_boff_t  boff_t;
	en_dac_ten_t   ten_t;
	en_dac_tsel_t  tsel_t;
	en_dac_wave_t  wave_t;
	en_dac_mamp_t  mamp_t;
	en_dac_sref_t  sref_t;
	en_port_trig_t port_trig_t;
	en_align_t     align;
	uint16_t       dhr12;
	uint8_t        dhr8;
}stc_dac_config_t;



extern void Dac_DmaCmd(boolean_t NewState);
extern void Dac_DmaITConfig(boolean_t NewState);
extern boolean_t Dac_GetITStatus(void);
extern void Dac_Cmd(boolean_t NewState);
extern void Dac_SoftwareTriggerCmd(void);
extern void Dac_Init(stc_dac_config_t* DAC_InitStruct);
extern void Dac_SetChannelData(en_align_t DAC_Align, en_bitno_t DAC_Bit, uint16_t Data);
extern uint16_t Dac_GetDataOutputValue(void);

#ifdef __cplusplus
}
#endif
#endif //__DAC_H__

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
