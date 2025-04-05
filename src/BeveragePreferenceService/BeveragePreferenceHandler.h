#ifndef VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H

#include "../../gen-cpp/BeveragePreferenceService.h"

#include <string>
#include <random>

namespace vending_machine {

class BeveragePreferenceServiceHandler : public BeveragePreferenceServiceIf {
public:
    BeveragePreferenceServiceHandler() = default;
    virtual ~BeveragePreferenceServiceHandler() = default;

    void getBeverage(std::string& _return, const BeverageType::type btype) override;
};

void BeveragePreferenceServiceHandler::getBeverage(std::string& _return, const BeverageType::type btype) {
  std::vector<std::string> hotBeverages = {"Cappuccino", "Latte", "Espresso"};
  std::vector<std::string> coldBeverages = {"Lemonade", "Iced Coffee", "Soda"};
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 2);  // Assuming we have 3 beverages in each list

  if (btype == BeverageType::HOT) {
      _return = hotBeverages[dis(gen)];  // Randomly pick a hot beverage
  } else if (btype == BeverageType::COLD) {
      _return = coldBeverages[dis(gen)];  // Randomly pick a cold beverage
  } else {
      _return = "No beverage found!";
  }
}

} // namespace vending_machine

#endif //VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H
