//===========================================================================
//=============================nurbs private variables=======================
//===========================================================================
static int p;
static float du;
static float x[MAX_P], y[MAX_P], weight[MAX_P], knot[MAX_P], basis[MAX_P], left[MAX_P - 1], right[MAX_P - 1];
static float x_out = 0, y_out = 0;


void reset_nurbs (void) {
	p = 0;
	x_out = 0;
	y_out = 0;
	memset (&x, 0, MAX_P * sizeof(float));
	memset (&y, 0, MAX_P * sizeof(float));
	memset (&weight, 0, MAX_P * sizeof(float));
	memset (&knot, 0, MAX_P * sizeof(float));
	memset (&basis, 0, MAX_P * sizeof(float));
	memset (&left, 0, (MAX_P-1) * sizeof(float));
	memset (&right, 0, (MAX_P-1) * sizeof(float));
}

reset_nurbs ();

void push_back (float cx, float cy, float cw, float ck) {
	for (int i = 0; i < p - 1; i++) {
		x[i] = x[i+1];	
		y[i] = y[i+1];
		weight[i] = weight[i+1];
		knot[i] = knot[i+1];
	}
	x[p-1] = cx;
	y[p-1] = cy;
	weight[p-1] = cw;
	knot[p-1] = ck;
}



// destination = [x,y,z,e]
void nurbs_move (void) {
	destination[0] = x_out;
	destination[1] = y_out;
	// destination[3] = e_out; /* Extrusion Not Implemented */
	prepare_move ();
}

void nurbs_start (int p_seen) {
	p = p_seen;
}

void nurbs_end () {
	reset_nurbs ();
}

void nurbs_next () {
	// GET THESE FROM BUFFER
	float cx, cy, cw, ck;
	push_back (cx, cy, cw, ck);
	
}