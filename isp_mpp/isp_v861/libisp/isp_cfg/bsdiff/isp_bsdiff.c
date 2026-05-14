
/*
 ******************************************************************************
 *
 * aw_bsdiff.c
 *
 * Hawkview ISP - aw_bsdiff.c module
 *
 * Copyright (c) 2026 by Allwinnertech Co., Ltd.  http://www.allwinnertech.com
 *
 * Version		  Author         Date		    Description
 *
 *   1.0		  Ma YiFei   	2026/3/27	   .bsdiff parameter Support
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isp_bsdiff.h"
#include "../../isp_math/isp_math_util.h"
#include "../../include/isp_debug.h"

struct suffix {
	const unsigned char *data;
	int idx;
	int len;
};

static int suffix_cmp(const void *a, const void *b)
{
	const struct suffix *sa = (const struct suffix *)a;
	const struct suffix *sb = (const struct suffix *)b;
	int len = min(sa->len - sa->idx, sb->len - sb->idx);
	int cmp = memcmp(sa->data + sa->idx, sb->data + sb->idx, len);
	if (cmp != 0)
		return cmp;
	return (sa->len - sa->idx) - (sb->len - sb->idx);
}

static int find_match(const unsigned char *old_data, int old_len,
					const struct suffix *sa, int sa_len,
					const unsigned char *new_data, int new_pos, int new_len,
					int *match_pos)
{
	int best_len = 0, mid, cmp, len, max_len;
	*match_pos = 0;

	int left = 0, right = sa_len - 1;
	int iter;
	for (iter = 0; iter < 10 && left <= right; iter++) {
		mid = (left + right) / 2;
		cmp = memcmp(old_data + sa[mid].idx, new_data + new_pos,
					min(old_len - sa[mid].idx, new_len - new_pos));

		if (cmp == 0) {
			len = min(old_len - sa[mid].idx, new_len - new_pos);
			if (len > best_len) {
				best_len = len;
				*match_pos = sa[mid].idx;
			}
			right = mid - 1;
		} else if (cmp < 0) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	for (iter = max(0, left - 5); iter < min(sa_len, left + 5); iter++) {
		len = 0;
		max_len = min(old_len - sa[iter].idx, new_len - new_pos);
		while (len < max_len && old_data[sa[iter].idx + len] == new_data[new_pos + len]) {
			len++;
		}
		if (len > best_len) {
			best_len = len;
			*match_pos = sa[iter].idx;
		}
	}

	return best_len;
}

/*
 *adler32 checksum algo
 */
unsigned int adler32(const unsigned char *data, unsigned int len)
{
	unsigned int a = 1, b = 0;
	unsigned int i;

	for (i = 0; i < len; i++) {
		a = (a + data[i]) % 65521;
		b = (b + a) % 65521;
	}

	return (b << 16) | a;
}

/*
 *  Control instruction structure - 12 bytes
 */
struct ctrl_entry {
    unsigned int old_pos;
    unsigned int old_len;
    unsigned int extra_len;
};

/*
 * bsdiff - generate diff
 *
 * input:
 *   old_data - old data
 *   old_size - old size
 *   new_data - new data
 *   new_size - new size
 *   patch    - output patch data（Internal malloc, external need free）
 *
 * return:
 *   >0: patch datasize
 *   -1: error
 */
int isp_bsdiff(const unsigned char *old_data, unsigned int old_size,
			const unsigned char *new_data, unsigned int new_size,
			unsigned char **patch)
{
	int i, j, match_pos, match_len, extra_start, next_match_pos, next_match_len;
	int ctrl_count = 0;
	int extra_len = 0;

    if (old_size == 0 || new_size == 0) return -1;

    struct suffix *sa = (struct suffix *)malloc(old_size * sizeof(struct suffix));
    if (!sa) return -1;

	for (i = 0; i < (int)old_size; i++) {
		sa[i].data = old_data;
		sa[i].idx = i;
		sa[i].len = old_size;
	}

    qsort(sa, old_size, sizeof(struct suffix), suffix_cmp);

	int max_ctrl = (int)new_size + 1;
	struct ctrl_entry *ctrl = (struct ctrl_entry *)malloc(max_ctrl * sizeof(struct ctrl_entry));
	unsigned char *extra = (unsigned char *)malloc(new_size);

	if (!ctrl || !extra) {
		free(sa); free(ctrl); free(extra);
		return -1;
	}

	i = 0;
	while (i < (int)new_size) {
		match_pos = 0;
		match_len = find_match(old_data, old_size, sa, old_size,
							new_data, i, new_size, &match_pos);

		if (match_len < MATCH_THRESHOLD) {
			match_len = 0;
		}

		if (match_len > 0) {
			ctrl[ctrl_count].old_pos = (unsigned int)match_pos;
			ctrl[ctrl_count].old_len = (unsigned int)match_len;
			ctrl[ctrl_count].extra_len = 0;
			ctrl_count++;
			i += match_len;
		} else {
			extra_start = extra_len;
			j = i;

			while (j < (int)new_size) {
				next_match_pos = 0;
				next_match_len = find_match(old_data, old_size, sa, old_size,
												new_data, j, new_size, &next_match_pos);
				if (next_match_len >= MATCH_THRESHOLD) break;

				extra[extra_len++] = new_data[j];
				j++;
			}

			ctrl[ctrl_count].old_pos = 0;
			ctrl[ctrl_count].old_len = 0;
			ctrl[ctrl_count].extra_len = (unsigned int)(extra_len - extra_start);
			ctrl_count++;

			i = j;
		}
	}

	unsigned int header_size = 16;
	unsigned int ctrl_size = ctrl_count * sizeof(struct ctrl_entry);
	unsigned int patch_size = header_size + ctrl_size + extra_len;

	*patch = (unsigned char *)malloc(patch_size);
	if (!*patch) {
		free(sa);
		free(ctrl);
		free(extra);
		return -1;
	}

	unsigned char *p = *patch;
	*(unsigned int *)p = BSDIFF_MAGIC;
	p += 4;
	*(unsigned int *)p = old_size;
	p += 4;
	*(unsigned int *)p = new_size;
	p += 4;
	*(unsigned int *)p = (unsigned int)ctrl_count;
	p += 4;

	memcpy(p, ctrl, ctrl_size);
	p += ctrl_size;
	memcpy(p, extra, extra_len);

	free(sa);
	free(ctrl);
	free(extra);

	return (int)patch_size;
}

/*
 * bspatch - enable patch
 *
 * input:
 *   old_data - old data
 *   old_size - old size
 *   patch_data - patch data
 *   patch_size - patch size
 *   new_data - new data
 *   new_size - new size
 *
 * return：
 *   >0: patch datasize
 *   -1: error
 */
int isp_bspatch(const unsigned char *old_data, unsigned int old_size,
			const unsigned char *patch_data, unsigned int patch_size,
			unsigned char *new_data, unsigned int new_size)
{
    const unsigned char *p = patch_data;
	unsigned int magic;
	unsigned int header_old_size, header_new_size, ctrl_count;
	const struct ctrl_entry *ctrl;
	const unsigned char *extra_data;
	int i, new_pos = 0, extra_pos = 0;
	unsigned int old_pos, old_len, extra_len;

    if (patch_size < 16) {
		ISP_ERR("error, patch_size < 16\n");
		return -1;
	}

	magic = *(unsigned int *)p;
	if (magic != BSDIFF_MAGIC) {
		ISP_ERR("error, magic 0x%.8x != 0x%.8x\n", magic, BSDIFF_MAGIC);
		return -1;
	}
	p += 4;
	header_old_size = *(unsigned int *)p;
	p += 4;
	header_new_size = *(unsigned int *)p;
	p += 4;
	ctrl_count = *(unsigned int *)p;
	p += 4;

	if (old_size != header_old_size) {
		ISP_ERR("old_size = %d, header_old_size = %d, no match.\n", old_size, header_old_size);
		return -1;
	}

	if (new_size != header_new_size) {
		ISP_ERR("new_size = %d, header_new_size = %d, no match.\n", new_size, header_new_size);
		return -1;
	}

	ctrl = (const struct ctrl_entry *)p;
	p += ctrl_count * sizeof(struct ctrl_entry);

	extra_data = p;

	for (i = 0; i < ctrl_count && new_pos < (int)header_new_size; i++) {
		old_pos = ctrl[i].old_pos;
		old_len = ctrl[i].old_len;
		extra_len = ctrl[i].extra_len;

		if (old_len > 0) {
			if (old_pos >= old_size) {
				ISP_ERR("error, old_pos >= old_size\n");
				return -1;
			}
			if (old_pos + old_len > old_size)
				old_len = old_size - old_pos;
			if ((unsigned int)new_pos + old_len > header_new_size)
				old_len = header_new_size - new_pos;

			memcpy(new_data + new_pos, old_data + old_pos, old_len);
			new_pos += old_len;
		}

		if (extra_len > 0) {
			if ((unsigned int)new_pos + extra_len > header_new_size)
				extra_len = header_new_size - new_pos;

			memcpy(new_data + new_pos, extra_data + extra_pos, extra_len);
			new_pos += extra_len;
			extra_pos += extra_len;
		}
	}

    return 0;
}

