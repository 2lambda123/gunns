#ifndef GunnsElectBattery_EXISTS
#define GunnsElectBattery_EXISTS

/**
@file
@brief    GUNNS Electrical Battery declarations

@defgroup GUNNS_ELECTRICAL_BATTERY_LINK    GUNNS Electrical Battery Model
@ingroup  GUNNS_ELECTRICAL_BATTERY

@copyright Copyright 2019 United States Government as represented by the Administrator of the
           National Aeronautics and Space Administration.  All Rights Reserved.

@details
PURPOSE:
- (Classes for the GUNNS Electrical Battery link model.)

 REFERENCE:
- (TBD)

 ASSUMPTIONS AND LIMITATIONS:
- (TBD)

 LIBRARY DEPENDENCY:
- ((GunnsElectBattery.o))

 PROGRAMMERS:
- ((Jason Harvey) (CACI) (Initial) (2016-09))

@{
*/

#include "core/GunnsBasicPotential.hh"
#include "math/approximation/TsLinearInterpolator.hh"
#include "GunnsElectBatteryCell.hh"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    Electrical Battery Model Configuration Data
///
/// @details  This class provides a data structure for the GunnsElectBattery configuration data.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsElectBatteryConfigData : public GunnsBasicPotentialConfigData
{
    public:
        int                   mNumCells;               /**< (--)     trick_chkpnt_io(**) Number of battery cells. */
        bool                  mCellsInParallel;        /**< (--)     trick_chkpnt_io(**) Whether the cells are in parallel (True) or series (False). */
        double                mCellResistance;         /**< (ohm)    trick_chkpnt_io(**) Internal resistance of each cell. */
        double                mInterconnectResistance; /**< (ohm)    trick_chkpnt_io(**) Total interconnect resistance between all cells. */
        double                mMaxCapacity;            /**< (amp*hr) trick_chkpnt_io(**) Maximum charge capacity of the battery. */
        TsLinearInterpolator* mSocVocTable;            /**< (--)     trick_chkpnt_io(**) Pointer to open-circuit voltage vs. State of Charge table. */
        /// @brief Electrical Battery Model configuration data default constructor.
        GunnsElectBatteryConfigData(const std::string     name                   = "",
                                    GunnsNodeList*        nodes                  = 0,
                                    const int             numCells               = 0,
                                    const bool            cellsInParallel        = false,
                                    const double          cellResistance         = 0.0,
                                    const double          interconnectResistance = 0.0,
                                    const double          maxCapacity            = 0.0,
                                    TsLinearInterpolator* socVocTable            = 0);
        /// @brief Electrical Battery Model configuration data default destructor.
        virtual ~GunnsElectBatteryConfigData();

    private:
        /// @brief Copy constructor is not available since declared private and not implemented.
        GunnsElectBatteryConfigData(const GunnsElectBatteryConfigData&);
        /// @brief Assignment operator is not available since declared private and not implemented.
        GunnsElectBatteryConfigData& operator =(const GunnsElectBatteryConfigData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    Electrical Battery Model Input Data
///
/// @details  This class provides a data structure for the GunnsElectBattery input data.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsElectBatteryInputData : public GunnsBasicPotentialInputData
{
    public:
        double mSoc;         /**< (--) trick_chkpnt_io(**) Initial battery State of Charge (0-1). */
        /// @brief Electrical Battery Model input data default constructor.
        GunnsElectBatteryInputData(const bool   malfBlockageFlag  = false,
                                   const double malfBlockageValue = 0.0,
                                   const double soc               = 0.0);
        /// @brief Electrical Battery Model input data default destructor.
        virtual ~GunnsElectBatteryInputData();

    private:
        /// @brief Copy constructor is not available since declared private and not implemented.
        GunnsElectBatteryInputData(const GunnsElectBatteryInputData&);
        /// @brief  Assignment operator unavailable since declared private and not implemented.
        GunnsElectBatteryInputData& operator =(const GunnsElectBatteryInputData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    Electrical Battery Model Class
///
/// @details  This models an electrical battery containing one or more voltage cells in series or
///           parallel.  The battery acts like a voltage (potential) source in the network, with
///           internal resistance based on the cells' internal resistance and resistance of the
///           interconnects between the cells.  The actual closed-circuit output voltage of this
///           battery in a circuit is its open-circuit voltage minus the drop under load (current)
///           due to the total internal resistance, same as any basic potential source.
///
///           With the cells in series, the battery's open-circuit voltage (base class
///           mSourcePotential term) is the sum of the voltages of the cells, which are a function
///           of their individual States of Charge.  With the cells in parallel, the battery's open-
///           circuit voltage is that of the cell with the highest voltage.
///
///           Port 0 of the link is the input port, and Port 1 is the output port.  The closed-
///           circuit output voltage is equal to the Port 1 node potential.
///
///           This is a consolidation & improvement of the old BattElect and BattElectEmu links
///           originally written for TS21.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsElectBattery: public GunnsBasicPotential
{
    TS_MAKE_SIM_COMPATIBLE (GunnsElectBattery);

    public:
        /// @name    Embedded objects.
        /// @{
        /// @details Embedded objects are public to allow access from the Trick events processor.
        GunnsElectBatteryCell* mCells;                  /**< (--)     trick_chkpnt_io(**) Battery cells. */
        /// @}
        /// @brief   Electrical Battery Model default constructor.
        GunnsElectBattery();
        /// @brief   Electrical Battery Model default destructor.
        virtual ~GunnsElectBattery();
        /// @brief   Electrical Battery Model initialize method.
        void           initialize(GunnsElectBatteryConfigData&  configData,
                                  GunnsElectBatteryInputData&   inputData,
                                  std::vector<GunnsBasicLink*>& networkLinks,
                                  const int                     port0,
                                  const int                     port1);
        /// @brief   Updates the link's conductance and potential source.
        virtual void   updateState(const double timeStep);
        /// @brief   Updates the flux through the link and its effects.
        virtual void   updateFlux(const double timeStep, const double flux);
        /// @brief   Returns the output closed-circuit voltage under load.
        virtual double getVoltage() const;
        /// @brief   Returns the state of charge.
        virtual double getSoc() const;

    protected:
        int                    mNumCells;               /**< (--)     trick_chkpnt_io(**) Number of battery cells. */
        bool                   mCellsInParallel;        /**< (--)     trick_chkpnt_io(**) Whether the cells are in parallel (True) or series (False). */
        double                 mInterconnectResistance; /**< (ohm)    trick_chkpnt_io(**) Total interconnect resistance between all cells. */
        TsLinearInterpolator*  mSocVocTable;            /**< (--)     trick_chkpnt_io(**) Pointer to open-circuit voltage vs. State of Charge table. */
        double                 mSoc;                    /**< (--)     trick_chkpnt_io(**) Battery average State Of Charge (0-1) of active cells. */
        double                 mCurrent;                /**< (amp)    trick_chkpnt_io(**) Battery current. */
        double                 mVoltage;                /**< (V)      trick_chkpnt_io(**) Output closed-circuit voltage under load. */
        /// @brief   Validates the link's configuration and input data.
        void         validate(GunnsElectBatteryConfigData& configData,
                              GunnsElectBatteryInputData&  inputData);
        /// @brief   Allocates dynamic arrays based on the number of battery cells.
        void         allocateArrays();
        /// @brief   Deletes dynamic memory objects.
        void         cleanup();
        /// @brief   Virtual method for derived links to perform their restart functions.
        virtual void restartModel();
        /// @brief   Finds resistance of all cells in parallel.
        double       computeParallelResistance() const;
        /// @brief   Finds resistance of all cells in series.
        double       computeSeriesResistance() const;
        /// @brief   Finds total Voc of all cells in parallel.
        double       computeParallelVoc() const;
        /// @brief   Finds total Voc of all cells in series.
        double       computeSeriesVoc() const;
        /// @brief   Updates the cells State of Charge.
        void         updateCells(const double timeStep);
        /// @brief   Updates the battery model output terms.
        void         updateOutputs();

    private:
        /// @brief Copy constructor unavailable since declared private and not implemented.
        GunnsElectBattery(const GunnsElectBattery& that);
        /// @brief Assignment operator unavailable since declared private and not implemented.
        GunnsElectBattery& operator =(const GunnsElectBattery& that);
};

/// @}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @returns double (V) Output closed-circuit voltage under load.
///
/// @details Returns the battery's output closed-circuit voltage under load.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline double GunnsElectBattery::getVoltage() const
{
    return mVoltage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @returns double (--) Output average State Of Charge (0-1) of active cells.
///
/// @details Returns the battery's output average State Of Charge (0-1) of active cells.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline double GunnsElectBattery::getSoc() const
{
    return mSoc;
}

#endif