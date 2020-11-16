#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000

typedef struct {
	float x, y, z, w;
} vertex;

typedef struct {
	float m[4][4];
} matrix;

void display_res(float *res)
{
	int i;
	
	for (i = 0; i < 4; i++)
		printf("%.2f ", res[i]);
	printf("\n");
}

void xform_pointer(float *res, const float *v, const float *m, int numverts) {
	float dp;
	int i;
	const vertex *vv = (vertex *) v;

	for (i = 0; i < numverts; i++) {
		dp =  vv->x * *m++;
		dp += vv->y * *m++;
		dp += vv->z * *m++;
		dp += vv->w * *m++;
		*res++ = dp;
		
		dp =  vv->x * *m++;
		dp += vv->y * *m++;
		dp += vv->z * *m++;
		dp += vv->w * *m++;
		*res++ = dp;

		dp =  vv->x * *m++;
		dp += vv->y * *m++;
		dp += vv->z * *m++;
		dp += vv->w * *m++;
		*res++ = dp;

		dp =  vv->x * *m++;
		dp += vv->y * *m++;
		dp += vv->z * *m++;
		dp += vv->w * *m++;
		*res++ = dp;

		++vv;
		m -= 16;
	}
	//display_res(res-4);
}

void xform_array(float *res, const float *v, const float *m, int numverts)
{
	int i;
	const vertex *vv = (vertex *)v;
	const matrix *mm = (matrix *)m;
	vertex *rr = (vertex *)res;

	for (i = 0; i < numverts; i++) {
		rr->x = vv->x * mm->m[0][0] + vv->y * mm->m[0][1] +
			vv->z * mm->m[0][2] + vv->w * mm->m[0][3];
		
		rr->y = vv->x * mm->m[1][0] + vv->y * mm->m[1][1] +
			vv->z * mm->m[1][2] + vv->w * mm->m[1][3];
		
		rr->z = vv->x * mm->m[2][0] + vv->y * mm->m[2][1] +
			vv->z * mm->m[2][2] + vv->w * mm->m[2][3];

		rr->w = vv->x * mm->m[3][0] + vv->y * mm->m[3][1] +
			vv->z * mm->m[3][2] + vv->w * mm->m[3][3];
	}
	//display_res(res);
}

void t_xform_array(float *res, const float *v, const float *m, int numverts)
{
	int i;
	clock_t begin, end;
	double time_spent;
	
	for (i = 0; i < 4; i++)
		*(res + i) = 0;
	
	time_spent = 0.0;
	begin = clock();
	for (i = 0; i < N; i++)
		xform_array(res, v, m, numverts);
	end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("array spent: %f\n", time_spent);
}

void t_xform_pointer(float *res, const float *v, const float *m, int numverts)
{
	int i;
	clock_t begin, end;
	double time_spent;
	
	for (i = 0; i < 4; i++)
		*(res + i) = 0;
	
	time_spent = 0.0;
	begin = clock();
	for (i = 0; i < N; i++)
		xform_pointer(res, v, m, numverts);
	end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("pointer spent: %f\n", time_spent);
}

int main(int argc, char *argv[])
{
	int i;
	float *res = (float*)malloc(4 * sizeof(float));
	float *m = (float*)malloc( 16 * sizeof(float));
	float *v = (float*)malloc(  4 * sizeof(float));
	

	for (i = 0; i < 4; i++)
		*(v + i) = i + 0.5;
	for (i = 0; i < 16;i++)
		*(m + i) = i + 0.5;

	t_xform_array(res, v, m, 1);
	t_xform_pointer(res, v, m, 1);
	
	return 0;
}
