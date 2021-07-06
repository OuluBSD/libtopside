#ifndef _SharedCore_Policies_h_
#define _SharedCore_Policies_h_

struct Pol {
	
	struct Ecs {
		struct Eon {
			struct Loop {
				
				// If loop has both side-in and side-out, then side-out is always after side-in
				static constexpr bool SideInIsBeforeSideOutAlways = true;
				
			};
			struct Loader {
				
				// Corresponding "Add component" action is always before "add extension" action.
				// Note: "add extension" might be out-of-order later
				static constexpr bool CorrespondingAddCompAndExt = true;
				
			};
		};
		
		struct ExtComp {
			
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
