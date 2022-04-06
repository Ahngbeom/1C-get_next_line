# get_next_line [![bahn's 42 get_next_line Score](https://badge42.vercel.app/api/v2/cl1n6fb2j003009l0lfanbfyx/project/2065203)](https://github.com/JaeSeoKim/badge42)
# get_next_line의 목적

    get_next_line은 반복문 안에서 외부 파일의 내용을 
    
    개행문자까지 또는 EOF를 만날때까지 출력하는 함수이다. 

    개행문자를 만났다면 해당 라인을 출력하고

    다시 get_next_line 함수를 호출하면서 출력한 문자열의 다음 라인부터 출력한다.

    매개변수로 fd(파일디스크립터 값)과 line(출력할 파일내용이 저장될 메모리 주소)을 받게된다.

    매개변수 line이 이중포인터인 이유는 

    단일 포인터 line을 매개변수 인자로 보내게 되면 함수 종료시 line은 사라지기 때문에 
    
    그 주소값인 이중 포인터를 이용해 line을 보내고 단일 포인터 line을 수정하는 방식으로 진행해야 문자열을 전달받을 수 있다.

    지역 변수나 매개 변수는 스택 영역에 할당되어진다.

    스택 영역은 함수의 호출과 함께 할당되며, 함수의 호출이 완료되면 소멸한다.

    get_next_line은 외부 파일을 불러온 후 (open 함수)

# get_next_line 설명

  ## 상수
    
   * ### BUFFER_SIZE

            read 함수에서 파일의 내용을 읽을 수 있는 최대 Byte 수이다.

            BUFFER_SIZE가 1일 때도, 9999일 때도, 10000000 (1000만)일 때도 함수가 알맞게 동작해야 한다.

            Makefile에서 정의해주었듯이 #ifndef 전처리기를 이용하여 BUFFER_SIZE 라는 상수가 정의되어 있지 않다면 임의의 값으로 정의를 해주었다.

            과제 PDF에도 나와있듯이 "당신의 프로그램은 -D BUFFER_SIZE=xx 플래그를 붙여서 컴파일 해야 합니다. 그것은 여러분의 get_next_line에서 read함수를 호출하기 위한 buffer size로 사용될 것입니다." 라고 적혀있기 때문에

            상수 이름을 동일하게 정의해주어야 한다.

   * ### OPEN_MAX

        <a href="https://code4human.tistory.com/123"> 참고자료 </a>

            BONUS 파트에서의 요구사항은 다중 파잍 디스크립터를 관리할 수 있어야 하는 것이다.

            만약 1개의 파일이 아닌 2개 이상의 파일을 읽고 라인 출력을 하려는 경우에도

            함수는 완벽하게 수행이 되어야 한다.

            따라서 OPEN_MAX 는 읽을 수 있는 최대 파일 디스크립터 수이다.

            FD의 최대값은 OPEN_MAX라는 값이다.

            OPEN_MAX 값은 플랫폼에 따라 다르다.

            Unix 시스템에서 C언어의 OPEN_MAX는 limits.h에 정의되어있다.

            OPEN_MAX 또한 #ifndef 전처리기를 이용하여 OPEN_MAX 라는 상수가 정의되어 있지 않다면 임의의 값으로 정의를 해주었다.

            뮬리넷에서 따로 정의를 해주고 컴파일을 한다면 해당 OPEN_MAX값을 가지고 함수를 실행하게 된다.

## 변수
    
* ### static char *stc_buff[OPEN_MAX]
   
        파일의 내용을 출력하는 과정에서 

        이미 출력한 라인과 아직 출력하지 않은 라인을 구분하기 위해서

        static 정적 포인터 변수를 선언해야한다.

        static 변수는 함수가 종료되더라도 프로그램(main)을 종료하기 전까지 계속 남아있는 변수이다.

    >    ![화면 캡처 2021-01-16 021203](https://user-images.githubusercontent.com/57256332/104757327-44778700-57a0-11eb-96c1-677d37c18c7b.png)

        get_next_line 함수를 수행할 때마다 파일의 내용을 static 포인터 변수 메모리에 저장시켜놓고,

        하나의 라인을 line 메모리에 저장이 완료되었다면 

        다음 get_next_line 함수를 호출할 때 다음 라인을 출력해야하기 때문에,
        
        해당 라인을 제외한 나머지 파일의 내용을 static 메모리에 저장한다.

        만약 파일의 내용 끝까지 line 메모리에 저장했다면

        static 포인터를 NULL로 초기화시켜준다.

* ### char  buff[BUFFER_SIZE + 1]
    
        read 함수를 통해 읽어들인 파일의 내용을 저장할 용도.

        buff 마지막 인덱스 위치에 '\0'를 추가하기 위해 
        
        BUFFER_SIZE보다 1 증가시킨 값을 buff의 용량으로 설정한다.

* ### ssize_t   read_size
    
        read 함수의 반환 값을 저장할 용도.

        read 함수는 읽어들인 데이터의 길이를 반환한다.

* ### ssize_t   lf_idx

        파일의 내용 중 줄바꿈 문자의 위치 인덱스를 저장하는 용도.

        파일의 내용이 저장되어있는 stc_buff 에서 줄바꿈 문자의 존재 유무를 검사하는 용도.


## 동작 원리

    먼저 if 문을 통해 

    fd 값이 0보다 작은 값이거나, OPEN_MAX 상수 값보다 큰 값이거나,
    
    line 포인터 변수가 NULL 이거나, BUFFER_SIZE가 0보다 작거나 같은 값이라면

    get_next_line 함수를 제대로 수행할 수 없기에 (-1)를 리턴해준다.


    
    read 함수로 읽어들인 파일의 내용을 문자열로 buff 변수에 저장한다.

    read 함수를 수행해 read_size가 0보다 큰 값이라면 while문을 반복한다.

    buff 마지막 인덱스 공간에 '\0'을 대입한다.

    만약 stc_buff[fd]가 NULL 포인터라면

    즉, 아직 메모리가 할당되지 않은 상태라면(파일의 내용을 처음 읽기 시작한 경우) ft_strdup함수를 통해 

    메모리를 buff 용량만큼 할당한 후 buff의 내용을 복제한다.

    여기서 stc_buff의 인덱스 값을 fd로 설정한 이유는

    bonus 파트에서 2개 이상의 파일을 읽을 수 있어야 함으로 

    2개 이상의 fd 값이 들어올 때마다 각각의 다른 static 공간에 저장이 이루어져 하기 때문이다.

    만약 stc_buff[fd]가 메모리 할당된 상태라면

    저장된 문자열에 읽어들인 문자열을 이어붙인 후

    새로운 메모리 공간에 이어붙인 문자열을 저장한다.

    ft_strjoin 함수에서 기존 stc_buff[fd] (join 처리하기 전) 메모리를 해제 후

    이어붙인 문자열이 저장된 새로운 메모리의 주소를 stc_buff[fd]에 다시 대입한다.

    stc_buff에 파일의 내용을 저장하는 if 조건 분기문을 수행 후

    stc_buff에 저장된 문자열 중에 '\n' 줄바꿈 문자가 있는지 검사한다.

    find_line_feed 함수는 줄바꿈 문자가 존재하지 않을 경우 (-1)을 리턴한다.
    
    존재하는 경우 줄바꿈 문자의 위치 인덱스를 넘겨주게된다.

    줄바꿈 문자가 있다면 extract_line 함수를 수행하게 된다.
    
    extract_line 함수는 line 메모리에 줄바꿈 문자까지의 문자열을 저장한 후

    줄바꿈 문자 이후에 문자열이 남아있다면 남아있는 문자열을 stc_buff에 저장한다.

    여기에서도 기존 stc_buff는 메모리를 해제하고, 남아있는 문자열이 저장된 메모리의 주소를 다시 stc_buff에 대입한다.

    남아있는 문자열이 없다면 단순하게 stc_buff 메모리를 해제시켜주고 NULL 포인터로 초기화만 시켜준다.

<a href="https://www.it-note.kr/201">read 함수 관련 참고 블로그</a>

    즉, EOF에 도달하여 파일에서 더 이상 읽을 내용이 없을 경우

    while 문을 수행하지 않고 end_of_file 함수를 수행하게 된다.

    end_of_file 함수에서 stc_buff에 남아있는 문자열이 있는지 검사를 하게 된다.

    개행 문자는 없지만 남아있는 문자열이 있을 경우(널 종료 문자가 있을 경우) 
    
    line에 해당 문자열 위치를 대입한 후 

    stc_buff는 NULL 포인터로 초기화 시켜준다.

    남아있는 문자열이 없을 경우 line에 ft_strdup을 이용하여 '\0'을 저장시켜주었다.

    이 과정까지 마치게 되면 최종적으로 get_next_line의 수행을 마치게 된다. 



<hr>
   
    end_of_file()에서 stc_buff의 메모리 해제? - KO
        => end_of_file() *stc_buff 조건 분기문이 필요할까?

            stc_buff에 남아있는 데이터 중 개행문자가 없다면

            남아있는 데이터의 메모리 위치 주소를 line에 대입하여 추출/출력

            여기서 stc_buff를 메모리 해제를 시켜버리면

            line 에 대입된 메모리 주소가 해제되는 것이기 때문에

            main에서 line을 출력할 수 없게된다.

            (line 메모리 해제는 main에서 해주겟지)

            line에 대입 후 stc_buff는 NULL 포인터로 초기화 시켜준다.


    end_of_file()에서 else 문을 추가하여 가독성 높임- OK

    BUFFER_SIZE를 10000000(1000만)으로 정의했을 때 - Segmentation fault
        => 보통 스택 사이즈가 윈도우는 1메가, 리눅스는 8메가로 설정되어있다.
            10000000 byte = 10MB이기 때문에 스택 오버플로우가 발생해 작동이 안된다.
            1개의 static 변수를 선언하고, malloc 등을 이용해 동적 할당하여 힙 영역에 잡는다. 


    파일내용

	abcde\n
	12345\n

    buffer_size 
        6
    ====================================================
    extract_line 함수는 

    read()를 통해 읽어들인 문자열을 stc_buff에 복사 또는 연결한 결과를 가지고

    라인을 추출하는 함수이다.

    개행문자까지의 라인을 추출한 후

    개행 문자 다음에 남은 문자열이 없다하더라도

    return (1)을 하게 된다.

    stc_buff에는 아직 파일의 내용을 모두 복사 또는 연결했는지 모르기 때문에

    get_next_line 함수 호출을 반복해야한다.



