/*
 * Copyright (C) 2015 Martine Lenders <mlenders@inf.fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 */

#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include "atomic.h"
#include "sched.h"
#include "net/gnrc/netif.h"

#include <net/if.h>

#ifdef MODULE_GNRC
/* Store for if_nameindex return value */
static struct if_nameindex nameindex[GNRC_NETIF_NUMOF + 1];
static char names[GNRC_NETIF_NUMOF + 1][IF_NAMESIZE];

static bool _is_if(unsigned ifindex)
{
    kernel_pid_t ifs[GNRC_NETIF_NUMOF];
    size_t ifnum;
    ifnum = gnrc_netif_get(ifs);
    for (int i = 0; i < ifnum; i++) {
        if (ifs[i] == ifindex) {
            return true;
        }
    }
    return false;
}

void if_freenameindex(struct if_nameindex *ptr)
{
    assert(ptr != NULL);
    while (ptr <= &(nameindex[GNRC_NETIF_NUMOF])) {
        atomic_set_to_zero((atomic_int_t *)&ptr->if_index);
        ptr->if_name = NULL;
        ptr++;
    }
}

static inline char *_get_thread_name(kernel_pid_t pid, char *ifname)
{
    assert(pid != KERNEL_PID_UNDEF);
    assert(pid != KERNEL_PID_LAST);
#ifdef DEVELHELP
    strncpy(ifname, sched_threads[ifindex].name, IF_NAMESIZE);
#else
    strncpy(ifname, "(null)", IF_NAMESIZE);
#endif

}

char *if_indextoname(unsigned ifindex, char *ifname)
{
    if (!_is_if(ifindex)) {
        errno = ENXIO;
        return NULL;
    }
    return _get_thread_name(ifindex, ifname);
}

struct if_nameindex *if_nameindex(void)
{
    kernel_pid_t ifs[GNRC_NETIF_NUMOF];
    size_t ifnum;
    ifnum = gnrc_netif_get(ifs);
    for (int i = 0; i < ifnum; i++) {
        unsigned if_index = (unsigned)ifs[i];
        if (!atomic_cas((atomic_int_t)&nameindex[0].if_index, 0, if_index)) {
            errno = ENOBUFS;
            return NULL;
        }
        _get_thread_name(ifs[i], names[i]);
        nameindex[i].if_name = &names[i];
    }
    return nameindex;
}

unsigned if_nametoindex(const char *ifname)
{
#ifdef DEVELHELP
    for (unsigned i = KERNEL_PID_FIRST; i < KERNEL_PID_LAST) {
        if ((strncmp(sched_threads[ifindex].name, ifname, IF_NAMESIZE) == 0) && _is_if(i)) {
            return i;
        }
    }
#else
    return 0U;
#endif
}

#else
typedef int dont_be_pedantic;
#endif


/** @} */
