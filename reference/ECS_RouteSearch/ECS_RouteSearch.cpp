#include "ECS_RouteSearch.h"


CONSOLE_APP_MAIN {
	SetCoutLog();
	
	Machine& mach = GetMachine();
	RegistrySystem& reg = *mach.Add<RegistrySystem>();
	EntityStore& es = *mach.Add<EntityStore>();
	EntityPool& root = es.GetRoot();
	EntityPool& externals = root.AddPool("externals");
	EntityPool& external_cls = root.AddPool("external_classes");
	
    mach.Add<ComponentStore>();
    mach.Add<ConnectorSystem>();
    mach.Add<OverlapSystem>();
    mach.Add<ActionSystem>();
    //mach.Add<RouteSystem>();
    
    
    
    SE road_cls			= external_cls.Create<RouteRoad>();
    SE ground_cls		= external_cls.Create<RouteGround>();
    SE wall_cls			= external_cls.Create<RouteWall>();
    SE water_cls		= external_cls.Create<RouteWater>();
    
    ArrayMap<int, SE> classes;
    classes.Add('.', road_cls);
    classes.Add('x', wall_cls);
    classes.Add(' ', ground_cls);
    classes.Add('-', water_cls);
    
    const char* map =
		"|A| | | | | | | | | | | | | | | \n"
		"| |.| | |.|.|.|.|.|.|.|.| | | | \n"
		"| |.| | |.| |x|x|x| | |.| | | | \n"
		"| |.|.|.|.|x|x| |x|x| |.|.| | | \n"
		"| | | | |x|x| | | |x|x| |.| | | \n"
		"| | | |x|x| | | | | | | |.| | | \n"
		"| | | |x| | |.|.|.| |x|x|.|x|x|x\n"
		"| | |x|x| | |.| |.|.| | |.| | |.\n"
		"|-|-|x| | | |.| | |.|.|.|.|.|.|.\n"
		"|-|-|x| |x| |.|.| | |x|x|x| | |.\n"
		"|-|-|x| |x|x|x|.|x|x|x| | | | | \n"
		"|-|-|x| | | |x|x|x| |x|x|x| | | \n"
		"|-|-|x| | |x|x|.| | | |.|x|x|x|x\n"
		"|-|-|-|-|-|x| |.| | |x|.|.|.|.|.\n"
		"|-|-|-|-|.|.|.|.| | |x| | | | |.\n"
		"|-|-|-|-|-|x| | | | | | | | | |B";
	
    
    TraverseMap(externals, map, classes);
    
    
    
    mach.DieFast();
}


void TraverseMap(EntityPool& externals, String map, ArrayMap<int, SE>& classes) {
	Vector<String> lines = Split(map, "\n");
	if (lines.IsEmpty())
		throw Exc("No lines");
	int width = lines[0].GetCount();
	int height = lines.GetCount();
	if (width < 2 || height < 2)
		throw Exc("Too small resolution. At least 2x2 is expected");
	if (width % 2 != 0)
		throw Exc("width must be even number");
	for(String& line : lines)
		if (line.GetCount() != width)
			throw Exc("Unexpected length in line");
	width /= 2;
	
	struct Tile : Moveable<Tile> {
		double act_cost[9];
		bool invalid[9];
		int value, cls;
		int x, y;
		bool is_begin = false, is_end = false;
		SE e;
		
		Tile() {
			memset(&act_cost, 0, sizeof(act_cost));
			memset(&invalid, 0, sizeof(invalid));
		}
		void SetCost(int x, int y, double d) {x += 1; y += 1; act_cost[y * 3 + x] = d;}
		void Check(Tile* t, int x, int y) {
			if (!t) {
				x += 1; y += 1; invalid[y * 3 + x] = true;
				return;
			}
			if (value == '.' && t->value == '.' && (x == 0 || y == 0))
				SetCost(x, y, 0.1);
			else if (value == 'x' || t->value == 'x')
				SetCost(x, y, 1000000000.0);
			else if (value == '-' && t->value == '-')
				SetCost(x, y, 1.0);
			else if (value == '-' || t->value == '-')
				SetCost(x, y, 0.7);
			else
				SetCost(x, y, 0.5);
		}
	};
	Vector<Tile> tiles;
	tiles.SetCount(width * height);
	
	enum {
		BIT_NUM = 0x1,
		BIT_LETTER = 0x2,
	};
	
	for(int y = 0; y < lines.GetCount(); y++) {
		const String& line = lines[y];
		for(int x2 = 0; x2 < line.GetCount(); x2++) {
			int value = line[x2];
			int x = x2 / 2;
			dword coord = y * width + x;
			
			if (value == '|') continue;
			
			Tile& t = tiles[x + y * width];
			t.x = x;
			t.y = y;
			if (value == 'A') {
				t.value = ' ';
				t.is_begin = true;
			}
			else if (value == 'B') {
				t.value = '.';
				t.is_end = true;
			}
			else
				t.value = value;
			t.cls = classes.Find(t.value);
			if (t.cls < 0)
				throw Exc("Map value is not defined in classes: " + IntStr(value));
			
		}
	}
	
	for(int i = 0; i < tiles.GetCount(); i++) {
		Tile& ct = tiles[i];
		Tile* tl = ct.x > 0			&& ct.y > 0			? &tiles[ct.x - 1	+ (ct.y - 1) * width] : 0;
		Tile* t  =					   ct.y > 0			? &tiles[ct.x		+ (ct.y - 1) * width] : 0;
		Tile* tr = ct.x < width-1	&& ct.y > 0			? &tiles[ct.x + 1	+ (ct.y - 1) * width] : 0;
		Tile* r  = ct.x < width-1						? &tiles[ct.x + 1	+       ct.y * width] : 0;
		Tile* br = ct.x < width-1	&& ct.y < height-1	? &tiles[ct.x + 1	+ (ct.y + 1) * width] : 0;
		Tile* b  =					   ct.y < height-1	? &tiles[ct.x		+ (ct.y + 1) * width] : 0;
		Tile* bl = ct.x > 0			&& ct.y < height-1	? &tiles[ct.x - 1	+ (ct.y + 1) * width] : 0;
		Tile* l  = ct.x > 0								? &tiles[ct.x - 1	+       ct.y * width] : 0;
		
		ct.Check(tl, -1, -1);
		ct.Check(t,   0, -1);
		ct.Check(tr, +1, -1);
		ct.Check(r,  +1,  0);
		ct.Check(br, +1, +1);
		ct.Check(b,   0, +1);
		ct.Check(bl, -1, +1);
		ct.Check(l,  -1,  0);
		if (ct.value == '-')
			ct.SetCost(0, 0, 1);
	}
	
	for (Tile& t : tiles) {
		t.e = externals.Create<RouteNode>();
		Transform& tf = *t.e->Get<Transform>();
		tf.position = vec3(t.x, 0, -t.y);
	}
	
	for (Tile& t : tiles) {
		RouteSource& src = *t.e->FindRouteSource();
		for(int i = 0; i < 9; i++) {
			if (i == 4) {
				src.SetIdleCost(t.act_cost[4]);
			}
			else if (t.invalid[i])
				continue;
			else {
				int x_diff = (i % 3) - 1;
				int y_diff = (i / 3) - 1;
				int x = t.x + x_diff;
				int y = t.y + y_diff;
				
				Tile& dst = tiles[x + y * width];
				RouteSink& sink = *dst.e->FindRouteSink();
				src.LinkManually(sink);
			}
		}
	}
	
}

