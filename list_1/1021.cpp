#include <iostream>
#include <iomanip>
#include <math.h>
 
#define EPLISON 0.009

using namespace std;
 
int main() {
  double moneyVal[12] = {100.00, 50.00, 20.00, 10.00, 5.00, 2.00, 1.00, 0.50, 0.25, 0.10, 0.050, 0.010};
  int moneyCount[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  /**
   * Escreva a sua solução aqui
   * Code your solution here
   * Escriba su solución aquí
   */
  double value = 0.0;
  int i = 0;
  std::cin >> value;
  int aa = 0;
  for (i = 0; i < 12; i++) {
    if(i == 11) {
      std::cout << "a=> " << value << " " << moneyVal[i] << " " <<  (value >= moneyVal[i])<< std::endl;
    }
    while ((value + EPLISON) >= moneyVal[i]) {
      moneyCount[i]++;
      value -= moneyVal[i];
    }
    
    // moneyCount[i] = roundf(value / moneyVal[i]);
    // value -= moneyCount[i] * moneyVal[i];
    if(moneyCount[i] != 0) {
      std::cout << "=> " << value << " " << i  << std::endl;
      int aa = 1;
    }
  }

  std::cout << "NOTAS:" << std::endl;
  for (i = 0; i < 6; i++) {
    std::cout << moneyCount[i] << " nota(s) de R$ ";
    std::cout << std::fixed << std::setprecision(2) << moneyVal[i] << std::endl;
  }
  std::cout << "MOEDAS:" << std::endl;
  for (; i < 12; i++) {
    std::cout << moneyCount[i] << " moeda(s) de R$ ";
    std::cout << std::fixed << std::setprecision(2) << moneyVal[i] << std::endl;
  }

  return 0;
}