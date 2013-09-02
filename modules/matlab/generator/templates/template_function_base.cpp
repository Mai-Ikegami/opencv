{% import 'functional.cpp' as functional %}
/*
 * file:   {{fun.name}}.cpp
 * author: A trusty code generator
 * date:   {{time.strftime("%a, %d %b %Y %H:%M:%S", time.localtime())}}
 * 
 * This file was autogenerated, do not modify.
 * See LICENSE for full modification and redistribution details.
 * Copyright {{time.strftime("%Y", time.localtime())}} The OpenCV Foundation
 */
#include <string>
#include <vector>
#include <cassert>
#include <exception>
#include <opencv2/matlab/bridge.hpp>
#include <opencv2/{{includes}}.hpp>
using namespace cv;
using namespace matlab;
using namespace bridge;

/* 
 * {{ fun.name }}
 * {{ fun }}
 * Gateway routine
 *   nlhs - number of return arguments
 *   plhs - pointers to return arguments
 *   nrhs - number of input arguments
 *   prhs - pointers to input arguments
 */
void mexFunction(int nlhs, mxArray*{% if fun|noutputs %} plhs[]{% else %}*{% endif %},
                 int nrhs, const mxArray*{% if fun|ninputs %} prhs[]{% else %}*{% endif %}) {

  {% if fun|ninputs %}
  // parse the inputs
  ArgumentParser parser("{{fun.name}}");
  parser.{{ functional.composeVariant(fun) }};
  MxArrayVector sorted = parser.parse(MxArrayVector(prhs, prhs+nrhs));
  {% endif %}

  {% if fun|ninputs or fun|noutputs %}
  // setup
  {% if fun|ninputs %}
  BridgeVector inputs(sorted.begin(), sorted.end());
  {% endif -%}
  {%- if fun|noutputs %}
  BridgeVector outputs({{fun|noutputs}});
  {% endif %}
  {% endif %}

  {{ functional.handleInputs(fun) }}
  {{ functional.composeWithExceptionHandler(fun) }}
  {{ functional.handleOutputs(fun) }}

  {% if fun|noutputs %}
  // push the outputs back to matlab
  for (size_t n = 0; n < static_cast<size_t>(std::max(nlhs,1)); ++n) {
    plhs[n] = outputs[n].toMxArray().releaseOwnership();
  }
  {% endif %}
}

