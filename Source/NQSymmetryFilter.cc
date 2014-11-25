#include "NQSymmetryFilter.hh"

NQSolution FlipX(const NQSolution& s, unsigned int n)
{
  NQSolution flippedSolution;
  for (unsigned int i = 0; i<s.size();i++)
  {
    flippedSolution.push_back(NQPosition(n - s[i].first - 1,s[i].second));
  }
  std::sort(flippedSolution.begin(),flippedSolution.end(),LesserPositionSort);
  return flippedSolution;
}

NQSolution FlipY(const NQSolution& s, unsigned int n)
{
  NQSolution flippedSolution;
  for (unsigned int i = 0; i<s.size();i++)
  {
    flippedSolution.push_back(NQPosition(s[i].first,n - s[i].second - 1));
  }
  std::sort(flippedSolution.begin(),flippedSolution.end(),LesserPositionSort);
  return flippedSolution;
}

NQSolution Rotate90(const NQSolution& s, unsigned int n)
{
  NQSolution rotatedSolution;

  for (unsigned int i = 0; i<s.size();i++)
  {
    rotatedSolution.push_back(NQPosition(n - s[i].second - 1,s[i].first));
  }
  std::sort(rotatedSolution.begin(),rotatedSolution.end(),LesserPositionSort);
  return rotatedSolution;
}

NQSolution Rotate180(const NQSolution& s, unsigned int n)
{
  NQSolution rotatedSolution;

  for (unsigned int i = 0; i<s.size();i++)
  {
    rotatedSolution.push_back(NQPosition(n - s[i].first - 1,n - s[i].second - 1));
  }
  std::sort(rotatedSolution.begin(),rotatedSolution.end(),LesserPositionSort);
  return rotatedSolution;
}

NQSolution Rotate270(const NQSolution& s, unsigned int n)
{
  NQSolution rotatedSolution;

  for (unsigned int i = 0; i<s.size();i++)
  {
    rotatedSolution.push_back(NQPosition(s[i].second,n - s[i].first - 1));
  }
  std::sort(rotatedSolution.begin(),rotatedSolution.end(),LesserPositionSort);
  return rotatedSolution;
}

void RemoveSymmetries(unsigned int n,NQSolutionSet& ss)
{
  NQSolutionSet noDuplicates;

  std::vector<bool> d(ss.size(),false);

  for (unsigned int i=0;i<ss.size();i++)
  {
    if (d[i]) continue;
    noDuplicates.push_back(ss[i]);

    NQSolutionSet symmetries;

    symmetries.push_back(FlipX(ss[i],n));
    symmetries.push_back(FlipY(ss[i],n));
    symmetries.push_back(Rotate90(ss[i],n));
    symmetries.push_back(Rotate180(ss[i],n));
    symmetries.push_back(Rotate270(ss[i],n));

    for (unsigned int j=i+1;j<ss.size();j++)
    {
      if (d[j])
	continue;
      for (unsigned int k=0;k<symmetries.size();k++)
      {
	if (ss[j] == symmetries[k])
	{
	  d[j] = true;
	  break;
	}
      }
    }
  }

  ss = noDuplicates;
}
