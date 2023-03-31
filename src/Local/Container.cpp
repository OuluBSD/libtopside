#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN








void HugePersistent::StoreData() {
	ASSERT(data_size > 0);
	ASSERT(persistent_size > 0);
	ASSERT(data);
	ASSERT(filename.GetCount());
	RealizeDirectory(GetDataDirectory());
	String file = AppendFileName(GetDataDirectory(), filename);
	String prev_file = file + ".0";
	
	if (FileExists(file)) {
		if (FileExists(prev_file))
			DeleteFile(prev_file);
		RenameFile(file, prev_file);
	}
	FileOut fout(file);
	fout.Put(&persistent_size, sizeof(persistent_size));
	
	dword* data = (dword*)this->data;
	int64 data_left = persistent_size;
	int chunk_dwords = 0x1000000;
	int chunk = chunk_dwords * sizeof(int);
	while (data_left > 0) {
		if (data_left > chunk) {
			fout.Put(data, chunk);
			data += chunk_dwords;
			data_left -= chunk;
		}
		else {
			fout.Put(data, (int)data_left);
			data_left = 0;
		}
	}
	// TODO: maybe use slower backup drive
	DeleteFile(prev_file);
}

void HugePersistent::LoadData() {
	if (persistent_size == 0)
		Panic("Database size is 0");
	ASSERT(filename.GetCount());
	RealizeDirectory(GetDataDirectory());
	String file = AppendFileName(GetDataDirectory(), filename);
	String prev_file = file + ".0";
	
	if (FileExists(prev_file))
		file = prev_file;
	
	FileIn fin(file);
	int64 file_persistent_size = 0;
	fin.Get(&file_persistent_size, sizeof(file_persistent_size));
	if (file_persistent_size != persistent_size)
		Panic("File header size mismatch configuration size: " + IntStr64(file_persistent_size) + " != " + IntStr64(persistent_size));
	
	if (!data) {
		data = MemoryAlloc(data_size);
		
		//byte* zero_begin = (byte*)data + persistent_size;
		//int64 zero_size = data_size - persistent_size;
		memset(data, 0, data_size);
	}
	
	TimeStop ts;
	dword* data = (dword*)this->data;
	int64 data_left = persistent_size;
	int chunk_dwords = 0x1000000;
	int chunk = chunk_dwords * sizeof(int);
	while (data_left > 0) {
		if (data_left > chunk) {
			fin.Get(data, chunk);
			data += chunk_dwords;
			data_left -= chunk;
		}
		else {
			fin.Get(data, (int)data_left);
			data_left = 0;
		}
	}
	LOG("Loading database took " << ts.ToString());
}









bool& EnvState::SetBool(dword key, bool b) {
	Object& o = data.GetAdd(key);
	return o.Set<bool>(b);
}

int& EnvState::SetInt(dword key, int i) {
	Object& o = data.GetAdd(key);
	return o.Set<int>(i);
}

bool& EnvState::GetBool(dword key) {
	Object& o = data.GetAdd(key);
	if (o.Is<bool>())
		return o.Get<bool>();
	else
		return o.Create<bool>(false);
}

int& EnvState::GetInt(dword key) {
	Object& o = data.GetAdd(key);
	if (o.Is<int>())
		return o.Get<int>();
	else
		return o.Create<int>(0);
}



NAMESPACE_TOPSIDE_END
