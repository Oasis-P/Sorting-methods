#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAXSIZE 100	
struct insert{
	int r[MAXSIZE+1];
	int com[6],ex[6];
	int n;
	int length;
};
void input(struct insert *tab)/*随机产生数列*/
{
	srand((unsigned)time(NULL));
	for(tab->length=1;tab->length<16;tab->length++)
		tab->r[tab->length]=rand()%100;
	tab->n=1;
}
	
void output(struct insert *tab)/*输出*/
{
	int i;
	printf("原序列排序结果：");
	for(i=1;i<tab->length;i++)
		printf("%-6d",tab->r[i]);
	printf("\n");
	
	for(i=0;i<15;i++)
		printf("********");
	printf("\n");
}

void insertsort(struct insert *tab)	 /*直接插入法排序*/
{	 
	int m,i,j;	
	for(i=2;i<tab->length;i++)
	{
		j=i-1;
		tab->r[0]=tab->r[i]; 
		while(tab->r[0]<tab->r[j])
		{
			tab->r[j+1]=tab->r[j];
			j=j-1;
			tab->ex[0]++;  /*交换次数*/
			
		}
		tab->r[j+1]=tab->r[0];	
		printf("第%.2d次排序结果：",i-1);
		for(m=1;m<tab->length;m++)
			printf("%-6d",tab->r[m]);
		printf("\n");
		tab->com[0]=tab->com[0]+i-1;/*比较次数*/
	}
}

void shellinsertsort(struct insert *tab) /*shell插入排序*/
{
	int i,j,d,m,n;
	for(d=(tab->length-1)/2,n=1;d>=1;d=d/2,n++)
	{
		for(i=d+1;i<tab->length;i++)
		{
			tab->r[0]=tab->r[i];
			j=i-d;
			while(j>0&&tab->r[0]<tab->r[j])
			{
				tab->r[j+d]=tab->r[j];
				j=j-d;
				tab->ex[1]++;/*交换次数*/
			}
			tab->r[j+d]=tab->r[0]; 
		}
		printf("第%.2d次排序结果：",n);
		for(m=1;m<tab->length;m++)
			printf("%-6d",tab->r[m]);
		printf("\n");
		tab->com[1]=tab->length-d+tab->com[1]; /*比较次数*/
	}

}
void simpleselectsort(struct insert *tab)/*直接选择排序*/
{
	int i,j,k,m;	
	for(i=1;i<tab->length-1;i++)
	{
		k=i;
		for(j=i+1;j<tab->length;j++)
			if(tab->r[j]<tab->r[k])
			{
				tab->com[2]++;/*比较次数*/
				k=j;
			}
			if(k!=i)																						      
			{ 
				tab->r[0]=tab->r[k];
				tab->r[k]=tab->r[i];
				tab->r[i]=tab->r[0];
				tab->ex[2]++;		   /*交换次数*/
			}
		printf("第%.2d次排序结果：",i);
		for(m=1;m<tab->length;m++)
			printf("%-6d",tab->r[m]);
		printf("\n");

	}
}

void bubblesort(struct insert *tab)/*冒泡排序*/
{
	int i=1,j,done=1,m;
	while(i<tab->length&&done)
	{
		done=0;
		for(j=1;j<tab->length-i;j++)
		{
			tab->com[3]++;  /*比较次数*/
			if(tab->r[j+1]<tab->r[j])
			{
				tab->r[0]=tab->r[j];
				tab->r[j]=tab->r[j+1];
				tab->r[j+1]=tab->r[0];
				done=1;
				tab->ex[3]++;		 /*交换次数*/
			}
		}
		
		printf("第%.2d次排序结果：",i);
		for(m=1;m<tab->length;m++)
			printf("%-6d",tab->r[m]);
		printf("\n");
		i++;

	}
}

void quicksort(struct insert *tab,int left ,int right)/*快速排序*/
{
	int i,j,m;
	if(left<right)
	{
		i=left;j=right;
		tab->r[0]=tab->r[i];
		do
		{
			while (tab->r[j]>tab->r[0]&&i<j)
			{
				tab->com[4]++;				 /*比较次数*/
				j--;
			}
			if(i<j)
			{
				tab->r[i]=tab->r[j];
				i++;
				tab->ex[4]++;				/*交换次数*/
			}
			while(tab->r[i]<tab->r[0]&&i<j)
			{
				i++;
				tab->com[4]++;					/*比较次数*/
			}
			if(i<j)
			{
				tab->r[j]=tab->r[i];
				j--;
				tab->ex[4]++;				   /*交换次数*/
			}	
		}
		while(i!=j);
		tab->r[i]=tab->r[0];
		printf("第%.2d次排序结果：",tab->n++); 
		for(m=1;m<tab->length;m++)
			printf("%-6d",tab->r[m]);
		printf("\n");
		quicksort(tab,left,i-1);
		quicksort(tab,i+1,right);
	}
}
void merge(struct insert *tabs,struct insert *tabg,int u, int m, int v)/*一次归并排序*/
{
	int i,j,k,t;
	i=u;
	j=m+1;
	k=u;
	while(i<=m&&j<=v)
	{
		if(tabs->r[i]<=tabs->r[j])
		{
			tabg->r[k]=tabs->r[i];
			i++;
		}
		else
		{
			tabg->r[k]=tabs->r[j];
			j++;
			tabg->ex[5]++;/*交换次数*/
		}
		k++;
	}
	if(i<=m)
		for(t=i;t<=m;t++)
			tabg->r[k+t-i]=tabs->r[t];
		else
			for(t=j;t<=v;t++)
				tabg->r[k+t-j]=tabs->r[t];
}
void mergepass(struct insert *tabs,struct insert *tabg,int len)/*一趟归并算法*/
{
	int i,j,n,m;
	tabg->length=tabs->length;
	n=tabg->length-1;
	i=1;
	while(i<=n-2*len+1)
	{
		merge(tabs,tabg,i,i+len-1,i+2*len-1);
		i=i+2*len;
		tabg->com[5]=tabg->com[5]+len;/*比较次数*/
	}
	if(i+len-1<n)
	{
		merge(tabs,tabg,i,i+len-1,n);
		tabg->com[5]=tabg->com[5]+n-i-len+1;/*比较次数*/
	}
	else
		for(j=i;j<=n;j++)
			tabg->r[j]=tabs->r[j];
	printf("第%.2d次排序结果：",tabg->n);
	for(m=1;m<tabg->length;m++)
		printf("%-6d",tabg->r[m]); 
	printf("\n");
} 

void mergesort(struct insert *tab)/*归并排序*/
{
	int len;
	struct insert temp;
	temp.n=1;
	tab->n=1;
	temp.com[5]=0;
	temp.ex[5]=0;
	len=1;
	while(len<tab->length-1)
	{
		mergepass(tab,&temp,len);/*结果在temp中*/
		tab->ex[5]=temp.ex[5];/*交换次数*/
		tab->com[5]=temp.com[5];/*比较次数*/
		tab->n=temp.n+1;
		temp.n=tab->n+1;
		len=2*len;
		mergepass(&temp,tab,len);/*结果在tab中*/
		len=2*len;
		temp.ex[5]=tab->ex[5];/*交换次数*/
		temp.com[5]=tab->com[5];/*比较次数*/
	}
}

int main()
{	
	int g;
	for(g=0;g<10;g++)//10组排序比较
	{
	struct insert n;
	int i;
	for(i=0;i<6;i++)
	{
		n.com[i]=0;
		n.ex[i]=0;
	}
	input(&n);
	printf("随机产生数列为：");
	for(i=1;i<n.length;i++)
		printf("%-6d",n.r[i]);
	printf("\n");
	for(i=0;i<15;i++)
		printf("*****");
	printf("\n");
	input(&n);
	printf("直接插入法排序\n");
	insertsort(&n);
	output(&n);
	input(&n);
	printf("shell排序\n");
	shellinsertsort(&n);
	output(&n);
	input(&n);
	printf("直接选择排序\n");
	simpleselectsort(&n);
	output(&n);								  
	input(&n);
	printf("冒泡排序\n");
	bubblesort(&n);
	output(&n);
	input(&n);
	printf("快速排序\n");
	quicksort(&n,1,n.length-1);
	output(&n);
	input(&n);
	printf("归并排序\n");
	mergesort(&n);
	output(&n);
	printf("             直接插入排序   shell排序  直接选择排序  冒泡排序   快速排序     归并排序\n");
	printf("compare：");
	for(i=0;i<6;i++)
		printf("%12d",n.com[i]);
	printf("\n");
	printf("exchange:");
	for(i=0;i<6;i++)
		printf("%12d",n.ex[i]);
	printf("\n");
	}
	return 0;
}		
