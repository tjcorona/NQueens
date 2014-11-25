#include <getopt.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "NQTypeDefs.hh"
#include "NQDisplay.hh"
#include "NQSymmetryFilter.hh"

#include "NQBackTrackingSolver.hh"
#include "NQDLXSolver.hh"

int main(int argc, char** argv)
{
  std::string usage =
    "\n"
    "Usage: NQueens <options>\n"
    "\n"
    "This program solves the N Queens puzzle.\n"
    "\n"
    "\tAvailable options:\n"
    "\t -h, --help              (shows this message and exits)\n"
    "\t -s, --board-size        (set the size of the board)\n"
    "\t -x, --dancing-links     (bool; use dancing links method)\n"
    "\t -d, --display-solutions (bool; use ASCII to display solutions)\n"
    "\t -t, --time-solutions    (bool; time the solution search)\n"
    "\t -f, --filter-solutions  (bool; filter solutions to remove symmetries)\n"
    ;

  unsigned int boardSize = 8;
  bool use_dancing_links = false;
  bool time_solutions = false;
  bool filter_solutions = false;
  bool display_solutions = false;

  static struct option longOptions[] = {
    {"help", no_argument, 0, 'h'},
    {"board-size", required_argument, 0, 's'},
    {"dancing-links", no_argument, 0, 'x'},
    {"display-solutions", no_argument, 0, 'd'},
    {"time-solutions", no_argument, 0, 't'},
    {"filter-solutions", no_argument, 0, 'f'},
  };

  static const char *optString = "hs:xdtdf";

  while(1) {
    char optId = getopt_long(argc, argv,optString, longOptions, NULL);
    if(optId == -1) break;
    switch(optId) {
    case('h'): // help
      std::cout<<usage<<std::endl;
      return 0;
    case('s'):
      boardSize = atoi(optarg);
      break;
    case('x'):
      use_dancing_links = true;
      break;
    case('d'):
       display_solutions = true;
      break;
    case('t'):
      time_solutions = true;
      break;
    case('f'):
      filter_solutions = true;
      break;
    default: // unrecognized option
      std::cout<<usage<<std::endl;
      return 1;
    }
  }

  double time_s = -1.;
  
  std::cout<<"solving for board size "<<boardSize<<std::endl;

  NQSolutionSet solutions;

  NQSolver* solver;

  clock_t start = clock();
  if (use_dancing_links)
  {
    solver = new NQDLXSolver();
    solver->FindSolutions(solutions,boardSize);
  }
  else
  {
    solver = new NQBackTrackingSolver();
    solver->FindSolutions(solutions,boardSize);
  }
  clock_t stop = clock();
  time_s = ((double)(stop - start))/CLOCKS_PER_SEC;

  std::cout<<"There are "<<solutions.size()<<" total solutions"<<std::endl;

  if (time_solutions)
    std::cout<<"solutions found in "<<time_s<<" seconds"<<std::endl;
    
  if (filter_solutions)
  {
    RemoveSymmetries(boardSize,solutions);
    std::cout<<"There are "<<solutions.size()<<" unique solutions"<<std::endl;
  }

  if (display_solutions)
  {
    for (unsigned int i=0;i<solutions.size();i++)
    {
      PrintBoard(boardSize,solutions[i]);
      std::cout<<""<<std::endl;
    }
  }

  delete solver;
  
  return 0;
}
