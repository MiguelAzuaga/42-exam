/* Assignment name: tsp
Expected files: *.c *.h
Allowed functions: write, sqrtf, getline, fseek, fscanf, ferror, feof,
fabsf, memcpy, fprintf, fclose, malloc, calloc, realloc, free, fopen,
errno, stderr, stdin, stdout
-------------------------------------------------------

The first publication referring to this problem as the "traveling salesman
problem" is found in the 1949 RAND Corporation report by Julia Robinson,
"On the Hamiltonian game (a traveling salesman problem)."

Here is how she defines the problem:

"The purpose of this note is to give a method for solving a problem related
to the traveling salesman problem. It seems worthwhile to give a description
of the original problem. One formulation is to find the shortest route for a
salesman starting from Washington, visiting all the state capitals and then
returning to Washington.

More generally, to find the shortest CLOSED CURVE containing n given points
in the plane."

for example with the following set of cities:
0, 0
1, 0
2, 0
0, 1
1, 1
2, 1
1, 2
2, 2
which can be presented as follows:
+ + +
+ + +
  + +
the shortest path is:
 _____
|__   |
   |__|

so you should print the length of this path that is:
8.00

Write a program that will read a set of city coordinates in the form
'%f, %f\n' from the standard input and will print the length of the shortest
possible path containing all these cities under the form '%.2f'.

Your program will not be tested with more than 11 cities.

You will find in this directory a file tsp.c containing all the boring parts of
this exercise and example files to help you test your program.

hint: in order to use sqrtf, add -lm at the end of your compilation command.

For example this should work:
$> cat square.txt
1, 1
0, 1
1, 0
0, 0
$> ./tsp < square.txt | cat -e
4.00$ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_point
{
	float x;
	float y;
}	t_point;

typedef struct s_ctx
{
	int     n;
	float **dist;
	int    *vis;
	float   best;
}	t_ctx;

static void	*xfree2d(float **m, int n)
{
	if (m)
	{
		for (int i = 0; i < n; ++i)
			free(m[i]);
		free(m);
	}
	return NULL;
}

static void	build_dist(float **d, t_point *p, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			float dx = p[i].x - p[j].x;
			float dy = p[i].y - p[j].y;
			d[i][j] = sqrtf(dx * dx + dy * dy);
		}
	}
}

/*
Backtracking DFS:
- Fix start at city 0 to remove rotational symmetry.
- depth = number of cities visited so far.
- cur  = current city index.
- cost = path length so far.
Prune when cost >= best.
*/
static void	dfs(t_ctx *c, int cur, int depth, float cost)
{
	if (cost >= c->best)
		return;
	if (depth == c->n)
	{
		float total = cost + c->dist[cur][0]; // close the tour
		if (total < c->best)
			c->best = total;
		return;
	}
	for (int nxt = 1; nxt < c->n; ++nxt)
	{
		if (!c->vis[nxt])
		{
			c->vis[nxt] = 1;
			dfs(c, nxt, depth + 1, cost + c->dist[cur][nxt]);
			c->vis[nxt] = 0;
		}
	}
}

int	main(void)
{
	t_point *pts = NULL;
	size_t   cap = 0, len = 0;

	// Read "x, y" pairs from stdin using fscanf until EOF
	while (1)
	{
		float x, y;
		int r = fscanf(stdin, " %f , %f", &x, &y);
		if (r == 2)
		{
			if (len == cap)
			{
				size_t ncap = cap ? cap * 2 : 16;
				t_point *tmp = (t_point *)realloc(pts, ncap * sizeof(*pts));
				if (!tmp)
				{
					free(pts);
					fprintf(stderr, "malloc failed\n");
					return 1;
				}
				pts = tmp;
				cap = ncap;
			}
			pts[len].x = x;
			pts[len].y = y;
			len++;
		}
		else if (r == EOF)
		{
			if (ferror(stdin))
			{
				free(pts);
				fprintf(stderr, "read error\n");
				return 1;
			}
			break;
		}
		else
		{
			// Line didn't match "x, y" — stop (or you could skip invalid lines)
			break;
		}
	}

	int n = (int)len;
	if (n <= 1)
	{
		fprintf(stdout, "0.00");
		free(pts);
		return 0;
	}

	// Allocate distance matrix
	float **dist = (float **)calloc(n, sizeof(*dist));
	if (!dist)
	{
		free(pts);
		fprintf(stderr, "malloc failed\n");
		return 1;
	}
	for (int i = 0; i < n; ++i)
	{
		dist[i] = (float *)calloc(n, sizeof(**dist));
		if (!dist[i]) {
			xfree2d(dist, n);
			free(pts);
			fprintf(stderr, "malloc failed\n");
			return 1;
		}
	}
	build_dist(dist, pts, n);

	// Prepare context
	t_ctx ctx;
	ctx.n = n;
	ctx.dist = dist;
	ctx.vis = (int *)calloc(n, sizeof(int));
	if (!ctx.vis)
	{
		xfree2d(dist, n);
		free(pts);
		fprintf(stderr, "malloc failed\n");
		return 1;
	}
	ctx.best = 1e30f; // big number
	ctx.vis[0] = 1;

	// Backtracking from city 0
	dfs(&ctx, 0, 1, 0.0f);

	// Output length with 2 decimals
	fprintf(stdout, "%.2f", ctx.best);

	// Cleanup
	free(ctx.vis);
	xfree2d(dist, n);
	free(pts);
	return 0;
}