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
#pragma once

#include "score/mw/com/types.h"
#include "tests/score_com_poc/ipc_buffer.h"

namespace score::crypto::ipc::control
{

/// S-CORE com service interface for the crypto daemon control plane.
/// A single Method transports serialized FlatBuffer bytes in both directions.
///
/// The template parameter selects either ProxyTrait (client) or SkeletonTrait
/// (server), following the ara::com Skeleton/Proxy pattern.
template <typename Trait>
class ControlPlaneInterface : public Trait::Base
{
  public:
    using Trait::Base::Base;

    // Single RPC method: request (IpcBuffer) → response (IpcBuffer).
    // The IpcBuffer carries a FlatBuffer-serialized ControlRequest / ControlResponse.
    typename Trait::template Method<IpcBuffer(IpcBuffer)> execute{
        *this, "Execute"};
};

using ControlPlaneProxy   = score::mw::com::AsProxy<ControlPlaneInterface>;
using ControlPlaneSkeleton = score::mw::com::AsSkeleton<ControlPlaneInterface>;

}  // namespace score::crypto::ipc::control
