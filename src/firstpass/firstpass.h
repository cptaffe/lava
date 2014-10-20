// First pass optimizer
// Consolidates references

#ifndef LAVA_FIRSTPASS_FIRSTPASS_H_
#define LAVA_FIRSTPASS_FIRSTPASS_H_

#include <unordered_map>
#include <future>
#include "types/types.h"

namespace lava {

class FirstPass {
    // Hash Map provides best case O(1) lookup, futures provide convenient concurrent execution.
    std::unordered_map<std::string, std::future<ObjTree *> > *symtable;

    // TODO: implement lazy-evaluation dependency graph for each def.
    // TODO: implement topological sorting for this graph.
    // TODO: implement implement compiling of functions to llvm ir before running,
    // i.e. defs are always in compiler space. This is done by condensing the function to
    // the least dependant implementation.

public:
    FirstPass();
    ~FirstPass();
    ObjTree *Pass(ObjTree *);
private:
    ObjTree *DefTraverse(ObjTree *);
};

}

#endif // LAVA_FIRSTPASS_FIRSTPASS_H_
