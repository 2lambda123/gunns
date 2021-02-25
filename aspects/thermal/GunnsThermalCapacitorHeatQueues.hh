#ifndef GunnsThermalCapacitorHeatQueues_EXISTS
#define GunnsThermalCapacitorHeatQueues_EXISTS

/**
@file      GunnsThermalCapacitorHeatQueues.hh
@brief     GUNNS Thermal Capacitor Heat Queues Spotter declarations

@defgroup  TSM_GUNNS_THERMAL_CAPACITOR_HEAT_QUEUES   GUNNS Thermal Capacitor Heat Queues Spotter
@ingroup   TSM_GUNNS_THERMAL

@copyright Copyright 2020 United States Government as represented by the Administrator of the
           National Aeronautics and Space Administration.  All Rights Reserved.

PURPOSE:   (Provides the classes for the GUNNS Thermal Capacitor Heat Queues Spotter.
            This spotter is used to collect heat from sim bus queues for a GunnsThermalCapacitor.
            The GunnsThermalCapaciftor doesn't have variables to receive queues directly from the
            sim bus.  This spotter allows heats generated by a model with a higher execution rate
            than the capacitor to be queued and integrated, for better conservation of energy.)

@details
REFERENCE:
- (TBD)

ASSUMPTIONS AND LIMITATIONS:
- (TBD)

LIBRARY DEPENDENCY:
- ((GunnsThermalCapacitorHeatQueues.o))

PROGRAMMERS:
- ((Jason Harvey) (CACI) (2020-09) (Initial))

@{
*/

#include <vector>
#include "software/SimCompatibility/TsSimCompatibility.hh"
#include "aspects/thermal/GunnsThermalCapacitor.hh"
#include "core/GunnsNetworkSpotter.hh"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    GUNNS Thermal Capacitor Heat Queues Spotter Configuration Data
///
/// @details  This class provides a data structure for the Thermal Capacitor Heat Queues Spotter
///           configuration data.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsThermalCapacitorHeatQueuesConfigData : public GunnsNetworkSpotterConfigData
{
    public:
        /// @brief  Default constructs this GUNNS Thermal Capacitor Heat Queues Spotter configuration data.
        GunnsThermalCapacitorHeatQueuesConfigData(const std::string& name);
        /// @brief  Default destructs this GUNNS Thermal Capacitor Heat Queues Spotter configuration data.
        virtual ~GunnsThermalCapacitorHeatQueuesConfigData();

    private:
        /// @brief  Copy constructor unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueuesConfigData(const GunnsThermalCapacitorHeatQueuesConfigData& that);
        /// @brief  Assignment operator unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueuesConfigData& operator =(const GunnsThermalCapacitorHeatQueuesConfigData& that);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    GUNNS Thermal Capacitor Heat Queues Spotter Input Data
///
/// @details  This class provides a data structure for the Thermal Capacitor Heat Queues Spotter
///           input data.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsThermalCapacitorHeatQueuesInputData : public GunnsNetworkSpotterInputData
{
    public:
        /// @brief  Default constructs this GUNNS Thermal Capacitor Heat Queues Spotter input data.
        GunnsThermalCapacitorHeatQueuesInputData();
        /// @brief  Default destructs this GUNNS Thermal Capacitor Heat Queues Spotter input data.
        virtual ~GunnsThermalCapacitorHeatQueuesInputData();

    private:
        /// @brief  Copy constructor unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueuesInputData(const GunnsThermalCapacitorHeatQueuesInputData& that);
        /// @brief  Assignment operator unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueuesInputData& operator =(const GunnsThermalCapacitorHeatQueuesInputData& that);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    GUNNS Thermal Capacitor Heat Queue Data.
///
/// @details  This provides the sim bus target variables for one queue of heat values.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsThermalCapacitorHeatQueueData
{
    public:
        double* mHeat_queue;      /**< (W) Queued heat data values. */
        int     mHeat_queue_size; /**< (1) Current size of the data queue. */
        /// @brief  Default constructs this GUNNS Thermal Capacitor Heat Queue data.
        GunnsThermalCapacitorHeatQueueData();
        /// @brief  Default destructs this GUNNS Thermal Capacitor Heat Queue data.
        virtual ~GunnsThermalCapacitorHeatQueueData();

    private:
        /// @brief  Copy constructor unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueueData(const GunnsThermalCapacitorHeatQueueData& that);
        /// @brief  Assignment operator unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueueData& operator =(const GunnsThermalCapacitorHeatQueueData& that);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    GUNNS Thermal Capacitor Heat Queues Spotter Class.
///
/// @details  This spotter is used to integrate heats from a faster running model via sim bus queues
///           and give the integrated heat to a GunnsThermalCapacitor link.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsThermalCapacitorHeatQueues : public GunnsNetworkSpotter
{
    TS_MAKE_SIM_COMPATIBLE(GunnsThermalCapacitorHeatQueues);
    public:
        /// @brief  Default Constructor
        GunnsThermalCapacitorHeatQueues(GunnsThermalCapacitor& capacitor);
        /// @brief   Default destructor.
        virtual     ~GunnsThermalCapacitorHeatQueues();
        /// @brief   Initializes the GUNNS Thermal Capacitor Heat Queues Spotter with configuration and
        ///          input data.
        virtual void initialize(const GunnsNetworkSpotterConfigData* configData,
                                const GunnsNetworkSpotterInputData*  inputData);
        /// @brief   Steps the GUNNS Thermal Capacitor Heat Queues Spotter prior to the GUNNS solver step.
        virtual void stepPreSolver(const double dt);
        /// @brief   Steps the GUNNS Thermal Capacitor Heat Queues Spotter after the GUNNS solver step.
        virtual void stepPostSolver(const double dt);

    protected:
        GunnsThermalCapacitor& mCapacitor; /**< *o (1) trick_chkpnt_io(**) Reference to the thermal capacitor. */
        GunnsThermalCapacitorHeatQueueData mQueues[GunnsThermalCapacitor::NUM_EXT_HEATFLUXES]; /**< *o (1) trick_chkpnt_io(**) Array of the sim bus queues. */
        /// @brief   Validates the supplied configuration data.
        const GunnsThermalCapacitorHeatQueuesConfigData* validateConfig(const GunnsNetworkSpotterConfigData* config);
        /// @brief   Validates the supplied input data.
        const GunnsThermalCapacitorHeatQueuesInputData*  validateInput (const GunnsNetworkSpotterInputData* input);

    private:
        /// @brief  Copy constructor unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueues(const GunnsThermalCapacitorHeatQueues& that);
        /// @brief  Assignment operator unavailable since declared private and not implemented.
        GunnsThermalCapacitorHeatQueues& operator =(const GunnsThermalCapacitorHeatQueues& that);
};

/// @}

#endif