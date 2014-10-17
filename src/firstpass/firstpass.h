// First pass optimizer
// Consolidates references

#ifndef LAVA_FIRSTPASS_FIRSTPASS_H_
#define LAVA_FIRSTPASS_FIRSTPASS_H_

#include "types/types.h"

namespace lava {

  class FirstPass {
    //std::vector<ObjTree *> *children;
    //int index; // increment each time called.
  public:
    void Pass(ObjTree *);
  };

}

#endif // LAVA_FIRSTPASS_FIRSTPASS_H_
