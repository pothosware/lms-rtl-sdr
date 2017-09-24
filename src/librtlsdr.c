/*
 * rtl-sdr, turns your Realtek RTL2832 based DVB dongle into a SDR receiver
 * Copyright (C) 2012-2014 by Steve Markgraf <steve@steve-m.de>
 * Copyright (C) 2012 by Dimitri Stolnikov <horiz0n@gmx.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rtl-sdr.h"

struct rtlsdr_dev {
	
};

int rtlsdr_set_xtal_freq(rtlsdr_dev_t *dev, uint32_t rtl_freq, uint32_t tuner_freq)
{
}

int rtlsdr_get_xtal_freq(rtlsdr_dev_t *dev, uint32_t *rtl_freq, uint32_t *tuner_freq)
{
}

int rtlsdr_get_usb_strings(rtlsdr_dev_t *dev, char *manufact, char *product,
			    char *serial)
{
}

int rtlsdr_write_eeprom(rtlsdr_dev_t *dev, uint8_t *data, uint8_t offset, uint16_t len)
{
}

int rtlsdr_read_eeprom(rtlsdr_dev_t *dev, uint8_t *data, uint8_t offset, uint16_t len)
{
}

int rtlsdr_set_center_freq(rtlsdr_dev_t *dev, uint32_t freq)
{
}

uint32_t rtlsdr_get_center_freq(rtlsdr_dev_t *dev)
{
}

int rtlsdr_set_freq_correction(rtlsdr_dev_t *dev, int ppm)
{
}

int rtlsdr_get_freq_correction(rtlsdr_dev_t *dev)
{
}

enum rtlsdr_tuner rtlsdr_get_tuner_type(rtlsdr_dev_t *dev)
{
}

int rtlsdr_get_tuner_gains(rtlsdr_dev_t *dev, int *gains)
{
}

int rtlsdr_set_tuner_bandwidth(rtlsdr_dev_t *dev, uint32_t bw)
{
}

int rtlsdr_set_tuner_gain(rtlsdr_dev_t *dev, int gain)
{
}

int rtlsdr_get_tuner_gain(rtlsdr_dev_t *dev)
{
}

int rtlsdr_set_tuner_if_gain(rtlsdr_dev_t *dev, int stage, int gain)
{
}

int rtlsdr_set_tuner_gain_mode(rtlsdr_dev_t *dev, int mode)
{
}

int rtlsdr_set_sample_rate(rtlsdr_dev_t *dev, uint32_t samp_rate)
{
}

uint32_t rtlsdr_get_sample_rate(rtlsdr_dev_t *dev)
{
}

int rtlsdr_set_testmode(rtlsdr_dev_t *dev, int on)
{
}

int rtlsdr_set_agc_mode(rtlsdr_dev_t *dev, int on)
{
}

int rtlsdr_set_direct_sampling(rtlsdr_dev_t *dev, int on)
{
}

int rtlsdr_get_direct_sampling(rtlsdr_dev_t *dev)
{
}

int rtlsdr_set_offset_tuning(rtlsdr_dev_t *dev, int on)
{
}

int rtlsdr_get_offset_tuning(rtlsdr_dev_t *dev)
{
}

uint32_t rtlsdr_get_device_count(void)
{
}

const char *rtlsdr_get_device_name(uint32_t index)
{
}

int rtlsdr_get_device_usb_strings(uint32_t index, char *manufact,
				   char *product, char *serial)
{
}

int rtlsdr_get_index_by_serial(const char *serial)
{
}

int rtlsdr_open(rtlsdr_dev_t **out_dev, uint32_t index)
{
}

int rtlsdr_close(rtlsdr_dev_t *dev)
{
}

int rtlsdr_reset_buffer(rtlsdr_dev_t *dev)
{
}

int rtlsdr_read_sync(rtlsdr_dev_t *dev, void *buf, int len, int *n_read)
{
}

int rtlsdr_wait_async(rtlsdr_dev_t *dev, rtlsdr_read_async_cb_t cb, void *ctx)
{
}

int rtlsdr_read_async(rtlsdr_dev_t *dev, rtlsdr_read_async_cb_t cb, void *ctx,
			  uint32_t buf_num, uint32_t buf_len)
{
}

int rtlsdr_cancel_async(rtlsdr_dev_t *dev)
{
}

int rtlsdr_set_bias_tee(rtlsdr_dev_t *dev, int on)
{
	
}
