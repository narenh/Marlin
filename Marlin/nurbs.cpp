
void basis_funs() {
	basis[0] = 1.0;
	float saved, temp;
	// todo: set/replace i in terms of p
	for (int j = 1; j <= degree; j++) {
		left[j] = u - knot[i+1-j];
		right[j] = knot[i+j] - u;
		saved = 0.0;
		for (int r = 0; r < j; r++) {
			temp = basis[r] / (right[r+1] + left[j-r]);
			basis[r] = saved + right[r+1] * temp;
			saved = left[j-r] * temp;
		}
		basis[j] = saved;
	}
}

void curve() {
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

