#include<renderer.h>
#include<stdio.h>

#ifdef CONFIG_PAINT_MODE
void addPointToArray(int x, int y, char use)
{
	if (currentSize < maxSize)
	{
		array[current].x = x;
		array[current].y = y;
		array[current].isUsed = use;
		current++;
		currentSize++;
	}else
	{
		if (current == maxSize)
			current = 0;
		array[current].x = x;
		array[current].y = y;
		array[current].isUsed = use;
		current++;
	}
}
#endif

int rendererInit(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("GENOM");
	glutDisplayFunc(displayMe);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(displayMe);
	glutMotionFunc(motion);
#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
	mouse_callback = NULL;
#endif
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	dx = 0;
	dy = 0;
	leftMouseDown = 0;
	rightMouseDown = 0;
#ifdef CONFIG_PAINT_MODE
	currentSize = 0;
	current = 0;
#endif
#ifdef CONFIG_MOUSE_SCROLL_MODE
	k = 1;
#endif
	glutMainLoop();
	return 1;
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
  
   	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
   
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	width = w;
	height = h;
}

void mouse(int button, int state,int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			leftMouseDown = 1;
			lastMouseX = x;
			lastMouseY = y;
#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
			if (mouse_callback)
				mouse_callback(x,y,LEFT_MOUSE_DOWN);
#endif
		}else if (state == GLUT_UP)
		{
			leftMouseDown = 0;
#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
			if (mouse_callback)
				mouse_callback(x,y,LEFT_MOUSE_UP);
#endif
		}
	}else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			rightMouseDown = 1;
#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
			if (mouse_callback)
				mouse_callback(x,y,RIHGT_MOUSE_DOWN);
#endif
			
		}else
		if (state == GLUT_UP)
		{
			rightMouseDown = 0;
#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
			if (mouse_callback)
				mouse_callback(x,y,RIHGT_MOUSE_UP);
#endif
#ifdef CONFIG_PAINT_MODE
#ifdef CONFIG_MOUSE_SCROLL_MODE
			addPointToArray((x - dx)/k, (height - dy - y)/k , 1);
#else
			addPointToArray(x - dx, height - dy - y , 1);
#endif
			//printf("addPointToArray x = %f y = %f\n", x - dx, height - dy - y);
#endif
		}
	}else
	{
		if ((button == 3) ) // It's a wheel up event
		{
	   // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
		if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
		printf("Denis lox Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
#ifdef CONFIG_MOUSE_SCROLL_MODE
		dx = x - (x - dx)*coef ;
		dy = (height-y) - ((height-y) - dy)*coef;
		k*=coef;
		printf("dx = %f, dy = %f, k = %f\n",(dx-x)*coef,(dy-(height-y))*coef,k );
#endif
		}else if (button == 4){  // It's a wheel up event
			if (state == GLUT_UP) return;
		printf("Denis lox Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
#ifdef CONFIG_MOUSE_SCROLL_MODE
		dx = x - (x - dx)/coef ;
		dy = (height-y) - ((height-y) - dy)/coef;
		k/=coef;
		printf("dx = %f, dy = %f, k = %f\n",(dx-x)*coef,(dy-(height-y))*coef,k );
#endif
	   //printf("Denis lox Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
		}
	}
}
void motion(int x, int y)
{
	unsigned char leftState = leftMouseDown, rightState = rightMouseDown;
	if (leftState)
	{
		dx += x - lastMouseX;
		dy -= y - lastMouseY;
		lastMouseX = x;
		lastMouseY = y;
	}else
	if (rightState)
	{
#ifdef CONFIG_PAINT_MODE
#ifdef CONFIG_MOUSE_SCROLL_MODE
		addPointToArray((x - dx)/k, (height - dy - y)/k , 1);
#else
		addPointToArray(x - dx, height - dy - y , 1);
#endif
#endif
	}

}
void setImage(unsigned char **row, int w, int h)
{
	row_pointers = row;
	imageWidth = w;
	imageHeight = h;
}

void displayMe(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); 
#ifdef CONFIG_MOUSE_SCROLL_MODE
	
	glTranslated(dx, dy, 0);
	glScalef(k,k,1);
#else
	glTranslated(dx, dy, 0);
#endif
	glBegin(GL_POINTS);

	if (row_pointers != NULL)
	{
		for(int y = 0; y < imageHeight; y++) 
		{
			unsigned char* row = row_pointers[y];
			for(int x = 0; x < imageWidth; x++) 
			{
				unsigned char* px = &(row[x * 4]);
				glColor4f((float)px[0]/255.0f, (float)px[1]/255.0f,(float)px[2]/255.0f,(float)px[3]/255.0f);
				//glColor4b(px[0], px[1],px[2],px[3]);//прекол
				glVertex2i(x, (imageHeight - y));
				// Do something awesome for each pixel here...
				//printf("%4d, %4d = RGBA(%d, %d, %d, %d)\n", x, y, px[0], px[1], px[2], (float)px[3]/255.0f);
			}
		}
	}
	glEnd();

	#ifdef CONFIG_PAINT_MODE
	glBegin(GL_LINES);
	glColor3f( 1.0, 1.0, 1.0);
   // glVertex2i(0, 10 );
	//glVertex2i(10, 1 );
   // glVertex2i(10, 0 );
	for (int i = 1; i < currentSize; i++)
	{
		if (array[i - 1].isUsed)
			glVertex2i(array[i - 1].x,  array[i - 1].y  );
		if (array[i].isUsed)
			glVertex2i(array[i].x,  array[i].y  );
		//printf(" y = %d\n", array[i].y);
	}
	glEnd();
	#endif

	glFlush();
	glutSwapBuffers();
}

#ifdef CONFIG_MOUSE_CALLBACK_ENABLE
int setMouseCallback(void (*func)(int,int,int))
{
	if (!mouse_callback)
		mouse_callback = func;
	else return 0;
	return 1;
}
#endif