#include <cmath>
#include <iostream>

using namespace std;

double x, x_start, x_end, x_step;
double y, z;
double a, b;
double n;

double dRound(double x, int n) {
  return round(x * pow(10, n)) / pow(10, n);
}

double calculateA(double x, double y, double z, double b) {
  double a, h1, h2, h3;

  h1 = (z / pow(x, 2)) + pow(sin(b), 2);
  h2 = fabs((pow(x, 2) + y) / (z + (pow(x, 3) / 3)));
  h3 = log(fabs(pow(x, 2) + z));
  a = pow(y, 2) + (h1 / (h2 - h3));

  return a;
}

double calculateB(double x, double y, double z) {
  double b, h1, h2, h3;

  h1 = (x + y) / (pow(fabs(z), 0.6));
  h2 = pow(sin((x + pow(z, 2)) / ((2 * x) + y)), 2);
  h3 = z * exp((pow(x, 2) - y) / (1 + z));

  b = pow(fabs(h1 + h2), 1 / 3.0) - h3;

  return b;
}

int main() {
  n = 16;

  x_start = -1;
  x_end = 1;
  x_step = 0.2;

  y = 0.47 * n;
  z = -1.32 * n;

  for (x = x_start; x <= x_end; x = dRound(x + x_step, 3)) {
    b = calculateB(x, y, z);
    a = calculateA(x, y, z, b);

    cout << "x = " << x << ", a = " << a << ", b = " << b << "\n";
  }

  return 0;
}
