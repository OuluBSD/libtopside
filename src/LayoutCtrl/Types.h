#ifndef _LayoutCtrl_Types_h_
#define _LayoutCtrl_Types_h_

NAMESPACE_LAYOUT_BEGIN

class Element;


typedef ArrayMap<String, String>				StrMap;
typedef Vector<Element*>						ElementsVector;
typedef Vector<int>								IntVector;
typedef Vector<String>							StringVector;

inline int FindPos(const ElementsVector& vec, Element* el) {
	for(int i = 0; i < vec.GetCount(); i++)
		if (vec[i] == el)
			return i;
	return -1;
}

const unsigned int FontDecorationNone			= 0x00;
const unsigned int FontDecorationUnderline		= 0x01;
const unsigned int FontDecorationLinethrough	= 0x02;
const unsigned int FontDecorationOverline		= 0x04;


struct Margins {
	int	left;
	int	right;
	int top;
	int bottom;

	Margins() {
		left = right = top = bottom = 0;
	}

	int Width()		const	{ return left + right; }
	int Height()	const	{ return top + bottom; }
};

struct Position : public Moveable<Position> {
	int	x ;
	int	y;
	int	width;
	int	height;
	
	operator Rect() const {return RectC(x, y, width, height);}
	
	Position() {
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	Position(int x, int y, int width, int height) {
		this->x			= x;
		this->y			= y;
		this->width		= width;
		this->height	= height;
	}
	
	Rect GetRect() const {return RectC(x, y, width, height);}

	int Right()		const		{ return x + width;		}
	int Bottom()	const		{ return y + height;	}
	int Left()		const		{ return x;				}
	int Top()		const		{ return y;				}

	void operator+=(const Margins& mg) {
		x		-= mg.left;
		y		-= mg.top;
		width	+= mg.left + mg.right;
		height	+= mg.top + mg.bottom;
	}
	void operator-=(const Margins& mg) {
		x		+= mg.left;
		y		+= mg.top;
		width	-= mg.left + mg.right;
		height	-= mg.top + mg.bottom;
	}

	void Clear() {
		x = y = width = height = 0;
	}

	void operator=(const Size& sz) {
		width	= sz.cx;
		height	= sz.cy;
	}

	void MoveTo(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool DoesIntersect() const {return true;}
	bool DoesIntersect(const Position& val) const {
		//if(!val) return true;

		return (
			Left()			<= val.Right()		&&
			Right()			>= val.Left()		&&
			Bottom()		>= val.Top()		&&
			Top()			<= val.Bottom()	)
			|| (
			val.Left()		<= Right()			&&
			val.Right()		>= Left()			&&
			val.Bottom()	>= Top()			&&
			val.Top()		<= Bottom()			);
	}

	bool IsEmpty() const {
		if(!width && !height)
		{
			return true;
		}
		return false;
	}

	bool IsPointInside(int x, int y) const
	{
		if(x >= Left() && x <= Right() && y >= Top() && y <= Bottom())
		{
			return true;
		}
		return false;
	}
};

struct FontMetrics {
	int		height;
	int		ascent;
	int		descent;
	int		x_height;
	bool	draw_spaces;

	FontMetrics() {
		height			= 0;
		ascent			= 0;
		descent			= 0;
		x_height		= 0;
		draw_spaces		= true;
	}
	int BaseLine()	{ return descent; }
};

struct FontItem {
	uint32		font;
	FontMetrics	metrics;
};

typedef ArrayMap<String, FontItem>	FontsMap;

enum DrawFlag {
	DrawRoot,
	DrawBlock,
	DrawFloats,
	DrawInlines,
	DrawPositioned,
};

#define  StyleDisplayStrings		"none;block;inline;inline-block;inline-table;list-item;table;table-caption;table-cell;table-column;table-column-group;table-footer-group;table-header-group;table-row;table-row-group"

enum StyleDisplay {
	DisplayNone,
	DisplayBlock,
	DisplayInline,
	DisplayInlineBlock,
	DisplayInlineTable,
	DisplayListItem,
	DisplayTable,
	DisplayTableCaption,
	DisplayTableCell,
	DisplayTableColumn,
	DisplayTableColumnGroup,
	DisplayTableFooterGroup,
	DisplayTableHeaderGroup,
	DisplayTableRow,
	DisplayTableRowGroup,
	DisplayInlineText,
};

enum StyleBorder {
	BorderNope,
	BorderNone,
	BorderHidden,
	BorderDotted,
	BorderDashed,
	BorderSolid,
	BorderDouble
};

#define  FontSizeStrings		"xx-small;x-small;small;medium;large;x-large;xx-large;smaller;larger"

enum FontSize {
	FontSizeXXSmall,
	FontSizeXSmall,
	FontSizeSmall,
	FontSizeMedium,
	FontSizeLarge,
	FontSizeXLarge,
	FontSizeXXLarge,
	FontSizeSmaller,
	FontSizeLarger,
};

#define  FontstyleStrings		"normal;italic"

enum FontStyle {
	FontStyleNormal,
	FontStyleItalic
};

#define  FontVariantStrings		"normal;small-caps"

enum FontVariant {
	FontVariantNormal,
	FontVariantItalic
};

#define  FontWeightStrings	"normal;bold;bolder;lighter100;200;300;400;500;600;700"

enum FontWeight {
	FontWeightNormal,
	FontWeightBold,
	FontWeightBolder,
	FontWeightLighter,
	FontWeight100,
	FontWeight200,
	FontWeight300,
	FontWeight400,
	FontWeight500,
	FontWeight600,
	FontWeight700
};

#define  ListStyleTypeStrings	"none;circle;disc;square;armenian;cjk-ideographic;decimal;decimal-leading-zero;georgian;hebrew;hiragana;hiragana-iroha;katakana;katakana-iroha;lower-alpha;lower-greek;lower-latin;lower-roman;upper-alpha;upper-latin;upper-roman"

enum ListStyleType
{
	ListStyleTypeNone,
	ListStyleTypeCircle,
	ListStyleTypeDisc,
	ListStyleTypeSquare,
	ListStyleTypeArmenian,
	ListStyleTypeCjkIdeographic,
	ListStyleTypeDecimal,
	ListStyleTypeDecimalLeadingZero,
	ListStyleTypeGeorgian,
	ListStyleTypeHebrew,
	ListStyleTypeHiragana,
	ListStyleTypeHiraganaIroha,
	ListStyleTypeKatakana,
	ListStyleTypeKatakanaIroha,
	ListStyleTypeLowerAlpha,
	ListStyleTypeLowerGreek,
	ListStyleTypeLowerLatin,
	ListStyleTypeLowerRoman,
	ListStyleTypeUpperAlpha,
	ListStyleTypeUpperLatin,
	ListStyleTypeUpperRoman,
};

#define  ListStylepositionStrings	"inside;outside"

enum ListStylePosition
{
	ListStylepositionInside,
	ListStylepositionOutside
};

#define  VerticalAlignStrings	"baseline;sub;super;top;text-top;middle;bottom;text-bottom"

enum VerticalAlign
{
	VABaseline,
	VASub,
	VASuper,
	VATop,
	VATextTop,
	VAMiddle,
	VABottom,
	VATextBottom
};

#define  BorderWidthStrings	"thin;medium;thick"

enum BorderWidth
{
	BorderWidthThin,
	BorderWidthMedium,
	BorderWidthThick
};

#define  BorderStyleStrings	"none;hidden;dotted;dashed;solid;double;groove;ridge;inset;outset"

enum BorderStyle
{
	BorderStyleNone,
	BorderStyleHidden,
	BorderStyleDotted,
	BorderStyleDashed,
	BorderStyleSolid,
	BorderStyleDouble,
	BorderStyleGroove,
	BorderStyleRidge,
	BorderStyleInset,
	BorderStyleOutset
};

#define  ElementFloatStrings	"none;left;right"

enum ElementFloat
{
	FloatNone,
	FloatLeft,
	FloatRight
};

#define  ElementClearStrings	"none;left;right;both"

enum ElementClear
{
	ClearNone,
	ClearLeft,
	ClearRight,
	ClearBoth
};

#define  BackgroundAttachmentStrings	"scroll;fixed"

enum BackgroundAttachment
{
	BackgroundAttachmentScroll,
	BackgroundAttachmentFixed
};

#define  BackgroundRepeatStrings	"repeat;repeat-x;repeat-y;no-repeat"

enum BackgroundRepeat
{
	BackgroundRepeatRepeat,
	BackgroundRepeatRepeatX,
	BackgroundRepeatRepeatY,
	BackgroundRepeatNoRepeat
};

#define  BackgroundBoxStrings	"border-box;padding-box;content-box"

enum BackgroundBox
{
	BackgroundBoxBorder,
	BackgroundBoxPadding,
	BackgroundBoxContent
};

#define ElementPositionStrings	"static;relative;absolute;fixed"

enum ElementPosition
{
	ElementPositionStatic,
	ElementPositionRelative,
	ElementPositionAbsolute,
	ElementPositionFixed,
};

#define TextAlignStrings		"left;right;center;justify"

enum TextAlign
{
	TextAlignLeft,
	TextAlignRight,
	TextAlignCenter,
	TextAlignJustify
};

#define TextTransformStrings		"none;capitalize;uppercase;lowercase"

enum TextTransform
{
	TextTransformNone,
	TextTransformCapitalize,
	TextTransformUppercase,
	TextTransformLowercase
};

#define WhiteSpaceStrings		"normal;nowrap;pre;pre-line;pre-wrap"

enum WhiteSpace
{
	WhiteSpaceNormal,
	WhiteSpaceNowrap,
	WhiteSpacePre,
	WhiteSpacePreLine,
	WhiteSpacePreWrap
};

#define OverflowStrings		"visible;hidden;scroll;auto;no-display;no-content"

enum Overflow
{
	OverflowVisible,
	OverflowHidden,
	OverflowScroll,
	OverflowAuto,
	OverflowNoDisplay,
	OverflowNoContent
};

#define BackgroundSizeStrings		"auto;cover;contain"

enum BackgroundSize
{
	BackgroundSizeAuto,
	BackgroundSizeCover,
	BackgroundSizeContain,
};

#define VisibilityStrings			"visible;hidden;collapse"

enum Visibility
{
	VisibilityVisible,
	VisibilityHidden,
	VisibilityCollapse,
};

#define BorderCollapseStrings		"collapse;separate"

enum BorderCollapse
{
	BorderCollapseCollapse,
	BorderCollapseSeparate,
};


#define PseudoClassStrings		"only-child;only-of-type;first-child;first-of-type;last-child;last-of-type;nth-child;nth-of-type;nth-last-child;nth-last-of-type;not"

enum PseudoClass
{
	PseudoClassOnlyChild,
	PseudoClassOnlyOfType,
	PseudoClassFirstChild,
	PseudoClassFirstOfType,
	PseudoClassLastChild,
	PseudoClassLastOfType,
	PseudoClassNthChild,
	PseudoClassNthOfType,
	PseudoClassNthLastChild,
	PseudoClassNthLastOfType,
	PseudoClassNot,
};

#define ContentPropertyString		"none;normal;open-quote;close-quote;no-open-quote;no-close-quote"

enum ContentProperty
{
	ContentPropertyNone,
	ContentPropertyNormal,
	ContentPropertyOpenQuote,
	ContentPropertyCloseQuote,
	ContentPropertyNoOpenQuote,
	ContentPropertyNoCloseQuote,
};


struct FloatedBox : public Moveable<FloatedBox>
{
	typedef Vector<FloatedBox>	vector;

	Position		pos;
	ElementFloat	float_side;
	ElementClear	clear_floats;
	Element*		el;
};

struct IntIntCache
{
	int		hash;
	int		val;
	bool	is_valid;
	bool	is_default;

	IntIntCache()
	{
		hash		= 0;
		val			= 0;
		is_valid	= false;
		is_default	= false;
	}
	void invalidate()
	{
		is_valid	= false;
		is_default	= false;
	}
	void SetValue(int vHash, int vVal)
	{
		hash		= vHash;
		val			= vVal;
		is_valid	= true;
	}
};

enum SelectResult
{
	SelectNoMatch				= 0x00,
	SelectMatch					= 0x01,
	SelectMatchPseudoClass		= 0x02,
	SelectMatchWithBefore		= 0x10,
	SelectMatchWithAfter		= 0x20,
};

template<class T>
class DefValue {
	T		val;
	bool	is_default;
	
public:
	DefValue(T def_val)
	{
		is_default	= true;
		val			= def_val;
	}
	void Reset(T def_val) {
		is_default	= true;
		val			= def_val;
	}
	bool IsDefault() {
		return is_default;
	}
	T operator=(T new_val) {
		val			= new_val;
		is_default	= false;
		return val;
	}
	operator T() {
		return val;
	}
};


#define MediaOrientationStrings		"portrait;landscape"

enum MediaOrientation
{
	MediaOrientationPortrait,
	MediaOrientationLandscape,
};

#define MediaFeatureStrings		"none;width;min-width;max-width;height;min-height;max-height;device-width;min-device-width;max-device-width;device-height;min-device-height;max-device-height;orientation;aspect-ratio;min-aspect-ratio;max-aspect-ratio;device-aspect-ratio;min-device-aspect-ratio;max-device-aspect-ratio;color;min-color;max-color;color-index;min-color-index;max-color-index;monochrome;min-monochrome;max-monochrome;resolution;min-resolution;max-resolution"

enum MediaFeature
{
	MediaFeatureNone,

	MediaFeatureWidth,
	MediaFeatureMinWidth,
	MediaFeatureMaxWidth,

	MediaFeatureHeight,
	MediaFeatureMinHeight,
	MediaFeatureMaxHeight,

	MediaFeatureDeviceWidth,
	MediaFeatureMinDeviceWidth,
	MediaFeatureMaxDeviceWidth,

	MediaFeatureDeviceHeight,
	MediaFeatureMinDeviceHeight,
	MediaFeatureMaxDeviceHeight,

	MediaFeatureOrientation,

	MediaFeatureAspectRatio,
	MediaFeatureMinAspectRatio,
	MediaFeatureMaxAspectRatio,

	MediaFeatureDeviceAspectRatio,
	MediaFeatureMinDeviceAspectRatio,
	MediaFeatureMaxDeviceAspectRatio,

	MediaFeatureColor,
	MediaFeatureMinColor,
	MediaFeatureMaxColor,

	MediaFeatureColorIndex,
	MediaFeatureMinColorIndex,
	MediaFeatureMaxColorIndex,

	MediaFeatureMonochrome,
	MediaFeatureMinMonochrome,
	MediaFeatureMaxMonochrome,

	MediaFeatureResolution,
	MediaFeatureMinResolution,
	MediaFeatureMaxResolution,
};

#define BoxSizingStrings		"content-box;border-box"

enum BoxSizing
{
	BoxSizingContentBox,
	BoxSizingBorderBox,
};


#define MediaTypeStrings		"none;all;screen;print;braille;embossed;handheld;projection;speech;tty;tv"

enum MediaType
{
	MediaTypeNone,
	MediaTypeAll,
	MediaTypeScreen,
	MediaTypePrint,
	MediaTypeBraille,
	MediaTypeEmbossed,
	MediaTypeHandheld,
	MediaTypeProjection,
	MediaTypeSpeech,
	MediaTypeTty,
	MediaTypeTv,
};

struct MediaFeatures
{
	MediaType	type;
	int			width;			// (pixels) For continuous media, this is the width of the viewport including the size of a rendered scroll bar (if any). For paged media, this is the width of the page Box.
	int			height;			// (pixels) The height of the targeted display area of the output device. For continuous media, this is the height of the viewport including the size of a rendered scroll bar (if any). For paged media, this is the height of the page Box.
	int			device_width;	// (pixels) The width of the rendering surface of the output device. For continuous media, this is the width of the screen. For paged media, this is the width of the page sheet size.
	int			device_height;	// (pixels) The height of the rendering surface of the output device. For continuous media, this is the height of the screen. For paged media, this is the height of the page sheet size.
	int			color;			// The number of bits per color component of the output device. If the device is not a color device, the value is zero.
	int			color_index;	// The number of entries in the color lookup table of the output device. If the device does not use a color lookup table, the value is zero.
	int			monochrome;		// The number of bits per pixel in a monochrome frame buffer. If the device is not a monochrome device, the output device value will be 0.
	int			resolution;		// The resolution of the output device (in DPI)
};

enum RenderType
{
	RenderAll,
	RenderNoFixed,
	RenderFixedOnly,
};

// List of the Void Elements (can't have any contents)
const char* const void_elements = "area;base;br;col;command;embed;hr;img;input;keygen;link;meta;param;source;track;wbr";


NAMESPACE_LAYOUT_END

#endif
