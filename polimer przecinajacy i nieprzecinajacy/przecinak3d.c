#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream.h>
#define N 201
int x[N],y[N],z[N],n=201;
double a=0.637876,b=0.234198,c;
double r2[N],s2[N];

void zerowanie(void){
  int i,j;
  for(i=0;i<N;i++){
    s2[i]=0;
    r2[i]=0;

  }
}
double modulo(void){
  int i;
    
    c=a+b;if(c>=1){c-=1;}
		
        b=a;
        a=c;
return c*6;
}


void liczenie(int i){
  double sr2,dx,dy,dz,ycm,xcm,zcm;
  int k;
  dx=x[i]-x[0];
  dy=y[i]-y[0];
  dz=z[i]-z[0];
  r2[i/20]+=(dx*dx)+(dy*dy)+(dz*dz);

//$$$$$$ CENTER MASS
	xcm=0;ycm=0;zcm=0;
  for(k=0;k<i;k++){
    xcm+=x[k];ycm+=y[k];zcm+=z[k];
  }
  xcm/=i;ycm/=i;zcm/=i;
//$$$$$$ PROMIEN ZYRAFY
  sr2=0;
  for(k=0;k<i;k++){
  dx=xcm-x[k];
  dy=ycm-y[k];
  dz=zcm-z[k];
  sr2+=(dx*dx)+(dy*dy)+(dz*dz);
  }
  s2[i/20]+=sr2/double(i);
}


void buduj(void){
  int k,i,l,j;


	x[0]=100;y[0]=100;z[0]=100;
	x[1]=101;y[1]=101;z[1]=101;    


  
  for(i=2;i<n;i++){
 lab: 
  x[i]=x[i-1];
  y[i]=y[i-1];
  z[i]=z[i-1];

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
case 4: z[i]+=1;
break;
case 5: z[i]-=1;
break;
default : break;}
  if(x[i]==x[i-2]&&y[i]==y[i-2]&&z[i]==z[i-2]){goto lab;}
if(i%20==0&&i>0){liczenie(i);}
}
//$$$$$$ printf("\n\n\n\n\n");

}


void koncowka(int m){
  int i;
  for(i=1;i<11;i++){
    r2[i]/=m;
    s2[i]/=m;
    printf("%d %lf %lf \n",(i*20),r2[i],s2[i]);

  }

}

 
int main(void){
  int i,m=1000000;

  zerowanie();
  
  for(i=0;i<m;i++){
//$$$$$$     if(i%100==0){printf("%d\n",i);}

  buduj();
//$$$$$$   printf("%d ",i);
  }
koncowka(m);
}