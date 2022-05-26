#include "IHolograph.h"


NAMESPACE_PARALLEL_BEGIN


namespace {

constexpr const char* TouchIndicatorMaterialName = "TouchIndicator";

// Decompose, interpolate each component, and then recompose.
void InterpolateNode(const Pbr::Node& min, const Pbr::Node& max, float t, Pbr::Node& result)
{
    vec4 min_scale, min_rot, min_trans;
    vec4 max_scale, max_rot, max_trans;
    if (XMMatrixDecompose(&min_scale, &min_rot, &min_trans, min.GetTransform()) &&
        XMMatrixDecompose(&max_scale, &max_rot, &max_trans, max.GetTransform()))
    {
        const mat4 interpolated_matrix =
            XMMatrixScalingFromVector(XMVectorLerp(min_scale, max_scale, t)) *
            XMMatrixRotationQuaternion(XMQuaternionSlerp(min_rot, max_rot, t)) *
            XMMatrixTranslationFromVector(XMVectorLerp(min_trans, max_trans, t));
        result.SetTransform(interpolated_matrix);
    }
}

void AddTouchpadTouchIndicator(Pbr::Model& ctrl_model, Pbr::Resources& pbr_res)
{
    // Create a material for the touch indicator. Use emissive color so it is visible in all light conditions.
    Shared<Pbr::Material> touch_indi_material = Pbr::Material::CreateFlat(
        pbr_res,
        Colors::Black /* base color */,
        0.5f /* roughness */,
        0.0f /* metallic */,
        Colors::DarkSlateBlue /* emissive */);
    touch_indi_material->name = TouchIndicatorMaterialName;
    touch_indi_material->hidden = true;

    // Add a touch indicator primitive parented to the TOUCH node. This material will be hidden or visible based on the touch state.
    for (auto i = 0; i < ctrl_model.GetNodeCount(); i++)
    {
        Pbr::Node& node = ctrl_model.GetNode(i);
        if (node.Name == "TOUCH") // Add a touch indicator sphere to the TOUCH node.
        {
            // Create a new node parented to the TOUCH node. This node will positioned at the correct place.
            const Pbr::Node& touch_indi_node = ctrl_model.AddNode(XMMatrixIdentity(), node.index, "TouchIndicator");

            // Create a sphere primitive which is rooted on the TOUCH node.
            Pbr::PrimitiveBuilder touch_sphere;
            touch_sphere.AddSphere(0.004f /* Diameter */, 5 /* Tessellation */, touch_indi_node.index);

            ctrl_model.AddPrimitive(Pbr::Primitive(pbr_res, touch_sphere, touch_indi_material));
        }
    }
}

}

namespace ControllerRendering {

/*ControllerModelKey GetControllerModelKey(const SpatialInteractionSource& source) {
    if (!source.Controller()) {
        return {};
    }
    return std::make_tuple(source.Controller().ProductId(), source.Controller().VendorId(), source.Controller().Version(), source.Handedness());
}*/

/*
template <class Holo>
Future<Shared<const Pbr::Model>> ControllerRenderingT<Holo>::TryLoadRenderModelAsync(
    Shared<Pbr::Resources> pbr_res,
    SpatialInteractionSource source)
{
    const SpatialInteractionController controller = source.Controller();
    if (!controller)
    {
        co_return nullptr;
    }

    IRandomAccessStreamWithContentType model_stream = co_await controller.TryGetRenderableModelAsync();
    if (model_stream == nullptr) // Mesh data is optional. If not available, a null stream is returned.
    {
        co_return nullptr;
    }

    // Gltf::FromGltfBinary is a synchronous operation and can be slow, so do it in a background context
    ResumeBackground();

    // Read all data out of the stream.
    DataReader dr(model_stream.GetInputStreamAt(0));
    uint32 read_amount = co_await dr.LoadAsync(static_cast<unsigned int>(model_stream.Size()));
    const IBuffer buffer = dr.DetachBuffer();

    uint8* raw_buffer;
    Holo::CheckResult(buffer.as<::Windows::Storage::Streams::IBufferByteAccess>()->Buffer(&raw_buffer));

    // Load the binary controller model data into a Pbr::Model
    const Shared<Pbr::Model> model = Gltf::FromGltfBinary(*pbr_res, raw_buffer, buffer.Length());

    // Give the model a debug friendly name.
    model->name = source.Handedness() == SpatialInteractionSourceHandedness::Left ? "Left" :
                  source.Handedness() == SpatialInteractionSourceHandedness::Right ? "Right" : "Unspecified";

    // Add a touchpad touch indicator node and primitive/material to the model.
    AddTouchpadTouchIndicator(*model, *pbr_res);

    co_return model;
}
*/

template <class Holo>
ArticulateValues ControllerRenderingT<Holo>::GetArticulateValues(constSpatialSourceState& src_state)
{
    ArticulateValues arti_vals;

    arti_vals.grasp_press = src_state.IsGrasped() ? 1.0f : 0.0f;
    arti_vals.menu_press = src_state.IsMenuPressed() ? 1.0f : 0.0f;
    arti_vals.select_press = (float)src_state.SelectPressedValue();
    arti_vals.thumbstick_press = src_state.ControllerProperties().IsThumbstickPressed() ? 1.0f : 0.0f;
    arti_vals.thumbstick_x = (float)(src_state.ControllerProperties().thumbstick_x() / 2) + 0.5f;
    arti_vals.thumbstick_y = (float)(src_state.ControllerProperties().thumbstick_y() / 2) + 0.5f;
    arti_vals.touchpad_press = src_state.ControllerProperties().IsTouchpadPressed() ? 1.0f : 0.0f;

    // If the the touchpad is pressed, use the touch location to control touchpad tilting, otherwise keep it centered.
    arti_vals.touch_indicator_visible = src_state.ControllerProperties().IsTouchpadTouched();
    arti_vals.touchpad_touch_x = (float)(src_state.ControllerProperties().TouchpadX() / 2) + 0.5f;
    arti_vals.touchpad_touch_y = (float)(src_state.ControllerProperties().TouchpadY() / 2) + 0.5f;
    arti_vals.touchpad_press_x = src_state.ControllerProperties().IsTouchpadPressed() ? arti_vals.touchpad_touch_x : 0.5f;
    arti_vals.touchpad_press_y = src_state.ControllerProperties().IsTouchpadPressed() ? arti_vals.touchpad_touch_y : 0.5f;

    return arti_vals;
}

template <class Holo>
void ControllerRenderingT<Holo>::ArticulateControllerModel(ArticulateValues const& arti_vals, Pbr::Model& model)
{
    // Every articulatable node in the model has three children, two which define the extents of the motion and one (VALUE) which holds the interpolated value.
    // In some cases, there nodes are nested to create combined transformations, like the X and Y movements of the thumbstick.
    auto interpolate_node = [&](Pbr::Node& root_node, const char* min_name, const char* max_name, float t)
    {
        const Optional<Pbr::NodeIndex> min_child = model.FindFirstNode(min_name, root_node.index);
        const Optional<Pbr::NodeIndex> max_child = model.FindFirstNode(max_name, root_node.index);
        const Optional<Pbr::NodeIndex> value_child = model.FindFirstNode("VALUE", root_node.index);
        if (min_child && max_child && value_child) {
            InterpolateNode(model.GetNode(min_child.value()), model.GetNode(max_child.value()), t, model.GetNode(value_child.value()));
        }
    };

    for (uint32 i = 0; i < model.GetNodeCount(); i++)
    {
        Pbr::Node& node = model.GetNode(i);
        if (node.Name == "GRASP") { interpolate_node(node, "UNPRESSED", "PRESSED", arti_vals.grasp_press); }
        else if (node.Name == "MENU") { interpolate_node(node, "UNPRESSED", "PRESSED", arti_vals.menu_press); }
        else if (node.Name == "SELECT") { interpolate_node(node, "UNPRESSED", "PRESSED", arti_vals.select_press); }
        else if (node.Name == "THUMBSTICK_PRESS") { interpolate_node(node, "UNPRESSED", "PRESSED", arti_vals.thumbstick_press); }
        else if (node.Name == "THUMBSTICK_X") { interpolate_node(node, "MIN", "MAX", arti_vals.thumbstick_x); }
        else if (node.Name == "THUMBSTICK_Y") { interpolate_node(node, "MAX", "MIN", arti_vals.thumbstick_y); }
        else if (node.Name == "TOUCHPAD_PRESS") { interpolate_node(node, "UNPRESSED", "PRESSED", arti_vals.touchpad_press); }
        else if (node.Name == "TOUCHPAD_PRESS_X") { interpolate_node(node, "MIN", "MAX", arti_vals.touchpad_press_x); }
        else if (node.Name == "TOUCHPAD_PRESS_Y") { interpolate_node(node, "MAX", "MIN", arti_vals.touchpad_press_y); }
        else if (node.Name == "TOUCHPAD_TOUCH_X") { interpolate_node(node, "MIN", "MAX", arti_vals.touchpad_touch_x); }
        else if (node.Name == "TOUCHPAD_TOUCH_Y") { interpolate_node(node, "MAX", "MIN", arti_vals.touchpad_touch_y); }
    }

    // Show or hide touch indicator by showing or hiding the material exclusively used by the touch indicator.
    for (uint32 i = 0; i < model.GetPrimitiveCount(); i++)
    {
        Shared<Pbr::Material>& prim_material = model.GetPrimitive(i).GetMaterial();
        if (prim_material->name == TouchIndicatorMaterialName) { prim_material->hidden = !arti_vals.touch_indicator_visible; }
    }
}

/*
template <class Holo>
Future<Shared<const Pbr::Model>>
	ControllerRenderingT<Holo>::ControllerModelCache::TryGetControllerModelAsync(
	    Shared<Pbr::Resources> pbr_res,
	    SpatialInteractionSource source)
{
    const ControllerRenderingT<Holo>::ControllerModelKey model_key = ControllerRenderingT<Holo>::GetControllerModelKey(source);

    // Check the cache for the model. If one is found, return it.
    {
        Mutex::Lock guard(lock);
        auto ctrl_mesh_it = ctrl_meshes.find(model_key);
        if (ctrl_mesh_it != std::end(ctrl_meshes))
        {
            co_return ctrl_mesh_it->second;
        }
    }

    const Shared<const Pbr::Model> ctrl_model = co_await ControllerRenderingT<Holo>::TryLoadRenderModelAsync(pbr_res, source);
    if (ctrl_model)
    {
        Mutex::Lock guard(lock);
        ctrl_meshes[model_key] = std::move(ctrl_model);
    }

    co_return ctrl_model;
}
*/

template <class Holo>
void ControllerRenderingT<Holo>::ControllerModelCache::ReleaseDeviceDependentResources()
{
    Mutex::Lock guard(lock);
    ctrl_meshes.clear();
}

}

NAMESPACE_PARALLEL_END
