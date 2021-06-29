; ModuleID = 'MTPex10.c.ll'
source_filename = "MTPex10.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = dso_local global i32 0, align 4
@p1 = dso_local global i32* @a, align 8
@b = dso_local global i32 0, align 4
@p2 = dso_local global i32* @b, align 8
@c = dso_local global i32 0, align 4
@p3 = dso_local global i32* @c, align 8
@d = dso_local global i32 0, align 4
@p4 = dso_local global i32* @d, align 8
@p5 = dso_local global i32** @p1, align 8

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
bb:
  store i32* @b, i32** @p1, align 8
  %i1 = load i32*, i32** @p3, align 8
  store i32* %i1, i32** @p2, align 8
  %i2 = load i32**, i32*** @p5, align 8
  %i3 = load i32*, i32** %i2, align 8
  store i32* %i3, i32** @p4, align 8
  %i4 = load i32*, i32** @p3, align 8
  %i5 = load i32**, i32*** @p5, align 8
  store i32* %i4, i32** %i5, align 8
  %i6 = load i32**, i32*** @p5, align 8
  %i7 = load i32*, i32** %i6, align 8
  %i8 = load i32, i32* %i7, align 4
  ret i32 %i8
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-++20210626052612+b7c7b42db1d1-1~exp1~20210626033339.126"}
