#include <string>
#include <pybind11/pybind11.h>
#include <util/MMapQueue.hpp>
namespace py = pybind11;

PYBIND11_MODULE(trading, m)
{
    py::class_<MMapQueueV2>(m, "mmapQueueV2")
        .def(py::init<std::string &, size_t>())
        .def("push", &MMapQueueV2::push)
        .def("pop", &MMapQueueV2::pop);
}
