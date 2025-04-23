#pragma once

#ifdef USE_ESP_IDF

#include "esphome/core/component.h"
#include "esphome/components/display/display.h"
#include "esphome/components/display/display_buffer.h"

#ifdef USE_QUAD_SPI
  #include "esphome/components/quad_spi/quad_spi.h"
  namespace bus = esphome::quad_spi;
#else
  #include "esphome/components/spi/spi.h"
  namespace bus = esphome::spi;
#endif

namespace esphome {
namespace axs15231 {

class AXS15231Display : public display::DisplayBuffer,
                        public bus::SPIDevice<bus::BIT_ORDER_MSB_FIRST,
                                              bus::CLOCK_POLARITY_LOW,
                                              bus::CLOCK_PHASE_LEADING,
                                              bus::DATA_RATE_20MHZ> {
 public:
  void update() override;
  float get_setup_priority() const override;
  void setup() override;
  bool can_proceed() override;
  void dump_config() override;

  // DisplayBuffer overrides
  display::DisplayType get_display_type() override;
  int get_width_internal() override;
  int get_height_internal() override;

  void draw_absolute_pixel_internal(int x, int y, Color color) override;
  void draw_pixels_at(int x_start, int y_start, int w, int h, const uint8_t *ptr,
                      display::ColorOrder order, display::ColorBitness bitness,
                      bool big_endian, int x_offset, int y_offset, int x_pad) override;

  // Configuration
  void set_reset_pin(GPIOPin *reset_pin);
  void set_backlight_pin(GPIOPin *backlight_pin);
  void set_width(uint16_t width);
  void set_dimensions(uint16_t width, uint16_t height);
  void set_offsets(int16_t offset_x, int16_t offset_y);
  void set_mirror_x(bool mirror_x);
  void set_mirror_y(bool mirror_y);
  void set_swap_xy(bool swap_xy);
  void set_brightness(uint8_t brightness);

  // Other
  void fill(Color color);
  uint32_t get_buffer_length_();

 protected:
  void setup_pins_();
  void setup_madctl_();
  void init_lcd_();
  void reset_();
  void invalidate_();

  void write_command_(uint8_t cmd, const uint8_t *bytes, size_t len);
  void write_command_(uint8_t cmd, uint8_t data);
  void write_command_(uint8_t cmd);
  void set_addr_window_(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

 private:
  GPIOPin *reset_pin_{nullptr};
  GPIOPin *backlight_pin_{nullptr};

  uint16_t x_low_{1};
  uint16_t y_low_{1};
  uint16_t x_high_{0};
  uint16_t y_high_{0};
  bool setup_complete_{false};

  size_t width_{};
  size_t height_{};
  int16_t offset_x_{0};
  int16_t offset_y_{0};
  bool swap_xy_{false};
  bool mirror_x_{false};
  bool mirror_y_{false};
  bool draw_from_origin_{true};
  uint8_t brightness_{0xD0};
};

}  // namespace axs15231
}  // namespace esphome

#endif  // USE_ESP_IDF
