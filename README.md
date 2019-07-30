# Whole Cell Simulator
 A whole cell model (WCM)  is a comprehensive multi-scale computational
 model representing all the known biochemical processes in a cell. It relies
 on a variety of intracellular pathway models and omics data.

 This computational framework  enables  seamless integration of diverse
 simulation methods used in WCM such as stochastic simulation algorithm
 (SSA), ordinary differential equations (ODE), flux balance analysis (FBA),
 and logic-based approaches.
 These methods run simultaneously, not only for whole pathways but
 also for subsets of reactions. Furthermore, we aim to enable switching
 dynamically between the methods when beneficial.

## Current Requirements:
 + **c++ compiler that supports c++17**
   e.g., clang++ 5.0 or later, g++ 7.1 or later, and icpc 19.0.1 or later

 + **GNU Boost library**
   The particular boost libraries used are `graph`, `filesystem`, `regex` and
   `system`.
   To build with other pre-existing installation of boost, set the environment
   variable `BOOST_ROOT` or pass `-DBOOST_ROOT=<path-to-boost>`
   to cmake. To run the executable, you might need to add `${BOOST_ROOT}/lib`
   to the `LD_LIBRARY_PATH`
   - Guide specific to Livermore Computing (LC) platforms:
     Currently, there are three versions of boost available on TOSS3 systems.
     The one under the default system path, another under
     `/usr/tce/packages/boost/boost-1.69.0-mvapich2-2.2-gcc-4.9.3`, and finally
     the one under `/usr/tce/packages/boost/boost-1.66.0-mvapich2-2.2-gcc-6.1.0`

     The first one does not work well with the compiler choices above.
     The second one works well with the aforementioned clang version, and the
     third with that of gcc. This has to do with the compatibility between the
     compiler used to build the boost library and the one chosen for this project.
 + **cmake 3.12 or later**
   This requirement mostly comes from the compatibility between the cmake
   module `find_package()`, and the version of boost used. An older version
   might still work with some warnings.

## Future requirements:
 + **Charm++ and Charades (ROSS over Charm++)**
 + [**Sundial CVODE**](https://github.com/LLNL/sundials.git)
   For linking with CVODES of Sundials package, use `-DWCS_WITH_SUNDIALS:BOOL=ON`
   and `-DSUNDIALS_ROOT:FILEPATH=<path-to-sundials>`.
   Make sure that Sundials is built with the cmake option `-DBUILD_CVODE:BOOL=ON`.

## Optional requirements:
 + [**libSBML C++ API**](http://sbml.org/Software/libSBML)
 + [**ExprTK**](https://github.com/ArashPartow/exprtk)

 We rely on either of the two approaches to ingest problem inputs. The one
 based on libSBML, currently under development. The other is based on ExprTk
 to parse the formula of the reaction rate annotated to each reaction
 vertex in the GraphML-formatted description of the reaction network.
 To enable one of the optional components, either set the environment
 variable `WCS_WITH_SBML` or `WCS_WITH_EXPRTK`, or invoke cmake with
 the option `-DWCS_WITH_SBML:BOOL=ON` or `-DWCS_WITH_EXPRTK:BOOL=ON`
 respectively for libSBML or ExprTk.
 In case that both are set, only libSBML is enabled and ExprTk is ignored.
 To use a pre-installed libSBML, either set the environment variable
 `SBML_ROOT` or invoke cmake with the option `-DSBML_ROOT=<path-to-libsbml>`.
 For ExprTk, no pre-installation is required as it will automatically download
 it during the build if the presence is not detected. To use a pre-installed
 copy, use the variable `EXPRTK_ROOT`.

## Unit testing:
 + [**Catch2**](https://github.com/catchorg/Catch2)
 We rely on Catch2 for unit testing. To enable testing for development, set
 the environment variable `WCS_WITH_UNIT_TESTING` or invoke cmake with the
 option `-DWCS_WITH_UNIT_TESTING=ON`. No pre-installation of Catch2 is required
 as it is automatically downloaded and made available. To use a pre-installed
 copy, use the variable `CATCH2_ROOT`.
