#include <stdio.h>
#include <stdlib.h>

/* Make the data structure self-contained.  Element at row i and col j
   is x[i * w + j].  More often than not, though,  you might want
   to represent a matrix some other way */
typedef struct { int h, w; double *x;} matrix_t, *matrix;

inline double dot(double *a, double *b, int len, int step)
{
	double r = 0;
	while (len--) {
		r += *a++ * *b;
		b += step;
	}
	return r;
}

matrix mat_new(int h, int w)
{
	matrix r = malloc(sizeof(matrix_t) + sizeof(double) * w * h);
	r->h = h, r->w = w;
	r->x = (double*)(r + 1);
	return r;
}

matrix mat_mul(matrix a, matrix b)
{
	matrix r;
	double *p, *pa;
	int i, j;
	if (a->w != b->h) return 0;

	r = mat_new(a->h, b->w);
	p = r->x;
	for (pa = a->x, i = 0; i < a->h; i++, pa += a->w)
		for (j = 0; j < b->w; j++)
			*p++ = dot(pa, b->x + j, a->w, b->w);
	return r;
}

void mat_show(matrix a)
{
	int i, j;
	double *p = a->x;
	for (i = 0; i < a->h; i++, putchar('\n'))
		for (j = 0; j < a->w; j++)
			printf("\t%7.3f", *p++);
	putchar('\n');
}

int main(int argc,char *argv[])
{
  int da_size_col=0;
  int da_size_row=0;
	sscanf(argv[1], "%d", &da_size_col);
	sscanf(argv[2], "%d", &da_size_row);
  matrix da = mat_new(da_size_row, da_size_col);
	matrix db = mat_new(da_size_row, da_size_col);

	matrix c = mat_mul(da, db);

	/* mat_show(&a), mat_show(&b); */
	//mat_show(c);
	/* free(c) */
	return 0;
}
