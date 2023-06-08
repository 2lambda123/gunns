#ifndef GunnsOptimBase_EXISTS
#define GunnsOptimBase_EXISTS

/**
@file     GunnsOptimBase.hh
@brief    GUNNS Optimization Optimizer Base Class declarations

@defgroup  TSM_GUNNS_CORE_OPTIM_BASE    GUNNS Optimization Optimizer Base Class
@ingroup   TSM_GUNNS_CORE

@copyright Copyright 2023 United States Government as represented by the Administrator of the
           National Aeronautics and Space Administration.  All Rights Reserved.

@details
PURPOSE:
- (Refer to class details below.)

REFERENCE:
- (TBD)

ASSUMPTIONS AND LIMITATIONS:
- (TBD)

LIBRARY_DEPENDENCY:
- ((GunnsOptimBase.o))

PROGRAMMERS:
- ((Jason Harvey) (CACI) (2023-05) (Initial))

@{
*/

#include "GunnsOptimMonteCarloTypes.hh"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    GUNNS Monte Carlo Optimizer Base Configuration Data
///
/// @details  This provides a base class for derived GUNNS Monte Carlo Optimizer configuration data
///           classes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsOptimBaseConfigData
{
    public:
        /// @brief Constructs the GUNNS Monte Carlo Optimizer Base Config Data object.
        GunnsOptimBaseConfigData();
        /// @brief Destructs the GUNNS Monte Carlo Optimizer Base Config Data object.
        virtual ~GunnsOptimBaseConfigData();

    private:
        /// @brief Copy constructor unavailable since declared private and not implemented.
        GunnsOptimBaseConfigData(const GunnsOptimBaseConfigData&);
        /// @brief Assignment operator unavailable since declared private and not implemented.
        GunnsOptimBaseConfigData& operator =(const GunnsOptimBaseConfigData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    GUNNS Monte Carlo Optimizer Base Class
///
/// @details  This is the base class for GUNNS Monte Carlo Optimizer classes to inherit.  This
///           provides a generic interface with the GUNNS Monte Carlo Manager.  This also implements
///           a few math functions that derived optimizers might find useful.
///
/// @note     This is a pure-virtual class and cannot be instantiated directly.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsOptimBase
{
    public:
        /// @brief Constructs the GUNNS Monte Carlo Optimizer Base object.
        GunnsOptimBase();
        /// @brief Destructs the GUNNS Monte Carlo Optimizer Base object.
        virtual ~GunnsOptimBase();
        /// @brief Sets the amount of detail output to the console.
        void setVerbosityLevel(const unsigned int level);

        /// @name    Pure-virtual functions.
        /// @{
        /// @details These are the pure-virtual functions that must be implemented by a derived
        ///          class.
        /// @brief Gives the configuration data to the optimizer.
        virtual void setConfigData(const GunnsOptimBaseConfigData* configData) = 0;
        /// @brief Initializes the optimizer with the given Monte Carlo input variables.
        virtual void initialize(const std::vector<GunnsOptimMonteCarloInput>* inStatesMaster) = 0;
        /// @brief Main update function for the optimizer.
        virtual void update() = 0;
        /// @brief Returns the total number of Monte Carlo Slave runs that the optimizer expects.
        virtual unsigned int getNumRuns() const = 0;
        /// @brief Returns the Monte Carlo input variables state for the next Slave run.
        virtual const std::vector<double>* getState() const = 0;
        /// @brief Assigns the given cost to the optimizer state for the given Slave run.
        virtual void assignCost(const double cost, double runID, double runIdReturned) = 0;
        /// @brief Shuts down the optimizer.
        virtual void shutdown() const = 0;
        /// @}

    protected:
        std::string                                   mName;             /**< *o (1) trick_chkpnt_io(**) Object name for error messages. */
        const std::vector<GunnsOptimMonteCarloInput>* mInStatesMaster;   /**< ** (1) trick_chkpnt_io(**) Pointer to the Master state space description. */
        int                                           mGlobalRunCounter; /**< *o (1) trick_chkpnt_io(**) Count of the total elapsed runs from all epochs. */
        int                                           mRunCounter;       /**< *o (1) trick_chkpnt_io(**) Count of the elapsed runs in the current epoch. */
        int                                           mEpoch;            /**< *o (1) trick_chkpnt_io(**) The current epoch number. */
        unsigned int                                  mVerbosityLevel;   /**< *o (1) trick_chkpnt_io(**) The amount of output to the console, higher values output more detail. */
        /// @brief Validates the monte carlo variables description.
        virtual void validate();
        /// @brief Returns a uniform distribution random number in the range [0, 1].
        double uniformRand() const;
        /// @brief Returns the RSS magnitude of the given vector's components.
        double computeVectorMagnitude(const std::vector<double>& vec) const;
        /// @brief Normalizes the given vector to the given magnitude.
        void normalizeVector(std::vector<double>& vec, const double magnitude = 1.0) const;

    private:
        /// @brief Copy constructor unavailable since declared private and not implemented.
        GunnsOptimBase(const GunnsOptimBase&);
        /// @brief Assignment operator unavailable since declared private and not implemented.
        GunnsOptimBase& operator =(const GunnsOptimBase&);
};

/// @}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] level (--) The amount of verbage to output to the console, higher values give more output.
///
/// @details  Sets mVerbosityLevel to the given value.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GunnsOptimBase::setVerbosityLevel(const unsigned int level)
{
    mVerbosityLevel = level;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @returns  double (--) Uniform distribution random number in the range [0, 1].
///
/// @details  Returns a uniformly-distributed random number between 0 and 1 inclusive.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline double GunnsOptimBase::uniformRand() const
{
    return (1.0 * std::rand() / RAND_MAX);
}

#endif