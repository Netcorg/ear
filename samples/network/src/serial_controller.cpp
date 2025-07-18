#include <cstring>
#include "serial_controller.h"
#include "position.h"

static Position position = {0.0f, 0.0f};

SerialController::SerialController(const std::string &name)
  : EAR::IO::Controller(name)
{
  
}

SerialController::~SerialController() {
  
}

int32_t SerialController::open(void *param) {
  return -1;
}

int32_t SerialController::close(void) {
  return -1;
}

int32_t SerialController::read(void *buf, const uint16_t size) {
  memset(buf, 0x00, size);

  /// @todo how to generate position model here
  position.longitude += -0.1f;
  position.latitude += 0.2f;

  memcpy(buf, &position, sizeof(position));
    
  return sizeof(position);
}

int32_t SerialController::write(const void *buf, const uint16_t size) {
  const Position *pos = reinterpret_cast<const Position *>(buf);
  
  position.longitude += pos->longitude;
  position.latitude += pos->latitude;
  
  return sizeof(position);
}
