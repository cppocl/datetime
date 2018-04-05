# datetime

![](header_image.jpg)

## Overview

C++ Date and time classes.
Designed to be an easier to use alternative to the C++ 11 chrono library.
The library only uses header files, which means they can be used purely by including the header file.

## Code Examples

```cpp
#include "datetime/Date.hpp"
#include "datetime/NowDate.hpp"

int main()
{
    ocl::Date gmt_now_date = ocl::NowDate::Now();
    ocl::Date my_birthday(1, ocl::Date::January, 1980);

    auto days_alive = my_birthday.GetDifferenceInDays(gmt_now_date);

    printf("You have been alive %lu days\n", static_cast<unsigned long>(days_alive));
}
```
