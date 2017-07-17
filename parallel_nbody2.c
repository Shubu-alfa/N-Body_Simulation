#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include"omp.h"

int main()
{
	
        int c=0,c1=0;
	int x,y,z;
	double m;
	FILE *fp1,*fp2,*fp3;
	fp1 = fopen("values1.txt","r");
	double d,G =6.673e-11;    //G is the gravitational constant
	int i,x1,x2,y1,y2,z1,z2,j;
	double m1,m2;
	long double f=0,f1=0;

	int nthreads,tid,b1,b2;
	omp_set_num_threads(10);
	
	
	/*#pragma omp parallel for
	for(i=0;i<=9;i++)
	{
		
		m = rand() % 100; // to get a number under 100 which is the mass of the body
		printf("Thread number:%d mass: %lf\n",omp_get_thread_num(),m);
		x = rand() % 1000;   //to get a number under 1000 which is the x-coordinate of the position of the body.
		y = rand() % 1000;
		z = rand() % 1000;
		fprintf(fp1 , "\n %lf %d %d %d" , m, x, y, z);		//%lf used for double values
	}
	printf("-----------------------------------------------------------------------------\n");
	
 	rewind(fp1);   // to set the pointer back to the starting point of the file.
	char ch1=fgetc(fp1),ch;
	//fp2 = fopen("values1.txt","r");*/
	
	#pragma omp parallel for num_threads(10) private(m1,z1,y1,x1,fp2,b1,f1)
	for(i=0;i<10;i++)	
	{
		
		fp2=fopen("values1.txt","r");
		m1=0;
		f1=0.0;
		#pragma omp critical          //only one thread will be able to read/increment/write m1,z1,y1,x1,fp2,b1,f1 at any time 
		fscanf(fp1 , "%d %lf %d %d %d" , &b1,&m1, &x1, &y1, &z1);

		#pragma omp parallel for num_threads(10) private(m2,x2,y2,z2,b2,tid,f,d)	
		for(j=0;j<10;j++)
		{
			
			tid=omp_get_thread_num();
			//c1=c1%10;
			
			#pragma omp critical  //only one thread will be able to read/increment/write m2,z2,y2,x2,tid,f,d at any time
			fscanf(fp2 , "%d %lf %d %d %d" , &b2,&m2, &x2, &y2, &z2);

			d = sqrt(pow((x2-x1),2) + pow((y2-y1),2)+pow((z2-z1),2));
		//	printf("distance between body %d and %d: %lg \n",c,c1,d);
		//	printf("mass of body %d is : %lf and body %d is : %lf \n\n",c,m1,c1,m2);
			if(d==0)
			{
				f=0;
				#pragma omp critical
				f1+=0;	
			}
			else	
			{
				f = ((G*m1*m2)/(d*d));
				#pragma omp critical
				f1 = f1 + ((G*m1*m2)/(d*d));
				
			}
			printf("force on body %d by body %d by thread %d: %LG Newtons \n",b1,b2,tid,f);
			//c1++;
			
		}
			
		
		
		printf("-----------------------------------------------------------------------------\n");
		printf("Total force on body %d : %LG Newtons \n",b1,f1);
		printf("-----------------------------------------------------------------------------\n");	
	
		fclose(fp2);
		
		//c++;
	}

}
