
/*
 ******************************************************************************
 *
 * isp_ini_parse.h
 *
 * Hawkview ISP - isp_ini_parse.h module
 *
 * Copyright (c) 2015 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Version		  Author         Date		    Description
 *
 *   3.0		  Yang Feng   	2015/11/23	ISP Tuning Tools Support
 *
 ******************************************************************************
 */

#ifndef _ISP_INI_PARSE_H_
#define _ISP_INI_PARSE_H_
#include "isp_manage.h"
#include "isp_debug.h"

#define ISP_CFG_BIN_PATH_LEN 128
#define ISP_CFG_BIN_TIME_LEN 20
#define ISP_CFG_BIN_NOTES_LEN 50

struct isp_cfg_pt
{
	struct isp_test_param          *isp_test_settings;
	struct isp_3a_param            *isp_3a_settings;
	struct isp_tunning_param     *isp_tunning_settings;
	struct isp_dynamic_param           *isp_iso_settings;
};

struct isp_cfg_array
{
	char sensor_name[20];
	char isp_cfg_name[50];
	int width;
	int height;
	int fps;
	int wdr;
	int ir;
	struct isp_cfg_pt *cfg;
};

struct load_isp_param_t {
	char path[ISP_CFG_BIN_PATH_LEN];
	char *isp_param_settings;
	int size;
};
int parser_ini_info(struct isp_param_config *param, char *isp_cfg_name, char *sensor_name,
			int w, int h, int fps, int wdr, int ir, int sync_mode, int isp_id);
int parse_isp_cfg(struct isp_param_config *param, char *isp_cfg_name, char *sensor_name, int isp_id, int ir, char *isp_cfg_path);

#endif	/*_ISP_INI_PARSE_H_*/

