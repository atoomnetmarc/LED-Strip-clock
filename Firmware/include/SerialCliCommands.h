/**
 * @file SerialCliCommands.h
 * @brief Registration of project-specific serial CLI commands
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "utils/SerialCli.h"

namespace cli {
    // Register all LED strip clock commands on the given CLI instance.
    void registerCommands(SerialCli &cli);

    // Input event debug output toggle (controlled by the 'inputdebug' command).
    void setInputDebugEnabled(bool enabled);
    bool inputDebugEnabled();
}
