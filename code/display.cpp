#include"display.h"
#include"util.h"
//#define NDEBUG  // used to disabled all assert.
GLsizei width, height;
double m_xtheta=0;
double m_ytheta=0;
double m_ztheta=0;
double m_slide=80;// 观察者的z轴坐标，正方向垂直屏幕向外，正值说明是远离屏幕，用于zoom in and zoom out.

double b_s = 0;
void setup(){
    glClearColor(0, 0, 0, 1.0); // *should* display black background
}

void reshape( int w, int h ){
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h ); // set to size of window
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //gluOrtho2D( 0.0, (float)w, 0.0, (float)h );
    glOrtho( 0, w, h, 0, -1, 1 );
    width = w;  // records width globally
    height = h; // records height globally
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(){
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT );
    glColor3f(0,1,0);
    glLineWidth(1);
    //// V1,low-right,
    glViewport(width/2.0, 0, width/2.0, height/2.0); //V1
    {
        projection(width/2.0, height/2.0, 1);

        gluLookAt(0, 0, m_slide,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
        // first :
        glPushMatrix();
        glRotatef(m_xtheta, 1,0,0);
        glRotatef(m_ytheta, 0,1,0);
        glRotatef(m_ztheta, 0,0,1);
        RenderGLScene(5, 5, 30);
        DrawGround();
        // RenderGLScene(1, 1, 30);
        glPopMatrix();
    }
    //// V2,low-left, viewPoint(x,y=40,z), v vecotr Z axis
    glViewport(0, 0, width/2.0, height/2.0); //V1
    {
        projection(width/2.0, height/2.0, 1);
        gluLookAt(0, 80, 0,
                  0.0, 0.0, 0.0,
                  0.0, 0.0, 1.0);
        one_viewPort();
    }
    //// V3,upper-left,viewPoint(x=40,y,z), v vecotr Y axis
    glViewport(0, height/2.0, width/2.0, height/2.0); //V1
    {
        projection(width/2.0, height/2.0, 1);
        gluLookAt( 80,0, 0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
        one_viewPort();
    }
    //// v4,upper-right,viewPoint(x,y,z=40) v vector along Y axix
    glViewport(width/2.0, height/2.0, width/2.0, height/2.0); //V1
    {
        projection(width/2.0, height/2.0, 1);

        gluLookAt(0, 0 , 80,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
        //// 原始glulookat
//        gluLookAt(0, 0, 60,
//                  0.0, 0.0, 0,
//                  0.0, 1.0, 0.0);
        one_viewPort();
    }
    glutSwapBuffers(); // display newly drawn image in window
}

void projection(int width, int height, int perspectiveORortho){
    float ratio = (float)width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspectiveORortho)
        gluPerspective(40, ratio, 1, 256);
    else
        glOrtho(-ratio, ratio, -ratio, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderGLScene(int base_radius, int top_radius, int height){
    //// draw a cylinder or a sphere
    //// you will draw more objects in this function


    //// draw cylinder
    if(height != 0)
    {
        GLUquadricObj* s = gluNewQuadric ();
        gluQuadricDrawStyle (s, GLU_LINE);
        gluCylinder(s, base_radius, top_radius, height, 20, 10);
        gluDeleteQuadric(s);
        glFlush();
    }
    //// draw spheres
    if(height == 0)
    {
        GLUquadricObj* b = gluNewQuadric();
        gluSphere(b, base_radius, 20, 10);
        gluDeleteQuadric(b);
        glFlush();
    }
}

void DrawGround(){
  glBegin(GL_LINES);

  for(float i =-1; i<=1; )
   {
       glVertex3f(i*100.f, -20.f, -100.f);
       glVertex3f(i*100.f, -20.f, 100.f);
       i+=0.1;
   }
  for(float j =-1; j<=1; )
    {
       glVertex3f(-100.f, -20.f, j*100.f);
       glVertex3f(100.f, -20.f, j*100.f);
       j+=0.1;
    }
  glEnd();
}

void RollUp(float n){
  m_ztheta+=n;
  if(m_ztheta > 360) m_ztheta=-360;
}
void RollDown(float n){
  m_ztheta-=n;
  if(m_ztheta < -360) m_ztheta=360;
}
void PitchUp(float n){
  m_ytheta+=n;
  if(m_ytheta > 360) m_ytheta=-360;
}
void PitchDown(float n){
  m_ytheta-=n;
  if(m_ytheta < -360) m_ytheta=360;
}
void YawUp(float n){
  m_xtheta+=n;
  if(m_xtheta > 360) m_xtheta=-360;
}
void YawDown(float n){
  m_xtheta-=n;
  if(m_xtheta < -360) m_xtheta=360;
}
void SlideUp(float n){
  m_slide+=n;
}
void SlideDown(float n ){
  m_slide-=n;
}
void startRotation(float n , int flag){
    while(flag)
    {
        b_s += n;
        if(b_s < -360) b_s = 360;
    }
}
void startRotation(float n){
        b_s += n;
        if(b_s < -360) b_s = 360;
}
void one_viewPort()
{
    DrawGround();
    //// (b1)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glTranslatef(0,0,10);
    RenderGLScene(2, 0, 0);
    glPopMatrix();
    //// (b2)
    glPushMatrix();
    glRotatef(0, 0,0,0);
    glTranslatef(0,0,0);
    RenderGLScene(2, 0, 0);
    glPopMatrix();
    //// (b3)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glTranslatef(0,0,-10);
    RenderGLScene(2, 0, 0);
    glPopMatrix();
    //// (b4)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glRotatef(b_s, 0,0,-1);
    glTranslatef(0,-10,10);
    RenderGLScene(3, 0, 0);
    glPopMatrix();
    //// (b5)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glRotatef(b_s, 0,0,1);
    glTranslatef(0,-10,-10);
    RenderGLScene(3, 0, 0);
    glPopMatrix();
    //// (s1)
    glPushMatrix();
    glRotatef(90, 0,0,0);
    glTranslatef(0,0,0);
    RenderGLScene(2, 2, 20);
    glPopMatrix();
    //// (s2)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glTranslatef(0,0,0);
    RenderGLScene(1, 1, 10);
    glPopMatrix();
    //// (s3)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glTranslatef(0,0,-10);
    RenderGLScene(1, 1, 10);
    glPopMatrix();
    //// (s4)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glRotatef(b_s, 0,0,-1);
    glRotatef(90, 1,0,0);
    glTranslatef(0,10,0);
    RenderGLScene(0, 2, 10);
    glPopMatrix();
    //// (s5)
    glPushMatrix();
    glRotatef(b_s, 0,1,0);
    glRotatef(b_s, 0,0,1);
    glRotatef(90, 1,0,0);
    glTranslatef(0,-10,0);
    RenderGLScene(0, 2, 10);
    glPopMatrix();
}
