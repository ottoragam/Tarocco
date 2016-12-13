# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\code\cypress\SCB_Bootloader\cncboot.cydsn\cncboot.cyprj
# Date: Sun, 18 Sep 2016 00:34:04 GMT
#set_units -time ns
create_clock -name {Clock_1(FFB)} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/ff_div_8}]]
create_clock -name {UART_SCBCLK(FFB)} -period 708.33333333333326 -waveform {0 354.166666666667} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 9 17} [list]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 17 35} -nominal_period 708.33333333333326 [list]


# Component constraints for D:\code\cypress\SCB_Bootloader\cncboot.cydsn\TopDesign\TopDesign.cysch
# Project: D:\code\cypress\SCB_Bootloader\cncboot.cydsn\cncboot.cyprj
# Date: Sun, 18 Sep 2016 00:34:02 GMT
