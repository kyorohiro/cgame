#include "cgame.h"
#include "core/cmemory.h"

CGame* newCGame(CMemory* mem) {
  CGame * ret = cmemory_calloc(mem, 1, sizeof(CGame));
  ret->parent.cmemory = mem;
  return ret;
}

CGame* initCGame(CGame* obj, char* name, char *title, int width, int height) {
  initCObject((CObject*)obj, name);
  snprintf(obj->title, sizeof(obj->title), "%s", title);
  obj->width = width;
  obj->height = height;
  return obj;
}
