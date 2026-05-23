;--- DO NOT put spaces at the start of the next 5 lines ---
    AREA    RESET, CODE, READONLY
    THUMB
    EXPORT  __Vectors
    EXPORT  Reset_Handler
    IMPORT  main

;--- This line MUST start at the absolute left margin ---
__Vectors
    DCD     0x20040000     ; Top of Stack (RAM End for RP2040)
    DCD     Reset_Handler  ; Reset Vector

;--- This line MUST start at the absolute left margin ---
Reset_Handler
    LDR     R0, =main
    BX      R0
    ALIGN
    END