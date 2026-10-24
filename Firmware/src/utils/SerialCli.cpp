/**
 * @file SerialCli.cpp
 * @brief Serial CLI implementation - buffer management, tokenization, dispatch
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include "utils/SerialCli.h"

#include <cstdio>
#include <cstring>

namespace cli {

    // Construction

    SerialCli::SerialCli(OutputCallback onOutput)
        : onOutput(std::move(onOutput)), commandCount(0), pos(0) {
        buffer[0] = '\0';
    }

    // Command Registration

    bool SerialCli::registerCommand(const CommandDef &cmd) {
        if (commandCount >= MAX_COMMANDS) {
            return false;
        }
        if (cmd.name == nullptr || !cmd.handler) {
            return false;
        }

        // Check for duplicate names - overwrite existing registration
        for (size_t i = 0; i < commandCount; ++i) {
            if (strcmp(commands[i].name, cmd.name) == 0) {
                commands[i] = cmd;
                return true;
            }
        }

        commands[commandCount++] = cmd;
        return true;
    }

    // Input Feeding

    void SerialCli::feed(char c) {
        // Handle backspace (DEL or BS)
        if (c == 0x7F || c == '\b') {
            if (pos > 0) {
                pos--;
                // Echo backspace sequence
                onOutput("\b \b", 3);
            }
            return;
        }

        // Handle line termination
        if (c == '\n' || c == '\r') {
            // '\r' standalone or '\r\n' - only dispatch once
            // State: if we just processed '\r' and see '\n', skip it
            // We handle this by dispatching on first terminator and
            // ignoring the second if buffer is already empty.

            if (pos > 0) {
                buffer[pos] = '\0';
                pos = 0;
                onOutput("\r\n", 2);
                dispatch(buffer);
            }
            return;
        }

        // Echo and buffer printable characters
        if (pos < INPUT_BUFFER_SIZE - 1) {
            buffer[pos++] = c;
            onOutput(&c, 1);
        }
        // If buffer full, silently drop - prevents overflow
    }

    // Dispatch

    void SerialCli::dispatch(const char *line) {
        // Skip leading whitespace
        while (*line == ' ') {
            line++;
        }

        if (*line == '\0') {
            return;
        }

        // Tokenize in-place: replace spaces with '\0', build argv
        constexpr size_t MAX_ARGS = 16;
        char *argv[MAX_ARGS];
        int argc = 0;

        // Make a mutable copy for tokenization
        char tokenBuffer[INPUT_BUFFER_SIZE];
        strncpy(tokenBuffer, line, INPUT_BUFFER_SIZE - 1);
        tokenBuffer[INPUT_BUFFER_SIZE - 1] = '\0';

        char *p = tokenBuffer;
        while (*p != '\0' && argc < static_cast<int>(MAX_ARGS)) {
            // Skip spaces between tokens
            while (*p == ' ') {
                p++;
            }
            if (*p == '\0') {
                break;
            }

            argv[argc++] = p;

            // Find end of this token
            while (*p != '\0' && *p != ' ') {
                p++;
            }

            // Terminate token if not at end
            if (*p == ' ') {
                *p = '\0';
                p++;
            }
        }

        if (argc == 0) {
            return;
        }

        // Built-in "help" command
        if (strcmp(argv[0], "help") == 0) {
            cmdHelp(argc, argv);
            return;
        }

        // Search registered commands
        for (size_t i = 0; i < commandCount; ++i) {
            if (strcmp(commands[i].name, argv[0]) == 0) {
                commands[i].handler(argc, argv);
                return;
            }
        }

        // Unknown command
        char errMsg[64];
        int errLen = snprintf(errMsg, sizeof(errMsg),
                              "Unknown command: '%s'. Try 'help'.\r\n",
                              argv[0]);
        onOutput(errMsg, static_cast<size_t>(errLen));
    }

    // Help Command

    void SerialCli::cmdHelp(int argc, char **argv) {
        (void)argc;
        (void)argv;

        onOutput("=== ClockAll - Serial Commands ===\r\n", 37);

        for (size_t i = 0; i < commandCount; ++i) {
            // Format: "  name              help text\r\n"
            char line[INPUT_BUFFER_SIZE];
            int len = snprintf(line, sizeof(line),
                               "  %-18s %s\r\n",
                               commands[i].name,
                               commands[i].help ? commands[i].help : "");
            if (len > 0) {
                onOutput(line, static_cast<size_t>(len));
            }
        }
    }

} // namespace cli
