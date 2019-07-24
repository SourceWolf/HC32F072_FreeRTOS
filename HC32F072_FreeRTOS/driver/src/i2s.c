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
/** \file i2s.c
 **
 ** I2S driver API.
 **
 **   - 2019-04-01    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "i2s.h"

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
  * @brief  ʹ��I2Sx��ص��ж�
  * @param  i2sx: M0P_I2S0����M0P_I2S1
  * @param  i2s_it: Ϊ����ֵ
  *     @arg I2S_IT_TXE: ���ͻ��������ж�ʹ��λ
  *     @arg I2S_IT_RXNEIE:���ջ��������ж�ʹ��λ
  *     @arg I2S_IT_ERRIE: �����ж�ʹ��λ
  * @param  NewState: =ENALE �� DISABLE
  * @retval None
 **
 ******************************************************************************/
void I2S_ConfIt(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it, en_en_state_t NewState)
{
	uint16_t itmark=0;
	itmark=(uint16_t)1<<i2s_it;
	if(NewState == ENABLE)   //ʹ���ж�
	{
		i2sx->CR |= (uint16_t)itmark;
	}
	else if(NewState == DISABLE)  //��ֹ�ж�
	{
		i2sx->CR &= ~(uint16_t)itmark;
	}
}

/**
 ******************************************************************************
 ** \brief  I2S��������������DMA���ݷ�����������
 ** 
  * @param  i2sx: M0P_I2S0����M0P_I2S1
  * @param  i2s_it: Ϊ����ֵ
  *     @arg I2S_RDMA_EN: ������������DMA���ݷ���ʹ��λ
  *     @arg I2S_LDMA_EN: ������������DMA���ݷ���ʹ��λ
  * @param  NewState: =ENALE �� DISABLE
 ** \retval none
 **
 ******************************************************************************/
void I2s_ConfDma(M0P_I2S_TypeDef *i2sx, uint8_t rl_dma_en, en_en_state_t NewState)
{
	uint16_t itmark=0;
	itmark=(uint16_t)1<<rl_dma_en;
	if(NewState == ENABLE)   //ʹ����������������DMA
	{
		i2sx->CR |= itmark;
	}
	else if(NewState == DISABLE)  //��ֹ��������������DMA
	{
		i2sx->CR &= ~(uint16_t)itmark;
	}	
}

/**
 ******************************************************************************
 ** \brief  I2S״̬��־λ״̬��ȡ
 ** 
  * @param  i2sx: M0P_I2S0����M0P_I2S1
  * @param  i2s_status: Ϊ����ֵ
  *     @arg I2S_RXNE_L: ���������ջ������ǿձ�־
	*     @arg I2S_TXE_L: ���������ͻ������ձ�־
  *     @arg I2S_UDR_L: �����������־
  *     @arg I2S_UDR_R: �����������־
  *     @arg I2S_OVR_L: �����������־
  *     @arg I2S_BSY: æ��־
  *     @arg I2S_FRE: ֡�����־
  *     @arg I2S_OVR_R: �����������־
  *     @arg I2S_RXNE_R: ���������ջ������ǿձ�־
	*     @arg I2S_TXE_R: ���������ͻ������ձ�־
 ** \retval ״̬��־λ״̬   RESET �� SET
 **
 ******************************************************************************/
en_flag_status_t I2s_GetStatus(M0P_I2S_TypeDef *i2sx, uint8_t i2s_status)
{
	uint16_t itmark=0;
	en_flag_status_t bitstatus;
	itmark=(uint16_t)1<<i2s_status;	
	if(!(i2sx->SR & itmark))
	{
		bitstatus = RESET;
	}
	else
	{
		bitstatus = SET;
	}
	return bitstatus;
}

/**
 ******************************************************************************
 ** \brief  I2S�ж�״̬��־λ����
 ** 
  * @param  i2sx: M0P_I2S0����M0P_I2S1
  * @param  i2s_status: Ϊ����ֵ
  *     @arg I2S_FLAG_UDF: �����жϱ�־λ
	*     @arg I2S_FLAG_OVR: �����жϱ�־λ
  *     @arg I2S_FLAG_FRE: ֡�����־λ
 ** \retval none
 **
 ******************************************************************************/
void I2s_ClearITPendingBit(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it_flag)
{
	uint16_t bitstatus;
	bitstatus = (uint16_t)1<<i2s_it_flag;
	i2sx->ICR &= ~bitstatus;
}

/**
 ******************************************************************************
 ** \brief  �����������ݼĴ���DRLд��Ҫ���͵�����
 ** 
 * @param  i2sx: M0P_I2S0����M0P_I2S1
 * @param  Data: Ҫ���͵�16λ����
 ** \retval none
 **
 ******************************************************************************/
void I2s_SendDataL(M0P_I2S_TypeDef *i2sx, uint16_t Data)
{	
	i2sx->DRL_f.DRL = Data;
}

/**
 ******************************************************************************
 ** \brief  �����������ݼĴ���DRRд��Ҫ���͵�����
 ** 
 * @param  i2sx: M0P_I2S0����M0P_I2S1
 * @param  Data: Ҫ���͵�16λ����
 ** \retval none
 **
 ******************************************************************************/
void I2s_SendDataR(M0P_I2S_TypeDef *i2sx, uint16_t Data)
{
	i2sx->DRR_f.DRR = Data;
}

/**
 ******************************************************************************
 ** \brief  �����������ݼĴ���DRL��ȡ�����յ�����
 ** 
 * @param  i2sx: M0P_I2S0����M0P_I2S1
 ** \retval ����ȡ������
 **
 ******************************************************************************/
uint16_t I2s_ReceiveDataL(M0P_I2S_TypeDef *i2sx)
{	
	uint16_t data;
	data = (uint16_t)i2sx->DRL;
	return data;
}

/**
 ******************************************************************************
 ** \brief  �����������ݼĴ���DRR��ȡ�����յ�����
 ** 
 * @param  i2sx: M0P_I2S0����M0P_I2S1
 ** \retval ����ȡ������
 **
 ******************************************************************************/
uint16_t I2s_ReceiveDataR(M0P_I2S_TypeDef *i2sx)
{	
	uint16_t data;
	data = (uint16_t)i2sx->DRR;
	return data;
}

/**
 ******************************************************************************
 ** \brief  ��ʼ��I2Sx����
 **  (һ)С����ƵFRACT=0:
 **  (1)�����ʱ��(MCKOE=1)
 **  ͨ��֡���λ16λ��������=��ƵI2SxCLK/[(16*2)*(2*I2SDIV+ODD)*8]
 **  ͨ��֡���λ32λ��������=��ƵI2SxCLK/[(32*2)*(2*I2SDIV+ODD)*4]
 **  (2)��ֹ��ʱ��(MCKOE=0)
 **  ͨ��֡���λ16λ��������=��ƵI2SxCLK/[(16*2)*(2*I2SDIV+ODD)]
 **  ͨ��֡���λ32λ��������=��ƵI2SxCLK/[(32*2)*(2*I2SDIV+ODD)]
 **  (��)С����ƵFRACT=0:
 **  (1)�����ʱ��(MCKOE=1)
 **  ͨ��֡���λ16λ��������=��ƵI2SxCLK/[(16*2)*(2*(I2SDIV+FRACT/64))*8]
 **  ͨ��֡���λ32λ��������=��ƵI2SxCLK/[(32*2)*(2*(I2SDIV+FRACT/64))*4]
 **  (2)�����ʱ��(MCKOE=0)
 **  ͨ��֡���λ16λ��������=��ƵI2SxCLK/[(16*2)*(2*(I2SDIV+FRACT/64))]
 **  ͨ��֡���λ32λ��������=��ƵI2SxCLK/[(32*2)*(2*(I2SDIV+FRACT/64))]
 **  I2SDIV��FRACT��I2SODD�������ϵļ��㹫ʽ����ʵ�����������ֵ
 * @param  i2sx: M0P_I2S0����M0P_I2S1
 * @param  i2s_conf �����ò���
 ** \retval ��
 **
 ******************************************************************************/
void I2s_Init(M0P_I2S_TypeDef *i2sx, stc_i2s_config_t *i2s_conf)
{
	i2sx->CFGR_f.CFG     = i2s_conf->i2s_Mode;           //����ģʽ
	i2sx->CFGR_f.PCMSYNC = i2s_conf->i2s_PcmSync;    //PCM֡ͬ��λ�� ֻ����I2SSTD=3������¸�λ��������
	i2sx->CFGR_f.CKSEL   = i2s_conf->i2s_Cksel;      //��ģʽ��I2Sʼ��ѡ��0��PCLK 1:HCLK
	i2sx->CFGR_f.STD     = i2s_conf->i2s_Std;        //��׼ѡ�� 0��I2S Philips 1:MAS����� 2��LSB�Ҷ��� 3��PCM��׼
	i2sx->CFGR_f.DATLEN  = i2s_conf->i2s_Datalen;    //Ҫ��������ݳ���
	i2sx->CFGR_f.CHIEN   = i2s_conf->i2s_Chlen;      //ÿ����Ƶͨ����λ����0��16λ 1��32λ
	i2sx->PR_f.MCKOE     = i2s_conf->i2s_Mckoe;      //��ʱ��MCK���ʹ��
	i2sx->PR_f.I2SDIV    = i2s_conf->i2s_Div;
	i2sx->PR_f.FRACT     = i2s_conf->i2s_Fract;
	i2sx->PR_f.ODD       = i2s_conf->i2s_Odd;
}

/**
 ******************************************************************************
 ** \brief  ʹ�ܻ��߽�ֹI2Sx
 ** 
 * @param  i2sx:  M0P_I2S0����M0P_I2S1
 **
 * @param  NewState :EANBLE ����DISABLE
 ** \retval ��
 **
 ******************************************************************************/
void I2S_Cmd(M0P_I2S_TypeDef *i2sx, en_en_state_t NewState)
{
	i2sx->CFGR_f.E = NewState;
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/









