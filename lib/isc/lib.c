/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, you can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

/*! \file */

#include <isc/bind9.h>
#include <isc/lib.h>
#include <isc/mem.h>
#include <isc/tls.h>
#include <isc/util.h>

#include "config.h"
#include "mem_p.h"
#include "tls_p.h"
#include "trampoline_p.h"

#ifndef ISC_CONSTRUCTOR
#error Either __attribute__((constructor|destructor))__ or DllMain support needed to compile BIND 9.
#endif

/***
 *** Functions
 ***/

void
isc_lib_register(void) {
	isc_bind9 = false;
}

void
isc__initialize(void) ISC_CONSTRUCTOR(101);
void
isc__shutdown(void) ISC_DESTRUCTOR(101);

void
isc__initialize(void) {
	isc__mem_initialize();
	isc__tls_initialize();
	isc__trampoline_initialize();
}

void
isc__shutdown(void) {
	isc__trampoline_shutdown();
	isc__tls_shutdown();
	isc__mem_shutdown();
}
