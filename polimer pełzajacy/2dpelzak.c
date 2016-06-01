#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream.h>
#define N 201
#define M 1000000
int x[N],y[N],n=200,busy[N][N];
double a=0.637876,b=0.234198,c;
double r2[M],xcm[M],ycm[M];

double modulo(void){
  int i;
  for(i=0;i<100;i++){    
    c=a+b;if(c>=1){c-=1;}
		
        b=a;
        a=c;
}
return c*4;}


void losowanie(int i){
  int k;
  x[i]=x[i-1];
  y[i]=y[i-1];
 lab: 
  k=int(modulo());
  switch(k){
case 0: y[i]+=1;
break;
case 1: y[i]-=1;
break;
case 2: x[i]+=1;
break;
case 3: x[i]-=1;
break;
default : break;}
  if(x[i]==x[i-2]&&y[i]==y[i-2]){goto lab;}  
}


void liczenie(int k){
  double dx,dy;
  int i;
  dx=x[n-1]-x[0];
  dy=y[n-1]-y[0];
  r2[k]=(dx*dx)+(dy*dy);

//$$$$$$ CENTER MASS
	xcm[k]=0;ycm[k]=0;
  for(i=0;i<n;i++){
    xcm[k]+=x[i];ycm[k]+=y[i];
  }
  xcm[k]/=n;ycm[k]/=n;  
}
  

void autocorr2(void){
  int i,tal;
  double srAB=0,s=0,sig2=0;

//$$$$$$   LICZENIE SREDNIEJ
for(i=0;i<M;i++){
  s+=r2[i];
}
  s/=M;
//$$$$$$ ODCHYLENIE

  for(i=0;i<M;i++){sig2+=(r2[i]-s)*(r2[i]-s);}
  sig2=sig2/(M-1);

for(tal=0;tal<100;tal++){
  srAB=0;
  for(i=0;i<M-tal;i++){srAB+=r2[i]*r2[i+tal];}
  printf("%lf\n",(((srAB)/(M-tal-1))-s*s)/(sqrt(sig2*sig2)));
}
}



void autocorcm(void){
  int i,tal;
  double srAB=0,s[100],sig2=0,dx,dy,r[M];
for(i=0;i<100;i++){s[i]=0;}
  
for(tal=1;tal<100;tal++){
  
//$$$$$$   LICZENIE SREDNIEJ


for(i=0;i<M-tal;i++){
  dx=xcm[i+tal]-xcm[i];
  dy=ycm[i+tal]-ycm[i]; 
  r[i]=sqrt((dx*dx)+(dy*dy));
  s[tal]+=r[i];

}
  s[tal]/=M-tal;

		printf("%lf \n",((s[tal])));
  }
}


void buduj(void){
  int i,l,j;
	x[0]=100;y[0]=100;

//$$$$$$ LOSOWANIE LANCUCHA
  
  for(i=1;i<n;i++){
losowanie(i);
}
  printf("\n\n\n\n");
}



void pelzl(int k){
  int i;
  losowanie(n);

//$$$$$$ GLOWNA ZABAWA      
	for(i=0;i<n;i++){
      x[i]=x[i+1];
      y[i]=y[i+1];  
    }
      liczenie(k);
}



int main(void){
  int i;
  buduj();

  for(i=0;i<M;i++){
  pelzl(i);}
	autocorr2();
  printf("\n\n\n\n");
      autocorcm();
}