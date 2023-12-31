#ifndef GunnsDistributed2WayBusBase_EXISTS
#define GunnsDistributed2WayBusBase_EXISTS

/**
@file     GunnsDistributed2WayBusBase.hh
@brief    GUNNS Distributed 2-Way Bus Base Interface declarations

@defgroup  TSM_GUNNS_CORE_LINK_DISTR_2WAY_BUS_BASE    GUNNS Distributed 2-Way Bus Base Interface
@ingroup   TSM_GUNNS_CORE_LINK

@copyright Copyright 2023 United States Government as represented by the Administrator of the
           National Aeronautics and Space Administration.  All Rights Reserved.

@details
PURPOSE:
- (Classes for the GUNNS Distributed 2-Way Bus Base Interface.)

REFERENCE:
- ()

ASSUMPTIONS AND LIMITATIONS:
- ()

LIBRARY DEPENDENCY:
- ((GunnsDistributed2WayBusBase.o))

PROGRAMMERS:
- ((Jason Harvey) (CACI) (2023-05) (Initial))

@{
*/

#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    Distributed 2-Way Bus Base Interface Data
///
/// @details  This holds the data that is transferred between instances of
///           GunnsDistributed2WayBusBase across the sim-sim interface (HLA, etc.)
///
/// @note     This must remain a base class, since it can be used in multiple inheritance elsewhere
///           in the GUNNS baseline, to avoid the diamond inheritance problem.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsDistributed2WayBusBaseInterfaceData // !!! NOTE this must remain a base class, see above !!!
{
    public:
        unsigned int mFrameCount;    /**< (1) Frame count driven by this side. */
        unsigned int mFrameLoopback; /**< (1) Frame count driven by other side, echoed back. */
        bool         mDemandMode;    /**< (1) Demand mode flag. */
        /// @brief  Default constructs this Distributed 2-Way Bus Base interface data.
        GunnsDistributed2WayBusBaseInterfaceData();
        /// @brief  Default destructs this Distributed 2-Way Bus Base interface data.
        virtual ~GunnsDistributed2WayBusBaseInterfaceData();
        /// @brief  Returns whether this object has received valid data.
        virtual bool hasValidData() const = 0;
        /// @brief Assignment operator for this Distributed 2-Way Bus Base interface data.
        GunnsDistributed2WayBusBaseInterfaceData& operator =(const GunnsDistributed2WayBusBaseInterfaceData& that);

    private:
        /// @brief Copy constructor unavailable since declared private and not implemented.
        GunnsDistributed2WayBusBaseInterfaceData(const GunnsDistributed2WayBusBaseInterfaceData&);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    Distributed 2-Way Bus Base notification message.
///
/// @details  This describes a notification message from the GunnsDistributed2WayBusBase to the
///           outside, including severity level and message string.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsDistributed2WayBusNotification
{
    public:
        /// @brief Enumeration of notification severity levels.
        typedef enum {
            INFO = 0, ///< Information.
            WARN = 1, ///< Warning.
            ERR  = 2, ///< Error.
            NONE = 3  ///< No notification, empty queue.
        } NotificationLevel;
        NotificationLevel mLevel;   /**< (1) The severity level of the notification. */
        std::string       mMessage; /**< (1) the notification message. */
        /// @brief Default constructor.
        GunnsDistributed2WayBusNotification(const NotificationLevel level = NONE, const std::string& message = "");
        /// @brief Default destructor.
        virtual ~GunnsDistributed2WayBusNotification();
        /// @brief Copy constructor.
        GunnsDistributed2WayBusNotification(const GunnsDistributed2WayBusNotification& that);
        /// @brief Assignment operator.
        GunnsDistributed2WayBusNotification& operator =(const GunnsDistributed2WayBusNotification& that);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief    Distributed 2-Way Bus Base Interface.
///
/// @details  This is the base class for 2-way bus distributed interface logic models.
////////////////////////////////////////////////////////////////////////////////////////////////////
class GunnsDistributed2WayBusBase
{
    public:
        /// @brief Enumeration of interface roles. */
        typedef enum {
            NONE   = 0, ///< No role.
            SUPPLY = 1, ///< Supply role.
            DEMAND = 2  ///< Demand role.
        } Roles;
        /// @brief Default Constructor.
        GunnsDistributed2WayBusBase(GunnsDistributed2WayBusBaseInterfaceData* inDataPtr,
                                    GunnsDistributed2WayBusBaseInterfaceData* outDataPtr);
        /// @brief Default Destructor.
        virtual ~GunnsDistributed2WayBusBase();
        /// @brief Initializes this Distributed 2-Way Bus Interface.
        void initialize(const bool isPairMaster);
        /// @brief Forces this interface to remain in Demand role.
        void forceDemandRole();
        /// @brief Forces this interface to remain in Supply role.
        void forceSupplyRole();
        /// @brief Resets the forced role and lets the interface logic determine role normally.
        void resetForceRole();
        /// @brief Returns whether this Distributed 2-Way Bus Interface is in the Demand role.
        bool isInDemandRole() const;
        /// @brief Pops a notification message off of the queue and returns the remaining queue size.
        unsigned int popNotification(GunnsDistributed2WayBusNotification& notification);

    protected:
        bool                                             mIsPairMaster;         /**<    (1) trick_chkpnt_io(**) This is the master side of the interface. */
        bool                                             mInDataLastDemandMode; /**<    (1)                     Last-pass demand mode from the other paired link. */
        int                                              mFramesSinceFlip;      /**<    (1)                     Number of frames since the last mode flip. */
        int                                              mLoopLatency;          /**<    (1)                     Round-trip loop data lag measurement. */
        Roles                                            mForcedRole;           /**<    (1)                     The role this interface is forced to be in, if any. */
        std::vector<GunnsDistributed2WayBusNotification> mNotifications;        /**< ** (1) trick_chkpnt_io(**) Notifications queue. */
        /// @brief Updates frame counters and the loop latency measurement.
        void updateFrameCounts();
        /// @brief Adds a notification message to the queue.
        void pushNotification(const GunnsDistributed2WayBusNotification::NotificationLevel level,
                              const std::string&                                           message);

    private:
        GunnsDistributed2WayBusBaseInterfaceData*        mInDataPtr;            /**<    (1) trick_chkpnt_io(**) Pointer to the derived class incoming data instance. */
        GunnsDistributed2WayBusBaseInterfaceData*        mOutDataPtr;           /**<    (1) trick_chkpnt_io(**) Pointer to the derived class outgoing data instance. */
        /// @brief Copy constructor unavailable since declared private and not implemented.
        GunnsDistributed2WayBusBase(const GunnsDistributed2WayBusBase& that);
        /// @brief Assignment operator unavailable since declared private and not implemented.
        GunnsDistributed2WayBusBase& operator =(const GunnsDistributed2WayBusBase& that);
};

/// @}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Sets the mForcedRole attribute to DEMAND.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GunnsDistributed2WayBusBase::forceDemandRole()
{
    mForcedRole = DEMAND;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Sets the mForcedRole attribute to SUPPLY.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GunnsDistributed2WayBusBase::forceSupplyRole()
{
    mForcedRole = SUPPLY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @details  Sets the mForcedRole attribute to NONE.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GunnsDistributed2WayBusBase::resetForceRole()
{
    mForcedRole = NONE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @returns  bool (1) True if this is currently in the Demand role.
///
/// @details  Returns the value of mDemandMode from the derived class outgoing data instance.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool GunnsDistributed2WayBusBase::isInDemandRole() const
{
    return mOutDataPtr->mDemandMode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @param[in] level   (--) Severity level of the message.
/// @param[in] message (--) Detailed message string.
///
/// @details  Adds a new notification message object to the message queue.
////////////////////////////////////////////////////////////////////////////////////////////////////
inline void GunnsDistributed2WayBusBase::pushNotification(
        const GunnsDistributed2WayBusNotification::NotificationLevel level,
        const std::string&                                           message)
{
    mNotifications.push_back(GunnsDistributed2WayBusNotification(level, message));
}

#endif
