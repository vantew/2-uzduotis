#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include <iostream>
#include <vector>
#include <sstream> // getline išskirstymui
#include <random> // atsitiktiniai skaičiai
#include <algorithm> // sort
#include <fstream> // darbas su failais
#include <iomanip> // setw, setprecision, std::left, std::right
#include <stdexcept> // try catch
#include <chrono>
#include <list>
#include <numeric>
#include <cstring>

using std::list;
using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::setw;
using std::setprecision;
using std::left;
using std::fixed;
using std::sort;
using std::rand;
using std::numeric_limits;
using std::streamsize;
using std::getline;
using std::ifstream;
using std::stringstream;
using std::runtime_error;
using std::ofstream;
using std::cerr;
using std::exception;
using std::to_string;
using std::istringstream;
using std::ostream;
using std::swap;
using std::is_same;
using std::istream;
using std::conditional;
using std::is_same_v;
using std::next;
using std::prev;

class Timer {
  private:
    using hrClock = std::chrono::high_resolution_clock;
    using durationDouble = std::chrono::duration<double>;
    std::chrono::time_point<hrClock> start;
  public:
    Timer() : start{ hrClock::now() } {}
    void reset() {
      start = hrClock::now();
    }
    double elapsed() const {
      return durationDouble (hrClock::now() - start).count();
    }
};

#endif
