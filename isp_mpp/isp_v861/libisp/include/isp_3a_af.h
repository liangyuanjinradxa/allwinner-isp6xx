
/*
 ******************************************************************************
 *
 * isp_3a_af.h
 *
 * Hawkview ISP - isp_3a_af.h module
 *
 * Copyright (c) 2016 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Version		  Author         Date		    Description
 *
 *   3.0		  Yang Feng   	2016/03/31	VIDEO INPUT
 *
 *****************************************************************************
 */

#ifndef _ISP_3A_AF_LIB_H_
#define _ISP_3A_AF_LIB_H_

/* focus range 0~1024 */
#define ISP_AF_DIR_TH	24
#define ISP_AF_DIR_TH_MAX	96

#define FOCUS_MIN	0
#define FOCUS_MAX	1024

#define ISP_AF_START_FRAME_NUM 3

#if defined LIBISP_DISABLED_AF
#define ISP_LIB_USE_AF		0
#else
#define ISP_LIB_USE_AF		1
#endif

/* pdaf */
#define PD_MAX_WINS 256
#define ALG_WIN_W 8
#define ALG_WIN_H 6
#define MIN_SPLIT_W 8
#define MIN_SPLIT_H 6
#define MAX_SPLIT_W 24
#define MAX_SPLIT_H 18
#define MAX_PD_WIDTH 2048
#define MAX_PD_HEIGHT 1536
#define MAX_BLOCK_W (MAX_PD_WIDTH / MIN_SPLIT_W)
#define MAX_BLOCK_H (MAX_PD_HEIGHT / MIN_SPLIT_H)
#define MAX_BLOCK_S (MAX_BLOCK_W > MAX_BLOCK_H ? MAX_BLOCK_W : MAX_BLOCK_H)
#define FFT_SIZE_NEXT_POW2(size) ((size <= 1) ? 1 : (1 << (32 - __builtin_clz(size - 1))))
#define MAX_FFT_SIZE FFT_SIZE_NEXT_POW2(2 * MAX_BLOCK_S)

typedef struct isp_af_ini_cfg {
	HW_S32 af_use_otp;
	HW_S32 vcm_min_code;
	HW_S32 vcm_max_code;
	HW_S32 af_interval_time;
	HW_S32 af_speed_ind;
	HW_S32 af_auto_fine_en;
	HW_S32 af_single_fine_en;
	HW_S32 af_fine_step;
	HW_S32 af_move_cnt;
	HW_S32 af_still_cnt;
	HW_S32 af_move_monitor_cnt;
	HW_S32 af_still_monitor_cnt;
	HW_S32 af_stable_min;
	HW_S32 af_stable_max;
	HW_S32 af_low_light_lv;
	HW_S32 af_near_tolerance;
	HW_S32 af_far_tolerance;
	HW_S32 af_tolerance_off;
	HW_S32 af_peak_th;
	HW_S32 af_dir_th;
	HW_S32 af_change_ratio;
	HW_S32 af_move_minus;
	HW_S32 af_still_minus;
	HW_S32 af_scene_motion_th;
	HW_S32 af_tolerance_tbl_len;
	HW_S32 af_std_code_tbl[20];
	HW_S32 af_tolerance_value_tbl[20];
	HW_U8 af_delay_frame;
	HW_U8 af_pdaf_pd_w_num;
	HW_U8 af_pdaf_pd_h_num;
	HW_U8 af_pdaf_dcc_map_w_num;
	HW_U8 af_pdaf_dcc_map_h_num;
	HW_U8 af_pdaf_gain_map_w_num;
	HW_U8 af_pdaf_gain_map_h_num;
	HW_U8 af_pdaf_win_conf_th;
	HW_U8 af_pdaf_weight_conf_th;
	HW_S16 af_pdaf_defocus_begin_th;
	HW_S16 af_pdaf_max_step;
	HW_S16 af_pdaf_defocus_step0_th;
	HW_S16 af_pdaf_defocus_step0_coef;
	HW_S16 af_pdaf_defocus_step1_th;
	HW_S16 af_pdaf_defocus_step1_coef;
	HW_S16 af_pdaf_defocus_step2_th;
	HW_S16 af_pdaf_defocus_step2_coef;
	HW_S16 af_pdaf_defocus_continue_th;
	HW_U8 af_pdaf_delay;
	HW_U8 af_pdaf_pd_err_th1;
	HW_U8 af_pdaf_pd_err_th2;
	HW_S16 af_pdaf_weight_win[64];
	HW_U8 af_pdaf_algo_type;
	HW_U8 af_pdaf_algo_touch_en;
	HW_U8 af_pdaf_algo_calc_tbl[48];
	HW_U8 af_pdaf_algo_conf_th;
	HW_U8 af_pdaf_algo_blk_calc_times;
	HW_U8 af_pdaf_algo_conf_coef;
	HW_U8 af_pdaf_algo_overexp_th;
	HW_U8 af_touch_dist_ind;
} af_ini_cfg_t;

enum auto_focus_run_mode {
	AUTO_FOCUS_MANUAL	= 0,
	AUTO_FOCUS_CONTINUEOUS	= 1,
	AUTO_FOCUS_TOUCH	= 2,
	AUTO_FOCUS_SNAP		= 3,
};

enum auto_focus_metering_mode {
	AUTO_FOCUS_METERING_AVERAGE		= 0,
	AUTO_FOCUS_METERING_CENTER_WEIGHTED	= 1,
	AUTO_FOCUS_METERING_SPOT		= 2,
	AUTO_FOCUS_METERING_MATRIX		= 3,
	AUTO_FOCUS_METERING_ROI			= 4,
};

enum auto_focus_range_new {
	AUTO_FOCUS_RANGE_AUTO		= 0,
	AUTO_FOCUS_RANGE_NORMAL		= 1,
	AUTO_FOCUS_RANGE_MACRO		= 2,
	AUTO_FOCUS_RANGE_INFINITY	= 3,
};

enum auto_focus_status {
	AUTO_FOCUS_STATUS_IDLE		= 0,
	AUTO_FOCUS_STATUS_BUSY		= 1,
	AUTO_FOCUS_STATUS_REACHED	= 2,
	AUTO_FOCUS_STATUS_APPROCH	= 3,
	AUTO_FOCUS_STATUS_REFOCUS	= 4,
	AUTO_FOCUS_STATUS_FAILED	= 5,
};

enum isp_pdaf_mode {
	PDAF_CLOSE           = 0,
	PDAF_EMBED_DATA      = 1,
	PDAF_VC_DATA         = 2,
	PDAF_RAW_DATA        = 3,
};

typedef struct isp_af_test_config {
	HW_S32 isp_test_mode;
	HW_S32 isp_test_focus;
	HW_S32 focus_start;
	HW_S32 focus_step;
	HW_S32 focus_end;
	HW_S32 focus_change_interval;
	HW_S32 af_en;

} af_test_config_t;

typedef enum isp_af_param_type {
	ISP_AF_INI_DATA,
	ISP_AF_TRIGGER,
	ISP_AF_PRINT_INFO,
	ISP_AF_BUILD_TOUCH_WEIGHT,
	ISP_AF_PARAM_TYPE_MAX,
} af_param_type_t;

struct vcm_para {
	HW_S32 vcm_max_code;
	HW_S32 vcm_min_code;
};

struct otp_pdaf_info {
	unsigned short mode;
	unsigned short pattern_mode;
	unsigned short dir;
	unsigned short ddc_map_width;
	unsigned short ddc_map_height;
	unsigned short dcc_map_table_1[PD_MAX_WINS];
	unsigned short dcc_map_table_2[PD_MAX_WINS];
	unsigned short gain_map_width;
	unsigned short gain_map_height;
	unsigned short gain_map_table_1[PD_MAX_WINS];
	unsigned short gain_map_table_2[PD_MAX_WINS];
};

struct isp_pdaf_config {
	HW_U8 pdaf_entity_id;
	HW_U16 pdaf_video_in_chn;
	HW_U8 pdaf_video_init_en;
	HW_U8 pdaf_en;
	HW_U32 pdaf_width;
	HW_U32 pdaf_height;
	struct otp_pdaf_info *otp_pdaf_info;
};

/* struct auto_focus_settings - Stores the auto focuse related settings. */
typedef struct isp_af_settings {
	HW_S32 focus_absolute;
	HW_S32 focus_relative;
	enum auto_focus_run_mode af_mode;
	enum auto_focus_metering_mode af_metering_mode;
	enum auto_focus_range_new af_range;
	bool focus_lock;
	struct isp_h3a_coor_win af_coor;
	HW_S16 af_pdaf_noise_ref;
} isp_af_settings_t;

typedef struct isp_af_param {
	af_param_type_t type;
	HW_S32 isp_platform_id;
	HW_S32 af_frame_id;
	af_ini_cfg_t af_ini;
	HW_S32 focus_absolute;
	HW_S32 focus_relative;
	enum auto_focus_run_mode af_run_mode;
	enum auto_focus_metering_mode af_metering_mode;
	enum auto_focus_range_new af_range;
	struct vcm_para vcm;
	bool focus_lock;
	isp_sensor_info_t sensor_info;
	af_test_config_t test_cfg;
	HW_S32 auto_focus_trigger;
	HW_S32 mov;
	isp_af_settings_t af_settings;
	struct isp_pdaf_config pdaf_cfg;
	struct isp_offset blc_offset;
} af_param_t;

typedef struct isp_af_stats {
	struct isp_af_stats_s *af_stats;
} af_stats_t;

#define AF_PRINT_LENGTH 8192
typedef struct isp_af_result {
	enum auto_focus_status af_status_output;
	HW_U32 last_code_output;
	HW_U32 real_code_output;
	HW_U32 std_code_output;
	HW_U16 af_sap_lim_output;
	HW_U32 af_sharp_output;
	char af_printf_out[AF_PRINT_LENGTH];
} af_result_t;

typedef struct isp_af_core_ops {
	HW_S32 (*isp_af_set_params)(void *af_core_obj, af_param_t *param, af_result_t *result);
	HW_S32 (*isp_af_get_params)(void *af_core_obj, af_param_t **param);
	HW_S32 (*isp_af_run)(void *af_core_obj, af_stats_t *stats, af_result_t *result);
} isp_af_core_ops_t;

enum isp_pd_pattern_mode {
	PDAF_2_2OCL_FULL_RESOLUTION  = 0,
	PDAF_2_2OCL_Vbin             = 1,
	PDAF_2_2OCL_HVbin            = 2,
	PDAF_SHIELD_PD_GC13A2        = 3,
};

typedef struct complex{
	float real;
	float imag;
} Complex;

typedef struct {
	HW_U16 *data;
	HW_U32 h;
	HW_U32 w;
} pd_img_t;

typedef struct {
	HW_U16 row_valid[MAX_BLOCK_S];
	HW_FLOAT l_norm[MAX_BLOCK_S];
	HW_FLOAT r_norm[MAX_BLOCK_S];
	HW_FLOAT c_norm[MAX_BLOCK_S];
	Complex fft_data[2 * MAX_FFT_SIZE];
	HW_FLOAT tmp_data[2 * MAX_FFT_SIZE];
} pdaf_stat_entity_t;

typedef struct {
	HW_S32 defocus[PD_MAX_WINS];
	HW_U8 confidence_val[PD_MAX_WINS];
} pdaf_stat_t;

void* af_init(isp_af_core_ops_t **af_core_ops);
void  af_exit(void *af_core_obj);

#endif /*_ISP_3A_AF_LIB_H_*/

