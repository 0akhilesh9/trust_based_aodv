#include<gl/glut.h>
#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <iomanip>
#include "aodv without.cpp"
#include "trust without.cpp"
#define maxrreq 1000
#define tr 0
#define trs 20
#define transr -19
#define transl 19
int trusterror=0,aodverror=0;
int a=5,b=5,c=70,d1=15;
int a1=100,b1=b,c1=170,d2=d1;
int ato=1;
int p1=tr,p2=tr,p3=tr,p4=tr;
int xw=25;
char st[4][30]={"Routing Overhead","Normalized Routing Load","System Throughput","Path Optimality"};
char st1[2][30]={"AODV","TRUST"};
int w=1350,h=700,p=16;
int dispflag=0,odispflag=0;
int kk=0,qa=0,qt=0,ia=0,it=0,fa=0,ft=0;
int kk1=0,qa1=0,qt1=0,ia1=0,it1=0,fa1=0,ft1=0;
int kk2=0,qa2=0,qt2=0,ia2=0,it2=0,fa2=0,ft2=0;
int kk3=0,qa3=0,qt3=0,ia3=0,it3=0,fa3=0,ft3=0;
int trustn,trustv,trustcost[max][max],trustdist[max][max];
int n,v,cost[max][max],dist[max][max];
GLfloat xt=30,yt=1.0,zt=1.0;
int go=1,l=0,tra=0;

void mouse(int button,int state,int x,int y);

void display()
{
	int temp=0,temp1=0,temp2=0,temp3=0;
	if(go==1)
	{
	switch(dispflag){
	case 1:{
		if(ato==0) glPushMatrix();
		if(kk<soverhead)
				//delay(10);
		if(kk<soverhead){
			if((fa==1)&&(ft==1)){
				kk++;
				fa=0;
				ft=0;
				if(kk%3==0){
					p1=p1-trs;		
					if(kk*xw/5>(tra*(-1))){
						tra=p1;
						cout<<"translate1";
						glTranslatef(p1,0,0);
					}
					cout<<"P1: "<<p1<<" "<<kk*xw/5<<" "<<(tra*(-1))<<"\n";
					delay(100);				
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0,1.0,1.0,1.0);
		glColor3f(1.0,0.0,0.0);
		float mi=999,ma=0;
		float scale=1;
		for(int i=0;i<soverhead;i++){
			if(overhead[i]>ma)
				ma=overhead[i];
			if(overhead[i]<mi)
				mi=overhead[i];
		}
		for(int i=0;i<trustsoverhead;i++){
			if(trustoverhead[i]>ma)
				ma=trustoverhead[i];
			if(trustoverhead[i]<mi)
				mi=trustoverhead[i];
		}
		if(ma==mi){
			scale=(h-10)/ma;
			mi=0;
		}
		else
			scale=(h-10)/(ma-mi);
		glPointSize(1);
		ia=CheckBre(kk*xw,(overhead[kk]-mi)*scale,kk*xw+xw,(overhead[kk+1]-mi)*scale);
		it=CheckBre(kk*xw,(trustoverhead[kk]-mi)*scale,kk*xw+xw,(trustoverhead[kk+1]-mi)*scale);
		if(ia>it){
			it=1;
			ia=ia/it;
		}
		else if(ia<it){
			ia=1;
			it=it/ia;
		}
		else if(ia==it){
			ia=1;
			it=1;
		}
		for(int i=0,j=0;j<soverhead && j<=kk;i+=xw,j++){
			if(j==kk)
				temp=lineBre(i,(overhead[j]-mi)*scale,i+xw,(overhead[j+1]-mi)*scale,qa,1);
			else if(j<kk)
				temp=lineBre(i,(overhead[j]-mi)*scale,i+xw,(overhead[j+1]-mi)*scale,qa,0);
		}
		if(kk<soverhead){
			if(temp<0){
				fa=1;
				qa=0;
			}
			if(temp>=0){
				qa+=ia;
			}
		}	
		for(int i=0,j=0;j<=soverhead && j<=kk+1;i+=xw,j++){
			glPointSize(5);
			glBegin(GL_POINTS);
				glVertex2i(i,(overhead[j]-mi)*scale);
			glEnd();
		}
		glPointSize(1);
		glColor3f(0.0,0.0,1.0);
		for(int i=0,j=0;j<trustsoverhead && j<=kk;i+=xw,j++){
			if(j==kk)
				temp=lineBre(i,(trustoverhead[j]-mi)*scale,i+xw,(trustoverhead[j+1]-mi)*scale,qt,1);
			else if(j<kk)
				temp=lineBre(i,(trustoverhead[j]-mi)*scale,i+xw,(trustoverhead[j+1]-mi)*scale,qt,0);
		}
		if(kk<soverhead){
			if(temp<0){
				ft=1;
				qt=0;
			}
			if(temp>=0){
				qt+=it;
			}
		}	
		for(int i=0,j=0;j<trustsoverhead && j<=kk+1;i+=xw,j++){
			glPointSize(5);
			glColor3f(0.0,0.0,1.0);
			glBegin(GL_POINTS);
				glVertex2i(i,(trustoverhead[j]-mi)*scale);	
			glEnd();
		}
		glColor3f(0.0,0.0,0.0);
		glPushMatrix();
		glTranslatef(w-140,h-20,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st[0][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st[0][i]);
		glPopMatrix();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,h-32); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,h-35,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[0][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[0][i]);
		glPopMatrix();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,h-45); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,h-48,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[1][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[1][i]);
		glPopMatrix();
		if(ato==0) glPopMatrix();
		glutPostRedisplay();
	break;
	}
	case 2:{
		if(ato==0) glPushMatrix();
		if(kk1<snormalload)
				//delay(10);
		if(kk1<snormalload){
			if((fa1==1)&&(ft1==1)){
				kk1++;
				fa1=0;
				ft1=0;
				if(kk1%3==0){
					p2=p2-trs;
					if(kk1*xw/5>(tra*(-1))){
						tra=p2;
						cout<<"translate2";
						glTranslatef(p2,0,0);
					}
					cout<<"P2: "<<p2<<" "<<kk1*xw/5<<" "<<(tra*(-1))<<"\n";
					delay(100);
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0,1.0,1.0,1.0);
		float mi=999,ma=0;
		float scale=1;
		for(int i=0;i<snormalload;i++){
			if(normalload[i]>ma)
				ma=normalload[i];
			if(normalload[i]<mi)
				mi=normalload[i];
		}
		for(int i=0;i<trustsnormalload;i++){
			if(trustnormalload[i]>ma)
				ma=trustnormalload[i];
			if(trustnormalload[i]<mi)
				mi=trustnormalload[i];
		}
		if(ma==mi){
			scale=(h-10)/ma;
			mi=0;
		}
		else
			scale=(h-10)/(ma-mi);
		glColor3f(1.0,0.0,0.0);
		glPointSize(1);
		ia1=CheckBre(kk1*xw,(normalload[kk1]-mi)*scale,kk1*xw+xw,(normalload[kk1+1]-mi)*scale);
		it1=CheckBre(kk1*xw,(trustnormalload[kk1]-mi)*scale,kk1*xw+xw,(trustnormalload[kk1+1]-mi)*scale);
		if(ia1>it1){
			it1=1;
			ia1=ia1/it1;
		}
		else if(ia1<it1){
			ia1=1;
			it1=it1/ia1;
		}
		else if(ia1==it1){
			ia1=1;
			it1=1;
		}
		for(int i=0,j=0;j<snormalload && j<=kk1;i+=xw,j++){	
			if(j==kk1)
				temp1=lineBre(i,(normalload[j]-mi)*scale,i+xw,(normalload[j+1]-mi)*scale,qa1,1);
			else if(j<kk1)
				temp1=lineBre(i,(normalload[j]-mi)*scale,i+xw,(normalload[j+1]-mi)*scale,qa1,0);
		}
		if(kk1<snormalload){
			if(temp1<0){
				fa1=1;
				qa1=0;
			}
			if(temp1>=0){
				qa1+=ia1;
			}
		}	
		for(int i=0,j=0;j<snormalload && j<=kk1+1;i+=xw,j++){	
			glPointSize(5);
			glBegin(GL_POINTS);
				glVertex2f(i,(normalload[j]-mi)*scale);
			glEnd();
		}
		glPointSize(1);
		glColor3f(0.0,0.0,1.0);
		for(int i=0,j=0;j<trustsnormalload && j<=kk1;i+=xw,j++){
			if(j==kk1)
				temp1=lineBre(i,(trustnormalload[j]-mi)*scale,i+xw,(trustnormalload[j+1]-mi)*scale,qt1,1);
			else if(j<kk1)
				temp1=lineBre(i,(trustnormalload[j]-mi)*scale,i+xw,(trustnormalload[j+1]-mi)*scale,qt1,0);
		}
		if(kk1<snormalload){
			if(temp1<0){
				ft1=1;
				qt1=0;
			}
			if(temp1>=0){
				qt1+=it1;
			}
		}	
		for(int i=0,j=0;j<trustsnormalload && j<=kk1+1;i+=xw,j++){
			glPointSize(5);
			glColor3f(0.0,0.0,1.0);
			glBegin(GL_POINTS);
				glVertex2f(i,(trustnormalload[j]-mi)*scale);
			glEnd();
		}
		glColor3f(0.0,0.0,0.0);
		glPushMatrix();
		glTranslatef(w-195,h-20,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st[1][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st[1][i]);
		glPopMatrix();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,h-32); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,h-35,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[0][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[0][i]);
		glPopMatrix();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,h-45); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,h-48,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[1][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[1][i]);
		glPopMatrix();
		if(ato==0) glPopMatrix();
		glutPostRedisplay();
	break;
	}
	case 3:{ 
		if(ato==0) glPushMatrix();
		if(kk2<sdatasent)
				//delay(0);
		if(kk2<sdatasent){
			if((fa2==1)&&(ft2==1)){
				kk2++;
				fa2=0;
				ft2=0;
				if(kk2%3==0){
					p3=p3-trs;
					if(kk2*xw/5>(tra*(-1))){
						tra=p3;
						cout<<"translate3";
						glTranslatef(p3,0,0);
					}
					cout<<"P3: "<<p3<<" "<<kk2*xw/5<<" "<<(tra*(-1))<<"\n";
					delay(100);
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0,1.0,1.0,1.0);
		double mi=99999999,ma=0;
		float scale=1;
		for(int i=0;i<sdatasent;i++){
			if((datasent[i]/timetaken[i]*10000)>ma)
				ma=datasent[i]/timetaken[i]*10000;
			if((datasent[i]/timetaken[i]*10000)<mi)
				mi=datasent[i]/timetaken[i]*10000;
		}
		for(int i=0;i<trustsdatasent;i++){
			if(trusttimetaken[i]!=0)
				if(trustdatasent[i]/trusttimetaken[i]*10000>ma)
					ma=trustdatasent[i]/trusttimetaken[i]*10000;
			if(trusttimetaken[i]!=0)
				if(trustdatasent[i]/trusttimetaken[i]*10000<mi)
					mi=trustdatasent[i]/trusttimetaken[i]*10000;
		}
		if(ma==mi){
			scale=(h-10)/ma;
			mi=0;
		}
		else
			scale=(h-10)/(ma-mi);
		glColor3f(1.0,0.0,0.0);
		glPointSize(1);
		ia2=CheckBre(kk2*xw,(datasent[kk2]/timetaken[kk2]*10000-mi)*scale,kk2*xw+xw,(datasent[kk2+1]/timetaken[kk2+1]*10000-mi)*scale);
		it2=CheckBre(kk2*xw,(trustdatasent[kk2]/trusttimetaken[kk2]*10000-mi)*scale,kk2*xw+xw,(trustdatasent[kk2+1]/trusttimetaken[kk2]*10000-mi)*scale);
		if(ia2>it2){
			it2=1;
			ia2=ia2/it2;
		}
		else if(ia2<it2){
			ia2=1;
			it2=it2/ia2;
		}
		else if(ia2==it2){
			ia2=1;
			it2=1;
		}
		for(int i=0,j=0;j<sdatasent && j<=kk2;i+=xw,j++){
			if(j==kk2)
				temp2=lineBre(i,((datasent[j]/timetaken[j]*10000)-mi)*scale,i+xw,((datasent[j+1]/timetaken[j+1]*10000)-mi)*scale,qa2,1);
			else if(j<kk2)
				temp2=lineBre(i,((datasent[j]/timetaken[j]*10000)-mi)*scale,i+xw,((datasent[j+1]/timetaken[j+1]*10000)-mi)*scale,qa2,0);
		}
		if(kk2<sdatasent){
			if(temp2<0){
				fa2=1;
				qa2=0;
			}
			if(temp2>=0){
				qa2+=ia2;
			}
		}	
		for(int i=0,j=0;j<sdatasent && j<=kk2+1;i+=xw,j++){
			glPointSize(5);
			glBegin(GL_POINTS);
				glVertex2f(i,((datasent[j]/timetaken[j]*10000)-mi)*scale);
			glEnd();
		}
		float y1,y2;
		glPointSize(1);
		glColor3f(0.0,0.0,1.0);
		for(int i=0,j=0;j<trustsdatasent && j<=kk2;i+=xw,j++){
			if(trusttimetaken[j]!=0)
				y1=((trustdatasent[j]/trusttimetaken[j]*10000)-mi)*scale;
			else
				y1=(trustdatasent[j])*scale;
			if(trusttimetaken[j+1]!=0)
				y2=((trustdatasent[j+1]/trusttimetaken[j+1]*10000)-mi)*scale;	
			else
				y2=(trustdatasent[j+1])*scale;
			if(j==kk2)
				temp2=lineBre(i,y1,i+xw,y2,qt2,1);
			else if(j<kk2)
				temp2=lineBre(i,y1,i+xw,y2,qt2,0);
		}
		if(kk2<trustsdatasent){
			if(temp2<0){
				ft2=1;
				qt2=0;
			}
			if(temp2>=0){
				qt2+=it2;
			}
		}	
		for(int i=0,j=0;j<trustsdatasent && j<=kk2+1;i+=xw,j++){
			glPointSize(5);
			glBegin(GL_POINTS);
				if(trusttimetaken[j]!=0)
					glVertex2f(i,((trustdatasent[j]/trusttimetaken[j]*10000)-mi)*scale);
				else
					glVertex2f(i,(trustdatasent[j]*10000)*scale);
			glEnd();
		}
		glColor3f(0.0,0.0,0.0);
		glPushMatrix();
		glTranslatef(w-145,37,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st[2][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st[2][i]);
		glPopMatrix();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,24); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,21,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[0][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[0][i]);
		glPopMatrix();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,11); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,8,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[1][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[1][i]);
		glPopMatrix();
		if(ato==0) glPopMatrix();
		glutPostRedisplay();
    break;
	}
	case 4:{ 
		if(ato==0) glPushMatrix();
		if(kk3<shopsum)
				delay(0);
		if(kk3<shopsum){
			if((fa3==1)&&(ft3==1)){
				kk3++;
				fa3=0;
				ft3=0;
				if(kk3%5==0){
					p4=p4-trs;
					if(kk3*xw/5>(tra*(-1))){
						tra=p4;
						cout<<"translate";
						glTranslatef(p4,0,0);
					}
					cout<<"P4: "<<p4<<" "<<kk3*xw/5<<" "<<(tra*(-1))<<"\n";
					delay(100);
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0,1.0,1.0,1.0);
		double mi=99999999,ma=0;
		float scale=1;
		for(int i=0;i<shopsum;i++){
			if(hopsum[i]!=0){
				if(dist[source[i]][destination[i]]/hopsum[i]>ma)
					ma=dist[source[i]][destination[i]]/hopsum[i];
				if(dist[source[i]][destination[i]]/hopsum[i]<mi)
					mi=dist[source[i]][destination[i]]/hopsum[i];
			}
		}
		for(int i=0;i<trustshopsum;i++){
			if(trusthopsum[i]!=0)
				if(trustdist[trustsource[i]][trustdestination[i]]/trusthopsum[i]>ma)
					ma=trustdist[trustsource[i]][trustdestination[i]]/trusthopsum[i];
			if(trusthopsum[i]!=0)
				if(trustdist[trustsource[i]][trustdestination[i]]/trusthopsum[i]<mi)	
					mi=trustdist[trustsource[i]][trustdestination[i]]/trusthopsum[i];
		}
		if(ma==mi){
			scale=(h-10)/ma;
			mi=0;
		}
		if((ma-mi)<1)
			scale=h-10;
		else
			scale=(h-10)/(ma-mi);
		glColor3f(1.0,0.0,0.0);
		glPointSize(1);
		ia3=CheckBre(kk3*xw,(hopsum[kk3]-mi)*scale,kk3*xw+xw,(hopsum[kk3+1]-mi)*scale);
		it3=CheckBre(kk3*xw,(trusthopsum[kk3]-mi)*scale,kk3*xw+xw,(trusthopsum[kk3+1]-mi)*scale);
		if(ia3>it3){
			it3=1;
			ia3=ia3/it3;
		}
		else if(ia3<it3){
			ia3=1;
			it3=it3/ia3;
		}
		else if(ia3==it3){
			ia3=1;
			it3=1;
		}
		for(int i=0,j=0;j<shopsum && j<=kk3;i+=xw,j++){
			if(j==kk3)
				temp3=lineBre(i,((dist[source[j]][destination[j]]/hopsum[j]))*scale,i+xw,((dist[source[j+1]][destination[j+1]]/hopsum[j+1]))*scale,qa3,1);
			else if(j<kk3)
				temp3=lineBre(i,((dist[source[j]][destination[j]]/hopsum[j]))*scale,i+xw,((dist[source[j+1]][destination[j+1]]/hopsum[j+1]))*scale,qa3,0);
		}
		if(kk3<shopsum){
			if(temp3<0){
				fa3=1;
				qa3=0;
			}
			if(temp3>=0){
				qa3+=ia3;
			}
		}	
		for(int i=0,j=0;j<shopsum && j<=kk3+1;i+=xw,j++){
			glPointSize(5);
			glBegin(GL_POINTS);
				glVertex2f(i,((dist[source[j]][destination[j]]/hopsum[j]))*scale);
			glEnd();
		}
		float y1,y2;
		glPointSize(1);
		glColor3f(0.0,0.0,1.0);
		for(int i=0,j=0;j<trustshopsum && j<=kk3;i+=xw,j++){
			if(trusthopsum[j]==0)
				y1=(trusthopsum[j])*scale;
			else
				y1=((trustdist[trustsource[j]][trustdestination[j]]/trusthopsum[j]))*scale;
			if(trusthopsum[j+1]==0)
				y2=(trusthopsum[j+1])*scale;
			else
				y2=((trustdist[trustsource[j+1]][trustdestination[j+1]]/trusthopsum[j+1]))*scale;	
			if(j==kk3)
				temp3=lineBre(i,y1,i+xw,y2,qt3,1);
			else if(j<kk3)
				temp3=lineBre(i,y1,i+xw,y2,qt3,0);
		}
		if(kk3<trustshopsum){
			if(temp3<0){
				ft3=1;
				qt3=0;
			}
			if(temp3>=0){
				qt3+=it3;
			}
		}	
		for(int i=0,j=0;j<trustshopsum && j<=kk3+1;i+=xw,j++){
			glPointSize(5);
			glBegin(GL_POINTS);
				if(trusthopsum[j]==0)
					glVertex2f(i,(trusthopsum[j])*scale);
				else
					glVertex2f(i,((trustdist[trustsource[j]][trustdestination[j]]/trusthopsum[j]))*scale);
			glEnd();
		}
		glColor3f(0.0,0.0,0.0);
		glPushMatrix();
		glTranslatef(w-133,37,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st[3][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st[3][i]);
		glPopMatrix();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,24); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,21,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[0][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[0][i]);
		glPopMatrix();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
			glVertex2i(w-50,11); 
		glEnd();
		glPushMatrix();
		glTranslatef(w-45,8,0);
		scale=0.08;
		glScalef(scale,scale,scale);
		for(int i=0;st1[1][i]!='\0';i++)
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,st1[1][i]);
		glPopMatrix();
		if(ato==0) glPopMatrix();
		glutPostRedisplay();
	break;
	}
	default:{
		cout<<"else: "<<dispflag;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0,1.0,1.0,1.0);
    break;
	}
	}
	}
	if(ato==0){
		glColor3f(0.5,0.7,0.9);
		glBegin(GL_LINE_LOOP);
			glVertex2d(a,b);
			glVertex2d(a,d1);
			glVertex2d(c,d1);
			glVertex2d(c,b);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2d((a+c)/2-10,(b+d1)/2);
			glVertex2d((a+c)/2,d1);
			glVertex2d((a+c)/2,b);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex2d(a1,b1);
			glVertex2d(a1,d2);
			glVertex2d(c1,d2);
			glVertex2d(c1,b1);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2d((a1+c1)/2+10,(b1+d2)/2);
			glVertex2d((a1+c1)/2,d2);
			glVertex2d((a1+c1)/2,b1);
		glEnd();
	}
	glutSwapBuffers();
}

void CMain(int id)
 {
	 dispflag=id;
	 if(id==0)
		 exit(0);
 }

void metric(int id)
 {
	 glClearColor(1.0,1.0,1.0,1.0);
	 dispflag=id;
	 if(odispflag!=dispflag){
		  l=1;
		 glutPostRedisplay();
		 odispflag=dispflag;
	 }
 }

void myinit()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0,w,00.0,h,0.0,500.0);
}

void main(int argc,char* argv[])
{
	int i,j,ntimes;
	printf("Enter '1'-auto   '0'-manual: ");
	scanf("%d",&ato);
	freopen("outaodv.txt", "w", stdout);
	freopen("in3.txt", "r", stdin);
    for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			cin>>nodegraph[i][j];
		}
	}
	for(i=0;i<max;i++)
	{
		for(j=0;j<max;j++)
		{
			trustnodegraph[i][j]=nodegraph[i][j];
		}
	}
	freopen("in3o.txt", "r", stdin);
	cin>>times;
	ntimes=times;
    trusttimes=times;
	cout<<"No: of transmissions: "<<times<<"\n";
	while(times--)
	{	
		init();
		for(i=0;i<max;i++)
			nodep[i].read(i);
		cin>>s;
		cin>>d;
		cout<<"transmissions left: "<<times<<"Source: "<<s<<"Dest: "<<d<<"\n";
		source[++ssource]=s;
		destination[++sdestination]=d;
		cin>>ndp;
		cin>>sdp;
		cin>>bitrate;
		trustinit();
		for(i=0;i<max;i++)
			trustnodep[i].read(i);
		trusts=s;
		trustd=d;
		trustndp=ndp;
		trustsdp=sdp;
		trustbitrate=bitrate;	
		if(bitrate!=0){
			waitrreq=srreq*8/bitrate;
			waitrrep=srrep*8/bitrate;
		}
		if((s>max) ||(d>max))
		{
			cout<<"Error-node ip cannot exceed max limit(5)\n";
			done=0;
		}
		if(s==d)
		{
			cout<<"Error-source and destination cannot be same\n";
			done=0;
		}
		if((ntimes-times)>=2){
			for(i=0;i<max;i++){
				for(int k=0;k<=nodep[i].rtablep.entries;k++){
					nodep[i].rtablep.ttl[k]-=sttl;
				}
			}
			for(i=0;i<max;i++){
				for(int k=0;k<=nodep[i].rtablep.entries;k++){
					if(nodep[i].rtablep.ttl[k]<=0){
						for(int wr=k;wr<nodep[i].rtablep.entries;wr++){
							nodep[i].rtablep.destip[wr]=nodep[i].rtablep.destip[wr+1];
							nodep[i].rtablep.hopcount[wr]=nodep[i].rtablep.hopcount[wr+1];
							nodep[i].rtablep.seqno[wr]=nodep[i].rtablep.seqno[wr+1];
							nodep[i].rtablep.nexthop[wr]=nodep[i].rtablep.nexthop[wr+1];
							nodep[i].rtablep.ttl[wr]=nodep[i].rtablep.ttl[wr+1];
						}
						nodep[i].rtablep.entries--;
					}
				}
			}
			for(i=0;i<max;i++){
				for(int k=0;k<=trustnodep[i].rtablep.entries;k++){
					trustnodep[i].rtablep.ttl[k]-=sttl;
				}
			}
			for(i=0;i<max;i++){
				for(int k=0;k<=trustnodep[i].rtablep.entries;k++){
					if(trustnodep[i].rtablep.ttl[k]<=0){
						for(int wr=k;wr<trustnodep[i].rtablep.entries;wr++){
							trustnodep[i].rtablep.destip[wr]=trustnodep[i].rtablep.destip[wr+1];
							trustnodep[i].rtablep.hopcount[wr]=trustnodep[i].rtablep.hopcount[wr+1];
							trustnodep[i].rtablep.seqno[wr]=trustnodep[i].rtablep.seqno[wr+1];
							trustnodep[i].rtablep.nexthop[wr]=trustnodep[i].rtablep.nexthop[wr+1];
							trustnodep[i].rtablep.ttl[wr]=trustnodep[i].rtablep.ttl[wr+1];
						}
						trustnodep[i].rtablep.entries--;
					}
				}
			}
		}
		t1= clock();
		bid=nodep[s].ip;
		if(nodep[s].checkroute(d))
		{
			done=1;
			hopsum[++shopsum]=nodep[s].rtablep.hopcount[(nodep[s].checkroute(d))-1];
		}
		else{
			nodep[s].buildrreq(s,d,-1,bid);
			nodep[s].broadcast();
			while(flag)  //checking for complete broadcast
			{
				flag=0;
				processnodes();
				while(rflag==1)
				{
					rflag=0;
					processrrep();
				}
			}
		}
		if(done)
		{
			cout<<"aodv done\n";
			t2= clock();
			cout<<"rreq: "<<nrreq<<" rrep: "<<nrrep<<"\n";
		}
		else{
			cout<<"aodv error "<<s<<" "<<d<<"\n";
			hopsum[++shopsum]=0;
			aodverror++;
		}
		data=((nrreq*srreq)+(nrrep*srrep)+(ndp*hopsum[shopsum]*sdp)+(ndp*srack))*8;
		tdata=(ndp*hopsum[shopsum]*sdp)+(ndp*srack)*8;
		datasent[++sdatasent]=tdata;
		t=(double)(t2-t1)/CLOCKS_PER_SEC;
		if(ndp!=0)
			normalload[++snormalload]=(double)(nrreq+nrrep)/ndp;
		else
			normalload[++snormalload]=0;
		timetaken[++stimetaken]=(double)((data/bitrate)+t);
		overhead[++soverhead]=nrreq+nrrep;
		nrreq=0;
		nrrep=0;
		trustsource[++trustssource]=trusts;
		trustdestination[++trustsdestination]=trustd;
		if(trustbitrate!=0){
			trustwaitrreq=trustsrreq*8/trustbitrate;
			trustwaitrrep=trustsrrep*8/trustbitrate;
		}
		if((trusts>max) ||(trustd>max))
		{
			cout<<"Error-node ip cannot exceed max limit(5)\n";
			trustdone=0;
		}
		if(trusts==trustd)
		{
			cout<<"Error-source and destination cannot be same\n";
			trustdone=0;
		}
		trustt1= clock();
		trusts=trusts;
		trustd=trustd;
		trustbid=trustnodep[trusts].ip;
		if(trustnodep[trusts].checkroute(trustd))
		{
			trustdone=1;
			trusthopsum[++trustshopsum]=trustnodep[trusts].rtablep.hopcount[(trustnodep[trusts].checkroute(trustd))-1];
			cout<<"trust route exists\n";
		}
		else{
			trustnodep[trusts].buildrreq(trusts,trustd,-1,trustbid,deftrust);
			trustnodep[trusts].broadcast();
			while(trustflag)  //checking for complete broadcast
			{
				trustflag=0;
				trustprocessnodes();
				while(trustrflag==1)
				{
					trustrflag=0;
					trustprocessrrep();
				}
				if(trustnrreq>maxrreq){
					cout<<"Exceeded max rreq's. ";
					trustflag=0;
					break;
				}
			}
		}
		if(trustdone)
		{
			trustt2= clock();
			cout<<"trust done\n";
		}
		else{
			cout<<"trust eror\n";
			trusterror++;
		}
		if(trustdone){
			trustdata=((trustnrreq*trustsrreq)+(trustnrrep*trustsrrep)+(trustndp*trusthopsum[trustshopsum]*trustsdp)+(trustndp*trustsrack))*8;
			trusttdata=(trustndp*trusthopsum[trustshopsum]*trustsdp)+(trustndp*trustsrack)*8;
			trustdatasent[++trustsdatasent]=trusttdata;
			trustt=(double)(trustt2-trustt1)/CLOCKS_PER_SEC;
			if(trustndp!=0)
				trustnormalload[++trustsnormalload]=(double)(trustnrreq+trustnrrep)/trustndp;
			else
				trustnormalload[++trustsnormalload]=0;
			trusttimetaken[++truststimetaken]=(double)((trustdata/trustbitrate)+trustt);
			trustoverhead[++trustsoverhead]=trustnrreq+trustnrrep;
			cout<<"trreq: "<<trustnrreq<<" trrep: "<<trustnrrep<<"\n";
			trustnrreq=0;
			trustnrrep=0;
		}
		else{
			trustdata=0;
			//trustdatasent[++trustsdatasent]=trusttdata;
			trustdatasent[++trustsdatasent]=0;
			trustt=0;
			trustnormalload[++trustsnormalload]=0;
			trusttimetaken[++truststimetaken]=0;
			trustoverhead[++trustsoverhead]=0;
			trustnrreq=0;
			trustnrrep=0;
			trusthopsum[++trustshopsum]=0;
		}
	}
	n=max;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			cost[i][j]=nodegraph[i][j];
			if(nodegraph[i][j]==0)
				cost[i][j]=infinity;
		}
	for(i=0;i<n;i++)
		dij(n,i,cost,dist[i]);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(dist[j][i]>dist[i][j]){
				dist[j][i]=dist[i][j];
			}
		}
	}
	cout<<"\nRoverhead     Normalizedroutingload     Throughput     Optimality\n\n";
	for(int k=0;k<=soverhead;k++){
		cout<<k+1<<") "<<overhead[k]<<"\t\t";
		cout<<setprecision(10)<<normalload[k]<<"\t\t";
		cout<<setprecision(10)<<datasent[k]/timetaken[k]<<"\t\t";
		cout<<dist[source[k]][destination[k]]/hopsum[k]<<"\n\n";
	}
	for(int k=0;k<=trustnodep[trusts].rtablep.entries;k++){
		cout<<"dest: "<<trustnodep[trusts].rtablep.destip[k]<<"nexthop: "<<trustnodep[trusts].rtablep.nexthop[k]<<"trust: "<<setprecision(8)<<trustnodep[trusts].rtablep.trust[k]<<"\n";
	}
	trustn=max;
	for(i=0;i<trustn;i++)
		for(j=0;j<trustn;j++){
			trustcost[i][j]=trustnodegraph[i][j];
			if(trustnodegraph[i][j]==0)
				trustcost[i][j]=infinity;
		}
	for(i=0;i<trustn;i++)
		dij(trustn,i,trustcost,trustdist[i]);
	for(i=0;i<trustn;i++){
		for(j=0;j<trustn;j++){
			if(trustdist[j][i]>trustdist[i][j]){
				trustdist[j][i]=trustdist[i][j];
			}
		}
	}
	cout<<"\nRouting overhead     Normalized routing load     Throughput     Optimality\n\n";
	for(int k=0;k<=trustsoverhead;k++){
		cout<<k+1<<") "<<trustoverhead[k]<<"\t\t";
		cout<<setprecision(10)<<trustnormalload[k]<<"\t\t";
		if(trusttimetaken[k]==0)
			cout<<setprecision(10)<<trusttimetaken[k]<<"\t\t";
		else
			cout<<setprecision(10)<<trustdatasent[k]/trusttimetaken[k]<<"\t\t";
		if(trusthopsum[k]==0)
			cout<<trusthopsum[k]<<"\n\n";
		else
			cout<<trustdist[trustsource[k]][trustdestination[k]]/trusthopsum[k]<<"\n\n";
	}
	cout<<"AODV error: "<<aodverror<<"Trust error: "<<trusterror<<"\n";
	/////Graphics part/////
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w,h);
	glutInitWindowPosition(5,5);
	glutCreateWindow("Comparative Analysis");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,100,1.0);
	int sub_menu=glutCreateMenu(metric);
	glutAddMenuEntry("Routing overhead",1);
	glutAddMenuEntry("Normalized routing load",2);
	glutAddMenuEntry("System throughput",3);
	glutAddMenuEntry("Path optimality",4);
	glutCreateMenu(CMain);
    glutAddSubMenu("Metric",sub_menu);
	glutAddMenuEntry("Exit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}

void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN && (y<695 && y>686) && (x<170 && x>100) ){

		/*printf("\nhello");
		printf("\t**%d %d %d %d**\n",a,b,c,d1);
		printf("hello1");
		printf("\t**%d %d %d %d**\n",a1,b1,c1,d2);*/
		glTranslatef(transr,0,0);
		a-=transr;
		a1-=transr;
		//b-=transr;
		c-=transr;
		c1-=transr;
	//	d1-=transr;
		glutPostRedisplay();
	}
	else if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN && (y<695 && y>686) &&  (x<70 && x>5)){
		/*printf("\nhello1");
		printf("\t**%d %d %d %d**\n",a1,b1,c1,d2);
		printf("hello");
		printf("\t**%d %d %d %d**\n",a,b,c,d1);*/
		glTranslatef(transl,0,0);
		a1-=transl;
		a-=transl;
		//b-=transl;
		c1-=transl;
		c-=transl;
	//	d1-=transl;
		glutPostRedisplay();
	}
	else if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//delay(1000);
		go=~go;
	}
/*	case GLUT_MIDDLE_BUTTON: if(state==GLUT_DOWN)
								xt+=0.6;
								yt+=0.6;
								zt+=0.6;
								glScalef(xt,yt,zt);
								glutPostRedisplay();
						   break;*/
}
