
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include <stdlib.h>
#include<bits/stdc++.h>
using namespace std;
int choice,Tx,Ty,Tz,Sx,Sy,Sz;
int rotchoice;
float angle;

typedef float Matrix4 [4][4];

Matrix4 theMatrix;
float input[8][3]=
{
    {40,40,-50},{90,40,-50},{90,90,-50},{40,90,-50},
    {30,30,0},{80,30,0},{80,80,0},{30,80,0}
};
float rotateMat[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
float output[8][3];

void translate(int Tx,int Ty,int Tz){
    for(int i=0;i<8;i++){
        output[i][0] = input[i][0] + Tx;
        output[i][1] = input[i][1] + Ty;
        output[i][2] = input[i][2] + Tz;
    }
}

void scale(int sx,int sy,int sz){
    for(int i=0;i<8;i++){
        output[i][0] = input[i][0]*sx;
        output[i][1] = input[i][1]*sy;
        output[i][2] = input[i][2]*sz;
    }
}


void draw(float a[8][3]){
    glBegin(GL_QUADS);
    glColor3f(0.2,0.2,0.2);   //front
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);

    glColor3f(0.8,0.2,0.4);  //bottom
    glVertex3fv(a[0]);
    glVertex3fv(a[1]);
    glVertex3fv(a[5]);
    glVertex3fv(a[4]);

    glColor3f(0.3,0.6,0.7); //left
    glVertex3fv(a[0]);
    glVertex3fv(a[4]);
    glVertex3fv(a[7]);
    glVertex3fv(a[3]);

    glColor3f(0.2,0.8,0.2);  //right
    glVertex3fv(a[1]);
    glVertex3fv(a[2]);
    glVertex3fv(a[6]);
    glVertex3fv(a[5]);

    glColor3f(0.7,0.7,0.2); //up
    glVertex3fv(a[2]);
    glVertex3fv(a[3]);
    glVertex3fv(a[7]);
    glVertex3fv(a[6]);

    glColor3f(1.0,0.1,0.1);
    glVertex3fv(a[4]);
    glVertex3fv(a[5]);
    glVertex3fv(a[6]);
    glVertex3fv(a[7]);

    glEnd();
}

void Axes(){
     glColor3f (255.0, 255.0, 0.0);               // Set the color to BLACK
     glBegin(GL_LINES);
     glVertex2s(-1000,0);
     glVertex2s(1000,0);
     glEnd();
     glBegin(GL_LINES);
     glVertex2s(0,-1000);
     glVertex2s(0,1000);
     glEnd();
}
void setIdentityM(Matrix4 m){
    for(int i=0;i<4;i++){
        for(int j = 0; j<4;j++){
            m[i][j] = 0;
            if( i == j){
                m[i][j] = 1;
            }
        }
    }
}

void rotateX(float angle){
    angle = angle*3.14/180;
    theMatrix[1][1] = cos(angle);
    theMatrix[2][2] = cos(angle);
    theMatrix[1][2] = -sin(angle);
    theMatrix[2][1] = sin(angle);
}

void rotateY(float angle){
    angle = angle*3.14/180;
    theMatrix[0][0] = cos(angle);
    theMatrix[2][2] = cos(angle);
    theMatrix[0][2] = sin(angle);
    theMatrix[2][1] = -sin(angle);
}
void rotateZ(float angle){
    angle = angle*3.14/180;
    theMatrix[0][0] = cos(angle);
    theMatrix[1][1] = cos(angle);
    theMatrix[0][1] = -sin(angle);
    theMatrix[1][0] = sin(angle);
}

void Multiply(){
    for(int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            output[i][j] = 0;
            for(int k=0;k<3;k++){
                output[i][j] = output[i][j] + input[i][k]*theMatrix[k][j];
            }
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //This function will draw the axiss
    Axes();
    glColor3f(1.0,0.0,0.0);
    draw(input);
    setIdentityM(theMatrix);

    switch(choice){
       case 1 :  translate(Tx,Ty,Tz);
                 break;
       case 2 :  scale(Sx,Sy,Sz);
                 break;
       case 3 :  switch(rotchoice){
                    case 1: rotateX(angle);
                            break;
                    case 2: rotateY(angle);
                            break;
                    case 3: rotateZ(angle);
                            break;
                 }
                 Multiply();
                    break;
        default : break;
    }
    draw(output);
    glFlush();
}


void init(void){
    glClearColor(1.0,1.0,1.0,1.0); //set backgrond color to white
    glOrtho(-454.0,454.0,-250.0,250.0,-250.0,250.0);
    // Set the no. of Co-ordinates along X & Y axes and their gappings
    glEnable(GL_DEPTH_TEST);
     // To Render the surfaces Properly according to their depths
}
int main(int argc, char *argv[])
{
    // initialize the GLUT library
    glutInit(&argc,argv);
    // initializes the buffer mode
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    // gives the window size
    glutInitWindowSize(1362,750);
    // defines the window position
    glutInitWindowPosition(0,0);
    // creates a window with title mentioned in arguments
    glutCreateWindow("Cube Tranformations");
    // clear values for color buffers
    init();


    cout<<"Enter your choice number:\n1.Translation\n2.Scaling\n3.Rotation\n";
    cin>>choice;

    switch(choice){
        case 1 : cout<<"Enter Tx Ty Tz :";
                 cin>>Tx>>Ty>>Tz;
                 break;
        case 2 : cout<<"Enter the Sx Sy Sz :";
                 cin>>Sx>>Sy>>Sz;
                 break;
        case 3 : cout<<"Choose an option for rotation :"<<endl;
                 cout<<"1. Rotate about X-axis\n2.Rotate about Y-axis \n3. Rotate about Z-axis\n";
                 cin>>rotchoice;
                 cout<<"Enter the angle : ";
                 cin>>angle;
                 break;
    }
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
