#include "cobject.h"
#include <stdlib.h>
#include <stdio.h>
#include "cmemory.h"

int _hashCode(void *obj);
int _compareTo(void *obj, void *src);
int _equals(void *obj, void *src);

CObject* newCObject(CMemory* cmemory) {
  CObject *ret = cmemory_calloc(cmemory, 1,sizeof(CObject));
  ret->cmemory = cmemory;
  ret->funcFree = freeCObject;
  return ret;
}

CObject* initCObjectRock(CObject*obj, const char *name) {
  snprintf(obj->name, sizeof(obj->name), "%s", name);
  obj->cmemory = NULL;
  obj->funcFree = NULL;
  return initCObject(obj, name);
}

CObject* initCObject(CObject*obj, const char *name) {
  snprintf(obj->name, sizeof(obj->name), "%s", name);
  obj->reference = 1;
  obj->funcHashCode = _hashCode;
  obj->funcCompareTo = _compareTo;
  obj->funcEquals = _equals;
  cobject_onMode(obj, COBJECT_MODE_FREEABLE);
  return obj;
}

CObject* createCObject() {
  return initCObject(newCObject(getCMemory()), CObject_NAME);
}

void freeCObject(void* obj) {
  if(obj != NULL && ((CObject*)obj)->cmemory != NULL) {
    cmemory_free(((CObject*)obj)->cmemory, obj);
  }
}

int _hashCode(void *obj) {
  return 0;
}

int _compareTo(void *obj, void *src) {
  if(obj == src) {
    return 0;
  }
  if(obj > src) {
    return 1;
  } else {
    return-1;
  }
}

int _equals(void *obj, void *src) {
  if(obj == src) {
    return 1;
  }
  return 0;
}

CObject* cobject_upCounter(CObject* obj) {
  if(obj == NULL) {
    return NULL;
  }
  obj->reference++;
  return obj;
}

CObject* cobject_downCounter(CObject* obj) {
  if(obj == NULL) {
    return NULL;
  }

  obj->reference--;
  return obj;
}

CObject* cobject_onMode(CObject* obj, int mode) {
  obj->mode = (obj->mode & (~mode)) | mode;
  return obj;
}

CObject* cobject_offMode(CObject* obj, int mode) {
  obj->mode = (obj->mode & (~mode));
  return obj;
}

int cobject_getMode(CObject* obj, int mode) {
  if((obj->mode & mode) != 0) {
    return 1;
  } else {
    return 0;
  }
}

int cobject_hashCode(CObject* obj) {
  CObjectFuncHashCode func = obj->funcHashCode;
  if(func != NULL) {
    return func(obj);
  }
  return 0;
}

int cobject_compareTo(CObject* obj, CObject* src) {
  CObjectFuncCompareTo func = obj->funcCompareTo;
  if(func != NULL) {
    return func(obj, src);
  }
  return 0;
}

int cobject_equals(CObject* obj, CObject* src) {
  CObjectFuncEquals func = obj->funcEquals;
  if(func != NULL) {
    return func(obj, src);
  }
  return 0;
}

CObject* _releaseCObject(CObject* obj, int isForce) {
  if(obj == NULL) {
    return obj;
  }
  obj->reference--;
  if(isForce != 0 || (obj->reference<=0 && cobject_getMode(obj, COBJECT_MODE_FREEABLE) == 1)){
    CObjectFuncFree func = obj->funcFree;
    if(func != NULL) {
      func(obj);
    }
    return NULL;
  } else {
    return obj;
  }
}

CObject* releaseForceCObject(CObject* obj) {
  return  _releaseCObject(obj, 1);
}

CObject* releaseCObject(CObject* obj) {
  return  _releaseCObject(obj, 0);
}

CMemory* cobject_getCMemory(CObject*obj) {
  if(obj->cmemory == NULL) {
    return getCMemory();
  } else {
    return obj->cmemory;
  }
}
