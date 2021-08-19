onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+zync_gpio -L xilinx_vip -L xil_defaultlib -L xpm -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.zync_gpio xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {zync_gpio.udo}

run -all

endsim

quit -force
