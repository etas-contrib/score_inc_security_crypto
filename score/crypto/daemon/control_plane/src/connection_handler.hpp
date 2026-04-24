// =============================================================================
//  C O P Y R I G H T
// -----------------------------------------------------------------------------
//  Copyright (c) 2025-2026 by ETAS GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
// =============================================================================

#ifndef CONTROL_HANDLER_IMPL_H
#define CONTROL_HANDLER_IMPL_H

#include <memory>

#include "score/crypto/daemon/common/types.hpp"
#include "score/crypto/daemon/config/inc/config.hpp"
#include "score/crypto/daemon/control_plane/i_request_handler.hpp"
#include "score/crypto/daemon/data_manager/i_data_manager.hpp"

namespace score::crypto::daemon::control_plane
{

class ConnectionHandler : public IRequestHandler
{
  public:
    ConnectionHandler(std::unique_ptr<IRequestHandler> next_request_handler,
                      std::shared_ptr<data_manager::IDataManager> data_manager,
                      const config::Config& config);

    ~ConnectionHandler() override = default;

    // Move semantics - handler is move-only due to unique_ptr member
    ConnectionHandler(ConnectionHandler&&) = default;
    ConnectionHandler& operator=(ConnectionHandler&&) = default;

    // Delete copy semantics
    ConnectionHandler(const ConnectionHandler&) = delete;
    ConnectionHandler& operator=(const ConnectionHandler&) = delete;

    ControlResponse processRequest(const ControlRequest& request) override;

  private:
    std::unique_ptr<IRequestHandler> m_next_request_handler;
    std::shared_ptr<data_manager::IDataManager> m_data_manager;

    bool ProcessSingleRequest(const ControlRequest& request,
                              const common::OperationIdentifier& opId,
                              control_plane::protocol::OperationResponseBuilder& responseBuilder);

    bool ProcessConnectionCreation(const ControlRequest& request,
                                   const common::OperationIdentifier& opId,
                                   control_plane::protocol::OperationResponseBuilder& responseBuilder);
    bool ProcessConnectionClosure(const ControlRequest& request,
                                  const common::OperationIdentifier& opId,
                                  control_plane::protocol::OperationResponseBuilder& responseBuilder);
    bool ProcessUnknownRequest(const ControlRequest& request,
                               const common::OperationIdentifier& opId,
                               control_plane::protocol::OperationResponseBuilder& responseBuilder);
};

}  // namespace score::crypto::daemon::control_plane

#endif  // CONTROL_HANDLER_IMPL_H
