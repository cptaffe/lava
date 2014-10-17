// Define first pass

#ifndef LAVA_FIRSTPASS_FIRSTPASS_H
#define LAVA_FIRSTPASS_FIRSTPASS_H

#include "firstpass.h"
#include "err/err.h"

namespace lava {

void FirstPass::Pass(ObjTree *obj) {
  if (obj == NULL) {return;}
  if (obj->self != NULL) {
    if (obj->self->type == TYPE_ID) {
      Err((char *) "undefined '%s'", obj->self->str->c_str());
    }
  }
  if (!obj->children->empty()) {
    for (std::vector<ObjTree *>::iterator it = obj->children->begin(); it != obj->children->end(); it++) {
      Pass(*it);
    }
  }
}

}

#endif // LAVA_FIRSTPASS_FIRSTPASS_H
