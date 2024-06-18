#include <iostream>
#include <sstream>

bool control_operation(std::string str) {  //**Проверка на чистый ввод
  if (str.size() < 3) {
    std::cerr << "Error. Input a<operation>b";
    return false;
  }

  for (int i = 0, dots = 0; i < str.size() - 1; i++) {
    bool sign = str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/';

    if (str[i] == '.') dots++;
    if (dots > 1) return false;

    if (i < 1 && !isdigit(str[i]) && str[i] != '.') {  // проверка числа слева + точка
      return false;
    } else if (!isdigit(str[i]) && str[i] != '.') {
      if (!sign) {
        return false;
      } else {
        dots = 0;
        for (int j = i + 1; j < str.size(); j++) {  // проверка числа справа + точка
          if (str[i] == '.') dots++;
          if (dots > 1) return false;

          if (!isdigit(str[j]) && str[j] != '.') {
            return false;
          }
        }
        return true;
      }
    }
  }
  return false;
}

double resultFun(double a, double b, char sign) {
  double result;
  if (sign == '+') {
    result = a + b;
  } else if (sign == '-') {
    result = a - b;
  } else if (sign == '*') {
    result = a * b;
  } else if (sign == '/') {
    result = a / b;
  }
  return result;
}

int main() {
  std::cout << "Calculator\n";
  std::string function;

  do {
    std::cout << "Input you function(without spaces): ";
    std::getline(std::cin, function);

    if (!control_operation(function)) {
      std::cerr << "Error. Function type only (number)(operation)(number)\n";
    }
  } while (!control_operation(function));

  double a, b;
  char operation;

  std::stringstream buffer_stream(function);

  buffer_stream >> a >> operation >> b;

  std::cout << "You function: " << a << operation << b << "\n";

  double result = resultFun(a, b, operation);
  std::cout << "Result = " << result;
}