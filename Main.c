/* Coded with C Grammar for MSVC in Windows
   This Source uses UTF-8-BOM encoding & CRLF (Windows) line endings
   Alias : SingleTetris - Main.c & Last Moded : 2019.07.08.
   Tetris Program Coded by IRACK
   ICON : <a href="https://www.freepik.com/free-photos-vectors/logo">Logo vector created by freepik - www.freepik.com</a>
*/

#include "Main.h"
#include "include/Music.h"
#include "include/Tetris.h"
#include "include/WinAPI.h"


int main(int argc, char const * argv[]) {
    // 0. 게임에 사용될 데이터 선언
    _Bool struct_board[YSIZ][XSIZ] = {{0}};  // 테트리스 전체 구조(판) 저장용 배열
    struct object_info objstat;  // 객체(움직이는 테트리스 도형) 상태 저장용 구조체
    int ylimit = 3;  // y축 상한선 설정
    int ttspeed = 60;  // 테트리스 도형 자동 내림 스피드 (숫자가 증가할 수록 느려짐)
    int key = 0;  // _getch() 리턴값 저장용 변수

    // 2. 시작 화면 표시
    musicPlay(BGM);  // 배경 음악 재생
    showStart(3);  // 3초 동안 대기

    // 2. 테트리스 기본 구성요소 생성
    contructWall(struct_board);  // 벽 생성

    // 3. 게임 진행
    while (1) {
        // 3-0. 임시 변수 선언
        int saved_down_count = 0;  // 카운트가 ttspeed회 누적되면 자동으로 한칸 내림

        // 3-1. 신규 도형 생성하기
        getNewShape(&objstat);  // 새로운 도형 받아오기

        // 3-2. 바닥까지 내려가기 LOOP
        while (1) {
            // 3-2-0. 임시 변수 선언
            _Bool if_crash_occured = 0;  // 충돌 발생여부 확인용 플래그

            // 3-2-1. 사용자 입력 처리
            // 참고 : https://boongubbang.tistory.com/46
            if (_kbhit()) {  // 방향키는 한번 입력시 두가지 값을 반환
                key = _getch();  // 방향키(224)인지 스페이스키인지 받아옴
                if (key == 224) {  // 방향키일 경우
                    letObjMove(struct_board, &objstat, _getch());  // 어느 방향의 방향키인지 전달 후 도형 움직이기
                } else if (key == SPACE) {  // 스테이스일 경우 -> 하드 드롭
                    while (!letObjMove(struct_board, &objstat, DOWN));  // 바닥에 닿을 때 까지 반복
                    saved_down_count = 0;
                    if_crash_occured = 1;
                }
            }

            // 3-2-2. 바뀐 모양 출력
            printGameBoard(struct_board, &objstat, ylimit);  // 현재 상황 보여주기

            // 3-2-3. 도형 한칸 내리기
            if (saved_down_count == ttspeed) {  // 누적 카운트와 설정된 스피드가 같을 때
                if_crash_occured = letObjMove(struct_board, &objstat, DOWN);  // 자동으로 한칸씩 내림, 바닥에 닿음 확인
                saved_down_count = 0;  // 카운트 누적 초기화
            }

            // 3-2-4. 바닥에 닿았는지 검사
            if (if_crash_occured) {  // 1) 닿은 경우 - 완성된 줄 삭제
                musicPlay(DROP);  // 효과음 재생
                buildBoard(struct_board, &objstat, NORESET);  // 바닥 충돌 발생시 객체를 구조에 통합
                checkLineFull(struct_board);  // 한줄 채움 확인 후 삭제
                break;  // 바닥에 닿으면 브레이크
            } else {  // 2) 닿지 않은 경우 - 자동으로 한칸 내리기 위해 누적 수치 증가 시키기
            saved_down_count++;  // 카운트 1 증가
            }
        }

        // 3-3. 게임오버 체크
        if (checkGameOver(struct_board, ylimit)) {  // 게임 패배 확인
            break;  // 참이면 브레이크
        }
    }

    // 4. 결과 표시 및 재시작 여부 확인
    showTetrisResult(argv[0]);

    return 0;
}
