/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
* All rights reserved.
*
* File : ve_interface_ext.h
* Description :
* History :
*   Author  : xyliu <xyliu@allwinnertech.com>
*   Date    : 2016/04/13
*   Comment :
*
*/


#ifndef _VENCODER_EXT_V2_H
#define _VENCODER_EXT_V2_H

#ifdef CONFIG_AW_VIDEO_KERNEL_ENC
#else
#include <stddef.h>
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define VCU_ONLINE_MODE 3

#define MAX_RC_GOP_SIZE                   256

#define JPEG_MAX_SEG_LEN (65523)
typedef struct VencBinImageParam {
	unsigned int enable;
	unsigned int moving_th;//range[1,31], 1:all frames are moving,
						   //            31:have no moving frame, default: 20
} VencBinImageParam;

typedef struct VencGetBinImageBufInfo {
	unsigned int   max_size;
	unsigned char *buf;
} VencGetBinImageBufInfo;

typedef struct VencGetMvInfoBufInfo {
	unsigned int   max_size;
	unsigned char *buf;
} VencGetMvInfoBufInfo;

typedef struct VencEnvLvRange {
	int env_lv_high_th;
	int env_lv_low_th;
	int env_lv_coef;  //range[0,15]
} VencEnvLvRange;

typedef union {
	unsigned char val;
	struct {
		unsigned char qp    : 6;
		unsigned char skip  : 1;
		unsigned char en    : 1;
	} reg;
} uMbQpMap;

typedef union {
	unsigned int val;
	uMbQpMap     mb[4];
} uCtuQpMap;

typedef struct {
	// all these average value is for mb16x16
	unsigned int avg_mad;
	unsigned int avg_sse;
	unsigned int avg_qp;
	double avg_psnr;
} VencMBSumInfo_V2;

typedef enum ePERSPFUNC {
	Persp_Only,
	Persp_LDC
} ePerspFunc;

typedef enum eLENSDISTMODEL {
	DistModel_WideAngle,
	DistModel_FishEye
} eLensDistModel;

typedef enum eMOUNTTYPE {

	Mount_Top,

	Mount_Wall,

	Mount_Bottom
} eMountType;

typedef enum eWARPTYPE {

	Warp_LDC,

	Warp_LDC_Pro,

	Warp_Pano180,

	Warp_Pano360,

	Warp_Normal,

	Warp_Fish2Wide,

	Warp_Perspective,

	Warp_BirdsEye,

	Warp_User,
	Warp_Zoom,
} eWarpType;

typedef struct {
	char  src_file[256];
	char  dst_file[256];
//Top
	int img_format;
	int yuv_dns_en;
	int frame_num;
	int input_width;
	int input_height;
	int output_width;
	int output_height;
	int bTop_en;
	int rotAngle;
	int bMirror;
	int bLBC_en;
	int lbc_scale_mode;  //0 USE SMALLER RATIO   1:use bigger ratio
	int bSC_en;
	int bCrop_en;
	int crop_x;
	int crop_y;
	int crop_width;
	int crop_height;
//GDC
	int bGDC_en;
	int bByPass;
	eWarpType warpMode;
	eMountType mountMode;
	int calib_pic_w;
	int calib_pic_h;
	float fx;
	float fy;
	float cx;
	float cy;
	float fx_scale;
	float fy_scale;
	float cx_scale;
	float cy_scale;
	char path_lut_ldc_pro[256];
	enum eLENSDISTMODEL  eLensDistModel;
	float distCoef_wide_ra[3];
	float distCoef_wide_ta[2];
	float distCoef_fish_k[4];
	int centerOffsetX;
	int centerOffsetY;
	int rotateAngle;
	int radialDistortCoef;
	int trapezoidDistortCoef;
	int fanDistortCoef;
	int pan;
	int tilt;
	int zoomH;
	int zoomV;
	int scale;
	int innerRadius;
	float roll;
	float pitch;
	float yaw;
	ePerspFunc perspFunc;
	float perspectiveProjMat[9];
	char  birds_file[256];
	int birdsImg_width;
	int birdsImg_height;
	float mountHeight;
	float roiDist_ahead;
	float roiDist_left;
	float roiDist_right;
	float roiDist_bottom;
//Adscaler
	int peaking_en;
	int peaking_clamp;
	int peak_m;
	int th_strong_edge;
	int peak_weights_strength;

//debug
	int blk_format;//0=16x16,1=32x32,2=16x8,3=8x8
	//for user mode
	short *lut_x;
	short *lut_y;
} sInputPara;

typedef enum VENC_INDEXTYPE_PLATFORM_V2 {

	VENC_IndexParam_PlatformV2_Start = 0x3f000000,

	/**< reference type: VencMBSumInfo_V2 */
	VENC_IndexParamMBSumInfoOutput_V2,

	/**< reference type: unsigned int; 0: sp2305 1: c2398*/
	VENC_IndexParamSensorType,

	/**< reference type: VencBinImageParam */
	VENC_IndexParamEnableGetBinImage,

	/**< reference type: unsigned char* */
	VENC_IndexParamGetBinImageData,

	/**< reference type: unsigned int; 0: disable, 1: enable*/
	VENC_IndexParamEnableMvInfo,

	/**< reference type: unsigned char* */
	VENC_IndexParamGetMvInfoData,

	/**< reference type: unsigned int */
	VENC_IndexParamSetLVAdjTh,

	/**< reference type: VencEnvLvRange */
	VENC_IndexParamSetEnvLvTh,

	/**< reference type: VencVbrParam */
	VENC_IndexParamSetVbrParam,

	/**< reference type: Set or Get VencMotionSearchParam* */
	VENC_IndexParamMotionSearchParam,

	/**< reference type: Get VencMotionSearchRegin* */
	VENC_IndexParamMotionSearchResult,

	/**< reference type: TEST WB YUV* */
	VENC_IndexParamEnableWbYuv,

	/**< reference type: sInputPara*/
	VENC_IndexParamGdcConfig,
	/**< reference type: VencCropInfo*/
	VENC_IndexParamCropConfig,

	/**< reference type: unsinged int */
	VENC_IndexParamIspbeEn,

	/**< reference type: unsinged int */
	VENC_IndexParamIspbeEmbedEn,

	VENC_IndexParamIspbeTopConfig,

	VENC_IndexParamSharpConfig,

	VENC_IndexParamIspbeLdciConfig,

	/**< reference type: unsigned int; 0: have enought vbv buf, 1: vbv buf is full*/
	VENC_IndexParamBSbufIsFull,

	/**< reference type: int */
	VENC_IndexParamEnvLv,

	/**< reference type: int */
	VENC_IndexParamAeWeightLum,

	/**< reference type: eCameraStatus */
	VENC_IndexParamEnCameraMove,

	/**< reference type: sIspAeStatus */
	VENC_IndexParamIspAeStatus,

	/**< reference type: VencVe2IspParam */
	VENC_IndexParamVe2IspParam,

	/**< reference type: VencIspVeLinkParam*/
	VENC_IndexParamIspVeLinkParam, /*0x3F00001B*/

	/**< reference type: unsigned int; 0: disbale, 1: enable*/
	VENC_IndexParamEnableCheckOnlineStatus,

	/**< reference type: unsigned int; 0: not ready, 1: ready*/
	VENC_IndexParamCheckOnlineStatus,

	/**< reference type: int [0,1]*/
	/*every reg of frame start with 0xffffffff, and add some important info, such as:
	  0xffffffff      0x00020001,          0x00010001       0x00000041
	  startCode       channelId & bOnline  bk_id & sensor_id  frameCnt
	*/
	VENC_IndexParamDebugSetupDumpRegInfo,

	/**< reference type: unsigned int* */
	VENC_IndexParamDebugGetRegInfoData,

	/**< reference type: int [0,1] */
	VENC_IndexParamEncAndDecCase, /*encoder and decoder run at the same time. need reset the whole ve*/

	/* set RecRef buf reduce function; type: int; 0: disbale, 1: enable*/
	VENC_IndexParamEnableRecRefBufReduceFunc,

	VENC_IndexParamCheckIsReadyToEncode,

	/**< reference type: unsigned int */
	/* not encode some frame, such as: not encode the begining 10 frames */
	VENC_IndexParamDropFrame,

	/**< reference type: VencAdvFgProject* */
	VENC_IndexParamAdvanceFgProject,

	/**< reference type: VencAdvCuPred* */
	VENC_IndexParamAdvanceCuPred,

	/**< reference type: VencAdvSkipBias* */
	VENC_IndexParamAdvanceSkipBias,

	/**< reference type: VencAdvHierarchicalQp* */
	VENC_IndexParamAdvanceHierarchicalQp,

	/**< reference type: VencAdvSvcParam* */
	VENC_IndexParamAdvanceSvcParam,

	/**< reference type: VencAdvDeblur* */
	VENC_IndexParamAdvanceDeblur,

	/**< reference type: int*/
	VENC_IndexParamAeGain,
	/**< reference type: unsigned int; 0: disbale, 1: enable*/
	VENC_IndexParamEnableEncppSharp,//adapt rt-media

} VENC_INDEXTYPE_PLATFORM_V2;

#ifdef __cplusplus
}
#endif

#endif

