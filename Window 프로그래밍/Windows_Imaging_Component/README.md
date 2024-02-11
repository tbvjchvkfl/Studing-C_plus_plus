Windows Imaging Component
-
WIC는 마이크로 소프트에서 디지털 이미지들을 처리하기 위해 추가한 low-level API이다.
BMP, GIF, JPEG, PNG등의 포멧들을 읽고 쓸 수 있다.

COM Initialize
-
WIC는 COM기반이라 초기화를 해주어야 하는데, ***CoInitialize()*** 함수를 사용하고 초기화한다.
