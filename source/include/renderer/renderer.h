#include <GL/glut.h>
#include"../config.h"
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500
#define maxSize 1000

#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
enum MOUSE_STATE
{
	LEFT_MOUSE_DOWN = 0,
	LEFT_MOUSE_UP,
	RIHGT_MOUSE_DOWN,
	RIHGT_MOUSE_UP,
	MOUSE_LAST
};
#endif

struct point
{
	int x;
	int y;
	char isUsed;
};
typedef struct point point;
#ifdef CONFIG_PAINT_MODE
point array[maxSize];
int currentSize;
int current;
#endif
#ifdef CONFIG_MOUSE_SCROLL_MODE
double k;
#define coef 1.1f
#endif
#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
void (*mouse_callback) (int x, int y, int state) = NULL;
int setMouseCallback(void (*func)(int,int,int));
#endif
double dx, dy;
double lastMouseX, lastMouseY;
int width, height,imageWidth, imageHeight;
unsigned char leftMouseDown;
unsigned char rightMouseDown;
//png_bytep *row_pointers;
unsigned char **row_pointers;
int rendererInit(int argc, char** argv);
void setImage(unsigned char **row, int w, int h);