/*
 * Copyright (C) 2015 Martine Lenders <mlenders@inf.fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    posix_netif local interfaces
 * @ingroup     posix
 * @brief       sockets local intefaces
 * @{
 *
 * @file
 * @brief   sockets local interfaces
 *
 * @see     <a href="http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/net_if.h.html">
 *              The Open Group Base Specifications Issue 7, <net/if.h>
 *          </a>
 *
 * @author  Martine Lenders <mlenders@inf.fu-berlin.de>
 */
#ifndef NET_IF_H_
#define NET_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Maximum length of an interface name (including terminating NULL character).
 */
#define IF_NAMESIZE (8)

/**
 * @brief   Interface index structure
 */
struct if_nameindex {
    unsigned if_index;  /**< Numeric index of the interface */
    char *if_name;      /**< Null-terminated name of the interface */
}

/**
 * @brief   free memory allocated by if_nameindex()
 *
 * The if_freenameindex() function sall free the memory allocated by if_nameindex(). The @p ptr
 * argument shall be a pointer that was returned by if_nameindex(). After if_freenameindex() has
 * been called, the application shall not use the array of which @p ptr is the address.
 *
 * @see     <a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/if_freenameindex.html">
 *              The Open Group Base Specifications Issue 7, if_freenameindex()
 *          </a>
 *
 * @param[in] ptr   An array of struct if_nameindex, returned by if_nameindex().
 */
void if_freenameindex(struct if_nameindex *ptr);

/**
 * @brief   map a network interface index to its corresponding name
 *
 * The if_indextoname() function shall map an interface index to its corresponding name.
 *
 * When this function is called, @p ifname shall point to a buffer of at least {IF_NAMESIZE} bytes.
 * The function shall place in this buffer the name of the interface with index @p ifindex
 *
 * @see     <a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/if_indextoname.html">
 *              The Open Group Base Specifications Issue 7, if_indextoname()
 *          </a>
 *
 * @param[in] ifindex   Index number of an interface.
 * @param[out] ifname   The name of the interface.
 *
 * @return  If @p ifindex is an interface index, then the function shall return the value
 *          supplied in @p ifname, which points to a buffer now containing the interface name.
 * @return  Otherwise, the function shall return a null pointer and set errno to ENXIO.
 */
char *if_indextoname(unsigned ifindex, char *ifname);

/**
 * @brief   return all network interface names and indexes
 *
 * The if_nameindex() function shall return an array of if_nameindex structures, one structure per
 * interface. The end of the array is indicated by a structure with an if_index field of zero and
 * an if_name field of NULL. Applications should call if_freenameindex() to release the memory that
 * may be dynamically allocated by this function, after they have finished using it.
 *
 * @see     <a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/if_nameindex.html">
 *              The Open Group Base Specifications Issue 7, if_nameindex()
 *          </a>
 *
 * @return  An array of structures identifying local interfaces.
 * @return  A null pointer is returned upon an error, with errno set to ENOBUFS.
 */
struct if_nameindex *if_nameindex(void);

/**
 * @brief   map a network interface name to its corresponding index
 *
 * The if_nametoindex() function shall return the interface index corresponding to name @p ifname.
 *
 * @see     <a href="http://pubs.opengroup.org/onlinepubs/9699919799/functions/if_nametoindex.html">
 *              The Open Group Base Specifications Issue 7, if_nametoindex()
 *          </a>
 *
 * @param[in] ifname    An interface name.
 *
 * @return  The corresponding index if @p ifname is the name of an interface;
 * @return  otherwise, zero.
 */
unsigned if_nametoindex(const char *ifname);

#ifdef __cplusplus
}
#endif

#endif /* NET_IF_H_ */
/** @} */
