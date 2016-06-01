#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 25
double a=0.637876,b=0.234198,c;
int n=N*N/4;
double x[N*N],y[N*N],ys[N*N],xs[N*N],fx[N*N],fy[N*N];
double T=0.003;

double modulo(void){
  int i;
  for(i=0;i<100;i++){
    
    c=a+b;if(c>1){c-=1;}
        b=a;
        a=c;
  }
return c*N;
}


void lospol(void){
  int i,j,xxx,yyy;


  for(i=0;i<n;i++){
xylab:
    xxx=modulo(); 
    x[i]=xxx;
    xs[i]=x[i];        
    yyy=modulo();
    y[i]=yyy;
    ys[i]=y[i];
        for(j=0;j<i;j++){
            if(x[i]==x[j]){
            if(y[i]==y[j]){goto xylab;}}}
//$$$$$$ printf("%f %f %f %f\n ",x[i],y[i],xs[i],ys[i]);
            
  }
//$$$$$$ printf("\n\n\n\n\n");

}

inline void sila(void){
  int j,k;
  double r,t2,t4,t6,t7,t13,F,rX,rY;

//$$$$$$ ZEROWANIE SIL
  for(j=0;j<n;j++){fx[j]=0;fy[j]=0;}

	for(j=1;j<n;j++){
        for(k=0;k<j;k++){

      rX=x[j]-x[k];
      rY=y[j]-y[k];
//$$$$$$ CUTOFF
  if(abs(rX)<5&&abs(rY)<5){
      
  r=sqrt((rX*rX)+(rY*rY));  
  if(r<5){
  t2=r*r;t4=t2*t2;t6=t2*t4;t7=t6*r;t13=t6*t7;
  F=-((12/t13)-(6/t7));
  
  fx[j]-=F*(rX/r);
  fx[k]+=F*(rX/r);
  fy[j]-=F*(rY/r);
  fy[k]+=F*(rY/r);
  }}
    }}
}


inline void odbicie(int i){
  double deltx,delty,xprim,yprim,d=10;
  
  if(x[i]<0){x[i]=-x[i];xs[i]=-xs[i];}
  if(y[i]<0){y[i]=-y[i];ys[i]=-ys[i];}
  if(y[i]>N){y[i]=N+N-y[i];ys[i]=N+N-ys[i];}

  if(x[i]>N){
    if(xs[i]<N){
    deltx=x[i]-xs[i];
    delty=y[i]-ys[i];
    xprim=N-xs[i];
    yprim=(delty*xprim)/deltx;
    delty=ys[i]+yprim;
    if(delty<=d||delty>=(d+5)){
    x[i]=N+N-x[i];xs[i]=N+N-xs[i];goto skok;}
    }}

  if(x[i]<N){
    if(xs[i]>N){
    deltx=x[i]-xs[i];
    delty=y[i]-ys[i];
    xprim=N-xs[i];
    yprim=(delty*xprim)/deltx;
    delty=ys[i]+yprim;
    if(delty<d||delty>(d+5)){
    x[i]=N+N-x[i];xs[i]=N+N-xs[i];}
    }}
skok:

    
  if(x[i]>2*N){x[i]=4*N-x[i];xs[i]=4*N-xs[i];}

}



void verlet(int ble){
  int i,lewo,prawo;
  double xn,yn;
  lewo=prawo=0;
  for(i=0;i<n;i++){
  xn=2*x[i]-xs[i]+fx[i]*T;
  yn=2*y[i]-ys[i]+fy[i]*T;
// ZAMIANA POLOZEN
  xs[i]=x[i];	x[i]=xn;
  ys[i]=y[i];	y[i]=yn;
  
  odbicie(i);
if(ble%100==0){
  if(x[i]<N){lewo+=1;}
  else{prawo+=1;}
  }

  }

  
sila();
if(ble%100==0){
  printf("%d %d %d\n\n",lewo,prawo,ble);
  }
}



int main(void){
int i;
  lospol();
  sila();
  for(i=0;i<1000000;i++){
  verlet(i);}
}