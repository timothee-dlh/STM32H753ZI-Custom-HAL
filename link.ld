ENTRY(Reset_Handler)

MEMORY{
    FLASH(rx) : ORIGIN = 0x08000000 LENGTH = 2M
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}


SECTIONS{


    .isr_vectors : { 
        KEEP(*(.isr_vector)) 
    }> FLASH
    . = ALIGN(4);
    
    .text : {
        
        _stext = .;
        *(.text)
        _etext = .;
        . = ALIGN(4);


    }> FLASH

    .rodata : {
        *(.rodata)
        . = ALIGN(4);
    }> FLASH

    _lmaData = LOADADDR(.data);
    .data : {
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss : {
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    }> SRAM

}

