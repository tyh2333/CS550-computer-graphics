#include"menu.h"
#include"util.h"
#include"display.h"

#define ANGLE 30

bool YawBool=false;
bool PitchBool=false;
bool RollBool=false;
bool SlideBool=false;

void mouse(int button, int state, int x, int y){
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
	    	//do something when left mouse button is down
//	    	    startRotation(ANGLE/3);
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(state==GLUT_DOWN){
                //do something when left mouse button is down
                startRotation(ANGLE/3);
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void motion( int x, int y ){
   // record the position of the mouse.
    glutPostRedisplay();
}

//creat menu
void CreateMenu(void){ 
 
  glutCreateMenu(MenuItemClicked);
  glutAddMenuEntry("Roll+",  1);
  glutAddMenuEntry("Roll-",  2);
  glutAddMenuEntry("Pitch+", 3);
  glutAddMenuEntry("Pitch-", 4);
  glutAddMenuEntry("Yaw+",   5);
  glutAddMenuEntry("Yaw-",   6);
  glutAddMenuEntry("Slide+", 7);
  glutAddMenuEntry("Slide-", 8);
  glutAddMenuEntry("start rotation", 9);
  glutAddMenuEntry("exit", 10);
  //Attach Menu to RightClick
  glutAttachMenu(GLUT_MIDDLE_BUTTON);
}


void MenuItemClicked(int Value){
	switch(Value) 
	{
		case 1:
      YawBool=false;
      PitchBool=false;
      RollBool=true;
      SlideBool=false;
      RollUp(ANGLE);
      glFlush();
		  break;
		case 2:
      YawBool=false; 
      PitchBool=false;
      RollBool=true;
      SlideBool=false;
      RollDown(ANGLE);
			break;
		case 3:
      YawBool=false; 
      PitchBool=true;
      RollBool=false;
      SlideBool=false;
      PitchUp(ANGLE);
			break;
		case 4:
      YawBool=false; 
      PitchBool=true;
      RollBool=false;
      SlideBool=false;
      PitchDown(ANGLE);
			break;
		case 5:
      YawBool=true;
      PitchBool=false;
      RollBool=false;
      SlideBool=false;
      YawUp(ANGLE);
			break;
		case 6:
      YawBool=true;
      PitchBool=false;
      RollBool=false;
      SlideBool=false;

      YawDown(ANGLE);
			break;
		case 7:
      YawBool=false;
      PitchBool=false;
      RollBool=false;
      SlideBool=true;
     
      SlideUp(ANGLE);
			break;
		case 8:
      YawBool=false;
      PitchBool=false;
      RollBool=false;
      SlideBool=true;
      SlideDown(ANGLE);
			break;
        case 9:
            startRotation(ANGLE);
            break;
        case 10:
            exit(1);

   	}
 	//glutPostRedisplay();
}




void SubMenuItemClicked(int Value){
 	//glutPostRedisplay();
}


void specialKey(int key, int x, int y){
  switch(key){
    case GLUT_KEY_UP:
      if(YawBool)   YawUp(ANGLE);
      if(PitchBool) PitchUp(ANGLE);
      if(RollBool)  RollUp(ANGLE);
      if(SlideBool) SlideUp(ANGLE);
      
      break;
    case GLUT_KEY_DOWN:
      if(YawBool)   YawDown(ANGLE);
      if(PitchBool) PitchDown(ANGLE);
      if(RollBool)  RollDown(ANGLE);
      if(SlideBool) SlideDown(ANGLE);
      break;
  }
    glutPostRedisplay();
}
