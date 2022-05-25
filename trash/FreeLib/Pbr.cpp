#include "FreeLib.h"

#if 0

NAMESPACE_PBR_BEGIN


PrimitiveBuilder& PrimitiveBuilder::AddSphere(float diameter, uint32 tessellation, Pbr::NodeIndex_t trans_idx) {
	TODO
}

PrimitiveBuilder& PrimitiveBuilder::AddCube(float side_length, Pbr::NodeIndex_t trans_idx) {
	TODO
}






mat4 Node::GetTransform() const {
	TODO
}








Material& Primitive::GetMaterial() {
	TODO
}

const Material& Primitive::GetMaterial() const {
	TODO
}






Model::Model() {
	
}

void Model::Clone(const Pbr::Resources& pbr_res, Model& dst) const {
	TODO
}

Optional<NodeIndex_t> Model::FindFirstNode(char const* name, const Optional<NodeIndex_t>& parent_node_idx) const {
	TODO
}

mat4 Model::GetNodeWorldTransform(NodeIndex_t nodeIndex) const {
	TODO
}

NodeIndex_t Model::GetNodeCount() const {
	TODO
}

Node& Model::GetNode(NodeIndex_t nodeIndex) {
	TODO
}

const Node& Model::GetNode(NodeIndex_t nodeIndex) const {
	TODO
}

int Model::GetPrimitiveCount() const {
	TODO
}

Primitive& Model::GetPrimitive(int i) {
	TODO
}


NAMESPACE_PBR_END

#endif
