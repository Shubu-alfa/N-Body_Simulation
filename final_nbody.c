#include<math.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	
        int c=0,c1=0;
	int x,y,z;
	double m;
	FILE *fp1,*fp2,*fp3;
	fp1 = fopen("values1.txt","w+");
	double d,G =6.673e-11;    //G is the gravitational constant
	int i,x1,x2,y1,y2,z1,z2;
	double m1,m2;
	long double f=0,f1=0;

	for(i=0;i<=9;i++)
	{
		m = rand() % 100; // to get a number under 100 which is the mass of the body
		x = rand() % 1000;   //to get a number under 1000 which is the x-coordinate of the position of the body.
		y = rand() % 1000;
		z = rand() % 1000;
		fprintf(fp1 , "\n %lf %d %d %d" , m, x, y, z);		//%lf used for double values
	}
	
 	rewind(fp1);   // to set the pointer back to the starting point of the file.
	char ch1=fgetc(fp1),ch;
	fp2 = fopen("values1.txt","r");
	for(ch1=fgetc(fp1);ch1!=EOF;ch1=fgetc(fp1),f1=0.0)	
	{
		m1=0;
		fscanf(fp1 , "%lf %d %d %d" , &m1, &x1, &y1, &z1);
		for(ch=fgetc(fp2);ch!=EOF;ch=fgetc(fp2))
		{
			
			c1=c1%10;
			if(ch!='\n')
			{
				fscanf(fp2 , "%lf %d %d %d" , &m2, &x2, &y2, &z2);
				d = sqrt(pow((x2-x1),2) + pow((y2-y1),2)+pow((z2-z1),2));
			//	printf("distance between body %d and %d: %lg \n",c,c1,d);
			//	printf("mass of body %d is : %lf and body %d is : %lf \n\n",c,m1,c1,m2);
				if(d==0)
				{
					f=0;
					f1+=0;	
				}
				else
				{
					f = ((G*m1*m2)/(d*d));
					f1 = f1 + ((G*m1*m2)/(d*d));
					
				}
				printf("force on body %d by body %d : %LG Newtons \n",c,c1,f);
				c1++;
			}
			
		}
		printf("-----------------------------------------------------------------------------\n");
		printf("Total force on body %d : %LG Newtons \n",c,f1);
		printf("-----------------------------------------------------------------------------\n");	
	
		rewind(fp2);
		
		c++;
	}
}
