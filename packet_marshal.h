#include <jansson.h>
/* packet.c */
size_t unmarshal_gcomo_t(gcomo_t *t, char *data, size_t n);
size_t unmarshal_downconverter_t(downconverter_t *t, char *data, size_t n);
size_t unmarshal_bit_statistics_t(bit_statistics_t *t, char *data, size_t n);
size_t unmarshal_adb3l_t(adb3l_t *t, char *data, size_t n);
size_t unmarshal_core3h_t(core3h_t *t, char *data, size_t n);
size_t unmarshal_bbc_t(bbc_t *t, char *data, size_t n);
size_t unmarshal_dbbc3_ddc_multicast_t(dbbc3_ddc_multicast_t *t, char *data, size_t n);
json_t *marshal_json_gcomo_t(gcomo_t *t);
json_t *marshal_json_downconverter_t(downconverter_t *t);
json_t *marshal_json_bit_statistics_t(bit_statistics_t *t);
json_t *marshal_json_adb3l_t(adb3l_t *t);
json_t *marshal_json_core3h_t(core3h_t *t);
json_t *marshal_json_bbc_t(bbc_t *t);
json_t *marshal_json_dbbc3_ddc_multicast_t(dbbc3_ddc_multicast_t *t);
