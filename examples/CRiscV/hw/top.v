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
    input  [7:0] gpio_read,
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

wire [9:0] gpio_out;

assign gpio_write = gpio_out[7:0];
assign led0 = gpio_out[8];
assign led1 = gpio_out[9];

CRiscV soc(
    .mainClk(clk100m),
    .asyncReset(reset),
    
    .jtagCtrl_tck(jtagCtrl_tck),
    .jtagCtrl_tdi(jtagCtrl_tdi),
    .jtagCtrl_tdo(jtagCtrl_tdo),
    .jtagCtrl_enable(jtagCtrl_sel),
    .jtagCtrl_capture(jtagCtrl_capture),
    .jtagCtrl_shift(jtagCtrl_shift),
    .jtagCtrl_update(jtagCtrl_update),
    .jtagCtrl_reset(jtagCtrl_reset),
    
    .uart_rxd(uart_rx0),
    .uart_txd(uart_tx0), 
    .gpio_read(gpio_read),
    .gpio_write(gpio_out),
    .gpio_writeEnable(gpio_OE),
    
    .i2c_sda_read(sda_read),
    .i2c_sda_write(sda_write),
    .i2c_scl_read(scl_read),
    .i2c_scl_write(scl_write),
    .spi_ss(spi_ss),
    .spi_sclk(spi_sclk),
    .spi_mosi(spi_mosi),
    .spi_miso(spi_miso)
);
endmodule
