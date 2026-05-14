
/*
 ******************************************************************************
 *
 * aw_bsdiff.h
 *
 * Hawkview ISP - aw_bsdiff.h module
 *
 * Copyright (c) 2026 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Version		  Author         Date		    Description
 *
 *   1.0		  Ma YiFei   	2026/3/27	   .bsdiff parameter Support
 *
 ******************************************************************************
 */

#ifndef _ISP_BSDIFF_H_
#define _ISP_BSDIFF_H_

#define BSDIFF_MAGIC 0x42534446
#define MATCH_THRESHOLD 64

unsigned int adler32(const unsigned char *data, unsigned int len);
int isp_bsdiff(const unsigned char *old_data, unsigned int old_size,
				const unsigned char *new_data, unsigned int new_size,
				unsigned char **patch);
int isp_bspatch(const unsigned char *old_data, unsigned int old_size,
				const unsigned char *patch_data, unsigned int patch_size,
				unsigned char *new_data, unsigned int new_size);

#endif	/*_ISP_BSDIFF_H_*/

