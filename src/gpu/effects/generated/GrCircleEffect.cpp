/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrCircleEffect.fp; do not modify.
 **************************************************************************************************/
#include "GrCircleEffect.h"

#include "src/gpu/GrTexture.h"
#include "src/gpu/glsl/GrGLSLFragmentProcessor.h"
#include "src/gpu/glsl/GrGLSLFragmentShaderBuilder.h"
#include "src/gpu/glsl/GrGLSLProgramBuilder.h"
#include "src/sksl/SkSLCPP.h"
#include "src/sksl/SkSLUtil.h"
class GrGLSLCircleEffect : public GrGLSLFragmentProcessor {
public:
    GrGLSLCircleEffect() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrCircleEffect& _outer = args.fFp.cast<GrCircleEffect>();
        (void)_outer;
        auto edgeType = _outer.edgeType;
        (void)edgeType;
        auto center = _outer.center;
        (void)center;
        auto radius = _outer.radius;
        (void)radius;
        prevRadius = -1.0;
        circleVar = args.fUniformHandler->addUniform(&_outer, kFragment_GrShaderFlag,
                                                     kFloat4_GrSLType, "circle");
        fragBuilder->codeAppendf(
                R"SkSL(float2 prevCenter;
float prevRadius = %f;
half d;
@if (%d == 2 || %d == 3) {
    d = half((length((%s.xy - sk_FragCoord.xy) * %s.w) - 1.0) * %s.z);
} else {
    d = half((1.0 - length((%s.xy - sk_FragCoord.xy) * %s.w)) * %s.z);
})SkSL",
                prevRadius, (int)_outer.edgeType, (int)_outer.edgeType,
                args.fUniformHandler->getUniformCStr(circleVar),
                args.fUniformHandler->getUniformCStr(circleVar),
                args.fUniformHandler->getUniformCStr(circleVar),
                args.fUniformHandler->getUniformCStr(circleVar),
                args.fUniformHandler->getUniformCStr(circleVar),
                args.fUniformHandler->getUniformCStr(circleVar));
        SkString _input2566(args.fInputColor);
        SkString _sample2566;
        if (_outer.inputFP_index >= 0) {
            _sample2566 = this->invokeChild(_outer.inputFP_index, _input2566.c_str(), args);
        } else {
            _sample2566.swap(_input2566);
        }
        fragBuilder->codeAppendf(
                R"SkSL(
half4 inputColor = %s;
@if (%d == 1 || %d == 3) {
    %s = inputColor * clamp(d, 0.0, 1.0);
} else {
    %s = d > 0.5 ? inputColor : half4(0.0);
}
)SkSL",
                _sample2566.c_str(), (int)_outer.edgeType, (int)_outer.edgeType, args.fOutputColor,
                args.fOutputColor);
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor& _proc) override {
        const GrCircleEffect& _outer = _proc.cast<GrCircleEffect>();
        auto edgeType = _outer.edgeType;
        (void)edgeType;
        auto center = _outer.center;
        (void)center;
        auto radius = _outer.radius;
        (void)radius;
        UniformHandle& circle = circleVar;
        (void)circle;

        if (radius != prevRadius || center != prevCenter) {
            SkScalar effectiveRadius = radius;
            if (GrProcessorEdgeTypeIsInverseFill((GrClipEdgeType)edgeType)) {
                effectiveRadius -= 0.5f;
                // When the radius is 0.5 effectiveRadius is 0 which causes an inf * 0 in the
                // shader.
                effectiveRadius = std::max(0.001f, effectiveRadius);
            } else {
                effectiveRadius += 0.5f;
            }
            pdman.set4f(circle, center.fX, center.fY, effectiveRadius,
                        SkScalarInvert(effectiveRadius));
            prevCenter = center;
            prevRadius = radius;
        }
    }
    SkPoint prevCenter = float2(0);
    float prevRadius = 0;
    UniformHandle circleVar;
};
GrGLSLFragmentProcessor* GrCircleEffect::onCreateGLSLInstance() const {
    return new GrGLSLCircleEffect();
}
void GrCircleEffect::onGetGLSLProcessorKey(const GrShaderCaps& caps,
                                           GrProcessorKeyBuilder* b) const {
    b->add32((int32_t)edgeType);
}
bool GrCircleEffect::onIsEqual(const GrFragmentProcessor& other) const {
    const GrCircleEffect& that = other.cast<GrCircleEffect>();
    (void)that;
    if (edgeType != that.edgeType) return false;
    if (center != that.center) return false;
    if (radius != that.radius) return false;
    return true;
}
GrCircleEffect::GrCircleEffect(const GrCircleEffect& src)
        : INHERITED(kGrCircleEffect_ClassID, src.optimizationFlags())
        , edgeType(src.edgeType)
        , center(src.center)
        , radius(src.radius) {
    if (src.inputFP_index >= 0) {
        inputFP_index = this->cloneAndRegisterChildProcessor(src.childProcessor(src.inputFP_index));
    }
}
std::unique_ptr<GrFragmentProcessor> GrCircleEffect::clone() const {
    return std::unique_ptr<GrFragmentProcessor>(new GrCircleEffect(*this));
}
GR_DEFINE_FRAGMENT_PROCESSOR_TEST(GrCircleEffect);
#if GR_TEST_UTILS
std::unique_ptr<GrFragmentProcessor> GrCircleEffect::TestCreate(GrProcessorTestData* testData) {
    SkPoint center;
    center.fX = testData->fRandom->nextRangeScalar(0.f, 1000.f);
    center.fY = testData->fRandom->nextRangeScalar(0.f, 1000.f);
    SkScalar radius = testData->fRandom->nextRangeF(1.f, 1000.f);
    bool success;
    std::unique_ptr<GrFragmentProcessor> fp;
    do {
        GrClipEdgeType et = (GrClipEdgeType)testData->fRandom->nextULessThan(kGrClipEdgeTypeCnt);
        std::tie(success, fp) = GrCircleEffect::Make(/*inputFP=*/nullptr, et, center, radius);
    } while (!success);
    return fp;
}
#endif