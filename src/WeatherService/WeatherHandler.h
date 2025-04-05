#ifndef VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/WeatherService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine {

class WeatherServiceHandler : public WeatherServiceIf {
 public:
  WeatherServiceHandler();
  ~WeatherServiceHandler() override = default;

  WeatherType::type GetWeather(const int64_t city) override;
};

// Constructor implementation
inline WeatherServiceHandler::WeatherServiceHandler() {
  // Optional: Constructor logic
}

// GetWeather implementation
inline WeatherType::type WeatherServiceHandler::GetWeather(const int64_t city) {
  printf("GetWeather\n");
  if (city % 2 == 0) {
    printf("Returning COLD\n");
    return WeatherType::COLD;
  } else {
    printf("Returning WARM\n");
    return WeatherType::WARM;
  }
}

}  // namespace vending_machine

#endif  // VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H
