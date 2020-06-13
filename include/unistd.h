/*
 * unistd.h
 *
 *  Created on: Feb 21, 2020
 *      Author: wolf
 */

#ifndef INCLUDE_UNISTD_H_
#define INCLUDE_UNISTD_H_

#include <stdint.h>
#include <xen/xen.h>

int clone(uint32_t nr_children, domid_t *child_domids);


typedef int pid_t;

pid_t fork(void);

#endif /* INCLUDE_UNISTD_H_ */
