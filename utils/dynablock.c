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
int MIN = 1;

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
      if(spaces[i].y < tmp[i].y) {
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


void updateIndex(int x, int y, int w, int opt) {
  int isU = 0;
  for(int i=0;i<numOfSpace;i++) {
    if(spaces[i].y <= y-opt) {
      if(spaces[i].y == y) {
        isU = 1;
      }
      if(spaces[i].x <= x) {
        if(x+w <(spaces[i].x+spaces[i].w)) {
          //printf("s1\r\n");
          //   aa
          //  bbbb   -> d  b
          spaces[i].x = x+w;
          spaces[i].w = spaces[i].w-w;
          if(x-spaces[i].x > MIN){
            spaces[numOfSpace].x = spaces[i].x;
            spaces[numOfSpace].y = spaces[i].y;
            spaces[numOfSpace].w = x-spaces[i].x;
            spaces[numOfSpace].h = dyHeight-y;
            numOfSpace++;
          }
        } else {
          //printf("s2\r\n");
          //   aa
          //  bb    ->  b
          spaces[i].w = x-spaces[i].x;
        }
      } else {
        if((spaces[i].x+spaces[i].w)< (x+w)) {
          //printf("s3\r\n");
          //  aaaa
          //   bb     ->  0
          spaces[i].x = spaces[i].y = spaces[i].w = spaces[i].h = 0;
        } else {
          //printf("s4\r\n");
          //  aa
          //   bb   --> b
          spaces[i].x = x+w;
        }
      }
    } else {
      isU = 1;
    }
  }
  if(isU == 0) {
    printf("u1\r\n");
    spaces[numOfSpace].x = x;
    spaces[numOfSpace].y = y;
    spaces[numOfSpace].w = dyWidth;
    spaces[numOfSpace].h = dyHeight-y;
    numOfSpace++;
  }
}

void updateIndexBox(Block *b) {
  updateIndex(b->x, b->y, b->w, 0);
  updateIndex(b->x, b->y+b->h, b->w, 1);
}

void showDyBlock() {
  for(int i=0;i<numOfSpace;i++) {
    printf(">> %d %d %d %d\r\n",
      spaces[i].x,
      spaces[i].y,
      spaces[i].w,
      spaces[i].h);
  }
  printf("\r\n");
}

int main(int argc, char** argv) {
  printf("hello world!!\r\n");
  initDySpace();
  Block out;
  int ret;
  ret = findSpace(45,45, &out);
  updateIndexBox(&out);
  printf("xywh : %d %d %d %d \r\n", out.x, out.y, out.w, out.h);
  printf("r : %d \r\n\r\n", ret);
  showDyBlock();

  //
  //
  ret = findSpace(45,45, &out);
  updateIndexBox(&out);

  printf("xywh : %d %d %d %d \r\n", out.x, out.y, out.w, out.h);
  printf("r : %d \r\n\r\n", ret);
  showDyBlock();


  //
  ret = findSpace(45,45, &out);
  updateIndexBox(&out);
  printf("xywh : %d %d %d %d \r\n", out.x, out.y, out.w, out.h);
  printf("r : %d \r\n\r\n", ret);
  showDyBlock();

  return 0;
}
