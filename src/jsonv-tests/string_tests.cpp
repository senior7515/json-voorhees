/** \file
 *  
 *  Copyright (c) 2012 by Travis Gockel. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the Apache License
 *  as published by the Apache Software Foundation, either version 2 of the License, or (at your option) any later
 *  version.
 *
 *  \author Travis Gockel (travis@gockelhut.com)
**/
#include <jsonv/value.hpp>
#include <jsonv/parse.hpp>

#include "test.hpp"

TEST(parse_empty_string)
{
    jsonv::value val = jsonv::parse("\"\"");
    const std::string& str = val.as_string();
    ensure(str == "");
}

TEST(parse_single_backslash)
{
    jsonv::value val = jsonv::parse("\"\\\\\""); // "\\"
    const std::string& str = val.as_string();
    ensure(str == "\\");
    ensure_eq(1, val.size());
}

TEST(parse_bogus_string_throws)
{
    // Specify a Unicode escape that isn't long enough and doesn't use hex.
    ensure_throws(jsonv::parse_error, jsonv::parse("\"\\uTT\""));
}

TEST(parse_strict_string_unprintables)
{
    auto options = jsonv::parse_options::create_strict();
    ensure_throws(jsonv::parse_error, jsonv::parse("\"\t\"",   options));
    ensure_throws(jsonv::parse_error, jsonv::parse("\"\b\"",   options));
    ensure_throws(jsonv::parse_error, jsonv::parse("\"\f\"",   options));
    ensure_throws(jsonv::parse_error, jsonv::parse("\"\n\"",   options));
    ensure_throws(jsonv::parse_error, jsonv::parse("\"\r\"",   options));
    ensure_throws(jsonv::parse_error, jsonv::parse("\"\x01\"", options));
}
