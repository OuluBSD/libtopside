#include "Core.h"

NAMESPACE_UPP_BEGIN

void HttpCookie::Clear() {
	TODO
}

bool HttpCookie::Parse(const String& cookie) {
	TODO
}






HttpHeader::HttpHeader(const HttpHeader&) {
	
}

String HttpHeader::GetCookie(const char *id) const {
	TODO
}

bool HttpHeader::Response(String& protocol, int& code, String& reason) const {
	TODO
}

bool HttpHeader::Request(String& method, String& uri, String& version) const {
	TODO
}

bool HttpHeader::HasContentLength() const {
	TODO
}

int64 HttpHeader::GetContentLength() const {
	TODO
}

void HttpHeader::Clear() {
	TODO
}

bool HttpHeader::ParseAdd(const String& hdrs) {
	TODO
}

bool HttpHeader::Parse(const String& hdrs) {
	TODO
}

bool HttpHeader::ParseSCGI(const String& scgi_hdr) {
	TODO
}

bool HttpHeader::Read(TcpSocket& socket) {
	TODO
}

void HttpHeader::Add(const String& id, const String& value) {
	TODO
}












HttpRequest::HttpRequest() {
	
}

HttpRequest& HttpRequest::UserAgent(String s) {
	TODO
}

HttpRequest& HttpRequest::Cookie(HttpCookie& c) {
	TODO
}

HttpRequest& HttpRequest::Method(int i) {
	TODO
}

HttpRequest& HttpRequest::PostData(String s) {
	TODO
}

HttpRequest& HttpRequest::Url(String url) {
	TODO
}

HttpRequest& HttpRequest::Trace(bool b) {
	TODO
}

String HttpRequest::Execute() {
	TODO
}

String HttpRequest::GetRedirectUrl() {
	TODO
}

int HttpRequest::GetStatusCode() const {
	TODO
}

const HttpHeader& HttpRequest::GetHttpHeader() const {
	TODO
}


NAMESPACE_UPP_END
