#ifndef NQSYMMETRYFILTER_HH
#define NQSYMMETRYFILTER_HH

#include "NQTypeDefs.hh"

NQSolution FlipX(const NQSolution& s, unsigned int n);

NQSolution FlipY(const NQSolution& s, unsigned int n);

NQSolution Rotate90(const NQSolution& s, unsigned int n);

NQSolution Rotate180(const NQSolution& s, unsigned int n);

NQSolution Rotate270(const NQSolution& s, unsigned int n);

void RemoveSymmetries(unsigned int n,NQSolutionSet& ss);

#endif /* NQSYMMETRYFILTER_HH */
