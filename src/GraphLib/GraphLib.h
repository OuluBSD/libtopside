#ifndef _GraphLib_GraphLib_h_
#define _GraphLib_GraphLib_h_

#include <LocalCtrl/LocalCtrl.h>


#define GRAPHLIB						GraphLib
#define NAMESPACE_GRAPHLIB_BEGIN		namespace  TS { namespace  GRAPHLIB {
#define NAMESPACE_GRAPHLIB_END			}}


NAMESPACE_GRAPHLIB_BEGIN
using namespace UPP;
NAMESPACE_GRAPHLIB_END


#include "Graph.h"
#include "Layout.h"
#include "Renderer.h"
#include "OrderedTree.h"
#include "Spring.h"
#include "TournamentTree.h"
#include "TopologicalSort.h"
#include "Dijkstra.h"
#include "BinaryHeapMap.h"


NAMESPACE_GRAPHLIB_BEGIN

template <class T>
class GraphLayout : public Graph, public T, public Ctrl {
	ScrollBar vert, horz;
	Renderer rend;
	One<ImageDraw> id;
	Size id_sz, max_size;
	Point last_pt, last_img_pt;
	double buffer_zoom_level;
	double drawer_zoom_level;
	bool route_weights;
	
	Image cached_img;
	Rect cached_rect;
	
public:
	RTTI_DECL1(GraphLayout<T>, Ctrl)
	typedef GraphLayout<T> CLASSNAME;
	GraphLayout() :
		rend(static_cast<Graph&>(*this)),
		T(static_cast<Graph&>(*this)) {
		route_weights = false;
		
		buffer_zoom_level = 1.0;
		drawer_zoom_level = 1.0;
		max_size = Size(1920,1080);
		
		AddFrame(vert.Vert());
		AddFrame(horz.Horz());
		vert.WhenScroll = THISBACK(Scroll);
		vert.SetLine(GetLineHeight());
		horz.WhenScroll = THISBACK(Scroll);
		horz.SetLine(GetLineHeight());
		
		PostCallback(THISBACK(Layout));
	}
	
	void RouteWeights(bool b=true) {route_weights = b;}
	void SetMaxSize(Size sz) {max_size = sz;}
	
	void Dijkstra(Node& n) {
		// calculating the shortest paths via Dijkstra
		try {
			GRAPHLIB::Dijkstra(*this, n);
		}
		catch (Exc e) {
			// probably orphaned node
			LOG(e);
		}
		
		// colourising the shortest paths and setting labels
		for(int i = 0; i < GetEdgeCount(); i++) {
			Edge& e = GetEdge(i);
			e.SetLabel(DblStr(e.GetWeight()));
		    if (e.target->predecessor == e.source || e.source->predecessor == e.target) {
		        e.SetStroke(3, Color(0x88,0xBB,0x77));
		    } else {
		        e.SetStroke(1, GrayColor(0xAA));
		    }
		}
	}
	
	int GetLineHeight() {return 30;}
	
	void Scroll() {
		Layout();
	}
	
	void Center() {
		horz.ScrollInto((horz.GetTotal() - horz.GetPage()) / 2);
		vert.ScrollInto((vert.GetTotal() - vert.GetPage()) / 2);
	}
	
	void ZoomAll() {
		Size sz = GetSize();
		double v_zoom = (double)sz.cx / (double)id_sz.cx;
		double h_zoom = (double)sz.cy / (double)id_sz.cy;
		double min_zoom = min(v_zoom, h_zoom);
		min_zoom = max(0.1, min(1.0, min_zoom));
		drawer_zoom_level = min_zoom;
		AfterZoom();
		PostCallback(THISBACK(Layout));
	}
	
	void ZoomNode(Node* n) {
		Rect r = n->GetBoundingBox();
		double w = r.GetWidth();
		double h = r.GetHeight();
		drawer_zoom_level = (id_sz.cx / (w * 4) + id_sz.cy / (h * 4)) * 0.5;
		
		Point spt = FromImage(r.CenterPoint());
		
		Size screen_size = GetSize();
		Point screen_pt(screen_size.cx / 2, screen_size.cy / 2);
		Point sbpt = spt - screen_pt;
		horz.Set(sbpt.x);
		vert.Set(sbpt.y);
		
		AfterZoom();
	}
	
	void AfterZoom() {
		Size zoom_sz = id_sz * drawer_zoom_level;
		horz.SetTotal(zoom_sz.cx);
		vert.SetTotal(zoom_sz.cy);
	}
	
	void LocalMenu(Bar& bar) {
		double zoom_step = 0.8;
		bar.Add("Zoom In", THISBACK2(Zoom, last_pt, zoom_step));
		bar.Add("Zoom Out", THISBACK2(Zoom, last_pt, 1.0/(1.0+zoom_step)-1.0));
		bar.Add("Zoom All", THISBACK(ZoomAll));
		Node* node = rend.FindNode(last_img_pt);
		if (node) {
			bar.Add("Zoom To Node", THISBACK1(ZoomNode, node));
		}
		bar.Separator();
		if (route_weights)		bar.Add("Disable one-click routing", THISBACK1(RouteWeights, !route_weights));
		else					bar.Add("Enable one-click routing", THISBACK1(RouteWeights, !route_weights));
	}

	void LeftDown(Point pt, dword) {
		last_pt = pt;
		last_img_pt = ToImage(pt);
		
		// Highlight shortest route to node if enabled
		if (route_weights) {
			Node* node = rend.FindNode(last_img_pt);
			if (node) {
				Dijkstra(*node);
				RefreshLayout();
				Refresh();
			}
		}
	}
	
	void RightDown(Point pt, dword) {
		last_pt = pt;
		last_img_pt = ToImage(pt);
		MenuBar::Execute(THISBACK(LocalMenu));
	}
	
	Point ToImage(Point pt) {
		double x = horz + pt.x;
		double y = vert + pt.y;
		double x_factor = x / horz.GetTotal();
		double y_factor = y / vert.GetTotal();
		return Point(x_factor * id_sz.cx, y_factor * id_sz.cy);
	}
	
	Point FromImage(Point pt) {
		double x_factor = (double)pt.x / id_sz.cx;
		double y_factor = (double)pt.y / id_sz.cy;
		return Point(x_factor * horz.GetTotal() , y_factor * vert.GetTotal());
	}
	
	void Zoom(Point screen_pt, double change) {
		Size sz = GetSize();
		Pointf factor = Pointf(screen_pt) / Pointf(sz.cx, sz.cy);
		
		Point ipt = ToImage(screen_pt);
		
		drawer_zoom_level *= 1.0 + change;
		if (drawer_zoom_level < 0.1) {
			drawer_zoom_level = 0.1;
			PostCallback(THISBACK(Layout));
		}
		Size zoom_sz = id_sz * drawer_zoom_level;
		horz.SetTotal(zoom_sz.cx);
		vert.SetTotal(zoom_sz.cy);
		
		Point spt = FromImage(ipt);
		
		Point sbpt = spt - screen_pt;
		horz.Set(sbpt.x);
		vert.Set(sbpt.y);
	}
	
	virtual void MouseWheel(Point pt, int zdelta, dword d) {
		
		// Scrolling view
		if (d == K_CTRL)
			horz.Wheel(zdelta);
		else if (d == 0)
			vert.Wheel(zdelta);
		
		// Zooming view
		else if (d == K_SHIFT)
			Zoom(pt, zdelta * 0.001);
		
	}
	
	virtual bool Key(dword key, int) {
		if (vert.VertKey(key)) return true;
		if (horz.HorzKey(key)) return true;
		if (key == K_PLUS || key == '+') {
			Size sz = GetSize();
			Zoom(Point(sz.cx/2,sz.cy/2), +0.1);
			return true;
		}
		if (key == K_MINUS || key == '-') {
			Size sz = GetSize();
			Zoom(Point(sz.cx/2,sz.cy/2), -0.1);
			return true;
		}
		if (key == (K_SHIFT | K_HOME)) {
			ZoomAll();
			return true;
		}
		return false;
	}

	virtual void Layout() {
		Size sz = GetSize();
		horz.SetPage(sz.cx);
		vert.SetPage(sz.cy);
		
		
		// Reset buffer zoom when there is room to fill the screen again
		/*if (sz.cx >= id_sz.cx && sz.cy >= id_sz.cy && buffer_zoom_level > 1.0 && drawer_zoom_level <= 1.0) {
			buffer_zoom_level = 1.0;
		}*/
		
		// Only refresh layout when not zooming
		if (buffer_zoom_level <= 1.0 && drawer_zoom_level <= 1.0) {
			RefreshLayout();
			horz.SetTotal(id_sz.cx);
			vert.SetTotal(id_sz.cy);
		}
		Refresh();
	}
	
	void RefreshLayout() {
		T::RefreshLayout();
		RefreshBuffer();
	}
	
	void RefreshBuffer() {
		Size sz = GetSize();
		if (sz.cx <= 2 || sz.cy <= 2) return;
		
		// prepare for zooming out buffer
		for (;;) {
			ASSERT(buffer_zoom_level > 0);
			Size new_size = (buffer_zoom_level > 1.0 ? Size(320,240) : sz) * buffer_zoom_level;
			if (new_size.cx > max_size.cx || new_size.cy > max_size.cy)
				break;
			
			id_sz = new_size;
			
			rend.SetImageSize(id_sz); // refreshes Node::point, which is required for GetBoundingBox
			
			// zoom out if nodes collided
			Rect lb = RectC(-2, 0, 2, id_sz.cy); // left border, right ... etc.
			Rect rb = RectC(id_sz.cx, 0, 2, id_sz.cy);
			Rect tb = RectC(0, -2, id_sz.cx, 2);
			Rect bb = RectC(0, id_sz.cy, id_sz.cx, 2);
			bool not_colliding = true;
			for(int i = 0; i < GetNodeCount() && not_colliding; i++) {
				Node& a = GetNode(i);
				Rect ar = a.GetBoundingBox();
				for(int j = 0; j < GetNodeCount() && not_colliding; j++) {
					if (j == i) continue;
					Node& b = GetNode(j);
					Rect br = b.GetBoundingBox();
					if (ar.Intersects(br)) {
						not_colliding = false;
					}
				}
				if      (ar.Intersects(lb)) not_colliding = false;
				else if (ar.Intersects(tb)) not_colliding = false;
				else if (ar.Intersects(rb)) not_colliding = false;
				else if (ar.Intersects(bb)) not_colliding = false;
			}
			if (not_colliding)
				break;
			
			buffer_zoom_level *= 1.3;
		}
		
		// Actually draw the image
		cached_img.Clear();
		id.Clear();
		id = new ImageDraw(id_sz);
		rend.SetImageSize(id_sz);
		rend.Paint(*id);
	}
	
	
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		if (this->id.IsEmpty() || id_sz.cx <= 2 || id_sz.cy <= 2) {
			w.DrawRect(sz, White());
			return;
		}
		
		if (drawer_zoom_level == 1.0) {
			if (!Rect(id_sz).Contains(Rect(sz)) && !Rect(sz).Contains(Rect(id_sz)))
				w.DrawRect(sz, White());
			w.DrawImage(0,0, *this->id, RectC(horz, vert, sz.cx, sz.cy));
		}
		else {
			double x_factor = (double)horz.Get() / horz.GetTotal();
			double y_factor = (double)vert.Get() / vert.GetTotal();
			int x = x_factor * id_sz.cx;
			int y = y_factor * id_sz.cy;
			double w_factor = (double)horz.GetPage() / horz.GetTotal();
			double h_factor = (double)vert.GetPage() / vert.GetTotal();
			int W = w_factor * id_sz.cx;
			int H = h_factor * id_sz.cy;
			//int W = w_factor > 1.0 ? w_factor * id_sz.cx : horz.GetPage();
			//int H = h_factor > 1.0 ? h_factor * id_sz.cy : vert.GetPage();
			if (x < 0) x = 0;
			if (y < 0) y = 0;
			if (x >= id_sz.cx-4) x = id_sz.cx-5;
			if (y >= id_sz.cy-4) y = id_sz.cy-5;
			if (W < 4) W = 4;
			if (H < 4) H = 4;
			if (x+W >= id_sz.cx) W = id_sz.cx - x;
			if (y+H >= id_sz.cy) H = id_sz.cy - y;
			Rect r = RectC(x, y, W, H);
			//DUMP(id_sz);
			//DUMP(sz);
			//DUMP(r);
			ASSERT(Rect(id_sz).Contains(r));
			if (cached_img.IsEmpty() || cached_rect != r || sz != cached_img.GetSize()) {
				cached_img = RescaleFilter(*this->id, sz, r, FILTER_NEAREST);
				cached_rect = r;
			}
			w.DrawImage(0, 0, cached_img);
		}
	}

};

typedef GraphLayout<Spring>				SpringGraph;
typedef GraphLayout<OrderedTree>		OrderedTreeGraph;
typedef GraphLayout<TournamentTree>		TournamentTreeGraph;

NAMESPACE_GRAPHLIB_END

#endif
