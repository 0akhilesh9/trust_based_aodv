#include<iostream>
#include "shortpath.h"

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

void drawPoint(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

int CheckBre(int x0,int y0,int xe,int ye)
{
	int incx=1,incy=1;	
	int dx=(xe-x0);
	if(dx<0)
		dx=dx*(-1);
	int dy=(ye-y0);
	if(dy<0)
		dy=dy*(-1);
	int p,i=0;
	int twody;
	int twodyminusdx;
	int x=x0,y=y0;
	if(x0>xe)
		incx=-1;
	if(y0>ye)
		incy=-1;
	if(dx==0)
		incx=0;
	if(dy==0)
		incy=0;
	//drawPoint(x,y);
	if(dx>dy)
	{
		return dx;
	}
	else 
	{
		return dy;
	}
}

int lineBre(int x0,int y0,int xe,int ye,int c,int f)
{
	int incx=1,incy=1,flag=0;	
	int dx=(xe-x0);
	if(dx<0)
		dx=dx*(-1);
	int dy=(ye-y0);
	if(dy<0)
		dy=dy*(-1);
	int p,i=0;
	int twody;
	int twodyminusdx;
	int x=x0,y=y0;
	if(x0>xe)
		incx=-1;
	if(y0>ye)
		incy=-1;
	if(dx==0)
		incx=0;
	if(dy==0)
		incy=0;
	drawPoint(x,y);
	if(dx>dy)
	{
		i=0;
		p=2*dy-dx;
		twody=2*dy;
		twodyminusdx=2*(dy-dx);
		while(i<dx && (i<c || (!f)))
		{
			x+=incx;
			if(p<0)
				p+=twody;
			else
			{
				y+=incy;
				p+=twodyminusdx;
			}
			drawPoint(x,y);
			i++;
		}
		if(i==dx){
			flag=1;
		}
	}
	else 
	{
		i=0;
		p=2*dx-dy;
		twody=2*dx;
		twodyminusdx=2*(dx-dy);
		while(i<dy && (i<c || (!f)))
		{
			y+=incy;
			if(p<0)
				p+=twody;
			else
			{
				x+=incx;
				p+=twodyminusdx;
			}
			drawPoint(x,y);
			i++;
		}
		if(i==dy){
			flag=1;
		}
	}
	if(flag==1)
		c=-20;
	return c;
}


void dij(int n,int v,int cost[max][max],int dist[max])
{
 int i,u,count,w,flag[max],min;
 for(i=0;i<n;i++)
  flag[i]=0,dist[i]=cost[v][i];
 count=2;
//cout<<"\n\n";


 while(count<=n)
 {
  min=99;
  for(w=0;w<n;w++)
   if(dist[w]<min && !flag[w]){
    min=dist[w],u=w;
//cout<<"  "<<w+1<<" ";
}
  flag[u]=1;
  count++;
  for(w=0;w<n;w++)
   if((dist[u]+cost[u][w]<dist[w]) && !flag[w])
    dist[w]=dist[u]+cost[u][w];
 }
//cout<<"\n";
}


 

