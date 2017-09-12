#include "cdynablock.h"
#include <stdio.h>

void _freeCDynaBlock(void* obj) {
  CObject* objObj = (CObject*)obj;
  CDynaBlock* dynObj = (CDynaBlock*)obj;
  if(dynObj->spaces != NULL) {
    CMemory *cmemory = cobject_getCMemory((CObject*)obj);
    cmemory_free(cmemory, dynObj->spaces);
  }
  freeCObject(obj);
}

CDynaBlock* newCDynaBlock(CMemory* cmemory) {
  CDynaBlock* ret = cmemory_calloc(cmemory, 1, sizeof(CDynaBlock));
  ret->parent.cmemory = cmemory;
  ret->parent.funcFree = _freeCDynaBlock;
  return ret;
}

CDynaBlock* initCDynaBlock(CDynaBlock* obj, int w, int h) {
  CMemory *cmemory = cobject_getCMemory((CObject*)obj);
  initCObject((CObject*)obj, CDYNABLOCK_NAME);
  obj->width = w;
  obj->height = h;
  obj->maxOfSpace = 100;
  obj->numOfSpace = 0;
  obj->spaces = (CDynaBlockSpace*)cmemory_calloc(cmemory, 1, sizeof(CDynaBlockSpace)*obj->maxOfSpace);
  obj->MIN = 1;
  //
  //
  obj->spaces[0].x = 0;
  obj->spaces[0].y = 0;
  obj->spaces[0].w = w;
  obj->spaces[0].h = h;
  obj->numOfSpace = 1;
  return obj;
}

CDynaBlock* createCDynaBlock(int w, int h) {
  return initCDynaBlock(newCDynaBlock(getCMemory()), w, h);
}

int cdynaBlock_findSpace(CDynaBlock* obj, int w, int h, CDynaBlockSpace *out) {
  CDynaBlockSpace* tmp = NULL;
  for(int i=0;i<obj->numOfSpace;i++) {
    if(obj->spaces[i].w >= w && obj->spaces[i].h >= h) {
      if(tmp == NULL) {
        tmp = &obj->spaces[i];
      }
      if(obj->spaces[i].y < tmp[i].y) {
        tmp = &obj->spaces[i];
      }
    }
  }
  if(tmp != NULL) {
    out->x = tmp->x;
    out->y = tmp->y;
    out->w = w;
    out->h = h;
    return 1;
  } else {
    return 0;
  }
}

void cdynaBlock_updateIndexInner(CDynaBlock* obj, int x, int y, int w, int opt);
void cdynaBlock_updateIndex(CDynaBlock* obj, CDynaBlockSpace *block){
  cdynaBlock_updateIndexInner(obj, block->x, block->y         , block->w, 0);
  cdynaBlock_updateIndexInner(obj, block->x, block->y+block->h, block->w, 1);
}

void cdynaBlock_updateIndexInner(CDynaBlock* obj, int x, int y, int w, int opt) {
  int isU = 0;
  for(int i=0;i<obj->numOfSpace;i++) {
    if(obj->spaces[i].y >= y) {
      isU = 1;
    }
    if(obj->spaces[i].w < w ) {
      continue;
    }
    if(obj->spaces[i].y <= y-opt) {

      if(obj->spaces[i].x <= x) {
        if(x+w <(obj->spaces[i].x+obj->spaces[i].w)) {
          //printf("s1 %d\r\n",i);
          //   aa
          //  bbbb   -> d  b
          obj->spaces[i].x = x+w;
          obj->spaces[i].w = obj->spaces[i].w-w;
          if(x-obj->spaces[i].x > obj->MIN){
            obj->spaces[obj->numOfSpace].x = obj->spaces[i].x;
            obj->spaces[obj->numOfSpace].y = obj->spaces[i].y;
            obj->spaces[obj->numOfSpace].w = x-obj->spaces[i].x;
            obj->spaces[obj->numOfSpace].h = obj->height-y;
            obj->numOfSpace++;
          }
        } else {
          //printf("s2 %d\r\n",i);
          if((obj->spaces[i].x+obj->spaces[i].w) > x ) {
            //   aa
            //  bb    ->  b
            obj->spaces[i].w = x-obj->spaces[i].x;
          } else {
            //     aa
            //  bb
          }
        }
      } else {
        if((obj->spaces[i].x+obj->spaces[i].w)< (x+w)) {
          //printf("s3 %d\r\n",i);
          //  aaaa
          //   bb     ->  0
          obj->spaces[i].x = obj->spaces[i].y = obj->spaces[i].w = obj->spaces[i].h = 0;
        } else {
          //printf("s4 %d %d\r\n",i, x+w);
          if((obj->spaces[i].x) > x+w ) {
            //  aa
            //   bb   --> b
            obj->spaces[i].x = x+w;
          } else {
            //  aa
            //     bb   -->
          }
        }
      }
    }
  }
  if(isU == 0) {
    //printf("u1\r\n");
    obj->spaces[obj->numOfSpace].x = x;
    obj->spaces[obj->numOfSpace].y = y;
    obj->spaces[obj->numOfSpace].w = obj->width;
    obj->spaces[obj->numOfSpace].h = obj->height-y;
    obj->numOfSpace++;
  }
}
