
LDLIBS += -lnng -ljansson 
main: main.c packet_unpack.c packet_json.c

packet_unpack.c packet_unpack.h packet_json.c packet_json.h: packet.h ../packgen/packgen
	../packgen/packgen --little packet.h
	clang-format -i packet_*
