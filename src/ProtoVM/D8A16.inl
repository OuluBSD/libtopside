// Address

case A0:
if (data_bytes == 2 && data_bits == 0) {
	data16 = *(uint16*)data;
	in_addr = data16;
	return true;
}
case A0+1:
case A0+2:
case A0+3:
case A0+4:
case A0+5:
case A0+6:
case A0+7:
	
case A0+8:
if (data_bytes == 1 && data_bits == 0) {
	in_addr = (in_addr & 0xFF) | (*data << 8);
	return true;
}
case A0+9:
case A0+10:
case A0+11:
case A0+12:
case A0+13:
case A0+14:
case A0+15:
off = conn_id - A0;
data16 = *(uint16*)data;
mask = ((1 << (int32)(data_bytes * 8 + data_bits + 1)) - 1) << off;
in_addr = (in_addr & ~mask) | ((data16 << off) & mask);
return true;



// Data

case D0:
if (data_bytes == 1 && data_bits == 0) {
	in_data = *data;
	return true;
}
else if (data_bytes == 1 && data_bits == 0) {
	in_data = (in_data & 0xFF00) | (*data);
	return true;
}
case D0+1:
case D0+2:
case D0+3:
case D0+4:
case D0+5:
case D0+6:
case D0+7:
off = conn_id - D0;
mask = ((1 << (int32)(data_bytes * 8 + data_bits + 1)) - 1) << off;
in_data = (in_data & ~mask) | ((*data << off) & mask);
return true;

