#include <jansson.h>

#include "packet.h"

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

json_t *marshal_json_bit_statistics32_t(bit_statistics32_t *t) {
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

json_t *marshal_json_bit_statistics16_t(bit_statistics16_t *t) {
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
		ret = marshal_json_bit_statistics32_t(&t->bit_statistics[i]);
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
	ret = marshal_json_bit_statistics16_t(&t->bit_statistics);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "bit_statistics", ret);
	ret = json_integer(t->tsys_usb);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "tsys_usb", ret);
	ret = json_integer(t->tsys_lsb);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "tsys_lsb", ret);
	ret = json_integer(t->sefd_usb);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "sefd_usb", ret);
	ret = json_integer(t->sefd_lsb);
	if (ret == NULL)
		return NULL;
	json_object_set_new(root, "sefd_lsb", ret);
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
