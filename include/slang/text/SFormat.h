//------------------------------------------------------------------------------
//! @file SFormat.h
//! @brief SystemVerilog string formatting routines
//
// File is under the MIT license; see LICENSE for details
//------------------------------------------------------------------------------
#pragma once

#include "slang/diagnostics/Diagnostics.h"
#include "slang/text/SourceLocation.h"
#include "slang/util/Function.h"
#include "slang/util/Util.h"

namespace slang {

namespace SFormat {

/// A collection of options that can be applied to the SFormat string formatting functions.
struct FormatOptions {
    /// The width of a numeric field. If left empty a default will be used.
    optional<uint32_t> width;

    /// An optional precision to apply when formatting floating point values.
    optional<uint32_t> precision;

    /// Set to true to left justify instead of right justify the field within
    /// its specified width.
    bool leftJustify = false;

    /// Set to true to zero pad instead of space pad the field within its
    /// specified width.
    bool zeroPad = false;
};

/// Parse the given formatString and call the provided callbacks for each parsed portion.
/// The formatString is specified by the SystemVerilog LRM -- see that for a complete reference.
///
/// @param onText will be invoked for each constant / non-formatted portion of the format string.
/// @param onArg will be invoked for each format specifier in the format string, with various
///              options parsed and provided as arguments.
/// @param onError will be invoked for any errors in the format string, with a diagnostic code
///                describing the problem and the location in the string where the error occurred.
/// @return true if parsing was successful, and false if an error occurred.
bool parse(
    string_view formatString, function_ref<void(string_view text)> onText,
    function_ref<void(char specifier, size_t offset, size_t len, const FormatOptions& options)>
        onArg,
    function_ref<void(DiagCode code, size_t offset, size_t len, optional<char> specifier)> onError);

/// Format the given @a value into a string and append it to @a result according
/// to the provided @a options
void formatInt(std::string& result, const SVInt& value, LiteralBase base,
               const FormatOptions& options);

/// Format the given @a arg into a string and append it to @a result according
/// to the provided @a options
void formatArg(std::string& result, const ConstantValue& arg, char specifier,
               const FormatOptions& options);

} // namespace SFormat

} // namespace slang