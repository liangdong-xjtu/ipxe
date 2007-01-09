/*
 * Copyright (C) 2006 Michael Brown <mbrown@fensystems.co.uk>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <string.h>
#include <vsprintf.h>
#include <gpxe/netdevice.h>
#include <gpxe/autoboot.h>

/** @file
 *
 * Automatic booting
 *
 */

#include <gpxe/netdevice.h>
void test_dhcp ( struct net_device *netdev );

void autoboot ( void ) {
	struct net_device *netdev;
	int rc;

	netdev = next_netdev ();
	if ( ! netdev ) {
		printf ( "No network device found\n" );
		return;
	}

	if ( ( rc = netdev_open ( netdev ) ) != 0 ) {
		printf ( "Could not open %s: %s\n", netdev->name,
			 strerror ( rc ) );
		return;
	}

	test_dhcp ( netdev );

	netdev_close ( netdev );
}
