module Top(
    input clk25m,
    input clk50m,
    input clk100m,
    input pll_locked,
    input uart_rx0, uart_rx1,
    input btn0, btn1,
    output uart_tx0, uart_tx1,
    output led0, led1,
    
    output camera_io,
    input [7:0] gpio_read,
    output [7:0] gpio_write,
    output [7:0] gpio_OE,

    input scl_read,
    input sda_read,
    output scl_write, scl_OE,
    output sda_write, sda_OE,
    
    input jtagCtrl_sel,
    input jtagCtrl_tdi,
    input jtagCtrl_tms,
    input jtagCtrl_capture,
    input jtagCtrl_shift,
    input jtagCtrl_update,
    input jtagCtrl_reset,
    input jtagCtrl_tck,
    input jtagCtrl_drck,
    input jtagCtrl_runtest,
    output jtagCtrl_tdo, 
    
    output spi_ss,
    output spi_sclk,
    output spi_mosi,
    input  spi_miso
);

wire reset = ~pll_locked;

HelloUart uart0(
    .uart_rxd(uart_rx0),
    .uart_txd(uart_tx0),
    .clk(clk100m),
    .inc(1),
    .reset(reset)
 );
 
 HelloUart uart1(
    .uart_rxd(uart_rx1),
    .uart_txd(uart_tx1),
    .clk(clk100m),
    .inc(0),
    .reset(reset)
 );
endmodule
