#include <GL/glut.h>
#include"../config.h"
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500
#define maxSize 1000
/*  paint */
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
double dx, dy;
double lastMouseX, lastMouseY;
int width, height,imageWidth, imageHeight;
unsigned char leftMouseDown;
unsigned char rightMouseDown;
//png_bytep *row_pointers;
unsigned char **row_pointers;
int rendererInit(int argc, char** argv);
void displayMe(void);
void reshape(int w, int h);
void setImage(unsigned char **row, int w, int h);
void mouse(int button, int state,int x, int y);// UP, DOWN buttons
void motion(int x, int y);