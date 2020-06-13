/*
 * Cloning support for Mini-OS.
 * Costin Lupu <costin.lupu@cs.pub.ro>, 2020
 */

#include <mini-os/types.h>
#include <mini-os/unistd.h>
#include <mini-os/os.h>
#include <mini-os/console.h>
#include <xen/clone.h>

extern start_info_t *start_info_ptr;

int clone(uint32_t nr_children, domid_t *child_domids)
{
    struct clone_op op;
    unsigned long flags;
    int rc;

    op.start_info_mfn = virt_to_mfn(start_info_ptr);
    op.nr_children = nr_children;
    set_xen_guest_handle(op.child_list, child_domids);

    local_irq_save(flags);
    rc = HYPERVISOR_clone(CLONEOP_clone, &op);
    local_irq_restore(flags);

    return rc;
}

pid_t fork(void)
{
    domid_t child_domid;
    int rc;

    rc = clone(1, &child_domid);
    if (rc == 0) /* parent */
        rc = child_domid;
    else if (rc == 1) /* child */
        rc = 0;
    else {
    	printk("Error calling clone() rc=%d\n", rc);
        rc = -1;
    }

    return rc;
}
