/**
 *  @file osdep_dummy.c
 *  @brief Mercury API - Sample OS-dependent functions that do nothing
 *  @author Nathan Williams
 *  @date 2/24/2010
 */

#include <stdint.h>
#include "pico/time.h"
#include "osdep.h"

uint64_t tmr_gettime(void) {
  uint64_t t = get_absolute_time();
  uint32_t t_ms = us_to_ms(t);
  return (uint64_t) t_ms;
}

uint32_t tmr_gettime_low()
{
  /* Fill in with code that returns the low 32 bits of a millisecond
   * counter. The API will not otherwise interpret the counter value.
   */
  return (tmr_gettime() >> 0) & 0xffffffff;
}

uint32_t tmr_gettime_high()
{
  /* Fill in with code that returns the hugh 32 bits of a millisecond
   * counter. The API will not otherwise interpret the counter value.
   * Returning 0 is acceptable here if you do not have a large enough counter.
   */
  return 0;
}

void
tmr_sleep(uint32_t sleepms)
{
  /*
   * Fill in with code that returns after at least sleepms milliseconds
   * have elapsed.
   */

  sleep_ms(sleepms);
}

TMR_TimeStructure
tmr_gettimestructure()
{
  TMR_TimeStructure timestructure;


  timestructure.tm_year = (uint32_t)0;
  timestructure.tm_mon = (uint32_t)0;
  timestructure.tm_mday = (uint32_t)0;
  timestructure.tm_hour = (uint32_t)0;
  timestructure.tm_min = (uint32_t)0;
  timestructure.tm_sec = (uint32_t)0;

  return timestructure;
}
