/* Copyright 2021 The AMReX Community
 *
 * Authors: Axel Huebl
 * License: BSD-3-Clause-LBNL
 */
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <AMReX_Config.H>
#include <AMReX.H>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;


// forward declarations of exposed classes
void init_Box(py::module &);
void init_IntVect(py::module &);

PYBIND11_MODULE(pyamrex_cxx, m) {
    m.doc() = R"pbdoc(
            pyamrex_cxx
            -----------
            .. currentmodule:: pyamrex_cxx

            .. autosummary::
               :toctree: _generate
               Box
               IntVect
    )pbdoc";

    // note: order from parent to child classes
    init_IntVect(m);
    init_Box(m);

    // API runtime version
    //   note PEP-440 syntax: x.y.zaN but x.y.z.devN
#ifdef PYAMReX_VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(PYAMReX_VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif

    // authors
    m.attr("__author__") =
        "Axel Huebl, Shreyas Ananthan, Steven R. Brandt, Andrew Myers, "
        "Weiqun Zhang, et al.";

    // API runtime build-time feature variants
    // m.attr("variants") = amrex::getVariants();
    // TODO allow to query runtime versions of all dependencies

    // license SPDX identifier
    m.attr("__license__") = "BSD-3-Clause-LBNL";

    // TODO broken numpy if not at least v1.15.0: raise warning
    // auto numpy = py::module::import("numpy");
    // auto npversion = numpy.attr("__version__");
    // std::cout << "numpy version: " << py::str(npversion) << std::endl;
}

