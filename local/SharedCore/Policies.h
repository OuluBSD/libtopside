#ifndef _SharedCore_Policies_h_
#define _SharedCore_Policies_h_

struct Pol {
	
	struct Serial {
		struct Script {
			struct Loop {
				
				// If loop has both side-in and side-out, then side-out is always after side-in
				static constexpr bool SideSinkIsBeforeSideSourceAlways = true;
				
			};
			struct Loader {
				
				
			};
		};
		
		struct Atom {
			
			// FwdScope loop starts always with a consumer. Not e.g. input, side-input, output...
			static constexpr bool ConsumerFirst = true;
			
			// FwdScope iteration started using AddOnce expects that the first Extension is
			// forwarded with the previous iteration (started normally or with AddOnce).
			static constexpr bool SkipDulicateExtFwd = true;
			
		};
	};
};

#define POPO(x)	static_assert(x == true, "Policy check failed: " #x " == false");




#endif
