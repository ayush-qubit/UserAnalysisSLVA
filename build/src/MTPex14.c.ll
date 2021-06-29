; ModuleID = 'MTPex14.c.ll'
source_filename = "MTPex14.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@c = dso_local global i32 6, align 4
@d = dso_local global i32 6, align 4
@z = dso_local global i32* @c, align 8
@w = dso_local global i32* @d, align 8
@a = dso_local global i32 0, align 4
@e = dso_local global i32* @a, align 8
@b = dso_local global i32 0, align 4
@f = dso_local global i32* @b, align 8

; Function Attrs: noinline nounwind uwtable
define dso_local void @func1() #0 {
bb:
  store i32* @d, i32** @z, align 8
  store i32* @c, i32** @w, align 8
  ret void
}

; Function Attrs: noinline nounwind uwtable
define dso_local void @func2() #0 {
bb:
  %i = load i32*, i32** @z, align 8
  store i32* %i, i32** @e, align 8
  %i1 = load i32*, i32** @w, align 8
  store i32* %i1, i32** @f, align 8
  ret void
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
bb:
  call void @func1()
  call void @func2()
  ret i32 0
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-++20210626052612+b7c7b42db1d1-1~exp1~20210626033339.126"}
