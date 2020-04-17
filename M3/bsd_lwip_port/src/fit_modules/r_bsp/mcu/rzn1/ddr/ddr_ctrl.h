/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1322 $
 * $Date: 2019-03-02 01:34:20 +0000 (Sat, 02 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  ddr_ctrl.h
 * Description  :  DDR Control Definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __DDR_CTRL_H_
#define __DDR_CTRL_H_

#include <stdint.h>

#ifdef DDR2
#include "1Gx16_DDR2-500.h"
#else
#include "2Gx16_DDR3-1000.h"
#endif

#if defined(DDR2)
#define DDR_SIZE  0x8000000
#else
#define DDR_SIZE 0x20000000
#endif

const uint32_t ddr_00_87[] =
{
DDR_CTL_00_DATA,
DDR_CTL_01_DATA,
DDR_CTL_02_DATA,
DDR_CTL_03_DATA,
DDR_CTL_04_DATA,
DDR_CTL_05_DATA,
DDR_CTL_06_DATA,
DDR_CTL_07_DATA,
DDR_CTL_08_DATA,
DDR_CTL_09_DATA,

DDR_CTL_10_DATA,
DDR_CTL_11_DATA,
DDR_CTL_12_DATA,
DDR_CTL_13_DATA,
DDR_CTL_14_DATA,
DDR_CTL_15_DATA,
DDR_CTL_16_DATA,
DDR_CTL_17_DATA,
DDR_CTL_18_DATA,
DDR_CTL_19_DATA,

DDR_CTL_20_DATA,
DDR_CTL_21_DATA,
DDR_CTL_22_DATA,
DDR_CTL_23_DATA,
DDR_CTL_24_DATA,
DDR_CTL_25_DATA,
DDR_CTL_26_DATA,
DDR_CTL_27_DATA,
DDR_CTL_28_DATA,
DDR_CTL_29_DATA,

DDR_CTL_30_DATA,
DDR_CTL_31_DATA,
DDR_CTL_32_DATA,
DDR_CTL_33_DATA,
DDR_CTL_34_DATA,
DDR_CTL_35_DATA,
DDR_CTL_36_DATA,
DDR_CTL_37_DATA,
DDR_CTL_38_DATA,
DDR_CTL_39_DATA,

DDR_CTL_40_DATA,
DDR_CTL_41_DATA,
DDR_CTL_42_DATA,
DDR_CTL_43_DATA,
DDR_CTL_44_DATA,
DDR_CTL_45_DATA,
DDR_CTL_46_DATA,
DDR_CTL_47_DATA,
DDR_CTL_48_DATA,
DDR_CTL_49_DATA,

DDR_CTL_50_DATA,
DDR_CTL_51_DATA,
DDR_CTL_52_DATA,
DDR_CTL_53_DATA,
DDR_CTL_54_DATA,
DDR_CTL_55_DATA,
DDR_CTL_56_DATA,
DDR_CTL_57_DATA,
DDR_CTL_58_DATA,
DDR_CTL_59_DATA,

DDR_CTL_60_DATA,
DDR_CTL_61_DATA,
DDR_CTL_62_DATA,
DDR_CTL_63_DATA,
DDR_CTL_64_DATA,
DDR_CTL_65_DATA,
DDR_CTL_66_DATA,
DDR_CTL_67_DATA,
DDR_CTL_68_DATA,
DDR_CTL_69_DATA,

DDR_CTL_70_DATA,
DDR_CTL_71_DATA,
DDR_CTL_72_DATA,
DDR_CTL_73_DATA,
DDR_CTL_74_DATA,
DDR_CTL_75_DATA,
DDR_CTL_76_DATA,
DDR_CTL_77_DATA,
DDR_CTL_78_DATA,
DDR_CTL_79_DATA,

DDR_CTL_80_DATA,
DDR_CTL_81_DATA,
DDR_CTL_82_DATA,
DDR_CTL_83_DATA,
DDR_CTL_84_DATA,
DDR_CTL_85_DATA,
DDR_CTL_86_DATA,
DDR_CTL_87_DATA,
DDR_CTL_88_DATA,
DDR_CTL_89_DATA,

DDR_CTL_90_DATA,
DDR_CTL_91_DATA,
DDR_CTL_92_DATA, };

const uint32_t ddr_350_374[] =
{
DDR_CTL_350_DATA,
DDR_CTL_351_DATA,
DDR_CTL_352_DATA,
DDR_CTL_353_DATA,
DDR_CTL_354_DATA,
DDR_CTL_355_DATA,
DDR_CTL_356_DATA,
DDR_CTL_357_DATA,
DDR_CTL_358_DATA,
DDR_CTL_359_DATA,

DDR_CTL_360_DATA,
DDR_CTL_361_DATA,
DDR_CTL_362_DATA,
DDR_CTL_363_DATA,
DDR_CTL_364_DATA,
DDR_CTL_365_DATA,
DDR_CTL_366_DATA,
DDR_CTL_367_DATA,
DDR_CTL_368_DATA,
DDR_CTL_369_DATA,

DDR_CTL_370_DATA,
DDR_CTL_371_DATA,
DDR_CTL_372_DATA,
DDR_CTL_373_DATA,
DDR_CTL_374_DATA, };

#endif /* __DDR_CTRL_H_ */
