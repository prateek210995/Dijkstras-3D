#include<unistd.h>                                      
#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
#define MAX 25
using namespace std;
int n,i=1,a[25],b[25],cost[25][25],tree[25][25],src,l[2],dist[10];
char s[20],*s1;
void *currentfont;

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
 
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}
//FUNCTION TO SELECT BITMAP FONT
void setFont(void *font)
{
     currentfont=font;
}
//FUNCTION TO DRAW BITMAP string at (x,y)
void drawstring(GLfloat x,GLfloat y,char *string)
{
   char *c;
   glRasterPos2f(x,y);

   for(c=string;*c!='\0';*c++)
   {
                              glutBitmapCharacter(currentfont,*c);
   }
}

//FUNCTION TO DELAY
void delay()
{
     for(int i=0;i<12000;i++)
        for(int j=0;j<12000;j++);
}
//DISPLAY FUNCTION FOR TITLE PAGE
void title()
{
     glLineWidth(3.0);
     glColor3f(1.0,1.0,0.0);
     glBegin(GL_LINE_LOOP);
                           glVertex2f(10,10);
                           glVertex2f(10,490);
                           glVertex2f(490,490);
                           glVertex2f(490,10);
     glEnd();
     
     setFont(GLUT_BITMAP_HELVETICA_18);
     glColor3f(1.0,1.0,1.0);
     drawstring(100,440,"Topic: Dijktra's Algorithm");
     
     //delay();

     glColor3f(1.0,1.0,1.0);
     drawstring(100,400,"Submitted by");

     //delay();
     
     glColor3f(0.0,1.0,0.0);
     drawstring(100,360,"Pavan Kumar M ");
     drawstring(100,340,"Prateek T C ");
     
     //delay();
     
     glColor3f(0.0,1.0,0.0);
     drawstring(100,320,"VI CSE B");
     //delay();

     glColor3f(0.0,1.0,0.0);
     drawstring(100,280,"1JS14CS063");
     drawstring(100,260,"1JS14CS066");
    
     //delay();
     glColor3f(1.0,1.0,1.0);
     drawstring(100,100,"Right click in My Window for options");
glFlush();
}
//DISPLAY FUNCTION FOR INITIALIZING (DRAWING) THE  INPUT AND OUTPUT AREAS
void initial()
{
     glClear(GL_COLOR_BUFFER_BIT);
     
     setFont(GLUT_BITMAP_HELVETICA_18);

     glColor3f(0.0,0.0,0.0);
     drawstring(20,230,"Input Area");
     drawstring(20,470,"Output Area");
     
     glColor3f(0.0,0.0,0.0);
     glLineWidth(3.0);
     glBegin(GL_LINES);
                           glVertex2f(10,10);
                           glVertex2f(10,490);
                           
                           glVertex2f(10,490);
                           glVertex2f(490,490);
                           
                           glVertex2f(490,490);
                           glVertex2f(490,10);
                           
                           glVertex2f(490,10);
                           glVertex2f(10,10);
                           
                           glVertex2f(10,250);
                           glVertex2f(490,250);
     glEnd();
     glFlush();
}

//BLANK DISPLAY FUNCTION
void display (void)
{

     glFlush();

}

//DRAW A BITMAP NUMBER i at (x,y)
void raster(int x,int y,int i)
{
     char z=i+'0';
     glRasterPos2f(x-5,y-5);
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,z);
}


//DRAW THE NODES (SQUARES) 
void drawSquare(int x, int y)
{

     if(i<=n)
     {
             y = 500-y;                              //Convert from screen coordinates
             glPointSize(40);
             
             if(i==src)
                       glColor3f(0.7f, 0.4f, 0.0f);
             else
                       glColor3f(0.5f, 0.5f, 0.8f);
             
             glBegin(GL_POINTS);
                                glVertex2f(x , y);
             glEnd();
             
             a[i]=x;
             b[i]=y;
             
             glColor3f(0.0f, 1.0f, 0.0f);
             s1=itoa(i,s,10);
             drawstring(x-5,y-5,s1);
             
             glFlush();
    }
    i=i+1;
}

//READ DATA: |V|,COST MATRIX, SOURCE VERTEX
void read()
{
     printf("Enter the number of vertices\n");
     scanf("%d",&n);
     printf("Enter the cost matrix\n");
     for(int j=1;j<=n;j++)
             for(int k=1;k<=n;k++)
             {
                     scanf("%d",&cost[j][k]);
                     if(cost[j][k]==0)
                                      cost[j][k]=999;
             }
      
      printf("Enter the source\n");
      scanf("%d",&src);
      
      printf("\nGO TO MY WINDOW AND CLICK RIGHT BUTTON FOR NEXT OPTION\n");	
      initial(); //Draw the initial screen
}

//DRAW THE EDGES
void drawline()
{
   int j,k,x1,x2,y1,y2;
   for(j=1;j<=n;j++)
   {
    for(k=1;k<=n;k++)
    {
     if(cost[j][k]!=999 && j<k)
     {
      x1=a[j];
      y1=b[j];
      x2=a[k];
      y2=b[k];
     

      glColor3f(0.0,0.5,0.0);
     
      glLineWidth(3);
      glBegin(GL_LINES);
                       glVertex2i(x1-7,y1+10);
                       glVertex2i(x2-7,y2+10);
      glEnd();
     
      s1=itoa(cost[j][k],s,10);
      drawstring((x1+x2-16)/2,(y1+y2+22)/2,s1);
      glFlush();
     }
     
     if(cost[j][k]!=cost[k][j] && cost[j][k]!=999 && j>k)
     {
      x1=a[j];
      y1=b[j];
      x2=a[k];
      y2=b[k];
      
      glColor3f(1.0,0.5,0.0);
      glBegin(GL_LINES);
                        glVertex2i(x1+10,y1+18);
                        glVertex2i(x2+10,y2+18);
      glEnd();

      s1=itoa(cost[j][k],s,10);
      drawstring((x1+x2+20)/2,(y1+y2+36)/2,s1);
      glFlush();	
     }
    }
   }
}


void shortestpath()
{

     //START OF DIJIKSTRA's
     int w,j,u,v,k,p,q,x1,y1,x2,y2,x,y;
     int dist[MAX],visit[MAX],parent[MAX],mincost,min;
     for(w=1;w<=n;w++)
     {
                      visit[w]=0;
                      dist[w]=cost[src][w];
                      parent[w]=src;
     }
     
     visit[src]=1;
     mincost=0;
     k=1;
     
     for(w=1;w<n;w++)
     {
                     min=999;
                     u=-1;
                     
                     for(j=1;j<=n;j++)
                     {
                                      if(!visit[j]&&dist[j]<min)
                                      {
                                                                min=dist[j];
                                                                u=j;
                                      }
                     }
                     
                     visit[u]=1;
                     mincost=mincost+dist[u];

                     tree[k][1]=parent[u];
                     tree[k++][2]=u;

                     for(v=1;v<=n;v++)
                     {
                                      if(!visit[v]&&(cost[u][v]+dist[u]<dist[v]))
                                      {
                                                                                 dist[v]=dist[u]+cost[u][v];
                                                                                 parent[v]=u;
                                      }
                     }
     }

     printf("\nThe cost from source to other vertices are\n\n");
     for(w=1;w<=n;w++)
     {
                      if(w!=src)
                                printf("%d-->%d = %d\n",src,w,dist[w]);
     }
                     
      //END OF DIJIKSTRAS               


      for(int r=1;r<=n;r++)
      {
              x=a[r];
              y=b[r];

              glPointSize(25);
              if(r==src)
                        glColor3f(0.7f, 0.4f, 0.0f);
              else
                        glColor3f(0.5f, 0.5f, 0.8f);

              glBegin(GL_POINTS);
                                 glVertex2f(x,y+250);
              glEnd();
              
              glColor3f(0.0,1.0,0.0);
              
              s1=itoa(r,s,10);
              drawstring(x,y+250,s1);
              
              glFlush();

//}

              for(int x=1;x<n;x++)
              {
                      p=tree[x][1];
                      q=tree[x][2];
                      
                      x1=a[p];
                      y1=b[p];
                      x2=a[q];
                      y2=b[q];
                      
                      if(p<q)
                      {
                             glColor3f(0.0,0.5,0.0);
                             glBegin(GL_LINES);
                                               glVertex2i(x1,y1+250);
                                               glVertex2i(x2,y2+250);
                             glEnd();

                             s1=itoa(cost[p][q],s,10);
                             drawstring((x1+x2)/2,(y1+y2+500)/2,s1);
                      }

                      else
                      {
                             glColor3f(1.0,0.5,0.0);
                             glBegin(GL_LINES);
                                               glVertex2i(x1,y1+250);
                                               glVertex2i(x2,y2+250);
                             glEnd();

                             s1=itoa(cost[p][q],s,10);
                             drawstring((x1+x2)/2,(y1+y2+500)/2,s1);
                      }
              }
              glFlush();
      }
}


void mouse(int bin, int state , int x , int y) 
{
     if(bin==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
                                                drawSquare(x,y);

}

void top_menu(int option)
{

     switch(option)
     {
                   case 1:
                        read();
                        glutPostRedisplay();
                        break;
                   case 2:
                        drawline();
                        glutPostRedisplay();
                        break;
                   case 3:
                        shortestpath();
                        glutPostRedisplay();
                        break;
                   case 4:
                        exit(0);
     }
}


void init (void)
{
     glClearColor (1.0, 1.0, 1.0, 1.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glViewport( 0,0, 500, 500 );
     glMatrixMode( GL_PROJECTION );
     glOrtho( 0.0, 500.0, 0.0, 500.0, 1.0, -1.0 );
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glFlush();
}
void myInit1()
{
   glClearColor(0.0,0.0,0.0,0.0);
   glColor3f(0.0f,0.0f,0.0f);
   glPointSize(5.0);
   gluOrtho2D(0.0,500.0,0.0,500.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   setFont(GLUT_BITMAP_HELVETICA_18);
}


void display1(void)
{  
   glClear(GL_COLOR_BUFFER_BIT);
   title();

}
int main (int argc,char** argv)
{
    glutInit(&argc,argv);
    
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(820,100);
    glutInitWindowSize(450,450);
    glutCreateWindow("Front Sheet");
    glutDisplayFunc(display1);
    myInit1();
    
    glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("My Window");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(top_menu);
    glutAddMenuEntry("Read Cost Matrix",1);
    glutAddMenuEntry("Display Weighted Graph",2);
    glutAddMenuEntry("Display Shortest Path",3);
    glutAddMenuEntry("Exit",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    printf("\nGO TO MY WINDOW AND CLICK RIGHT BUTTON FOR NEXT OPTION\n");
    init();

    glutMainLoop();
}
