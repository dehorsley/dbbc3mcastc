#include <stdint.h>
#include <sys/types.h>

#include <jansson.h>

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

ssize_t unmarshal_gcomo_t(gcomo_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_gcomo_t)
		return -1;
	t->agc = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	t->attenuation = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	t->total_power = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	t->total_power_target = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	return (p - data);
}

ssize_t unmarshal_downconverter_t(downconverter_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_downconverter_t)
		return -1;
	t->output_enabled = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	t->lock = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	t->attenuation = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	t->frequency = (p[0] << 0) | (p[1] << 8);
	p += 2;
	n -= 2;
	return (p - data);
}

ssize_t unmarshal_bit_statistics_t(bit_statistics_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_bit_statistics_t)
		return -1;
	for (int i = 0; i < 4; i++) {
		t->pattern[i] = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
		p += 4;
		n -= 4;
	}
	return (p - data);
}

ssize_t unmarshal_adb3l_t(adb3l_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_adb3l_t)
		return -1;
	for (int i = 0; i < 4; i++) {
		t->total_power[i] = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
		p += 4;
		n -= 4;
	}
	for (int i = 0; i < 4; i++) {
		ret = unmarshal_bit_statistics_t(&t->bit_statistics[i], p, n);
		p += ret;
		n -= ret;
	}
	for (int i = 0; i < 3; i++) {
		t->delay_correlation[i] = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
		p += 4;
		n -= 4;
	}
	return (p - data);
}

ssize_t unmarshal_core3h_t(core3h_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_core3h_t)
		return -1;
	t->timestamp = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->pps_delay = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->total_power_cal_on = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->total_power_cal_off = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->tsys = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->sefd = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	return (p - data);
}

ssize_t unmarshal_bbc_t(bbc_t *t, uint8_t *data, size_t n) {
	ssize_t ret;
	uint8_t *p = data;
	if (n < len_bbc_t)
		return -1;
	t->frequency = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->bandwidth = *p++;
	n--;
	t->agc = *p++;
	n--;
	t->gain_usb = *p++;
	n--;
	t->gain_lsb = *p++;
	n--;
	t->total_power_usb_cal_on = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->total_power_lsb_cal_on = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->total_power_usb_cal_off = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	t->total_power_lsb_cal_off = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
	p += 4;
	n -= 4;
	ret = unmarshal_bit_statistics_t(&t->bit_statistics, p, n);
	p += ret;
	n -= ret;
	return (p - data);
}

ssize_t unmarshal_dbbc3_ddc_multicast_t(dbbc3_ddc_multicast_t *t, uint8_t *data, size_t n) {
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

json_t *marshal_json_gcomo_t(gcomo_t *t) {
	json_t *root = json_object();
	json_t *a;
	json_t *ret;
	if (root == NULL)
		return NULL;
	ret = json_integer(t->agc);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "agc", ret);
	ret = json_integer(t->attenuation);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "attenuation", ret);
	ret = json_integer(t->total_power);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power", ret);
	ret = json_integer(t->total_power_target);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power_target", ret);
	return root;
}

json_t *marshal_json_downconverter_t(downconverter_t *t) {
	json_t *root = json_object();
	json_t *a;
	json_t *ret;
	if (root == NULL)
		return NULL;
	ret = json_integer(t->output_enabled);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "output_enabled", ret);
	ret = json_integer(t->lock);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "lock", ret);
	ret = json_integer(t->attenuation);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "attenuation", ret);
	ret = json_integer(t->frequency);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "frequency", ret);
	return root;
}

json_t *marshal_json_bit_statistics_t(bit_statistics_t *t) {
	json_t *root = json_object();
	json_t *a;
	json_t *ret;
	if (root == NULL)
		return NULL;

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 4; i++) {
		ret = json_integer(t->pattern[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "pattern", a);

	return root;
}

json_t *marshal_json_adb3l_t(adb3l_t *t) {
	json_t *root = json_object();
	json_t *a;
	json_t *ret;
	if (root == NULL)
		return NULL;

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 4; i++) {
		ret = json_integer(t->total_power[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "total_power", a);

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 4; i++) {
		ret = marshal_json_bit_statistics_t(&t->bit_statistics[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "bit_statistics", a);

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 3; i++) {
		ret = json_integer(t->delay_correlation[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "delay_correlation", a);

	return root;
}

json_t *marshal_json_core3h_t(core3h_t *t) {
	json_t *root = json_object();
	json_t *a;
	json_t *ret;
	if (root == NULL)
		return NULL;
	ret = json_integer(t->timestamp);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "timestamp", ret);
	ret = json_integer(t->pps_delay);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "pps_delay", ret);
	ret = json_integer(t->total_power_cal_on);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power_cal_on", ret);
	ret = json_integer(t->total_power_cal_off);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power_cal_off", ret);
	ret = json_integer(t->tsys);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "tsys", ret);
	ret = json_integer(t->sefd);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "sefd", ret);
	return root;
}

json_t *marshal_json_bbc_t(bbc_t *t) {
	json_t *root = json_object();
	json_t *a;
	json_t *ret;
	if (root == NULL)
		return NULL;
	ret = json_integer(t->frequency);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "frequency", ret);
	ret = json_integer(t->bandwidth);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "bandwidth", ret);
	ret = json_integer(t->agc);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "agc", ret);
	ret = json_integer(t->gain_usb);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "gain_usb", ret);
	ret = json_integer(t->gain_lsb);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "gain_lsb", ret);
	ret = json_integer(t->total_power_usb_cal_on);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power_usb_cal_on", ret);
	ret = json_integer(t->total_power_lsb_cal_on);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power_lsb_cal_on", ret);
	ret = json_integer(t->total_power_usb_cal_off);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power_usb_cal_off", ret);
	ret = json_integer(t->total_power_lsb_cal_off);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "total_power_lsb_cal_off", ret);
	ret = marshal_json_bit_statistics_t(&t->bit_statistics);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "bit_statistics", ret);
	return root;
}

json_t *marshal_json_dbbc3_ddc_multicast_t(dbbc3_ddc_multicast_t *t) {
	json_t *root = json_object();
	json_t *a;
	json_t *ret;
	if (root == NULL)
		return NULL;
	ret = json_stringn(t->version, 32);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "version", ret);

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 8; i++) {
		ret = marshal_json_gcomo_t(&t->gcomo[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "gcomo", a);

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 8; i++) {
		ret = marshal_json_downconverter_t(&t->downconverter[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "downconverter", a);

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 8; i++) {
		ret = marshal_json_adb3l_t(&t->adb3l[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "adb3l", a);

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 8; i++) {
		ret = marshal_json_core3h_t(&t->core3h[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "core3h", a);

	a = json_array();
	if (a == NULL)
		return NULL;
	for (int i = 0; i < 128; i++) {
		ret = marshal_json_bbc_t(&t->bbc[i]);
		if (ret == NULL)
			return NULL;
		json_array_append_new(a, ret);
	}
	json_object_set_new(root, "bbc", a);

	return root;
}
