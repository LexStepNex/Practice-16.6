#include <iostream>
#include <sstream>

bool control_function(std::string str) {  //**Проверка на чистый ввод
  if (str.size() < 3) {
    return false;
  }
  int count = 0;

  for (int i = count, dots = 0; i < str.size(); i++) {
    bool sign = str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/';
    
    count = i;

    if (str[i] == '.') dots++;
    if (dots > 1) return false;

    if (i < 1 && !isdigit(str[i]) && str[i] != '.') {  // проверка числа слева + точка
      return false;
    } else if (!isdigit(str[i]) && str[i] != '.') {
      if (!sign) {
        return false;
      } else {
        break;
      }
    }
  }
  if (count == str.size() - 1) return false;

  for (int i = count + 1, dots = 0; i < str.size(); i++) {  // проверка числа справа + точка
    if (str[i] == '.') dots++;
    if (dots > 1) return false;

    if (!isdigit(str[i]) && str[i] != '.') {
      return false;
    }
  }
  return true;
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

    if (!control_function(function)) {
      std::cerr << "Error. Function type only (number)(operation)(number)\n";
    }
  } while (!control_function(function));

  double a, b;
  char operation;

  std::stringstream buffer_stream(function);
  buffer_stream >> a >> operation >> b;
  std::cout << "You function: " << a << operation << b << "\n";

  double result = resultFun(a, b, operation);
  std::cout << "Result = " << result;
}