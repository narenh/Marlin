
//===========================================================================
//=============================nurbs private stuff=======================
//===========================================================================
#define DEGREE 2
#define MAX_P DEGREE + 1
static float du, u;
static float xs[MAX_P], ys[MAX_P], weight[MAX_P], knot[DEGREE * 2], basis[MAX_P], left[MAX_P - 1], right[MAX_P - 1];
static float x_out = 0, y_out = 0;
void reset_nurbs (void);
void nurbs_curve (void);
void reset_nurbs ();
void nurbs_move (void);
void nurbs_basis (void);
void push_back (float cx, float cy, float cw, float ck);
void nurbs_start (int p_seen);
void nurbs_next ();



void reset_nurbs (void) {

	x_out = 0;
	y_out = 0;
	memset (&xs, 0, MAX_P * sizeof(float));
	memset (&ys, 0, MAX_P * sizeof(float));
	memset (&weight, 0, MAX_P * sizeof(float));
	memset (&knot, 0, MAX_P * sizeof(float));
	memset (&basis, 0, MAX_P * sizeof(float));
	memset (&left, 0, (MAX_P-1) * sizeof(float));
	memset (&right, 0, (MAX_P-1) * sizeof(float));
}



void push_back (float cx, float cy, float cw, float ck) {
	for (int i = 0; i < (2 * MAX_P) - 1; i++) {
		knot[i] = knot[i+1];	
	}
	knot[(2 * MAX_P) - 1] = ck;
	for (int i = 0; i < MAX_P - 1; i++) {
		xs[i] = xs[i+1];	
		ys[i] = ys[i+1];
		weight[i] = weight[i+1];
	}
	xs[p-1] = cx;
	ys[p-1] = cy;
	weight[p-1] = cw;
}



// destination = [x,y,z,e]
void nurbs_move (void) {
	destination[0] = x_out;
	destination[1] = y_out;
	// destination[3] = e_out; /* Extrusion Not Implemented */
	prepare_move ();
}

void nurbs_start (int p_seen) {
	reset_nurbs ();
	int tmp;
	if(code_seen('U')) du = code_value();
	if(code_seen('K')) {
		tmp = code_value();
		knot[0] = tmp;
		knot[1] = tmp;
		knot[2] = tmp;
	}
   if(code_seen('K')) knot[3] = code_value();
	p = p_seen;
}


void nurbs_next () {

	float cx, cy, cw;
	if (code_seen('X')) cx = code_value ();
	if (code_seen('Y')) cy = code_value ();
	if (code_seen('W')) cw = code_value ();
	if (code_seen('K')) ck = code_value ();
	push_back (cx, cy, cw, ck);

	while (u < knot[3]) {
		nurbs_basis ();
		nurbs_curve ();
		nurbs_move ();
		u += du;
	}
	
}

void nurbs_basis (void) {
	basis[0] = 1.0;
	float saved, temp;
	// todo: set/replace i in terms of p
	for (int j = 1; j <= DEGREE; j++) {
		left[j] = u - knot[DEGREE+1-j];
		right[j] = knot[DEGREE+j] - u;
		saved = 0.0;
		for (int r = 0; r < j; r++) {
			temp = basis[r] / (right[r+1] + left[j-r]);
			basis[r] = saved + right[r+1] * temp;
			saved = left[j-r] * temp;
		}
		basis[j] = saved;
	}
}
void nurbs_curve (void) {
	x_out = 0.0;
	y_out = 0.0;
	float Nsum = 0.0;
	for (int j = 0; j <= degree; j++) {
		basis[j] *= weight[j];
		Nsum += basis[j];
		x_out += basis[j] * xs[i];
		y_out += basis[j] * ys[i];
	}
	x_out /= Nsum;
	y_out /= Nsum;
}






