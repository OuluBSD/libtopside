#include <Agent/Agent.h>

int TestDeepNN();

NAMESPACE_TOPSIDE_BEGIN

// Function which sets Node<Value> value in GenerateTree function
void SetValue(NodeValue* i) {
	static int counter;
	Object& v = *i;
	ObjectArray& arr = v.CreateArray();
	
	String str;
	str.Cat('A' + counter++);
	arr.Add(str);
	arr.Add((double)(-2 + Random(10)));
}

// Class which only only tells the utility value
struct SimpleGeneratorNode : RTTIBase {
	RTTI_DECL0(SimpleGeneratorNode)
	
	int value;
	
	String ToString() const {return IntStr(value);}
	double GetUtility() const {return value;}
};

// Use TerminalTest to generate sub nodes
template <>	inline bool TerminalTest<SimpleGeneratorNode>(Node<SimpleGeneratorNode>& n, Node<SimpleGeneratorNode>* prev) {
	int depth = n.GetDepth();
	if (depth >= 3 || n.GetCount()) return !n.GetCount();
	int sub_node_count = 1 + Random(2);
	for(int i = 0; i < sub_node_count; i++) {
		Node<SimpleGeneratorNode>& sub = n.Add();
		sub.value = -2 + Random(10);
	}
	return !n.GetCount();
}



// Class which tells length of route from the root to the node
struct RouteGeneratorNode : RTTIBase {
	RTTI_DECL0(RouteGeneratorNode)
	
	double length;
	double length_to_node;
	double estimate_to_goal;
	
	String ToString() const {return DblStr(length) + ", " + DblStr(length_to_node) + ", " + DblStr(estimate_to_goal);}
	double GetUtility() const {return length_to_node;}
	double GetEstimate() const {return estimate_to_goal;}
	double GetDistance(Node<RouteGeneratorNode>& n) {return n.length;} // no links, so this is always the parent
};

// Use TerminalTest to generate sub nodes
template <>	inline bool TerminalTest<RouteGeneratorNode>(Node<RouteGeneratorNode>& n, Node<RouteGeneratorNode>* prev) {
	if (n.GetCount()) return !n.GetCount();
	int goal = 0;
	if (n.estimate_to_goal <= goal) return true;
	int sub_node_count = 2 + Random(1);
	for(int i = 0; i < sub_node_count; i++) {
		Node<RouteGeneratorNode>& sub = n.Add();
		double length = 5 + Random(10);
		// Accumulate total route length
		if (sub.GetParent()) {
			sub.length				 = length;
			sub.length_to_node		 = n.length_to_node + length;
			sub.estimate_to_goal	 = n.estimate_to_goal - length;
			if (sub.estimate_to_goal < goal) sub.estimate_to_goal = goal;
		}
	}
	return !n.GetCount();
}


// Pretty print vector of pointers
template <class T>
String PtrVecStr(Vector<T*>& vec) {
	String out;
	for(int i = 0; i < vec.GetCount(); i++) {
		if (i) out << "\n";
		out << i << ": " << AsString(*vec[i]);
	}
	return out;
}

void PrintTotal(Vector<RouteGeneratorNode*>& vec) {
	double total = 0;
	for(int i = 0; i < vec.GetCount(); i++) {
		total += vec[i]->length;
	}
	double average = total / vec.GetCount();
	LOG("total=" << total << " average=" << average);
}




void ActionPlannerExample();
void Addition();
void SendMoreMoneyEasy();



void ActionPlannerExample() {
	using namespace ::TS::Agent;
	
	// Macros are poor man's meta-programming. Don't underestimate it! (I did it too earlier...)
	
	// I mean... actual meta-programming would be better (not that constexpr crap though)...
	// ...but meta-programming is better solution often, and this is the closest to it.
	
	#define ACT_LIST \
		ACT(CAT) \
		ACT(APPROACH) \
		ACT(COME_DOWN) \
		ACT(AIM) \
		ACT(ATTACK) \
		ACT(WAIT) \
		ACT(VERY_HIGH_JUMP_ATTACK) \
		ACT(FLEE)
	
	#define ATOM_LIST \
		ATOM(ARMED_WITH_CLAWS,	true) \
		ATOM(MOUSE_VISIBLE,		false) \
		ATOM(NEAR_MOUSE,		false) \
		ATOM(AT_HIGH_PLACE,		true) \
		ATOM(CLAWS_EXTENDED,	false) \
		ATOM(READY_TO_ATTACK,	false) \
		ATOM(MOUSE_ALIVE,		true) \
		ATOM(ALIVE,				true)
	
	enum {
		#define ACT(x) x,
		ACT_LIST
		#undef ACT
		ACT_COUNT
	};
	
	String act_names[ACT_COUNT+1] = {
		#define ACT(x) ToLower(#x),
		ACT_LIST
		#undef ACT
		""
	};
	
	enum {
		#define ATOM(x,y) x,
		ATOM_LIST
		#undef ATOM
		ATOM_COUNT
	};
	
	String atom_names[ATOM_COUNT+1] = {
		#define ATOM(x,y) ToLower(#x),
		ATOM_LIST
		#undef ATOM
		""
	};
	
	ActionPlanner planner;
	planner.SetSize(ACT_COUNT, ATOM_COUNT);
	
	ActionPlannerWrapper ap(planner);
	for(int i = 0; i < ACT_COUNT; i++)	ap.SetAction(i, act_names[i]);
	for(int i = 0; i < ATOM_COUNT; i++)	ap.SetAtom(i, atom_names[i]);
	
	planner.SetPreCondition (CAT, ARMED_WITH_CLAWS, true );
	planner.SetPostCondition(CAT, MOUSE_VISIBLE, true );

	planner.SetPreCondition (APPROACH, MOUSE_VISIBLE, true );
	planner.SetPostCondition(APPROACH, NEAR_MOUSE, true );
	
	planner.SetPreCondition (COME_DOWN, AT_HIGH_PLACE, true );
	planner.SetPostCondition(COME_DOWN, AT_HIGH_PLACE, false );
	
	planner.SetPreCondition (AIM, MOUSE_VISIBLE, true );
	planner.SetPreCondition (AIM, CLAWS_EXTENDED, true );
	planner.SetPostCondition(AIM, READY_TO_ATTACK, true );

	planner.SetPreCondition (ATTACK, READY_TO_ATTACK, true );
	planner.SetPreCondition (ATTACK, AT_HIGH_PLACE, false);
	planner.SetPostCondition(ATTACK, MOUSE_ALIVE, false );

	planner.SetPreCondition (WAIT, ARMED_WITH_CLAWS, true );
	planner.SetPostCondition(WAIT, CLAWS_EXTENDED, true );

	planner.SetPreCondition (VERY_HIGH_JUMP_ATTACK, AT_HIGH_PLACE, true );
	planner.SetPreCondition (VERY_HIGH_JUMP_ATTACK, NEAR_MOUSE, true );
	planner.SetPostCondition(VERY_HIGH_JUMP_ATTACK, ALIVE, false );
	planner.SetPostCondition(VERY_HIGH_JUMP_ATTACK, MOUSE_ALIVE, false );

	planner.SetPreCondition (FLEE, MOUSE_VISIBLE, true );
	planner.SetPostCondition(FLEE, NEAR_MOUSE, false );

	LOG(ap.GetDescription());
	
	WorldState src;
	#define ATOM(x,y) src.Set(x, y);
	ATOM_LIST
	#undef ATOM
	
	planner.SetCost(VERY_HIGH_JUMP_ATTACK, 5 );	// make hurting by fall more expensive than attacking at the same level.

	WorldState goal;
	goal.Set(MOUSE_ALIVE, false );
	goal.Set(ALIVE, true ); // add this to avoid hurting by fall actions in plan.
	
	APlanNode goal_node;
	goal_node.SetWorldState(goal);
	
	APlanNode root;
	root.SetActionPlanner(planner);
	root.SetGoal(goal_node);
	root.SetWorldState(src);
	AStar<ActionNode> as;
	Vector<ActionNode*> plan = as.Search(root);
	
	if (plan.IsEmpty()) {
		LOG("error: did not found path");
		LOG("warning: using best path found");
		plan = as.GetBest();
	}
	
	LOG("Beginning:");
	int total_cost = 0;
	for(int i = 0; i < plan.GetCount(); i++) {
		ActionNode& n = *plan[i];
		total_cost += n.GetCost();
		int id = n.GetActionId();
		if (id >= 0) {LOG(id << ": " << ap.GetActionName(id));}
		LOG("    " << i << ": " << ap.GetWorldstateDescription(n.GetWorldState()));
	}
	
	LOG("plan_cost=" << total_cost);
	
	// TODO:
	//  - tidy tmp_sub using
	//  - clear temp memory from ActionNode and ActionPlanner
	
}


NAMESPACE_TOPSIDE_END


using namespace UPP;
using namespace TS;

CONSOLE_APP_MAIN {
	
	
	// Simple game algorithms
	if (true) {
		NodeValue n = GenerateTree<NodeValue>(25, 2, 3, callback(SetValue));
		LOG(n.AsString());
		
		MiniMax<Object> mm;
		AlphaBeta<Object> ab;
		
		Vector<Object*> ans = mm.Search(n);
		LOG(PtrVecStr(ans));
		
		ans = ab.Search(n);
		LOG(PtrVecStr(ans));
	}
	
	// Simple game algorithms, with runtime node generation.
	if (true) {
		Node<SimpleGeneratorNode> n;
		LOG(n.AsString()); // n has nothing generated yet, so this should be ""
		
		MiniMax<SimpleGeneratorNode> mm;
		AlphaBeta<SimpleGeneratorNode> ab;
		
		Vector<SimpleGeneratorNode*> ans = mm.Search(n);
		LOG(n.AsString());
		LOG(PtrVecStr<SimpleGeneratorNode>(ans));
		
		ans = ab.Search(n);
		LOG(PtrVecStr(ans));
	}
	
	// Uninformed search strategies, with runtime node generation
	if (true) {
		Node<RouteGeneratorNode> n;
		n.estimate_to_goal = 20;
		n.length_to_node = 0;
		n.length = 0;
		
		BreadthFirst<RouteGeneratorNode> bf;
		UniformCost<RouteGeneratorNode> uc;
		DepthFirst<RouteGeneratorNode> df;
		DepthLimited<RouteGeneratorNode> dl;
		
		Vector<RouteGeneratorNode*> ans = bf.Search(n);
		LOG(n.AsString());
		LOG(PtrVecStr(ans));
		
		ans = uc.Search(n);
		LOG(PtrVecStr(ans));
		
		ans = df.Search(n);
		LOG(PtrVecStr(ans));
		
		dl.SetLimit(3);
		ans = dl.Search(n);
		LOG(PtrVecStr(ans));
	}
	
	
	// Informed (heuristic) search strategies, with runtime node generation
	if (true) {
		Node<RouteGeneratorNode> n;
		n.estimate_to_goal = 100;
		n.length_to_node = 0;
		n.length = 0;
		
		BestFirst<RouteGeneratorNode> bf;
		AStar<RouteGeneratorNode> as;
		as.TrimWorst(0);
		
		Vector<RouteGeneratorNode*> ans;
		
		ans = bf.Search(n);
		//LOG(n.AsString());
		LOG(PtrVecStr(ans));
		PrintTotal(ans);
		
		TimeStop ts;
		
		ts.Reset();
		ans = as.Search(n);
		LOG(PtrVecStr(ans));
		PrintTotal(ans);
		LOG(ts.ToString());
		
		
	}
	
	// Decision tree
	if (true) {
		if (1) {
			QueryTable<String> qt;
			
			Vector<String>& ot = qt.AddPredictor("Outlook");
			Vector<String>& temp = qt.AddPredictor("Temp");
			Vector<String>& hum = qt.AddPredictor("Humidity");
			Vector<String>& w = qt.AddPredictor("Windy");
			
			ot.Add("Rainy");				temp.Add("Hot");				hum.Add("High");				w.Add("False");		qt.AddTargetValue("No");
			ot.Add("Rainy");				temp.Add("Hot");				hum.Add("High");				w.Add("True");		qt.AddTargetValue("No");
			ot.Add("Overcast");				temp.Add("Hot");				hum.Add("High");				w.Add("False");		qt.AddTargetValue("Yes");
			ot.Add("Sunny");				temp.Add("Mild");				hum.Add("High");				w.Add("False");		qt.AddTargetValue("Yes");
			ot.Add("Sunny");				temp.Add("Cool");				hum.Add("Normal");				w.Add("False");		qt.AddTargetValue("Yes");
			ot.Add("Sunny");				temp.Add("Cool");				hum.Add("Normal");				w.Add("True");		qt.AddTargetValue("No");
			ot.Add("Overcast");				temp.Add("Cool");				hum.Add("Normal");				w.Add("True");		qt.AddTargetValue("Yes");
			ot.Add("Rainy");				temp.Add("Mild");				hum.Add("High");				w.Add("False");		qt.AddTargetValue("No");
			ot.Add("Rainy");				temp.Add("Cool");				hum.Add("Normal");				w.Add("False");		qt.AddTargetValue("Yes");
			ot.Add("Sunny");				temp.Add("Mild");				hum.Add("Normal");				w.Add("False");		qt.AddTargetValue("Yes");
			ot.Add("Rainy");				temp.Add("Mild");				hum.Add("Normal");				w.Add("True");		qt.AddTargetValue("Yes");
			ot.Add("Overcast");				temp.Add("Mild");				hum.Add("High");				w.Add("True");		qt.AddTargetValue("Yes");
			ot.Add("Overcast");				temp.Add("Hot");				hum.Add("Normal");				w.Add("False");		qt.AddTargetValue("Yes");
			ot.Add("Sunny");				temp.Add("Mild");				hum.Add("High");				w.Add("True");		qt.AddTargetValue("No");
			
			int i = qt.GetLargestInfoGainPredictor();
			DUMP(i);
			DUMPC(qt.GetInfoGains());
		}
		
		{
			QueryTable<String> qt;
			
			Vector<String>& x = qt.AddPredictor("X");
			Vector<String>& y = qt.AddPredictor("Y");
			
			x.Add("0");		y.Add("10");		qt.AddTargetValue("a");
			x.Add("1");		y.Add("10");		qt.AddTargetValue("a");
			x.Add("1");		y.Add("100");		qt.AddTargetValue("b");
			x.Add("0");		y.Add("100");		qt.AddTargetValue("b");
			x.Add("1");		y.Add("100");		qt.AddTargetValue("a");
			x.Add("1");		y.Add("100");		qt.AddTargetValue("a");
			x.Add("0");		y.Add("100");		qt.AddTargetValue("b");
			x.Add("0");		y.Add("100");		qt.AddTargetValue("b");
			
			int i = qt.GetLargestInfoGainPredictor();
			DUMP(i);
			DUMPC(qt.GetInfoGains());
		}
	}
	
	// Action planner
	if (true) {
		ActionPlannerExample();
	}
	
}

