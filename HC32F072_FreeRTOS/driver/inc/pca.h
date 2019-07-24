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
/*****************************************************************************/
/** \file pca.h
 **
 ** PCA���ɱ�̼������У����ݽṹ��API����
 **  
 **
 ** History:
 **   - 2019-04-09        First version
 **
 *****************************************************************************/

#ifndef __PCA_H__
#define __PCA_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup PcaGroup Programmable Counter Array (PCA)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief PCA  ģ��ѡ��
 ** \note 
 ******************************************************************************/
typedef enum
{
	pca_module0 = 0,      //  PCA_0
	pca_module1 = 1,      //  PCA_1
	pca_module2 = 2,      //  PCA_2
	pca_module3 = 3,      //  PCA_3
	pca_module4 = 4       //  PCA_4
}en_pca_module_t;

/**
 *******************************************************************************
 ** \brief PCA  �жϱ�־λ  �ж����λ
 ** \note           PCA_CCON�е�CCF0-CCF4��CF; PCA_ICLR�е�CCF0-CCF4��CF
 ******************************************************************************/
typedef enum
{
	pca_ccf0 = 0,
	pca_ccf1 = 1,
	pca_ccf2 = 2,
	pca_ccf3 = 3,
	pca_ccf4 = 4,
	pca_cf   = 7
}en_pca_ccficlr_t;

/**
 *******************************************************************************
 ** \brief PCA  ʱ�ӷ�Ƶѡ��ʱ��Դѡ��
 ** \note       PCA_CMOD   CPS[2:0]
 ******************************************************************************/
typedef enum
{
	pca_pclkdiv32 = 0,      // PCLK/32
	pca_pclkdiv16 = 1,      // PCLK/16
	pca_pclkdiv8  = 2,      // PCLK/8
	pca_pclkdiv4  = 3,      // PCLK/4
	pca_pclkdiv2  = 4,      // PCLK/2
	pca_tim0ovf   = 5,      // timer0 overflow
	pca_tim1ovf   = 6,      // timer1 overflow
	pca_eci       = 7       // ECI�ⲿʱ��
}en_pca_clksrc_t;

/**
 *******************************************************************************
 ** \brief PCA  ����Ƚ������ܿ���
 ** \note       PCA_CCAPMx   ECOM
 ******************************************************************************/
typedef enum
{
	Ecom_Disable = 0,
	Ecom_Enable  = 1
}en_pca_ecom_t;

/**
 *******************************************************************************
 ** \brief PCA  ���ز������λ
 ** \note       PCA_CCAPMx  CAPP
 ******************************************************************************/
typedef enum
{
	Capp_Disable = 0,
	Capp_Enable  = 1
}en_pca_capp_t;

/**
 *******************************************************************************
 ** \brief PCA  ���ز������λ
 ** \note       PCA_CCAPMx  CAPN
 ******************************************************************************/
typedef enum
{
	Capn_Disable = 0,
	Capn_Enable  = 1
}en_pca_capn_t;

/**
 *******************************************************************************
 ** \brief PCA  ƥ�����λ
 ** \note       PCA_CCAPMx  MAT
 ******************************************************************************/
typedef enum
{
	Mat_Disable = 0,
	Mat_Enable  = 1
}en_pca_mat_t;

/**
 *******************************************************************************
 ** \brief PCA  ��ת����λ
 ** \note       PCA_CCAPMx  TOG
 ******************************************************************************/
typedef enum
{
	Tog_Disable = 0,
	Tog_Enable  = 1
}en_pca_tog_t;

/**
 *******************************************************************************
 ** \brief PCA  PWM����λ
 ** \note       PCA_CCAPMx  PWM
 ******************************************************************************/
typedef enum
{
	Pwm8bit_Disable = 0,
	Pwm8bit_Enable  = 1
}en_pca_pwm8bit_t;

/**
 *******************************************************************************
 ** \brief PCA  EPWM����λ
 ** \note       PCA_EPWM  EPWM
 ******************************************************************************/
typedef enum
{
	Epwm_Disable = 0,
	Epwm_Enable  = 1
}en_pca_epwm_t;

/**
 *******************************************************************************
 ** \brief PCA  ��ʼ�����õĽṹ��
 ** \note       
 ******************************************************************************/
typedef struct
{
	en_pca_clksrc_t     pca_clksrc;           // PCA_CMOD CPS[2:0] 
	boolean_t           pca_cidl;                 // PCA_CMOD CIDL
	en_pca_ecom_t       pca_ecom;             // PCA_CCAPMx ECOM
	en_pca_capp_t       pca_capp;             // PCA_CCAPMx CAPP
	en_pca_capn_t       pca_capn;             // PCA_CCAPMx CAPN
	en_pca_mat_t        pca_mat;              // PCA_CCAPMx MAT
	en_pca_tog_t        pca_tog;              // PCA_CCAPMx TOG
	en_pca_pwm8bit_t    pca_pwm;              // PCA_CCAPMx PWM
	en_pca_epwm_t       pca_epwm;             // PCA_EPWM
	uint16_t            pca_ccap;             // PCA_CCAP
	uint8_t             pca_ccapl;            // PCA_CCAPL  PCA_CCAP�ĵ��ֽ�
	uint8_t             pca_ccaph;            // PCA_CCAPH  PCA_CCAP�ĸ��ֽ�
	uint16_t            pca_carr;             // PCA_CARR
}stc_pcaconfig_t;
/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
extern boolean_t Pca_GetItStatus(en_pca_ccficlr_t It_Src);
extern void Pca_ClrItStatus(en_pca_ccficlr_t It_Src);
extern void Pca_StartPca(boolean_t NewStatus);
extern void Pca_SetCidl(boolean_t NewStatus);
extern void Pca_Set4Wdte(boolean_t NewStatus);
extern void Pca_ConfPcaIt(boolean_t NewStatus);
extern void Pca_ConfModulexIt(en_pca_module_t Modulex, boolean_t NewStatus);
extern void Pca_M0Init(stc_pcaconfig_t* InitStruct);
extern void Pca_M1Init(stc_pcaconfig_t* InitStruct);
extern void Pca_M2Init(stc_pcaconfig_t* InitStruct);
extern void Pca_M3Init(stc_pcaconfig_t* InitStruct);
extern void Pca_M4Init(stc_pcaconfig_t* InitStruct);
extern uint16_t Pca_GetCnt(void);
extern void Pca_SetCnt(uint16_t cnt);
extern boolean_t Pca_GetOut(en_pca_module_t Modulex);
extern void Pca_SetCcap(en_pca_module_t Modulex, uint16_t Value);
extern uint16_t Pca_GetCcap(en_pca_module_t Modulex);
extern void Pca_SetCarr(uint16_t Value);
extern uint16_t Pca_GetCarr(void);
extern void Pca_SetCcapHL(en_pca_module_t Modulex, uint8_t ValueH, uint8_t ValueL);
extern void Pca_GetCcapHL(en_pca_module_t Modulex, uint8_t *ValueH, uint8_t *ValueL);

//@} // PcaGroup

#ifdef __cplusplus
#endif

#endif /* __PCA_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
