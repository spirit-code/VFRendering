#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "pybind11_glm.hpp"

#include <VFRendering/View.hxx>
#include <VFRendering/Geometry.hxx>
#include <VFRendering/RendererBase.hxx>
#include <VFRendering/ArrowRenderer.hxx>
#include <VFRendering/Options.hxx>

#include <memory>

namespace py = pybind11;
using namespace VFRendering;

typedef unsigned int index_type;

PYBIND11_MODULE(pyVFRendering, m)
{
    py::class_<Geometry>(m, "Geometry")
        .def(py::init<>())
        .def(py::init<const std::vector<glm::vec3>&, const std::vector<std::array<index_type, 3>>&, const std::vector<std::array<index_type, 4>>&, const bool&>())
        .def("cartesianGeometry", &Geometry::cartesianGeometry)
        .def("rectilinearGeometry", &Geometry::rectilinearGeometry)
        .def("min", &Geometry::min)
        .def("max", &Geometry::max);

    py::class_<View>(m, "View")
        .def(py::init<>())
        .def("update", &View::update)
        .def("draw", &View::draw)
        .def("renderers", &View::renderers)
        .def("setFramebufferSize", &View::setFramebufferSize)
        .def("updateOptions", &View::updateOptions);


    py::enum_<Utilities::Colormap>(m, "Colormap")
        .value("HSV", Utilities::Colormap::HSV)
        .value("BLUEWHITERED", Utilities::Colormap::BLUEWHITERED)
        .export_values();

    m.def("getColormapImplementation", &Utilities::getColormapImplementation, "Get a CM implementation from the CM enum");

    
    py::class_<RendererBase, std::shared_ptr<RendererBase>>(m, "RendererBase");
    py::class_<ArrowRenderer, RendererBase, std::shared_ptr<ArrowRenderer>>(m, "ArrowRenderer")
        .def(py::init<View&>());
    
    
    py::class_<Options>(m, "Options")
        .def(py::init<>())
        .def("set_system_center",             &Options::set<View::Option::SYSTEM_CENTER>)
        .def("set_vertical_fov",              &Options::set<View::Option::VERTICAL_FIELD_OF_VIEW>)
        .def("set_background_color",          &Options::set<View::Option::BACKGROUND_COLOR>)
        .def("set_colormap_implementation",   &Options::set<View::Option::COLORMAP_IMPLEMENTATION>)
        .def("set_is_visible_implementation", &Options::set<View::Option::IS_VISIBLE_IMPLEMENTATION>)
        .def("set_camera_position",           &Options::set<View::Option::CAMERA_POSITION>)
        .def("set_center_position",           &Options::set<View::Option::CENTER_POSITION>)
        .def("set_up_vector",                 &Options::set<View::Option::UP_VECTOR>);
}