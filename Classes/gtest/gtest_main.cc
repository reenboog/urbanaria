// Copyright 2006, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <stdio.h>

#include "gtest.h"

#include "NumericPair.h"

TEST(string_cmpr, str_0) {
    EXPECT_STRCASEEQ("ss", "Ss");
}

TEST(NumericPair_evaluation, empty_construction) {
    NumericPair a;
    
    EXPECT_EQ(0, a.getHigher());
    EXPECT_EQ(0, a.getLower());
}

TEST(NumericPair_evaluation, normal_construction) {
    NumericPair a(1, 2);
    
    EXPECT_EQ(2, a.getHigher());
    EXPECT_EQ(1, a.getLower());
}

TEST(NumericPair_evaluation, setters) {
    NumericPair a(0, 2);
    
    a.setHigher(3);
    a.setLower(2);
    
    EXPECT_EQ(3, a.getHigher());
    EXPECT_EQ(2, a.getLower());
}

TEST(NumericPair_evaluation, applying) {
    NumericPair a(0, 10);
    
    a.apply(10);
    
    EXPECT_EQ(11, a.getHigher());
    EXPECT_EQ(0, a.getLower());
}


TEST(NumericPair_evaluation, applyying_overflow) {
    NumericPair a(3, 5);
    
    a.apply(5);
    
    EXPECT_EQ(2, a.getHigher());
    EXPECT_EQ(0, a.getLower());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}