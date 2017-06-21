
void init(void)
{
	// Define técnica de shading: GL_FLAT, GL_SMOOTH
	glShadeModel(GL_SMOOTH);

	// Activa o teste de profundidade
	glEnable(GL_DEPTH_TEST);

	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void initDL(void)
{
	// Compila o modelo
	funcmyDL();
}
void display(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(1.0f, 1.0f, 5.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);

	// Cubo
	glCallList(myDL);
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();

	glFlush();
}
/*void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.5, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
*/

void funcmyDL(void)
{
	myDL = glGenLists(1);

	glNewList(myDL, GL_COMPILE);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Z+ Face
	// Selecciona textura
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
	glEnd();
	// Z- Face
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
	glEnd();
	// X+ Face
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 10.0f, 10.0f);
	glEnd();
	// X- Face
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
	glEnd();
	// Y+ Face
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 10.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, 10.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 10.0f, -10.0f);
	glEnd();
	// Y- Face
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -10.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, -10.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
	glEnd();

	glEndList();
}


void load_cube_images(void)
{
	char *impathfile[6] = { "cm_front.tga", "cm_back.tga", "cm_right.tga", "cm_left.tga", "cm_top.tga", "cm_bottom.tga" };
	int i;

	// Carrega as imagens de textura
	for (i = 0; i<6; i++)
	{
		image[i] = tgaLoad(impathfile[i]);

		printf("IMAGE INFO: %s\nstatus: %d\ntype: %d\npixelDepth: %d\nsize%d x %d\n", impathfile[i], image[i]->status, image[i]->type, image[i]->pixelDepth, image[i]->width, image[i]->height); fflush(stdout);
	}

	// Cria nomes de texturas
	glGenTextures(6, texture);

	for (i = 0; i<6; i++)
	{
		// Selecciona uma textura
		glBindTexture(GL_TEXTURE_2D, texture[i]);

		// Selecciona a mistura da textura com a cor
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// Cria textura de mipmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image[i]->width, image[i]->height, GL_RGB, GL_UNSIGNED_BYTE, image[i]->imageData);
		// Se não tem mipmaps
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im[i]->width, im[i]->height, 0, GL_RGB, GL_UNSIGNED_BYTE, im[i]->imageData);
	}

	// Destrói as imagens
	for (i = 0; i<6; i++) tgaDestroy(image[i]);
}


int main(int argc, char** argv)
{
	// Inicialização do GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

	// Cria a janela de visualização
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Prog-Textures-3");

	// Inicializações
	init();
	load_cube_images();
	initDL();

	// Registar funções de callback
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(pressNormalKeys);

	// Ciclo infinito do GLUT
	glutMainLoop();

	return 0;
}


