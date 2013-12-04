//===========================================================================
//=============================nurbs private variables=======================
//===========================================================================
static int p;
static float du;
static float x[MAX_P], y[MAX_P], weight[MAX_P], knot[MAX_P], basis[MAX_P], left[MAX_P - 1], right[MAX_P - 1];
memset (&x, 0, MAX_P * sizeof(float));
memset (&y, 0, MAX_P * sizeof(float));
memset (&weight, 0, MAX_P * sizeof(float));
memset (&knot, 0, MAX_P * sizeof(float));
memset (&basis, 0, MAX_P * sizeof(float));
memset (&left, 0, (MAX_P-1) * sizeof(float));
memset (&right, 0, (MAX_P-1) * sizeof(float));

void push_back (float *array, int len, float new) {
	for (int i = 0; i < len - 1; i++) {
		array[i] = array[len-1];	
	}
	array[len-1] = new;
}

