# 15: subtypes; Inheritance; Virtual Functions

## **What is subtype:** 

**#S is a subtype of T:** For any instance where an object of type T is expected, an object of type S can be supplied without changing the correctness of the original computation. (简单来说，T能正常用的，S也能正常用)

<img src="/Users/michaelxu/Library/Application Support/typora-user-images/image-20200803152428988.png" alt="image-20200803152428988" style="zoom:30%;" />

**注意：**when use a subtype where a supertype is expected, it is not converted to the supertype. 所以subtypes 并不是 type-conversion，使用过程中不需要类型转换。

## Creating Subtypes:

1. Add one or more operations.
2. Strengthen the postcondition of one or more operations.
3. Weaken the precondition of one or more operations.

### · Add one ore more operations:

> 因为新加入的功能并不妨碍原本的功能实现

### · Strengthening Postconditions

> 例子：在 `A:: f (int arg)`中多加入输出，比如多print a message.
>
> <img src="/Users/michaelxu/Library/Application Support/typora-user-images/image-20200803154344074.png" alt="image-20200803154344074" style="zoom:30%;" />

### · Weaken the precondition

> 1. Weaken the REQUIRES clause
> 2. Weaken the argument type
>
> <img src="/Users/michaelxu/Library/Application Support/typora-user-images/image-20200803154710225.png" alt="image-20200803154710225" style="zoom:33%;" />

## Subclasses

> 也就是inheritance. 通常使用public inheritance
>
> <img src="/Users/michaelxu/Library/Application Support/typora-user-images/image-20200803155044194.png" alt="image-20200803155044194" style="zoom:25%;" />

