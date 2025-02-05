/* Error Codes :
 *         uart_init_err : Green LED on
 *         uart_transmit_err : Yellow LED on
 *         pll1_not_ready : Red on
 *         sys_clk_nok : Green + Yellow on
 *         uart_transmit : Green + Yellow + Red on
 */

enum errors {uart_init_err, uart_transmit_err, pll1_not_ready, sys_clk_nok, uart_transmit};

void init_err_led();
void set_error(int err_code);
void clear_status();
void green_on();
void yellow_on();
void red_on();
