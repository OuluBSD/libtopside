#define TMPL(x)	template <class DevSpec> x ScopeDevLibT<DevSpec>::


NAMESPACE_TOPSIDE_BEGIN


TMPL(String) Component::GetStringFromType(TypeCls i) {
	#define IFACE(x) \
		if (i == AsTypeCls<typename ScopeValDevCoreT<VD<DevSpec, x##Spec>>::ValSource>()) \
			return DevSpec::GetPrefix() + #x "Source"; \
		if (i == AsTypeCls<typename ScopeValDevCoreT<VD<DevSpec, x##Spec>>::ValSink>()) \
			return DevSpec::GetPrefix() + #x "Sink"; \
		if (i == AsTypeCls<typename ScopeValDevLibT<VD<DevSpec, x##Spec>>::PipeComponent>()) \
			return DevSpec::GetPrefix() + #x "PipeComponent";
		//if (i == AsTypeCls<ConvertCenterAccel##x##Component>()) return "ConvertCenterAccel" #x "Component";
	IFACE_LIST
	#undef IFACE
	return "invalid";
}

TMPL(void) Component::OnError(String fn, String msg) {
	if (ctx && ctx->GetParent()) {
		ctx->GetParent()->OnError(RTTI::GetRTTI().GetTypeId(), fn, msg);
	}
	else {
		LOG(DevSpec::GetName() + "Component::" << fn << ": error: " << msg);
	}
}






TMPL() ContextComponent::ContextComponent() {
	
}

TMPL(void) ContextComponent::PostLoadFileAny(String path) {
	Object content;
	if (LoadFileAny(path, content)) {
		post_load = content;
	}
}

TMPL(bool) ContextComponent::LoadFileAny(String path, Object& dst) {
	
	// If path is a directory instead of a file, then add default filename and extension
	if (DirectoryExists(path)) {
		for (String ext : GetDefaultExt<DevSpec>()) {
			if (path.Right(1) == DIR_SEPS)
				path = path.Left(path.GetCount()-1);
			String title = GetFileName(path);
			path = AppendFileName(path, title + ext);
			if (LoadFileAny(path, dst))
				return true;
		}
	}
	// Load file
	else {
		String ext = GetFileExt(path);
		
		// Iterate through all file extension loaders
		auto& ext_loaders = GetExtLoaders<DevSpec>();
		auto iter = ext_loaders.begin();
		for (; iter; ++iter)
			if (ext == *iter.key && iter.value()(path, dst, this))
				return true;
	}
	
	return false;
}


NAMESPACE_TOPSIDE_END

#undef TMPL
