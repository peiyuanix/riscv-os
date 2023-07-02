.equ REGSZ, 8
.global trap_entry

.text

trap_entry:

# swap x5/mscratch
csrrw x5, mscratch, x5
# use x5 as cpu state base address register
la x5, trap_cpu
# save general purpose registers
# x0 ~ x4
sd x0, (0 * REGSZ)(x5)
sd x1, (1 * REGSZ)(x5)
sd x2, (2 * REGSZ)(x5)
sd x3, (3 * REGSZ)(x5)
sd x4, (4 * REGSZ)(x5)
# save origin x5 by x1, which has been saved
csrr x1, mscratch
sd x1, (5 * REGSZ)(x5)
# x6 ~ x31
sd x6, (6 * REGSZ)(x5)
sd x7, (7 * REGSZ)(x5)
sd x8, (8 * REGSZ)(x5)
sd x9, (9 * REGSZ)(x5)
sd x10, (10 * REGSZ)(x5)
sd x11, (11 * REGSZ)(x5)
sd x12, (12 * REGSZ)(x5)
sd x13, (13 * REGSZ)(x5)
sd x14, (14 * REGSZ)(x5)
sd x15, (15 * REGSZ)(x5)
sd x16, (16 * REGSZ)(x5)
sd x17, (17 * REGSZ)(x5)
sd x18, (18 * REGSZ)(x5)
sd x19, (19 * REGSZ)(x5)
sd x20, (20 * REGSZ)(x5)
sd x21, (21 * REGSZ)(x5)
sd x22, (22 * REGSZ)(x5)
sd x23, (23 * REGSZ)(x5)
sd x24, (24 * REGSZ)(x5)
sd x25, (25 * REGSZ)(x5)
sd x26, (26 * REGSZ)(x5)
sd x27, (27 * REGSZ)(x5)
sd x28, (28 * REGSZ)(x5)
sd x29, (29 * REGSZ)(x5)
sd x30, (30 * REGSZ)(x5)
sd x31, (31 * REGSZ)(x5)
# save privilege registers
# save mepc by x1, which has been saved
csrr x1, mepc
sd x1, (32 * REGSZ)(x5)

# call trap_handler
# Need set stack pointer?
call trap_handler

# use x5 as cpu state base address register
la x5, trap_cpu
# restore privilege registers
# restore mepc by x1, which will be restored later
ld x1, (32 * REGSZ)(x5)
csrw mepc, x1
# restore general purpose registers
# x0 ~ x4
ld x0, (0 * REGSZ)(x5)
ld x1, (1 * REGSZ)(x5)
ld x2, (2 * REGSZ)(x5)
ld x3, (3 * REGSZ)(x5)
ld x4, (4 * REGSZ)(x5)
# postpone the restoration of x5
# because it is being used as the base address register
# x6 ~ x31
ld x6, (6 * REGSZ)(x5)
ld x7, (7 * REGSZ)(x5)
ld x8, (8 * REGSZ)(x5)
ld x9, (9 * REGSZ)(x5)
ld x10, (10 * REGSZ)(x5)
ld x11, (11 * REGSZ)(x5)
ld x12, (12 * REGSZ)(x5)
ld x13, (13 * REGSZ)(x5)
ld x14, (14 * REGSZ)(x5)
ld x15, (15 * REGSZ)(x5)
ld x16, (16 * REGSZ)(x5)
ld x17, (17 * REGSZ)(x5)
ld x18, (18 * REGSZ)(x5)
ld x19, (19 * REGSZ)(x5)
ld x20, (20 * REGSZ)(x5)
ld x21, (21 * REGSZ)(x5)
ld x22, (22 * REGSZ)(x5)
ld x23, (23 * REGSZ)(x5)
ld x24, (24 * REGSZ)(x5)
ld x25, (25 * REGSZ)(x5)
ld x26, (26 * REGSZ)(x5)
ld x27, (27 * REGSZ)(x5)
ld x28, (28 * REGSZ)(x5)
ld x29, (29 * REGSZ)(x5)
ld x30, (30 * REGSZ)(x5)
ld x31, (31 * REGSZ)(x5)
# x5
ld x5, (6 * REGSZ)(x5)

mret
# j trap_entry
