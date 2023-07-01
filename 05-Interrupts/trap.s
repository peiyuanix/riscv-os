.equ REGSZ, 8
.global trap_entry

.text

trap_entry:

# temp region
la t0, trap_cpu

# save registers
sd x0, (0 * REGSZ)(t0)
sd x1, (1 * REGSZ)(t0)
sd x2, (2 * REGSZ)(t0)
sd x3, (3 * REGSZ)(t0)
sd x4, (4 * REGSZ)(t0)
sd x5, (5 * REGSZ)(t0)
sd x6, (6 * REGSZ)(t0)
sd x7, (7 * REGSZ)(t0)
sd x8, (8 * REGSZ)(t0)
sd x9, (9 * REGSZ)(t0)
sd x10, (10 * REGSZ)(t0)
sd x11, (11 * REGSZ)(t0)
sd x12, (12 * REGSZ)(t0)
sd x13, (13 * REGSZ)(t0)
sd x14, (14 * REGSZ)(t0)
sd x15, (15 * REGSZ)(t0)
sd x16, (16 * REGSZ)(t0)
sd x17, (17 * REGSZ)(t0)
sd x18, (18 * REGSZ)(t0)
sd x19, (19 * REGSZ)(t0)
sd x20, (20 * REGSZ)(t0)
sd x21, (21 * REGSZ)(t0)
sd x22, (22 * REGSZ)(t0)
sd x23, (23 * REGSZ)(t0)
sd x24, (24 * REGSZ)(t0)
sd x25, (25 * REGSZ)(t0)
sd x26, (26 * REGSZ)(t0)
sd x27, (27 * REGSZ)(t0)
sd x28, (28 * REGSZ)(t0)
sd x29, (29 * REGSZ)(t0)
sd x30, (30 * REGSZ)(t0)
sd x31, (31 * REGSZ)(t0)

# call trap_handler
# Need set stack pointer?
call trap_handler

# restore registers
ld x0, (0 * REGSZ)(t0)
ld x1, (1 * REGSZ)(t0)
ld x2, (2 * REGSZ)(t0)
ld x3, (3 * REGSZ)(t0)
ld x4, (4 * REGSZ)(t0)
ld x5, (5 * REGSZ)(t0)
ld x6, (6 * REGSZ)(t0)
ld x7, (7 * REGSZ)(t0)
ld x8, (8 * REGSZ)(t0)
ld x9, (9 * REGSZ)(t0)
ld x10, (10 * REGSZ)(t0)
ld x11, (11 * REGSZ)(t0)
ld x12, (12 * REGSZ)(t0)
ld x13, (13 * REGSZ)(t0)
ld x14, (14 * REGSZ)(t0)
ld x15, (15 * REGSZ)(t0)
ld x16, (16 * REGSZ)(t0)
ld x17, (17 * REGSZ)(t0)
ld x18, (18 * REGSZ)(t0)
ld x19, (19 * REGSZ)(t0)
ld x20, (20 * REGSZ)(t0)
ld x21, (21 * REGSZ)(t0)
ld x22, (22 * REGSZ)(t0)
ld x23, (23 * REGSZ)(t0)
ld x24, (24 * REGSZ)(t0)
ld x25, (25 * REGSZ)(t0)
ld x26, (26 * REGSZ)(t0)
ld x27, (27 * REGSZ)(t0)
ld x28, (28 * REGSZ)(t0)
ld x29, (29 * REGSZ)(t0)
ld x30, (30 * REGSZ)(t0)
ld x31, (31 * REGSZ)(t0)

mret
# j trap_entry
