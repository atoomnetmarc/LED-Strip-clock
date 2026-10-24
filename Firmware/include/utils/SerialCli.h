/**
 * @file SerialCli.h
 * @brief Interactive command-line parser - push-driven, runtime registration
 *
 * Provides a host-testable command line parser that accepts single bytes
 * via feed(), tokenizes input in-place, and dispatches to registered
 * command handlers. All output goes through a configurable callback,
 * making the module independent of Arduino Serial.
 *
 * Architecture:
 *  - Push-driven input (void feed(char c))
 *  - Output callback seam (std::function)
 *  - Handler signature: void(int argc, char** argv)
 *  - Runtime command registration with auto-generated help
 *  - Zero heap allocation - compile-time buffer and command table
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <functional>
#include <stddef.h>
#include <stdint.h>

namespace cli {

    /**
     * @brief Descriptor for a registered command
     */
    struct CommandDef {
        const char *name; ///< Command name (e.g. "ls", "sd")
        std::function<void(int argc,
                           char **argv)>
            handler;      ///< Handler - capturing lambda for module self-registration
        const char *help; ///< One-line help text
    };

    /**
     * @brief Callback type for output produced by the parser and handlers
     *
     * Receives a pointer to data and the data length in bytes.
     * Callers can bind this to Serial.write, a PSRAM buffer, or a test
     * string capture.
     */
    using OutputCallback = std::function<void(const char *data, size_t len)>;

    /**
     * @brief Command-line parser accepting single bytes
     *
     * Usage in loop():
     * @code
     *   while (Serial.available()) { cli.feed(Serial.read()); }
     * @endcode
     */
    class SerialCli {
    public:
        static constexpr size_t MAX_COMMANDS = 48;
        static constexpr size_t INPUT_BUFFER_SIZE = 256;

        /**
         * @brief Construct the parser with an output callback
         * @param onOutput Called for every byte of response output
         */
        explicit SerialCli(OutputCallback onOutput);

        /**
         * @brief Register a command handler
         * @param cmd Command descriptor (copied by value)
         * @return true on success, false if table full or duplicate name
         */
        bool registerCommand(const CommandDef &cmd);

        /**
         * @brief Feed a single character into the parser
         *
         * On '\n' (or '\r' alone), dispatches the buffered line.
         * Backspace (0x7F or '\b') removes the last character.
         * Echoes printable characters back through the output callback.
         *
         * @param c Single input character
         */
        void feed(char c);

    private:
        OutputCallback onOutput;
        CommandDef commands[MAX_COMMANDS];
        size_t commandCount = 0;
        char buffer[INPUT_BUFFER_SIZE];
        size_t pos = 0;

        /// Dispatch a complete command line
        void dispatch(const char *line);

        /// Built-in help command - lists all registered commands
        void cmdHelp(int argc, char **argv);
    };

} // namespace cli
