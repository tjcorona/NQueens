#include "NQDisplay.hh"

#include <iostream>

void PrintBoard(unsigned int n,const NQSolution& s)
{
  NQSolution solution = s;
  std::sort(solution.begin(),solution.end(),GreaterPositionSort);

  for (unsigned int i=0;i<n;i++)
  {
    std::cout<<std::endl<<" ---";
    for (unsigned int j=0;j<n-1;j++)
      std::cout<<" ---";
    std::cout<<std::endl<<"|";
    for (unsigned int j=0;j<n;j++)
    {
      std::cout<<" ";
      if (!solution.empty())
      {
	if (i == solution.back().first &&
	    j == solution.back().second)
	{
	  std::cout<<"Q";
	  solution.pop_back();
	}
	else
	  std::cout<<" ";
      }
      else
	std::cout<<" ";
      std::cout<<" |";
    }
  }
  std::cout<<std::endl<<" ---";
  for (unsigned int j=0;j<n-1;j++)
    std::cout<<" ---";
  std::cout<<std::endl;
}

void PrintBoard(unsigned int n)
{
  NQSolution null;
  return PrintBoard(n,null);
}

