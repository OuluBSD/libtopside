#include "LocalVR.h"


NAMESPACE_HMD_BEGIN


void tracking_model_init(struct tracking_model *model, unsigned int num_points)
{
	model->num_points = num_points;
	model->points = (vec3*)malloc(num_points * sizeof(vec3));
	model->normals = (vec3*)malloc(num_points * sizeof(vec3));
}

void tracking_model_fini(struct tracking_model *model)
{
	free(model->points);
	free(model->normals);
	memset(model, 0, sizeof(*model));
}

void tracking_model_copy(struct tracking_model *dst, struct tracking_model *src)
{
	free(dst->points);
	free(dst->normals);
	tracking_model_init(dst, src->num_points);
	memcpy(dst->points, src->points, src->num_points * sizeof(vec3));
	memcpy(dst->normals, src->points, src->num_points * sizeof(vec3));
}

void tracking_model_dump_obj(struct tracking_model *model, const char *name)
{
	unsigned int i;

	printf("# ouvrt OBJ File: ''\n"
	       "o %s\n", name);

	for (i = 0; i < model->num_points; i++) {
		vec3 *p = &model->points[i];
		vec3 *n = &model->normals[i];

		printf("v %9.6f %9.6f %9.6f\n"
		       "v %9.6f %9.6f %9.6f\n",
		       p->data[0], p->data[1], p->data[2],
		       p->data[0] + n->data[0], p->data[1] + n->data[1], p->data[2] + n->data[2]);
	}
	for (i = 0; i < model->num_points; i++)
		printf("l %d %d\n", i * 2 + 1, i * 2 + 2);
}

void tracking_model_dump_struct(struct tracking_model *model)
{
	unsigned int i;

	printf("struct tracking_model model = {\n"
	       "\t.num_points = %d\n"
	       "\t.points = {\n", model->num_points);

	for (i = 0; i < model->num_points; i++) {
		vec3 *p = &model->points[i];

		printf("\t\t{ %9.6f, %9.6f, %9.6f },\n", p->data[0], p->data[1], p->data[2]);
	}

	printf("\t},\n"
	       "\t.normals = {\n");

	for (i = 0; i < model->num_points; i++) {
		vec3 *n = &model->normals[i];

		printf("\t\t{ %9.6f, %9.6f, %9.6f },\n", n->data[0], n->data[1], n->data[2]);
	}

	printf("\t},\n"
	       "};\n");
}


NAMESPACE_HMD_END

