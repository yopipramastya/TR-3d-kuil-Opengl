#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 2
// Pragnanta Yopie Pramastya (672020133)
// Zuriel Fernando (672020299)
// Wijaya Yoga Krisetianto (672020128)
// Radyan Prayoga (672020129)
// Ari Setyawan  (672020133)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion{
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init(){
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3ub(135, 92, 62);

    glVertex3f(1000.0, 0, -1000.0);

    glVertex3f(1000.0, 0, 1000.0);

    glColor3ub(95, 181, 58);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void lantai1() {

glColor3ub(74, 72, 72);
glBegin(GL_POLYGON);//depan
glVertex3f(-150.0, 0.0, 150);
glVertex3f(-150.0, 25.0, 150);
glVertex3f(150.0, 25.0, 150);
glVertex3f(150.0, 0.0, 150);
glEnd();

glBegin(GL_POLYGON);//belakang
glColor3f(0.3, 0.3, 0.3);
glVertex3f(-150.0, 0.0, -150);
glVertex3f(-150.0, 25.0, -150);
glVertex3f(150.0, 25.0, -150);
glVertex3f(150.0, 0.0, -150);
glEnd();

glBegin(GL_POLYGON);//Kanan
glColor3f(0.3, 0.3, 0.3);
glVertex3f(150.0, 0.0, 150);
glVertex3f(150.0, 25.0, 150);
glVertex3f(150.0, 25.0, -150);
glVertex3f(150.0, 0.0, -150);
glEnd();

glBegin(GL_POLYGON);//Kiri
glColor3f(0.3, 0.3, 0.3);
glVertex3f(-150.0, 0.0, -150);
glVertex3f(-150.0, 25.0, -150);
glVertex3f(-150.0, 25.0, 150);
glVertex3f(-150.0, 0.0, 150);
glEnd();

glBegin(GL_POLYGON);//Atas
glColor3ub(112, 112, 112);
glVertex3f(-150.0, 25.0, -150);
glVertex3f(-150.0, 25.0, 150);
glVertex3f(150.0, 25.0, 150);
glVertex3f(150.0, 25.0, -150);
glEnd();

}

void bangunlt1(){
glColor3f(0.9, 0.9, 0.9);

glBegin(GL_POLYGON);//depan
glVertex3f(-100.0, 25.0, 100);
glVertex3f(-100.0, 100.0, 100);
glVertex3f(100.0, 100.0, 100);
glVertex3f(100.0, 25.0, 100);
glEnd();

glBegin(GL_POLYGON);//belakang
glVertex3f(-100.0, 25.0, -100);
glVertex3f(-100.0, 100.0, -100);
glVertex3f(100.0, 100.0, -100);
glVertex3f(100.0, 25.0, -100);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(100.0, 25.0, 100);
glVertex3f(100.0, 100.0, 100);
glVertex3f(100.0, 100.0, -100);
glVertex3f(100.0, 25.0, -100);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-100.0, 25.0, -100);
glVertex3f(-100.0, 100.0, -100);
glVertex3f(-100.0, 100.0, 100);
glVertex3f(-100.0, 25.0, 100);
glEnd();

glBegin(GL_POLYGON);//Atas
glVertex3f(-100.0, 100.0, -100);
glVertex3f(-100.0, 100.0, 100);
glVertex3f(100.0, 100.0, 100);
glVertex3f(100.0, 100.0, -100);
glEnd();
}

void bangunlt2(){
glColor3f(0.9, 0.9, 0.9);

glBegin(GL_POLYGON);//depan
glVertex3f(-80, 115, 100);
glVertex3f(-80, 190, 100);
glVertex3f(80, 190, 100);
glVertex3f(80, 115, 100);
glEnd();
glPopMatrix();

glBegin(GL_POLYGON);//belakang
glVertex3f(-80, 115, -100);
glVertex3f(-80, 190, -100);
glVertex3f(80, 190, -100);
glVertex3f(80, 115, -100);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(80, 115, 100);
glVertex3f(80, 190, 100);
glVertex3f(80, 190, -100);
glVertex3f(80, 115, -100);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-80, 115, -100);
glVertex3f(-80, 190, -100);
glVertex3f(-80, 190, 100);
glVertex3f(-80, 115, 100);
glEnd();

glBegin(GL_POLYGON);//Atas
glVertex3f(-80, 190, -100);
glVertex3f(-80, 190, 100);
glVertex3f(80, 190, 100);
glVertex3f(80, 190, -100);
glEnd();
}

void bangunlt3(){
glColor3f(0.9, 0.9, 0.9);

glBegin(GL_POLYGON);//depan
glVertex3f(-60, 220, 75);
glVertex3f(-60, 270, 75);
glVertex3f(60, 270, 75);
glVertex3f(60, 220, 75);
glEnd();
glPopMatrix();

glBegin(GL_POLYGON);//belakang
glVertex3f(-60, 220, -75);
glVertex3f(-60, 270, -75);
glVertex3f(60, 270, -75);
glVertex3f(60, 220, -75);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(60, 220, 75);
glVertex3f(60, 270, 75);
glVertex3f(60, 270, -75);
glVertex3f(60, 220, -75);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-60, 220, -75);
glVertex3f(-60, 270, -75);
glVertex3f(-60, 270, 75);
glVertex3f(-60, 220, 75);
glEnd();

glBegin(GL_POLYGON);//Atas
glVertex3f(-60, 270, -75);
glVertex3f(-60, 270, 75);
glVertex3f(60, 270, 75);
glVertex3f(60, 270, -75);
glEnd();
}

void bangunlt4(){
glColor3f(0.9, 0.9, 0.9);

glBegin(GL_POLYGON);//depan
glVertex3f(-65, 308, 60);
glVertex3f(-65, 383, 60);
glVertex3f(65, 383, 60);
glVertex3f(65, 308, 60);
glEnd();
glPopMatrix();

glBegin(GL_POLYGON);//belakang
glVertex3f(-65, 308, -60);
glVertex3f(-65, 383, -60);
glVertex3f(65, 383, -60);
glVertex3f(65, 308, -60);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(65, 308, 60);
glVertex3f(65, 383, 60);
glVertex3f(65, 383, -60);
glVertex3f(65, 308, -60);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-65, 308, -60);
glVertex3f(-65, 383, -60);
glVertex3f(-65, 383, 60);
glVertex3f(-65, 308, 60);
glEnd();

glBegin(GL_POLYGON);//Atas
glVertex3f(-65, 383, -60);
glVertex3f(-65, 383, 60);
glVertex3f(65, 383, 60);
glVertex3f(65, 383, -60);
glEnd();

}


void lantai2(){

glColor3ub(227, 96, 20);
glBegin(GL_POLYGON);//depan
glVertex3f(-125.0, 110, 135);
glVertex3f(-125.0, 115, 135);
glVertex3f(125.0, 115, 135);
glVertex3f(125.0, 110, 135);
glEnd();

glBegin(GL_POLYGON);//belakang
glVertex3f(-125.0, 110, -135);
glVertex3f(-125.0, 115, -135);
glVertex3f(125.0, 115, -135);
glVertex3f(125.0, 110, -135);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(125.0, 110, 135);
glVertex3f(125.0, 115, 135);
glVertex3f(125.0, 115, -135);
glVertex3f(125.0, 110, -135);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-125.0, 110, -135);
glVertex3f(-125.0, 115, -135);
glVertex3f(-125.0, 115, 135);
glVertex3f(-125.0, 110, 135);
glEnd();

glBegin(GL_POLYGON);//Atas
glColor3f(0.3, 0.3, 0.3);
glVertex3f(-125.0, 115, -135);
glVertex3f(-125.0, 115, 135);
glVertex3f(125.0, 115, 135);
glVertex3f(125.0, 115, -135);
glEnd();
}

void lantai3(){

glColor3ub(227, 96, 20);
glBegin(GL_POLYGON);//depan
glVertex3f(-80, 215, 95);
glVertex3f(-80, 220, 95);
glVertex3f(80, 220, 95);
glVertex3f(80, 215, 95);
glEnd();

glBegin(GL_POLYGON);//belakang
glVertex3f(-80, 215, -95);
glVertex3f(-80, 220, -95);
glVertex3f(80, 220, -95);
glVertex3f(80, 215, -95);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(80, 215, 95);
glVertex3f(80, 220, 95);
glVertex3f(80, 220, -95);
glVertex3f(80, 215, -95);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-80, 215, -95);
glVertex3f(-80, 220, -95);
glVertex3f(-80, 220, 95);
glVertex3f(-80, 215, 95);
glEnd();

glBegin(GL_POLYGON);//Atas
glColor3f(0.3, 0.3, 0.3);
glVertex3f(-80, 220, -95);
glVertex3f(-80, 220, 95);
glVertex3f(80, 220, 95);
glVertex3f(80, 220, -95);
glEnd();
}

void lantai4(){

glColor3ub(227, 96, 20);
glBegin(GL_POLYGON);//depan
glVertex3f(-85, 305, 85);
glVertex3f(-85, 308, 85);
glVertex3f(85, 308, 85);
glVertex3f(85, 305, 85);
glEnd();

glBegin(GL_POLYGON);//belakang
glVertex3f(-85, 305, -85);
glVertex3f(-85, 308, -85);
glVertex3f(85, 308, -85);
glVertex3f(85, 305, -85);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(85, 305, 85);
glVertex3f(85, 308, 85);
glVertex3f(85, 308, -85);
glVertex3f(85, 305, -85);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-85, 305, -85);
glVertex3f(-85, 308, -85);
glVertex3f(-85, 308, 85);
glVertex3f(-85, 305, 85);
glEnd();

glBegin(GL_POLYGON);//Atas
glColor3f(0.3, 0.3, 0.3);
glVertex3f(-85, 308, -85);
glVertex3f(-85, 308, 85);
glVertex3f(85, 308, 85);
glVertex3f(85, 308, -85);
glEnd();
}


void sambunganlt(){

glColor3ub(184, 73, 9);

glBegin(GL_POLYGON);//depan
glVertex3f(-100.0, 100, 100);
glVertex3f(-125.0, 110, 135);
glVertex3f(125.0, 110, 135);
glVertex3f(100.0, 100, 100);
glEnd();


glBegin(GL_POLYGON);//belakang
glVertex3f(-100.0, 100, -100);
glVertex3f(-125.0, 110, -135);
glVertex3f(125.0, 110, -135);
glVertex3f(100.0, 100, -100);
glEnd();

glBegin(GL_POLYGON);//kanan
glVertex3f(100.0, 100, 100);
glVertex3f(125.0, 110, 135);
glVertex3f(125.0, 110, -135);
glVertex3f(100.0, 100, -100);
glEnd();

glBegin(GL_POLYGON);//kiri
glVertex3f(-100.0, 100, -100);
glVertex3f(-125.0, 110, -135);
glVertex3f(-125.0, 110, 135);
glVertex3f(-100.0, 100, 100);
glEnd();

}
void sambunganlt2() {
glColor3ub(184, 73, 9);
glBegin(GL_POLYGON);//bawah
glVertex3f(-125, 190, 125);
glVertex3f(-125, 190, -125);
glVertex3f(125, 190, -125);
glVertex3f(125, 190, 125);
glEnd();

glColor3f(0.3,0.3,0.3);
glBegin(GL_POLYGON);//atas
glVertex3f(-80, 215, 95);
glVertex3f(-80, 215, -95);
glVertex3f(80, 215, -95);
glVertex3f(80, 215, 95);
glEnd();

}

void sambunganlt3() {

glColor3ub(184, 73, 9);
glBegin(GL_POLYGON);//bawah
glVertex3f(-100, 270, 100);
glVertex3f(-100, 270, -100);
glVertex3f(100, 270, -100);
glVertex3f(100, 270, 100);
glEnd();

glBegin(GL_POLYGON);//atas
glVertex3f(-65, 295, 75);
glVertex3f(-65, 295, -75);
glVertex3f(65, 295, -75);
glVertex3f(65, 295, 75);
glEnd();
}

void sambunganlt4satu(){

glColor3ub(184, 73, 9);
glPushMatrix();
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//depan
glVertex3f(-65.0, 295, 75);
glVertex3f(-65.0, 297, 75);
glVertex3f(65.0, 297, 75);
glVertex3f(65.0, 295, 75);
glEnd();
glPopMatrix();

glBegin(GL_POLYGON);//belakang
glVertex3f(-65, 295, -75);
glVertex3f(-65, 297, -75);
glVertex3f(65, 297, -75);
glVertex3f(65, 295, -75);
glEnd();

glBegin(GL_POLYGON);//kanan
glVertex3f(65, 295, 75);
glVertex3f(65, 297, 75);
glVertex3f(65, 297, -75);
glVertex3f(65, 295, -75);
glEnd();

glBegin(GL_POLYGON);//kiri
glVertex3f(-65, 295, -75);
glVertex3f(-65, 297, -75);
glVertex3f(-65, 297, 75);
glVertex3f(-65, 295, 75);
glEnd();
}

void sambunganlt4dua(){

glColor3ub(227, 96, 20);
glPushMatrix();
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//depan
glVertex3f(-60.0, 297, 72);
glVertex3f(-60.0, 300, 72);
glVertex3f(60.0, 300, 72);
glVertex3f(60.0, 297, 72);
glEnd();
glPopMatrix();
glBegin(GL_POLYGON);//belakang
glVertex3f(-60.0, 297, -72);
glVertex3f(-60.0, 300, -72);
glVertex3f(60.0, 300, -72);
glVertex3f(60.0, 297, -72);
glEnd();

glBegin(GL_POLYGON);//kanan
glVertex3f(60.0, 297, 72);
glVertex3f(60.0, 300, 72);
glVertex3f(60.0, 300, -72);
glVertex3f(60.0, 297, -72);
glEnd();

glBegin(GL_POLYGON);//kiri
glVertex3f(-60.0, 297, -72);
glVertex3f(-60.0, 300, -72);
glVertex3f(-60.0, 300, 72);
glVertex3f(-60.0, 297, 72);
glEnd();
}

void sambunganlt4tiga(){

glColor3ub(184, 73, 9);

glBegin(GL_POLYGON);//depan
glVertex3f(-60.0, 300, 72);
glVertex3f(-85.0, 305, 85);
glVertex3f(85.0, 305, 85);
glVertex3f(60.0, 300, 72);
glEnd();

glBegin(GL_POLYGON);//belakang
glVertex3f(-60.0, 300, -72);
glVertex3f(-85.0, 305, -85);
glVertex3f(85.0, 305, -85);
glVertex3f(60.0, 300, -72);
glEnd();

glBegin(GL_POLYGON);//kanan
glVertex3f(60.0, 300, 72);
glVertex3f(85.0, 305, 85);
glVertex3f(85.0, 305, -85);
glVertex3f(60.0, 300, -72);
glEnd();

glBegin(GL_POLYGON);//kiri
glVertex3f(-60.0, 300, -72);
glVertex3f(-85.0, 305, -85);
glVertex3f(-85.0, 305, 85);
glVertex3f(-60.0, 300, 72);
glEnd();

}


void atap(){
//glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//depan
glVertex3f(-125, 190, 125);
glVertex3f(-80, 215, 95);
glVertex3f(80, 215, 95);
glVertex3f(125, 190, 125);
glEnd();
//glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//belakang
glVertex3f(-125, 190, -125);
glVertex3f(-80, 215, -95);
glVertex3f(80, 215, -95);
glVertex3f(125, 190, -125);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//kiri
glVertex3f(-125, 190, -125);
glVertex3f(-80, 215, -95);
glVertex3f(-80, 215, 95);
glVertex3f(-125, 190, 125);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//kanan
glVertex3f(125, 190, -125);
glVertex3f(80, 215, -95);
glVertex3f(80, 215, 95);
glVertex3f(125, 190, 125);
glEnd();
glPopMatrix();
}

void atap2(){
//glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//depan
glVertex3f(-100, 270, 100);
glVertex3f(-65, 295, 75);
glVertex3f(65, 295, 75);
glVertex3f(100, 270, 100);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//belakang
glVertex3f(-100, 270, -100);
glVertex3f(-65, 295, -75);
glVertex3f(65, 295, -75);
glVertex3f(100, 270, -100);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//kiri
glVertex3f(-100, 270, -100);
glVertex3f(-65, 295, -75);
glVertex3f(-65, 295, 75);
glVertex3f(-100, 270, 100);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//kanan
glVertex3f(100, 270, -100);
glVertex3f(65, 295, -75);
glVertex3f(65, 295, 75);
glVertex3f(100, 270, 100);
glEnd();
glPopMatrix();

}

void atap3(){
//glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//depan
glVertex3f(-85, 383, 90);
glVertex3f(-20, 440, 30);
glVertex3f(20, 440,  30);
glVertex3f(85, 383, 90);
glEnd();
glPopMatrix();
glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//belakang
glVertex3f(-85, 383, -90);
glVertex3f(-20, 440, -30);
glVertex3f(20, 440,  -30);
glVertex3f(85, 383, -90);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//kiri
glVertex3f(-85, 383, -90);
glVertex3f(-20, 440, -30);
glVertex3f(-20, 440,  30);
glVertex3f(-85, 383, 90);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3ub(1, 1, 1);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//kanan
glVertex3f(85, 383, -90);
glVertex3f(20, 440, -30);
glVertex3f(20, 440,  30);
glVertex3f(85, 383, 90);
glEnd();
glPopMatrix();

glPushMatrix();
glColor3f(0.3,0.3,0.3);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//atas
glVertex3f(-20, 440, -30);
glVertex3f(-20, 440, 30);
glVertex3f(20, 440,  30);
glVertex3f(20, 440, -30);
glEnd();
glPopMatrix();

//bawah
glPushMatrix();
glColor3ub(184, 73, 9);
//glTranslatef(x_geser,y_geser,z_geser);
glBegin(GL_POLYGON);//bawah
glVertex3f(-85, 383, -90);
glVertex3f(-85, 383, 90);
glVertex3f(85, 383,  90);
glVertex3f(85, 383, -90);
glEnd();
glPopMatrix();
}

void puncak1(){

glColor3ub(227, 96, 20);
glBegin(GL_POLYGON);//depan
glVertex3f(-17, 440, 25);
glVertex3f(-17, 443, 25);
glVertex3f(17, 443, 25);
glVertex3f(17, 440, 25);
glEnd();

glBegin(GL_POLYGON);//belakang
glVertex3f(-17, 440, -25);
glVertex3f(-17, 443, -25);
glVertex3f(17, 443, -25);
glVertex3f(17, 440, -25);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(17, 440, 25);
glVertex3f(17, 443, 25);
glVertex3f(17, 443, -25);
glVertex3f(17, 440, -25);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-17, 440, -25);
glVertex3f(-17, 443, -25);
glVertex3f(-17, 443, 25);
glVertex3f(-17, 440, 25);
glEnd();

glBegin(GL_POLYGON);//Atas
glColor3f(0.3, 0.3, 0.3);
glVertex3f(-17, 443, -25);
glVertex3f(-17, 443, 25);
glVertex3f(17, 443, 25);
glVertex3f(17, 443, -25);
glEnd();
}

void bangunpuncak(){

glColor3ub(227, 96, 20);
glBegin(GL_POLYGON);//depan
glVertex3f(-15, 443, 23);
glVertex3f(-15, 455, 23);
glVertex3f(15, 455, 23);
glVertex3f(15, 443, 23);
glEnd();

glBegin(GL_POLYGON);//belakang
glVertex3f(-15, 443, -23);
glVertex3f(-15, 455, -23);
glVertex3f(15, 455, -23);
glVertex3f(15, 443, -23);
glEnd();

glBegin(GL_POLYGON);//Kanan
glVertex3f(15, 443, 23);
glVertex3f(15, 455, 23);
glVertex3f(15, 455, -23);
glVertex3f(15, 443, -23);
glEnd();

glBegin(GL_POLYGON);//Kiri
glVertex3f(-15, 443, -23);
glVertex3f(-15, 455, -23);
glVertex3f(-15, 455, 23);
glVertex3f(-15, 443, 23);
glEnd();

glBegin(GL_POLYGON);//Atas
glColor3f(0.3, 0.3, 0.3);
glVertex3f(-15, 455, -23);
glVertex3f(-15, 455, 23);
glVertex3f(15, 455, 23);
glVertex3f(15, 455, -23);
glEnd();
}

void tiangpuncak(){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(255,215,0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(0,0,455);
	gluCylinder(pObj, 2, 2, 120, 25, 25);

    glEnd();
    glPopMatrix();

}

void tiangpuncak2(){

    glPushMatrix();//lingkaran
    glColor3ub(255,215,0);
	glRotated(270,1,0,0);
    glTranslatef(0,0,455);
    glutSolidSphere(12.0, 30, 30);
    glEnd();
    glPopMatrix();

    glPushMatrix();//donat
	glRotated(270,0.5,0,0);
    glTranslatef(0,0,485);
    glutSolidTorus(4.0, 5.0, 20, 20);
    glEnd();
    glPopMatrix();

    glPushMatrix();//donat
	glRotated(270,0.5,0,0);
    glTranslatef(0,0,495);
    glutSolidTorus(4.0, 4.5, 20, 20);
    glEnd();
    glPopMatrix();

    glPushMatrix();//donat
	glRotated(270,0.5,0,0);
    glTranslatef(0,0,505);
    glutSolidTorus(4.0, 4.0, 20, 20);
    glEnd();
    glPopMatrix();

    glPushMatrix();//donat
	glRotated(270,0.5,0,0);
    glTranslatef(0,0,515);
    glutSolidTorus(4.0, 3.5, 20, 20);
    glEnd();
    glPopMatrix();

    glPushMatrix();//donat
	glRotated(270,0.5,0,0);
    glTranslatef(0,0,525);
    glutSolidTorus(4.0, 3.0, 20, 20);
    glEnd();
    glPopMatrix();

    glPushMatrix();//donat
	glRotated(270,0.5,0,0);
    glTranslatef(0,0,540);
    glutSolidTorus(4.0, 3.0, 20, 20);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kerucut
	glRotated(270,0.5,0,0);
    glTranslatef(0,0,558);
    glutSolidCone(3.0, 20.0, 20, 20);
    glEnd();
    glPopMatrix();

}

void tangga(){

    glBegin(GL_TRIANGLES);//kiri
    glColor3ub(84, 84, 84);
    glVertex3f(-25, 0, 150);
    glVertex3f(-25, 25, 150);
    glVertex3f(-25, 0, 200);
    glEnd();

    glBegin(GL_TRIANGLES);//kanan
    glVertex3f(25, 0, 150);
    glVertex3f(25, 25, 150);
    glVertex3f(25, 0, 200);
    glEnd();

    glBegin(GL_POLYGON);//part1 - atas
    glColor3ub(112, 112, 112);
    glVertex3f(-25, 25, 150);
    glVertex3f(-25, 25, 160);
    glVertex3f(25, 25, 160);
    glVertex3f(25, 25, 150);
    glEnd();

    glBegin(GL_POLYGON);//part1 - bawah
    glColor3ub(84, 84, 84);
    glVertex3f(-25, 25, 160);
    glVertex3f(-25, 20, 160);
    glVertex3f(25, 20, 160);
    glVertex3f(25, 25, 160);
    glEnd();

    glBegin(GL_POLYGON);//part2 - atas
    glColor3ub(112, 112, 112);
    glVertex3f(-25, 20, 160);
    glVertex3f(-25, 20, 170);
    glVertex3f(25, 20, 170);
    glVertex3f(25, 20, 160);
    glEnd();

    glBegin(GL_POLYGON);//part2 - bawah
    glColor3ub(84, 84, 84);
    glVertex3f(-25, 20, 170);
    glVertex3f(-25, 15, 170);
    glVertex3f(25, 15, 170);
    glVertex3f(25, 20, 170);
    glEnd();

    glBegin(GL_POLYGON);//part3 - atas
    glColor3ub(112, 112, 112);
    glVertex3f(-25, 15, 170);
    glVertex3f(-25, 15, 180);
    glVertex3f(25, 15, 180);
    glVertex3f(25, 15, 170);
    glEnd();

    glBegin(GL_POLYGON);//part3 - bawah
    glColor3ub(84, 84, 84);
    glVertex3f(-25, 15, 180);
    glVertex3f(-25, 10, 180);
    glVertex3f(25, 10, 180);
    glVertex3f(25, 15, 180);
    glEnd();

    glBegin(GL_POLYGON);//part4 - atas
    glColor3ub(112, 112, 112);
    glVertex3f(-25, 10, 180);
    glVertex3f(-25, 10, 190);
    glVertex3f(25, 10, 190);
    glVertex3f(25, 10, 180);
    glEnd();

    glBegin(GL_POLYGON);//part4 - bawah
    glColor3ub(84, 84, 84);
    glVertex3f(-25, 10, 190);
    glVertex3f(-25, 5, 190);
    glVertex3f(25, 5, 190);
    glVertex3f(25, 10, 190);
    glEnd();

    glBegin(GL_POLYGON);//part5 - atas
    glColor3ub(112, 112, 112);
    glVertex3f(-25, 5, 190);
    glVertex3f(-25, 5, 200);
    glVertex3f(25, 5, 200);
    glVertex3f(25, 5, 190);
    glEnd();

    glBegin(GL_POLYGON);//part5 - bawah
    glColor3ub(84, 84, 84);
    glVertex3f(-25, 5, 200);
    glVertex3f(-25, 0, 200);
    glVertex3f(25, 0, 200);
    glVertex3f(25, 5, 200);
    glEnd();

    //tutup kiri

    glBegin(GL_TRIANGLES);//1
    glColor3ub(84, 84, 84);
    glVertex3f(-25, 25, 150);
    glVertex3f(-25, 25, 160);
    glVertex3f(-25, 20, 160);
    glEnd();

    glBegin(GL_TRIANGLES);//2
    glVertex3f(-25, 20, 160);
    glVertex3f(-25, 20, 170);
    glVertex3f(-25, 15, 170);
    glEnd();

    glBegin(GL_TRIANGLES);//3
    glVertex3f(-25, 15, 170);
    glVertex3f(-25, 15, 180);
    glVertex3f(-25, 10, 180);
    glEnd();

    glBegin(GL_TRIANGLES);//4
    glVertex3f(-25, 10, 180);
    glVertex3f(-25, 10, 190);
    glVertex3f(-25, 5, 190);
    glEnd();

    glBegin(GL_TRIANGLES);//5
    glVertex3f(-25, 5, 190);
    glVertex3f(-25, 5, 200);
    glVertex3f(-25, 0, 200);
    glEnd();

    //tutup kanan

    glBegin(GL_TRIANGLES);//1
    glVertex3f(25, 25, 150);
    glVertex3f(25, 25, 160);
    glVertex3f(25, 20, 160);
    glEnd();

    glBegin(GL_TRIANGLES);//2
    glVertex3f(25, 20, 160);
    glVertex3f(25, 20, 170);
    glVertex3f(25, 15, 170);
    glEnd();

    glBegin(GL_TRIANGLES);//3
    glVertex3f(25, 15, 170);
    glVertex3f(25, 15, 180);
    glVertex3f(25, 10, 180);
    glEnd();

    glBegin(GL_TRIANGLES);//4
    glVertex3f(25, 10, 180);
    glVertex3f(25, 10, 190);
    glVertex3f(25, 5, 190);
    glEnd();

    glBegin(GL_TRIANGLES);//5
    glVertex3f(25, 5, 190);
    glVertex3f(25, 5, 200);
    glVertex3f(25, 0, 200);
    glEnd();
}

void pegangantangga(){

    //tiang tangga kanan

    glBegin(GL_POLYGON);//depan
    glColor3ub(204, 76, 16);
    glVertex3f(25.0, 0.0, 200);
    glVertex3f(32.0, 0.0, 200);
    glVertex3f(32.0, 25.0, 200);
    glVertex3f(25.0, 25.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//belakang

    glVertex3f(25.0, 0.0, 193);
    glVertex3f(32.0, 0.0, 193);
    glVertex3f(32.0, 25.0, 193);
    glVertex3f(25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kiri

    glVertex3f(25.0, 0.0, 193);
    glVertex3f(25.0, 0.0, 200);
    glVertex3f(25.0, 25.0, 200);
    glVertex3f(25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kanan

    glVertex3f(32.0, 0.0, 193);
    glVertex3f(32.0, 0.0, 200);
    glVertex3f(32.0, 25.0, 200);
    glVertex3f(32.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//atas

    glVertex3f(25.0, 25.0, 200);
    glVertex3f(32.0, 25.0, 200);
    glVertex3f(32.0, 25.0, 193);
    glVertex3f(25.0, 25.0, 193);
    glEnd();

    //tiang tangga kiri

    glBegin(GL_POLYGON);//depan

    glVertex3f(-25.0, 0.0, 200);
    glVertex3f(-32.0, 0.0, 200);
    glVertex3f(-32.0, 25.0, 200);
    glVertex3f(-25.0, 25.0, 200);
    glEnd();

    glBegin(GL_POLYGON);//belakang

    glVertex3f(-25.0, 0.0, 193);
    glVertex3f(-32.0, 0.0, 193);
    glVertex3f(-32.0, 25.0, 193);
    glVertex3f(-25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kiri

    glVertex3f(-25.0, 0.0, 193);
    glVertex3f(-25.0, 0.0, 200);
    glVertex3f(-25.0, 25.0, 200);
    glVertex3f(-25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kanan

    glVertex3f(-32.0, 0.0, 193);
    glVertex3f(-32.0, 0.0, 200);
    glVertex3f(-32.0, 25.0, 200);
    glVertex3f(-32.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//atas

    glVertex3f(-25.0, 25.0, 200);
    glVertex3f(-32.0, 25.0, 200);
    glVertex3f(-32.0, 25.0, 193);
    glVertex3f(-25.0, 25.0, 193);
    glEnd();

    //pegangan tangga kiri - kanan

    glBegin(GL_POLYGON);//atas

    glVertex3f(-25.0, 25.0, 200);
    glVertex3f(-32.0, 25.0, 200);
    glVertex3f(-32.0, 50.0, 147);
    glVertex3f(-25.0, 50.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(204, 76, 16);
    glVertex3f(-25.0, 25.0, 193);
    glVertex3f(-32.0, 25.0, 193);
    glVertex3f(-32.0, 45.0, 147);
    glVertex3f(-25.0, 45.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//kanan

    glVertex3f(-25.0, 45.0, 147);
    glVertex3f(-25.0, 50.0, 147);
    glVertex3f(-25.0, 25.0, 200);
    glVertex3f(-25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kiri

    glVertex3f(-32.0, 45.0, 147);
    glVertex3f(-32.0, 50.0, 147);
    glVertex3f(-32.0, 25.0, 200);
    glVertex3f(-32.0, 25.0, 193);
    glEnd();

    //pegangan tangga kiri - kiri

    glBegin(GL_POLYGON);//atas

    glVertex3f(-25.0, 25.0, 200);
    glVertex3f(-32.0, 25.0, 200);
    glVertex3f(-32.0, 50.0, 147);
    glVertex3f(-25.0, 50.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//bawah

    glVertex3f(-25.0, 25.0, 193);
    glVertex3f(-32.0, 25.0, 193);
    glVertex3f(-32.0, 45.0, 147);
    glVertex3f(-25.0, 45.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//kanan

    glVertex3f(-25.0, 45.0, 147);
    glVertex3f(-25.0, 50.0, 147);
    glVertex3f(-25.0, 25.0, 200);
    glVertex3f(-25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kiri

    glVertex3f(-32.0, 45.0, 147);
    glVertex3f(-32.0, 50.0, 147);
    glVertex3f(-32.0, 25.0, 200);
    glVertex3f(-32.0, 25.0, 193);
    glEnd();


    //pegangan tangga kanan - kanan

    glBegin(GL_POLYGON);//atas

    glVertex3f(25.0, 25.0, 200);
    glVertex3f(32.0, 25.0, 200);
    glVertex3f(32.0, 50.0, 147);
    glVertex3f(25.0, 50.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//bawah

    glVertex3f(25.0, 25.0, 193);
    glVertex3f(32.0, 25.0, 193);
    glVertex3f(32.0, 45.0, 147);
    glVertex3f(25.0, 45.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//kanan

    glVertex3f(25.0, 45.0, 147);
    glVertex3f(25.0, 50.0, 147);
    glVertex3f(25.0, 25.0, 200);
    glVertex3f(25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kiri

    glVertex3f(32.0, 45.0, 147);
    glVertex3f(32.0, 50.0, 147);
    glVertex3f(32.0, 25.0, 200);
    glVertex3f(32.0, 25.0, 193);
    glEnd();

    //pegangan tangga kanan - kiri

    glBegin(GL_POLYGON);//atas

    glVertex3f(25.0, 25.0, 200);
    glVertex3f(32.0, 25.0, 200);
    glVertex3f(32.0, 50.0, 147);
    glVertex3f(25.0, 50.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//bawah

    glVertex3f(25.0, 25.0, 193);
    glVertex3f(32.0, 25.0, 193);
    glVertex3f(32.0, 45.0, 147);
    glVertex3f(25.0, 45.0, 147);
    glEnd();

    glBegin(GL_POLYGON);//kanan

    glVertex3f(25.0, 45.0, 147);
    glVertex3f(25.0, 50.0, 147);
    glVertex3f(25.0, 25.0, 200);
    glVertex3f(25.0, 25.0, 193);
    glEnd();

    glBegin(GL_POLYGON);//kiri

    glVertex3f(32.0, 45.0, 147);
    glVertex3f(32.0, 50.0, 147);
    glVertex3f(32.0, 25.0, 200);
    glVertex3f(32.0, 25.0, 193);
    glEnd();

}

void pagarkecil_depan(float x,float y,float z,float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3){
    //pagar kecil (depan)
    for(int a=0; a<4; a++){
        glBegin(GL_POLYGON);
        glColor3f(0,0,0);
        glVertex3f(x,y,z);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glVertex3f(x3,y3,z3);
        x+=22 ; x1+=22 ; x2+=22 ; x3+=22 ;
        glEnd();
    }
}
void pagarkecil_belakang (float x,float y,float z,float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3){
     //pagar kecil belakang
    for (int b=0; b<12; b++){
        glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(x,y,z);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glVertex3f(x3,y3,z3);
        x-=22 ; x1-=22 ; x2-=22 ; x3-=22 ;
        glEnd();
    }
}
void pagarkecil_kiri (float x,float y,float z,float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3){
     //pagar kecil (belakang)
    for (int c=0; c<12; c++){
        glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(x,y,z);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glVertex3f(x3,y3,z3);
        z-=22; z1-=22; z2-=22; z3-=22;
        glEnd();
    }
}
void pagarkecil_kanan (float x,float y,float z,float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3){
     //pagar kecil (belakang)
    for (int d=0; d<12; d++){
        glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,0.0);
        glVertex3f(x,y,z);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glVertex3f(x3,y3,z3);
        z-=22; z1-=22; z2-=22; z3-=22;
        glEnd();
    }
}
void pagarpanjang(float x,float y,float z,float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3){
    for(int e=0; e<2; e++){
    glBegin(GL_POLYGON);//depan
    glColor3ub(232, 87, 14);
    glVertex3f(x,y,z);
    glVertex3f(x1,y1,z1);
    glVertex3f(x2,y2,z2);
    glVertex3f(x3,y3,z3);
    glEnd();
    y-=12; y1-=12; y2-=12; y3-=12;
    }
}

void pagar_lantai1() {
    /////pagar depan (kanan tangga)
    glBegin(GL_POLYGON);//depan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, 147);
    glVertex3f(37.0, 25.0, 147);
    glVertex3f(37.0, 50.0, 147);
    glVertex3f(30.0, 50.0, 147);
    glEnd();
    glBegin(GL_POLYGON);//belakang
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, 140);
    glVertex3f(37.0, 25.0, 140);
    glVertex3f(37.0, 50.0, 140);
    glVertex3f(30.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, 140);
    glVertex3f(30.0, 25.0, 147);
    glVertex3f(30.0, 50.0, 147);
    glVertex3f(30.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kanan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(37.0, 25.0, 140);
    glVertex3f(37.0, 25.0, 147);
    glVertex3f(37.0, 50.0, 147);
    glVertex3f(37.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//atas
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 50.0, 147);
    glVertex3f(37.0, 50.0, 147);
    glVertex3f(37.0, 50.0, 140);
    glVertex3f(30.0, 50.0, 140);
    glEnd();


    //////pagar ujung kanan depan
    glBegin(GL_POLYGON);//depan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(140.0, 25.0, 147);
    glVertex3f(147.0, 25.0, 147);
    glVertex3f(147.0, 50.0, 147);
    glVertex3f(140.0, 50.0, 147);
    glEnd();
    glBegin(GL_POLYGON);//belakang
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(140.0, 25.0, 140);
    glVertex3f(147.0, 25.0, 140);
    glVertex3f(147.0, 50.0, 140);
    glVertex3f(140.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kiri
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(140.0, 25.0, 140);
    glVertex3f(140.0, 25.0, 147);
    glVertex3f(140.0, 50.0, 147);
    glVertex3f(140.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kanan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(147.0, 25.0, 140);
    glVertex3f(147.0, 25.0, 147);
    glVertex3f(147.0, 50.0, 147);
    glVertex3f(147.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//atas
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(140.0, 50.0, 147);
    glVertex3f(147.0, 50.0, 147);
    glVertex3f(147.0, 50.0, 140);
    glVertex3f(140.0, 50.0, 140);
    glEnd();

    //pagar depan (kiri tangga)
    glBegin(GL_POLYGON);//depan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, 147);
    glVertex3f(-37.0, 25.0, 147);
    glVertex3f(-37.0, 50.0, 147);
    glVertex3f(-30.0, 50.0, 147);
    glEnd();
    glBegin(GL_POLYGON);//belakang
    glVertex3f(-30.0, 25.0, 140);
    glVertex3f(-37.0, 25.0, 140);
    glVertex3f(-37.0, 50.0, 140);
    glVertex3f(-30.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kiri
    glVertex3f(-30.0, 25.0, 140);
    glVertex3f(-30.0, 25.0, 147);
    glVertex3f(-30.0, 50.0, 147);
    glVertex3f(-30.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kanan
    glVertex3f(-37.0, 25.0, 140);
    glVertex3f(-37.0, 25.0, 147);
    glVertex3f(-37.0, 50.0, 147);
    glVertex3f(-37.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//atas
    glVertex3f(-30.0, 50.0, 147);
    glVertex3f(-37.0, 50.0, 147);
    glVertex3f(-37.0, 50.0, 140);
    glVertex3f(-30.0, 50.0, 140);
    glEnd();


    //pagar ujung kiri depan
    glBegin(GL_POLYGON);//depan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-138.0, 25.0, 147);
    glVertex3f(-145.0, 25.0, 147);
    glVertex3f(-145.0, 50.0, 147);
    glVertex3f(-138.0, 50.0, 147);
    glEnd();
    glBegin(GL_POLYGON);//belakang
    glVertex3f(-138.0, 25.0, 140);
    glVertex3f(-145.0, 25.0, 140);
    glVertex3f(-145.0, 50.0, 140);
    glVertex3f(-138.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kiri
    glVertex3f(-138.0, 25.0, 140);
    glVertex3f(-138.0, 25.0, 147);
    glVertex3f(-138.0, 50.0, 147);
    glVertex3f(-138.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//kanan
    glVertex3f(-145.0, 25.0, 140);
    glVertex3f(-145.0, 25.0, 147);
    glVertex3f(-145.0, 50.0, 147);
    glVertex3f(-145.0, 50.0, 140);
    glEnd();
    glBegin(GL_POLYGON);//atas
    glVertex3f(-138.0, 50.0, 147);
    glVertex3f(-145.0, 50.0, 147);
    glVertex3f(-145.0, 50.0, 140);
    glVertex3f(-138.0, 50.0, 140);
    glEnd();



    //pagar belakang - ujung kanan
    glBegin(GL_POLYGON);//depan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(140.0, 25.0, -147);
    glVertex3f(147.0, 25.0, -147);
    glVertex3f(147.0, 50.0, -147);
    glVertex3f(140.0, 50.0, -147);
    glEnd();
    glBegin(GL_POLYGON);//belakang
    glVertex3f(140.0, 25.0, -140);
    glVertex3f(147.0, 25.0, -140);
    glVertex3f(147.0, 50.0, -140);
    glVertex3f(140.0, 50.0, -140);
    glEnd();
    glBegin(GL_POLYGON);//kiri
    glVertex3f(140.0, 25.0, -140);
    glVertex3f(140.0, 25.0, -147);
    glVertex3f(140.0, 50.0, -147);
    glVertex3f(140.0, 50.0, -140);
    glEnd();
    glBegin(GL_POLYGON);//kanan
    glVertex3f(147.0, 25.0, -140);
    glVertex3f(147.0, 25.0, -147);
    glVertex3f(147.0, 50.0, -147);
    glVertex3f(147.0, 50.0, -140);
    glEnd();
    glBegin(GL_POLYGON);//atas
    glVertex3f(140.0, 50.0, -147);
    glVertex3f(147.0, 50.0, -147);
    glVertex3f(147.0, 50.0, -140);
    glVertex3f(140.0, 50.0, -140);
    glEnd();

    //pagar belakang - ujung kiri
    glBegin(GL_POLYGON);//depan
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-138.0, 25.0, -147);
    glVertex3f(-145.0, 25.0, -147);
    glVertex3f(-145.0, 50.0, -147);
    glVertex3f(-138.0, 50.0, -147);
    glEnd();
    glBegin(GL_POLYGON);//belakang
    glVertex3f(-138.0, 25.0, -140);
    glVertex3f(-145.0, 25.0, -140);
    glVertex3f(-145.0, 50.0, -140);
    glVertex3f(-138.0, 50.0, -140);
    glEnd();
    glBegin(GL_POLYGON);//kiri
    glVertex3f(-138.0, 25.0, -140);
    glVertex3f(-138.0, 25.0, -147);
    glVertex3f(-138.0, 50.0, -147);
    glVertex3f(-138.0, 50.0, -140);
    glEnd();
    glBegin(GL_POLYGON);//kanan
    glVertex3f(-145.0, 25.0, -140);
    glVertex3f(-145.0, 25.0, -147);
    glVertex3f(-145.0, 50.0, -147);
    glVertex3f(-145.0, 50.0, -140);
    glEnd();
    glBegin(GL_POLYGON);//atas
    glVertex3f(-138.0, 50.0, -147);
    glVertex3f(-145.0, 50.0, -147);
    glVertex3f(-145.0, 50.0, -140);
    glVertex3f(-138.0, 50.0, -140);
    glEnd();
}

void pagarlantai2depankanan(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(115,-125,110);//depan kanan
	gluCylinder(pObj, 3, 3, 40, 25, 25);

    glEnd();
    glPopMatrix();
}
void pagarlantai2depankiri(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-115,-125,110);//depan kiri
	gluCylinder(pObj, 3, 3, 40, 25, 25);

    glEnd();
    glPopMatrix();
}
void pagarlantai2belakangkanan(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(115,125,110);//depan kanan
	gluCylinder(pObj, 3, 3, 40, 25, 25);

    glEnd();
    glPopMatrix();
}
void pagarlantai2belakangkiri(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-115,125,110);//depan kiri
	gluCylinder(pObj, 3, 3, 40, 25, 25);

    glEnd();
    glPopMatrix();
}

void pagarkecil_depanLT2(float x,float y,float z){

    for (int a=0; a<23; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    x-=10;
	gluCylinder(pObj, 1.5, 1.5, 30, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_kiriLT2(float x,float y,float z){

    for (int a=0; a<25; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    y+=10;
	gluCylinder(pObj, 1.5, 1.5, 30, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_belakangLT2(float x,float y,float z){

    for (int a=0; a<23; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    x+=10;
	gluCylinder(pObj, 1.5, 1.5, 30, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_kananLT2(float x,float y,float z){

    for (int a=0; a<25; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    y+=10;
	gluCylinder(pObj, 1.5, 1.5, 30, 25, 25);

    glEnd();
    glPopMatrix();
    }

}

//PONDASI
void pagarlantai3depankanan(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(70,-85,220);//depan kanan
	gluCylinder(pObj, 3, 3, 25, 25, 25);

    glEnd();
    glPopMatrix();
}
void pagarlantai3depankiri(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-70,-85,220);//depan kiri
	gluCylinder(pObj, 3, 3, 25, 25, 25);

    glEnd();
    glPopMatrix();
}
void pagarlantai3belakangkanan(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(70,85,220);//depan kanan
	gluCylinder(pObj, 3, 3, 25, 25, 25);

    glEnd();
    glPopMatrix();
}
void pagarlantai3belakangkiri(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-70,85,220);//depan kiri
	gluCylinder(pObj, 3, 3, 25, 25, 25);

    glEnd();
    glPopMatrix();
}

void pagarlantai4depankanan(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

   // glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(75,-75,307.5);//depan kanan
	gluCylinder(pObj, 3, 3, 30, 25, 25);

    glEnd();
    glPopMatrix();
}

void pagarlantai4depankiri(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

   // glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-75,-75,307.5);//depan kiri
	gluCylinder(pObj, 3, 3, 30, 25, 25);

    glEnd();
    glPopMatrix();
}

void pagarlantai4belakangkanan(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(75,75,307.5);//depan kanan
	gluCylinder(pObj, 3, 3, 30, 25, 25);

    glEnd();
    glPopMatrix();
}

void pagarlantai4belakangkiri(){

    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(122,61,31);
	glRotated(270,1,0,0);

   // glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-75,75,307.5);//depan kiri
	gluCylinder(pObj, 3, 3, 30, 25, 25);

    glEnd();
    glPopMatrix();
}

//PAGAR Lantai 3
void pagarkecil_depanLT3(float x,float y,float z){

    for (int a=0; a<14; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    x-=10;
	gluCylinder(pObj, 1.5, 1.5, 20, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_kiriLT3(float x,float y,float z){

    for (int a=0; a<17; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    y+=10;
	gluCylinder(pObj, 1.5, 1.5, 20, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_belakangLT3(float x,float y,float z){

    for (int a=0; a<14; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    x+=10;
	gluCylinder(pObj, 1.5, 1.5, 20, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_kananLT3(float x,float y,float z){

    for (int a=0; a<17; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    y+=10;
	gluCylinder(pObj, 1.5, 1.5, 20, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
//PAGAR Lanta 4
void pagarkecil_depanLT4(float x,float y,float z){

    for (int a=0; a<15; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    x-=10;
	gluCylinder(pObj, 1.5, 1.5, 25, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_kiriLT4(float x,float y,float z){

    for (int a=0; a<15; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    y+=10;
	gluCylinder(pObj, 1.5, 1.5, 25, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_belakangLT4(float x,float y,float z){

    for (int a=0; a<15; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    x+=10;
	gluCylinder(pObj, 1.5, 1.5, 25, 25, 25);

    glEnd();
    glPopMatrix();
    }

}
void pagarkecil_kananLT4(float x,float y,float z){

    for (int a=0; a<15; a++){
    glPushMatrix();
	glRotated(360,0,1,0);
	glPopMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(201, 81, 2);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(x , y, z);//depan kanan
    y+=10;
	gluCylinder(pObj, 1.5, 1.5, 25, 25, 25);

    glEnd();
    glPopMatrix();
    }

}


void tiang(void){


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

	glTranslatef(40,-120,25);//depan kanan
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);
	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-75,0,-5);//depan kiri
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);
	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(155,120,5);//kanan
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);

   // glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-240,0,-5);//kiri
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);
	glPopMatrix();
}

void tiang1(void){


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);


	glTranslatef(40,120,25);//belakang kanan
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);

	glTranslatef(-75,0,-5);//belakang kiri
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);
    glEnd();
    glPopMatrix();
}

void tiang2(void){

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(40,-120,115);//depan kanan
	gluCylinder(pObj, 1, 1, 75, 30, 30);
	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-75,0,0);//depan kiri
	gluCylinder(pObj, 1, 1, 75, 30, 30);
	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(145,120,-3);//kanan
	gluCylinder(pObj, 1, 1, 80, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-220,0,-2);//kiri
	gluCylinder(pObj, 1, 1, 80, 30, 30);
	glPopMatrix();
}

void tiang3(void){

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(40,120,115);//belakang kanan
	gluCylinder(pObj, 1, 1, 75, 30, 30);

	glTranslatef(-75,0,0);//belakang kiri
	gluCylinder(pObj, 1, 1, 75, 30, 30);
    glEnd();
    glPopMatrix();
}

void rangka (void){
glPushMatrix();
    //glTranslatef(x_geser, 470, z_geser);
    //glutWireCube(60);
    //glutWireCube(170);
    //glutWireCube(190);
    //glutWireCube(250);
    //glutWireCube(200);
    glPopMatrix();
}

void pintu(){

    //pintu lantai 1
    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-15,25,102);
    glVertex3f(-15,80,102);
    glVertex3f(15,80,102);
    glVertex3f(15,25,102);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-15,25,100);
    glVertex3f(-15,80,100);
    glVertex3f(-15,80,102);
    glVertex3f(-15,25,102);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(15,25,102);
    glVertex3f(15,80,102);
    glVertex3f(15,80,100);
    glVertex3f(15,25,100);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-15,80,100);
    glVertex3f(-15,80,102);
    glVertex3f(15,80,102);
    glVertex3f(15,80,100);
    glEnd();

    //pintu lantai 2 - depan

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-25,110,102);
    glVertex3f(-25,175,102);
    glVertex3f(25,175,102);
    glVertex3f(25,110,102);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-25,110,100);
    glVertex3f(-25,175,100);
    glVertex3f(-25,175,102);
    glVertex3f(-25,110,102);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(25,110,102);
    glVertex3f(25,175,102);
    glVertex3f(25,175,100);
    glVertex3f(25,110,100);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-25,175,100);
    glVertex3f(-25,175,102);
    glVertex3f(25,175,102);
    glVertex3f(25,175,100);
    glEnd();

    //pintu lantai 2 - kiri

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-82,130,-20);
    glVertex3f(-82,175,-20);
    glVertex3f(-82,175,20);
    glVertex3f(-82,130,20);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-80,130,-20);
    glVertex3f(-80,175,-20);
    glVertex3f(-82,175,-20);
    glVertex3f(-82,130,-20);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-80,130,20);
    glVertex3f(-80,175,20);
    glVertex3f(-82,175,20);
    glVertex3f(-82,130,20);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-80,175,-20);
    glVertex3f(-82,175,-20);
    glVertex3f(-82,175,20);
    glVertex3f(-80,175,20);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(-80,130,-20);
    glVertex3f(-82,130,-20);
    glVertex3f(-82,130,20);
    glVertex3f(-80,130,20);
    glEnd();

    //pintu lantai 2 - kiri

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-82,130,-20);
    glVertex3f(-82,175,-20);
    glVertex3f(-82,175,20);
    glVertex3f(-82,130,20);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-80,130,-20);
    glVertex3f(-80,175,-20);
    glVertex3f(-82,175,-20);
    glVertex3f(-82,130,-20);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-80,130,20);
    glVertex3f(-80,175,20);
    glVertex3f(-82,175,20);
    glVertex3f(-82,130,20);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-80,175,-20);
    glVertex3f(-82,175,-20);
    glVertex3f(-82,175,20);
    glVertex3f(-80,175,20);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(-80,130,-20);
    glVertex3f(-82,130,-20);
    glVertex3f(-82,130,20);
    glVertex3f(-80,130,20);
    glEnd();

    //pintu lantai 2 - kanan

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(82,130,-20);
    glVertex3f(82,175,-20);
    glVertex3f(82,175,20);
    glVertex3f(82,130,20);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(80,130,-20);
    glVertex3f(80,175,-20);
    glVertex3f(82,175,-20);
    glVertex3f(82,130,-20);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(80,130,20);
    glVertex3f(80,175,20);
    glVertex3f(82,175,20);
    glVertex3f(82,130,20);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(80,175,-20);
    glVertex3f(82,175,-20);
    glVertex3f(82,175,20);
    glVertex3f(80,175,20);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(80,130,-20);
    glVertex3f(82,130,-20);
    glVertex3f(82,130,20);
    glVertex3f(80,130,20);
    glEnd();

    //pintu lantai 2 - belakang

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-25,110,-102);
    glVertex3f(-25,175,-102);
    glVertex3f(25,175,-102);
    glVertex3f(25,110,-102);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-25,110,-100);
    glVertex3f(-25,175,-100);
    glVertex3f(-25,175,-102);
    glVertex3f(-25,110,-102);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(25,110,-102);
    glVertex3f(25,175,-102);
    glVertex3f(25,175,-100);
    glVertex3f(25,110,-100);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-25,175,-100);
    glVertex3f(-25,175,-102);
    glVertex3f(25,175,-102);
    glVertex3f(25,175,-100);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(-25,110,-100);
    glVertex3f(-25,110,-102);
    glVertex3f(25,110,-102);
    glVertex3f(25,110,-100);
    glEnd();

    //pintu lantai 3 - depan

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-15,220,77);
    glVertex3f(-15,250,77);
    glVertex3f(15,250,77);
    glVertex3f(15,220,77);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-15,220,75);
    glVertex3f(-15,250,75);
    glVertex3f(-15,250,77);
    glVertex3f(-15,220,77);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(15,220,77);
    glVertex3f(15,250,77);
    glVertex3f(15,250,75);
    glVertex3f(15,220,75);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-15,250,75);
    glVertex3f(-15,250,77);
    glVertex3f(15,250,77);
    glVertex3f(15,250,75);
    glEnd();

    //pintu lantai 3 - kiri

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-62,220,-20);
    glVertex3f(-62,250,-20);
    glVertex3f(-62,250,20);
    glVertex3f(-62,220,20);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-60,220,-20);
    glVertex3f(-60,250,-20);
    glVertex3f(-62,250,-20);
    glVertex3f(-62,220,-20);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-60,220,20);
    glVertex3f(-60,250,20);
    glVertex3f(-62,250,20);
    glVertex3f(-62,220,20);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-60,250,-20);
    glVertex3f(-62,250,-20);
    glVertex3f(-62,250,20);
    glVertex3f(-60,250,20);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(-60,220,-20);
    glVertex3f(-62,220,-20);
    glVertex3f(-62,220,20);
    glVertex3f(-60,220,20);
    glEnd();

    //pintu lantai 3 - kanan

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(62,220,-20);
    glVertex3f(62,250,-20);
    glVertex3f(62,250,20);
    glVertex3f(62,220,20);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(60,220,-20);
    glVertex3f(60,250,-20);
    glVertex3f(62,250,-20);
    glVertex3f(62,220,-20);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(60,220,20);
    glVertex3f(60,250,20);
    glVertex3f(62,250,20);
    glVertex3f(62,220,20);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(60,250,-20);
    glVertex3f(62,250,-20);
    glVertex3f(62,250,20);
    glVertex3f(60,250,20);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(60,220,-20);
    glVertex3f(62,220,-20);
    glVertex3f(62,220,20);
    glVertex3f(60,220,20);
    glEnd();

    //pintu lantai 3 - belakang

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-15,220,-77);
    glVertex3f(-15,250,-77);
    glVertex3f(15,250,-77);
    glVertex3f(15,220,-77);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-15,220,-75);
    glVertex3f(-15,250,-75);
    glVertex3f(-15,250,-77);
    glVertex3f(-15,220,-77);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(15,220,-77);
    glVertex3f(15,250,-77);
    glVertex3f(15,250,-75);
    glVertex3f(15,220,-75);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-15,250,-75);
    glVertex3f(-15,250,-77);
    glVertex3f(15,250,-77);
    glVertex3f(15,250,-75);
    glEnd();

        //pintu lantai 4 - depan

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-15,305,62);
    glVertex3f(-15,350,62);
    glVertex3f(15,350,62);
    glVertex3f(15,305,62);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-15,305,60);
    glVertex3f(-15,350,60);
    glVertex3f(-15,350,62);
    glVertex3f(-15,305,62);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(15,305,62);
    glVertex3f(15,350,62);
    glVertex3f(15,350,60);
    glVertex3f(15,305,60);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-15,350,60);
    glVertex3f(-15,350,62);
    glVertex3f(15,350,62);
    glVertex3f(15,350,60);
    glEnd();

    //pintu lantai 4 - kiri

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-67,305,-20);
    glVertex3f(-67,350,-20);
    glVertex3f(-67,350,20);
    glVertex3f(-67,305,20);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-65,305,-20);
    glVertex3f(-65,350,-20);
    glVertex3f(-67,350,-20);
    glVertex3f(-67,305,-20);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-65,305,20);
    glVertex3f(-65,350,20);
    glVertex3f(-67,350,20);
    glVertex3f(-67,305,20);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-65,350,-20);
    glVertex3f(-67,350,-20);
    glVertex3f(-67,350,20);
    glVertex3f(-65,350,20);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(-65,305,-20);
    glVertex3f(-67,305,-20);
    glVertex3f(-67,305,20);
    glVertex3f(-65,305,20);
    glEnd();

    //pintu lantai 4 - kanan

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(67,305,-20);
    glVertex3f(67,350,-20);
    glVertex3f(67,350,20);
    glVertex3f(67,305,20);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(65,305,-20);
    glVertex3f(65,350,-20);
    glVertex3f(67,350,-20);
    glVertex3f(67,305,-20);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(65,305,20);
    glVertex3f(65,350,20);
    glVertex3f(67,350,20);
    glVertex3f(67,305,20);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(65,350,-20);
    glVertex3f(67,350,-20);
    glVertex3f(67,350,20);
    glVertex3f(65,350,20);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(65,305,-20);
    glVertex3f(67,305,-20);
    glVertex3f(67,305,20);
    glVertex3f(65,305,20);
    glEnd();

    //pintu lantai 4 - belakang

    glBegin(GL_POLYGON);//depan
    glColor3ub(214, 181, 167);
    glVertex3f(-15,305,-62);
    glVertex3f(-15,350,-62);
    glVertex3f(15,350,-62);
    glVertex3f(15,305,-62);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glColor3ub(148, 127, 118);
    glVertex3f(-15,305,-60);
    glVertex3f(-15,350,-60);
    glVertex3f(-15,350,-62);
    glVertex3f(-15,305,-62);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(15,305,-62);
    glVertex3f(15,350,-62);
    glVertex3f(15,350,-60);
    glVertex3f(15,305,-60);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glVertex3f(-15,350,-60);
    glVertex3f(-15,350,-62);
    glVertex3f(15,350,-62);
    glVertex3f(15,350,-60);
    glEnd();

}

void detaildepanlt1(void){

	glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(18,-100,25);//depan kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(38,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(42,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-115,0,0);//depan kiri
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-40,0,0);//depan kiri
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-40,0,0);//depan kiri
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	glPopMatrix();

	//kiriatas
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-100, 75, 105);
    glVertex3f(-100, 70, 105);
    glVertex3f(-15, 70, 105);
    glVertex3f(-15, 75, 105);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-100, 75, 100);
    glVertex3f(-100, 75, 105);
    glVertex3f(-15, 75, 105);
    glVertex3f(-15, 75, 100);
    glEnd();


    glBegin(GL_POLYGON);//depan kiri - bawah
    glVertex3f(-15, 70, 100);
    glVertex3f(-100, 70, 100);
    glVertex3f(-100, 70, 105);
    glVertex3f(-15, 70, 105);
    glEnd();

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - kanan
    glVertex3f(-15, 70, 105);
    glVertex3f(-15, 75, 105);
    glVertex3f(-15, 75, 100);
    glVertex3f(-15, 70, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-100, 70, 100);
    glVertex3f(-100, 75, 100);
    glVertex3f(-100, 75, 105);
    glVertex3f(-100, 70, 105);
    glEnd();

    //kiri bawah
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-100, 50, 105);
    glVertex3f(-100, 45, 105);
    glVertex3f(-15, 45, 105);
    glVertex3f(-15, 50, 105);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-100, 50, 100);
    glVertex3f(-100, 50, 105);
    glVertex3f(-15, 50, 105);
    glVertex3f(-15, 50, 100);
    glEnd();


    glBegin(GL_POLYGON);//depan kiri - bawah
    glVertex3f(-15, 45, 100);
    glVertex3f(-100, 45, 100);
    glVertex3f(-100, 45, 105);
    glVertex3f(-15, 45, 105);
    glEnd();

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - kanan
    glVertex3f(-15, 45, 105);
    glVertex3f(-15, 50, 105);
    glVertex3f(-15, 50, 100);
    glVertex3f(-15, 45, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-100, 45, 100);
    glVertex3f(-100, 50, 100);
    glVertex3f(-100, 50, 105);
    glVertex3f(-100, 45, 105);
    glEnd();


    //kanan atas

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kanan - depan
    glVertex3f(100, 75, 105);
    glVertex3f(100, 70, 105);
    glVertex3f(15, 70, 105);
    glVertex3f(15, 75, 105);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan - atas
    glColor3ub(184, 73, 0);
    glVertex3f(100, 75, 100);
    glVertex3f(100, 75, 105);
    glVertex3f(15, 75, 105);
    glVertex3f(15, 75, 100);
    glEnd();


    glBegin(GL_POLYGON);//depan kanan - bawah
    glVertex3f(15, 70, 100);
    glVertex3f(100, 70, 100);
    glVertex3f(100, 70, 105);
    glVertex3f(15, 70, 105);
    glEnd();

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kanan - kanan
    glVertex3f(15, 70, 105);
    glVertex3f(15, 75, 105);
    glVertex3f(15, 75, 100);
    glVertex3f(15, 70, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan - kiri
    glVertex3f(100, 70, 100);
    glVertex3f(100, 75, 100);
    glVertex3f(100, 75, 105);
    glVertex3f(100, 70, 105);
    glEnd();

    //kanan bawah

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(100, 50, 105);
    glVertex3f(100, 45, 105);
    glVertex3f(15, 45, 105);
    glVertex3f(15, 50, 105);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(100, 50, 100);
    glVertex3f(100, 50, 105);
    glVertex3f(15, 50, 105);
    glVertex3f(15, 50, 100);
    glEnd();


    glBegin(GL_POLYGON);//depan kiri - bawah
    glVertex3f(15, 45, 100);
    glVertex3f(100, 45, 100);
    glVertex3f(100, 45, 105);
    glVertex3f(15, 45, 105);
    glEnd();

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - kanan
    glVertex3f(15, 45, 105);
    glVertex3f(15, 50, 105);
    glVertex3f(15, 50, 100);
    glVertex3f(15, 45, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(100, 45, 100);
    glVertex3f(100, 50, 100);
    glVertex3f(100, 50, 105);
    glVertex3f(100, 45, 105);
    glEnd();
}

void detailbelakanglt1(void){

	glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(18,100,25);//belakang kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(38,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(42,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-115,0,0);//belakang kiri
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-35,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-45,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	glPopMatrix();

	//atas
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//belakang - depan
    glVertex3f(-100, 75, -105);
    glVertex3f(-100, 70, -105);
    glVertex3f(100, 70, -105);
    glVertex3f(100, 75, -105);
    glEnd();

    glBegin(GL_POLYGON);//belakang - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-100, 75, -100);
    glVertex3f(-100, 75, -105);
    glVertex3f(100, 75, -105);
    glVertex3f(100, 75, -100);
    glEnd();


    glBegin(GL_POLYGON);//belakang - bawah
    glVertex3f(100, 70, -100);
    glVertex3f(-100, 70, -100);
    glVertex3f(-100, 70, -105);
    glVertex3f(100, 70, -105);
    glEnd();

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//belakang - kanan
    glVertex3f(100, 70, -105);
    glVertex3f(100, 75, -105);
    glVertex3f(100, 75, -100);
    glVertex3f(100, 70, -100);
    glEnd();

    glBegin(GL_POLYGON);//belakang - kiri
    glVertex3f(-100, 70, -100);
    glVertex3f(-100, 75, -100);
    glVertex3f(-100, 75, -105);
    glVertex3f(-100, 70, -105);
    glEnd();

    //bawah

    //atas
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//belakang - depan
    glVertex3f(-100, 50, -105);
    glVertex3f(-100, 45, -105);
    glVertex3f(100, 45, -105);
    glVertex3f(100, 50, -105);
    glEnd();

    glBegin(GL_POLYGON);//belakang - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-100, 50, -100);
    glVertex3f(-100, 50, -105);
    glVertex3f(100, 50, -105);
    glVertex3f(100, 50, -100);
    glEnd();


    glBegin(GL_POLYGON);//belakang - bawah
    glVertex3f(100, 45, -100);
    glVertex3f(-100, 45, -100);
    glVertex3f(-100, 45, -105);
    glVertex3f(100, 45, -105);
    glEnd();

    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//belakang - kanan
    glVertex3f(100, 45, -105);
    glVertex3f(100, 50, -105);
    glVertex3f(100, 50, -100);
    glVertex3f(100, 45, -100);
    glEnd();

    glBegin(GL_POLYGON);//belakang - kiri
    glVertex3f(-100, 45, -100);
    glVertex3f(-100, 50, -100);
    glVertex3f(-100, 50, -105);
    glVertex3f(-100, 45, -105);
    glEnd();
}

void detailkananlt1(void){

	glPushMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(100,-60,25);
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(0,40,0);
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(0,42,0);
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(0,40,0);
    gluCylinder(pObj, 3, 3, 80, 30, 30);
	glPopMatrix();

	glColor3ub(227, 96, 20);
    //atas
    glBegin(GL_POLYGON);//depan
    glVertex3f(105,70,-105);
    glVertex3f(105,75,-105);
    glVertex3f(105,75,105);
    glVertex3f(105,70,105);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(100,70,-105);
    glVertex3f(100,75,-105);
    glVertex3f(105,75,-105);
    glVertex3f(105,70,-105);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(100,70,105);
    glVertex3f(100,75,105);
    glVertex3f(105,75,105);
    glVertex3f(105,70,105);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(100,75,-105);
    glVertex3f(105,75,-105);
    glVertex3f(105,75,105);
    glVertex3f(100,75,105);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(100,70,-105);
    glVertex3f(105,70,-105);
    glVertex3f(105,70,105);
    glVertex3f(100,70,105);
    glEnd();


    //bawah
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan
    glVertex3f(105,45,-105);
    glVertex3f(105,50,-105);
    glVertex3f(105,50,105);
    glVertex3f(105,45,105);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(100,45,-105);
    glVertex3f(100,50,-105);
    glVertex3f(105,50,-105);
    glVertex3f(105,45,-105);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(100,45,105);
    glVertex3f(100,50,105);
    glVertex3f(105,50,105);
    glVertex3f(105,45,105);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(100,50,-105);
    glVertex3f(105,50,-105);
    glVertex3f(105,50,105);
    glVertex3f(100,50,105);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(100,45,-105);
    glVertex3f(105,45,-105);
    glVertex3f(105,45,105);
    glVertex3f(100,45,105);
    glEnd();
}

void detailkirilt1(void){

	glPushMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-100,-60,25);
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(0,40,0);
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(0,42,0);
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(0,40,0);
    gluCylinder(pObj, 3, 3, 80, 30, 30);
	glPopMatrix();

	 glColor3ub(227, 96, 20);
    //atas
    glBegin(GL_POLYGON);//depan
    glVertex3f(-105,70,-105);
    glVertex3f(-105,75,-105);
    glVertex3f(-105,75,105);
    glVertex3f(-105,70,105);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(-100,70,-105);
    glVertex3f(-100,75,-105);
    glVertex3f(-105,75,-105);
    glVertex3f(-105,70,-105);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-100,70,105);
    glVertex3f(-100,75,105);
    glVertex3f(-105,75,105);
    glVertex3f(-105,70,105);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(-100,75,-105);
    glVertex3f(-105,75,-105);
    glVertex3f(-105,75,105);
    glVertex3f(-100,75,105);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(-100,70,-105);
    glVertex3f(-105,70,-105);
    glVertex3f(-105,70,105);
    glVertex3f(-100,70,105);
    glEnd();

    //bawah
    glBegin(GL_POLYGON);//depan
    glColor3ub(227, 96, 20);
    glVertex3f(-105,45,-105);
    glVertex3f(-105,50,-105);
    glVertex3f(-105,50,105);
    glVertex3f(-105,45,105);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(-100,45,-105);
    glVertex3f(-100,50,-105);
    glVertex3f(-105,50,-105);
    glVertex3f(-105,45,-105);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-100,45,105);
    glVertex3f(-100,50,105);
    glVertex3f(-105,50,105);
    glVertex3f(-105,45,105);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(-100,50,-105);
    glVertex3f(-105,50,-105);
    glVertex3f(-105,50,105);
    glVertex3f(-100,50,105);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glVertex3f(-100,45,-105);
    glVertex3f(-105,45,-105);
    glVertex3f(-105,45,105);
    glVertex3f(-100,45,105);
    glEnd();
}

void detaildepanlt2(void){

	glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(28,-100,115);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(50,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-106,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-50,0,0);//depan kiri
	gluCylinder(pObj, 3, 3, 60, 30, 30);
	glPopMatrix();

    //tengah
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-80, 177, 103);
    glVertex3f(-80, 172, 103);
    glVertex3f(80, 172, 103);
    glVertex3f(80, 177, 103);
    glEnd();
    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 177, 100);
    glVertex3f(-80, 177, 103);
    glVertex3f(80, 177, 103);
    glVertex3f(80, 177, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-80, 172, 103);
    glVertex3f(-80, 177, 103);
    glVertex3f(-80, 177, 100);
    glVertex3f(-80, 172, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kanan
     glVertex3f(80, 172, 100);
    glVertex3f(80, 177, 100);
    glVertex3f(80, 177, 103);
    glVertex3f(80, 172, 103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 172, 100);
    glVertex3f(-80, 172, 103);
    glVertex3f(80, 172, 103);
    glVertex3f(80, 172, 100);
    glEnd();

    //atas
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-80, 185, 103);
    glVertex3f(-80, 180, 103);
    glVertex3f(80, 180, 103);
    glVertex3f(80, 185, 103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 185, 100);
    glVertex3f(-80, 185, 103);
    glVertex3f(80, 185, 103);
    glVertex3f(80, 185, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-80, 180, 103);
    glVertex3f(-80, 185, 103);
    glVertex3f(-80, 185, 100);
    glVertex3f(-80, 180 ,100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kanan
    glVertex3f(80, 180, 100);
    glVertex3f(80, 185, 100);
    glVertex3f(80, 185, 103);
    glVertex3f(80, 180, 103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 180, 100);
    glVertex3f(-80, 180, 103);
    glVertex3f(80, 180, 103);
    glVertex3f(80, 180, 100);
    glEnd();

    //bawah kiri
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-80, 145, 103);
    glVertex3f(-80, 140, 103);
    glVertex3f(-30, 140, 103);
    glVertex3f(-30, 145, 103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 145, 100);
    glVertex3f(-80, 145, 103);
    glVertex3f(-30, 145, 103);
    glVertex3f(-30, 145, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-80, 140, 103);
    glVertex3f(-80, 145, 103);
    glVertex3f(-80, 145, 100);
    glVertex3f(-80, 140 ,100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kanan
    glVertex3f(-30, 140, 100);
    glVertex3f(-30, 145, 100);
    glVertex3f(-30, 145, 103);
    glVertex3f(-30, 140, 103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 140, 100);
    glVertex3f(-80, 140, 103);
    glVertex3f(-30, 140, 103);
    glVertex3f(-30, 140, 100);
    glEnd();

      //bawah kanan
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kanan - depan
    glVertex3f(30, 145, 103);
    glVertex3f(30, 140, 103);
    glVertex3f(80, 140, 103);
    glVertex3f(80, 145, 103);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan- atas
    glColor3ub(184, 73, 0);
    glVertex3f(30, 145, 100);
    glVertex3f(30, 145, 103);
    glVertex3f(80, 145, 103);
    glVertex3f(80, 145, 100);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan- kiri
    glVertex3f(30, 140, 103);
    glVertex3f(30, 145, 103);
    glVertex3f(30, 145, 100);
    glVertex3f(30, 140 ,100);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan - kanan
    glVertex3f(80, 140, 100);
    glVertex3f(80, 145, 100);
    glVertex3f(80, 145, 103);
    glVertex3f(80, 140, 103);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(30, 140, 100);
    glVertex3f(30, 140, 103);
    glVertex3f(80, 140, 103);
    glVertex3f(80, 140, 100);
    glEnd();

    //jendela
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//depan kanan
    glVertex3f(32, 170, 101);
    glVertex3f(32, 147, 101);
    glVertex3f(74, 147, 101);
    glVertex3f(74, 170, 101);
    glEnd();

    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//depan kiri
    glVertex3f(-32, 170, 101);
    glVertex3f(-32, 147, 101);
    glVertex3f(-74, 147, 101);
    glVertex3f(-74, 170, 101);
    glEnd();

    //jendela
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//belakang kanan
    glVertex3f(32, 170, -101);
    glVertex3f(32, 147, -101);
    glVertex3f(74, 147, -101);
    glVertex3f(74, 170, -101);
    glEnd();

    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//belakang kiri
    glVertex3f(-32, 170, -101);
    glVertex3f(-32, 147, -101);
    glVertex3f(-74, 147, -101);
    glVertex3f(-74, 170, -101);
    glEnd();

}

void detailbelakanglt2(void){

	glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(28,100,115);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(50,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-106,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-50,0,0);//depan kiri
	gluCylinder(pObj, 3, 3, 60, 30, 30);
	glPopMatrix();

	//tengah
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-80, 177, -103);
    glVertex3f(-80, 172, -103);
    glVertex3f(80, 172, -103);
    glVertex3f(80, 177, -103);
    glEnd();
    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 177, -100);
    glVertex3f(-80, 177, -103);
    glVertex3f(80, 177, -103);
    glVertex3f(80, 177, -100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-80, 172, -103);
    glVertex3f(-80, 177, -103);
    glVertex3f(-80, 177, -100);
    glVertex3f(-80, 172, -100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kanan
     glVertex3f(80, 172, -100);
    glVertex3f(80, 177, -100);
    glVertex3f(80, 177, -103);
    glVertex3f(80, 172, -103);
    glEnd();

      glBegin(GL_POLYGON);//depan kiri - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 172, -100);
    glVertex3f(-80, 172, -103);
    glVertex3f(80, 172, -103);
    glVertex3f(80, 172, -100);
    glEnd();

    //atas
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-80, 185, -103);
    glVertex3f(-80, 180, -103);
    glVertex3f(80, 180, -103);
    glVertex3f(80, 185, -103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 185, -100);
    glVertex3f(-80, 185, -103);
    glVertex3f(80, 185, -103);
    glVertex3f(80, 185, -100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-80, 180, -103);
    glVertex3f(-80, 185, -103);
    glVertex3f(-80, 185, -100);
    glVertex3f(-80, 180 ,-100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kanan
    glVertex3f(80, 180, -100);
    glVertex3f(80, 185, -100);
    glVertex3f(80, 185, -103);
    glVertex3f(80, 180, -103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 180, -100);
    glVertex3f(-80, 180, -103);
    glVertex3f(80, 180, -103);
    glVertex3f(80, 180, -100);
    glEnd();

    //bawah kiri
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kiri - depan
    glVertex3f(-80, 145, -103);
    glVertex3f(-80, 140, -103);
    glVertex3f(-30, 140, -103);
    glVertex3f(-30, 145, -103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 145, -100);
    glVertex3f(-80, 145, -103);
    glVertex3f(-30, 145, -103);
    glVertex3f(-30, 145, -100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kiri
    glVertex3f(-80, 140, -103);
    glVertex3f(-80, 145, -103);
    glVertex3f(-80, 145, -100);
    glVertex3f(-80, 140 ,-100);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - kanan
    glVertex3f(-30, 140, -100);
    glVertex3f(-30, 145, -100);
    glVertex3f(-30, 145, -103);
    glVertex3f(-30, 140,-103);
    glEnd();

    glBegin(GL_POLYGON);//depan kiri - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80, 140, -100);
    glVertex3f(-80, 140, -103);
    glVertex3f(-30, 140, -103);
    glVertex3f(-30, 140, -100);
    glEnd();

      //bawah kanan
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan kanan - depan
    glVertex3f(30, 145, -103);
    glVertex3f(30, 140, -103);
    glVertex3f(80, 140, -103);
    glVertex3f(80, 145, -103);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan- atas
    glColor3ub(184, 73, 0);
    glVertex3f(30, 145, -100);
    glVertex3f(30, 145, -103);
    glVertex3f(80, 145, -103);
    glVertex3f(80, 145, -100);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan- kiri
    glVertex3f(30, 140, -103);
    glVertex3f(30, 145, -103);
    glVertex3f(30, 145, -100);
    glVertex3f(30, 140 ,-100);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan - kanan
    glVertex3f(80, 140, -100);
    glVertex3f(80, 145, -100);
    glVertex3f(80, 145, -103);
    glVertex3f(80, 140, -103);
    glEnd();

    glBegin(GL_POLYGON);//depan kanan - bawah
    glColor3ub(184, 73, 0);
    glVertex3f(30, 140, -100);
    glVertex3f(30, 140, -103);
    glVertex3f(80, 140, -103);
    glVertex3f(80, 140, -100);
    glEnd();
}

void detailkananlt2(void){

	glPushMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(80,-23,115);
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(0,46,0);
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	glPopMatrix();


	//atas
    glBegin(GL_POLYGON);//depan
    glColor3ub(227, 96, 20);
    glVertex3f(83,180,-103);
    glVertex3f(83,185,-103);
    glVertex3f(83,185,103);
    glVertex3f(83,180,103);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(80,180,103);
    glVertex3f(80,185,103);
    glVertex3f(83,185,103);
    glVertex3f(83,180,103);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(80,180,-103);
    glVertex3f(80,185,-103);
    glVertex3f(83,185,-103);
    glVertex3f(83,180,-103);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(80,185,-103);
    glVertex3f(83,185,-103);
    glVertex3f(83,185,103);
    glVertex3f(80,185,103);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(80,180,-103);
    glVertex3f(83,180,-103);
    glVertex3f(83,180,103);
    glVertex3f(80,180,103);
    glEnd();

    //tengah
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan
    glVertex3f(83,172,-103);
    glVertex3f(83,177,-103);
    glVertex3f(83,177,103);
    glVertex3f(83,172,103);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(80,172,103);
    glVertex3f(80,177,103);
    glVertex3f(83,177,103);
    glVertex3f(83,172,103);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(80,172,-103);
    glVertex3f(80,177,-103);
    glVertex3f(83,177,-103);
    glVertex3f(83,172,-103);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(80,177,-103);
    glVertex3f(83,177,-103);
    glVertex3f(83,177,103);
    glVertex3f(80,177,103);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(80,172,-103);
    glVertex3f(83,172,-103);
    glVertex3f(83,172,103);
    glVertex3f(80,172,103);
    glEnd();

    //bawah kanan
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan
    glVertex3f(83,140,-103);
    glVertex3f(83,145,-103);
    glVertex3f(83,145,-25);
    glVertex3f(83,140,-25);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(80,140,-25);
    glVertex3f(80,145,-25);
    glVertex3f(83,145,-25);
    glVertex3f(83,140,-25);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(80,140,-103);
    glVertex3f(80,145,-103);
    glVertex3f(83,145,-103);
    glVertex3f(83,140,-103);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(80,145,-103);
    glVertex3f(83,145,-103);
    glVertex3f(83,145,-25);
    glVertex3f(80,145,-25);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(80,140,-103);
    glVertex3f(83,140,-103);
    glVertex3f(83,140,-25);
    glVertex3f(80,140,-25);
    glEnd();

    //bawah kiri
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan
    glVertex3f(83,140,25);
    glVertex3f(83,145,25);
    glVertex3f(83,145,103);
    glVertex3f(83,140,103);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(80,140,103);
    glVertex3f(80,145,103);
    glVertex3f(83,145,103);
    glVertex3f(83,140,103);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(80,140,25);
    glVertex3f(80,145,25);
    glVertex3f(83,145,25);
    glVertex3f(83,140,25);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(80,145,25);
    glVertex3f(83,145,25);
    glVertex3f(83,145,103);
    glVertex3f(80,145,103);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(80,140,25);
    glVertex3f(83,140,25);
    glVertex3f(83,140,103);
    glVertex3f(80,140,103);
    glEnd();

    //Jendela
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//kiri
    glVertex3f(81,147,35);
    glVertex3f(81,169,35);
    glVertex3f(81,169,88);
    glVertex3f(81,147,88);
    glEnd();

    //Jendela
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//kanan
    glVertex3f(81,147,-35);
    glVertex3f(81,169,-35);
    glVertex3f(81,169,-88);
    glVertex3f(81,147,-88);
    glEnd();

}

void detailkirilt2(void){

	glPushMatrix();

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-80,-23,115);
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(0,46,0);
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	glPopMatrix();


	//atas
    glBegin(GL_POLYGON);//depan
    glColor3ub(227, 96, 20);
    glVertex3f(-83,180,-103);
    glVertex3f(-83,185,-103);
    glVertex3f(-83,185,103);
    glVertex3f(-83,180,103);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(-80,180,103);
    glVertex3f(-80,185,103);
    glVertex3f(-83,185,103);
    glVertex3f(-83,180,103);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-80,180,-103);
    glVertex3f(-80,185,-103);
    glVertex3f(-83,185,-103);
    glVertex3f(-83,180,-103);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80,185,-103);
    glVertex3f(-83,185,-103);
    glVertex3f(-83,185,103);
    glVertex3f(-80,185,103);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80,180,-103);
    glVertex3f(-83,180,-103);
    glVertex3f(-83,180,103);
    glVertex3f(-80,180,103);
    glEnd();

    //tengah
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan
    glVertex3f(-83,172,-103);
    glVertex3f(-83,177,-103);
    glVertex3f(-83,177,103);
    glVertex3f(-83,172,103);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(-80,172,103);
    glVertex3f(-80,177,103);
    glVertex3f(-83,177,103);
    glVertex3f(-83,172,103);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-80,172,-103);
    glVertex3f(-80,177,-103);
    glVertex3f(-83,177,-103);
    glVertex3f(-83,172,-103);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80,177,-103);
    glVertex3f(-83,177,-103);
    glVertex3f(-83,177,103);
    glVertex3f(-80,177,103);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80,172,-103);
    glVertex3f(-83,172,-103);
    glVertex3f(-83,172,103);
    glVertex3f(-80,172,103);
    glEnd();

    //bawah kanan
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan
    glVertex3f(-83,140,-103);
    glVertex3f(-83,145,-103);
    glVertex3f(-83,145,-25);
    glVertex3f(-83,140,-25);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(-80,140,-25);
    glVertex3f(-80,145,-25);
    glVertex3f(-83,145,-25);
    glVertex3f(-83,140,-25);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-80,140,-103);
    glVertex3f(-80,145,-103);
    glVertex3f(-83,145,-103);
    glVertex3f(-83,140,-103);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80,145,-103);
    glVertex3f(-83,145,-103);
    glVertex3f(-83,145,-25);
    glVertex3f(-80,145,-25);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80,140,-103);
    glVertex3f(-83,140,-103);
    glVertex3f(-83,140,-25);
    glVertex3f(-80,140,-25);
    glEnd();

    //bawah kiri
    glColor3ub(227, 96, 20);
    glBegin(GL_POLYGON);//depan
    glVertex3f(-83,140,25);
    glVertex3f(-83,145,25);
    glVertex3f(-83,145,103);
    glVertex3f(-83,140,103);
    glEnd();

    glBegin(GL_POLYGON);//kiri
    glVertex3f(-80,140,103);
    glVertex3f(-80,145,103);
    glVertex3f(-83,145,103);
    glVertex3f(-83,140,103);
    glEnd();

    glBegin(GL_POLYGON);//kanan
    glVertex3f(-80,140,25);
    glVertex3f(-80,145,25);
    glVertex3f(-83,145,25);
    glVertex3f(-83,140,25);
    glEnd();

    glBegin(GL_POLYGON);//atas
    glColor3ub(184, 73, 0);
    glVertex3f(-80,145,25);
    glVertex3f(-83,145,25);
    glVertex3f(-83,145,103);
    glVertex3f(-80,145,103);
    glEnd();

    glBegin(GL_POLYGON);//bawah
    glColor3ub(184, 73, 0);
    glVertex3f(-80,140,25);
    glVertex3f(-83,140,25);
    glVertex3f(-83,140,103);
    glVertex3f(-80,140,103);
    glEnd();

      //Jendela
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//kiri
    glVertex3f(-81,147,35);
    glVertex3f(-81,169,35);
    glVertex3f(-81,169,88);
    glVertex3f(-81,147,88);
    glEnd();

    //Jendela
    //glTranslatef(x_geser,y_geser,z_geser);
	glColor3ub(29, 66, 39);
    glBegin(GL_POLYGON);//kanan
    glVertex3f(-81,147,-35);
    glVertex3f(-81,169,-35);
    glVertex3f(-81,169,-88);
    glVertex3f(-81,147,-88);
    glEnd();
}

void tianglt3(void){


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

	glTranslatef(40,-82,190);//depan kanan
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);
	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-75,0,-5);//depan kiri
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(100,80,5);//kanan1
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);

    glTranslatef(-130,0,-5);//kiri1
	gluCylinder(pObj, 1.5, 1.5, 90, 30, 30);
	glPopMatrix();

}

void tianglt3blkg (void){

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(40,80,210);//belakang kanan
	gluCylinder(pObj, 1.5, 1.5, 75, 30, 30);

	glTranslatef(-80,0,0);//belakang kiri
	gluCylinder(pObj, 1.5, 1.5, 75, 45, 45);
    glEnd();
    glPopMatrix();

}

void tianglt4(void){


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

	glTranslatef(40,-80,305);//depan kanan
	gluCylinder(pObj, 1.5, 1.5, 85, 30, 30);
	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-75,0,0);//depan kiri
	gluCylinder(pObj, 1.5, 1.5, 85, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(115,80,3);//kanan1
	gluCylinder(pObj, 1.5, 1.5, 75, 30, 30);

    glTranslatef(-160,0,0);//kiri1
	gluCylinder(pObj, 1.5, 1.5, 75, 30, 30);
	glPopMatrix();

}

void tianglt4blkg (void){

	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(40,80,210);//belakang kanan
	gluCylinder(pObj, 1.5, 1.5, 75, 30, 30);

	glTranslatef(-80,0,0);//belakang kiri
	gluCylinder(pObj, 1.5, 1.5, 0, 45, 45);
    glEnd();
    glPopMatrix();
}


void detaildepanlt3(void){
    glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(20,-75,220);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(40,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-80,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-40,0,0);//depan kiri
	gluCylinder(pObj, 3, 3, 60, 30, 30);
	glPopMatrix();


}

void detailbelakanglt3(void){

	glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(27,76,220);//belakang kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(30,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-85,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 60, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-30,0,0);//belakang kiri
	gluCylinder(pObj, 3, 3, 60, 30, 30);
	glPopMatrix();


}

void detaildepanlt4(void){
    glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(23,-60,305);//depan kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(39,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-85,0,0);//depan kanan
	gluCylinder(pObj, 3, 3, 80, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-40,0,0);//depan kiri
	gluCylinder(pObj, 3, 3, 80, 30, 30);
	glPopMatrix();


}

void detailbelakanglt4(void){

	glPushMatrix();


	GLUquadricObj * pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	glPushMatrix();
	glColor3ub(237, 87, 0);
	glRotated(270,1,0,0);

    //glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(28,60,302);//belakang kanan
	gluCylinder(pObj, 3, 3, 100, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(39,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 90, 30, 30);

	//glTranslatef(x_geser,y_geser,z_geser);
	glTranslatef(-100,0,0);//belakang kanan
	gluCylinder(pObj, 3, 3, 100, 30, 30);

    //glTranslatef(x_geser,y_geser,z_geser);
    glTranslatef(-30,0,0);//belakang kiri
	gluCylinder(pObj, 3, 3, 90, 30, 30);
	glPopMatrix();


}


void draw() {
    // Mulai tuliskan isi pikiranmu disini
    lantai1();

    //PAGAR LANTAI 1
    //depan kanan
    pagarkecil_depan(53,25,146, 60,25,146, 60,40,146, 53,40,146);
    pagarkecil_depan(53,25,139, 60,25,139, 60,40,139, 53,40,139);
    pagarkecil_depan(53,25,139, 53,25,146, 53,40,146, 53,40,139);
    pagarkecil_depan(60,25,139, 60,25,146, 60,40,146, 60,40,139);
    pagarkecil_depan(53,40,146, 60,40,146, 60,40,139, 53,40,139);
    //depan kiri
    pagarkecil_depan(-119.0,25.0,146, -126.0,25.0,146, -126.0,40.0,146, -119.0,40.0,146);
    pagarkecil_depan(-119.0,25.0,139, -126.0,25.0,139, -126.0,40.0,139, -119.0,40.0,139);
    pagarkecil_depan(-119.0,25.0,139, -119.0,25.0,146, -119.0,40.0,146, -119.0,40.0,139);//kiri
    pagarkecil_depan(-126.0,25.0,139, -126.0,25.0,146, -126.0,40.0,146, -126.0,40.0,139);//kanan
    pagarkecil_depan(-119.0,40.0,146, -126.0,40.0,146, -126.0,40.0,139, -119.0,40.0,139);

    pagarkecil_belakang(119.0,25.0,-146, 126.0,25.0,-146, 126.0,40.0,-146, 119.0,40.0,-146);//depam
    pagarkecil_belakang(119.0,25.0,-139, 126.0,25.0,-139, 126.0,40.0,-139, 119.0,40.0,-139);//belakang
    pagarkecil_belakang(119.0,25.0,-139, 119.0,25.0,-146, 119.0,40.0,-146, 119.0,40.0,-139);//kiri
    pagarkecil_belakang(126.0,25.0,-139, 126.0,25.0,-146, 126.0,40.0,-146, 126.0,40.0,-139);//kanan
    pagarkecil_belakang(119.0,40.0,-146, 126.0,40.0,-146, 126.0,40.0,-139, 119.0,40.0,-139);//atas

    pagarkecil_kanan(139,25,125, 146.0,25.0,125, 146.0,40.0,125, 139.0,40.0,125); //depan
    pagarkecil_kanan(139.0,25.0,118, 146.0,25.0,118, 146.0,40.0,118, 139.0,40.0,118); //belakang
    pagarkecil_kanan(139.0,25.0,118, 139.0,25.0,125, 139.0,40.0,125, 139.0,40.0,118);//kiri
    pagarkecil_kanan(146.0,25.0,118, 146.0,25.0,125, 146.0,40.0,125, 146.0,40.0,118);//kanan
    pagarkecil_kanan(139.0,40.0,125, 146.0,40.0,125, 146.0,40.0,118, 139.0,40.0,118); //atas

    pagarkecil_kiri(-137.0,25.0,125, -144.0,25.0,125, -144.0,40.0,125, -137.0,40.0,125);//depan
    pagarkecil_kiri(-137.0,25.0,118, -144.0,25.0,118, -144.0,40.0,118, -137.0,40.0,118);//belakang
    pagarkecil_kiri(-137.0,25.0,118, -137.0,25.0,125, -137.0,40.0,125, -137.0,40.0,118);//kiri
    pagarkecil_kiri(-144.0,25.0,118, -144.0,25.0,125, -144.0,40.0,125, -144.0,40.0,118);//kanan
    pagarkecil_kiri(-137.0,40.0,125, -144.0,40.0,125, -144.0,40.0,118, -137.0,40.0,118);//atas

    //pagar depan
    pagarpanjang(37.0,47.0,147, 140.0,47.0,147, 140.0,40.0,147, 37.0,40.0,147); //kanan tangga
    pagarpanjang(-37.0, 47.0, 147, -140.0, 47.0, 147, -140.0, 40.0, 147, -37.0, 40.0, 147); //kiri tangga
    //pagar kanan
    pagarpanjang(147,40,140, 147,47,140, 147,47,-140, 147,40,-140);
    //pagar kiri
    pagarpanjang(-145,47,140, -145,47,-140, -145,40,-140, -145,40,140);
    //pagarbelakang
    pagarpanjang(-138,47,-147, 140,47,-147, 140,40,-147, -138,40,-147);
    pagar_lantai1();

    //PAGAR LANTAI 2
    pagarlantai2depankanan();
    pagarlantai2depankiri();
    pagarlantai2belakangkanan();
    pagarlantai2belakangkiri();
    pagarkecil_depanLT2(115,-125,110);
    pagarkecil_kiriLT2(-115,-125,110);
    pagarkecil_belakangLT2(-115,125,110);
    pagarkecil_kananLT2(115,-125,110);
    //PAGAR LANTAI 3
    pagarlantai3depankanan();
    pagarlantai3depankiri();
    pagarlantai3belakangkanan();
    pagarlantai3belakangkiri();
    pagarkecil_depanLT3(70,-85,220);
    pagarkecil_kiriLT3(-70,-85,220);
    pagarkecil_belakangLT3(-70,85,220);
    pagarkecil_kananLT3(70,-85,220);
    //PAGAR LANTAI 4
    pagarlantai4depankanan();
    pagarlantai4depankiri();
    pagarlantai4belakangkanan();
    pagarlantai4belakangkiri();
    pagarkecil_depanLT4(75,-75,307.5);
    pagarkecil_kiriLT4(-75,-75,307.5);
    pagarkecil_belakangLT4(-75,75,307.5);
    pagarkecil_kananLT4(75,-75,307.5);

    tiang();
    tiang1();
    tiang2();
    tiang3();
    tianglt3();
    tianglt3blkg();
    tianglt4();
    tianglt4blkg;
    detaildepanlt1();
    detailbelakanglt1();
    detailkananlt1();
    detailkirilt1();
    detaildepanlt2();
    detailbelakanglt2();
    detailkananlt2();
    detailkirilt2();
    detaildepanlt3();
    detailbelakanglt3();
    detaildepanlt4();
    detailbelakanglt4();
    atap();
    atap2();
    atap3();
    puncak1();
    tiangpuncak();
    tiangpuncak2();

    sambunganlt();
    sambunganlt2();
    sambunganlt3();
    sambunganlt4satu();
    sambunganlt4dua();
    sambunganlt4tiga();

    bangunlt1();
    bangunlt2();
    bangunlt3();
    bangunlt4();
    bangunpuncak();

    lantai2();
    lantai3();
    lantai4();

    tangga();
    pegangantangga();

    //detail
    pintu();

    ground();
    cout << "X_GESER = " <<x_geser<< " Y_GESER = " << y_geser << "  Z_GESER = " << z_geser << endl;
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y){
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera(){
    if (motion.Forward){
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward){
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left){
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right){
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik){
        terbang -= 2.0;
    }
    if (motion.Turun){
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 10;
        break;
    case '4':
        x_geser -= 10;
        break;
    case '8':
        y_geser += 10;
        break;
    case '2':
        y_geser -= 10;
        break;
    case '9':
        z_geser -= 10;
        break;
    case '1':
        z_geser += 10;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y){
    switch (key){
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 2");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}
