#ifndef _LayoutCtrl_Media_h_
#define _LayoutCtrl_Media_h_

NAMESPACE_LAYOUT_BEGIN

class Document;


struct MediaQueryExpression : Moveable<MediaQueryExpression>
{
	typedef Vector<MediaQueryExpression>	vector;
	
	MediaFeature	feature;
	int				val;
	int				val2;
	bool			check_as_bool;
	
	MediaQueryExpression()
	{
		check_as_bool	= false;
		feature			= MediaFeatureNone;
		val				= 0;
		val2			= 0;
	}

	bool Check(const MediaFeatures& features) const;
};

class MediaQuery : public Object
{
public:
	RTTI_DECL1(MediaQuery, Object)
	typedef Vector<MediaQuery*>	vector;
	
private:
	MediaQueryExpression::vector	expressions;
	bool							not_;
	MediaType						media_type;
public:
	MediaQuery(const MediaQuery& val);

	static MediaQuery* CreateFromString(const String& str, Document* doc);
	bool Check(const MediaFeatures& features) const;
private:
	MediaQuery();
};

class Context;

class MediaQueryList : public Object, public Pte<MediaQueryList>
{
public:
	RTTI_DECL1(MediaQueryList, Object)
	typedef Vector<MediaQueryList*>	vector;
	
private:
	MediaQuery::vector	queries;
	bool				is_used;
	
public:
	MediaQueryList(const MediaQueryList& val);

	static MediaQueryList* CreateFromString(const String& str, Document* doc);
	bool IsUsed() const;
	bool ApplyMediaFeatures(const MediaFeatures& features);	// returns true if the is_used changed
	
protected:
	friend class Context;
	MediaQueryList();
	
};

inline MediaQueryList::MediaQueryList(const MediaQueryList& val)
{
	is_used	= val.is_used;
	queries	<<= val.queries;
}

inline MediaQueryList::MediaQueryList()
{
	is_used = false;
}

inline bool MediaQueryList::IsUsed() const
{
	return is_used;
}


NAMESPACE_LAYOUT_END

#endif
