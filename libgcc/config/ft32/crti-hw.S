.equ SYS_REGMSC0CFG_B3  , 0x1001b
.equ SYS_REGIRQCTL_B3   , 0x100e3

.global _start
_start:
# START Interrupt Vector Table [[
        jmp     0x3fffc         # RESET Vector
        jmp     _watchdog_isr   # WATCHDOG Vector # TODO: Change me to reset the chip proper
        jmp     interrupt_0
        jmp     interrupt_1
        jmp     interrupt_2
        jmp     interrupt_3
        jmp     interrupt_4
        jmp     interrupt_5
        jmp     interrupt_6
        jmp     interrupt_7
        jmp     interrupt_8
        jmp     interrupt_9
        jmp     interrupt_10
        jmp     interrupt_11
        jmp     interrupt_12
        jmp     interrupt_13
        jmp     interrupt_14
        jmp     interrupt_15
        jmp     interrupt_16
        jmp     interrupt_17
        jmp     interrupt_18
        jmp     interrupt_19
        jmp     interrupt_20
        jmp     interrupt_21
        jmp     interrupt_22
        jmp     interrupt_23
        jmp     interrupt_24
        jmp     interrupt_25
        jmp     interrupt_26
        jmp     interrupt_27
        jmp     interrupt_28
        jmp     interrupt_29
        jmp     interrupt_30
        jmp     interrupt_31
        jmp     0x3fff8
# ]] END Interrupt Vector Table

codestart:
        jmp    init

        
.global _exithook
_exithook:               # Debugger uses '_exithook' at 0x90 to catch program exit
        return
        
init:
        # Disable all interrupts
        ldk     $r0,0x80
        sta.b   0x100e3,$r0
        
        # Reset all peripherals
        # lda.l   $r0, 0x10018
        # bins.l  $r0, $r0, 0x23F  # Set bit 31
        # sta.l   0x10018, $r0
        
        # Initialize DATA by copying from program memory
        ldk.l   $r0,__data_load_start
        ldk.l   $r1,__data_load_end
        ldk.l   $r2,0   # Will use __data after binutils patch

        jmp     .dscopy
.dsloop:
        # Copy PM[$r0] to RAM $r2
        lpmi.l  $r3,$r0,0
        sti.l   $r2,0,$r3
        add.l   $r0,$r0,4
        add.l   $r2,$r2,4
.dscopy:
        cmp.l   $r0,$r1
        jmpc    lt,.dsloop

        # Zero BSS
        ldk.l   $r0,_bss_start
        ldk.l   $r2,_end
        sub.l   $r2,$r2,$r0
        ldk.l   $r1,0
        memset.l  $r0,$r1,$r2

        sub.l   $sp,$sp,24  # Space for the caller argument frame
        call    main

.equ EXITEXIT    , 0x1fffc

.global _exit
_exit:
        sta.l   EXITEXIT,$r0    # simulator end of test
        jmp     _exithook

_watchdog_isr:
        ldk.l   $sp, 0x80FFFF   # Reset the stack pointer so it doesn't grow to a huge size
        jmp     0

# Macro to construct the interrupt stub code.
# it just saves r0, loads r0 with the int vector
# and branches to interrupt_common.

.macro  inth i=0
interrupt_\i:
        push    $r0     # {
        lda     $r0,(vector_table + 4 * \i)
        jmp     interrupt_common
.endm

        inth    0
        inth    1
        inth    2
        inth    3
        inth    4
        inth    5
        inth    6
        inth    7
        inth    8
        inth    9
        inth    10
        inth    11
        inth    12
        inth    13
        inth    14
        inth    15
        inth    16
        inth    17
        inth    18
        inth    19
        inth    20
        inth    21
        inth    22
        inth    23
        inth    24
        inth    25
        inth    26
        inth    27
        inth    28
        inth    29
        inth    30
        inth    31
        inth    32

        # On entry: r0, already saved, holds the handler function
interrupt_common:
        push    $r1     # {
        push    $r2     # {
        push    $r3     # {
        push    $r4     # {
        push    $r5     # {
        push    $r6     # {
        push    $r7     # {
        push    $r8     # {
        push    $r9     # {
        push    $r10    # {
        push    $r11    # {
        push    $r12    # {
        push    $cc     # {

        calli   $r0

        pop     $cc     # }
        pop     $r12    # }
        pop     $r11    # }
        pop     $r10    # }
        pop     $r9     # }
        pop     $r8     # }
        pop     $r7     # }
        pop     $r6     # }
        pop     $r5     # }
        pop     $r4     # }
        pop     $r3     # }
        pop     $r2     # }
        pop     $r1     # }
        pop     $r0     # } matching push in interrupt_0-31 above
        reti

        # Null function for unassigned interrupt to point at
.global     nullvector
nullvector:
        return

.section .data
.global vector_table
vector_table:
        .rept 33
                .long   nullvector
        .endr


.section .text
.global __gxx_personality_sj0
__gxx_personality_sj0:
