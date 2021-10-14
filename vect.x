struct vectors {
	int vector<>;
	int n;
};

struct vector_pair{
	vectors vector_a;
	vectors vector_b;
};

struct make_vector{
	vector_pair pair;
	float r;
};

struct results_3{
	float avg<2>;
};

struct results_4{
	float new_vector<>;
};

program VECT_PROG {
		version VECT_VERS {
			float MAG(vectors) = 1;
			int DOTPROD(vector_pair) = 2;
			results_3 VECAVG(vector_pair) = 3;
			results_4 NEWVEC(make_vector) = 4;
	} = 1;
} = 0x23451111;
