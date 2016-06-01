#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream.h>
#define N 201
int busy[2*N][2*N][2*N];
int x[N],y[N],z[N],n=200;
int dlug[N];
double a=0.637876,b=0.234198,c;
double r2[N],s2[N];

void zerowanie(void){
  int i,j,k;
  for(i=0;i<N;i++){
    s2[i]=0;
    r2[i]=0;
    dlug[i]=0;
  }
    
      for(i=0;i<2*n;i++){
    for(j=0;j<2*n;j++){
      for(k=0;k<2*n;k++){        
    busy[i][j][k]=0;
      }}}
}

double modulo(void){
//$$$$$$   int i;
//$$$$$$   for(i=0;i<100;i++){
    
    c=a+b;if(c>=1){c-=1;}
		
        b=a;
        a=c;
//$$$$$$ }
return c*6;
}


void liczenie(int i){
  double sr2,dx,dy,dz,ycm,xcm,zcm;
  int k;
  dx=x[i]-x[0];
  dy=y[i]-y[0];
  dz=z[i]-z[0];
  r2[i]+=(dx*dx)+(dy*dy)+(dz*dz);

//$$$$$$ CENTER MASS
	xcm=0;ycm=0;zcm=0;
  for(k=0;k<i;k++){
    xcm+=x[k];ycm+=y[k];zcm+=z[k];
  }
  xcm/=i;ycm/=i;zcm/=i;
//$$$$$$ PROMIEN ZYRAFY
  sr2=0;
  for(k=0;k<i+1;k++){
  dx=xcm-x[k];
  dy=ycm-y[k];
  dz=zcm-z[k];
  sr2+=(dx*dx)+(dy*dy)+(dz*dz);
  }
  s2[i]+=sr2/double(i);
}


void buduj(void){
  int k,i,l,j,o;


	x[0]=n;y[0]=n;z[0]=n;
	x[1]=n+1;y[1]=n;z[1]=n;
    
            busy[x[0]][y[0]][z[0]]=1;
            busy[x[1]][y[1]][z[1]]=1;
  
  for(i=2;i<n;i++){
 lab: 
  x[i]=x[i-1];
  y[i]=y[i-1];
  z[i]=z[i-1];

  o=int(modulo());
  switch(o){
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
}
  if(x[i]==x[i-2]&&y[i]==y[i-2]&&z[i]==z[i-2]){goto lab;}
  if(busy[x[i]][y[i]][z[i]]==1){dlug[i-1]+=1;goto end;}
    else{busy[x[i]][y[i]][z[i]]=1;}
//$$$$$$ printf("%d %d %d\n ",x[i],y[i],z[i]);
//$$$$$$ i
}
dlug[n-1]+=1;
end:
liczenie(i-1);
  for(i=0;i<n;i++){
    busy[x[i]][y[i]][z[i]]=0;}
//$$$$$$ printf("\n\n\n\n\n");

}


void koncowka(void){
  int i;
  for(i=1;i<n;i++){
    if(dlug[i]>0){
    r2[i]/=dlug[i];
    s2[i]/=dlug[i];}
//$$$$$$     printf("%lf %lf %lf ",log(i*20),log(r2[i]),log(s2[i]));
    printf("%d %lf %lf \n",i,r2[i],s2[i]);

  }

}

 
int main(void){
  int i,m=10000000;

  zerowanie();
  
  for(i=0;i<m;i++){
	if(i%100==0){printf("%d\n",i);}
  buduj();
  }
printf("\n\n\n\n\n");
  for(i=1;i<n;i++){ 
  printf("%d %d\n",i,dlug[i]);
  }
printf("\n\n\n\n\n");
koncowka();
}