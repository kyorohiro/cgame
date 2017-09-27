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
    //if(obj->spaces[i].w < w ) {
    //  continue;
    //}
    if(obj->spaces[i].y <= y-opt) {

      if(obj->spaces[i].x <= x) {
        if(x+w <(obj->spaces[i].x+obj->spaces[i].w)) {
          //printf("s1 a %d\r\n",i);
          //   aa
          //  bbbb   -> d  b
          int sx = obj->spaces[i].x;
          int sy = obj->spaces[i].y;
          int sw = obj->spaces[i].w;
          obj->spaces[i].x = x+w;
          obj->spaces[i].w = sw-(x+w-sx);
          if(x-sx > obj->MIN){
            //printf("s1 b %d\r\n",i);
            if(obj->numOfSpace+2 >= obj->maxOfSpace) {
              cdynaBlock_expandIndexCache(obj);
            }
            obj->spaces[obj->numOfSpace].x = sx;
            obj->spaces[obj->numOfSpace].y = sy;
            obj->spaces[obj->numOfSpace].w = x-sx;
            obj->spaces[obj->numOfSpace].h = obj->height-sy;
            obj->numOfSpace++;
          }
        } else {
          if((obj->spaces[i].x+obj->spaces[i].w) > x ) {
            //printf("s2 a %d\r\n",i);
            //   aa
            //  bb    ->  b
            obj->spaces[i].w = x-obj->spaces[i].x;
          } else {
            //printf("s2 b %d\r\n",i);
            //     aa
            //  bb
          }
        }
      } else {
        if((obj->spaces[i].x+obj->spaces[i].w)< (x+w)) {
          //printf("s3 a %d\r\n",i);
          //  aaaa
          //   bb     ->  0
          obj->spaces[i].x = obj->spaces[i].y = obj->spaces[i].w = obj->spaces[i].h = 0;
        } else {
          if((obj->spaces[i].x) < x+w ) {
            //printf("s3 b %d\r\n",i);
            //  aa
            //   bb   --> b
            int tmpX = obj->spaces[i].x;
            int tmpW = obj->spaces[i].w;
            obj->spaces[i].x = x+w;
            obj->spaces[i].w = (tmpX+tmpW) - (x+w) ;

          } else {
            //printf("s3  %d\r\n",i);
            //  aa
            //     bb   -->
          }
        }
      }
    }
  }
  if(isU == 0) {
    //printf("u1\r\n");
    if(obj->numOfSpace+2 >= obj->maxOfSpace) {
      cdynaBlock_expandIndexCache(obj);
    }
    obj->spaces[obj->numOfSpace].x = 0;
    obj->spaces[obj->numOfSpace].y = y;
    obj->spaces[obj->numOfSpace].w = obj->width;
    obj->spaces[obj->numOfSpace].h = obj->height-y;
    obj->numOfSpace++;
  }
}

void cdynaBlock_show(CDynaBlock* obj) {
  for(int i=0;i<obj->numOfSpace;i++) {
    printf(" - %d %d %d %d\r\n",
      obj->spaces[i].x,
      obj->spaces[i].y,
      obj->spaces[i].w,
      obj->spaces[i].h);
  }
  printf("\r\n");
}

void cdynaBlock_resetIndex(CDynaBlock* obj) {
  obj->numOfSpace = 0;
  obj->spaces[0].x = 0;
  obj->spaces[0].y = 0;
  obj->spaces[0].w = obj->width;
  obj->spaces[0].h = obj->height;
  obj->numOfSpace = 1;
}

void cdynaBlock_clearIndexCache(CDynaBlock* obj) {
  int j=0;
  for(int i=0;i<obj->numOfSpace;i++) {
    if(obj->spaces[i].x == 0 && obj->spaces[i].y == 0 && obj->spaces[i].w <= obj->MIN && obj->spaces[i].h <= obj->MIN) {
    } else {
      obj->spaces[j++] = obj->spaces[i];
    }
  }
  obj->numOfSpace = j;
}

void cdynaBlock_expandIndexCache(CDynaBlock* obj) {
  CMemory* cmemory = cobject_getCMemory((CObject*)obj);
  CDynaBlockSpace* next = (CDynaBlockSpace*)cmemory_calloc(cmemory, 1, sizeof(CDynaBlockSpace)*obj->maxOfSpace*2);
  for(int i=0;i<obj->numOfSpace;i++) {
      next[i] = obj->spaces[i];
  }
  obj->maxOfSpace *= 2;
  CDynaBlockSpace* tmp = obj->spaces;
  obj->spaces = next;
  cmemory_free(cmemory, tmp);
}
