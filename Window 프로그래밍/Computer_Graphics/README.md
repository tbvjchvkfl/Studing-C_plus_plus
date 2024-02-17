Computer Graphics
-

기존에는 컴퓨터 메모리에 이미지를 저장하고 있다가 그래픽 카드 메모리로 전송하는 방식을 사용했다.
즉, 그래픽 카드가 Frame Buffer(Front Buffer)를 갱신할 때 CPU에 요청해서 데이터를 읽어 가는 방식이었다. 이에 게임 개발자들은 주로 메모리에 화면에 그릴 이미지를 들고 있는 경우가 많았는데, 이를 구분해서 Back Buffer라고 한다.

BITMAP
-
Bit + Map의 약자로 비트로 구성된 맵을 의미한다. 디지털 이미지를 저장하는 이미지 파일 포멧 중 하나이며 가장 기본적인 방식이다.
각 픽셀당 할당하는 비트의 크기에 따라 다양한 색을 표현할 수 있게 된다.


Alpha Blending
-
기존 색상에 알파값(투명도)을 더하는 것

파이프 라인
-
3차원 그래픽에서 어떻게 그리는지를 담당하는 것이 ***렌더링 파이프라인***이다.
파이프 라인의 순서는 다음과 같다.</br>
Input Assembler -> Vertex Shader -> Hull Shader -> Tessellator -> DomainShader -> GeometryShader -> Rasterizer -> Pixel Shader -> Output Merger

