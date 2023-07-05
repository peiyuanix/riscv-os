## mtime 和 mtimecmp 只属于机器模式！

### mtime & mtimecmp
> Reter to: Volume II: RISC-V Privileged Architectures V20211203 P45  
> 
> Lower privilege levels do not have their own timecmp registers. Instead, machine-mode software can implement any number of virtual timers on a hart by multiplexing the next timer interrupt into the mtimecmp register.

### ecall
> ECALL generates a different exception for each originating privilege mode so that environment call exceptions can be selectively delegated. A typical use case for Unix-like operating systems is to delegate to S-mode the environment-call-from-U-mode exception but not the others.

### sstatus
> sstatus
> 
> The SIE bit enables or disables all interrupts in supervisor mode. When SIE is clear, interrupts are not taken while in supervisor mode. When the hart is running in user-mode, the value in SIE is ignored, and supervisor-level interrupts are enabled. The supervisor can disable individual interrupt sources using the sie CSR. The SPIE bit indicates whether supervisor interrupts were enabled prior to trapping into supervisor mode. When a trap is taken into supervisor mode, SPIE is set to SIE, and SIE is set to 0. When an SRET instruction is executed, SIE is set to SPIE, then SPIE is set to 1.  

### When trap to M-mode?  
> An interrupt i will trap to M-mode (causing the privilege mode to change to M-mode) if all of the following are true: (a) either the current privilege mode is M and the MIE bit in the mstatus register is set, or the current privilege mode has less privilege than M-mode; (b) bit i is set in both mip and mie; and (c) if register mideleg exists, bit i is not set in mideleg.
> 
> Interrupts to M-mode take priority over any interrupts to lower privilege modes.


### When trap to S-mode?  
> An interrupt i will trap to S-mode if both of the following are true: (a) either the current privilege mode is S and the SIE bit in the sstatus register is set, or the current privilege mode has less privilege than S-mode; and (b) bit i is set in both sip and sie.
> 
> Interrupts to S-mode take priority over any interrupts to lower privilege modes.
> 
> Each standard interrupt type (SEI, STI, or SSI) may not be implemented, in which case the corresponding interrupt-pending and interrupt-enable bits are read-only zeros. All bits in sip and sie are WARL fields. The implemented interrupts may be found by writing one to every bit location in sie, then reading back to see which bit positions hold a one.