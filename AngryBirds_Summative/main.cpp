#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "ShaderLoader.h"
#include "SceneManager.h"
#include "Utilities.h"
#include "Physics.h"

void Update();
void Render();

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	glutCreateWindow("Angry Birds Project - Author: Jasper Lyons");
	glEnable(GL_MULTISAMPLE);	
	glewInit();
		
	// Set the starting scene
	SceneManager::GetInstance()->SetCurrentScene(MENU_SCENE);
	// Initialize the starting scene
	SceneManager::GetInstance()->InitializeScene(MENU_SCENE);
	glClearColor(0.0, 0.0, 0.0, 1.0);	
	
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();
	return 0;
}

void Render()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SceneManager::GetInstance()->RenderCurrentScene();
	glutSwapBuffers();
}

void Update()
{		
	SceneManager::GetInstance()->UpdateCurrentScene();
	glutPostRedisplay();
}