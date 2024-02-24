Markdown 메모
=
## ♦︎ 큰 제목
```
입력)
This is an H1
=
```
결과물)

This is an H1
=

## ♦︎ 작은 제목
```
입력)
This is an H2
---
```
결과물)

This is an H2
---

## ♦︎ 글머리
```
입력)
# This is a H1
## This is a H2
### This is a H3
#### This is a H4
##### This is a H5
###### This is a H6
```
결과물)
# This is a H1
## This is a H2
### This is a H3
#### This is a H4
##### This is a H5
###### This is a H6

## ♦︎ BlockQuote 인용

```
입력)
> This is a first blockqute.
>	> This is a second blockqute.
>	>	> This is a third blockqute.
```
결과물)
> This is a first blockqute.
>	> This is a second blockqute.
>	>	> This is a third blockqute.

## ♦︎ 목록
### ♦︎ 순서있는 목록

```
입력)
1. Item
  1. SubItem
  2. SubItem
2. Item
  1. SubItem
  2. SubItem
```
결과물)
1. Item
   1. SubItem
   2. SubItem
2. Item
   1. SubItem
   2. SubItem

### ♦︎ 순서없는 목록
*, +, - 지원

```
입력)
* Item
   * SubItem
   * SubItem
+ Item
   + SubItem
   + SubItem
- Item
   - SubItem
   - SubItem
```
결과물)
* Item
   * SubItem
   * SubItem
+ Item
   + SubItem
   + SubItem
- Item
   - SubItem
   - SubItem

혼용해서 사용할 수 있다.
```
입력)
* Item
   + SubItem
     - SubItem
   - SubItem
     * SubItem
   * SubItem
```
결과물)
* Item
   + SubItem
     - SubItem
   - SubItem
     * SubItem
   * SubItem

## ♦︎ 블록 표시
### ♦︎ 들여쓰기
4개의 공백 또는 하나의 탭으로 들여쓰기를 만나면 변환되기 시작하여 들여쓰지 않은 행을 만날때까지 변환이 계속된다.
```
입력)
This is a normal paragraph:
<반드시 빈 줄이 있어야 한다>
    This is a code block.
<반드시 빈 줄이 있어야 한다> 
end code block.
```
표시)
This is a normal paragraph:

    This is a code block.
    
end code block.
### ♦︎ \<pre\>\<code\>{code}\</code\>\</pre\> 이용방식
```
입력)
<pre>
<code>
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }

}
</code>
</pre>
```
결과물)
<pre>
<code>
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }

}
</code>
</pre>

### ♦︎ 코드블럭코드("```") 을 이용하는 방법
```
입력)
"```"
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }
}
"```"
```
결과물)
```
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }
}
```
코드블록코드를 지정하면 [문법강조(Syntax Highlighting)](https://docs.github.com/en/github/writing-on-github/creating-and-highlighting-code-blocks#syntax-highlighting) 할 수 있다.
```
입력)
```java
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }
}
```
```
결과물)
```java
public class BootSpringBootApplication {
  public static void main(String[] args) {
    System.out.println("Hello, Honeymon");
  }
}
```

## ♦︎ 수평선
예
```
* * *

***

*****

- - -

---------------------------------------
```
결과물)
* * *

***

*****

- - -

---------------------------------------

## ♦︎ 링크
● 참조링크
```
입력)
Link: [Google][googlelink]

[googlelink]: https://google.com "Go google"
```
결과물)
Link: [Google][googlelink]

[googlelink]: https://google.com "Go google"

● 외부링크
```
입력)
[Google](https://google.com, "google link")
```
결과물)
[Google](https://google.com, "google link")

● 자동연결
일반적인 URL 혹은 이메일주소인 경우 적절한 형식으로 링크를 형성한다.
```
입력)
* 외부링크: <http://example.com/>
* 이메일링크: <address@example.com>
```
결과물)
* 외부링크: <http://example.com/>
* 이메일링크: <address@example.com>

## ♦︎ 강조

문장 중간에 사용할 경우에는 **띄어쓰기**를 사용하는 것이 좋다.

```
입력)
*single asterisks*
_single underscores_
**double asterisks**
__double underscores__
~~cancelline~~
```
결과)
*single asterisks*
_single underscores_
**double asterisks**
__double underscores__
~~cancelline~~

## ♦︎ 이미지

```
입력)
![Alt text](./img/img-A.png)
![Alt text](./img/img-A.png "Optional title")
```
결과)
![Alt text](./img/img-A.png)
![Alt text](./img/img-A.png "Optional title")

사이즈 조절 기능은 없기 때문에 \<img width="" height=""\>\</img\>를 이용한다.
```
입력)
<img src="./img/img-A.png" width="450px" height="300px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
<img src="./img/img-A.png" width="40%" height="30%" title="px(픽셀) 크기 설정" alt="RubberDuck"></img>
```
결과)
<img src="./img/img-A.png" width="450px" height="300px" title="px(픽셀) 크기 설정" alt="RubberDuck"></img><br/>
<img src="./img/img-A.png" width="40%" height="30%" title="px(픽셀) 크기 설정" alt="RubberDuck"></img>

## ♦︎ Line Breaks 줄바꿈
\<br\>를 사용하면 줄바꿈을 할 수 있다.
```
예)
안녕하세요. <br> 줄바꿈을 합니다.
```
결과)
안녕하세요. <br> 줄바꿈을 합니다.

## ♦︎ Backslash Escapes
특수문자를 표현할 때, 표시될 문자 앞에 \를 넣고 특수문자를 쓰면 됩니다.
```
예)
* 특수문자
\* 특수문자
```
결과)
* 특수문자
\* 특수문자

## ♦︎ 체크 리스트
```
예)
- [x] this is a complete item
- [ ] this is an incomplete item
```
결과)
- [x] this is a complete item
- [ ] this is an incomplete item

## ♦︎ Table 테이블
3개 이상의 -(hyphen/dash) 기호를 사용하여 헤더와 셀을 구분
(Colons) 기호로 셀(열/칸) 안에 내용을 정렬할 수 있다.
테이블 양옆의 |(vertical bar) 기호는 생략 가능하다.
### Table 생성
```
예)
헤더1|헤더2|헤더3|헤더4
---|---|---|---
셀1|셀2|셀3|셀4
셀5|셀6|셀7|셀8
셀9|셀10|셀11|셀12
```
결과)
헤더1|헤더2|헤더3|헤더4
---|---|---|---
셀1|셀2|셀3|셀4
셀5|셀6|셀7|셀8
셀9|셀10|셀11|셀12

### Table 정렬
```
예)
헤더1|헤더2|헤더3
:---|:---:|---:
Left|Center|Right
1|2|3
4|5|6
7|8|9

```
결과)
헤더1|헤더2|헤더3
:---|:---:|---:
Left|Center|Right
1|2|3
4|5|6
7|8|9
