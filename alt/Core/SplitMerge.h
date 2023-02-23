#ifndef _Core_SplitMerge_h_
#define _Core_SplitMerge_h_

NAMESPACE_UPP_BEGIN


Vector<String> Split(String to_split, String split_str, bool ignore_empty=true);
Vector<WString> Split(WString to_split, WString split_str, bool ignore_empty=true);
String Join(const Vector<String>& v, String join_str, bool ignore_empty=true);


NAMESPACE_UPP_END

#endif
