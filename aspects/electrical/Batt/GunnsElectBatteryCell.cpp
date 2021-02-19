/**
@file
@brief    GUNNS Electrical Battery Cell implementation

@copyright Copyright 2019 United States Government as represented by the Administrator of the
           National Aeronautics and Space Administration.  All Rights Reserved.

LIBRARY DEPENDENCY:
 ((math/UnitConversion.o)
  (math/approximation/TsLinearInterpolator.o))
*/

#include "GunnsElectBatteryCell.hh"
#include "math/Math.hh"
#include "core/GunnsBasicNode.hh"    // for H&S macros
#include "math/approximation/TsLinearInterpolator.hh"
#include "simulation/hs/TsHsMsg.hh"
#include "software/exceptions/TsInitializationException.hh"
#include <cfloat>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] resistance  (ohm)    Internal resistance.
/// @param[in] maxCapacity (amp*hr) Maximum charge capacity.
///
/// @details  Default constructs this GunnsElectBatteryCell config data.
////////////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCellConfigData::GunnsElectBatteryCellConfigData(const double resistance,
                                                                 const double maxCapacity)
    :
    mResistance(resistance),
    mMaxCapacity(maxCapacity)
{
    // Nothing to to.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs this GunnsElectBatteryCell config data.
////////////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCellConfigData::~GunnsElectBatteryCellConfigData()
{
    // Nothing to to.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] that (--) Object to copy.
///
/// @details  Copy constructs this GunnsElectBatteryCell config data.
////////////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCellConfigData::GunnsElectBatteryCellConfigData(const GunnsElectBatteryCellConfigData& that)
    :
    mResistance(that.mResistance),
    mMaxCapacity(that.mMaxCapacity)
{
    // Nothing to to.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] malfOpenCircuit (--) Initial failed open-circuit malfunction.
/// @param[in] malfOpenCircuit (--) Initial failed short-circuit malfunction.
/// @param[in] soc             (--) Initial State of Charge (0-1).
///
/// @details  Default constructs this GunnsElectBatteryCell input data.
////////////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCellInputData::GunnsElectBatteryCellInputData(const bool   malfOpenCircuit,
                                                               const bool   malfShortCircuit,
                                                               const double soc)
    :
    mMalfOpenCircuit(malfOpenCircuit),
    mMalfShortCircuit(malfShortCircuit),
    mSoc(soc)
{
    // Nothing to to.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs this GunnsElectBatteryCell input data.
////////////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCellInputData::~GunnsElectBatteryCellInputData()
{
    // Nothing to to.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] that (--) Object to copy.
///
/// @details  Copy constructs this GunnsElectBatteryCell input data.
////////////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCellInputData::GunnsElectBatteryCellInputData(const GunnsElectBatteryCellInputData& that)
    :
    mMalfOpenCircuit(that.mMalfOpenCircuit),
    mMalfShortCircuit(that.mMalfShortCircuit),
    mSoc(that.mSoc)
{
    // Nothing to to.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default constructs this GunnsElectBatteryCell.
////////////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCell::GunnsElectBatteryCell()
    :
    mMalfOpenCircuit(false),
    mMalfShortCircuit(false),
    mResistance(0.0),
    mMaxCapacity(0.0),
    mSoc(0.0)
{
    // Nothing to to.
}

///////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Default destructs this GunnsElectBatteryCell.
///////////////////////////////////////////////////////////////////////////////////////////////
GunnsElectBatteryCell::~GunnsElectBatteryCell()
{
    // Nothing to to.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] configData (--) Reference to cell config data.
/// @param[in] inputData  (--) Reference to cell input data.
/// @param[in] name       (--) Instance name for messages.
///
/// @details  Initializes this GunnsElectBatteryCell with config and input data.
////////////////////////////////////////////////////////////////////////////////////////////////////
void GunnsElectBatteryCell::initialize(const GunnsElectBatteryCellConfigData& configData,
		                               const GunnsElectBatteryCellInputData&  inputData,
		                               const std::string&                     name)
{
    /// - Initialize from configuration and input data.
    mResistance       = configData.mResistance;
    mMaxCapacity      = configData.mMaxCapacity;
    mMalfOpenCircuit  = inputData.mMalfOpenCircuit;
    mMalfShortCircuit = inputData.mMalfShortCircuit;
    mSoc              = inputData.mSoc;
    mName             = name;

    validate();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// @throws   TsInitializationException
///
/// @details  Validates the initial state of this GunnsElectBatteryCell.
////////////////////////////////////////////////////////////////////////////////////////////////////
void GunnsElectBatteryCell::validate()
{
    /// - Issue an error on no instance name.
    if (mName.empty()) {
        GUNNS_ERROR(TsInitializationException, "Invalid Initialization Data",
                    "Instance has no name.");
    }

    /// - Issue an error on internal resistance < 0.
    if (mResistance < 0.0) {
        GUNNS_ERROR(TsInitializationException, "Invalid Configuration Data",
                    "Internal resistance < 0.");
    }

    /// - Issue an error on maximum capacity < DBL_EPSILON.
    if (mMaxCapacity < DBL_EPSILON) {
        GUNNS_ERROR(TsInitializationException, "Invalid Initialization Data",
                    "Maximum charge capacity < DBL_EPSILON.");
    }

    /// - Issue an error on initial SOC not in (0-1).
    if (!Math::isInRange(0.0, mSoc, 1.0)) {
        GUNNS_ERROR(TsInitializationException, "Invalid Initialization Data",
                    "Initial State of Charge not in (0-1).");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] current  (amp) Current through the cell.
/// @param[in] timeStep (s)   Integration time step.
///
/// @details  Update this cell's State of Charge based on the accumulated current though it.  SOC is
///           limited to (0-1).  Positive current discharges, negative current charges.
///           Short-circuit failure discharges the cell internally so its SOC goes to zero.  Open-
///           circuit failure bypasses the cell so it sees no current and SOC remains the same.
////////////////////////////////////////////////////////////////////////////////////////////////////
void GunnsElectBatteryCell::updateSoc(const double current, const double timeStep)
{
    if (mMalfShortCircuit) {
        mSoc = 0.0;
    } else if (!mMalfOpenCircuit) {
        if (mMaxCapacity > DBL_EPSILON) {
            mSoc -= current * timeStep / mMaxCapacity / UnitConversion::SEC_PER_HR;
        } else {
            mSoc = 0.0;
        }
        mSoc = Math::limitRange(0.0, mSoc, 1.0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @returns  double (--) Effective State of Charge of the cell (0-1).
///
/// @details  Returns the effective State of Charge of the cell based on the actual charge and the
///           failure malfunctions.
////////////////////////////////////////////////////////////////////////////////////////////////////
double GunnsElectBatteryCell::getEffectiveSoc() const
{
    if (mMalfOpenCircuit or mMalfShortCircuit) {
        return 0.0;
    } else {
        return mSoc;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @returns  double (ohm) Effective resistance of the cell.
///
/// @details  Computes and returns the effective resistance of the cell based on its nominal
///           internal resistance and failure malfunctions.
////////////////////////////////////////////////////////////////////////////////////////////////////
double GunnsElectBatteryCell::getEffectiveResistance() const
{
    if (mMalfShortCircuit) {
        return DBL_EPSILON;
    } else if (mMalfOpenCircuit) {
        return 1.0 / DBL_EPSILON;
    } else {
        return mResistance;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] socVocTable (--) Pointer to open-circuit voltage vs. State of Charge table.
///
/// @returns  double (v) Effective open-circuit voltage of the cell.
///
/// @details  Returns the effective open-circuit voltage of the cell based on its State of Charge,
///           failure malfunction, and the given open-circuit voltage vs. State of Charge table.
///           Any kind of cell failure results in it contributing zero volts to the battery.
////////////////////////////////////////////////////////////////////////////////////////////////////
double GunnsElectBatteryCell::getEffectiveVoltage(TsLinearInterpolator* socVocTable) const
{
    if (mMalfOpenCircuit or mMalfShortCircuit) {
        return 0.0;
    } else {
        return socVocTable->get(mSoc);
    }
}