#!/usr/bin/python
# @copyright Copyright 2019 United States Government as represented by the Administrator of the
#            National Aeronautics and Space Administration.  All Rights Reserved.
#
# @revs_title
# @revs_begin
# @rev_entry(Jason Harvey, CACI, GUNNS, March 2019, --, Initial implementation.}
# @revs_end
#
# This is a dictionary of geometry biases and coordinates to translate a GunnShow link shape
# to its corresponding GunnsDraw shape, so the GunnsDraw shape will appear with the same
# orientation and connection points as in the source GunnShow drawing.
#
# The key is the GunnsDraw subtype (GunnShow model path), and the value is another dict of values.
# value = {direction, rotation, scaleX, scaleY, biasX, biasY, flipX, flipY, [connect_0, connect_1...]}
# direction: overrides the default GD shape style direction.  This applies a 90, 180, or 270 bias to the shape's rotation
#            (not including the label) before the GS rotation value is applied.
# rotation:  allow or inhibit rotation angle
# flipX/Y:  'ignore' - ignore the GunnShow flip states and don't flip this axis.
#           'gs'     - use the GunnShow flip state as-is
#           'flip'   - flip this axis relative to the GunnShow flip state, i.e logical not the flip state with the GunnShow value.
# connects: location of the connection points in the GunnsDraw shape, and which link ports have an affinity for each connection point.
#           [x, y, [affinity ports]]

migrate_link_map = {
    'core/GunnsBasicCapacitor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsBasicConductor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsBasicExternalDemand': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'core/GunnsBasicExternalSupply': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'core/GunnsBasicFlowController': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsBasicJumper': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsBasicPotential': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsBasicSocket': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'core/GunnsBasicSource': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsFluidCapacitor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    0.5,
        'scaleY':    0.5,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]]],
        },
    'core/GunnsFluidConductor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsFluidExternalDemand': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'core/GunnsFluidExternalSupply': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'core/GunnsFluidFlowController': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsFluidJumper': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsFluidPotential': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'core/GunnsFluidShadow': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [1]]],
        },
    'core/GunnsFluidSocket': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'core/GunnsFluidSource': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/electrical/Batt/GunnsElectBattery': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'flip',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/electrical/ConstantPowerLoad/EpsConstantPowerLoad': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/electrical/Converter/ConverterElect': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     -12.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [2]]],
        },
    'aspects/electrical/Diode/GunnsElectRealDiode': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    # IPS/IpsElect isn't currently supported...
    # PowerBus/PowerBusElect isn't currently supported...
    'aspects/electrical/resistive/GunnsElectricalResistor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/electrical/resistive/GunnsResistiveLoad': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/electrical/resistive/GunnsResistorPowerFunction': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/electrical/sar/GunnsSolarArrayRegulator': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     1.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [2]]],
        },
    'aspects/electrical/SolarArray/GunnsElectPvArray': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [0]]],
        },
    'aspects/electrical/SolarArray/GunnsElectPvRegConv': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     20.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [0]]],
        },
    'aspects/electrical/SolarArray/GunnsElectPvRegShunt': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     20.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]],[1.0, 0.5, [1]]],
        },
    'aspects/electrical/SolarArray/SolarArray': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/electrical/Switch/GunnsElectSelector': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.045, [1]], [1.0, 0.35, [2]], [1.0, 0.65, [3]], [1.0, 0.955, [4]]],
        },
    'aspects/electrical/Switch/GunnsElectUserLoadSwitch': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     -20.0,
        'biasY':     -10.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 1.0, [0,1]], [1.0, 1.0, [0,1]]],
        },
    'aspects/electrical/Switch/SwitchElect': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 1.0, [0,1]], [1.0, 1.0, [0,1]]],
        },
    # SwitchCardElect isn't currently supported...
    'aspects/fluid/capacitor/GunnsFluidAccum': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [1]]],
        },
    'aspects/fluid/capacitor/GunnsFluidAccumGas': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [1]], [1.0, 0.5, [0]]],
        },
    'aspects/fluid/capacitor/GunnsFluidBalloon': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/capacitor/GunnsFluidTank': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]]],
        },
    'aspects/fluid/conductor/GunnsFluid3WayCheckValve': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     10.0,
        'flipX':     'ignore',
        'flipY':     'gs',
        'connects':  [[0.0, 0.667, [0,1]], [1.0, 0.667, [0,1]], [0.5, 0.0, [2]]],
        },
    'aspects/fluid/conductor/GunnsFluid3WayValve': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     -1.5,
        'biasY':     6.0,
        'flipX':     'ignore',
        'flipY':     'gs',
        'connects':  [[0.0, 0.667, [0,1]], [1.0, 0.667, [0,1]], [0.5, 0.0, [2]]],
        },
    'aspects/fluid/conductor/GunnsFluidBalancedPrv': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     5.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.6, [0,1]], [1.0, 0.6, [0,1]], [0.5, 0.0, [2]]],
        },
    'aspects/fluid/conductor/GunnsFluidCheckValve': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/conductor/GunnsFluidCondensingHx': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/conductor/GunnsFluidCondensingHxSeparator': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/conductor/GunnsFluidEqConductor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidHatch': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidHeatExchanger': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidLeak': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidLiquidWaterSensor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]], [0.5, 0.0, [0,1]], [0.5, 1.0, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidPhaseChangeConductor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/conductor/GunnsFluidPipe': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidRegulatorValve': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     -5.0,
        'flipX':     'ignore',
        'flipY':     'gs',
        'connects':  [[0.0, 0.667, [0,1]], [1.0, 0.667, [0,1]], [0.625, 0.0, [2,3]], [0.375, 0.0, [2,3]]],
        },
    'aspects/fluid/conductor/GunnsFluidReliefValve': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     -5.0,
        'flipX':     'ignore',
        'flipY':     'gs',
        'connects':  [[0.0, 0.667, [0,1]], [1.0, 0.667, [0,1]], [0.625, 0.0, [2,3]], [0.375, 0.0, [2,3]]],
        },
    'aspects/fluid/conductor/GunnsFluidSensor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]], [0.5, 0.0, [0,1]], [0.5, 1.0, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidSimpleQd': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidSimpleRocket': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/conductor/GunnsFluidValve': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/conductor/GunnsFluidGasTurbine': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/hi-fi/GunnsFluidHiFiOrifice': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/hi-fi/GunnsFluidHiFiValve': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/potential/GunnsFluidImpeller': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/potential/GunnsGasFan': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]], [0.5, 0.0, [0,1]], [0.5, 1.0, [0,1]]],
        },
    'aspects/fluid/potential/GunnsLiquidCentrifugalPump': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]], [0.5, 0.0, [0,1]], [0.5, 1.0, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidAdsorber': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidEvaporation': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/source/GunnsFluidFireSource': {
        'direction': 'north',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.5, 1.0, [0]]],
        },
    'aspects/fluid/source/GunnsFluidHeater': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidHotAdsorber': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidHotReactor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidMetabolic': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [1]], [1.0, 0.5, [1]], [0.5, 0.0, [1]], [0.5, 1.0, [1]]],
        },
    'aspects/fluid/source/GunnsFluidMetabolic2': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [1]], [1.0, 0.5, [1]], [0.5, 0.0, [1]], [0.5, 1.0, [1]]],
        },
    'aspects/fluid/source/GunnsFluidMultiAdsorber': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidPhaseChangeSource': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/source/GunnsFluidReactor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidSelectiveMembrane': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     10.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.75, [0,1]], [1.0, 0.75, [0,1]], [0.5, 0.0, [2]]],
        },
    'aspects/fluid/source/GunnsFluidSeparatorGas': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidSeparatorLiquid': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/fluid/source/GunnsFluidSimpleH2Redox': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.167, 0.0, [0]], [0.167, 1.0, [1]]],
        },
    'aspects/fluid/source/GunnsFluidSourceBoundary': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [0]]],
        },
    'aspects/fluid/source/GunnsFluidSublimator': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/source/GunnsGasDisplacementPump': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/fluid/source/GunnsLiquidDisplacementPump': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]], [1.0, 0.5, [1]]],
        },
    'aspects/thermal/GunnsThermalCapacitor': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    0.5,
        'scaleY':    0.5,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]]],
        },
    'aspects/thermal/GunnsThermalHeater': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [0]]],
        },
    'aspects/thermal/GunnsThermalMultiPanel': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'flip',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]]],
        },
    'aspects/thermal/GunnsThermalPanel': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'flip',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0]]],
        },
    'aspects/thermal/GunnsThermalPhaseChangeBattery': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'flip',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [0]]],
        },
    'aspects/thermal/GunnsThermalPotential': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [0]]],
        },
    'aspects/thermal/GunnsThermalRadiation': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'aspects/thermal/GunnsThermalSource': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'gs',
        'flipY':     'gs',
        'connects':  [[1.0, 0.5, [0]]],
        },
    'aspects/thermal/GunnsThermoelectricDevice': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     10.0,
        'flipX':     'gs',
        'flipY':     'flip',
        'connects':  [[0.0, 0.0, [0]], [1.0, 0.0, [1]]],
        },
    # TODO nexsys_subsystems links, move out to user-defined area...
    'gunns/GunnsFluidMetabolic4': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [1]], [1.0, 0.5, [1]], [0.5, 0.0, [1]], [0.5, 1.0, [1]]],
        },
    'gunns/GunnsFluidAdsorberRca': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    'gunns/GunnsFluidCdraAdsorber': {
        'direction': 'east',
        'rotation' : True,
        'scaleX':    1.0,
        'scaleY':    1.0,
        'biasX':     0.0,
        'biasY':     0.0,
        'flipX':     'ignore',
        'flipY':     'ignore',
        'connects':  [[0.0, 0.5, [0,1]], [1.0, 0.5, [0,1]]],
        },
    }
