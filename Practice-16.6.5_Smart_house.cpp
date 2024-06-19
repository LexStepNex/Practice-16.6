#include <iostream>
#include <sstream>

enum switches {
  LIGHT_iNSIDE = 1,
  LIGHT_OUTSIDE = 2,
  HEATING = 4,
  HEATING_WATER_PIPE = 8,
  CONDITIONER = 16
};

bool input_control(std::string str) {
  {  // проверка пробелов
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

  for (int i = 0; i < num_1.size(); i++) { //проверка температуры в доме
    if (num_1[0] = '-') continue;
    if (!isdigit(num_1[i])) {
      std::cerr << "Enter the inside temperature as a number only\n";
      return false;
    }
  }
  for (int i = 0; i < num_2.size(); i++) { //проверка температуры снаружи
    if (num_2[0] = '-') continue;
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

int color_temperature(int time) {
  int temp = 5000;
  if (time >= 16 && time <= 20) {
    temp = 5000 + (16 - time) * 575;
  } else if (time > 20) {
    temp = 5000 - 4 * 575;
  }
  if (time == 0) temp = 5000;
  return temp;
}

int light_inside(int switches, std::string light, bool times_Of_day, int time) {
  if (!(switches & LIGHT_iNSIDE) && light == "on") {  // вкл свет в доме
    switches |= LIGHT_iNSIDE;
    std::cout << "LIGHT_iNSIDE ON\n";
  } else if ((switches & LIGHT_iNSIDE) && light == "off") {  // выкл свет в доме
    switches &= ~LIGHT_iNSIDE;
    std::cout << "LIGHT_iNSIDE OFF\n";
  }
  if (light == "on") {
    std::cout << "Color temperature: " << color_temperature(time) << "K\n";
  }
  return switches;
}

int light_outside(int switches, std::string light, bool time) {
  if (!(switches & LIGHT_OUTSIDE) && light == "yes" && time) {  // вкл свет в саду
    switches |= LIGHT_OUTSIDE;
    std::cout << "LIGHT_OUTSIDE ON\n";
  } else if ((switches & LIGHT_OUTSIDE) && !time ||
             (switches & LIGHT_OUTSIDE) && light == "no") {  // выкл свет в саду
    switches &= ~LIGHT_OUTSIDE;
    std::cout << "LIGHT_OUTSIDE OFF\n";
  }
  return switches;
}

int heaters(int switches, int inside) {
  if (!(switches & HEATING) && inside < 22) {  // вкл отопление
    switches |= HEATING;
    std::cout << "HEATING ON\n";
  }
  if ((switches & HEATING) && inside >= 25) {  // выкл отопление 
    switches &= ~HEATING;
    std::cout << "HEATING OFF\n";
  }
  return switches;
}

int water_pipe(int switches, int outside) {
  if (!(switches & HEATING_WATER_PIPE) && outside < 0) {  // вкл отопление труб
    switches |= HEATING_WATER_PIPE;
    std::cout << "HEATING WATER PIPE ON\n";
  }
  if ((switches & HEATING_WATER_PIPE) && outside > 5) {  // выкл отопление труб
    switches &= ~HEATING_WATER_PIPE;
    std::cout << "HEATING WATER PIPE OFF\n";
  }
  return switches;
}

int air_conditioner(int switches, int inside) {
  if (!(switches & CONDITIONER) && inside >= 30) {  // вкл кондиционер
    switches |= CONDITIONER;
    std::cout << "CONDITION ON\n";
  }
  if ((switches & CONDITIONER) && inside < 26) {  // выкл кондиционер
    switches &= ~CONDITIONER;
    std::cout << "CONDITION OFF\n";
  }
  return switches;
}

int main() {
  std::cout << "Smart house\n";

  int time = 0;
  int switches_states = 0;
  int color_temp = 5000;

  for (int i = 0; i < 25; i++, time++) {
    std::cout << "Time O'clock: " << (time < 10 ? "0" : "") << time << ":00\n";
    
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

    bool night = time >= 16 || time < 5;
    switches_states = light_outside(switches_states, movement, night);

    switches_states = heaters(switches_states, temp_inside);
    switches_states = water_pipe(switches_states, temp_outside);

    switches_states = air_conditioner(switches_states, temp_inside);

    bool evening = time >= 16 || time < 20;
    switches_states = light_inside(switches_states, light, evening, time);

    std::cout << "\n";

    if (time == 23) time = -1;
  }
}