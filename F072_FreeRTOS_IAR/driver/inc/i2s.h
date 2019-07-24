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
/** \file i2s.h
 **
 ** Header file for i2s Converter functions
 ** @link I2S Group Some description @endlink
 **
 **   - 2019-04-01      First Version
 **
 ******************************************************************************/
#ifndef __I2S_H__
#define __I2S_H__
/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "hc32f072.h"

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define I2S_IT_TXE      ((uint8_t)7)
#define I2S_IT_RXNEIE   ((uint8_t)6)
#define I2S_IT_ERRIE    ((uint8_t)5)
#define I2S_RDMA_EN     ((uint8_t)1)
#define I2S_LDMA_EN     ((uint8_t)0)

#define I2S_RXNE_L      ((uint8_t)0)
#define I2S_TXE_L       ((uint8_t)1)
#define I2S_UDR_L       ((uint8_t)2)
#define I2S_UDR_R       ((uint8_t)3)
#define I2S_OVR_L       ((uint8_t)6)
#define I2S_BSY         ((uint8_t)7)
#define I2S_FRE         ((uint8_t)8)
#define I2S_OVR_R       ((uint8_t)13)
#define I2S_RXNE_R      ((uint8_t)14)
#define I2S_TXE_R       ((uint8_t)15)

#define I2S_FLAG_UDF    ((uint8_t)3)
#define I2S_FLAG_OVR    ((uint8_t)6)
#define I2S_FLAG_FRE    ((uint8_t)8)



//��Ƶ������ 
#define I2S_AudioFreq_192k                (uint32_t)192000u
#define I2S_AudioFreq_96k                 (uint32_t)96000u
#define I2S_AudioFreq_48k                 (uint32_t)48000u
#define I2S_AudioFreq_44k                 (uint32_t)44100u
#define I2S_AudioFreq_32k                 (uint32_t)32000u
#define I2S_AudioFreq_22k                 (uint32_t)22050u
#define I2S_AudioFreq_16k                 (uint32_t)16000u
#define I2S_AudioFreq_11k                 (uint32_t)11025u
#define I2S_AudioFreq_8k                  (uint32_t)8000u


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

/**
 ******************************************************************************
 ** \brief ʹ�ܻ��߽�ָֹ��
 ******************************************************************************/ 
typedef enum 
{
	DISABLE  = 0,         //��ֹ
	ENABLE   = 1          //ʹ��
}en_en_state_t;

/**
 ******************************************************************************
 ** \brief ״̬��־λ
 ******************************************************************************/
typedef enum 
{
	RESET = 0, 
	SET = !RESET
}en_flag_status_t;

 /**
 ******************************************************************************
 ** \brief I2S ����ͨ��ѡ������
 ******************************************************************************/ 
typedef enum 
{
	I2S0     = 0u,  // I2Sͨ��0
	I2S1     = 1u,  // I2Sͨ��1
}en_i2s_channel_t;

/**
 ******************************************************************************
 ** \brief I2S ����ʹ������
 ******************************************************************************/ 
typedef enum 
{
	I2sEnable     = 1u,  // I2Sģ��ʹ��
	I2sDisable    = 0u,  // I2Sģ���ֹ
}en_i2s_en_t;

/**
 ******************************************************************************
 ** \brief I2S ģʽ����
 ******************************************************************************/ 
typedef enum 
{
	I2sSlaveSend   = 0u,  //��ģʽ����
  I2sSlaveRec    = 1u,  //��ģʽ����
	I2sMasterSend  = 2u,  //��ģʽ����
	I2sMasterRec   = 3u,  //��ģʽ����
}en_spi_mode_t;

/**
 ******************************************************************************
 ** \brief I2S PCMSYNCͬ��֡��־
 ******************************************************************************/ 
typedef enum 
{
	I2sPcmsyncShort = 0u,      //��֡ͬ��
	I2sPcmsyncLong  = 1u
}en_i2s_pcmsync_t;

/**
 ******************************************************************************
 ** \brief I2S ����ʱ��ѡ��
 ******************************************************************************/
typedef enum 
{
	I2sPclk = 0u,
	I2sHclk = 1u
}en_i2s_cksel_t;

/**
 ******************************************************************************
 ** \brief I2S��׼ѡ��
 ******************************************************************************/
typedef enum 
{
	i2sstdPhilips = 0u,
	i2sstdMSBL    = 1u,
	i2sstdLSBR    = 2u,
	i2sstdPCM     = 3u
}en_i2s_i3sstd_t;

/**
 ******************************************************************************
 ** \brief I2S Ҫ��������ݳ���
 ******************************************************************************/
typedef enum 
{
	i2sDatlen16Bit = 0u,
	i2sDatlen24Bit = 1u,
	i2sDatlen32Bit = 2u
}en_i2s_datlen_t;

/**
 ******************************************************************************
 ** \brief I2S ͨ�����ݳ���
 ******************************************************************************/
typedef enum 
{
	i2sChlen16Bit = 0u,
	i2sChlen32Bit = 1u
}en_i2s_chlen_t;

/**
 *******************************************************************************
 ** \brief I2S ���ýṹ��
 ******************************************************************************/
typedef struct 
{
    en_spi_mode_t               i2s_Mode;        //I2S ģʽ����λ
		en_i2s_pcmsync_t            i2s_PcmSync;     //I2S ֡ͬ��
		en_i2s_cksel_t              i2s_Cksel;       //I2S ��ģʽ��ʼ��ѡ��0��PCLK 1:HCLK
		en_i2s_i3sstd_t             i2s_Std;         //I2S ��׼ѡ�� 0��I2S Philips 1:MAS����� 2��LSB�Ҷ��� 3��PCM��׼
    en_i2s_datlen_t             i2s_Datalen;     //I2S Ҫ��������ݳ���
    en_i2s_chlen_t              i2s_Chlen;       //I2S ÿ����Ƶͨ����λ����0��16λ 1��32λ��
    en_en_state_t       				i2s_Mckoe;        //I2S ��ʱ��MCK���ʹ��
    uint32_t                    i2s_AudioFreq;    ///< I2S audio frequecy
		uint8_t                     i2s_Div;         //I2S PR�Ĵ�����DIV��λ��8λ
		uint8_t                     i2s_Odd;
	  uint8_t                     i2s_Fract;       //I2S PR�Ĵ�����FRACTС����Ƶ��λ��6λ
}stc_i2s_config_t;

/*******************************************************************************
 ** \brief I2Sx��غ�������
 ******************************************************************************/
extern void I2S_ConfIt(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it, en_en_state_t NewState);
extern void I2s_ConfDma(M0P_I2S_TypeDef *i2sx, uint8_t rl_dma_en, en_en_state_t NewState);
extern en_flag_status_t I2s_GetStatus(M0P_I2S_TypeDef *i2sx, uint8_t i2s_status);
extern void I2s_ClearITPendingBit(M0P_I2S_TypeDef *i2sx, uint8_t i2s_it_flag);
extern void I2s_SendDataL(M0P_I2S_TypeDef *i2sx, uint16_t Data);
extern void I2s_SendDataR(M0P_I2S_TypeDef *i2sx, uint16_t Data);
extern uint16_t I2s_ReceiveDataL(M0P_I2S_TypeDef *i2sx);
extern uint16_t I2s_ReceiveDataR(M0P_I2S_TypeDef *i2sx);
extern void I2s_Init(M0P_I2S_TypeDef *i2sx, stc_i2s_config_t *i2s_conf);
extern void I2S_Cmd(M0P_I2S_TypeDef *i2sx, en_en_state_t NewState);

#endif //__I2S_H__

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
