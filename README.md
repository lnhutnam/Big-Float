# Big float

Floating-point numbers are typically packed into a computer datum as the sign bit, the exponent field, and the significand or mantissa, from left to right. For the IEEE 754 binary formats (basic and extended) which have extant hardware implementations, they are apportioned as follows:

|Type|Sign|Exponent|Significand field|Total bits|Exponent bias|Bits precision|Number of decimal digits|
|---|---|---|---|---|---|---|---|
|Half (IEEE 754-2008)|1|5|10|16|15|11|~3.3|
|Single|1|8|23|32|127|24|~7.2|
|Double|1|11|52|64|1023|53|~15.9|
|x86 extended precision|1|15|64|80|16383|64|~19.2|
|Quad|1|15|128|112|16383|64|~34.0|

Thiết kế kiểu dữ liệu biểu diễn số chấm động có độ chính xác Quadruple-precision (độ chính xác gấp 4 lần) độ lớn 128 bit có cấu trúc biểu diễn như sau:
![](https://upload.wikimedia.org/wikipedia/commons/2/24/IEEE_754_Quadruple_Floating_Point_Format.svg)

Hãy định nghĩa các hàm sau:<br>
a. Hàm Nhập: void ScanQfloat (Qfloat &x)<br>
b. Hàm xuất: void PrintQfloat( Qfloat x)<br>
c. Hàm chuyển đổi số Qfloat nhị phân sang thập phân: Qfloat BinToDec(bool * bit) <br>
d. Hàm chuyển đổi số Qfloat thập phân sang nhị phân bool * DecToBin(Qfloat x) <br>
e. Các toán tử “+”, “-”, “*”, “/” <br>

## x86 extended precision

![](https://upload.wikimedia.org/wikipedia/commons/e/e1/X86_Extended_Floating_Point_Format.svg)

## Double

![](https://upload.wikimedia.org/wikipedia/commons/a/a9/IEEE_754_Double_Floating_Point_Format.svg)

## Single

![](https://upload.wikimedia.org/wikipedia/commons/d/d2/Float_example.svg)

## Half (IEEE 754-2008)

![](https://upload.wikimedia.org/wikipedia/commons/2/21/IEEE_754r_Half_Floating_Point_Format.svg)
