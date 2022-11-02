#ifndef _ToyHub_Storage_h_
#define _ToyHub_Storage_h_

NAMESPACE_TOYHUB_BEGIN


int64 NewTextId();
String LoadText(int64 text_id);
void StoreText(int64 text_id, String text);

String LoadHtmlFile(int page_id);
void StoreHtmlFile(int page_id, String text);

String LoadFile(int hub, String name);
void StoreFile(int hub, String name, String data);

String LoadWikipedia(String prefix, String title);


NAMESPACE_TOYHUB_END

#endif
