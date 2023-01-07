#ifndef _ParallelLib_HandleT_h_
#define _ParallelLib_HandleT_h_

NAMESPACE_PARALLEL_BEGIN


template <class Dim>
class HandleT :
	public Dim::Interface
{
	
public:
	using Interface = typename Dim::Interface;
	using InterfaceProxy = typename Dim::InterfaceProxy;
	
	typedef HandleT<Dim> CLASSNAME;
	HandleT();
	
	void SetInterface(typename Dim::InterfaceProxy& iface);
	
	void						Title(const String& title) override;
	Interface&					Sizeable(bool b=true) override;
	Interface&					MaximizeBox(bool b=true) override;
	Interface&					MinimizeBox(bool b=true) override;
	int							Run(bool appmodal=false) override;
	String						GetTitle() const override;
	void						SetPendingPartialRedraw() override;
	
};


NAMESPACE_PARALLEL_END

#endif
