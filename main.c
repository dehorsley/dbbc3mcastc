#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "packet.h"
#include "packet_marshal.h"

const char mcast_addr[] = "224.0.0.255";
const short mcast_port  = 25000;

const int MAX_UDP = 65535;

int main() {

	struct sockaddr_in addr = {};
	addr.sin_family         = AF_INET;
	addr.sin_addr.s_addr    = htonl(INADDR_ANY);
	addr.sin_port           = htons(mcast_port);

	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("Opening datagram socket error");
		exit(1);
	}

	int yes = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
		perror("Setting SO_REUSEADDR error");
		close(sock);
		exit(1);
	}

	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr))) {
		perror("Binding datagram socket error");
		close(sock);
		exit(1);
	}

	struct ip_mreq mreq       = {};
	mreq.imr_multiaddr.s_addr = inet_addr(mcast_addr);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		perror("Adding multicast group error");
		close(sock);
		exit(1);
	}

	ssize_t n;
	unsigned char buf[MAX_UDP];
	json_t *s;
	struct sockaddr_in from;
	socklen_t len = sizeof(from);

	dbbc3_ddc_multicast_t packet = {};
	for (;;) {
		if ((n = recvfrom(sock, buf, sizeof(dbbc3_ddc_multicast_t), 0,
		                  (struct sockaddr *)&from, &len)) < 0) {
			perror("recv");
			exit(1);
		}
		if (unmarshal_dbbc3_ddc_multicast_t(&packet, buf, n) < 0) {
			fprintf(stderr, "error unmarshaling packet");
			continue;
		}
		s = marshal_json_dbbc3_ddc_multicast_t(&packet);
		if (s == NULL)
			continue;
		json_dumpf(s, stdout, JSON_INDENT(1));
		json_decref(s);
	}
}
