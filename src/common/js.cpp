#include <cstdlib>
#include "js.h"

extern "C" {
  void EMSCRIPTEN_KEEPALIVE initialize_random_seed(int seed) {
    srand(seed);
  }
}
