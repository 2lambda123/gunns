#!/usr/bin/python
#
# @copyright Copyright 2021 United States Government as represented by the Administrator of the
#            National Aeronautics and Space Administration.  All Rights Reserved.
#
# @revs_title
# @revs_begin
# @rev_entry(Jason Harvey, CACI, GUNNS, June 2021, --, Initial implementation.}
# @revs_end
#
# This lists the classes that will be skipped by the SIM_class_test_compile sim.
# This should contain the classes that cannot be directly instantiated (either pure virtual
# or have private & unimplemented non-default constructors).  These are usually base
# classes for other derived types, and get tested when their derived types are tested.
class_ignore_list = ['GunnsDynEulerBase',
                     'GunnsDynStateTypes',
                     'GunnsDynUtils',
                     'GunnsElectUserLoad',
                     'UserLoadBase',
                     'GunnsTripLogic',
                     'GunnsBasicLink',
                     'GunnsBasicJumperPlug',
                     'GunnsFluidJumperPlug',
                     'GunnsFluidUtils',
                     'GunnsNetworkBase',
                     'GunnsSuperNetworkBase',
                     'GunnsNetworkSpotter',
                     'GunnsMacros',
                     'GunnsInfraMacros',
                     'HtrControl',
                     'TsNoise',
                     'SensorBase',
                     'Combust',
                     'PredefinedMaterialProperties',
                     'SimBusQutils',
                     'TsMemoryManager',
                     'UnitConversion',
                     'TS_random',
                     'TsApproximation',
                     'Sor',
                     'LaguerreMethod',
                     'BrentMethod',
                     'ParseTool',
                     'tinystr.hh',         # possibly to be handled with class_custom_construction
                     'tinyxml.hh',         # possibly to be handled with class_custom_construction
                     'tinyxmlparser.hh',   # possibly to be handled with class_custom_construction
                     'TsHsOutputPlugin.hh',
                     'TsHsMngr',
                     'TsHsMsgFilter',
                    ]