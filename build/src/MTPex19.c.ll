; ModuleID = 'MTPex19.c.ll'
source_filename = "MTPex19.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@c = dso_local global i32 0, align 4
@e = dso_local global i32* @c, align 8
@d = dso_local global i32 0, align 4
@f = dso_local global i32* @d, align 8
@b = dso_local global i32 0, align 4
@g = dso_local global i32* null, align 8
@g1 = dso_local global i32 0, align 4
@g2 = dso_local global i32 0, align 4
@a = dso_local global i32 0, align 4

; Function Attrs: noinline nounwind uwtable
define dso_local void @fun3(i32 %arg) #0 {
bb:
  %i1 = load i32*, i32** @e, align 8
  store i32* %i1, i32** @f, align 8
  store i32* @b, i32** @e, align 8
  ret void
}

; Function Attrs: noinline nounwind uwtable
define dso_local void @fun1() #0 {
bb:
  store i32* @d, i32** @g, align 8
  %i = load i32*, i32** @g, align 8
  %i1 = load i32, i32* %i, align 4
  %i2 = icmp sgt i32 %i1, 1
  br i1 %i2, label %bb3, label %bb6

bb3:                                              ; preds = %bb
  %i4 = load i32*, i32** @e, align 8
  store i32* %i4, i32** @f, align 8
  %i5 = load i32, i32* @c, align 4
  call void @fun3(i32 %i5)
  br label %bb8

bb6:                                              ; preds = %bb
  %i7 = load i32*, i32** @g, align 8
  store i32* %i7, i32** @f, align 8
  br label %bb8

bb8:                                              ; preds = %bb6, %bb3
  ret void
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
bb:
  call void @fun1()
  call void @fun3(i32 3)
  %i1 = load i32*, i32** @e, align 8
  %i2 = load i32, i32* %i1, align 4
  %i3 = load i32*, i32** @f, align 8
  %i4 = load i32, i32* %i3, align 4
  %i5 = icmp sgt i32 %i2, %i4
  br i1 %i5, label %bb6, label %bb7

bb6:                                              ; preds = %bb
  br label %bb7

bb7:                                              ; preds = %bb6, %bb
  ret i32 0
}

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.1-++20210626052612+b7c7b42db1d1-1~exp1~20210626033339.126"}
