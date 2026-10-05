# OpenCVStudy

Visual Studio C++ 기반 OpenCV 학습 프로젝트입니다.

## 개발 환경

- Visual Studio C++ 도구 집합 v145
- Windows SDK 10.0
- C++20
- OpenCV 4.14.0 Windows x64

## 빌드 준비

OpenCV SDK는 저장소에 포함하지 않습니다. 로컬에 준비한 OpenCV 4.14.0의 파일을 다음과 같이 배치합니다.

```text
ThirdParty/
  include/
    opencv2/                       # OpenCV 헤더
  lib/
    opencv_world4140.lib
    opencv_world4140d.lib
  bin/
    opencv_world4140.dll
    opencv_world4140d.dll
    opencv_videoio_ffmpeg4140_64.dll
```

`OpenCVStudy.slnx`를 열고 **x64 / Debug** 또는 **x64 / Release** 구성으로 빌드합니다. 현재 OpenCV 링크 설정은 x64 구성에 지정되어 있습니다.

실행 파일은 `Binaries/`, 중간 빌드 파일은 `Intermediate/`에 생성됩니다. 빌드 후 `ThirdParty/bin/`의 DLL이 실행 파일 폴더로 복사됩니다.

`ThirdParty/`, 빌드 결과물, Visual Studio 캐시와 사용자 설정은 Git에서 제외합니다. Git LFS는 사용하지 않습니다.

OpenCV 및 관련 구성 요소의 라이선스 파일은 `Licenses/`에 보관합니다.
