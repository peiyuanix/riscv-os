### 为什么 mstatus 会包含 SIE/SPIE/SPP 字段?它们真的有实际作用吗？  
事实上，只有一个物理 `status` 寄存器，`mstatus` 和 `sstatus` 看到的都是同一个物理 `status` 寄存器的视图！！！  

> Refer to: Volume II: RISC-V Privileged Architectures V20211203 P64  
> 
> The sstatus register is a subset of the mstatus register.  
> 
> In a straightforward implementation, reading or writing any field in sstatus is equivalent to reading or writing the homonymous field in mstatus.

> Refer to: fu540-c000-manual-v1p4.pdf P59  
> 
> 8.4.2 Supervisor Status Register (sstatus)
Similar to machine mode, supervisor mode has a register dedicated to keeping track of the hart’s current state called sstatus. sstatus is effectively a restricted view of mstatus, described in Section 8.3.1, in that changes made to sstatus are reflected in mstatus and viceversa, with the exception of the machine mode fields, which are not visible in sstatus.

实验测试：  
```
[firmware_main] Clear MSTATUS_MIE | MSTATUS_SIE for mstatus
[firmware_main] mstatus is 0x0
[firmware_main] sstatus is 0x0
[firmware_main] Set MSTATUS_SIE for mstatus
[firmware_main] mstatus is 0x2
[firmware_main] sstatus is 0x2
[firmware_main] Clear MSTATUS_MIE | MSTATUS_SIE for mstatus
[firmware_main] mstatus is 0x0
[firmware_main] sstatus is 0x0
[firmware_main] Set SSTATUS_SIE for sstatus
[firmware_main] mstatus is 0x2
[firmware_main] sstatus is 0x2
```

### `sie/sip` 是 `mie/mip` 的视图！！！
> Restricted views of the mip and mie registers appear as the sip and sie registers for supervisor level. If an interrupt is delegated to S-mode by setting a bit in the mideleg register, it becomes visible in the sip register and is maskable using the sie register. Otherwise, the corresponding bits in sip and sie are read-only zero.

> Volume II: RISC-V Privileged Architectures V20211203 P68  
> The sip and sie registers are subsets of the mip and mie registers. Reading any implemented field, or writing any writable field, of sip/sie effects a read or write of the homonymous field of mip/mie.  
> 
> Bits 3, 7, and 11 of sip and sie correspond to the machine-mode software, timer, and external interrupts, respectively. Since most platforms will choose not to make these interrupts delegatable from M-mode to S-mode, they are shown as 0 in Figures 4.6 and 4.7.

### Traps never transition from a more-privileged mode to a less-privileged mode
> Traps never transition from a more-privileged mode to a less-privileged mode. For example, if M-mode has delegated illegal instruction exceptions to S-mode, and M-mode software later executes an illegal instruction, the trap is taken in M-mode, rather than being delegated to S-mode. By contrast, traps may be taken horizontally. Using the same example, if M-mode has delegated illegal instruction exceptions to S-mode, and S-mode software later executes an illegal instruction, the trap is taken in S-mode.  
> 
> **What about M-mode timer interrupt?**  
> **What about M-mode software interrupt?**  
> **Is there S-mode timer interrupt?**  
> **Is the external interrupt in M-mode or S-mode?**  

### Delegated interrupts result in the interrupt being masked at the delegator privilege level  
> Delegated interrupts result in the interrupt being masked at the delegator privilege level. For example, if the supervisor timer interrupt (STI) is delegated to S-mode by setting mideleg[5], STIs will not be taken when executing in M-mode. By contrast, if mideleg[5] is clear, STIs can be taken in any mode and regardless of current mode will transfer control to M-mode.


### mtime 和 mtimecmp 只属于机器模式: mtime & mtimecmp
> Reter to: Volume II: RISC-V Privileged Architectures V20211203 P45  
> 
> Lower privilege levels do not have their own timecmp registers. Instead, machine-mode software can implement any number of virtual timers on a hart by multiplexing the next timer interrupt into the mtimecmp register.

### 何时触发 `M-mode external interrupt`?
> Bits mip.MEIP and mie.MEIE are the interrupt-pending and interrupt-enable bits for machinelevel external interrupts. MEIP is read-only in mip, and is set and cleared by a **platform-specific interrupt controller**.  

### 何时触发 `M-mode timer interrupt`?
> Bits mip.MTIP and mie.MTIE are the interrupt-pending and interrupt-enable bits for machine timer interrupts. MTIP is read-only in mip, and is cleared by writing to the memory-mapped **machine-mode timer compare register**.

### 何时触发 `M-mode software interrut`?
> Bits mip.MSIP and mie.MSIE are the interrupt-pending and interrupt-enable bits for machinelevel software interrupts. MSIP is read-only in mip, and is **written by accesses to memory-mapped control registers**, which are used by remote harts to provide machine-level interprocessor interrupts. A hart can write its own MSIP bit using the same memory-mapped control register. If a system has only one hart, or if a platform standard supports the delivery of machine-level interprocessor
interrupts through external interrupts (MEI) instead, then mip.MSIP and mie.MSIE may both be read-only zeros.

### 何时触发 `S-mode external interrupt`?
> If supervisor mode is implemented, bits mip.SEIP and mie.SEIE are the interrupt-pending and interrupt-enable bits for supervisor-level external interrupts. SEIP is writable in mip, and may be **written by M-mode software to indicate to S-mode that an external interrupt is pending**. Additionally, the **platform-level interrupt controller may generate supervisor-level external interrupts**. Supervisor-level external interrupts are made pending based on the logical-OR of the softwarewritable SEIP bit and the signal from the external interrupt controller. When mip is read with a CSR instruction, the value of the SEIP bit returned in the rd destination register is the logical-OR of the software-writable bit and the interrupt signal from the interrupt controller, but the signal from the interrupt controller is not used to calculate the value written to SEIP. Only the software-writable SEIP bit participates in the read-modify-write sequence of a CSRRS or CSRRC instruction.

### 何时触发 `S-mode timer interrupt`?
> If supervisor mode is implemented, bits mip.STIP and mie.STIE are the interrupt-pending and interrupt-enable bits for supervisor-level timer interrupts. STIP is writable in mip, and may be written by M-mode software to deliver timer interrupts to S-mode.

### 何时触发 `S-mode software interrupt`?
> If supervisor mode is implemented, bits mip.SSIP and mie.SSIE are the interrupt-pending and interrupt-enable bits for supervisor-level software interrupts. SSIP is writable in mip and may also be set to 1 by a platform-specific interrupt controller.


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

### Higher-privilege-level code can disable selected higher-privilege-mode before ceding control to a lower-privilege mode  
> When a hart is executing in privilege mode x, interrupts are globally enabled when xIE=1 and globally disabled when xIE=0. Interrupts for lower-privilege modes, w<x, are always globally disabled regardless of the setting of any global wIE bit for the lower-privilege mode. Interrupts for higher-privilege modes, y>x, are always globally enabled regardless of the setting of the global yIE bit for the higher-privilege mode. Higher-privilege-level code can use separate per-interrupt enable bits to disable selected higher-privilege-mode interrupts before ceding control to a lower-privilege mode.  
