; ModuleID = 'MTPex1.c.ll'
source_filename = "MTPex1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@c = dso_local global i32 6, align 4
@d = dso_local global i32 6, align 4
@z = dso_local global i32* @c, align 8
@w = dso_local global i32* @d, align 8
@a = dso_local global i32 0, align 4
@b = dso_local global i32 0, align 4
@x = dso_local global i32* null, align 8
@y = dso_local global i32* null, align 8

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
bb:
  %i1 = load i32, i32* @c, align 4
  %i2 = load i32, i32* @d, align 4
  %i3 = add nsw i32 %i1, %i2
  store i32 %i3, i32* @a, align 4
  %i4 = load i32, i32* @c, align 4
  %i5 = load i32, i32* @d, align 4
  %i6 = sub nsw i32 %i4, %i5
  store i32 %i6, i32* @b, align 4
  %i7 = load i32*, i32** @z, align 8
  %i8 = load i32, i32* %i7, align 4
  %i9 = add nsw i32 %i8, 1
  store i32 %i9, i32* @a, align 4
  %i10 = load i32, i32* @b, align 4
  %i11 = add nsw i32 %i10, 1
  store i32 %i11, i32* @b, align 4
  %i12 = load i32*, i32** @x, align 8
  %i13 = load i32, i32* %i12, align 4
  %i14 = load i32*, i32** @y, align 8
  %i15 = load i32, i32* %i14, align 4
  %i16 = add nsw i32 %i13, %i15
  ret i32 %i16
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-++20210626052612+b7c7b42db1d1-1~exp1~20210626033339.126"}
