// stdlibs we need
#include <stdio.h>
#include <math.h>

// basic allegro functions to give us a window and an OpenGL context
#include <allegro5/allegro.h>

//all matrix maths functions
#include "matrix.h"

// opengl functions
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

// basic window constants
#define FPS 60
#define SCREEN_W 1280
#define SCREEN_H 720

// for getpwuid
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


struct glinfo {
	GLuint program;
	GLint attribute_coord2d;
	GLint attribute_colour;
	GLuint cube_vertices;
	GLuint cube_colours;
	GLuint cube_elements;
	GLint uniform_mvp;
	GLint uniform_rotation;
	GLint uniform_translation;
};

struct allegroinfo {
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_EVENT ev;
};

GLint	MakeShader(const char * filename, GLenum type);
void	PrintLog(GLuint object);
int		InitResources(struct glinfo * glpointers);
void	Draw(int rotation, struct glinfo * glpointers);
struct allegroinfo* StartAllegro(void);

int main() {
	bool redraw = true;
	struct allegroinfo* alinfo = StartAllegro();
	int rotation = 0;
	struct glinfo* glpointers = (struct glinfo*)malloc(sizeof(struct glinfo));
	
	InitResources(glpointers);
	
	while (1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(alinfo -> event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			rotation++;
		}
		else
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
			
		if (redraw && al_is_event_queue_empty(alinfo -> event_queue)) {
			redraw = false;
			
			Draw(rotation, glpointers);
			al_flip_display();
		}
	}
	
	return 0;
}

struct allegroinfo* StartAllegro(void) {
	struct allegroinfo* retval = (struct allegroinfo*)malloc(sizeof(struct allegroinfo));
	
	if (!al_init()) {
		fprintf(stderr, "failed to initialise allegro!\n");
		return 0;
	}
	
	retval->timer = al_create_timer(1.0 / FPS);
	if (!retval -> timer) {
		fprintf(stderr, "failed to create timer!\n");
		return 0;
	}
	
	
	al_set_new_display_flags(ALLEGRO_OPENGL);
	printf("%d\n", al_get_new_display_option(ALLEGRO_DEPTH_SIZE, NULL));
	
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 24, ALLEGRO_SUGGEST);
	printf("%d\n", al_get_new_display_option(ALLEGRO_DEPTH_SIZE, NULL));
	
	retval -> display =  al_create_display(SCREEN_W , SCREEN_H);
	if (!retval -> display) {
		fprintf(stderr, "failed to create display!\n");
		return 0;
	}
	
	retval -> event_queue = al_create_event_queue();
	if (!retval -> event_queue) {
		fprintf(stderr, "failed to create event queue!\n");
		return 0;
	}
	
	al_register_event_source(retval -> event_queue, al_get_display_event_source(retval->display));
	al_register_event_source(retval -> event_queue, al_get_timer_event_source(retval->timer));
	al_start_timer(retval -> timer);
	
	return retval;
}

int InitResources(struct glinfo * glpointers) {
	GLint link_ok = GL_FALSE;
	GLuint vs;
	GLuint fs;
	const char* attribute_name;
	
	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
	};
	
	GLfloat cube_colours[] = {
		//front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};
	
	GLushort cube_elements[] = {
		//front
		0, 1, 2,
		2, 3, 0,
		//top
		1, 5, 6,
		6, 2, 1,
		//back
		7, 6, 5,
		5, 4, 7,
		//bottom
		4, 0, 3,
		3, 7, 4,
		//left
		4, 5, 1,
		1, 0, 4,
		//right
		3, 2, 6,
		6, 7, 3
	};
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	// vertices
	glGenBuffers(1, &(glpointers -> cube_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, glpointers -> cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	
	// colors
	glGenBuffers(1, &(glpointers -> cube_colours));
	glBindBuffer(GL_ARRAY_BUFFER, glpointers -> cube_colours);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colours), cube_colours, GL_STATIC_DRAW);
	
	// elements
	glGenBuffers(1, &(glpointers -> cube_elements));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glpointers -> cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	// load shaders
	struct passwd *pw = getpwuid(getuid());
	char vert[100];
	char frag[100];
	
	strcpy(vert, pw->pw_dir);
	strcat(vert, "/libtopside/uppsrc/ReferenceOgl/vert.glsl");
	if ((vs = MakeShader(vert, GL_VERTEX_SHADER)) == 0)
		return 0;
	
	strcpy(frag, pw->pw_dir);
	strcat(frag, "/libtopside/uppsrc/ReferenceOgl/frag.glsl");
	if ((fs = MakeShader(frag, GL_FRAGMENT_SHADER)) == 0)
		return 0;
	
	
	// link shaders
	glpointers -> program = glCreateProgram();
	glAttachShader(glpointers -> program, vs);
	glAttachShader(glpointers -> program, fs);
	glLinkProgram(glpointers -> program);
	glGetProgramiv(glpointers -> program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		PrintLog(glpointers -> program);
		return 0;
	}
	
	
	// read input value coordinates from compiled program
	attribute_name = "coord2d";
	glpointers -> attribute_coord2d = glGetAttribLocation(glpointers -> program, attribute_name);
	if (glpointers -> attribute_coord2d == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		return 0;
	}
	
	attribute_name = "v_colour";
	glpointers -> attribute_colour = glGetAttribLocation(glpointers -> program, attribute_name);
	if (glpointers -> attribute_colour == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		return 0;
	}
	
	attribute_name = "mvp";
	glpointers -> uniform_mvp = glGetUniformLocation(glpointers -> program, attribute_name);
	if (glpointers -> uniform_mvp == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", attribute_name);
		return 0;
	}
	
	return 1;
}

void Draw(int rotation, struct glinfo * glpointers) {
	int size;
	float r[4][4];	//holds a rotation, to be applied before m, so multiplied in before it
	float m[4][4];	//holds a translation to move the cube away from the scree
	float v[4][4];	//holds the view matrix output by lookat()
	float p[4][4];	//holds the projection matrix we get from perspective
	float mvp[4][4];//holds the final matrix equal to p * v * m * r
	float temp[4][4];
	float temp2[4][4];
	
	#define DEG2RAD(x) (x / 180.0 * M_PI)
	perspective(DEG2RAD(45.0), SCREEN_W / (float) SCREEN_H, 0.1, 100, p);
	Translate(0.0, 0.0, -4.0, m);
	lookat(0, 2, 0, 0, 0, -4, 0, 1, 0, v);
	rotate(rotation, 0.0, 1.0, 0.0, r);
	
	if (rotation % 360 == 0) {
		printf("Full turn!\n");
	}
	
	// rotation * model * lookat * perspective
	multmatrix(p, v, temp);
	multmatrix(temp, m, temp2);
	multmatrix(temp2, r, mvp);
	
	// Clear the background as white
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(glpointers -> program);
	
	glUniformMatrix4fv(glpointers -> uniform_mvp, 1, GL_FALSE, (GLfloat *) mvp);
	
	glBindBuffer(GL_ARRAY_BUFFER, glpointers -> cube_vertices);
	
	glEnableVertexAttribArray(glpointers -> attribute_coord2d);
	
	// Describe our vertices array to OpenGL (it can't guess its format automatically)
	glVertexAttribPointer(
		glpointers -> attribute_coord2d,	// attribute
		3,									// number of elements per vertex, here (x,y,z)
		GL_FLOAT,							// the type of each element
		GL_FALSE,							// take our values as-is
		0,									// stride
		0									// offset of first element
	);
	
	glBindBuffer(GL_ARRAY_BUFFER, glpointers -> cube_colours);
	glEnableVertexAttribArray(glpointers -> attribute_colour);
	
	glVertexAttribPointer(
		glpointers -> attribute_colour,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
	
	// Push each element in buffer_vertices to the vertex shader
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glpointers -> cube_elements);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	
	glDisableVertexAttribArray(glpointers -> attribute_coord2d);
	glDisableVertexAttribArray(glpointers -> attribute_colour);
	
}

#define BLOCKSIZE 512
#define BLOCK (BLOCKSIZE*sizeof(char))

char* readfile(const char* filename) {
	int size = BLOCK;
	int read = 0; // total we've read
	char * retval = (char*)malloc(size);
	char * temp;
	FILE * in = fopen(filename, "r");
	
	if (!retval) {
		printf("Memory allocation failure in readfile\n");
		return NULL;
	}
	
	if (! in) {
		printf("%s\n", strerror(errno));
	}
	
	read += fread(retval, sizeof(char), BLOCKSIZE, in);
	
	while (!feof(in)) {
		temp = (char*)realloc(retval, size += BLOCK);
		if (temp) {
			retval = temp;
		}
		else {
			printf("Memory allocation failure in readfile\n");
			return NULL;
		}
		read += fread(retval + read, sizeof(char), BLOCK, in);
	}
	
	retval = (char*)realloc(retval, read + 1);
	retval[read] = '\0';
	return retval;
}

// Display compilation errors from the OpenGL shader compiler

void PrintLog(GLuint object) {
	GLint log_length = 0;
	char *log;
	
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else
	if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}
		
	log = (char*) malloc(log_length);
	
	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);
			
	fprintf(stderr, "%s", log);
	free(log);
}

GLint MakeShader(const char * filename, GLenum type) {
	const GLchar* source = readfile(filename);
	GLuint shader = glCreateShader(type);
	GLint compile_ok = GL_FALSE;
	
	if (source == NULL) {
		printf("Failure reading file\n");
		return 0;
	}
	
	glShaderSource(shader, 1, &source, NULL);
	
	free((void*)source);
	
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		fprintf(stderr, "%s", filename);
		PrintLog(shader);
		glDeleteShader(shader);
		return 0;
	}
	
	return shader;
}
