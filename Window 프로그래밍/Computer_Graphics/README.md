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

|단계 명(Stage Name)|설명|
|---|---|
|Input Assembler|그리기 위한 모든 입력을 조합한다.|
|Vertex Shader|각 점들의 위치나 기타 정보들로 음영을 잘 입힐 수 있게 준비한다. Transform & light 연산 역시 이 곳에서 일어난다.|
|Hull Shader|간략한 도형들을 세분화하는 역할을 한다.|
|Tessellator|Hull Shader에서 만든 더 세분화된 도형을 삼각형으로 더 잘게 쪼개서 표현한다. </br> 잘라낸 삼각형에서 텍스쳐를 매핑하기 위한 정보까지 추출한다.|
|Domain Shader|위에서 나온 세분화된 삼각형의 각 꼭지점의 위치를 계산한다.|
|Geometry Shader|삼각형, 선, 점 등에 대한 계산을 실행한다.|
|Rasterizer|2차원으로 변환된 위치 정보들을 화면에 표시할 준비를 한다.|
|Pixel Shader|픽셀에 저장된 정보를 이용하여 색상을 칠한다. </br>또한, 보간 등의 그래픽 기법을 적용해 최종 픽셀을 만들어 낸다.|
|Output Merger| 깊이 스텐실 버퍼등을 이용하여 지금까지 그린 이미지가 화면에 나타날지 등에 대한 처리를 한 후 화면에 보낸다.|

Direct3D Primitive Type
-

> POINTLIST
>  - 점으로 이루어진 리스트이다.
>  - 배열에 점에 대한 위치 정보를 적어주면 각 점을 그린다.

> LINELIST
>  - 선으로 된 리스트이다.
>  - 첫번째 점과 두번째 점을 잇는 선을 만들고 세번째 점과 네번째 점을 잇는 선을 만든다.
>  - 따라서 2 이상의 짝수여야 정상적으로 실행된다.

> LINESTRIP
>   - 연속된 선으로 구성된 도형이다.
>   - 첫번째와 두번째 점을 잇고, 두번째와 세번째 점을 이어주는 방식이다.

> TRIANGLELIST
>   - 삼각형 목록이다.
>   - 3개의 점으로 삼각형 하나를 표현하기 때문에 3의 배수로 되어있다.

> TRIANGLESTRIP
>   - 연결된 삼각형 도형이다.
>   - 첫번째, 두번째, 세번째 점으로 삼각형 하나를 그리고 두번째, 세번째, 네번째 점으로 삼각형을 그린다.
>   - n개의 삼각형을 그리기 위해서는 3 + (n-1) = n+2개의 점이 필요하다.

HLSL(High Level Shader Language)
-
일반 언어의 발전과 비슷하게 GPU의 성능이 올라가면서 셰이더 언어도 C 스타일이 고급 언어로 발전하게 되었다. 그 중 DirectX에서 사용하는 것을 DirectX HLSL이라고 한다. 
