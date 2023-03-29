#ifndef LOOPBACK_H
#define LOOPBACK_H

#include "net.h"

#define LOOPBACK_MTU UINT16_MAX /* maximum size of IP datagram */

extern struct net_device* loopback_init(void);

#endif
