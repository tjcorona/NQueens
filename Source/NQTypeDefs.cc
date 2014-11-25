#include "NQTypeDefs.hh"

#include <algorithm>

bool LesserPositionSort(const NQPosition& left,const NQPosition& right)
{
  return (left.first != right.first ?
	  left.first < right.first : left.second < right.second);
}

bool GreaterPositionSort(const NQPosition& left,const NQPosition& right)
{
  return (left.first != right.first ?
	  left.first > right.first : left.second > right.second);
}
