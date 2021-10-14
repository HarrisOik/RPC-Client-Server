/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _VECT_H_RPCGEN
#define _VECT_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct vectors {
	struct {
		u_int vector_len;
		int *vector_val;
	} vector;
	int n;
};
typedef struct vectors vectors;

struct vector_pair {
	vectors vector_a;
	vectors vector_b;
};
typedef struct vector_pair vector_pair;

struct make_vector {
	vector_pair pair;
	float r;
};
typedef struct make_vector make_vector;

struct results_3 {
	struct {
		u_int avg_len;
		float *avg_val;
	} avg;
};
typedef struct results_3 results_3;

struct results_4 {
	struct {
		u_int new_vector_len;
		float *new_vector_val;
	} new_vector;
};
typedef struct results_4 results_4;

#define VECT_PROG 0x23451111
#define VECT_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define MAG 1
extern  float * mag_1(vectors *, CLIENT *);
extern  float * mag_1_svc(vectors *, struct svc_req *);
#define DOTPROD 2
extern  int * dotprod_1(vector_pair *, CLIENT *);
extern  int * dotprod_1_svc(vector_pair *, struct svc_req *);
#define VECAVG 3
extern  results_3 * vecavg_1(vector_pair *, CLIENT *);
extern  results_3 * vecavg_1_svc(vector_pair *, struct svc_req *);
#define NEWVEC 4
extern  results_4 * newvec_1(make_vector *, CLIENT *);
extern  results_4 * newvec_1_svc(make_vector *, struct svc_req *);
extern int vect_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define MAG 1
extern  float * mag_1();
extern  float * mag_1_svc();
#define DOTPROD 2
extern  int * dotprod_1();
extern  int * dotprod_1_svc();
#define VECAVG 3
extern  results_3 * vecavg_1();
extern  results_3 * vecavg_1_svc();
#define NEWVEC 4
extern  results_4 * newvec_1();
extern  results_4 * newvec_1_svc();
extern int vect_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_vectors (XDR *, vectors*);
extern  bool_t xdr_vector_pair (XDR *, vector_pair*);
extern  bool_t xdr_make_vector (XDR *, make_vector*);
extern  bool_t xdr_results_3 (XDR *, results_3*);
extern  bool_t xdr_results_4 (XDR *, results_4*);

#else /* K&R C */
extern bool_t xdr_vectors ();
extern bool_t xdr_vector_pair ();
extern bool_t xdr_make_vector ();
extern bool_t xdr_results_3 ();
extern bool_t xdr_results_4 ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_VECT_H_RPCGEN */