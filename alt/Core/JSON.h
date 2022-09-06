#ifndef _CoreAlt_JSON_h_
#define _CoreAlt_JSON_h_

NAMESPACE_UPP_BEGIN

Object ParseJSON(String json);
Object ParseJSONSafe(String json);

template <class T>
bool LoadFromJsonValue(T& o, Value v) {TODO_}

NAMESPACE_UPP_END

#endif
