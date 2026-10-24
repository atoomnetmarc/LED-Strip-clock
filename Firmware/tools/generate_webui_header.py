#!/usr/bin/env python3
"""
generate_webui_header.py - PlatformIO extra_script

Reads webui/index.html, injects cache-busting timestamps, gzips, and
writes a C++ header with a PROGMEM byte array to include/WebContent.h.

PlatformIO integration:
    extra_scripts = tools/generate_webui_header.py

Manual run:
    python3 tools/generate_webui_header.py
"""

import gzip
import os
import time
from pathlib import Path


def _project_root():
    return Path(os.environ.get("PROJECT_DIR", os.getcwd()))


def _cache_bust_token():
    """Unix timestamp string for cache-busting."""
    return str(int(time.time()))


def _c_array(lines, name, blob):
    """Append a PROGMEM byte-array definition for blob to lines."""
    lines.append(f"static const uint32_t {name}_LEN = {len(blob)};")
    lines.append("")
    lines.append(f"static const uint8_t {name}[] PROGMEM = {{")
    if not blob:
        # A zero-size array is ill-formed in C++; keep one filler byte
        # (LEN stays 0 so the route never serves it as content).
        lines.append("    0x00,")
    for i in range(0, len(blob), 16):
        chunk = ", ".join(f"0x{b:02x}" for b in blob[i : i + 16])
        lines.append(f"    {chunk},")
    lines.append("};")
    lines.append("")


def generate():
    """Generate WebContent.h from webui/index.html."""
    project_root = _project_root()
    src_path = project_root / "webui" / "index.html"
    output_file = project_root / "include" / "WebContent.h"

    cache_bust = _cache_bust_token()
    html = src_path.read_text(encoding="utf-8")
    html = html.replace("{{CACHE_BUST}}", cache_bust)

    gzipped = gzip.compress(html.encode("utf-8"))

    lines = [
        "/**",
        " * @file WebContent.h",
        " * @brief Generated gzipped web UI - DO NOT EDIT",
        " *",
        " * Generated from webui/index.html by tools/generate_webui_header.py",
        f" * Cache-bust token: {cache_bust}",
        " *",
        " * @copyright Marc Ketel",
        " * SPDX-License-Identifier: Apache-2.0",
        " */",
        "",
        "#pragma once",
        "",
        "#include <pgmspace.h>",
        "",
    ]

    _c_array(lines, "WEBUI_HTML_GZ", gzipped)

    output_file.write_text("\n".join(lines), encoding="utf-8")
    print(f"WebContent.h generated ({len(gzipped)} bytes gzipped html)")


# Generate during SCons configuration, before compilation needs the header.
# This also supports running the script directly.
generate()
