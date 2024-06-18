#include <iostream>
enum note { DO = 1, RE = 2, MI = 4, FA = 8, SOL = 16, LA = 32, SI = 64 };

void printNotes(int val) {
  if (val & DO) std::cout << "DO ";
  if (val & RE) std::cout << "RE ";
  if (val & MI) std::cout << "MI ";
  if (val & FA) std::cout << "FA ";
  if (val & SOL) std::cout << "SOL ";
  if (val & LA) std::cout << "LA ";
  if (val & SI) std::cout << "SI ";
  std::cout << "\n";
}

int main() {
  std::cout << "Simulation piano\n";

  std::string chord ;
  std::cout << "Input chord: \n";
  std::cin >> chord;
  
  for (int i = 0; i < chord.size(); i++) {
    if ('1' > chord[i] || chord[i] > '7') {
      std::cerr << "Input only digit from 1 to 7\n";
      return 0;
    }
  }

  int notes = 0;
  for (int i = 0, n = 1; i < chord.size(); i++) {
    notes |= (int)n << ((int)chord[i] - (int)'0' - (int)1);
  }

  printNotes(notes);
}