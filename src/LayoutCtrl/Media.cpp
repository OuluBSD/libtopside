#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN

MediaQuery::MediaQuery()
{
	media_type		= MediaTypeAll;
	not_			= false;
}

MediaQuery::MediaQuery(const MediaQuery& val)
{
	not_			= val.not_;
	expressions		<<= val.expressions;
	media_type		= val.media_type;
}

MediaQuery* MediaQuery::CreateFromString(const String& str, Document* doc)
{
	MediaQuery* query = new MediaQuery();

	StringVector tokens;
	SplitString(str, tokens, " \t\r\n", "", "(");

	for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
	{
		if ((*tok) == "not") {
			query->not_ = true;
		}
		else if ((*tok)[0] == '(') {
			tok->Remove(0);
			
			if ((*tok)[tok->GetCount() - 1] == ')')
				tok->Remove(tok->GetCount() - 1, 1);
		
			MediaQueryExpression expr;
			StringVector expr_tokens;
			SplitString((*tok), expr_tokens, ":");
			if(!expr_tokens.IsEmpty())
			{
				Trim(expr_tokens[0]);
				expr.feature = (MediaFeature) ValueIndex(expr_tokens[0], MediaFeatureStrings, MediaFeatureNone);
				if(expr.feature != MediaFeatureNone)
				{
					if(expr_tokens.GetCount() == 1)
					{
						expr.check_as_bool = true;
					}
					else
					{
						Trim(expr_tokens[1]);
						expr.check_as_bool = false;
						if(expr.feature == MediaFeatureOrientation)
						{
							expr.val = ValueIndex(expr_tokens[1], MediaOrientationStrings, MediaOrientationLandscape);
						}
						else
						{
							int slash_pos = expr_tokens[1].Find('/');
							if( slash_pos != -1 )
							{
								String val1 = expr_tokens[1].Mid(0, slash_pos);
								String val2 = expr_tokens[1].Mid(slash_pos + 1);
								Trim(val1);
								Trim(val2);
								expr.val = StrInt(val1);
								expr.val2 = StrInt(val2);
							}
							else
							{
								CssLength length;
								length.FromString(expr_tokens[1]);
								if(length.Units() == CssUnitsDpcm)
								{
									expr.val = (int) (length.GetValue() * 2.54);
								}
								else if(length.Units() == CssUnitsDpi)
								{
									expr.val = (int) (length.GetValue() * 2.54);
								}
								else
								{
									if(doc)
										doc->CvtUnits(length, doc->GetHtmlCtrl().GetDefaultFontSize());
									
									expr.val = (int) length.GetValue();
								}
							}
						}
					}
					query->expressions.Add(expr);
				}
			}
		}
		else {
			query->media_type = (MediaType) ValueIndex((*tok), MediaTypeStrings, MediaTypeAll);
		}
	}

	return query;
}

bool MediaQuery::Check( const MediaFeatures& features ) const
{
	bool res = false;
	if (media_type == MediaTypeAll || media_type == features.type)
	{
		res = true;
		for(MediaQueryExpression::vector::ConstIterator expr = expressions.Begin(); expr != expressions.End() && res; expr++)
			if (!expr->Check(features))
				res = false;
	}

	if(not_)
		res = !res;

	return res;
}


MediaQueryList* MediaQueryList::CreateFromString(const String& str, Document* doc)
{
	MediaQueryList* list = new MediaQueryList();

	StringVector tokens;
	SplitString(str, tokens, ",");

	for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
	{
		Trim(*tok);
		LowerCase(*tok);

		MediaQuery* query = MediaQuery::CreateFromString(*tok, doc);
		if(query)
			list->queries.Add(query);
	}
	
	if (list->queries.IsEmpty())
		list = 0;

	return list;
}

bool MediaQueryList::ApplyMediaFeatures(const MediaFeatures& features)
{
	bool apply = false;
	
	for(MediaQuery::vector::Iterator iter = queries.Begin(); iter != queries.End() && !apply; iter++)
	{
		if((*iter)->Check(features))
			apply = true;
	}

	bool ret = (apply != is_used);
	is_used = apply;
	return ret;
}

bool MediaQueryExpression::Check( const MediaFeatures& features ) const
{
	switch(feature)
	{
	case MediaFeatureWidth:
		if (check_as_bool)
			return (features.width != 0);
		else if (features.width == val)
			return true;
		break;
		
	case MediaFeatureMinWidth:
		if (features.width >= val)
			return true;
		break;
		
	case MediaFeatureMaxWidth:
		if (features.width <= val)
			return true;
		break;
		
	case MediaFeatureHeight:
		if(check_as_bool)
			return (features.height != 0);
		else if(features.height == val)
			return true;
		break;

	case MediaFeatureMinHeight:
		if(features.height >= val)
			return true;
		break;

	case MediaFeatureMaxHeight:
		if(features.height <= val)
			return true;
		break;

	case MediaFeatureDeviceWidth:
		if(check_as_bool)
			return (features.device_width != 0);
		else if(features.device_width == val)
			return true;
		break;

	case MediaFeatureMinDeviceWidth:
		if(features.device_width >= val)
			return true;
		break;

	case MediaFeatureMaxDeviceWidth:
		if(features.device_width <= val)
			return true;
		break;

	case MediaFeatureDeviceHeight:
		if(check_as_bool)
			return (features.device_height != 0);
		else if(features.device_height == val)
			return true;
		break;

	case MediaFeatureMinDeviceHeight:
		if(features.device_height <= val)
			return true;
		break;

	case MediaFeatureMaxDeviceHeight:
		if(features.device_height <= val)
			return true;
		break;

	case MediaFeatureOrientation:
		if(features.height >= features.width) {
			if(val == MediaOrientationPortrait)
				return true;
		}
		else {
			if(val == MediaOrientationLandscape)
				return true;
		}
		break;

	case MediaFeatureAspectRatio:
		if(features.height && val2) {
			int ratio_this = RoundDbl( (double) val / (double) val2 * 100 );
			int ratio_feat = RoundDbl( (double) features.width / (double) features.height * 100.0 );
			if(ratio_this == ratio_feat)
				return true;
		}
		break;

	case MediaFeatureMinAspectRatio:
		if(features.height && val2) {
			int ratio_this = RoundDbl( (double) val / (double) val2 * 100 );
			int ratio_feat = RoundDbl( (double) features.width / (double) features.height * 100.0 );
			if(ratio_feat >= ratio_this)
				return true;
		}
		break;

	case MediaFeatureMaxAspectRatio:
		if(features.height && val2) {
			int ratio_this = RoundDbl( (double) val / (double) val2 * 100 );
			int ratio_feat = RoundDbl( (double) features.width / (double) features.height * 100.0 );
			if(ratio_feat <= ratio_this)
				return true;
		}
		break;


	case MediaFeatureDeviceAspectRatio:
		if(features.device_height && val2) {
			int ratio_this = RoundDbl( (double) val / (double) val2 * 100 );
			int ratio_feat = RoundDbl( (double) features.device_width / (double) features.device_height * 100.0 );
			if(ratio_feat == ratio_this)
				return true;
		}
		break;

	case MediaFeatureMinDeviceAspectRatio:
		if(features.device_height && val2) {
			int ratio_this = RoundDbl( (double) val / (double) val2 * 100 );
			int ratio_feat = RoundDbl( (double) features.device_width / (double) features.device_height * 100.0 );
			if(ratio_feat >= ratio_this)
				return true;
		}
		break;

	case MediaFeatureMaxDeviceAspectRatio:
		if(features.device_height && val2) {
			int ratio_this = RoundDbl( (double) val / (double) val2 * 100 );
			int ratio_feat = RoundDbl( (double) features.device_width / (double) features.device_height * 100.0 );
			if(ratio_feat <= ratio_this)
				return true;
		}
		break;

	case MediaFeatureColor:
		if(check_as_bool)
			return (features.color != 0);
		else if(features.color == val)
			return true;
		break;

	case MediaFeatureMinColor:
		if(features.color >= val)
			return true;
		break;

	case MediaFeatureMaxColor:
		if(features.color <= val)
			return true;
		break;

	case MediaFeatureColorIndex:
		if(check_as_bool)
			return (features.color_index != 0);
		else if(features.color_index == val)
			return true;
		break;

	case MediaFeatureMinColorIndex:
		if(features.color_index >= val)
			return true;
		break;

	case MediaFeatureMaxColorIndex:
		if(features.color_index <= val)
			return true;
		break;

	case MediaFeatureMonochrome:
		if(check_as_bool)
			return (features.monochrome != 0);
		else if(features.monochrome == val)
			return true;
		break;

	case MediaFeatureMinMonochrome:
		if(features.monochrome >= val)
			return true;
		break;

	case MediaFeatureMaxMonochrome:
		if(features.monochrome <= val)
			return true;
		break;

	case MediaFeatureResolution:
		if(features.resolution == val)
			return true;
		break;

	case MediaFeatureMinResolution:
		if(features.resolution >= val)
			return true;
		break;

	case MediaFeatureMaxResolution:
		if(features.resolution <= val)
			return true;
		break;

	default:
		return false;
	}

	return false;
}


NAMESPACE_LAYOUT_END
