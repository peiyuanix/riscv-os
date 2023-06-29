.text

.global trap_entry

.equ MTIME, 0x200bff8

trap_entry:

li t0, MTIME
ld a0, 0(t0)

j trap_entry
