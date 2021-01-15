#include <Arduino.h>
#include "./gfx/gfx.h"
#include "./state/state.h"

void setup() {
  state::setup();
  gfx::setup();
}

void loop() {
  gfx::loop();
}