// First pass optimizer
// Consolidates references

#ifndef LAVA_FIRSTPASS_FIRSTPASS_H_
#define LAVA_FIRSTPASS_FIRSTPASS_H_

#include <unordered_map>
#include <future>
#include "types/types.h"

namespace lava {

class FirstPass {
    // Hash Map of id names and futures (from their evaluation)
    std::unordered_map<std::string, std::future<ObjTree *> > *symtable; // hash map
public:
    FirstPass();
    ~FirstPass();
    ObjTree *Pass(ObjTree *);
private:
    ObjTree *DefTraverse(ObjTree *);
};

}

#endif // LAVA_FIRSTPASS_FIRSTPASS_H_
