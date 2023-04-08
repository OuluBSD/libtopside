#ifndef GLD_ARRAYELT_H
#define GLD_ARRAYELT_H


extern GLboolean _ae_create_context( GLcontext *ctx );
extern void _ae_destroy_context( GLcontext *ctx );
extern void _ae_invalidate_state( GLcontext *ctx, GLuint new_state );
extern void GLAPIENTRY _ae_loopback_array_elt( GLint elt );

#endif
