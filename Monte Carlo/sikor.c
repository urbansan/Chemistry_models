#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 50
int n=(N*N)/4;
double epot=0,echwil=0,eps=0.5;
double x[(N*N)/4],y[(N*N)/4],hist[100];

void lospol(void){
  int i,j;

  for(i=0;i<n;i++){
xylab:
    x[i]=rand()%N;           
    y[i]=rand()%N;
    
        for(j=0;j<i;j++){
            if(x[i]==x[j]){
            if(y[i]==y[j]){goto xylab;}}}
//$$$$$$      printf("%d. %lf  %lf\n",i+1,x[i],y[i]);
  }
//$$$$$$     ZEROWANIE HISTOGRAMU
for(i=0;i<100;i++){
hist[i]=0;}
}

inline void rozklad(void){
  int i,m=n,k,l;
  double rX,rY,r;
  
for(i=0;i<n-1;i++){
  for(k=1;k<m;k++){
	rX=x[i]-x[i+k];
	rY=y[i]-y[i+k];

	r=sqrt((rX*rX)+(rY*rY));
        if(r<=10){
        l=int(10*r);
        hist[l]+=0.1;}
  }m=m-1;}

}

void energiacalk(void){
  int m=n,k,i;
  double rX,rY,r;
  double t2,t4,t6;
  
for(i=0;i<n-1;i++){
  for(k=1;k<m;k++){
	rX=x[i]-x[i+k];
	rY=y[i]-y[i+k];

	r=sqrt((rX*rX)+(rY*rY));
    t2=r*r;t4=t2*t2;t6=t2*t4;
	epot+=((1.0/(t6*t6))-(1.0/t6))*eps;
}m=m-1;}
    printf("\n\n%lf\n",epot); 
}

inline void brzegi(int i){
x[i]-=N*int(x[i]/N);
if(x[i]<0){x[i]+=N;}
y[i]-=N*int(y[i]/N);
if(y[i]<0){y[i]+=N;}
}

  
void boltz(void){
  int i,j;
  double rX,rY,r,xs,ys;
  double t2,t4,t6;
  double edelt,a;
  double estara;
  
//$$$$$$     LOSOWANIE KULKI I PRZESUNIECIA
  i=(rand()%n);
	
  xs=x[i];
  ys=y[i];
  
//$$$$$$ OBLICZNIE STAREJ ENERGII
  
  estara=0;
  for(j=0;j<n;j++){
      if(j==i){goto skok1;}
      
		rX=xs-x[j];
		rY=ys-y[j];

		r=sqrt((rX*rX)+(rY*rY));
            
		t2=r*r;t4=t2*t2;t6=t2*t4;
		estara+=((1.0/(t6*t6))-(1.0/t6))*eps;
    
skok1:
    }
//$$$$$$ ZMIANA POLOZENIA

  x[i]+=((rand()/(double)RAND_MAX)*2-1)*0.5;
  y[i]+=((rand()/(double)RAND_MAX)*2-1)*0.5;
  
  brzegi(i);


//$$$$$$     NOWA ENERGIA

  echwil=epot-estara;
	for(j=0;j<n;j++){
      if(j==i){goto skok2;}
      
		rX=x[i]-x[j];
		rY=y[i]-y[j];

		r=sqrt((rX*rX)+(rY*rY));
//$$$$$$             if(r>(N/4)){goto skok;} // ZAKRES KULEK DO LICZENIA
            
		t2=r*r;t4=t2*t2;t6=t2*t4;
		echwil+=((1.0/(t6*t6))-(1.0/t6))*eps;
    
skok2:
    }
//$$$$$$     BOLTZMANN    
    if(epot>=echwil){epot=echwil;}
    
    else{
      a=rand()/(double)RAND_MAX;
      edelt=echwil-epot;      
      if(a<exp(-edelt)){epot=echwil;}
      	else{x[i]=xs;y[i]=ys;}}

      }


    
void printhist(void){
  int i;
  FILE *zrzut;
  zrzut=fopen("histogram.txt","a");
  
    for(i=1;i<100;i++){
	hist[i]/=i*i;
  }
  for(i=0;i<100;i++){
    fprintf(zrzut,"%d %f\n",i,hist[i]);
  }
    fprintf(zrzut,"\n\n");

  fclose(zrzut);
}

int main(void){
  int i,j,k,ilosckolek=10000;
  for(j=0;j<2;j++){

    
  lospol();
  energiacalk();
	
	for(i=0;i<ilosckolek;i++){
      for(k=0;k<n;k++){
        boltz();}
        rozklad();
        printf("%lf\n",epot);
}
    printhist();
    eps+=1.2;
}
}
