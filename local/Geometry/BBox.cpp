#include "Geometry.h"

NAMESPACE_OULU_BEGIN



BoundingBox::BoundingBox() {
	
}

BoundingBox::BoundingBox(vec3 min, vec3 max)
		: m_min(min), m_max(max) {
	
}

void BoundingBox::SetMinMax(vec3 min, vec3 max) {
	m_min = min;
	m_max = max;
}

void BoundingBox::GetMinMax(vec3& min, vec3& max) const {
	min = m_min;
	max = m_max;
}

vec3 BoundingBox::GetDimensions() const {
	return m_max - m_min;
}

vec3 BoundingBox::GetCenter(Align align) const {
	vec3 center = (m_min + m_max) * 0.5f;
	if (align == ALIGN_CENTER) {
		return center;
	}
	vec3 half_dim = (m_max - m_min) * 0.5f;
	switch (align) {
	case ALIGN_X_MIN:
		center[0] -= half_dim[0];
		break;
	case ALIGN_X_MAX:
		center[0] += half_dim[0];
		break;
	case ALIGN_Y_MIN:
		center[1] -= half_dim[1];
		break;
	case ALIGN_Y_MAX:
		center[1] += half_dim[1];
		break;
	case ALIGN_Z_MIN:
		center[2] -= half_dim[2];
		break;
	case ALIGN_Z_MAX:
		center[2] += half_dim[2];
		break;
	default:
		break;
	}
	return center;
}

bool BoundingBox::Contains(vec3 pos) const {
	vec3 _min = m_min - vec3(EPSILONf);
	vec3 _max = m_max + vec3(EPSILONf);
	return pos[0] > _min[0] && pos[1] > _min[1] && pos[2] > _min[2] &&
		   pos[0] < _max[0] && pos[1] < _max[1] && pos[2] < _max[2];
}

vec3 BoundingBox::GetLimit(vec3 pos) const {
	vec3 _pos = pos;
	_pos[0] = std::min(_pos[0], m_max[0]);
	_pos[1] = std::min(_pos[1], m_max[1]);
	_pos[2] = std::min(_pos[2], m_max[2]);
	_pos[0] = std::max(_pos[0], m_min[0]);
	_pos[1] = std::max(_pos[1], m_min[1]);
	_pos[2] = std::max(_pos[2], m_min[2]);
	return _pos;
}

vec3 BoundingBox::GetWrap(vec3 pos) const {
	vec3 _pos = pos;
	if (_pos[0] < m_min[0]) {
		_pos[0] = m_max[0];
	}
	if (_pos[1] < m_min[1]) {
		_pos[1] = m_max[1];
	}
	if (_pos[2] < m_min[2]) {
		_pos[2] = m_max[2];
	}
	if (_pos[0] > m_max[0]) {
		_pos[0] = m_min[0];
	}
	if (_pos[1] > m_max[1]) {
		_pos[1] = m_min[1];
	}
	if (_pos[2] > m_max[2]) {
		_pos[2] = m_min[2];
	}
	return _pos;
}






NAMESPACE_OULU_END
