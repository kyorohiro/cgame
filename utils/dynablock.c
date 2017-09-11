#include<stdio.h>


typedef struct {
    int x;
    int y;
    int h;
    int w;
} Block;

typedef struct {
  int x;
  int y;
  int w;
  int h;
} DySpace;

int numOfSpace = 0;
DySpace spaces[10];
int dyWidth = 100;
int dyHeight = 100;

void initDySpace(){
  spaces[0].x = 0;
  spaces[0].y = 0;
  spaces[0].w = dyWidth;
  spaces[0].h = dyHeight;
  numOfSpace = 1;
}

int findSpace(int w, int h, Block* out) {
  DySpace* tmp = NULL;
  for(int i=0;i<numOfSpace;i++) {
    if(spaces[i].w >= w && spaces[i].h >= h) {
      if(tmp == NULL) {
        tmp = &spaces[i];
      }
      if(spaces[i].y > tmp[i].y) {
        tmp = &spaces[i];
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

void search() {

}

int main(int argc, char** argv) {
  printf("hello world!!\r\n");
  initDySpace();
  Block out;
  int ret;
  ret = findSpace(10,10, &out);
  printf("xywh : %d %d %d %d \r\n", out.x, out.y, out.w, out.h);
  printf("r : %d \r\n\r\n", ret);
  return 0;
}
