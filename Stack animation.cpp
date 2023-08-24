#include <string>
#include <sstream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
//#include <windows.h>
#include<climits>
#include <GL/glut.h>
#endif
#include <iostream>
#include<vector>
#include<stack>
using namespace std;
stack<int>mystack;
vector<int>stack_to_vector(stack<int>somestack){
    vector<int>res;
    while(!somestack.empty()){
       res.push_back(somestack.top());
       somestack.pop();
    }
    return res;
}
void display()
{
    int y = 20;                   // initial y_position
    glClearColor(0.8, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT); //clear buffers to preset values
    glPointSize(10.0);
    glColor3f(0.8, 0.8, 0.4); // color of polygon
    vector<int>data = stack_to_vector(mystack);
    glColor3f(0, 0, 0);
    glPolygonMode(GL_FRONT, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(0.78, 0.9, 1.0);
    glVertex2f(220, 10);
    glVertex2f(280, 10);
    glVertex2f(280, 400);
    glVertex2f(220, 400);
    glEnd();
    for (int j = mystack.size() ; j >= 0; j--)
    {
        glColor3f(0.8, 0.8, 0.4); // color of polygon
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POLYGON);
        glVertex2f(225, y);
        glColor3f(0.8, 0.4, 0.8);
        glVertex2f(275, y);
        glColor3f(0.4, 0.8, 0.8);
        glVertex2f(275, y + 50);
        glColor3f(0.8, 0.8, 0.8);
        glVertex2f(225, y + 50);
        glEnd();
        glRasterPos2f(115, y + 20);
        int val = data[j];
        ostringstream stream;
        stream << val;
        string s = stream.str();
            glColor3f(0, 0, 0); // color of polygon
            glRasterPos2i(240, y+20);
        for (int i = 0; i < 2; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
        }
        y += 55;
        glEnd();
    }
                    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glVertex2f(220, 10);
    glVertex2f(280, 10);
    glVertex2f(280, 400);
    glVertex2f(220, 400);
    glEnd();
    glFlush();
}
void keyboard(unsigned char key, int x, int y){
    switch (key)
    {
    case 'p' | 'P':
        cout << "Enter the element you want to push" << endl;
        int data;
        cin >> data;
        mystack.push(data);
        display();
        break;
    case 'q' | 'Q':
    {
        int dat = mystack.top();
        mystack.pop();
        if (dat == INT_MAX)
        {
            cout << "STACK UNDERFLOW" << endl;
        }
        else
        {
            cout << "Element popped is " << dat << endl;
        }
        display();
        break;
    }
    case 's' | 'S':
        cout << "Total element/s in Stack is/are: " << mystack.size() << endl;
        ;
        display();
        break;
    case 'f' | 'F':
        cout << "The front element is: " << mystack.top() << endl;
        display();
        break;
    case 'x' | 'X':
        exit(0);
    }
}
void init()
{
    glClearColor(1, 1, 1, 1);
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char *argv[]){
    int option = 1;
    while (option != 7)
    {
        cout << "\n\n<---------- MENU ---------->" << endl;
        cout << "Enter operation to be performed on Stacks: " << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Total Elements" << endl;
        cout << "5. Display" << endl;
        cout << "-1. Exit" << endl;
        cout << "Enter option (0 to exit): ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Enter the element you want to push" << endl;
            int data;
            cin >> data;
            mystack.push(data);
            break;
        case 2:{
            int dat = mystack.top();
            mystack.pop();
            if (dat == INT_MAX)
            {
                cout << "STACK UNDERFLOW" << endl;
            }
            else
            {
                cout << "Element popped is " << dat << endl;
            }
            break;
        }
        case 3:
            cout<<"Element is my stack is "<<mystack.top()<<endl;
            break;
        case 4:
            cout<<"STack::size = "<<" :: stk.size()= "<<mystack.size()<<endl;
            break;
        case 5:
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowPosition(0, 0);
            glutInitWindowSize(500, 500);
            glutCreateWindow("Stack_using_opengl_21216 ");
            glutDisplayFunc(display);
            glutKeyboardFunc(keyboard);
            glutReshapeFunc(reshape);
            init();
            glutMainLoop();
            break;
        case -1:
            cout << "Program ended successfully!" << endl;
            break;
        default:
            cout << "Program ended successfully!" << endl;
            break;
        }
    }
    return 0;
}
