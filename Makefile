packet.c packet_marshal.h: packet.h ../packgen/packgen
	../packgen/packgen --little packet.h | clang-format > packet.c
	cproto packet.c > packet_marshal.h
