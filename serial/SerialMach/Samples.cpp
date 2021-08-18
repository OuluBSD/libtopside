#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


String MidiSample::ToString(Type t) {
	switch (t) {
		case MIDI_EVENT: return "MidiEvent";
		default: break;
	}
	return "<invalid>";
}

int MidiSample::GetSize(Type t) {
	switch (t) {
		case MIDI_EVENT: return sizeof(MidiEvent);
		default: break;
	}
	ASSERT_(0, "invalid type");
	return 0;
}
















String EventSample::ToString(Type t) {
	switch (t) {
		case CTRL_EVENT: return "CtrlEvent";
		default: break;
	}
	return "<invalid>";
}

int EventSample::GetSize(Type t) {
	switch (t) {
		case CTRL_EVENT: return sizeof(CtrlEvent);
		default: break;
	}
	ASSERT_(0, "invalid type");
	return 0;
}









String OrderSample::ToString(Type t) {
	switch (t) {
		case INVALID: return "INVALID";
		case GENERIC: return "GENERIC";
		case DEV_INTERNAL: return "DEV_INTERNAL";
		#define ORDER_SMPL(type) \
			case type: return #type;
		ORDER_SMPL_LIST
		#undef ORDER_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int OrderSample::GetSize(Type t) {
	PANIC("Invalid call. (Do not use OrderSample with SimpleBufferedValue)");
}






String ReceiptSample::ToString(Type t) {
	switch (t) {
		case INVALID: return "INVALID";
		case GENERIC: return "GENERIC";
		case DEV_INTERNAL: return "DEV_INTERNAL";
		#define RECEIPT_SMPL(type) \
			case type: return #type;
		RECEIPT_SMPL_LIST
		#undef RECEIPT_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int ReceiptSample::GetSize(Type t) {
	PANIC("Invalid call. (Do not use ReceiptSample with SimpleBufferedValue)");
}








String DataSample::ToString(Type t) {
	switch (t) {
		case INVALID: return "INVALID";
		#define DATA_SMPL(type) \
			case type: return #type;
		DATA_SMPL_LIST
		#undef DATA_SMPL
		default: break;
	}
	return "<invalid-sample-type>";
}

int DataSample::GetSize(Type t) {
	PANIC("Invalid call. (Do not use DataSample with SimpleBufferedValue)");
}


NAMESPACE_SERIAL_END
