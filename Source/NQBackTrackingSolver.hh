#ifndef NQBACKTRACKINGSOLVER_HH
#define NQBACKTRACKINGSOLVER_HH

#include "NQSolver.hh"

class NQBackTrackingSolver : public NQSolver
{
public:
  virtual ~NQBackTrackingSolver() {}

  void FindSolutions(NQSolutionSet& solutionSet, unsigned int boardSize);

private:
  bool Collision(const NQSolution& s,const NQPosition& p);

  void BackTrackingSearchRecursive(NQSolution& s,unsigned int i,unsigned int j,unsigned int n,NQSolutionSet& ss);

};

#endif /* NQBACKTRACKINGSOLVER_HH */
