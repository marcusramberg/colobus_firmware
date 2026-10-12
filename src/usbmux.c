#include "usbmux.h"

#include <hardware/gpio.h>
#include <stdint.h>

#pragma mark public
static void usbmux_configure_pair(enum Muxcfg cfg, uint32_t sel0, uint32_t sel1){
  gpio_init(sel0);
  gpio_init(sel1);
  uint32_t val =  ((((uint8_t)cfg) >> 0) & 1) << sel0
                | ((((uint8_t)cfg) >> 1) & 1) << sel1;
  uint32_t mask = (1<<sel0) | (1<<sel1);
  gpio_put_masked(mask, val);
  gpio_set_dir_out_masked(mask);
}

static void usbmux_release_pair(uint32_t sel0, uint32_t sel1){
  gpio_init(sel0);
  gpio_init(sel1);
  gpio_set_dir(sel0, GPIO_IN);
  gpio_set_dir(sel1, GPIO_IN);
}

void usbmux_configure_old(enum Muxcfg cfg){
  usbmux_release_pair(USBMUX_ALT_SEL0, USBMUX_ALT_SEL1);
  usbmux_configure_pair(cfg, USBMUX_SEL0, USBMUX_SEL1);
}

void usbmux_configure_new(enum Muxcfg cfg){
  usbmux_release_pair(USBMUX_SEL0, USBMUX_SEL1);
  usbmux_configure_pair(cfg, USBMUX_ALT_SEL0, USBMUX_ALT_SEL1);
}

void usbmux_configure(enum Muxcfg cfg){
  usbmux_configure_pair(cfg, USBMUX_SEL0, USBMUX_SEL1);
  usbmux_configure_pair(cfg, USBMUX_ALT_SEL0, USBMUX_ALT_SEL1);
}
