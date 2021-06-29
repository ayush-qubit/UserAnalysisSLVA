; ModuleID = 'MTPex28.c.ll'
source_filename = "MTPex28.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@c = dso_local global i32 6, align 4
@d = dso_local global i32 6, align 4
@z = dso_local global i32* @c, align 8
@w = dso_local global i32* @d, align 8
@b = dso_local global i32 0, align 4
@a = dso_local global i32 0, align 4
@x = dso_local global i32* null, align 8
@y = dso_local global i32* null, align 8

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
bb:
  %i1 = load i32*, i32** @w, align 8
  %i2 = load i32, i32* %i1, align 4
  store i32 %i2, i32* @b, align 4
  br label %bb3

bb3:                                              ; preds = %bb20, %bb
  %i4 = load i32, i32* @c, align 4
  %i5 = icmp sgt i32 %i4, 0
  br i1 %i5, label %bb6, label %bb21

bb6:                                              ; preds = %bb3
  %i7 = load i32, i32* @c, align 4
  %i8 = icmp eq i32 %i7, 4
  br i1 %i8, label %bb9, label %bb14

bb9:                                              ; preds = %bb6
  %i10 = load i32*, i32** @z, align 8
  %i11 = load i32, i32* %i10, align 4
  %i12 = load i32, i32* @c, align 4
  %i13 = add nsw i32 %i11, %i12
  store i32 %i13, i32* @a, align 4
  br label %bb20

bb14:                                             ; preds = %bb6
  %i15 = load i32*, i32** @x, align 8
  %i16 = load i32, i32* %i15, align 4
  %i17 = load i32*, i32** @z, align 8
  %i18 = load i32, i32* %i17, align 4
  %i19 = sub nsw i32 %i16, %i18
  store i32 %i19, i32* @a, align 4
  br label %bb20

bb20:                                             ; preds = %bb14, %bb9
  br label %bb3, !llvm.loop !2

bb21:                                             ; preds = %bb3
  store i32* @a, i32** @x, align 8
  store i32* @b, i32** @y, align 8
  %i22 = load i32*, i32** @x, align 8
  %i23 = load i32, i32* %i22, align 4
  %i24 = load i32*, i32** @y, align 8
  %i25 = load i32, i32* %i24, align 4
  %i26 = add nsw i32 %i23, %i25
  ret i32 %i26
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-++20210626052612+b7c7b42db1d1-1~exp1~20210626033339.126"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.mustprogress"}
