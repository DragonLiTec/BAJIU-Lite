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

    //hello led
    reg l0, l1;
    assign led0 = l0;
    assign led1 = l1;
    reg [22:0] cnt;
    always@(posedge clk25m) begin
        cnt <= cnt + 1;
        if(cnt == 0)
            l0 <= ~l0;
    end
    reg btn_last;
    always@(posedge clk100m) begin
        if(btn0 & ~btn_last)
            l1 <= ~l1;
        btn_last = btn0;
    end
endmodule
