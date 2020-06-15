/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrBlurredEdgeFragmentProcessor.fp; do not modify.
 **************************************************************************************************/
#include "GrBlurredEdgeFragmentProcessor.h"

#include "src/gpu/GrTexture.h"
#include "src/gpu/glsl/GrGLSLFragmentProcessor.h"
#include "src/gpu/glsl/GrGLSLFragmentShaderBuilder.h"
#include "src/gpu/glsl/GrGLSLProgramBuilder.h"
#include "src/sksl/SkSLCPP.h"
#include "src/sksl/SkSLUtil.h"
class GrGLSLBlurredEdgeFragmentProcessor : public GrGLSLFragmentProcessor {
public:
    GrGLSLBlurredEdgeFragmentProcessor() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrBlurredEdgeFragmentProcessor& _outer =
                args.fFp.cast<GrBlurredEdgeFragmentProcessor>();
        (void)_outer;
        auto mode = _outer.mode;
        (void)mode;
        SkString _input308 = SkStringPrintf("%s", args.fInputColor);
        SkString _sample308;
        if (_outer.inputFP_index >= 0) {
            _sample308 = this->invokeChild(_outer.inputFP_index, _input308.c_str(), args);
        } else {
            _sample308 = _input308;
        }
        fragBuilder->codeAppendf(
                "half inputAlpha = %s.w;\nhalf factor = 1.0 - inputAlpha;\n@switch (%d) {\n    "
                "case 0:\n        factor = exp((-factor * factor) * 4.0) - 0.017999999225139618;\n "
                "       break;\n    case 1:\n        factor = smoothstep(1.0, 0.0, factor);\n      "
                "  break;\n}\n%s = half4(factor);\n",
                _sample308.c_str(), (int)_outer.mode, args.fOutputColor);
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor& _proc) override {}
};
GrGLSLFragmentProcessor* GrBlurredEdgeFragmentProcessor::onCreateGLSLInstance() const {
    return new GrGLSLBlurredEdgeFragmentProcessor();
}
void GrBlurredEdgeFragmentProcessor::onGetGLSLProcessorKey(const GrShaderCaps& caps,
                                                           GrProcessorKeyBuilder* b) const {
    b->add32((int32_t)mode);
}
bool GrBlurredEdgeFragmentProcessor::onIsEqual(const GrFragmentProcessor& other) const {
    const GrBlurredEdgeFragmentProcessor& that = other.cast<GrBlurredEdgeFragmentProcessor>();
    (void)that;
    if (mode != that.mode) return false;
    return true;
}
GrBlurredEdgeFragmentProcessor::GrBlurredEdgeFragmentProcessor(
        const GrBlurredEdgeFragmentProcessor& src)
        : INHERITED(kGrBlurredEdgeFragmentProcessor_ClassID, src.optimizationFlags())
        , mode(src.mode) {
    if (src.inputFP_index >= 0) {
        inputFP_index = this->cloneAndRegisterChildProcessor(src.childProcessor(src.inputFP_index));
    }
}
std::unique_ptr<GrFragmentProcessor> GrBlurredEdgeFragmentProcessor::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrBlurredEdgeFragmentProcessor(*this));
}
