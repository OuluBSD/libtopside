#ifndef _DrawAlt_Chameleon_h_
#define _DrawAlt_Chameleon_h_

//Copying: U++ compatibility headers

NAMESPACE_UPP


enum LookOp {
	LOOK_PAINT,
	LOOK_MARGINS,
	LOOK_PAINTEDGE,
};


template <class T>
struct ChStyle {
	byte status;
	byte registered;
	T   *standard;

	const T& Standard() const      { return *standard; }
	T&       Write() const         { T& x = *(T *)this; x.status = 2; return x; }
	void     Assign(const T& src)  { *(T *)this = src; }

	ChStyle()                      { status = 0; registered = 0; standard = NULL; }
};



Rect ChMargins(const Value& look);
void ChPaintEdge(Draw& w, const Rect& r, const Value& look, Color ink = Null);
void ChPaint(Draw& w, int x, int y, int cx, int cy, const Value& look, Color ink = Null);


Value sChOp(Draw& w, const Rect& r, const Value& v, int op, Color ink = Null);


// CH_VAR0 allows inserting action into _Write (missing ending '}')
#define CH_VAR0(chtype, type, name, init) \
chtype& COMBINE(ch_var__, name)(); \
void COMBINE(ch_init__, name)() { \
	COMBINE(ch_var__, name)(); \
} \
\
chtype& COMBINE(ch_var__, name)() { \
	static chtype b; \
	if(b.status == 0) { \
		ChRegisterStyle__(b.status, b.registered, COMBINE(ch_init__, name)); \
		b.value = init; \
		b.status = 1; \
	} \
	return b; \
} \
\
type name() { return COMBINE(ch_var__, name)().value; } \
void COMBINE(name, _Write)(type v) { COMBINE(ch_var__, name)().Write().value = v;

#define CH_VAR(chtype, type, name, init) CH_VAR0(chtype, type, name, init) }

struct ChColor : ChStyle<ChColor> { Color value; };
#define CH_COLOR(name, init) CH_VAR(ChColor, Color, name, init)

struct ChInt : ChStyle<ChInt> { int value; };
#define CH_INT(name, init) CH_VAR(ChInt, int, name, init)

struct ChValue : ChStyle<ChValue> { Value value; };
#define CH_VALUE(name, init) CH_VAR(ChValue, Value, name, init)

struct ChImage : ChStyle<ChImage> { Image value; };
#define CH_IMAGE(name, init) CH_VAR(ChImage, Image, name, init)

void ChRegisterStyle__(byte& state, byte& registered, void (*init)());

#define CH_STYLE(klass, type, style) \
struct COMBINE5(klass, __, type, __, style) : klass::type { \
	void Init(); \
	static void InitIt(); \
}; \
\
void COMBINE5(klass, __, type, __, style)::InitIt() { \
	klass::style(); \
} \
\
const klass::type& klass::style() \
{ \
	static COMBINE5(klass, __, type, __, style) b, standard; \
	if(b.status == 0) { \
		ChRegisterStyle__(b.status, b.registered, COMBINE5(klass, __, type, __, style)::InitIt); \
		b.Init(); \
		b.status = 1; \
		standard = b; \
		standard.standard = b.standard = &standard; \
	} \
	return b; \
} \
\
void COMBINE5(klass, __, type, __, style)::Init()

END_UPP_NAMESPACE

#endif
