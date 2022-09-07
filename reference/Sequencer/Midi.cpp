#include "Sequencer.h"


NAMESPACE_TOPSIDE_BEGIN


int current_timestamp;

PmTimestamp midithru_time_proc(void *info) {
	return current_timestamp;
}

void process_midi(PtTimestamp timestamp, void *userData) {
	Midi* m = (Midi*)userData;
	
	current_timestamp++;
	PmError result;
	PmEvent buffer;

	do {
		result = Pm_Poll(m->midi_in);
		
		if (result) {
			int status;
			int rslt = Pm_Read(m->midi_in, &buffer, 1);
			
			if (rslt == pmBufferOverflow)
				continue;
				
			status = Pm_MessageStatus(buffer.message);
			
			if (Pm_MessageStatus(buffer.message) == 0x90) {
				m->WhenNote(Pm_MessageData1(buffer.message), Pm_MessageData2(buffer.message));
			}
			
			//Pm_Enqueue(m->in_queue, &buffer);
		}
	}
	
	while (result)
		;
		
}

Midi::Midi() {
	in_queue = Pm_QueueCreate(IN_QUEUE_SIZE, sizeof(PmEvent));
	ASSERT(in_queue != NULL);
	
	/* always start the timer before you start midi */
	Pt_Start(1, &process_midi, this); /* start a timer with millisecond accuracy */
	/* the timer will call our function, process_midi() every millisecond */
	
	Pm_Initialize();
	
	id = Pm_GetDefaultInputDeviceID();
	info = Pm_GetDeviceInfo(id);
	
	if (info == NULL) {
		LOG("Could not open default input device " << id);
	}
	else {
		LOG("Opening input device " << info->interf << ": " << info->name);
		
		Pm_OpenInput(&midi_in,
					 id,
					 NULL /* driver info */,
					 0 /* use default input size */,
					 &midithru_time_proc,
					 NULL /* time info */);
		             
		             
		Pm_SetFilter(midi_in, PM_FILT_ACTIVE | PM_FILT_CLOCK);
		
		PmEvent buffer;
	}
}

Midi::~Midi() {
	Pt_Stop(); /* stop the timer */
    Pm_QueueDestroy(in_queue);

    Pm_Close(midi_in);

	Pm_Terminate();
}


NAMESPACE_TOPSIDE_END
