/** \file
 *  
 *  Copyright (c) 2014 by Travis Gockel. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it under the terms of the Apache License
 *  as published by the Apache Software Foundation, either version 2 of the License, or (at your option) any later
 *  version.
 *
 *  \author Travis Gockel (travis@gockelhut.com)
**/
#include "test.hpp"

#include <jsonv/encode.hpp>
#include <jsonv/parse.hpp>
#include <jsonv/value.hpp>

#include <cmath>
#include <iostream>
#include <locale>
#include <sstream>

namespace jsonv_test
{

static const char k_some_json[] = R"({
  "a": [ 4, 5, 6, [7, 8, 9, {"something": 5, "else": 6}]],
  "b": "blah",
  "c": { "baz": ["bazar"], "cat": ["Eric", "Bob"] },
  "d": {},
  "e": [],
  "f": null,
  "g": [ true, false ]
})";

TEST(encode_pretty_print)
{
    auto val = jsonv::parse(k_some_json);
    jsonv::ostream_pretty_encoder encoder(std::cout);
    encoder.encode(val);
}

TEST(encode_nan)
{
    auto val = jsonv::parse(k_some_json);
    val.at_path(".a[2]") = std::nan("");
    std::ostringstream ss;
    ss << val;
    
    std::string str = ss.str();
    auto decoded = jsonv::parse(str);
    ensure_ne(val, decoded);
    
    // change val to have null in place of the NaN
    val.at_path(".a[2]") = nullptr;
    ensure_eq(val, decoded);
}

}
