#include <stdint.h>
#include <sys/types.h>

#include "packet.h"

const size_t len_gcomo_t = 0 + 2 + 2 + 2 + 2;

const size_t len_downconverter_t = 0 + 2 + 2 + 2 + 2;

const size_t len_bit_statistics_t = 0 + 4 * (0 + 4);

const size_t len_adb3l_t = 0 + 4 * (0 + 4) + 4 * (0 + len_bit_statistics_t) + 3 * (0 + 4);

const size_t len_core3h_t = 0 + 4 + 4 + 4 + 4 + 4 + 4;

const size_t len_bbc_t = 0 + 4 + 1 + 1 + 1 + 1 + 4 + 4 + 4 + 4 + len_bit_statistics_t;

const size_t len_dbbc3_ddc_multicast_t = 0 + 32 * (0 + 1) + 8 * (0 + len_gcomo_t) +
                                         8 * (0 + len_downconverter_t) + 8 * (0 + len_adb3l_t) +
                                         8 * (0 + len_core3h_t) + 128 * (0 + len_bbc_t);

size_t unmarshal_gcomo_t(gcomo_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_gcomo_t)
		return -1;
	t->agc = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	t->attenuation = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	t->total_power = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	t->total_power_target = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	return (p - data);
}

size_t unmarshal_downconverter_t(downconverter_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_downconverter_t)
		return -1;
	t->output_enabled = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	t->lock = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	t->attenuation = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	t->frequency = (data[0] << 0) | (data[1] << 8);
	data += 2;
	n -= 2;
	return (p - data);
}

size_t unmarshal_bit_statistics_t(bit_statistics_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_bit_statistics_t)
		return -1;
	for (int i = 0; i < 4; i++) {
		t->pattern[i] = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
		data += 4;
		n -= 4;
	}
	return (p - data);
}

size_t unmarshal_adb3l_t(adb3l_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_adb3l_t)
		return -1;
	for (int i = 0; i < 4; i++) {
		t->total_power[i] =
		    (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
		data += 4;
		n -= 4;
	}
	for (int i = 0; i < 4; i++) {
		ret = unmarshal_bit_statistics_t(&t->bit_statistics[i], p, n);
		p += ret;
		n -= ret;
	}
	for (int i = 0; i < 3; i++) {
		t->delay_correlation[i] =
		    (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
		data += 4;
		n -= 4;
	}
	return (p - data);
}

size_t unmarshal_core3h_t(core3h_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_core3h_t)
		return -1;
	t->timestamp = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->pps_delay = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->total_power_cal_on = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->total_power_cal_off =
	    (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->tsys = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->sefd = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	return (p - data);
}

size_t unmarshal_bbc_t(bbc_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_bbc_t)
		return -1;
	t->frequency = (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->bandwidth = *p++;
	n--;
	t->agc = *p++;
	n--;
	t->gain_usb = *p++;
	n--;
	t->gain_lsb = *p++;
	n--;
	t->total_power_usb_cal_on =
	    (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->total_power_lsb_cal_on =
	    (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->total_power_usb_cal_off =
	    (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	t->total_power_lsb_cal_off =
	    (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
	data += 4;
	n -= 4;
	ret = unmarshal_bit_statistics_t(&t->bit_statistics, p, n);
	p += ret;
	n -= ret;
	return (p - data);
}

size_t unmarshal_dbbc3_ddc_multicast_t(dbbc3_ddc_multicast_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_dbbc3_ddc_multicast_t)
		return -1;
	for (int i = 0; i < 32; i++) {
		t->version[i] = *p++;
		n--;
	}
	for (int i = 0; i < 8; i++) {
		ret = unmarshal_gcomo_t(&t->gcomo[i], p, n);
		p += ret;
		n -= ret;
	}
	for (int i = 0; i < 8; i++) {
		ret = unmarshal_downconverter_t(&t->downconverter[i], p, n);
		p += ret;
		n -= ret;
	}
	for (int i = 0; i < 8; i++) {
		ret = unmarshal_adb3l_t(&t->adb3l[i], p, n);
		p += ret;
		n -= ret;
	}
	for (int i = 0; i < 8; i++) {
		ret = unmarshal_core3h_t(&t->core3h[i], p, n);
		p += ret;
		n -= ret;
	}
	for (int i = 0; i < 128; i++) {
		ret = unmarshal_bbc_t(&t->bbc[i], p, n);
		p += ret;
		n -= ret;
	}
	return (p - data);
}
