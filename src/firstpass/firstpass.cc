// Define first pass

#ifndef LAVA_FIRSTPASS_FIRSTPASS_H
#define LAVA_FIRSTPASS_FIRSTPASS_H

#include "firstpass.h"
#include "lava.h"

namespace lava {

// FirstPass is built with a tree
// It expects the tree to expand via the root.
FirstPass::FirstPass(ObjTree *obj) {
  children = obj->children;
  index = 0;
}

void FirstPass::Pass(ObjTree *obj) {
  if (obj->self != NULL) {
    if (obj->self->type == TYPE_ID) {
      Err((char *) "undefined '%s'", obj->self->str);
    }
  }
  if (!obj->children->empty()) {
    for (std::vector<ObjTree *>::iterator it = obj->children->begin(); it != obj->children->end(); it++) {
      Pass(*it);
    }
  }
}

// check for
void FirstPass::Pass() {
  if (!children->empty() && children->size() > index) {
    std::vector<ObjTree *>::iterator it = children->begin();
    Pass(*(it + index++));
  }
}

}

#endif // LAVA_FIRSTPASS_FIRSTPASS_H
