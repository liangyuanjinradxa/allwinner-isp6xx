/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef _AWAIISP_
#define _AWAIISP_

#ifdef __cplusplus
       extern "C" {
#endif

/**
  error code
*/
#define AWAIISP_SUCCESS                       (0x00000000)
#define ERR_AWAIISP_BUSY                      (0x00000001)
#define ERR_AWAIISP_NO_MEM                    (0x00000002)
#define ERR_AWAIISP_NULL_PTR                  (0x00000004)
#define ERR_AWAIISP_SYS_NOTREADY              (0x00000008)
#define ERR_AWAIISP_INVALID_DEVID             (0x00000010)
#define ERR_AWAIISP_ILLEGAL_PARAM             (0x00000011)
#define ERR_AWAIISP_NOT_SUPPORT               (0x00000012)

#define AWAIISP_FILE_PATH_MAX  (128)

#define AWAIISP_RESERVE_PARAM_NUM (8)
#define AWAIISP_RESERVE_PARAM_LEN (AWAIISP_RESERVE_PARAM_NUM * sizeof(int))

typedef struct awaiisp_config_param {
    /**
      Specify the version of the model file, [UNUSED].
    */
    int model_version;
    /**
      Specify the path to the weight file.
    */
    char weight_file[AWAIISP_FILE_PATH_MAX];
    /**
      Specify the path to the task queue file.
    */
    char task_q_file[AWAIISP_FILE_PATH_MAX];
    /**
      Pointer to the AIISP internal information structure.
    */
    void *aiisp_inform;
    /**
      Specify the number of AIISP tasks.
    */
    int aiisp_task_num;
    /**
      Specify the total number of AIISP registers.
    */
    int aiisp_total_reg_num;
    /**
      Reserved fields for future use.
    */
    int reserve[AWAIISP_RESERVE_PARAM_NUM];
} awaiisp_config_param;

int awaiisp_start(int isp, awaiisp_config_param *config_param);

int awaiisp_stop(int isp);

int awaiisp_update_config(int isp, awaiisp_config_param *pconfig_param);

#ifdef __cplusplus
       }
#endif

#endif
