#ifndef NQTYPEDEFS_HH
#define NQTYPEDEFS_HH

#include <utility>
#include <vector>

typedef std::pair<short,short> NQPosition;
typedef std::vector<NQPosition> NQSolution;
typedef std::vector<NQSolution> NQSolutionSet;

bool LesserPositionSort(const NQPosition& left,const NQPosition& right);

bool GreaterPositionSort(const NQPosition& left,const NQPosition& right);

#endif /* NQTYPEDEFS_HH */
