#include <iostream>
#include <sstream>

enum switches {
  LIGHT_iNSIDE = 1,
  LIGHT_OUTSIDE = 2,
  HEATING = 4,
  HEATING_WATER_PIPE = 8,
  CONDITION = 16
};

bool input_control(std::string str) {
  {
    int count = 0;
    for (int i = 0; i < str.size(); i++) {
      if (isspace(str[i])) {
        count++;
      }
    }
    if (count < 3) {
      std::cerr << "Enter all indicators separated by spaces\n";
    }
  }

  std::string num_1, num_2, movement, light;
  std::stringstream buffer_str(str);
  buffer_str >> num_1 >> num_2 >> movement >> light;

  for (int i = 0; i < num_1.size(); i++) {
    if (!isdigit(num_1[i])) {
      std::cerr << "Enter the inside temperature as a number only\n";
      return false;
    }
  }
  for (int i = 0; i < num_2.size(); i++) {
    if (!isdigit(num_2[i])) {
      std::cerr << "Enter the outside temperature as a number only\n";
      return false;
    }
  }
  if (movement != "yes" && movement != "no") {
    std::cerr << "Enter movement only: \"yes\" or \"no\"\n";
    return false;
  }
  if (light != "on" && light != "off") {
    std::cerr << "Enter light only: \"on\" or \"off\"\n";
    return false;
  }

  return true;
}

void printNotes(int val) {}

int main() {
  std::cout << "Calculator\n";
  std::string indicators;
  do {
    std::cout
        << "Temperature inside, temperature outside, movement, lights: \n";
    std::getline(std::cin, indicators);
  } while (!input_control(indicators));

  int temp_inside, temp_outside;
  std::string movement, light;
  std::stringstream buffer_indicators(indicators);
  buffer_indicators >> temp_inside >> temp_outside >> movement >> light;

  std::cout << "T inside: " << temp_inside << "\n";
  std::cout << "T outside: " << temp_outside << "\n";
  std::cout << "Movement: " << movement << "\n";
  std::cout << "Light: " << light << "\n";
}