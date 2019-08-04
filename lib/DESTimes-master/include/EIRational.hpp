/**
 * EIRational (Extended Infinity Rational) class for Discrete Event Simulation purposes
 * Copyright (C) 2016  Laouen Mayal Louan Belloli
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EIRATIONAL_HPP
#define EIRATIONAL_HPP

#include <iostream>
#include <string>
#include <boost/rational.hpp>

using namespace std;

class EIRational {

  private:
    boost::rational<int> _value;
    bool _inf;
    bool _possitive;

  public:
    EIRational() : _inf(false) {}
    EIRational(int n) : _value(n), _inf(false) {}
    EIRational(int n, int d) : _value(n,d), _inf(false) {}

    static EIRational infinity() noexcept {
      EIRational f;
      f._inf=true;
      f._possitive=true;
      return f;
    }

    static EIRational minusInfinity() noexcept {
      EIRational f;
      f._inf=true;
      f._possitive=false;
      return f;
    }

    EIRational& operator=(const EIRational& o) noexcept { 
      this->_value = o._value;
      this->_inf = o._inf;
      this->_possitive = o._possitive;
      return *this;
    }


    /* Aritmetical operators */

    EIRational& operator+=(const EIRational& o) noexcept {
      this->_value += o._value;
      if (o._inf) {
        this->_inf = o._inf;
        this->_possitive = o._possitive; // + * {+/-} = {+/-}
      };
      return *this;
    }

    EIRational& operator-=(const EIRational& o) noexcept { 
      this->_value -= o._value;
      if (!this->_inf && o._inf) {
        this->_inf = o._inf;
        this->_possitive = !o._possitive; // - * {+/-} = {-/+}
      } else if (o._inf && (this->_possitive == o._possitive)) { //-inf-(-inf) = -inf+inf = 0 = inf-inf
        this->_inf = false;
        this->_value = boost::rational<int>(0);
      }
      return *this;
    }

    EIRational& operator/=(const EIRational& o) noexcept {
      if (!this->inf) {
        if (o._inf) {
          this->_value = boost::rational<int>(0);
        } else {
          this->_value /= o._value;
        }
      }
      return *this;
    }

    EIRational& operator*=(const EIRational& o) noexcept {
      if (!this->inf && o._inf) {
        this->_inf = o._inf;
        this->_possitive = o._possitive;
      } else if (o._inf && (this->_possitive == o._possitive)) { // (+ * + = -) and (- * - = +)
        this->_possitive = !this->_possitive;
      } else {
        this->_value *= o._value;
      }
      return *this;
    }

    EIRational& operator--() noexcept {
      this->_value -= boost::rational<int>(1);
      return *this;
    }

    EIRational& operator++() noexcept {
      this->_value += boost::rational<int>(1);
      return *this;
    }

    string naturalDisplay() {
      if (this->_inf) {
        if (this->_possitive)
          return "inf";
        else
          return "-inf";
      }
      
      return to_string(_value.numerator()) + "/" + to_string(_value.denominator());  
    }
};

inline EIRational operator+(const EIRational lhs, const EIRational& rhs) noexcept {
  EIRational res = lhs;
  res += rhs;
  return res;
}

inline EIRational operator-(const EIRational lhs, const EIRational& rhs) noexcept {
  EIRational res = lhs;
  res -= rhs;
  return res;
}

inline EIRational operator/(const EIRational lhs, const EIRational& rhs) noexcept {
  EIRational res = lhs;
  res /= rhs; 
  return res;
}

inline bool operator==(const EIRational& lhs, const EIRational& rhs) noexcept {

  if (lhs._inf && rhs._inf) return (lhs._possitive == rhs._possitive);
  else if (lhs._inf || rhs._inf) return false;
  return (lhs._value == rhs._value);
}

inline bool operator!=(const EIRational& lhs, const EIRational& rhs) noexcept {
  return !operator==(lhs,rhs);
}

inline bool operator<(const EIRational& lhs, const EIRational& rhs) noexcept {
  if (lhs._inf && lhs._possitive) return false;
  else if (lhs._inf && !lhs._possitive) return !(rhs._inf && !rhs._possitive);
  else if (rhs._inf && rhs._possitive) return true;
  else if (rhs._inf) return false;
  return (lhs._value < rhs._value);
}

inline bool operator>(const EIRational& lhs, const EIRational& rhs) noexcept {
  return  operator< (rhs,lhs);
}

inline bool operator<=(const EIRational& lhs, const EIRational& rhs) noexcept {
  return !operator> (lhs,rhs);
}

inline bool operator>=(const EIRational& lhs, const EIRational& rhs) noexcept {
  return !operator< (lhs,rhs);
}

inline std::ostream& operator<<(std::ostream& os, const EIRational& t) noexcept {
    
  if (t._inf) {
    if (t._possitive)
      os << "inf";
    else
      os << "-inf";
  } else {
    os << t._value;
  } 
  return os;
}

inline std::istream& operator>>std::istream& is, EIRational& rhs) noexcept {
  string a;
  int n,d;
  is >> a;
  if (a == "inf") rhs = EIRational::infinity();
  else if (a == "-inf") = EIRational::minusInfinity();
  else {
    n = std::stoi(a.substr(0, a.find_last_of("/")));
    d = std::stoi(a.substr(a.find_last_of("/")+1));
    rhs = EIRational(n,d);
  }
  return is;
}


  //TODO: Chack this specialization
  // Specialize numeric_limits
namespace std {
  template<>
  class numeric_limits<EIRational>{
  public:
    static constexpr bool is_specialized = true;
    static EIRational min() noexcept { return EIRational(-1,1) * EIRational{numeric_limits<int>::max(), numeric_limits<int>::min()}; }
    static EIRational max() noexcept { return EIRational{numeric_limits<int>::max(), numeric_limits<int>::min()}; }
    static EIRational lowest() noexcept { return EIRational(-1,1) * EIRational{numeric_limits<int>::max(), numeric_limits<int>::min()}; }

    static constexpr bool is_signed = true;
    static constexpr bool is_integer = false;
    static constexpr bool is_exact = true;
    static EIRational epsilon() noexcept { return EIRational{1,1} - EIRational{numeric_limits<int>::max(), numeric_limits<int>::max() - 1}; }
    static EIRational round_error() noexcept { return EIRational(0); }

    static constexpr int  min_exponent = numeric_limits<int>::min(); // trash_value
    static constexpr int  min_exponent10 = min_exponent/radix; // trash_value
    static constexpr int  max_exponent = numeric_limits<int>::max(); // trash_value
    static constexpr int  max_exponent10 = max_exponent/radix; // trash_value

    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr float_denorm_style has_denorm = denorm_indeterminate;
    static constexpr bool has_denorm_loss = false;
    static EIRational infinity() noexcept { return EIRational::infinity(); }

    static constexpr bool is_iec559 = false;
    static constexpr bool is_bounded = false;
    static constexpr bool is_modulo = false;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before = false;
  };
}

#endif // EIRATIONAL_HPP