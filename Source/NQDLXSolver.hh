#ifndef NQDLXSOLVER_HH
#define NQDLXSOLVER_HH

#include "NQSolver.hh"

class NQDLXSolver : public NQSolver
{
public:
  virtual ~NQDLXSolver() {}

  void FindSolutions(NQSolutionSet& solutionSet, unsigned int boardSize);

private:

  class Header;

  class Node
  {
  public:
    Node(NQPosition position) : fLeft(NULL),
				fRight(NULL),
				fUp(NULL),
				fDown(NULL),
				fHeader(NULL),
				fPosition(position) {}

    void L(Node* n) { fLeft = n; }
    void R(Node* n) { fRight = n; }
    void U(Node* n) { fUp = n; }
    void D(Node* n) { fDown = n; }
    void C(Header* h) { fHeader = h; }

    Node* L() { return fLeft; }
    Node* R() { return fRight; }
    Node* U() { return fUp; }
    Node* D() { return fDown; }
    Header* C() { return fHeader; }
    NQPosition& Position() { return fPosition; }

  private:
    Node* fLeft;
    Node* fRight;
    Node* fUp;
    Node* fDown;
    Header* fHeader;
    NQPosition fPosition;
  };

  class Header : public Node
  {
  public:
    Header(NQPosition position) : Node(position),
				  fSize(0) { C(this); }

    size_t S() { return fSize; }

    void Inc() { fSize++; }
    void Dec() { fSize--; }

  private:
    size_t fSize;
};

  void DeleteNodes(Header* root);
  
  void StoreSolution(std::vector<Node*>& solution, NQSolutionSet& ss);

  Header* ChooseColumn(Header* root);

  void CoverColumn(Header* c);

  void UncoverColumn(Header* c);

  void Search(Header* root, std::vector<Node*>& solution, NQSolutionSet& ss, size_t k=0);

  class BinaryForm
  {
  public:
    BinaryForm(unsigned i=8) : fBoardDimension(i) {}

    bool operator()(unsigned i,unsigned j) const;

    unsigned ColumnRank() const { return 6*fBoardDimension - 6; }
    unsigned RowRank() const { return fBoardDimension*fBoardDimension; }

  private:
    unsigned PlusDiagonal(unsigned i,unsigned j) const;
    unsigned MinusDiagonal(unsigned i,unsigned j) const;

    unsigned fBoardDimension;
  };
  
  Header* PopulateFromBinaryMatrix(size_t dim);
};


#endif /* NQDLX_HH */
