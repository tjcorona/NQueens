#include "NQDLXSolver.hh"

#include <iostream>
#include <limits>

void NQDLXSolver::FindSolutions(NQSolutionSet& solutionSet,
				unsigned int boardSize)
{
  Header* root = PopulateFromBinaryMatrix(boardSize);
  std::vector<Node*> solution(boardSize,NULL);
  Search(root,solution,solutionSet);
  DeleteNodes(root);
}

void NQDLXSolver::DeleteNodes(NQDLXSolver::Header* root)
{
  Header* c = (Header*)(root->R());
  while (c != root)
  {
    Node* n = c->D();
    while (n != c)
    {
      Node* next_n = n->D();
      delete n;
      n = next_n;
    }
    Header* next_c = (Header*)(c->R());
    delete c;
    c = next_c;
  }
}

void NQDLXSolver::StoreSolution(std::vector<NQDLXSolver::Node*>& solution, NQSolutionSet& ss)
{
  NQSolution s;
  for (std::vector<Node*>::iterator it=solution.begin();it!=solution.end();++it)
    if (*it)
      s.push_back((*it)->Position());
  ss.push_back(s);
}

NQDLXSolver::Header* NQDLXSolver::ChooseColumn(NQDLXSolver::Header* root)
{
  return (Header*)(root->R());
}

void NQDLXSolver::CoverColumn(NQDLXSolver::Header* c)
{
  // Cover column c
  c->R()->L(c->L());
  c->L()->R(c->R());

  Node* i = c->D();
  while (i != c)
  {
    Node* j = i->R();
    while (j != i)
    {
      j->D()->U(j->U());
      j->U()->D(j->D());
      j->C()->Dec();

      j = j->R();
    }

    i = i->D();
  }
}

void NQDLXSolver::UncoverColumn(NQDLXSolver::Header* c)
{
  // Uncover column c
  Node* i = c->U();
  while (i != c)
  {
    Node* j = i->L();
    while (j != i)
    {
      j->C()->Inc();
      j->D()->U(j);
      j->U()->D(j);

      j = j->L();
    }

    i = i->U();
  }

  c->R()->L(c);
  c->L()->R(c);
}

void NQDLXSolver::Search(NQDLXSolver::Header* root, std::vector<NQDLXSolver::Node*>& solution, NQSolutionSet& ss, size_t k)
{
  // Dancing Links implementation

  // if (root->R() == root)
  //   return Print(solution);
  
  if (k == solution.size())
  {
    // return Print(solution);
    return StoreSolution(solution,ss);
  }
  
  // Choose a column object
  Header* c = ChooseColumn(root);

  // Cover column c
  CoverColumn(c);

  // loop over the column elments of c
  Node* r = c->D();
  while (r != c)
  {
    // try r as a solution
    solution[k] = r;

    // loop over row elements of r
    Node* j = r->R();
    while (j != r)
    {
      // cover all columns that share a row element with r
      CoverColumn(j->C());
      j = j->R();
    }

    // now that the linked list is updated to contain only the remaining
    // available positions, we try another move
    Search(root,solution,ss,k+1);
    
    // if we have returned, then either a solution was found or there were no
    // column elements on which we could pivot.  Either way, we undo the
    // selection of r as a solution and continue.

    r = solution[k];
    c = r->C();

    j = r->L();
    while (j != r)
    {
      UncoverColumn(j->C());
      j = j->L();
    }

    r = r->D();
  }

  UncoverColumn(c);
}

unsigned NQDLXSolver::BinaryForm::PlusDiagonal(unsigned i,unsigned j) const
{
  // for a queen at (i,j) (algebraic notation) returns the index of the plus
  // diagonal (or maximum unsigned for untracked diagonals)

  int offset = i - j;

  if (abs(offset) == fBoardDimension - 1)
    return std::numeric_limits<short>::max();
    
  return offset + (fBoardDimension - 2);
}

unsigned NQDLXSolver::BinaryForm::MinusDiagonal(unsigned i,unsigned j) const
{
  // for a queen at (i,j) (algebraic notation) returns the index of the minus
  // diagonal (or maximum unsigned for untracked diagonals)

  // (0,0): -3 = 0 - 3
  // (0,1) (1,0): -2 = 0 - 2 or 1 - 3
  // (0,2) (1,1) (2,0): -1
  // (0,3) (1,2) (2,1) (3,0): 0
  // (b4) (c3) (d2)
  // (c4) (d3)
  // (d4)

  int offset = i - (fBoardDimension - 1 - j);
  if (abs(offset) == fBoardDimension - 1)
    return std::numeric_limits<unsigned>::max();

  return offset + (fBoardDimension - 2);
}

bool NQDLXSolver::BinaryForm::operator()(unsigned i,unsigned j) const
{
  // Returns the value of the binary matrix form at (i,j) (index notation).

  // matrix row: per symbol, per grid location
  // matrix column: conditions:
  //   per row: symbol in row
  //   per column: symbol in column
  //   per grid diagonal: symbol in + diagonal
  //   per grid diagonal: symbol in - diagonal
  //
  // For N Queens:
  // there is 1 symbol
  // there are <dim*dim> grid locations
  // there are <dim> rows
  // there are <dim> columns
  // there are <2*dim-3> + diagonals
  // there are <2*dim-3> - diagonals
    
  unsigned row = i/fBoardDimension;
  unsigned column = i%fBoardDimension;
  unsigned plusDiagonal = PlusDiagonal(row,column);
  unsigned minusDiagonal = MinusDiagonal(row,column);

  if (j < fBoardDimension)
  {
    // we are querying the matrix columns corresponding to the row condition:
    return (row == j);
  }
  
  j -= fBoardDimension;
  
  if (j < fBoardDimension)
  {
    // we are querying the matrix columns corresponding to the column condition:
    return (column == j);
  }
  
  j -= fBoardDimension;

  if (j < 2*fBoardDimension-3)
  {
    // we are querying the matrix columns corresponding to the + diagonal
    // condition:
    return (plusDiagonal == j);
  }

  j -= 2*fBoardDimension-3;

  // we are querying the matrix columns corresponding to the - diagonal
  // condition:

  return (minusDiagonal == j);
}

NQDLXSolver::Header* NQDLXSolver::PopulateFromBinaryMatrix(size_t dim)
{
  // Construct the toroidal map

  // first, create the binary matrix for a <dim x dim> board
  BinaryForm m(dim);

  // construct the root header
  Header* root = new Header(std::make_pair(-1,-1));

  // construct the colum headers
  Node* last = root;
  for (unsigned i=0;i<m.ColumnRank();i++)
  {
    Header* c = new Header(std::make_pair(-1,i));
    last->R(c);
    c->L(last);
    c->R(root);
    root->L(c);

    last = c;
  }

  // fill the columns, one row at a time
  Header* c = root;
  Header** headers = new Header*[m.ColumnRank()];
  Node** previousInColumn = new Node*[m.ColumnRank()];
  for (unsigned i=0;i<m.ColumnRank();i++)
  {
    previousInColumn[i] = headers[i] = c = (Header*)(c->R());
  }

  for (unsigned i=0;i<m.RowRank();i++)
  {
    Node* firstInRow = NULL;
    Node* previousInRow = NULL;

    for (unsigned j=0;j<m.ColumnRank();j++)
    {
      if (m(i,j))
      {
	unsigned row = i/dim;
	unsigned column = i%dim;

	Node* n = new Node(std::make_pair(row,column));
	n->C(headers[j]);
	root->Inc();
	headers[j]->Inc();

	if (!firstInRow)
	  firstInRow = previousInRow = n;

	n->U(previousInColumn[j]);
	previousInColumn[j]->D(n);
	n->D(headers[j]);
	headers[j]->U(n);

	n->L(previousInRow);
	previousInRow->R(n);
	n->R(firstInRow);
	firstInRow->L(n);

	previousInColumn[j] = n;
	previousInRow = n;
      }
    }
  }

  delete [] headers;
  delete [] previousInColumn;

  return root;
}
