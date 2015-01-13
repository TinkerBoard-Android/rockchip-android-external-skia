/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gm.h"
#include "SkPaint.h"
#include "SkPictureRecorder.h"

static SkPicture* make_picture() {
    SkPictureRecorder rec;
    SkCanvas* canvas = rec.beginRecording(100, 100);

    SkPaint paint;
    paint.setAntiAlias(true);
    SkPath path;

    paint.setColor(0x800000FF);
    canvas->drawRect(SkRect::MakeWH(100, 100), paint);

    paint.setColor(0x80FF0000);
    path.moveTo(0, 0); path.lineTo(100, 0); path.lineTo(100, 100);
    canvas->drawPath(path, paint);
    
    paint.setColor(0x8000FF00);
    path.reset(); path.moveTo(0, 0); path.lineTo(100, 0); path.lineTo(0, 100);
    canvas->drawPath(path, paint);

    paint.setColor(0x80FFFFFF);
    paint.setXfermodeMode(SkXfermode::kPlus_Mode);
    canvas->drawRect(SkRect::MakeXYWH(25, 25, 50, 50), paint);

    return rec.endRecording();
}

// Exercise the optional arguments to drawPicture
//
class PictureGM : public skiagm::GM {
public:
    PictureGM() : fPicture(make_picture()) {}

protected:
    SkString onShortName() SK_OVERRIDE {
        return SkString("pictures");
    }

    SkISize onISize() SK_OVERRIDE {
        return SkISize::Make(450, 120);
    }

    void onDraw(SkCanvas* canvas) SK_OVERRIDE {
        canvas->translate(10, 10);

        SkMatrix matrix;
        SkPaint paint;

        canvas->drawPicture(fPicture);
        
        matrix.setTranslate(110, 0);
        canvas->drawPicture(fPicture, &matrix, NULL);
        
        matrix.postTranslate(110, 0);
        canvas->drawPicture(fPicture, &matrix, &paint);

        paint.setAlpha(0x80);
        matrix.postTranslate(110, 0);
        canvas->drawPicture(fPicture, &matrix, &paint);
    }

private:
    SkAutoTUnref<SkPicture> fPicture;

    typedef skiagm::GM INHERITED;
};

DEF_GM( return SkNEW(PictureGM); )
