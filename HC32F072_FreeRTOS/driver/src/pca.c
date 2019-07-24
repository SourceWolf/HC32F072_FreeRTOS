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
/** \file pca.c
 **
 ** pca driver API.
 ** @link pca Group Some description @endlink
 **
 **   - 2019-04-09       First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "pca.h"

/**
 ******************************************************************************
 ** \addtogroup PCAGroup
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

/**
******************************************************************************
	** \brief  ��ȡ�ж�Դ�ı�־λ
	** @param  IT_Src : �ж�Դ��־λ
	** \retval FALSE ��TRUE
	**
******************************************************************************/
boolean_t Pca_GetItStatus(en_pca_ccficlr_t It_Src)
{
	return (((M0P_PCA->CCON)>>It_Src) & 1) > 0? TRUE : FALSE;
}

/**
******************************************************************************
	** \brief  ����ж�Դ�ı�־λ
	** @param  IT_Src : �ж�Դ��־λ
	** \retval ��
	**
******************************************************************************/
void Pca_ClrItStatus(en_pca_ccficlr_t It_Src)
{
	M0P_PCA->ICLR &= ~(uint32_t)(1<<It_Src);
}

/**
******************************************************************************
	** \brief  PCA ���������п���   PCA_CCON CR����λ
	** @param  NewStatus : TRUE �� FALSE
	** \retval ��
	**
******************************************************************************/
void Pca_StartPca(boolean_t NewStatus)
{
	SetBit((uint32_t)(&(M0P_PCA->CCON)), 6, NewStatus);
}

/**
******************************************************************************
	** \brief  PCA ����ģʽIDLE�£�PCA�Ƿ�ֹͣ��������
	** @param  NewStatus : TRUE �� FALSE
	** \retval ��
	**
******************************************************************************/
void Pca_SetCidl(boolean_t NewStatus)
{
	SetBit((uint32_t)(&(M0P_PCA->CMOD)), 7, NewStatus);
}

/**
******************************************************************************
	** \brief  PCA ģ��4�Ŀ��Ź�ʹ�ܿ���
	** @param  NewStatus : TRUE �� FALSE
	** \retval ��
	**
******************************************************************************/
void Pca_Set4Wdte(boolean_t NewStatus)
{
	SetBit((uint32_t)(&(M0P_PCA->CMOD)), 6, NewStatus);
}

/**
******************************************************************************
	** \brief  PCA �������жϿ���PCA_CMOD��CFIE����Ӧ�Ŀ����ж�λPCA_CCON�е�CF��PCA_ICLR�е�CF
	** @param  NewStatus : TRUE �� FALSE
	** \retval ��
	**
******************************************************************************/
void Pca_ConfPcaIt(boolean_t NewStatus)
{
	SetBit((uint32_t)(&(M0P_PCA->CMOD)), 0, NewStatus);
}

/**
******************************************************************************
	** \brief  PCA �Ƚϲ����ж�ʹ�ܿ���  PCA_CCAPMx��CCIE
	** @param  Modulex : pca_module0~4
	** @param  NewStatus : TRUE �� FALSE
	** \retval ��
	**
******************************************************************************/
void Pca_ConfModulexIt(en_pca_module_t Modulex, boolean_t NewStatus)
{
	switch(Modulex)
	{
		case pca_module0:
			SetBit((uint32_t)(&(M0P_PCA->CCAPM0)), 0, NewStatus);
			break;
		case pca_module1:
			SetBit((uint32_t)(&(M0P_PCA->CCAPM1)), 0, NewStatus);
			break;		
		case pca_module2:
			SetBit((uint32_t)(&(M0P_PCA->CCAPM2)), 0, NewStatus);
			break;
		case pca_module3:
			SetBit((uint32_t)(&(M0P_PCA->CCAPM3)), 0, NewStatus);
			break;
		case pca_module4:
			SetBit((uint32_t)(&(M0P_PCA->CCAPM4)), 0, NewStatus);
			break;
		default:
			break;
	}
}

/**
******************************************************************************
	** \brief  PCA ģ��0�ĳ�ʼ��
	** @param  InitStruct : PCA��ʼ�����õĽṹ��
	** \retval ��
	**
******************************************************************************/
void Pca_M0Init(stc_pcaconfig_t* InitStruct)
{
	M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
	M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
	M0P_PCA->CCAPM0_f.ECOM = InitStruct->pca_ecom;
	M0P_PCA->CCAPM0_f.CAPP = InitStruct->pca_capp;
	M0P_PCA->CCAPM0_f.CAPN = InitStruct->pca_capn;
	M0P_PCA->CCAPM0_f.MAT  = InitStruct->pca_mat;
	M0P_PCA->CCAPM0_f.TOG  = InitStruct->pca_tog;
	M0P_PCA->CCAPM0_f.PWM  = InitStruct->pca_pwm;
	M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
	if(InitStruct->pca_pwm == Pwm8bit_Enable)
	{
		M0P_PCA->CCAP0L_f.CCAP0 = InitStruct->pca_ccapl;
		M0P_PCA->CCAP0H_f.CCAP0 = InitStruct->pca_ccaph;
	}
	else
	{
		M0P_PCA->CCAP0_f.CCAP0 = InitStruct->pca_ccap;		
	}
	M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
	** \brief  PCA ģ��1�ĳ�ʼ��
	** @param  InitStruct : PCA��ʼ�����õĽṹ��
	** \retval ��
	**
******************************************************************************/
void Pca_M1Init(stc_pcaconfig_t* InitStruct)
{
	M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
	M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
	M0P_PCA->CCAPM1_f.ECOM = InitStruct->pca_ecom;
	M0P_PCA->CCAPM1_f.CAPP = InitStruct->pca_capp;
	M0P_PCA->CCAPM1_f.CAPN = InitStruct->pca_capn;
	M0P_PCA->CCAPM1_f.MAT  = InitStruct->pca_mat;
	M0P_PCA->CCAPM1_f.TOG  = InitStruct->pca_tog;
	M0P_PCA->CCAPM1_f.PWM  = InitStruct->pca_pwm;
	M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
	if(InitStruct->pca_pwm == Pwm8bit_Enable)
	{
		M0P_PCA->CCAP1L_f.CCAP1 = InitStruct->pca_ccapl;
		M0P_PCA->CCAP1H_f.CCAP1 = InitStruct->pca_ccaph;
	}
	else
	{
		M0P_PCA->CCAP1_f.CCAP1 = InitStruct->pca_ccap;		
	}
	M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
	** \brief  PCA ģ��2�ĳ�ʼ��
	** @param  InitStruct : PCA��ʼ�����õĽṹ��
	** \retval ��
	**
******************************************************************************/
void Pca_M2Init(stc_pcaconfig_t* InitStruct)
{
	M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
	M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
	M0P_PCA->CCAPM2_f.ECOM = InitStruct->pca_ecom;
	M0P_PCA->CCAPM2_f.CAPP = InitStruct->pca_capp;
	M0P_PCA->CCAPM2_f.CAPN = InitStruct->pca_capn;
	M0P_PCA->CCAPM2_f.MAT  = InitStruct->pca_mat;
	M0P_PCA->CCAPM2_f.TOG  = InitStruct->pca_tog;
	M0P_PCA->CCAPM2_f.PWM  = InitStruct->pca_pwm;
	M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
	if(InitStruct->pca_pwm == Pwm8bit_Enable)
	{
		M0P_PCA->CCAP2L_f.CCAP2 = InitStruct->pca_ccapl;
		M0P_PCA->CCAP2H_f.CCAP2 = InitStruct->pca_ccaph;
	}
	else
	{
		M0P_PCA->CCAP2_f.CCAP2 = InitStruct->pca_ccap;		
	}
	M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
	** \brief  PCA ģ��3�ĳ�ʼ��
	** @param  InitStruct : PCA��ʼ�����õĽṹ��
	** \retval ��
	**
******************************************************************************/
void Pca_M3Init(stc_pcaconfig_t* InitStruct)
{
	M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
	M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
	M0P_PCA->CCAPM3_f.ECOM = InitStruct->pca_ecom;
	M0P_PCA->CCAPM3_f.CAPP = InitStruct->pca_capp;
	M0P_PCA->CCAPM3_f.CAPN = InitStruct->pca_capn;
	M0P_PCA->CCAPM3_f.MAT  = InitStruct->pca_mat;
	M0P_PCA->CCAPM3_f.TOG  = InitStruct->pca_tog;
	M0P_PCA->CCAPM3_f.PWM  = InitStruct->pca_pwm;
	M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
	if(InitStruct->pca_pwm == Pwm8bit_Enable)
	{
		M0P_PCA->CCAP3L_f.CCAP3 = InitStruct->pca_ccapl;
		M0P_PCA->CCAP3H_f.CCAP3 = InitStruct->pca_ccaph;
	}
	else
	{
		M0P_PCA->CCAP3_f.CCAP3 = InitStruct->pca_ccap;		
	}
	M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
	** \brief  PCA ģ��4�ĳ�ʼ��
	** @param  InitStruct : PCA��ʼ�����õĽṹ��
	** \retval ��
	**
******************************************************************************/
void Pca_M4Init(stc_pcaconfig_t* InitStruct)
{
	M0P_PCA->CMOD_f.CPS = InitStruct->pca_clksrc;
	M0P_PCA->CMOD_f.CIDL = InitStruct->pca_cidl;
	M0P_PCA->CCAPM4_f.ECOM = InitStruct->pca_ecom;
	M0P_PCA->CCAPM4_f.CAPP = InitStruct->pca_capp;
	M0P_PCA->CCAPM4_f.CAPN = InitStruct->pca_capn;
	M0P_PCA->CCAPM4_f.MAT  = InitStruct->pca_mat;
	M0P_PCA->CCAPM4_f.TOG  = InitStruct->pca_tog;
	M0P_PCA->CCAPM4_f.PWM  = InitStruct->pca_pwm;
	M0P_PCA->EPWM_f.EPWM   = InitStruct->pca_epwm;
	if(InitStruct->pca_pwm == Pwm8bit_Enable)
	{
		M0P_PCA->CCAP4L_f.CCAP4 = InitStruct->pca_ccapl;
		M0P_PCA->CCAP4H_f.CCAP4 = InitStruct->pca_ccaph;
	}
	else
	{
		M0P_PCA->CCAP4_f.CCAP4 = InitStruct->pca_ccap;		
	}
	M0P_PCA->CARR_f.CARR    = InitStruct->pca_carr;
}

/**
******************************************************************************
	** \brief  PCA ��ȡCNT�Ĵ�������ֵ
	** @param  ��
	** \retval CNT�ĵͰ���ֵ
	**
******************************************************************************/
uint16_t Pca_GetCnt(void)
{
	return (uint16_t)(M0P_PCA->CNT);
}

/**
******************************************************************************
	** \brief  PCA ��CNT�Ĵ���д����ֵ
	** @param  cnt : ��Ҫд�����ֵ
	** \retval ��
	**
******************************************************************************/
void Pca_SetCnt(uint16_t cnt)
{
	if(GetBit((uint32_t)(&(M0P_PCA->CCON)), 6)==TRUE)
	{
		Pca_StartPca(FALSE);
		M0P_PCA->CNT_f.CNT = cnt;		
		Pca_StartPca(TRUE);		
	}
	else
	{
		M0P_PCA->CNT_f.CNT = cnt;
	}

}

/**
******************************************************************************
	** \brief  PCA ����ָ��ͨ���Ƚϸ��������־�Ĵ�����ֵ
	** @param  Modulex : ͨ����x=0��1��2��3��4
	** \retval TRUE �� FALSE
	**
******************************************************************************/
boolean_t Pca_GetOut(en_pca_module_t Modulex)
{
	return GetBit((uint32_t)(&(M0P_PCA->CCAPO)), Modulex);
}

/**
******************************************************************************
	** \brief  PCA ���ñȽϲ���16λ�Ĵ���CCAPx��ֵ
	** @param  Modulex : ͨ����x=0��1��2��3��4
	** @param  Value:  ��Ҫ���õ�ֵ
	** \retval ��
	**
******************************************************************************/
void Pca_SetCcap(en_pca_module_t Modulex, uint16_t Value)
{
	switch(Modulex)
	{
		case 0:
			M0P_PCA->CCAP0_f.CCAP0 = Value;
		break;
		case 1:
			M0P_PCA->CCAP1_f.CCAP1 = Value;
			break;
		case 2:
			M0P_PCA->CCAP2_f.CCAP2 = Value;
			break;
		case 3:
			M0P_PCA->CCAP3_f.CCAP3 = Value;
			break;
		case 4:
			M0P_PCA->CCAP4_f.CCAP4 = Value;
			break;
		default:
			break;
	}	
}

/**
******************************************************************************
	** \brief  PCA ��ȡ�Ƚϲ���16λ�Ĵ���CCAPx��ֵ
	** @param  Modulex : ͨ����x=0��1��2��3��4
	** \retval CCAPx��ֵ��x=0��1��2��3��4
	**
******************************************************************************/
uint16_t Pca_GetCcap(en_pca_module_t Modulex)
{
	uint16_t tmp;
	switch(Modulex)
	{
		case 0:
			tmp = M0P_PCA->CCAP0_f.CCAP0;
		break;
		case 1:
			tmp = M0P_PCA->CCAP1_f.CCAP1;
			break;
		case 2:
			tmp = M0P_PCA->CCAP2_f.CCAP2;
			break;
		case 3:
			tmp = M0P_PCA->CCAP3_f.CCAP3;
			break;
		case 4:
			tmp = M0P_PCA->CCAP4_f.CCAP4;
			break;
		default:
			break;
	}
	return tmp;
}

/**
******************************************************************************
	** \brief  PCA �����Զ���װ�ؼĴ�����ֵ
	** @param  ��
	** \retval ��
	**
******************************************************************************/
void Pca_SetCarr(uint16_t Value)
{
	M0P_PCA->CARR_f.CARR = Value;
}

/**
******************************************************************************
	** \brief  PCA ��ȡ�Զ���װ�ؼĴ�����ֵ
	** @param  ��
	** \retval ��
	**
******************************************************************************/
uint16_t Pca_GetCarr(void)
{
	return M0P_PCA->CARR_f.CARR;
}

/**
******************************************************************************
	** \brief  PCA ���ñȽϲ���Ĵ����ĸ�8λ�͵�8λ
	** @param  Modulex : ͨ����x=0��1��2��3��4
	** @param  ValueH : Ҫд���8λ����ֵ
	** @param  ValueL : Ҫд���8λ����ֵ
	** \retval ��
	**
******************************************************************************/
void Pca_SetCcapHL(en_pca_module_t Modulex, uint8_t ValueH, uint8_t ValueL)
{
	switch(Modulex)
	{
		case 0:
			M0P_PCA->CCAP0H_f.CCAP0 = ValueH;
			M0P_PCA->CCAP0L_f.CCAP0 = ValueL;
			break;
		case 1:
			M0P_PCA->CCAP1H_f.CCAP1 = ValueH;
			M0P_PCA->CCAP1L_f.CCAP1 = ValueL;
			break;
		case 2:
			M0P_PCA->CCAP2H_f.CCAP2 = ValueH;
			M0P_PCA->CCAP2L_f.CCAP2 = ValueL;
			break;
		case 3:
			M0P_PCA->CCAP3H_f.CCAP3 = ValueH;
			M0P_PCA->CCAP3L_f.CCAP3 = ValueL;
			break;
		case 4:
			M0P_PCA->CCAP4H_f.CCAP4 = ValueH;
			M0P_PCA->CCAP4L_f.CCAP4 = ValueL;
			break;
        default:
            break;
	}
}

/**
******************************************************************************
	** \brief  PCA ��ȡ�Ƚϲ���Ĵ����ĸ�8λ�͵�8λ
	** @param  Modulex : ͨ����x=0��1��2��3��4
	** @param  ValueH : CCAPx��8λ����ֵ
	** @param  ValueL : CCAPx��8λ����ֵ
	** \retval ��
	**
******************************************************************************/
void Pca_GetCcapHL(en_pca_module_t Modulex, uint8_t *ValueH, uint8_t *ValueL)
{
	switch(Modulex)
	{
		case 0:
			*ValueH = M0P_PCA->CCAP0H_f.CCAP0;
			*ValueL = M0P_PCA->CCAP0L_f.CCAP0;
			break;
		case 1:
			*ValueH = M0P_PCA->CCAP1H_f.CCAP1;
			*ValueL = M0P_PCA->CCAP1L_f.CCAP1;
			break;
		case 2:
			*ValueH = M0P_PCA->CCAP2H_f.CCAP2;
			*ValueL = M0P_PCA->CCAP2L_f.CCAP2;
			break;
		case 3:
			*ValueH = M0P_PCA->CCAP3H_f.CCAP3;
			*ValueL = M0P_PCA->CCAP3L_f.CCAP3;
			break;
		case 4:
			*ValueH = M0P_PCA->CCAP4H_f.CCAP4;
			*ValueL = M0P_PCA->CCAP4L_f.CCAP4;
			break;
        default:
            break;
	}	
}
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/





