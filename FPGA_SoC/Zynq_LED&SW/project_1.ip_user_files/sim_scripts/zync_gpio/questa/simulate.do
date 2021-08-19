onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib zync_gpio_opt

do {wave.do}

view wave
view structure
view signals

do {zync_gpio.udo}

run -all

quit -force
