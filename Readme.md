

https://user-images.githubusercontent.com/63211297/132293042-09bc9f33-da92-4b7e-bbff-d5f7cc189a82.mp4

# Animator
# 개요

OpenGL로 구현된 범용 렌더링 엔진입니다.

이것을 테스트하기 위한 실행코드 샘플이 포함되어 있습니다.

샘플은 용 한마리가 건물 주변을 돌아다니는 것입니다. (?? 궁금하면 실행해봅시다 ??)

샘플의 용은 오픈소스, 건물은 학창시절에 설계한 '숲 도서관'(동대문도서관 리모델링) 입니다.

# 샘플 실행하는 법(윈도우즈용)
### 간단한 실행 방법
```./executable/Sample.exe```를 실행합니다.

> 샘플 데이터가 굉장히 큽니다. 90MB이상이므로 로딩에 시간이 오래 걸릴 수 있습니다.

### 빌드 방법
비주얼 스튜디오로 직접 빌드합니다.  
```./Renderer.sln```에서 ```Sample```프로젝트를 ```x64``` 플랫폼으로 빌드합니다.

### 샘플 조작 방법
- w : 전진
- s : 후진
- a : 좌로 이동
- d : 우로 이동
- CTRL(좌) : 하강
- spacebar : 상승
- 마우스 상/하 : (공중에 있을 때) 방향을 위/아래로
- 마우스 좌/우 : 화면 좌우 회전
- ESC : 종료
> 주의사항 : 앙각을 높이면 오작동 할 수 있습니다.

> 주의사항 : 마우스 커서가 사라지더라도 놀라지 마세요. ESC로 종료 할 수 있습니다.


## 만든 이유
이야기는 2011년, 김상병이었던 시절로 거슬러 갑니다. 건축학도로서 맨날 써 온 캐드가 어떻게 작동하는지, 열심히 하던 게임들은 어떻게 만드는지 궁금해서 프로그래밍 공부를 시작했습니다. 그때는 화면에 점 찍는 법만 누가 알려준다면 3차원을 구현해 볼 수 있을 것 같다는 생각을 했었는데, 안타깝게도 군인으로서는 얻을 수 있는 자료가 너무 한정적이어서 프로그래밍의 맛만 보고 끝났습니다.

그로부터 9년 후, 우여곡절 끝에 이번엔 아예 개발자가 되기로 했습니다. 목표 진로는 막연하게 캐드, 게임, 그래픽, 인공지능, 로봇 등 이었습니다.

1년 반 정도 기초를 탄탄하게 다진 후, OpenGL을 공부했습니다.

이제 처음에 목표했던 캐드 또는 게임을 위한 렌더링 엔진을 만들어보기로 했습니다.

다만 추상화를 어디까지 해야 하는지는 여전히 고민이고, 아직은 작업중입니다.

# 구현한 기능
1. 음영처리
	- 앰비언트(값, 텍스처)
	- 디퓨트(값, 텍스처)
	- 스펙큘러(값, 텍스처)
	- 노멀맵
	- 투명도
2. 셰이더 유틸리티 클래스
    - 셰이더 컴파일 및 링크
    - 유니폼 데이터 전달
3. 모델파일 불러오기
4. 스켈레탈 애니메이션
5. 카메라
6. 빛
7. 물체 이동

# 빌드 방법
소스코드를 직접 임베드합니다. 

- 다음 디렉토리를 프로젝트에 복사합니다.
    - ```./Animator```
    - ```./include```
    - ```./lib```
    - ```./Shader```
- 속성관리자에서 속성파일을 프로젝트에 추가합니다.
    - ```./x64.props```
        - Assimp 라이브러리 링크
        - include 디렉토리를 인클루드 경로로 추가
- Assimp 동적라이브러리 파일을 프로젝트에 추가합니다.
    - `./assimp-vc142-mt.dll` 을 실행파일이 있는 디렉토리에 복사합니다.
- Animator.hpp를 소스코드에 인클루드 합니다.
    
    ```c++
    #include "../Animator/Animator.hpp"
    ```
    

디렉토리의 계층구조가 다음과 같습니다.

```
root
|---Animator
|---include
|---lib
|---Shader
|---<실행파일 디렉토리>
					|---<실행 파일>
					|---assimp-vc142-mt.dll
```

> 빌드 방법이 다소 복잡합니다. lib 또는 dll을 만드는 편이 더 나을지 고민중입니다.




---

# 상세 설명
```Model::ptr		assimp_loader(const std::string& path);```
- 모델을 불러옵니다.
- 매개변수
	- 모델 파일의 경로입니다.
- 반환
	- 해당 경로의 모델을 불러와서 반환합니다.


# Model
이름 그대로 모형을 담는 그릇입니다. 모형에 대한 데이터 자체보다는 트리 구조를 구성하는 노드에 해당합니다. 모델은 또다른 모델을 자식으로 가질 수 있습니다.
```Object```를 상속합니다.

## 멤버 타입
```c++
typedef std::shared_ptr<Model>			ptr;
typedef std::pair<glm::vec3, glm::vec3>	box;
```

## 멤버 변수
### children
```Model```의 공유포인터 타입을 저장하는 컨테이너

### meshes
```Mesh```의 공유포인터 타입을 저장하는 컨테이너

## 생성자
### 기본생성자

## 메서드
### ```void		draw(Shader& shader, const glm::mat4& world);```
정적인 모형을 그립니다. 호출시 자식노드의 ```draw```함수를 재귀적으로 호출합니다.
- 매개변수
	- shader: 출력에 사용할 셰이더
	- world: 위치 변경이나 회전 등 변형을 위한 행렬

### ```void		draw(Shader& shader, const glm::mat4& world, double time, uint animation);```
애니메이션을 그립니다
- 매개변수
	- shader: 출력에 사용할 셰이더
	- world: 위치 변경이나 회전 등 변형을 위한 행렬
	- time: 애니메이션의 시간대를 설정합니다. 해당 시간대로 각 뼈대의 행렬이 설정됩니다. 단위는 ms입니다.
	- animaition: 애니메이션의 번호를 지정합니다.

### ```void		add_mesh(Mesh::ptr mesh);```
메시를 추가합니다.
- 매개변수
	- mesh: 추가할 메시

### ```void		add_child(ptr x);```
모델을 자식 노드에 추가합니다.
- 매개변수
	- x: 추가할 모델

### ```box			get_bounding_box();```
바운딩 박스를 구합니다. pair의 첫 번째는 작은 수, 두 번째는 큰 수로 된 두 좌표입니다.

# Shader
셰이더입니다.

## 관련된 타입
### shader_type
셰이더 종류 입니다.
- ```vertex``` : 버텍스 셰이더 타입
- ```tess_control``` : 테셀레이션 컨트롤 셰이더 타입
- ```tess_evaluation``` : 테셀레이션 평가 셰이더 타입
- ```geometry``` : 지오메트리 셰이더 타입
- ```fragment``` : 프래그먼트 셰이더 타입
- ```compute``` : 컴퓨트 셰이더 타입


## 생성자
### 기본 생성자

## 메서드

### ```GLuint		compile_shader(const std::string& path, shader_type type);```
주어진 경로의 셰이더 코드를 컴파일 합니다. 컴파일 된 셰이더들은 내부에 자동으로 저장됩니다.
- 매개변수:
	- path: 셰이더 코드의 경로
	- type: 셰이더의 종류
- 반환:
	- 컴파일 된 셰이더 객체의 아이디

### ```void		link_shader_program();```
컴파일 된 셰이더를 모두 링크합니다.

### ```GLuint		get_program() const;```
- 반환
	- 프로그램 객체의 아이디

### ```void		use();```
```glUseProgram(get_program());```과 동일합니다.

### ```void		set_uniform(const std::string& name, float value);```
### ```void		set_uniform(const std::string& name, int value);```
### ```void		set_uniform(const std::string& name, const glm::vec3& value);```
### ```void		set_uniform(const std::string& name, const glm::mat3& value, bool transpose = GL_FALSE);```
### ```void		set_uniform(const std::string& name, const glm::mat4& value, bool transpose = GL_FALSE);```
유니폼 데이터를 전송합니다.
- 입력
	- name: 셰이더 프로그램에서의 변수명
	- value: 전송할 값
	- transpose: 행렬인 경우, 트랜스포즈 여부

## 사용례
```c++
Shader	shader;
shader.compile_shader(vertex_shader.glsl, shader_type::vertex);
shader.compile_shader(frag_shader.glsl, shader_type::fragment);
shader.link_shader_program();
shader.use();
```
# Camera
카메라를 쉽게 다루기 위한 클래스입니다.
```Object```를 상속합니다.

## 멤버 변수
### ```float		fovy```
위아래 방향의 시야각입니다.

### ```float		aspect```
화면의 종횡비입니다. ```가로 / 세로``` 입니다.

### ```float		z_far```
출력할 최대 거리입니다. 이것보다 멀리 있는 물체는 출력되지 않습니다.

### ```float		z_near```
출력할 최소 걸입니다. 이것보다 가까이 있는 물체는 출력되지 않습니다.

### ```glm::mat4	projection```
투영행렬입니다. 투시도(perspective)를 그리며, 정규화된 장치공간으로의 변형 행렬입니다. 버텍스 셰이더의 ```projection```에 해당합니다. 

### ```glm::mat4	view```
시각 행렬입니다. 버텍스 셰이더의 ```model```에 해당합니다. update_view를 호출해서 갱신합니다.


## 생성자
### 기본생성자
### 다른 생성자
```	c++
Camera(
	glm::vec3	position,
	glm::vec3	direction,
	glm::vec3	up = glm::vec3(0, 0, 1),
	float		fovy = glm::pi<float>() / 3,
	float		aspect = 16.f / 9,
	float		z_far = 10000,
	float		z_near = 1
);
```
- 매개변수
	- position: 첫 위치
	- direction: 보는 방향
	- up: 카메라의 윗 방향(좌우 회전시 기준이 되는 벡터)

## 메서드
### ```void				update_projection()```
투영 행렬을 갱신합니다. 멤버를 수정하지 않는다면 따로 갱신할 필요가 없습니다.
### ```void				update_view()```
시각 행렬을 갱신합니다. 


# Light

## 멤버 변수
### ```float		strength```
빛의 세기의 제곱근입니다. 셰이더에서 빛의 세기는 거리의 제곱에 반비례하게 설정되어있습니다. 빛의 거리와 같은 값으로 설정하면 해당 위치에서는 그 값이 1배가 됩니다.

예를들어 현재 위치에서 10만큼 떨어진 곳에 빛이 있고, 그 빛의 strength를 10으로 설정하면 현재 위치에서는 세기가 1이 됩니다. 

### ```vec3			color```
빛의 색깔입니다.


## 생성자
### 기본생성자

## 메서드
### ```void				draw(Shader& shader)```
셰이더에 정보를 넘깁니다.


# Object
변환행렬을 멤버로 갖는 클래스입니다. 오일러 회전각을 통한 이동을 돕는 클래스입니다.

## 멤버 타입
```typedef std::shared_ptr<Object>		ptr;```
## 멤버 변수
### ```glm::mat4			matrix```
matrix[0] == x축, 전방

matrix[1] == y축, 좌측

matrix[2] == z축, 위

matrix[3] == 위치


### ```glm::vec3			up```
윗 부분을 가리키는 고정된 벡터입니다.

## 생성자
### 기본생성자
### ```Object(const glm::mat4& mat)```

### ```Object(glm::vec3 position, glm::vec3 x,	glm::vec3 z)```
- 매개변수
	- position: 위치
	- x: 방향
	- z: 윗 방향. x와 z가 수직이 아닌 경우, z를 우선하여 그램슈미츠 과정으로 나머지 좌표축을 정합니다.

## 메서드
### ``` virtual Object&		move(const glm::vec3& v)```
- 매개변수
	- v: v만큼 이동합니다.

### ``` virtual Object&		move_forward(float len)```
전방(x축 방향)으로 이동합니다.
- 매개변수
	- len: 이동할 거리

### ``` virtual Object&		move_left(float len)```
y축 방향으로 이동합니다.
- 매개변수
	- len: 이동할 거리

### ``` virtual Object&		move_up(float len)```
up 방향으로 이동합니다. z축 방향이 아님에 주의
- 매개변수
	- len: 이동할 거리


### ``` virtual Object&		pitch(float rad)```
x축을 들어 올립니다. y축을 회전축으로, 시계방향으로 합니다.
> 주의사항: 앙각이 지나치게 높아지면 오작동 합니다. 아직 고치지 않았습니다.
- 매개변수
	- rad: 회전각(라디안 단위)

### ``` virtual Object&		yaw(float rad)```
전방을 수평으로 회전시킵니다. z축을 회전축으로, 반시계방향으로 회전합니다. (사실 진짜 yaw임)
- 매개변수
	- rad: 회전각(라디안 단위)

### ``` virtual Object&		yaw(float rad, glm::vec3 up)```
전방을 수평으로 회전시킵니다. up축을 회전축으로, 반시계방향으로 회전합니다. (사실 가짜 yaw임)
- 매개변수
	- rad: 회전각(라디안 단위)


### ``` glm::vec3			get_position() const```
- 반환
	- 위치(== matrix[3])

### ``` glm::vec3			get_direction() const```
- 반환
	- 전방(== matrix[0])

### ``` glm::vec3			get_left() const```
- 반환
	- 좌측(== matrix[1])

### ``` glm::vec3			get_z() const```
- 반환
	- z축(== matrix[2])

### ``` void				set_identity()```
행렬을 항등행렬로 설정합니다.

### ``` void				set_position(const glm::vec3& v)```
- 매개변수
	- v: 설정하려는 위치



# Mesh
실제 정점 데이터를 담고 있으며, 모델을 불러오기만 한다면 직접 다룰 일은 없습니다.


---

# 기타 주의사항

1. Material을 초기화 하세요
```c++
Material::init_default_texture();
Material::init_default_texture_normal();
```
텍스처 기본값과 노멀맵 기본값을 초기화해야 하는데, glad 초기화가 선행되어야 하고, glad 초기화를 위해서는 glfw 초기화가 선행되어야 합니다. 따라서 부득이하게 정적변수를 따로 초기화해야 합니다.

2. Object의 pitch 함수를 주의하세요  
고각에서 오작동 합니다.

---

# 외부 소스

## [Assimp](http://assimp.org/)
각종 3D포맷 파일을 읽어들이는 것을 돕는 오픈소스 라이브러리입니다.

## [Stb Image](https://github.com/nothings/stb)
이미지 파일을 읽어들이는 것을 돕는 오픈소스 라이브러리입니다.

## [용 모델](http://wp.me/P3dmoi-1tI)
샘플에 쓰인 용의 모형파일입니다.

## [바닥 텍스처](https://kr.freepik.com/free-photo/rustic-stone-texture-background_15753412.htm#page=1&query=%EB%B0%94%EB%8B%A5&position=3)
샘플에 쓰인 바닥 텍스처입니다.
