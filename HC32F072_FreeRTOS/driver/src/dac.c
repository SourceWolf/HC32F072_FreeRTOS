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
/** \file dac.c
 **
 ** dac driver API.
 **
 **   - 2019-04-10    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "dac.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
******************************************************************************
	** \brief  ʹ�����ͨ����DMA DMA_CR0�е�DMAEN0
	** 
  ** @param  NewState  :   TRUE ���� FALSE
	** \retval ��
	**
******************************************************************************/
void Dac_DmaCmd(boolean_t NewState)
{
	SetBit((uint32_t)(&(M0P_DAC->CR0)), 12, NewState);
}

/**
******************************************************************************
	** \brief  ����DAC��DMA�����жϣ� DMA_CR0�е�DMAUDRIE0
	** 
  ** @param  NewState  :   TRUE ���� FALSE
	** \retval ��
	**
******************************************************************************/
void Dac_DmaITConfig(boolean_t NewState)
{
	SetBit((uint32_t)(&(M0P_DAC->CR0)), 13, NewState);
}

/**
******************************************************************************
	** \brief  ��ȡDAC��DMA�����жϱ�־λ״̬�� DMA_SR�е�DMAUDR0
	** 
	** @param  ��
	** \retval TRUE �� FALSE
	**
******************************************************************************/
boolean_t Dac_GetITStatus(void)
{
	return GetBit((uint32_t)(&(M0P_DAC->SR)), 13);
}

/**
******************************************************************************
	** \brief  ����DAC��ʹ�����ֹ�� DMA_CR0�е�EN0
	** 
  ** @param  NewState  :   TRUE ���� FALSE
	** \retval ��
	**
******************************************************************************/
void Dac_Cmd(boolean_t NewState)
{
	SetBit((uint32_t)(&(M0P_DAC->CR0)), 0, NewState);
}

/**
******************************************************************************
	** \brief  ��������Ĵ���������DACת�� DMA_SWTRIGR�е�SWTRIG0
	** 
	** @param  ��
	** \retval ��
	**
******************************************************************************/
void Dac_SoftwareTriggerCmd(void)
{
	SetBit((uint32_t)(&(M0P_DAC->SWTRIGR)), 0, 1);
}
	
/**
******************************************************************************
** \brief  ��ʼ��DAC0
	** 
	** @param  DAC_InitStruct  :   ���ڳ�ʼ��DAC0�Ľṹ��
	** \retval ��
	**
******************************************************************************/
void Dac_Init(stc_dac_config_t* DAC_InitStruct)
{
	M0P_DAC->CR0_f.BOFF0 = DAC_InitStruct->boff_t;
	M0P_DAC->CR0_f.TEN0  = DAC_InitStruct->ten_t;
	M0P_DAC->CR0_f.TSEL0 = DAC_InitStruct->tsel_t;
	M0P_DAC->CR0_f.WAVE0 = DAC_InitStruct->wave_t;
	M0P_DAC->CR0_f.MAMP0 = DAC_InitStruct->mamp_t;
	M0P_DAC->CR0_f.SREF0 = DAC_InitStruct->sref_t;
	if(DAC_InitStruct->align == Left_Align)
	{
		M0P_DAC->DHR12L0_f.DHR0 = DAC_InitStruct->dhr12;
	}
	else if(DAC_InitStruct->align == Right_Align)
	{
		M0P_DAC->DHR12R0_f.DHR0 = DAC_InitStruct->dhr12;
	}
	else
	{
		M0P_DAC->DHR8R0_f.DHR0 = DAC_InitStruct->dhr8;
	}
}

/**
******************************************************************************
** \brief  ��DAC0�����ݱ��ּĴ���д����
	** 
	** @param  DAC_Channel:   Dac_0
	** @param  DAC_Align  :   Right_Align ��Left_Align
	** @param  DAC_Bit    :   Bit8 ��Bit12
	** @param  Data       :   ��Ҫ���͵�����
	** \retval ��
	**
******************************************************************************/
void Dac_SetChannelData(en_align_t DAC_Align, en_bitno_t DAC_Bit, uint16_t Data)
{
		if(DAC_Align == Right_Align)
		{
			if(DAC_Bit == Bit8)
			{
				M0P_DAC->DHR8R0_f.DHR0 = (uint8_t)Data;
			}
			else if(DAC_Bit == Bit12)
			{
				M0P_DAC->DHR12R0_f.DHR0 = Data;
			}
            else
            {
              return;
            }
		}
		else if(DAC_Align == Left_Align)
		{
			if(DAC_Bit == Bit8)
			{
				return;
			}
			else if(DAC_Bit == Bit12)
			{
				M0P_DAC->DHR12L0_f.DHR0 = Data;
			}
            else
            {
              return;
            }
		}
        else
        {
            return;
        }
}



/**
******************************************************************************
	** \brief  ��ȡDAC��������Ĵ���DAC_DOR0
	** 
	** @param  ��
	** \retval DAC_DOR0��ֵ
	**
******************************************************************************/
uint16_t Dac_GetDataOutputValue(void)
{
	uint16_t tmp;
	tmp = M0P_DAC->DOR0_f.DOR0;
	return tmp&0x0fff;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


