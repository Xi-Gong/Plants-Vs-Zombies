/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>

#include "../Classes/Based/AppDelegate.h"
#include "Based/Runtime.h"

USING_NS_CC;

// compatible with fast math lib
extern "C" {
double __exp_finite(double x) { return exp(x); }
double __log_finite(double x) { return log(x); }
double __pow_finite(double x, double y) { return pow(x, y); }

float __expf_finite(float x) { return expf(x); }
float __logf_finite(float x) { return logf(x); }
float __powf_finite(float x, float y) { return powf(x, y); }
}

int main(int argc, char** argv) {
    // create application runtime database
    Runtime runtime;

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
