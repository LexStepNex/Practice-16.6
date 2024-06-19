#include <iostream>

int main() {
  std::cout << "Speedometer from 0 to 150 km/h\n";
  char speed_str[9] = "0.0";
  std::string result = speed_str;
  result += "km/h";
  std::cout << "Start ";

  do {
    std::cout << "Speed: " << result << "\n";
    float deltaSpeed = 0;

    while (1) {
      std::cout << "Input delta speed: ";
      std::cin >> deltaSpeed;

      if (atof(speed_str) <= 0.f && deltaSpeed <= 0.f) {
        std::cerr << "the first delta speed must be greater than\n";
        continue;
      }
      break;
    }

    sprintf(speed_str, "%.2f", atof(speed_str) + deltaSpeed);

    if (atof(speed_str) > 150.f) {
      sprintf(speed_str, "%.2f", 150.f);
    }
    if (atof(speed_str) < 0.f) {
      sprintf(speed_str, "%.2f", 0.f);
    }
    
    result = speed_str;
    result.pop_back();
    result += " km/h";
  } while (atof(speed_str) + 0.01f > 0.01f);

  std::cout << "Speed: " << result << "\n";
}