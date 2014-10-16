// First pass optimizer
// Consolidates references

#include "lava.h"

namespace lava {

  class FirstPass {
    std::vector<ObjTree *> *children;
    int index; // increment each time called.
  public:
    FirstPass(ObjTree *);
    void Pass();
  private:
    void Pass(ObjTree *);
  };

}
