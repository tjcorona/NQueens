#ifndef NQSOLVER_HH
#define NQSOLVER_HH

#include "NQTypeDefs.hh"

class NQSolver
{
public:
  virtual ~NQSolver() {}

  virtual void FindSolutions(NQSolutionSet& solutionSet,
			     unsigned int boardSize) = 0;
};

#endif /* NQSOLVER_HH */
