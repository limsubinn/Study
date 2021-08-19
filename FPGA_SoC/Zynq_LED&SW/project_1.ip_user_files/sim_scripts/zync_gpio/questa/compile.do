vlib questa_lib/work
vlib questa_lib/msim

vlib questa_lib/msim/xilinx_vip
vlib questa_lib/msim/xil_defaultlib
vlib questa_lib/msim/xpm

vmap xilinx_vip questa_lib/msim/xilinx_vip
vmap xil_defaultlib questa_lib/msim/xil_defaultlib
vmap xpm questa_lib/msim/xpm

vlog -work xilinx_vip -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L xilinx_vip "+incdir+C:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2018.3/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib -64 -sv -L axi_vip_v1_1_4 -L processing_system7_vip_v1_0_6 -L xilinx_vip "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/70cf/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -64 -93 \
"C:/Xilinx/Vivado/2018.3/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work xil_defaultlib -64 "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/ec67/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ipshared/70cf/hdl" "+incdir+../../../../project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2018.3/data/xilinx_vip/include" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_processing_system7_0_0/zync_gpio_processing_system7_0_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_axi_gpio_0_0/zync_gpio_axi_gpio_0_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_axi_gpio_0_2/zync_gpio_axi_gpio_0_2_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_xbar_0/zync_gpio_xbar_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_auto_pc_0/zync_gpio_auto_pc_0_sim_netlist.v" \
"c:/project_1/project_1.srcs/sources_1/bd/zync_gpio/ip/zync_gpio_rst_ps7_0_50M_0/zync_gpio_rst_ps7_0_50M_0_sim_netlist.v" \
"../../../bd/zync_gpio/sim/zync_gpio.v" \

vlog -work xil_defaultlib \
"glbl.v"

