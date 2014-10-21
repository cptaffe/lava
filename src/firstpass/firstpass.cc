// Define first pass

#ifndef LAVA_FIRSTPASS_FIRSTPASS_H
#define LAVA_FIRSTPASS_FIRSTPASS_H

#include <iostream>
#include "firstpass.h"
#include "types/types.h"
#include "err/err.h"
#include "keywords/keywords.h"

namespace lava {

FirstPass::FirstPass() {
    symtable = new std::unordered_map<std::string, std::future<ObjTree *> >();
}

FirstPass::~FirstPass() {
    for (auto it = symtable->begin(); it != symtable->end(); it++) {
        delete &it->first;
        delete &it->second;
    }
    delete symtable;
}

ObjTree *FirstPass::Pass(ObjTree *obj) {
    obj = DefTraverse(obj);
    return obj;
}

// builds hash table from def'd ids, mitigating side effects of def.
ObjTree *FirstPass::DefTraverse(ObjTree *obj) {
    if (obj->self != NULL && obj->self->type == TYPE_ID && obj->self->str->compare(KEYWORD_DEF) == 0) {
        // type checking
        if (obj->children->size() > 1) {
            if (obj->children->at(0)->self->type == TYPE_ID) {
                // Add tree as arg to async
                if (!symtable->count(std::string(*obj->children->at(0)->self->str))) {
                    symtable->insert(std::make_pair<std::string, std::future<ObjTree *> >(std::string(*obj->children->at(0)->self->str), std::future<ObjTree *>(std::async(std::launch::async, [](ObjTree* obj){
                      // lambda function
                      std::cout << *obj << std::endl;
                      return obj;
                    }, obj))));
                    return obj->children->at(0);
                } else {
                    // memory management...
                    delete obj->self;
                    ObjTree *ret = obj->children->at(0);
                    for (std::vector<ObjTree *>::iterator it = obj->children->begin() + 1; it != obj->children->end(); it++) {
                      delete *it;
                    }
                    delete obj->children;
                    return ret;
                }
            } else {
                err << "'def': must have id literal, found '" << *obj->children->at(0) << "'" << "\n";
                return obj;
            }
        } else {
            err << "'def': nothing to define" << "\n";
            return obj;
        }
    }
    if (obj->children->size() != 0) {
        for (std::vector<ObjTree *>::iterator it = obj->children->begin(); it != obj->children->end(); it++) {
          *it = DefTraverse(*it);
        }
    }
    return obj;
}

}

#endif // LAVA_FIRSTPASS_FIRSTPASS_H
