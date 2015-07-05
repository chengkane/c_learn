
#include <stdio.h>
#include <stdlib.h>

#define wayout 3
#define edge 2
#define obs 1
#define way 0

int find(int *trace,int *data,int width,int x,int y,int (*rs)[2],int n);

int main(int argc,char **argv)
{
	int width,size;
	int i,j,end,tmp;

	scanf("%d",&width);
	size=(width+2)*(width+2);
	int *data=(int*)malloc(sizeof(int)*size);
	int *trace=(int*)malloc(sizeof(int)*size);
	int (*rs)[2]=(int(*)[2])malloc(sizeof(int)*2*width*width);

	for(i=0;i<size;i++)
		data[i]=edge,trace[i]=0;

	for(i=width+3,end=size-width-3;i<end;){
		while((tmp=getchar())!='0'&&tmp!='1');
		data[i]=tmp-'0';
		i+=(i+2)%(width+2)?1:3;
	}
	data[width*(width+3)]=wayout;

	for(i=0;i<size;i++){
		putchar(data[i]+'0');
		if((i+1)%(width+2)==0)
			putchar('\n');
	}

	if(tmp=find(trace,data,width+2,1,1,rs,0)){
		for(i=0;i<tmp;i++)
			printf("%d. %d,%d\n",i+1,rs[i][0],rs[i][1]);
	}else
		puts("can't find!");

	free(rs);
	free(data);
	free(trace);
	return 0;
}

int find(int *trace,int *data,int width,int x,int y,int (*rs)[2],int n)
{
	static int next[4][2]={
		1,0,
		-1,0,
		0,1,
		0,-1};
	int i,tmp=x*width+y;
	if(trace[tmp]==1)
		return 0;
	trace[tmp]=1;
	switch(data[tmp]){
		case edge:
		case obs:
			return 0;
		case way:
			rs[n][0]=x,rs[n][1]=y;
			for(i=0;i<4;i++)
				if(tmp=find(trace,data,width,x+next[i][0],y+next[i][1],rs,n+1))
					return  tmp;
			return 0;
		case wayout:
			rs[n][0]=x,rs[n][1]=y;
			return n;
	}
}

