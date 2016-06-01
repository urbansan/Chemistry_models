#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream.h>
#define N 201
int x[N],y[N],n=201,busy[N][N];
double a=0.637876,b=0.234198,c;
double r2[N],s2[N];

void zerowanie(void){
  int i,j;
  for(i=0;i<N;i++){
    s2[i]=0;
    r2[N]=0;
  for(j=0;j<N;j++){
    busy[i][j]=0;
  }
  }
}
double modulo(void){
  int i;


  for(i=0;i<100;i++){
    
    c=a+b;if(c>=1){c-=1;}
		
        b=a;
        a=c;
}
return c*4;
}


void liczenie(int i){
  double sr2,dx,dy,ycm,xcm;
  int k;
  dx=x[i]-x[0];
  dy=y[i]-y[0];
  r2[i/20]+=(dx*dx)+(dy*dy);

//$$$$$$ CENTER MASS
	xcm=0;ycm=0;
  for(k=0;k<i;k++){
    xcm+=x[k];ycm+=y[k];
  }
  xcm/=i;ycm/=i;
//$$$$$$ PROMIEN ZYRAFY
  sr2=0;
  for(k=0;k<i;k++){
  dx=xcm-x[k];
  dy=ycm-y[k];
  sr2+=(dx*dx)+(dy*dy);
  }
  s2[i/20]+=sr2/double(i);
}


void buduj(void){
  int k,i,l,j;
//$$$$$$   ZEROWANIE TAB SHORTINTOWEJ
  for(l=0;l<N;l++){
    for(j=0;j<N;j++){
    busy[l][j]=0;
  }}

	x[0]=100;y[0]=100;
//$$$$$$         printf("%d %d\n",x[0],y[0]);
//$$$$$$             busy[x[0]][y[0]]=1;
  
  for(i=1;i<n;i++){

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
//$$$$$$   if(x[i]==x[i-1]&&y[i]==y[i-1]){goto lab;}
//$$$$$$   if(busy[x[i]][y[i]]==1){goto end;}
//$$$$$$     else{busy[x[i]][y[i]]=1;}
//$$$$$$ printf("%d %d ",x[i],y[i]);
if(i%20==0&&i>0){liczenie(i);}
}
end:
}


void koncowka(int m){
  int i;
  for(i=1;i<11;i++){
    r2[i]/=m;
    s2[i]/=m;
    printf("%lf %lf %lf ",log(i*20),log(r2[i]),log(s2[i]));
    printf("%d %lf %lf \n",(i*20),r2[i],s2[i]);

  }

}

 
int main(void){
  int i,m=2000;

  zerowanie();
  
  for(i=0;i<m;i++){
  buduj();
//$$$$$$   printf("%d ",i);
  }
koncowka(m);
}