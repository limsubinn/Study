vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xil_defaultlib
vlib activehdl/xpm

vmap xilinx_vip activehdl/xilinx_vip
vmap xil_defaultlib activehdl/xil_defaultlib
vmap xpm activehdl/xpm

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/70cf/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/70cf/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_processing_system7_0_0/zync_gpio_processing_system7_0_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_axi_gpio_0_0/zync_gpio_axi_gpio_0_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_axi_gpio_0_2/zync_gpio_axi_gpio_0_2_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_xbar_0/zync_gpio_xbar_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_auto_pc_0/zync_gpio_auto_pc_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_rst_ps7_0_50M_0/zync_gpio_rst_ps7_0_50M_0_sim_netlist.v" \
"../../../bd/zync_gpio/sim/zync_gpio.v" \

vlog -work xil_defaultlib \
"glbl.v"

