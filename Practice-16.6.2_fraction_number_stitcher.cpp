#include <iostream>

std::string beforDotAfterDot() {
  std::string str = "";
  int value;
  int n = 0;

  do {
    if (n == 0) {
      std::cout << "Input number before dot: ";
    } else {
      std::cout << "Input number after dot: ";
    }
    std::cin >> value;

    if (value < 0) {
      std::cerr << "Error. The number after the dot must be positive\n";
      continue;
    }

    str += std::to_string(value);
    if (n == 0) {
      str += '.';
    }

    n++;
  } while (n < 2);

  return str;
}

int main() {
  std::string fractionalNumber = beforDotAfterDot();

  double number = stod(fractionalNumber);

  std::cout << "You number: " << number;
}