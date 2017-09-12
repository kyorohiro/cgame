#ifndef _H_CDYNABLOCK_
#define _H_CDYNABLOCK_
//typedef int (*free)(int n);

#include "core/cmemory.h"
#include "core/cobject.h"

#define CDYNABLOCK_NAME "dyn"

typedef struct {
    int x;
    int y;
    int h;
    int w;
} CDynaBlockSpace;


// UTF8
typedef struct {
  CObject parent;
  int width;
  int height;

  int maxOfSpace;
  int numOfSpace;
  CDynaBlockSpace* spaces;
  int MIN;
} CDynaBlock;

CDynaBlock* newCDynaBlock(CMemory*);
CDynaBlock* initCDynaBlock(CDynaBlock* obj, int w, int h);
CDynaBlock* createCDynaBlock(int w, int h);

int cdynaBlock_findSpace(CDynaBlock* obj, int w, int h, CDynaBlockSpace *out);
void cdynaBlock_updateIndex(CDynaBlock* obj, CDynaBlockSpace *block);
void cdynaBlock_show(CDynaBlock* obj);
void cdynaBlock_resetIndex(CDynaBlock* obj);
void cdynaBlock_clearIndexCache(CDynaBlock* obj);
void cdynaBlock_expandIndexCache(CDynaBlock* obj);
#endif
