// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#include "score/crypto/daemon/key_management/interfaces/i_key_slot_handler.hpp"

#include "score/crypto/daemon/common/daemon_error.hpp"

namespace score::crypto::daemon::key_management
{

score::crypto::Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode> IKeySlotHandler::StoreKey(
    const KeySlotConfig& /*slot*/,
    IKeyHandler& /*handler*/)
{
    return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kUnsupportedOperation);
}

score::crypto::Expected<std::monostate, score::crypto::daemon::common::DaemonErrorCode> IKeySlotHandler::ClearSlot(
    const KeySlotConfig& /*slot*/)
{
    return score::crypto::make_unexpected(score::crypto::daemon::common::DaemonErrorCode::kUnsupportedOperation);
}

}  // namespace score::crypto::daemon::key_management
