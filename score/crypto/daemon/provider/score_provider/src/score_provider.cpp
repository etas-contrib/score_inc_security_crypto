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

#include "score/crypto/daemon/provider/score_provider/score_provider.hpp"

#include "score/mw/log/logging.h"

namespace score::crypto::daemon::provider::score_provider
{

bool ScoreProvider::Initialize(const ProviderInitContext& ctx)
{
    if (m_initialized)
    {
        return true;
    }

    m_numeric_id = ctx.numeric_id;
    m_provider_name = ctx.name;
    m_initialized = true;

    score::mw::log::LogDebug() << "[ScoreProvider] Initialized (ID:" << m_numeric_id << ", Name:" << m_provider_name
                               << ")";
    return true;
}

void ScoreProvider::Shutdown()
{
    if (!m_initialized)
    {
        return;
    }
    m_handler_factory.reset();
    m_initialized = false;
}

common::ProviderId ScoreProvider::GetProviderId() const
{
    return m_numeric_id;
}

const common::ProviderName& ScoreProvider::GetProviderName() const
{
    return m_provider_name;
}

std::shared_ptr<handler::ICryptoHandlerFactory> ScoreProvider::GetCryptoHandlerFactory()
{
    if (!m_handler_factory)
    {
        m_handler_factory = CreateHandlerFactory();
    }
    return m_handler_factory;
}

}  // namespace score::crypto::daemon::provider::score_provider
