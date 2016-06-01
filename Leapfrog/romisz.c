#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 50
#define time 0.01
int n=(N*N)/4;
double x[(N*N)/4],y[(N*N)/4],hist[100];
double xs[(N*N)/4],ys[(N*N)/4],aX[(N*N)/4],aY[(N*N)/4],vX[(N*N)/4],vY[(N*N)/4];
double rX,rY,r,vXn=0,vYn=0,epot,ekin,ekiny,ekinx,coff=5;
double a=0.637876,b=0.234198,c;

double modulo(void){
  int i;


  for(i=0;i<100;i++){
    
    c=a+b;if(c>1){c-=1;}
		
        b=a;
        a=c;

  }
return c*50;
}




void lospol(void){
  int i,j,k;
  double los1=0,los2=0;


  for(i=0;i<n;i++){
xylab:
    x[i]=int(modulo());           
    y[i]=int(modulo());
    
        for(j=0;j<i;j++){
            if(x[i]==x[j]){
            if(y[i]==y[j]){goto xylab;}}}
  }
//    ZEROWANIE HISTOGRAMU
for(i=0;i<100;i++){
hist[i]=0;}

if(i<n-1){
for(k=0;k<12;k++){
los1+=((rand()/(double)RAND_MAX*2)-1);
los2+=((rand()/(double)RAND_MAX*2)-1);
}
vX[i]=los1/12.;
vY[i]=los2/12.;
vXn+=vX[i];
vYn+=vY[i];
}
else{
vX[i]=-vXn;
vY[i]=-vYn;
}}

inline void rozklad(double nr){
  int i;
  i=int(10*nr);
  hist[i]+=0.1;
}



inline void brzegi(int i){
x[i]-=N*int(x[i]/N);
if(x[i]<0){x[i]+=N;}
y[i]-=N*int(y[i]/N);
if(y[i]<0){y[i]+=N;}
}

void energia(int i, int k){
  double t2,t4,t6,t7,t13,F;
  
t2=r*r;t4=t2*t2;t6=t2*t4;t7=t6*r;t13=t6*t7;
F=-((12/t13)-(6/(t7)));
epot+=(1.0/(t6*t6))-(1.0/t6);

rX/=r;
rY/=r;

rX*=F;
rY*=F;

aX[i]-=(rX);
aY[i]-=(rY);
aX[i+k]+=(rX);
aY[i+k]+=(rY);
  
}

  
inline void leapfrog(int p){
  int i,m=n,k,liczba=0,pip;

  epot=0;

for(i=0;i<n;i++){
aX[i]=0;aY[i]=0;
}

for(i=0;i<n-1;i++){
  for(k=1;k<m;k++){
	rX=x[i]-x[i+k];
	rY=y[i]-y[i+k];
    
    if(abs(rX)<coff&&abs(rY)<coff){
		r=sqrt((rX*rX)+(rY*rY));
    
// RADIALNA FUNKCJA ROZKLADU
	if(r<10){rozklad(r);}


// CUTOFF
  if(r<coff){
	energia(i,k);}}
    
// ODCZUWANIE BRZEGOW	
if(abs(rY)<5){
	if(x[i]>N-5&&x[i+k]<5-(N-x[i])){
      rX=x[i]-(x[i+k]+N);
  		r=sqrt((rX*rX)+(rY*rY));
		  energia(i,k);}
          
	if(x[i]<5&&x[i+k]>N-(5-x[i])){
      rX=(x[i]+N)-x[i+k];
  		r=sqrt((rX*rX)+(rY*rY));
		  energia(i,k);}}
          
rX=x[i]-x[i+k];

if(abs(rX)<5){
	if(y[i]>N-5&&y[i+k]<5-(N-y[i])){
      rY=y[i]-(y[i+k]+N);
  		r=sqrt((rX*rX)+(rY*rY));
		  energia(i,k);}
          
	if(y[i]<5&&y[i+k]>N-(5-y[i])){
      rY=(y[i]+N)-y[i+k];
  		r=sqrt((rX*rX)+(rY*rY));
		  energia(i,k);}}
          
liczba++;

}m=m-1;}


ekiny=0;
ekinx=0;
  for(i=0;i<n;i++){
// LICZENIE NOWYCH PREDKOSCI     
vXn=(vX[i]+(time*aX[i]));
vYn=vY[i]+(time*aY[i]);
//	LICZENIE NOWYCH POLOZEN ORAZ DODAWANIE DO STARYCH
x[i]=x[i]+(time*vXn);
xs[i]=xs[i]+(time*vXn);
y[i]=y[i]+(time*vYn);
ys[i]=ys[i]+(time*vYn);
//WARUNEK BRZEGOWY
brzegi(i);
// OBLICZANIE PREDKOSCI W PUNKTACH CZASOWYCH
vX[i]=(vXn+vX[i])/2;
vY[i]=(vYn+vY[i])/2;


// OBLICZANIE ENERGII

  ekinx+=(vX[i]*vX[i])/2;
  ekiny+=(vY[i]*vY[i])/2;
// ZASTEPOWANIE STARYCH PREDKOSCI
vX[i]=vXn;
vY[i]=vYn;
}


if(p%100==0){
  for(pip=0;pip<n;pip++){
	printf("\n%f %f",x[pip],y[pip]);}
    printf(" %f %f %f\n",epot,ekinx,ekiny);}

}


    
void printhist(void){
  int i;
  FILE *zrzut;
  zrzut=fopen("histogram.txt","a");
  
    for(i=1;i<100;i++){
	hist[i]/=(M_PI*(i+1)*(i+1))-(M_PI*i*i);
  }
  for(i=0;i<100;i++){
    fprintf(zrzut,"%d %f\n",i,hist[i]);
  }
    fprintf(zrzut,"\n\n");

  fclose(zrzut);
}

int main(void){
  int p;
    
  lospol();
	
  	for(p=0;p<20000;p++){
  		leapfrog(p);
}
    printhist();
}
