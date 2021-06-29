; ModuleID = 'MTPex12.c.ll'
source_filename = "MTPex12.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = dso_local global i32 0, align 4
@p = dso_local global i32* @x, align 8
@y = dso_local global i32 0, align 4
@q = dso_local global i32* @y, align 8
@r = dso_local global i32* null, align 8
@z = dso_local global i32 0, align 4
@s = dso_local global i32* null, align 8

; Function Attrs: noinline nounwind uwtable
define dso_local void @fun() #0 {
bb:
  %i = alloca i32, align 4
  store i32* @y, i32** @p, align 8
  store i32* %i, i32** @r, align 8
  ret void
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
bb:
  %i = alloca i32, align 4
  store i32* %i, i32** @r, align 8
  call void @fun()
  store i32* @x, i32** @r, align 8
  store i32* %i, i32** @s, align 8
  %i8 = load i32*, i32** @s, align 8
  store i32* %i8, i32** @r, align 8
  ret i32 0
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-++20210626052612+b7c7b42db1d1-1~exp1~20210626033339.126"}
