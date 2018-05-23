#ifndef ADC_H
#define ADC_H

  #include <stdbool.h>
  #include <stdint.h>
  #include "nrf_drv_saadc.h"

  void measure_vcc(void);
  void saadc_callback(nrf_drv_saadc_evt_t const * p_event);
  void saadc_init(void);

#endif
