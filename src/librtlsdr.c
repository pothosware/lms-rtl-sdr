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
#include <lime/LimeSuite.h>

struct rtlsdr_dev {
	lms_device_t *lms;
	char manufact[256];
	char product[256];
	char serial[256];
	int channel;
	double rate;
	lms_stream_t stream;
	bool stream_active;
};

#define trace(format, ...) fprintf(stderr, "\e[36m\e[1m" format "\e[39m\n", ## __VA_ARGS__)
#define error(format, ...) fprintf(stderr, "\e[31m\e[1m" format "\e[39m\n", ## __VA_ARGS__)

int rtlsdr_set_xtal_freq(rtlsdr_dev_t *dev, uint32_t rtl_freq, uint32_t tuner_freq)
{
	return 0;
}

int rtlsdr_get_xtal_freq(rtlsdr_dev_t *dev, uint32_t *rtl_freq, uint32_t *tuner_freq)
{
	return 0;
}

int rtlsdr_get_usb_strings(rtlsdr_dev_t *dev, char *manufact, char *product,
			    char *serial)
{
	if (manufact != NULL) strcpy(manufact, dev->manufact);
	if (product != NULL) strcpy(product, dev->product);
	if (serial != NULL) strcpy(serial, dev->serial);
	return 0;
}

int rtlsdr_write_eeprom(rtlsdr_dev_t *dev, uint8_t *data, uint8_t offset, uint16_t len)
{
	return -1;
}

int rtlsdr_read_eeprom(rtlsdr_dev_t *dev, uint8_t *data, uint8_t offset, uint16_t len)
{
	return -1;
}

int rtlsdr_set_center_freq(rtlsdr_dev_t *dev, uint32_t freq)
{
	trace("LMS_SetLOFrequency(%g MHz)", (double)(freq)/1e6);
	return LMS_SetLOFrequency(dev->lms, LMS_CH_RX, dev->channel, (double)(freq));
}

uint32_t rtlsdr_get_center_freq(rtlsdr_dev_t *dev)
{
	double freq;
	int r = LMS_GetLOFrequency(dev->lms, LMS_CH_RX, dev->channel, &freq);
	if (r == LMS_SUCCESS) return (uint32_t)(freq);
	return -0.0;
}

int rtlsdr_set_freq_correction(rtlsdr_dev_t *dev, int ppm)
{
	return -1;
}

int rtlsdr_get_freq_correction(rtlsdr_dev_t *dev)
{
	return 0;
}

enum rtlsdr_tuner rtlsdr_get_tuner_type(rtlsdr_dev_t *dev)
{
	return RTLSDR_TUNER_UNKNOWN;
}

int rtlsdr_get_tuner_gains(rtlsdr_dev_t *dev, int *gains)
{
	size_t i = 0, num_gains = 71;
	if (gains != NULL)
	{
		for (i = 0; i < num_gains; i++) gains[i] = i*10; //10ths
	}
	return num_gains;
}

int rtlsdr_set_tuner_bandwidth(rtlsdr_dev_t *dev, uint32_t bw)
{
	trace("LMS_SetLPFBW(%g MHz)", (double)(bw)/1e6);
	return LMS_SetLPFBW(dev->lms, LMS_CH_RX, dev->channel, (double)(bw));
}

int rtlsdr_set_tuner_gain(rtlsdr_dev_t *dev, int gain)
{
	//gain is in 10ths of a dB
	trace("LMS_SetGaindB(%g dB)", (double)(gain)/10);
	return LMS_SetGaindB(dev->lms, LMS_CH_RX, dev->channel, (double)(gain)/10);
}

int rtlsdr_get_tuner_gain(rtlsdr_dev_t *dev)
{
	unsigned gain;
	int r = LMS_GetGaindB(dev->lms, LMS_CH_RX, dev->channel, &gain);
	if (r == LMS_SUCCESS) return gain*10; //10ths of a dB
	return 0;
}

int rtlsdr_set_tuner_if_gain(rtlsdr_dev_t *dev, int stage, int gain)
{
	return 0;
}

int rtlsdr_set_tuner_gain_mode(rtlsdr_dev_t *dev, int mode)
{
	//always manual
	return 0;
}

int rtlsdr_set_sample_rate(rtlsdr_dev_t *dev, uint32_t samp_rate)
{
	int ovs = 32;
	while (samp_rate*ovs > 640e6) ovs /= 2;
	if (ovs < 1) return -1;
	trace("LMS_SetSampleRate(%g MHz)", (double)(samp_rate)/1e6);
	return LMS_SetSampleRate(dev->lms, (double)(samp_rate), ovs);
}

uint32_t rtlsdr_get_sample_rate(rtlsdr_dev_t *dev)
{
	double host_Hz, rf_Hz;
	int r = LMS_GetSampleRate(dev->lms, LMS_CH_RX, dev->channel, &host_Hz, &rf_Hz);
	if (r == LMS_SUCCESS) return (uint32_t)(host_Hz);
	return -0.0;
}

int rtlsdr_set_testmode(rtlsdr_dev_t *dev, int on)
{
	return 0;
}

int rtlsdr_set_agc_mode(rtlsdr_dev_t *dev, int on)
{
	return 0;
}

int rtlsdr_set_direct_sampling(rtlsdr_dev_t *dev, int on)
{
	return 0;
}

int rtlsdr_get_direct_sampling(rtlsdr_dev_t *dev)
{
	return 0;
}

int rtlsdr_set_offset_tuning(rtlsdr_dev_t *dev, int on)
{
	return 0;
}

int rtlsdr_get_offset_tuning(rtlsdr_dev_t *dev)
{
	return 0;
}

uint32_t rtlsdr_get_device_count(void)
{
	return LMS_GetDeviceList(NULL);
}

static void read_info_field(const char *dev_info, const char *key, char *output)
{
	char *comma;
	size_t len;
	char *start = (char *)dev_info;
	if (key != NULL) start = strstr(dev_info, key);
	if (start == NULL)
	{
		printf("start == NULL!");
		output[0] = '\0';
		return;
	}
	if (start != NULL && key != NULL) start += strlen(key);

	comma = strstr(start, ",");
	len = (comma == NULL)?((int)strlen(dev_info)-(dev_info-start)):comma-start;
	memcpy(output, start, len);
	output[len] = '\0';
}

const char *rtlsdr_get_device_name(uint32_t index)
{
	static __thread char name[256];
	lms_info_str_t dev_list[256];
	int r = LMS_GetDeviceList(dev_list);
	if (r < (int)index) return "";
	read_info_field(&dev_list[index][0], NULL, name);
	return name;
}

int rtlsdr_get_device_usb_strings(uint32_t index, char *manufact,
				   char *product, char *serial)
{
	lms_info_str_t dev_list[256];
	int r = LMS_GetDeviceList(dev_list);
	if (r < (int)index) return -1;
	if (manufact != NULL) strcpy(manufact, "LimeSuite");
	if (product != NULL) read_info_field(&dev_list[index][0], NULL, product);
	if (serial != NULL) read_info_field(&dev_list[index][0], "serial=", serial);
	return 0;
}

int rtlsdr_get_index_by_serial(const char *serial)
{
	lms_info_str_t dev_list[256];
	int i = 0;
	int r = LMS_GetDeviceList(dev_list);
	if (serial == NULL) return -1;
	if (r == 0) return -2;
	for (i = 0; i < r; i++)
	{
		char serial_i[256];
		read_info_field(&dev_list[i][0], "serial=", serial_i);
		if (strcmp(serial, serial_i) == 0) return i;
	}
	return -3;
}

int rtlsdr_open(rtlsdr_dev_t **out_dev, uint32_t index)
{
	lms_info_str_t dev_list[256];
	int r = LMS_GetDeviceList(dev_list);
	if (r < (int)index) return -1;
	*out_dev = (rtlsdr_dev_t *)calloc(1, sizeof(rtlsdr_dev_t));
	r = LMS_Open(&((*out_dev)->lms), dev_list[index], NULL);
	if (r != LMS_SUCCESS)
	{
		free(*out_dev);
		return -1;
	}

	strcpy((*out_dev)->manufact, "LimeSuite");
	read_info_field(&dev_list[index][0], NULL, (*out_dev)->product);
	read_info_field(&dev_list[index][0], "serial=", (*out_dev)->serial);
	(*out_dev)->channel = 0; //default is channel 0 (A)
	(*out_dev)->rate = 8e6; //some default will do
	(*out_dev)->stream_active = false;

	r = LMS_Init((*out_dev)->lms);
	if (r != LMS_SUCCESS) error("LMS_Init() failed");

	r = LMS_EnableChannel((*out_dev)->lms, LMS_CH_RX, (*out_dev)->channel, true);
	if (r != LMS_SUCCESS) error("LMS_EnableChannel() failed");

	LMS_EnableCalibCache((*out_dev)->lms, true);

	r = LMS_SetAntenna((*out_dev)->lms, LMS_CH_RX, (*out_dev)->channel, LMS_PATH_LNAL);
	if (r != LMS_SUCCESS) error("LMS_SetAntenna() failed");
	return 0;
}

int rtlsdr_close(rtlsdr_dev_t *dev)
{
	if (!dev) return -1;
	LMS_EnableChannel(dev->lms, LMS_CH_RX, dev->channel, false);
	LMS_Close(dev->lms);
	free(dev);
	return 0;
}

static int start_stream(rtlsdr_dev_t *dev)
{
	int r;
	if (!dev) return -1;
	if (dev->stream_active) return 0;
	r = LMS_Calibrate(dev->lms, LMS_CH_RX, dev->channel, dev->rate, 0);
	if (r != LMS_SUCCESS) error("LMS_Calibrate() failed");

	dev->stream.handle = 0;
	dev->stream.isTx = LMS_CH_RX;
	dev->stream.channel = dev->channel;
	dev->stream.fifoSize = 0;
	dev->stream.throughputVsLatency = 1.0;
	dev->stream.dataFmt = LMS_FMT_I16;

	r = LMS_SetupStream(dev->lms, &dev->stream);
	if (r != LMS_SUCCESS) error("LMS_SetupStream() failed");

	r = LMS_StartStream(&dev->stream);
	if (r != LMS_SUCCESS) error("LMS_StartStream() failed");
	dev->stream_active = true;
	return 0;
}

int rtlsdr_reset_buffer(rtlsdr_dev_t *dev)
{
	return 0;
}

int rtlsdr_read_sync(rtlsdr_dev_t *dev, void *buf, int len, int *n_read)
{
	int r, i;
	uint8_t *out = (uint8_t *)buf;
	int16_t samples[len*2];

	if (!dev) return -1;
	if (!dev->stream_active) start_stream(dev); //ensure start if not

	while (true)
	{
		r = LMS_RecvStream(&dev->stream, samples, len, NULL, 1);
		if (!dev->stream_active) return -1; //done
		if (r == 0) continue; //continue on timeout
		if (r < 0) return -1; //error condition
		break;
	}

	*n_read = r*2;
	for (i = 0; i < *n_read; i++)
	{
		out[i] = (uint8_t)(samples[i] >> 8);
		out[i] += 127;
	}
	return 0;
}

int rtlsdr_wait_async(rtlsdr_dev_t *dev, rtlsdr_read_async_cb_t cb, void *ctx)
{
	//deprecated anyway...
	return -1;
}

#define DEFAULT_BUF_LENGTH	(16 * 32 * 512)

int rtlsdr_read_async(rtlsdr_dev_t *dev, rtlsdr_read_async_cb_t cb, void *ctx,
			  uint32_t buf_num, uint32_t buf_len)
{
	uint32_t i, len = 0;
	int r;
	uint32_t full_len = buf_len?buf_len:DEFAULT_BUF_LENGTH;
	uint8_t out[full_len];
	int16_t samples[full_len];

	if (!dev) return -1;
	if (!dev->stream_active) start_stream(dev); //ensure start if not

	while (dev->stream_active)
	{
		r = LMS_RecvStream(&dev->stream, samples + len, (full_len - len)/2, NULL, 1);
		if (r == 0) continue; //continue on timeout
		if (r < 0) return -1; //error condition

		len += r*2;
		if (len < full_len) continue; //need more

		//otherwise output it
		for (i = 0; i < len; i++)
		{
			out[i] = (uint8_t)(samples[i] >> 8);
			out[i] += 127;
		}
		cb((unsigned char *)out, len, ctx);

		len = 0; //reset for new loop of reads
	}
	return 0;
}

int rtlsdr_cancel_async(rtlsdr_dev_t *dev)
{
	if (!dev) return -1;
	LMS_StopStream(&dev->stream);
	LMS_DestroyStream(dev->lms, &dev->stream);
	dev->stream_active = false;
	return 0;
}

int rtlsdr_set_bias_tee(rtlsdr_dev_t *dev, int on)
{
	return 0;
}
