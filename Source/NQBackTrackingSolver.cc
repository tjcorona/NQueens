#include "NQBackTrackingSolver.hh"

#include <cstdlib>
#include <iostream>

void NQBackTrackingSolver::FindSolutions(NQSolutionSet& solutionSet,unsigned int boardSize)
{
  NQSolution s;
  BackTrackingSearchRecursive(s,0,0,boardSize,solutionSet);
  return;
}

bool NQBackTrackingSolver::Collision(const NQSolution& s,const NQPosition& p)
{
  for (unsigned int i=0;i<s.size();i++)
  {
    if (s[i].first == p.first ||
	s[i].second == p.second ||
	abs(s[i].first - p.first) == abs(s[i].second - p.second))
      return true;
  }

  return false;
}

void NQBackTrackingSolver::BackTrackingSearchRecursive(NQSolution& s,unsigned int i,unsigned int j,unsigned int n,NQSolutionSet& ss)
{  
  static bool exitCondition = false;

  if (s.empty() && i == 0 && j == 0)
  {
    if (!exitCondition)
      exitCondition = true;
    else
      return;
  }

  static bool firstJPass = true;

  // if we have already found our n queens, add the solution to the set and
  // continue the search
  if (i == n)
  {
    ss.push_back(s);
    unsigned int jp = s.back().second;
    s.pop_back();
    if ((jp+1)%n == 0)
      firstJPass = false;
    return BackTrackingSearchRecursive(s,i-1,(jp+1)%n,n,ss);
  }

  // if no solutions exist for the given position in row i, increment the
  // (i-1)-th position

  if (j == 0)
  {
    if (firstJPass)
      firstJPass = false;
    else
    {
      unsigned int jp = s.back().second;
      s.pop_back();
      return BackTrackingSearchRecursive(s,i-1,(jp+1)%n,n,ss);
    }
  }
  else
    firstJPass = false;

  // try adding position i,j
  NQPosition p(i,j);

  if (Collision(s,p))
    return BackTrackingSearchRecursive(s,i,(j+1)%n,n,ss);
  else
  {
    s.push_back(p);
    firstJPass = true;
    return BackTrackingSearchRecursive(s,i+1,0,n,ss);
  }
}
