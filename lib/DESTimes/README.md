# DESTimes Discrete Event Simulation Times
This repository contains two time classes to work with in Discrete Event Simulation (DES).

### Licence
This software is under the GNU - v3 licence:

### author
Laouen Mayal Louan Belloli

### Dependencies:
 - [c++11]  >=
 - [gcc]
 - [Boost 1.57] >=

### EIRational (Extended Infinity Rational): 
Is an extension of boost_rational\<int\> that allows using infinity.

### NDTime (Natural Deep Time):
Allows to work with the international standar time format hh:mm:ss:mmss and it also allows to work with smaller time units as: 
* microseconds 
* nanoseconds
* picoseconds
* femtoseconds

This time units are the smaller mesurable units in phisics

## Available constructors

```c++
1 - NDTime();
2 - NDTime(const NDTime& val);
3 - NDTime(std::initializer_list<int> val);
4 - NDTime(const string val);
```

	1 Default constructor: Initialize a new NDTime with value zero as default.
	2 Copy constructor: Initialize a new NDTime with the exact same value as the first parameter val.
	3 Natural constructor: Initialize a new NDTime with values from {hours} to {hours, ..., femtoseconds}.
	11 Parser constructor: Intializa a new NDTime parsing a string val. accepted strings are: {"inf","-inf",["hh", ..., "hh:mm:ss:mmss:mcs:nnss:ppss:ffss"]} the last format is the international standar time format extended until femtoseconds.

## Available operators

| Operator | Left type    | Right type |
|----------|--------------|------------|
| +=       | NDTime       | NDTime     |
| -=       | NDtime       | NDTim      |
| +        | NDTime       | NDTime     |
| -        | NDTime       | NDTime     |
| ==       | NDTime       | NDTime     |
| !=       | NDTime       | NDTime     |
| <        | NDTime       | NDTime     |
| >        | NDTime       | NDTime     |
| <=       | NDTime       | NDTime     |
| >=       | NDTime       | NDTime     |
| <<       | std::ostream | NDTime     |
| >>       | std::istream | NDTime     |

## Available methods

```c++
void resetToZero();

// Resets the NDTime object to zero (i.e. 00:00:00:000:000:000:000:000)
```

## static methods

```c++
static void startDeepView();

// When deep view mode is enabled calling NDTime::startDeepView() the << operator start printing all the units from hours to femtoseconds.

// line:
std::cout << NDTime({1,1,1,1,1,1,1,1}) << std::endl;
NDTime::startDeepView();
std::cout << NDTime({1,1,1,1,1,1,1,1}) << std::endl;

// output:
01:01:01:001
01:01:01:001:001:001:001:001
```

```c++
static void stopDeepView();

Stops deep view mode calling NDTime::stopDeepView()

// line:
NDTime::startDeepView();
std::cout << NDTime({1,1,1,1,1,1,1,1}) << std::endl;
NDTime::stopDeepView();
std::cout << NDTime({1,1,1,1,1,1,1,1}) << std::endl;

// output:
01:01:01:001:001:001:001:001
01:01:01:001
```

```c++
static NDTime infinity();

returns a NDTime with value possitive infinity
```

```c++
static NDTime minus_infinity();

returns a NDTime with value negative infinity
```

   [C++11]: <https://gcc.gnu.org/projects/cxx-status.html#cxx11>
   [gcc]: <https://gcc.gnu.org/>
   [Boost 1.57]: <http://www.boost.org/users/history/version_1_57_0.html>