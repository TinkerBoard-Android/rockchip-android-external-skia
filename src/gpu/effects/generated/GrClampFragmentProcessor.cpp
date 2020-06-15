/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrClampFragmentProcessor.fp; do not modify.
 **************************************************************************************************/
#include "GrClampFragmentProcessor.h"

#include "src/gpu/GrTexture.h"
#include "src/gpu/glsl/GrGLSLFragmentProcessor.h"
#include "src/gpu/glsl/GrGLSLFragmentShaderBuilder.h"
#include "src/gpu/glsl/GrGLSLProgramBuilder.h"
#include "src/sksl/SkSLCPP.h"
#include "src/sksl/SkSLUtil.h"
class GrGLSLClampFragmentProcessor : public GrGLSLFragmentProcessor {
public:
    GrGLSLClampFragmentProcessor() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrClampFragmentProcessor& _outer = args.fFp.cast<GrClampFragmentProcessor>();
        (void)_outer;
        auto clampToPremul = _outer.clampToPremul;
        (void)clampToPremul;
        SkString _input464 = SkStringPrintf("%s", args.fInputColor);
        SkString _sample464;
        if (_outer.inputFP_index >= 0) {
            _sample464 = this->invokeChild(_outer.inputFP_index, _input464.c_str(), args);
        } else {
            _sample464 = _input464;
        }
        fragBuilder->codeAppendf(
                "half4 inputColor = %s;\n@if (%s) {\n    half alpha = clamp(inputColor.w, 0.0, "
                "1.0);\n    %s = half4(clamp(inputColor.xyz, 0.0, alpha), alpha);\n} else {\n    "
                "%s = clamp(inputColor, 0.0, 1.0);\n}\n",
                _sample464.c_str(), (_outer.clampToPremul ? "true" : "false"), args.fOutputColor,
                args.fOutputColor);
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor& _proc) override {}
};
GrGLSLFragmentProcessor* GrClampFragmentProcessor::onCreateGLSLInstance() const {
    return new GrGLSLClampFragmentProcessor();
}
void GrClampFragmentProcessor::onGetGLSLProcessorKey(const GrShaderCaps& caps,
                                                     GrProcessorKeyBuilder* b) const {
    b->add32((int32_t)clampToPremul);
}
bool GrClampFragmentProcessor::onIsEqual(const GrFragmentProcessor& other) const {
    const GrClampFragmentProcessor& that = other.cast<GrClampFragmentProcessor>();
    (void)that;
    if (clampToPremul != that.clampToPremul) return false;
    return true;
}
GrClampFragmentProcessor::GrClampFragmentProcessor(const GrClampFragmentProcessor& src)
        : INHERITED(kGrClampFragmentProcessor_ClassID, src.optimizationFlags())
        , clampToPremul(src.clampToPremul) {
    if (src.inputFP_index >= 0) {
        inputFP_index = this->cloneAndRegisterChildProcessor(src.childProcessor(src.inputFP_index));
    }
}
std::unique_ptr<GrFragmentProcessor> GrClampFragmentProcessor::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrClampFragmentProcessor(*this));
}
GR_DEFINE_FRAGMENT_PROCESSOR_TEST(GrClampFragmentProcessor);
#if GR_TEST_UTILS
std::unique_ptr<GrFragmentProcessor> GrClampFragmentProcessor::TestCreate(GrProcessorTestData* d) {
    return GrClampFragmentProcessor::Make(/*inputFP=*/nullptr, d->fRandom->nextBool());
}
#endif
