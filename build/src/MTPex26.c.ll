; ModuleID = 'MTPex26.c.ll'
source_filename = "MTPex26.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = dso_local global i32 0, align 4
@b = dso_local global i32 0, align 4
@x = dso_local global i32* null, align 8
@y = dso_local global i32* null, align 8
@d = dso_local global i32 0, align 4
@c = dso_local global i32 0, align 4
@v = dso_local global i32* null, align 8
@u = dso_local global i32* null, align 8
@z = dso_local global i32* null, align 8

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @p() #0 {
bb:
  %i = load i32, i32* @a, align 4
  %i1 = load i32, i32* @b, align 4
  %i2 = icmp slt i32 %i, %i1
  br i1 %i2, label %bb3, label %bb5

bb3:                                              ; preds = %bb
  store i32* @a, i32** @x, align 8
  %i4 = load i32*, i32** @x, align 8
  store i32* %i4, i32** @y, align 8
  br label %bb6

bb5:                                              ; preds = %bb
  br label %bb6

bb6:                                              ; preds = %bb5, %bb3
  ret i32 0
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
bb:
  store i32* @d, i32** @x, align 8
  store i32* @c, i32** @y, align 8
  %i1 = call i32 @p()
  %i2 = load i32*, i32** @x, align 8
  %i3 = load i32, i32* %i2, align 4
  ret i32 %i3
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-++20210626052612+b7c7b42db1d1-1~exp1~20210626033339.126"}
